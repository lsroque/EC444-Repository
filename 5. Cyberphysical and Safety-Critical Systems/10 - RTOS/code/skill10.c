/* Author: Lesbeth Roque
Date: 09-22-2020
Quest 1, Skill 10
Team 15 */

/* Design these three tasks (each task should be a separate FreeRTOS task)
Task A: Count up in binary every 1 second (RGB LEDs with 330 Ohm resistors please)
Task B: A button press to toggle from counting up to counting down or vice-versa
Task C: Read the current direction value and display to alphanumeric “up” or “down”
Identify how to signal between tasks (global variables)
Report as usual */


/*
  Adapted I2C example code to work with the Adafruit 14-segment Alphanumeric Display. Key notes: MSB!!

  Emily Lam, Sept 2018, Updated Aug 2019
*/

#include <stdio.h>
#include <string.h>
#include "driver/i2c.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_vfs_dev.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//define LED configurations
#define LED1 26 // Pin A0 - 26, Yellow LED
#define LED2 25 //Pin A1 - 25, Green LED
#define LED3 5 // Pin SCK - 5, Blue LED
#define LED4 13 // Pin 13 - 13, Green LED
#define BUTTON1 34 //Pin A4 - 34, Button


//Define global variables
int decNum;
unsigned int binNum;
unsigned int binArray[4] = {0,0,0,0};
int dir = 0; //default direction is down. 1 will be used for up.

//I2C Display ASCII characters, this is a library i got from adafruit github repo

static const uint16_t alphafonttable[] = {

    0b0000000000000001, 0b0000000000000010, 0b0000000000000100,
    0b0000000000001000, 0b0000000000010000, 0b0000000000100000,
    0b0000000001000000, 0b0000000010000000, 0b0000000100000000,
    0b0000001000000000, 0b0000010000000000, 0b0000100000000000,
    0b0001000000000000, 0b0010000000000000, 0b0100000000000000,
    0b1000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0001001011001001, 0b0001010111000000, 0b0001001011111001,
    0b0000000011100011, 0b0000010100110000, 0b0001001011001000,
    0b0011101000000000, 0b0001011100000000,
    0b0000000000000000, //
    0b0000000000000110, // !
    0b0000001000100000, // "
    0b0001001011001110, // #
    0b0001001011101101, // $
    0b0000110000100100, // %
    0b0010001101011101, // &
    0b0000010000000000, // '
    0b0010010000000000, // (
    0b0000100100000000, // )
    0b0011111111000000, // *
    0b0001001011000000, // +
    0b0000100000000000, // ,
    0b0000000011000000, // -
    0b0000000000000000, // .
    0b0000110000000000, // /
    0b0000110000111111, // 0
    0b0000000000000110, // 1
    0b0000000011011011, // 2
    0b0000000010001111, // 3
    0b0000000011100110, // 4
    0b0010000001101001, // 5
    0b0000000011111101, // 6
    0b0000000000000111, // 7
    0b0000000011111111, // 8
    0b0000000011101111, // 9
    0b0001001000000000, // :
    0b0000101000000000, // ;
    0b0010010000000000, // <
    0b0000000011001000, // =
    0b0000100100000000, // >
    0b0001000010000011, // ?
    0b0000001010111011, // @
    0b0000000011110111, // A
    0b0001001010001111, // B
    0b0000000000111001, // C
    0b0001001000001111, // D
    0b0000000011111001, // E
    0b0000000001110001, // F
    0b0000000010111101, // G
    0b0000000011110110, // H
    0b0001001000000000, // I
    0b0000000000011110, // J
    0b0010010001110000, // K
    0b0000000000111000, // L
    0b0000010100110110, // M
    0b0010000100110110, // N
    0b0000000000111111, // O
    0b0000000011110011, // P
    0b0010000000111111, // Q
    0b0010000011110011, // R
    0b0000000011101101, // S
    0b0001001000000001, // T
    0b0000000000111110, // U
    0b0000110000110000, // V
    0b0010100000110110, // W
    0b0010110100000000, // X
    0b0001010100000000, // Y
    0b0000110000001001, // Z
    0b0000000000111001, // [
    0b0010000100000000, //
    0b0000000000001111, // ]
    0b0000110000000011, // ^
    0b0000000000001000, // _
    0b0000000100000000, // `
    0b0001000001011000, // a
    0b0010000001111000, // b
    0b0000000011011000, // c
    0b0000100010001110, // d
    0b0000100001011000, // e
    0b0000000001110001, // f
    0b0000010010001110, // g
    0b0001000001110000, // h
    0b0001000000000000, // i
    0b0000000000001110, // j
    0b0011011000000000, // k
    0b0000000000110000, // l
    0b0001000011010100, // m
    0b0001000001010000, // n
    0b0000000011011100, // o
    0b0000000101110000, // p
    0b0000010010000110, // q
    0b0000000001010000, // r
    0b0010000010001000, // s
    0b0000000001111000, // t
    0b0000000000011100, // u
    0b0010000000000100, // v
    0b0010100000010100, // w
    0b0010100011000000, // x
    0b0010000000001100, // y
    0b0000100001001000, // z
    0b0000100101001001, // {
    0b0001001000000000, // |
    0b0010010010001001, // }
    0b0000010100100000, // ~
    0b0011111111111111,

};

