/*
 * Copyright © 2017-2021 The Crust Firmware Authors.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 */

#include <error.h>
#include <simple_device.h>

int
simple_device_probe(const struct device *dev)
{
	const struct simple_device *self = to_simple_device(dev);
	int err;

	if (self->pins) {
		if ((err = gpio_get(&self->pins[0])))
			return err;
		if ((err = gpio_get(&self->pins[1])))
			goto err_put_gpio0;
	}

	clock_get(&self->clock);

	return SUCCESS;

err_put_gpio0:
	gpio_put(&self->pins[0]);

	return err;
}

void
simple_device_release(const struct device *dev)
{
	const struct simple_device *self = to_simple_device(dev);

	clock_put(&self->clock);
	if (self->pins) {
		gpio_put(&self->pins[1]);
		gpio_put(&self->pins[0]);
	}
}

void
simple_device_sync(const struct simple_device *sdev)
{
	uint8_t refcount = sdev->dev.state->refcount;

	if (clock_get_state(&sdev->clock) == CLOCK_STATE_ENABLED) {
		if (refcount == 0)
			device_get(&sdev->dev);
	} else {
		if (refcount == 1)
			device_put(&sdev->dev);
	}
}
