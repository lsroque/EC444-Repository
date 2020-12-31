/* Author: Lesbeth Roque
Date: 09-19-2020
Quest 1, Skill 06
Team 15 */

/*Toggle the onboard LED based on key input ‘t’
Echo input (2 or more characters) from the keyboard to the console
Echo decimal number input as a hexadecimal
Switch between the three modes based on key input ‘s’ */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "sdkconfig.h"
#include "esp_vfs_dev.h"

#define BLINK_GPIO 13

void app_main(void) {

  /* Install UART driver for interrupt-driven reads and writes */
  ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0) );

  /* Tell VFS to use UART driver */
  esp_vfs_dev_uart_use_driver(UART_NUM_0); // read user input

  gpio_pad_select_gpio(BLINK_GPIO);

  /* Set the GPIO as a push/pull output */
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT); //set up LEDs on the board

  char str[20];
  int num;
  int s = 1;
  bool tog = 0;

  printf("toggle mode\n");
  while(1) {
    switch(s) {
      case 1: //Toggle Mode
        printf("Read: ");
        scanf("%s", str);
        fflush(stdin);
        printf("%s\n", str);

        //if str is t, toggle LED on ESP
        if (str[0] == 't') {
          gpio_set_level(BLINK_GPIO, !tog);
          tog = !tog; //set up for next time a t is pressed
        }
        //is str is s, move onto next case
        else if (str[0] == 's') {
          printf("echo mode\n");
          s++;
        }
        break;

      case 2:
        fgets(str, 20, stdin);
        //source: https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/
        fflush(stdin);

        if (strlen(str) >= 2) {
          printf("echo: %s", str);
        }

        //if (str[0] == 's' && strlen(str) == 1){
        if (str[0] == 's') {
          printf("echo dec to hex mode\n");
          s++;
        }
        break;

      case 3:
        printf("Enter an integer: ");
        scanf("%s", str);
        fflush(stdin);

        if (str[0] == 's') {
          s = 1;
          printf("\ntoggle mode        \n");
        }
        else {
          num = atoi(str);
          printf("%d", num);
          printf("\nHex: %X\n", num);
        }
        //source: https://www.geeksforgeeks.org/converting-strings-numbers-cc/

        break;

    }
  }
}
