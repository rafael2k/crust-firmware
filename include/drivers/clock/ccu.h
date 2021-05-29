/*
 * Copyright © 2017-2021 The Crust Firmware Authors.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 */

#ifndef DRIVERS_CLOCK_CCU_H
#define DRIVERS_CLOCK_CCU_H

#include <clock.h>
#include <device.h>
#if CONFIG(PLATFORM_A64)
#include <clock/sun50i-a64-ccu.h>
#include <clock/sun8i-r-ccu.h>
#elif CONFIG(PLATFORM_A83T)
#include <clock/sun8i-a83t-ccu.h>
#include <clock/sun8i-r-ccu.h>
#elif CONFIG(PLATFORM_H3)
#include <clock/sun8i-h3-ccu.h>
#include <clock/sun8i-r-ccu.h>
#elif CONFIG(PLATFORM_H6)
#include <clock/sun50i-h6-ccu.h>
#include <clock/sun50i-h6-r-ccu.h>
#endif

struct ccu {
	struct device           dev;
	const struct ccu_clock *clocks;
	uintptr_t               regs;
};

extern const struct ccu ccu;
extern const struct ccu r_ccu;

void ccu_suspend(void);
void ccu_suspend_cluster(uint32_t cluster);
void ccu_resume(void);
void ccu_resume_cluster(uint32_t cluster);
void ccu_init(void);

void r_ccu_suspend(uint8_t depth);
void r_ccu_resume(void);
void r_ccu_init(void);

#endif /* DRIVERS_CLOCK_CCU_H */