// 14-Segment Display
#define SLAVE_ADDR                         0x70 // alphanumeric address
#define OSC                                0x21 // oscillator cmd
#define HT16K33_BLINK_DISPLAYON            0x01 // Display on cmd
#define HT16K33_BLINK_OFF                  0    // Blink off cmd
#define HT16K33_BLINK_CMD                  0x80 // Blink cmd
#define HT16K33_CMD_BRIGHTNESS             0xE0 // Brightness cmd

// Master I2C
#define I2C_EXAMPLE_MASTER_SCL_IO          22   // gpio number for i2c clk
#define I2C_EXAMPLE_MASTER_SDA_IO          23   // gpio number for i2c data
#define I2C_EXAMPLE_MASTER_NUM             I2C_NUM_0  // i2c port
#define I2C_EXAMPLE_MASTER_TX_BUF_DISABLE  0    // i2c master no buffer needed
#define I2C_EXAMPLE_MASTER_RX_BUF_DISABLE  0    // i2c master no buffer needed
#define I2C_EXAMPLE_MASTER_FREQ_HZ         100000     // i2c master clock freq
#define WRITE_BIT                          I2C_MASTER_WRITE // i2c master write
#define READ_BIT                           I2C_MASTER_READ  // i2c master read
#define ACK_CHECK_EN                       true // i2c master will check ack
#define ACK_CHECK_DIS                      false// i2c master will not check ack
#define ACK_VAL                            0x00 // i2c ack value
#define NACK_VAL                           0xFF // i2c nack value


// Function to initiate i2c -- note the MSB declaration!
static void i2c_example_master_init(){
    // Debug
    printf("\n>> i2c Config\n");
    int err;

    // Port configuration
    int i2c_master_port = I2C_EXAMPLE_MASTER_NUM;

    /// Define I2C configurations
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;                              // Master mode
    conf.sda_io_num = I2C_EXAMPLE_MASTER_SDA_IO;              // Default SDA pin
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;                  // Internal pullup
    conf.scl_io_num = I2C_EXAMPLE_MASTER_SCL_IO;              // Default SCL pin
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;                  // Internal pullup
    conf.master.clk_speed = I2C_EXAMPLE_MASTER_FREQ_HZ;       // CLK frequency
    err = i2c_param_config(i2c_master_port, &conf);           // Configure
    if (err == ESP_OK) {printf("- parameters: ok\n");}

    // Install I2C driver
    err = i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_EXAMPLE_MASTER_RX_BUF_DISABLE,
                       I2C_EXAMPLE_MASTER_TX_BUF_DISABLE, 0);
    // i2c_set_data_mode(i2c_master_port,I2C_DATA_MODE_LSB_FIRST,I2C_DATA_MODE_LSB_FIRST);
    if (err == ESP_OK) {printf("- initialized: yes\n\n");}

    // Dat in MSB mode
    i2c_set_data_mode(i2c_master_port, I2C_DATA_MODE_MSB_FIRST, I2C_DATA_MODE_MSB_FIRST);
}

