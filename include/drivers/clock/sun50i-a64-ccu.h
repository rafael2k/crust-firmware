/*
 * Copyright © 2017-2021 The Crust Firmware Authors.
 * SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0-only
 */

#ifndef DRIVERS_CLOCK_SUN50I_A64_CCU_H
#define DRIVERS_CLOCK_SUN50I_A64_CCU_H

enum {
	CLK_PLL_CPUX,
	CLK_PLL_DDR0,
	CLK_PLL_PERIPH0,
#if CONFIG(SOC_A64)
	CLK_PLL_DDR1,
#endif
	CLK_APB2,
	CLK_BUS_DRAM,
	CLK_BUS_MSGBOX,
	CLK_BUS_PIO,
#if CONFIG(SERIAL_DEV_UART0)
	CLK_BUS_UART0,
#elif CONFIG(SERIAL_DEV_UART1)
	CLK_BUS_UART1,
#elif CONFIG(SERIAL_DEV_UART2)
	CLK_BUS_UART2,
#elif CONFIG(SERIAL_DEV_UART3)
	CLK_BUS_UART3,
#elif CONFIG(SERIAL_DEV_UART4) /* depends on SOC_A64 */
	CLK_BUS_UART4,
#endif
	CLK_DRAM,
	CLK_MBUS,
	SUN50I_A64_CCU_CLOCKS
};

#endif /* DRIVERS_CLOCK_SUN50I_A64_CCU_H */
