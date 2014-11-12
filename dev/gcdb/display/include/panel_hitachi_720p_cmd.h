/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
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
 *  * Neither the name of The Linux Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
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

/*---------------------------------------------------------------------------
 * This file is autogenerated file using gcdb parser. Please do not edit it.
 * Update input XML file to add a new entry or update variable in this file
 * VERSION = "1.0"
 *---------------------------------------------------------------------------*/

#ifndef _PANEL_HITACHI_720P_CMD_H_

#define _PANEL_HITACHI_720P_CMD_H_
/*---------------------------------------------------------------------------*/
/* HEADER files                                                              */
/*---------------------------------------------------------------------------*/
#include "panel.h"

/*---------------------------------------------------------------------------*/
/* Panel configuration                                                       */
/*---------------------------------------------------------------------------*/

static struct panel_config hitachi_720p_cmd_panel_data = {
  "qcom,mipi_dsi_hitachi_720p_cmd", "dsi:0:", "qcom,mipi-dsi-panel",
  10, 1, "DISPLAY_1", 0, 384000000, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel resolution                                                          */
/*---------------------------------------------------------------------------*/
static struct panel_resolution hitachi_720p_cmd_panel_res = {
  720, 1280, 23, 16, 8, 0, 7, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel Color Information                                                   */
/*---------------------------------------------------------------------------*/
static struct color_info hitachi_720p_cmd_color = {
  24, 2, 0xff, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Panel Command information                                                 */
/*---------------------------------------------------------------------------*/
static char hitachi_720p_cmd_on_cmd0[] = {
0x11, 0x00, 0x05, 0x80, };


static char hitachi_720p_cmd_on_cmd1[] = {
0xB0, 0x04, 0x23, 0x80, };


static char hitachi_720p_cmd_on_cmd2[] = {
	0x21, 0x00, 0x29, 0xC0,
	0xCA, 0x01, 0x80, 0x88, 0x8C, 0xBC, 0x8C, 0x8C,
	0x8C, 0x18, 0x3F, 0x14, 0xFF, 0x0A, 0x4A, 0x37,
	0xA0, 0x55, 0xF8, 0x0C, 0x0C, 0x20, 0x10, 0x3F,
	0x3F, 0x00, 0x00, 0x10, 0x10, 0x3F, 0x3F, 0x3F,
	0x3F, 0xFF, 0xFF, 0xFF };

static char sharp_720p_cmd_on_cmd2[] = {
	0x21, 0x00, 0x29, 0xC0,
	0xCA, 0x01, 0x80, 0x8A, 0x8C, 0xC8, 0x8C, 0x80,
	0x8C, 0x18, 0x3F, 0x14, 0xFF, 0x0A, 0x4A, 0x37,
	0xA0, 0x55, 0xF8, 0x0C, 0x0C, 0x20, 0x10, 0x3F,
	0x3F, 0x00, 0x00, 0x10, 0x10, 0x3F, 0x3F, 0x3F,
	0x3F, 0xFF, 0xFF, 0xFF
};

static char hitachi_720p_cmd_on_cmd3[] = {
0xB0, 0x03, 0x23, 0x80, };


static char hitachi_720p_cmd_on_cmd4[] = {
0x03, 0x00, 0x39, 0xC0,
	0x51, 0x0E, 0xFF, 0xFF,  };


static char hitachi_720p_cmd_on_cmd5[] = {
0x53, 0x2C, 0x15, 0x80,
 };


static char hitachi_720p_cmd_on_cmd6[] = {
0x55, 0x01, 0x15, 0x80, };


static char hitachi_720p_cmd_on_cmd7[] = {
0x05, 0x00, 0x39, 0xC0,
	0x2A, 0x00, 0x00, 0x02,
	0xCF, 0xFF, 0xFF, 0xFF};


static char hitachi_720p_cmd_on_cmd8[] = {
0x05, 0x00, 0x39, 0xC0,
	0x2B, 0x00, 0x00, 0x04,
	0xFF, 0xFF, 0xFF, 0xFF
 };


static char hitachi_720p_cmd_on_cmd9[] = {
0x36, 0x00, 0x15, 0x80  };


static char hitachi_720p_cmd_on_cmd10[] = {
0x3a, 0x77, 0x15, 0x80 };


static char hitachi_720p_cmd_on_cmd11[] = {
0x29, 0x00, 0x05, 0x80  };


static struct mipi_dsi_cmd hitachi_720p_cmd_on_command[] = {
{ 0x4 , hitachi_720p_cmd_on_cmd0, 120, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd1, 0, 0},
{ 0x28 , hitachi_720p_cmd_on_cmd2, 0, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd3, 0, 0},
{ 0x8 , hitachi_720p_cmd_on_cmd4, 0, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd5, 0, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd6, 0, 0},
{ 0xc , hitachi_720p_cmd_on_cmd7, 0, 0},
{ 0xc , hitachi_720p_cmd_on_cmd8, 20, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd9, 20, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd10, 0, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd11, 20, 0}
};
#define HITACHI_720P_CMD_ON_COMMAND 12

static struct mipi_dsi_cmd sharp_720p_cmd_on_command[] = {
{ 0x4 , hitachi_720p_cmd_on_cmd0, 120, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd1, 0, 0},
{ 0x28 , sharp_720p_cmd_on_cmd2, 0, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd3, 0, 0},
{ 0x8 , hitachi_720p_cmd_on_cmd4, 0, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd5, 0, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd6, 0, 0},
{ 0xc , hitachi_720p_cmd_on_cmd7, 0, 0},
{ 0xc , hitachi_720p_cmd_on_cmd8, 20, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd9, 20, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd10, 0, 0},
{ 0x4 , hitachi_720p_cmd_on_cmd11, 20, 0}
};
#define SHARP_720P_CMD_ON_COMMAND 12

/*
static char hitachi_720p_cmdoff_cmd0[] = {
0x28, 0x00, 0x05, 0x80 };


static char hitachi_720p_cmdoff_cmd1[] = {
0x10, 0x00, 0x05, 0x80 };

static struct mipi_dsi_cmd hitachi_720p_cmd_off_command[] = {
{ 0x4 , hitachi_720p_cmdoff_cmd0, 0},
{ 0x4 , hitachi_720p_cmdoff_cmd1, 0}
};
#define HITACHI_720P_CMD_OFF_COMMAND 2
*/

static struct command_state hitachi_720p_cmd_state = {
  0, 1
};

/*---------------------------------------------------------------------------*/
/* Command mode panel information                                            */
/*---------------------------------------------------------------------------*/
static struct commandpanel_info hitachi_720p_cmd_command_panel = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Video mode panel information                                              */
/*---------------------------------------------------------------------------*/

static struct videopanel_info hitachi_720p_cmd_video_panel = {
  0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*---------------------------------------------------------------------------*/
/* Lane Configuration                                                        */
/*---------------------------------------------------------------------------*/

static struct lane_configuration hitachi_720p_cmd_lane_config = {
  4, 0, 1, 1, 1, 1
};


/*---------------------------------------------------------------------------*/
/* Panel Timing                                                              */
/*---------------------------------------------------------------------------*/
const uint32_t hitachi_720p_cmd_timings[] = {
  0xb3, 0x8c, 0x1d, 0x00, 0x20, 0x94, 0x20, 0x8e, 0x20, 0x03, 0x04
};


/*
static struct mipi_dsi_cmd hitachi_720p_cmd_rotation[] = {

};
#define TOSHIBA_720P_VIDEO_ROTATION 0
*/

static struct panel_timing hitachi_720p_cmd_timing_info = {
  0x04, 0x04, 34, 59
};

// TODO
static struct panel_reset_sequence hitachi_720p_cmd_panel_reset_seq = {
{ 1, 0, 1, }, { 20, 200, 20, }, 2
};

/*---------------------------------------------------------------------------*/
/* Backlight Settings                                                        */
/*---------------------------------------------------------------------------*/

// TODO
static struct backlight hitachi_720p_cmd_backlight = {
  1, 1, 4095, 100, 1, "PMIC_8921"
};
#define HITACHI_720P_CMD_SIGNATURE 0xFFF4


#endif /*_PANEL_HITACHI_720P_CMD_H_*/
