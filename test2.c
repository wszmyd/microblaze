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
        char inputBuffer[12];
        xil_printf("Enter LED number: ");

        int i = 0;
        char c;
        while ((c = getchar()) != '\n' && c != '\r' && i < 11)
        {
            inputBuffer[i++] = c;
            xil_printf("%c", c);
        }
        inputBuffer[i] = '\0';

        u32 input = (u32)strtoul(inputBuffer, NULL, 10);
        xil_printf("\n\r");

        if (input == 3)
        {
            input = 4;
        }
        else if (input == 4)
        {
            input = 8;
        }

        switch (input)
        {
            case 0x01:
                xil_printf("LED 1 turned on\n\r");
                XGpio_DiscreteWrite(&Gpio, 1, input);
                break;
            case 0x02:
                xil_printf("LED 2 turned on\n\r");
                XGpio_DiscreteWrite(&Gpio, 1, input);
                break;
            case 0x04:
                xil_printf("LED 3 turned on\n\r");
                XGpio_DiscreteWrite(&Gpio, 1, input);
                break;
            case 0x08:
                xil_printf("LED 4 turned on\n\r");
                XGpio_DiscreteWrite(&Gpio, 1, input);
                break;
            default:
                xil_printf("Invalid LED number entered\n\r");
                break;
        }
    }

    cleanup_platform();
    return 0;
}
