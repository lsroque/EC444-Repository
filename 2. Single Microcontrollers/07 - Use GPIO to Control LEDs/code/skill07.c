/* Author: Lesbeth Roque
Date: 09-19-2020
Quest 1, Skill 7
Team 15 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* Drive a blink-type program to count up, and wrap, in binary on the set of 4 LEDs */

#define LED1 26 // Pin A0 - 26, Yellow LED
#define LED2 25 //Pin A1 - 25, Green LED
#define LED3 5 // Pin SCK - 5, Blue LED
#define LED4 13 // Pin 13 - 13, Green LED

unsigned int decimalToBinary(int decimalNumber) {
    unsigned int binaryNumber = 0;
    int remainder, i = 1;

   while (decimalNumber != 0) {
     remainder = decimalNumber % 2;
     decimalNumber /= 2;
     binaryNumber += remainder * i;
     i *= 10;
     //printf("binaryNumber: %u\n ", binaryNumber);
   }

   return binaryNumber;
} // source: https://beginnersbook.com/2017/09/c-program-to-convert-decimal-number-to-binary-number/


void app_main(void) {
  int decNum;
  unsigned int binNum;
  unsigned int binArray[4] = {0, 0, 0, 0};

    /* Set the GPIO as a push/pull output */
    gpio_pad_select_gpio(LED1);
    gpio_pad_select_gpio(LED2);
    gpio_pad_select_gpio(LED3);
    gpio_pad_select_gpio(LED4);

    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED4, GPIO_MODE_OUTPUT);

    printf("Testing LEDs...\n");

    while(1) {
      /* LED turns off if output LOW (0), LED turns on if output is HIGH (1)*/
      decNum = 0;
      while(decNum < 16){
        binNum = decimalToBinary(decNum);
        unsigned int binNum2 = binNum;

          /* extract each binary digit and place it into an array */
          for (int i = 0; i < 5; i++) {
            binArray[i] = binNum % 10;
            binNum /= 10;
          }

          printf("-------------\n");

          printf("Decimal Num: %d\n",decNum);
          printf("Binary Num: %u\n",binNum2);

          printf("YELLOW LED1: %u\n", binArray[3] );
          printf("GREEN LED2: %u\n", binArray[2] );
          printf("BLUE LED3: %u\n", binArray[1] );
          printf("GREEN LED4: %u\n", binArray[0] );

          gpio_set_level(LED1, binArray[3]);
          gpio_set_level(LED2, binArray[2]);
          gpio_set_level(LED3, binArray[1]);
          gpio_set_level(LED4, binArray[0]);
          vTaskDelay(1000 / portTICK_PERIOD_MS);
          decNum++;

        }
      }
    }
