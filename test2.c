#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xil_types.h"
#include "sleep.h"

#define GPIO_DEVICE_ID_TIME XPAR_AXI_GPIO_0_DEVICE_ID         // ID for GPIO setting time
#define GPIO_DEVICE_ID_LED XPAR_AXI_GPIO_1_DEVICE_ID          // ID for LEDs
#define TIME_OUTPUT_CHANNEL 1                                 // Channel for time
#define LED_OUTPUT_CHANNEL 1                                  // Channel for LEDs

XGpio GpioTIME;
XGpio GpioLED;

int main() {
    init_platform();

    int Status;
    u32 time_value = 0;

    // Initialize GPIO_TIME
    Status = XGpio_Initialize(&GpioTIME, GPIO_DEVICE_ID_TIME);
    if (Status != XST_SUCCESS) {
        xil_printf("GPIO_TIME initialization failed\n");
        return XST_FAILURE;
    }

    // Set direction: output on channel 1 (for controlling time)
    XGpio_SetDataDirection(&GpioTIME, TIME_OUTPUT_CHANNEL, 0x0);

    // Initialize GPIO_LED
    Status = XGpio_Initialize(&GpioLED, GPIO_DEVICE_ID_LED);
    if (Status != XST_SUCCESS) {
        xil_printf("GPIO_LED initialization failed\n");
        return XST_FAILURE;
    }

    // Set direction: output on channel 1 (for controlling LEDs)
    XGpio_SetDataDirection(&GpioLED, LED_OUTPUT_CHANNEL, 0x0);

    while (1) {
        char inputBufferGlobal[12];
        xil_printf("\n\rEnter 1 for LED control or 2 for time setting: ");

        int i = 0;
        char c;
        while ((c = getchar()) != '\n' && c != '\r' && i < 11) {
            inputBufferGlobal[i++] = c;
            xil_printf("%c", c);
        }
        inputBufferGlobal[i] = '\0';

        u32 inputGlobal = (u32)strtoul(inputBufferGlobal, NULL, 10);
        xil_printf("\n\r");

        switch (inputGlobal) {
            case 1: { // LED control
                char inputBuffer[12];
                xil_printf("Enter LED number (1-4): ");

                int j = 0;
                char d;
                while ((d = getchar()) != '\n' && d != '\r' && j < 11) {
                    inputBuffer[j++] = d;
                    xil_printf("%c", d);
                }
                inputBuffer[j] = '\0';

                u32 ledInput = (u32)strtoul(inputBuffer, NULL, 10);
                xil_printf("\n\r");

                // Map LED numbers to GPIO outputs
                u32 gpioValue = 0;
                switch (ledInput) {
                    case 1: gpioValue = 0x01; break;
                    case 2: gpioValue = 0x02; break;
                    case 3: gpioValue = 0x04; break;
                    case 4: gpioValue = 0x08; break;
                    default:
                        xil_printf("Invalid LED number\n\r");
                        continue;
                }

                xil_printf("Turning on LED %u\n\r", ledInput);
                XGpio_DiscreteWrite(&GpioLED, LED_OUTPUT_CHANNEL, gpioValue);
                break;
            }

            case 2: { // Time setting
                char inputBuffer[12];
                xil_printf("Enter time value: ");

                int j = 0;
                char d;
                while ((d = getchar()) != '\n' && d != '\r' && j < 11) {
                    inputBuffer[j++] = d;
                    xil_printf("%c", d);
                }
                inputBuffer[j] = '\0';

                u32 timeInput = (u32)strtoul(inputBuffer, NULL, 10);
                xil_printf("\n\r");

                time_value = timeInput;

                // Send the value to GPIO
                xil_printf("Sending value %u to the pulse_generator module\n\r", time_value);
                XGpio_DiscreteWrite(&GpioTIME, TIME_OUTPUT_CHANNEL, time_value);
                break;
            }

            default:
                xil_printf("Invalid option selected\n\r");
                break;
        }
    }

    cleanup_platform();
    return 0;
}
