/*
 * Copyright © 2017-2021 The Crust Firmware Authors.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 */

#include <debug.h>
#include <device.h>
#include <error.h>
#include <stddef.h>

bool
device_active(const struct device *dev)
{
	return dev && dev->state->refcount;
}

int
device_get(const struct device *dev)
{
	int err;

	if (!dev)
		return ENODEV;

	if (!dev->state->refcount) {
		if ((err = dev->drv->probe(dev))) {
			warn("%s: Probe failed: %d", dev->name, err);
			return err;
		}
		debug("%s: Probed", dev->name);
	}

	/* Increment the refcount only after successful initialization. */
	++dev->state->refcount;

	return SUCCESS;
}

const struct device *
device_get_or_null(const struct device *dev)
{
	return device_get(dev) == SUCCESS ? dev : NULL;
}

void
device_put(const struct device *dev)
{
	if (!dev || --dev->state->refcount)
		return;

	debug("%s: Releasing", dev->name);
	dev->drv->release(dev);
}

int
dummy_probe(const struct device *dev UNUSED)
{
	return SUCCESS;
}

void
dummy_release(const struct device *dev UNUSED)
{
}