// Utility  Functions //////////////////////////////////////////////////////////

// Utility function to test for I2C device address -- not used in deploy
int testConnection(uint8_t devAddr, int32_t timeout) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    int err = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return err;
}

// Utility function to scan for i2c device
static void i2c_scanner() {
    int32_t scanTimeout = 1000;
    printf("\n>> I2C scanning ..."  "\n");
    uint8_t count = 0;
    for (uint8_t i = 1; i < 127; i++) {
        // printf("0x%X%s",i,"\n");
        if (testConnection(i, scanTimeout) == ESP_OK) {
            printf( "- Device found at address: 0x%X%s", i, "\n");
            count++;
        }
    }
    if (count == 0)
        printf("- No I2C devices found!" "\n");
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////

// Alphanumeric Functions //////////////////////////////////////////////////////

// Turn on oscillator for alpha display
int alpha_oscillator() {
  int ret;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, OSC, ACK_CHECK_EN);
  i2c_master_stop(cmd);
  ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  vTaskDelay(200 / portTICK_RATE_MS);
  return ret;
}

// Set blink rate to off
int no_blink() {
  int ret;
  i2c_cmd_handle_t cmd2 = i2c_cmd_link_create();
  i2c_master_start(cmd2);
  i2c_master_write_byte(cmd2, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd2, HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (HT16K33_BLINK_OFF << 1), ACK_CHECK_EN);
  i2c_master_stop(cmd2);
  ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd2, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd2);
  vTaskDelay(200 / portTICK_RATE_MS);
  return ret;
}

// Set Brightness
int set_brightness_max(uint8_t val) {
  int ret;
  i2c_cmd_handle_t cmd3 = i2c_cmd_link_create();
  i2c_master_start(cmd3);
  i2c_master_write_byte(cmd3, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
  i2c_master_write_byte(cmd3, HT16K33_CMD_BRIGHTNESS | val, ACK_CHECK_EN);
  i2c_master_stop(cmd3);
  ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd3, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd3);
  vTaskDelay(200 / portTICK_RATE_MS);
  return ret;
}

////////////////////////////////////////////////////////////////////////////////

// Task A: Function to convert decimal numbers into binary numbers
unsigned int dec_to_bin(int decimalNumber) {
    unsigned int binaryNumber = 0;
    int remainder, i = 1;

   while (decimalNumber != 0) {
     remainder = decimalNumber % 2;
     decimalNumber /= 2;
     binaryNumber += remainder * i;
     i *= 10;
   }
   return binaryNumber;
}

