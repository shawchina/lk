/*
 * Copyright (c) 2008, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <debug.h>
#include <err.h>
#include <printf.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <dev/fbcon.h>
#include <lib/console.h>

#include "font5x12.h"

struct pos {
	int x;
	int y;
};

static struct fbcon_config *config = NULL;

#define RGB565_BLACK        0x0000
#define RGB565_WHITE        0xffff

#define RGB888_BLACK        0x000000
#define RGB888_WHITE        0xffffff

#define FONT_WIDTH      5
#define FONT_HEIGHT     12

static uint16_t         BGCOLOR;
static uint16_t         FGCOLOR;

static struct pos       cur_pos;
static struct pos       max_pos;

static void fbcon_drawglyph(uint16_t *pixels, uint16_t paint, unsigned stride,
                            unsigned *glyph)
{
	unsigned x, y, data;
	stride -= FONT_WIDTH;

	data = glyph[0];
	for (y = 0; y < (FONT_HEIGHT / 2); ++y) {
		for (x = 0; x < FONT_WIDTH; ++x) {
			if (data & 1)
				*pixels = paint;
			data >>= 1;
			pixels++;
		}
		pixels += stride;
	}

	data = glyph[1];
	for (y = 0; y < (FONT_HEIGHT / 2); y++) {
		for (x = 0; x < FONT_WIDTH; x++) {
			if (data & 1)
				*pixels = paint;
			data >>= 1;
			pixels++;
		}
		pixels += stride;
	}
}

void fbcon_flush(void)
{
	if (config->update_start)
		config->update_start();
	if (config->update_done)
		while (!config->update_done());
}

/* TODO: Take stride into account */
static void fbcon_scroll_up(void)
{
	unsigned short *dst = config->base;
	unsigned short *src = dst + (config->width * FONT_HEIGHT);
	unsigned count = config->width * (config->height - FONT_HEIGHT);

	while (count--) {
		*dst++ = *src++;
	}

	count = config->width * FONT_HEIGHT;
	while (count--) {
		*dst++ = BGCOLOR;
	}

	fbcon_flush();
}

/* TODO: take stride into account */
void fbcon_clear(void)
{
	unsigned count = config->width * config->height;
	memset(config->base, BGCOLOR, count * ((config->bpp) / 8));
}


static void fbcon_set_colors(unsigned bg, unsigned fg)
{
	BGCOLOR = bg;
	FGCOLOR = fg;
}

void fbcon_putc(char c)
{
	uint16_t *pixels;

	/* ignore anything that happens before fbcon is initialized */
	if (!config)
		return;

	if ((unsigned char)c > 127)
		return;
	if ((unsigned char)c < 32) {
		if (c == '\n')
			goto newline;
		else if (c == '\r')
			cur_pos.x = 0;
		return;
	}

	pixels = config->base;
	pixels += cur_pos.y * FONT_HEIGHT * config->width;
	pixels += cur_pos.x * (FONT_WIDTH + 1);
	fbcon_drawglyph(pixels, FGCOLOR, config->stride,
	                font5x12 + (c - 32) * 2);

	cur_pos.x++;
	if (cur_pos.x < max_pos.x)
		return;

newline:
	cur_pos.y++;
	cur_pos.x = 0;
	if (cur_pos.y >= max_pos.y) {
		cur_pos.y = max_pos.y - 1;
		fbcon_scroll_up();
	} else
		fbcon_flush();
}

void fbcon_setup(struct fbcon_config *_config)
{
	uint32_t bg;
	uint32_t fg;

	ASSERT(_config);

	config = _config;

	switch (config->format) {
		case FB_FORMAT_RGB565:
			bg = RGB565_BLACK;
			fg = RGB565_WHITE;
			break;

	    case FB_FORMAT_RGB888:
	            bg = RGB888_BLACK;
	            fg = RGB888_WHITE;
	            break;
		default:
			dprintf(CRITICAL, "unknown framebuffer pixel format\n");
			ASSERT(0);
			break;
	}

	fbcon_set_colors(bg, fg);

#ifndef ENABLE_2NDSTAGE_BOOT
	fbcon_clear();
	fbcon_flush();
#endif

	cur_pos.x = 0;
	cur_pos.y = 0;
	max_pos.x = config->width / (FONT_WIDTH+1);
	max_pos.y = (config->height - 1) / FONT_HEIGHT;
}

struct fbcon_config* fbcon_display(void)
{
    return config;
}

static int cmd_fbcon(int argc, const cmd_args *argv)
{
	if (argc < 2) {
	notenoughargs:
		printf("not enough arguments\n");
	usage:
		printf("usage:\n");
		printf("%s config\n", argv[0].str);
		return ERR_GENERIC;
	}

	if (!strcmp(argv[1].str, "config")) {
		printf("config %p\n", config);

		if(config) {
			printf("\tbase %p\n", config->base);
			printf("\twidth %u\n", config->width);
			printf("\theight %u\n", config->height);
			printf("\tstride %u\n", config->stride);
			printf("\tbpp %u\n", config->bpp);
			printf("\tformat %u\n", config->format);
			printf("\tupdate_start %p\n", config->update_start);
			printf("\tupdate_done %p\n", config->update_done);
		}
	} else {
		printf("unknown command\n");
		goto usage;
	}

	return NO_ERROR;
}

STATIC_COMMAND_START
#if LK_DEBUGLEVEL > 0
STATIC_COMMAND("fbcon", "fbcon commands", &cmd_fbcon)
#endif
STATIC_COMMAND_END(fbcon);
