/*
 * Copyright © 2017-2019 The Crust Firmware Authors.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 */

#include <bitmap.h>
#include <clock.h>
#include <device.h>
#include <stdint.h>
#include <clock/sunxi-ccu.h>
#include <platform/devices.h>

#include "sunxi-ccu.h"

static struct sunxi_ccu_clock r_ccu_clocks[R_CCU_CLOCK_COUNT] = {
	[R_CCU_CLOCK_OSC24M] = FIXED_CLOCK("osc24m", 24000000, 0),
	[R_CCU_CLOCK_OSC32K] = FIXED_CLOCK("osc32k", 32768, 0),
	[R_CCU_CLOCK_OSC16M] = FIXED_CLOCK("osc16m", 16000000, 0),
	[R_CCU_CLOCK_AHB0]   = {
		.info = {
			.name     = "ahb0",
			.max_rate = 300000000,
			.flags    = CLK_CRITICAL,
		},
		.parents = CLOCK_PARENTS(4) {
			{ .dev = &r_ccu.dev, .id = R_CCU_CLOCK_OSC32K },
			{ .dev = &r_ccu.dev, .id = R_CCU_CLOCK_OSC24M },
			{
				.dev  = &ccu.dev,
				.id   = CCU_CLOCK_PLL_PERIPH0,
				.vdiv = BITFIELD(8, 5),
			},
			{ .dev = &r_ccu.dev, .id = R_CCU_CLOCK_OSC16M },
		},
		.reg = 0x0000,
		.mux = BITFIELD(16, 2),
		.p   = BITFIELD(4, 2),
	},
	[R_CCU_CLOCK_APB0] = {
		.info.name = "apb0",
		.parents   = CLOCK_PARENT(r_ccu, R_CCU_CLOCK_AHB0),
		.reg       = 0x000c,
		.p         = BITFIELD(0, 2),
	},
	[R_CCU_CLOCK_R_PIO] = {
		.info.name = "r_pio",
		.parents   = CLOCK_PARENT(r_ccu, R_CCU_CLOCK_APB0),
		.gate      = BITMAP_INDEX(0x0028 >> 2, 0),
	},
	[R_CCU_CLOCK_R_CIR] = {
		.info = {
			.name     = "r_cir",
			.max_rate = 100000000,
		},
		.parents = CLOCK_PARENT(r_ccu, R_CCU_CLOCK_APB0),
		.gate    = BITMAP_INDEX(0x0028 >> 2, 1),
		.reset   = BITMAP_INDEX(0x00b0 >> 2, 1),
	},
	[R_CCU_CLOCK_R_TIMER] = {
		.info.name = "r_timer",
		.parents   = CLOCK_PARENT(r_ccu, R_CCU_CLOCK_APB0),
		.gate      = BITMAP_INDEX(0x0028 >> 2, 2),
		.reset     = BITMAP_INDEX(0x00b0 >> 2, 2),
	},
	[R_CCU_CLOCK_R_RSB] = {
		.info.name = "r_rsb",
		.parents   = CLOCK_PARENT(r_ccu, R_CCU_CLOCK_APB0),
		.gate      = BITMAP_INDEX(0x0028 >> 2, 3),
		.reset     = BITMAP_INDEX(0x00b0 >> 2, 3),
	},
	[R_CCU_CLOCK_R_UART] = {
		.info.name = "r_uart",
		.parents   = CLOCK_PARENT(r_ccu, R_CCU_CLOCK_APB0),
		.gate      = BITMAP_INDEX(0x0028 >> 2, 4),
		.reset     = BITMAP_INDEX(0x00b0 >> 2, 4),
	},
	[R_CCU_CLOCK_R_I2C] = {
		.info.name = "r_i2c",
		.parents   = CLOCK_PARENT(r_ccu, R_CCU_CLOCK_APB0),
		.gate      = BITMAP_INDEX(0x0028 >> 2, 6),
		.reset     = BITMAP_INDEX(0x00b0 >> 2, 6),
	},
	[R_CCU_CLOCK_R_TWD] = {
		.info.name = "r_twd",
		.parents   = CLOCK_PARENT(r_ccu, R_CCU_CLOCK_APB0),
		.gate      = BITMAP_INDEX(0x0028 >> 2, 7),
	},
	[R_CCU_CLOCK_R_CIR_MOD] = {
		.info.name = "r_cir_mod",
		.parents   = CLOCK_PARENTS(4) {
			{ .dev = &r_ccu.dev, .id = R_CCU_CLOCK_OSC32K },
			{ .dev = &r_ccu.dev, .id = R_CCU_CLOCK_OSC24M },
		},
		.gate = BITMAP_INDEX(0x0054 >> 2, 31),
		.reg  = 0x0054,
		.mux  = BITFIELD(24, 2),
		.m    = BITFIELD(0, 4),
		.p    = BITFIELD(16, 2),
	},
};

const struct sunxi_ccu r_ccu = {
	.dev = {
		.name  = "r_ccu",
		.drv   = &sunxi_ccu_driver.drv,
		.state = DEVICE_STATE_INIT,
	},
	.clocks = r_ccu_clocks,
	.regs   = DEV_R_PRCM,
};
