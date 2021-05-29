/*
 * Copyright © 2017-2021 The Crust Firmware Authors.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 */

#ifndef WATCHDOG_PRIVATE_H
#define WATCHDOG_PRIVATE_H

#include <device.h>
#include <stdint.h>

struct watchdog_driver_ops {
	void (*restart)(const struct device *dev);
	void (*set_timeout)(const struct device *dev, uint32_t timeout);
};

struct watchdog_driver {
	struct driver              drv;
	struct watchdog_driver_ops ops;
};

#endif /* WATCHDOG_PRIVATE_H */
