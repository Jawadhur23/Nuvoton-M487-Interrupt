/**************************
 * @file     main.c
 * @version  V1.00
 * @brief    A project template for M031 MCU.
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ***************************/

#include <stdio.h>
#include "NuMicro.h"

#define PB_MODE      (*(volatile uint32_t *)(0x40004000 + 0x040))       /* PBMODE reg address */
#define SYS_GPB_MFPL (*(volatile uint32_t *)(0x40000000 + 0x38))       /* SYS_GPB_MFPL reg address */
#define UART_FUNCSEL (*(volatile uint32_t *)(0x40070000 + 0x30))       /* UARTFUNCSEL reg address */
#define UART_LINE    (*(volatile uint32_t *)(0x40070000 + 0x0C))       /* UARTLINE reg address */
#define UART_BAUD    (*(volatile uint32_t *)(0x40070000 + 0x24))       /* UARTBAUD reg address */
#define CLK_CLKSEL1  (*(volatile uint32_t *)(0x40000200 + 0x14))       /* CLKSEL1 reg address */
#define CLK_APBCLK0  (*(volatile uint32_t *)(0x40000200 + 0x08))       /* APBCLK0 reg address */
#define SYS_GPB_MFPH (*(volatile uint32_t *)(0x40000000 + 0x3C))       /* reg address */
#define UART_DAT     (*(volatile uint32_t *)(0x40070000 + 0x00))
#define UART_INTEN   (*(volatile uint32_t *)(0x40070000 + 0x04))
#define UART_INTSTS  (*(volatile uint32_t *)(0x40070000 + 0x1C))
#define UART_FIFO    (*(volatile uint32_t *)(0x40070000 + 0x08))
#define NVIC_ISER1   (*(volatile uint32_t *)(0xE000E100 + 0x04))

void SYS_Init()
{
    CLK_CLKSEL1 = (CLK_CLKSEL1 & (~(0x7 << 24))) | (0x3 << 24);
    CLK_APBCLK0 = (CLK_APBCLK0 & (~(1 << 16))) | (1 << 16);
    PB_MODE = (PB_MODE & ~(0x03 << 14));
    SYS_GPB_MFPL = (SYS_GPB_MFPL & (~(1 << 28))) | (0x1 << 28);
    SYS_GPB_MFPH = (SYS_GPB_MFPH & (~(0x6 << 16) | ~(0x6 << 20))) | ((0x6 << 16) | (0x6 << 20));

}

void UART_Init()
{
    UART_FUNCSEL = (UART_FUNCSEL & (~(0x7 << 0)));
    UART_LINE = (UART_LINE & (~(0x3 << 0))) | (0x3 << 0);
    UART_BAUD = (UART_BAUD & (~(0x3 << 28)));
    UART_BAUD = (UART_BAUD & (~(255 << 0))) | (76 << 0);
    UART_INTEN = (UART_INTEN & (~(0x1 << 0))) | (0x1 << 0);
    UART_FIFO = (UART_FIFO & (~(0x15 << 4))) | (0x1 << 4);// SINCE 1'S COMPLEMENT SHOULD BE DONE BY 1111 IS CHANGES TO 0000
    NVIC_ISER1 = (NVIC_ISER1 & (~(0x1<<4))) | (0x1<<4);
}

void UART0_IRQHandler()
{
	printf("Data has Been Wrote and Read");
    if (UART0->INTSTS & UART_INTSTS_RDAIF_Msk)
    {
        char c = UART0->DAT;

        // Process the received character 'c' here
        printf("%c\n", c);
    }
}

int main()
{
    SYS_Init();
    UART_Init();


    while (1) {
        // Your code here

    }

    return 0;
}