// Task B: Count up and Down
// Code taken from skill06.c, modified to change directions
static void task_wrapBinary(){
  if (dir == 1) {
    decNum = 0;
  }
  else if (dir == 0) {
    decNum = 15;
  }
  while(1) {
      binNum = dec_to_bin(decNum);

      /* extract each binary digit and place it into an array */
      for (int i = 0; i < 5; i++) {
          binArray[i] = binNum % 10;
          binNum /= 10;
      }

      printf("%d\n",decNum);
      gpio_set_level(LED1, binArray[3]);
      gpio_set_level(LED2,binArray[2]);
      gpio_set_level(LED3,binArray[1]);
      gpio_set_level(LED4,binArray[0]);

      if (dir == 1) {
        decNum++;
        if (decNum == 16) {
          decNum = 0;
        }
      }
      else if (dir == 0) {
        decNum--;
        if (decNum == -1){
          decNum = 15;
        }
      }
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}


///////////////////////////////////////////////////////////////////
// Task B Continued: Button to change directions
static void task_pushbutton(){
  while(1){
    /*the gpio_get_level function measures when the button is pushed, and
    the if statements are to toggle direction*/
    if(gpio_get_level(BUTTON1) && (dir == 0)) {
      dir = 1;
      //printf("direction is up\n");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    else if (gpio_get_level(BUTTON1) && (dir == 1)) {
      dir = 0;
      //printf("direction is down\n");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
}

/////////////////////////////////////////////////////////////////////
// Task C: Display Up/Down
static void test_alpha_display() {
    // Debug
    int ret;
    printf(">> Test Alphanumeric Display: \n");

    // Set up routines
    // Turn on alpha oscillator
    ret = alpha_oscillator();
    if(ret == ESP_OK) {printf("- oscillator: ok \n");}
    // Set display blink off
    ret = no_blink();
    if(ret == ESP_OK) {printf("- blink: off \n");}
    ret = set_brightness_max(0xF);
    if(ret == ESP_OK) {printf("- brightness: max \n");}

    char str[5]; //store user input

    uint16_t displaybuffer[128];

    // Continually writes the same command
    while (1) {
      if(ret == ESP_OK) { //if button is pushed, the check if statement
        if(dir == 1){
          strcpy(str,"UP  ");
          //vTaskDelay(1000 / portTICK_PERIOD_MS);

        }else if(dir == 0){
          strcpy(str,"DOWN");

        }
        for(int i = 0;i < 5;i++){
          displaybuffer[i] = alphafonttable[(uint16_t)str[i]]; //finds each letter in table according to str, and sets to displaybuffer, then displays
        }
      }
      vTaskDelay(100 / portTICK_PERIOD_MS);
      // Send commands characters to display over I2C
      i2c_cmd_handle_t cmd4 = i2c_cmd_link_create();
      i2c_master_start(cmd4);
      i2c_master_write_byte(cmd4, ( SLAVE_ADDR << 1 ) | WRITE_BIT, ACK_CHECK_EN);
      i2c_master_write_byte(cmd4, (uint8_t)0x00, ACK_CHECK_EN);
      for (uint8_t i=0; i<8; i++) {
        i2c_master_write_byte(cmd4, displaybuffer[i] & 0xFF, ACK_CHECK_EN);
        i2c_master_write_byte(cmd4, displaybuffer[i] >> 8, ACK_CHECK_EN);
      }
      i2c_master_stop(cmd4);
      ret = i2c_master_cmd_begin(I2C_EXAMPLE_MASTER_NUM, cmd4, 1000 / portTICK_RATE_MS);
      i2c_cmd_link_delete(cmd4);

    }


}


void init(){ //this function is just for initializations
  /* Install UART driver for interrupt-driven reads and writes */
  i2c_example_master_init();
  i2c_scanner();
  ESP_ERROR_CHECK( uart_driver_install(UART_NUM_0,
   256, 0, 0, NULL, 0) ); //this is from skill 6, so I can accept user input

 /* Tell VFS to use UART driver */
  esp_vfs_dev_uart_use_driver(UART_NUM_0);

  gpio_reset_pin(BUTTON1);

  //Configure the LEDs
  gpio_pad_select_gpio(LED1);
  gpio_set_direction(LED1, GPIO_MODE_OUTPUT);

  gpio_pad_select_gpio(LED2);
  gpio_set_direction(LED2, GPIO_MODE_OUTPUT);

  gpio_pad_select_gpio(LED3);
  gpio_set_direction(LED3, GPIO_MODE_OUTPUT);

  gpio_pad_select_gpio(LED4);
  gpio_set_direction(LED4, GPIO_MODE_OUTPUT);
  //
  gpio_pad_select_gpio(BUTTON1);
  gpio_set_direction(BUTTON1,GPIO_MODE_INPUT);
}

void app_main() { //Function initialized
  init();
  xTaskCreate(task_pushbutton,"task_pushbutton",1024*2,NULL,configMAX_PRIORITIES,NULL);
  //vTaskDelay(100 / portTICK_PERIOD_MS);
  xTaskCreate(task_wrapBinary,"task_wrapBinary",1024*2,NULL, configMAX_PRIORITIES-1, NULL);
  //vTaskDelay(100 / portTICK_PERIOD_MS);
  xTaskCreate(test_alpha_display,"test_alpha_display", 4096, NULL, configMAX_PRIORITIES-2, NULL);
}
