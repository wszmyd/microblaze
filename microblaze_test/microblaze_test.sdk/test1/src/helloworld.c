#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "xparameters.h"
#include "xgpio.h"
#include "xil_types.h"
#include "sleep.h"


int main()
{
    init_platform();

    XGpio Gpio;
    XGpio_Initialize(&Gpio, XPAR_AXI_GPIO_0_DEVICE_ID);
    while (1)
    {
    	u32 buttonsState = XGpio_DiscreteRead(&Gpio, 2);

    	switch (buttonsState)
    	{
	    case 0x01:
                xil_printf("Button 1 pressed\n\r");
                XGpio_DiscreteWrite(&Gpio, 1, buttonsState);
                break;
            case 0x02:
                xil_printf("Button 2 pressed\n\r");
                XGpio_DiscreteWrite(&Gpio, 1, buttonsState);
                break;
            case 0x04:
                xil_printf("Button 3 pressed\n\r");
                XGpio_DiscreteWrite(&Gpio, 1, buttonsState);
                break;
            case 0x08:
                xil_printf("Button 4 pressed\n\r");
                XGpio_DiscreteWrite(&Gpio, 1, buttonsState);
                break;
    	}
    	usleep(250000);
    }
    cleanup_platform();
    return 0;
}
