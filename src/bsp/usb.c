#include "stm32f103xb.h"

/* ================= LED ================= */

static void LED_On(void)
{
    GPIOA->BSRR = (1 << 0);
}

static void LED_Off(void)
{
    GPIOA->BRR = (1 << 0);
}

/* ================= USB INIT ================= */

static void USB_GPIO_Init(void)
{
    // PA12 push-pull (USB D+ pull-up)
    GPIOA->CRH &= ~(0xF << 16);
    GPIOA->CRH |= (0x3 << 16);

    GPIOA->BSRR = GPIO_BSRR_BS12;
}

/* ================= INIT ================= */

void USB_Init(void)
{
    USB_GPIO_Init();

    // Reset USB peripheral
    USB->CNTR = USB_CNTR_FRES;
    USB->CNTR = 0;

    // Clear all interrupt flags properly
    USB->ISTR = 0;

    // Enable RESET interrupt
    USB->CNTR = USB_CNTR_RESETM;

    // Enable pull-up (simulate USB connect)
    GPIOA->BSRR = GPIO_BSRR_BS12;
}
/* ================= ISR ================= */

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    GPIOA->ODR ^= (1 << 0);

    USB->ISTR = 0;
}