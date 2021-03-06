/*
 * Copyright (c) 2014 Travis Geiselbrecht
 * Copyright (c) 2014 Chris Anderson
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <platform/qcom.h>
#include <platform/uart_dm.h>

#ifdef QCOM_ENABLE_DISPLAY
#include <platform/msm_panel.h>
#endif

void target_early_init(void)
{
#ifdef QCOM_ENABLE_UART
	uart_dm_init(2, 0, BLSP1_UART1_BASE);
#endif
}

void target_init(void)
{
#ifdef QCOM_ENABLE_DISPLAY
	target_display_init("");
#endif
}
