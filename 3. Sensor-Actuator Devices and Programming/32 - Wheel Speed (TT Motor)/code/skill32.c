/* Author: Lesbeth Roque
Cluster 5, Skill 33: Wheel Speed
11/29/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_adc_cal.h"
#include "freertos/queue.h"
#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#define LEDC_HS_TIMER          LEDC_TIMER_0
#define LEDC_HS_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO       (13)     // GPIO 13 for LED
#define LEDC_HS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_TEST_CH_NUM       (1)
#define LEDC_TEST_DUTY         (4000)
#define LEDC_TEST_FADE_TIME    (3000)

ledc_timer_config_t ledc_timer = {
    .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
    .freq_hz = 5000,                      // frequency of PWM signal
    .speed_mode = LEDC_HS_MODE,           // timer mode
    .timer_num = LEDC_HS_TIMER            // timer index
};

ledc_channel_config_t ledc_channel = {

        .channel    = LEDC_HS_CH0_CHANNEL,
        .duty       = 0,
        .gpio_num   = LEDC_HS_CH0_GPIO,
        .speed_mode = LEDC_HS_MODE,
        .timer_sel  = LEDC_HS_TIMER

};

// TT Motor Stuff
#define GPIO_PWM0A_OUT 26   // Set GPIO A0 as PWM0A
#define GPIO_PWM0B_OUT 14   // Set GPIO 14 as PWM0B
#define GPIO_MOTOR1_0  18   // GPIO 18/MOSI
#define GPIO_MOTOR1_1  25   // GPIO 25/A1
#define GPIO_MOTOR2_0  32   // GPIO 32
#define GPIO_MOTOR2_1  12   // GPIO 12


// Encoder Stuff
#define DEFAULT_VREF    1023        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64          //Multisampling
static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC2_CHANNEL_6;   // GPIO #34 / A2 input for phototransistor
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_2;
#define HIGH  1
#define LOW   0

// Timer Stuff
#define TIMER_DIVIDER         16  //  Hardware timer clock divider
#define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds
#define TIMER_INTERVAL0_SEC   (3.4179) // sample test interval for the first timer
#define TIMER_INTERVAL1_SEC   (5.78)   // sample test interval for the second timer
#define TEST_WITHOUT_RELOAD   0        // testing will be done without auto reload
#define TEST_WITH_RELOAD      1        // testing will be done with auto reload

/////////////////////////////////////////////////////
static void mcpwm_example_gpio_initialize()
{
	//only using one of the MCPWM units
    printf("initializing mcpwm gpio...\n");
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, GPIO_PWM0B_OUT);
}

/**
 * @brief motor moves in forward direction, with duty cycle = duty %
 */
static void brushed_motor_forward(float duty_cycle)
{

    gpio_set_level(GPIO_MOTOR1_0, 1);
    gpio_set_level(GPIO_MOTOR1_1, 0);
    gpio_set_level(GPIO_MOTOR2_0, 0);
    gpio_set_level(GPIO_MOTOR2_1, 1);

   //mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
   //mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state

    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, duty_cycle);

}

/**
 * @brief motor moves in backward direction, with duty cycle = duty %
 */
static void brushed_motor_backward(float duty_cycle)
{

    gpio_set_level(GPIO_MOTOR1_0, 0);
    gpio_set_level(GPIO_MOTOR1_1, 1);
    gpio_set_level(GPIO_MOTOR2_0, 1);
    gpio_set_level(GPIO_MOTOR2_1, 0);

    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state

    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, duty_cycle);
}

/**
 * @brief motor stop
 */
static void brushed_motor_stop()
{
   // mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
   // mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state

	mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 0.0);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 0.0);

}

 static void brushed_motor_turn_left(float duty_cycle)
 {
  // mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
  // mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state

   mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 0.0);
   mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, duty_cycle);

   // gpio_set_level(GPIO_MOTOR2_0, 1);
   // gpio_set_level(GPIO_MOTOR2_1, 0);
   gpio_set_level(GPIO_MOTOR1_0, 1);
   gpio_set_level(GPIO_MOTOR1_1, 0);
 }


  static void brushed_motor_turn_right(float duty_cycle)
  {
   // mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state
   // mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //call this each time, if operator was previously in low/high state

    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty_cycle);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, 0.0);

    gpio_set_level(GPIO_MOTOR2_0, 1);
    gpio_set_level(GPIO_MOTOR2_1, 0);
  }
/**
 * @brief Configure MCPWM module for brushed dc motor
 */
static void mcpwm_example_brushed_motor_control(void *arg)
{
    //1. mcpwm gpio initialization
    mcpwm_example_gpio_initialize();

    gpio_pad_select_gpio(GPIO_MOTOR1_0);
    gpio_pad_select_gpio(GPIO_MOTOR1_1);
    gpio_pad_select_gpio(GPIO_MOTOR2_0);
    gpio_pad_select_gpio(GPIO_MOTOR2_1);

    gpio_set_direction(GPIO_MOTOR1_0, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_MOTOR1_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_MOTOR2_0, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_MOTOR2_1, GPIO_MODE_OUTPUT);

    gpio_set_level(GPIO_MOTOR1_0, 0);
    gpio_set_level(GPIO_MOTOR1_1, 1);
    gpio_set_level(GPIO_MOTOR2_0, 1);
    gpio_set_level(GPIO_MOTOR2_1, 0);

    //2. initial mcpwm configuration
    printf("Configuring Initial Parameters of mcpwm...\n");
    mcpwm_config_t pwm_config;

	//only need to initialize one unit
    pwm_config.frequency = 100;    //frequency = 500Hz,
    pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
   	pwm_config.cmpr_b = 0;	//duty cycle of PWMxB = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM with above settings

    while (1) {
		mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); //sets duty type of PWM0A
		mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0); //sets duty type of PWM0B

    // this works!
    brushed_motor_forward(90.0); //drive forward with duty cycle of 90
		vTaskDelay(1000/portTICK_RATE_MS);

    // brushed_motor_stop();
    // vTaskDelay(1000/portTICK_RATE_MS);
    //
    // // not working
    // brushed_motor_backward(90.0); //drive backward with duty cycle of 50%
		// vTaskDelay(1000/portTICK_RATE_MS);//delay 1 second
    //
    // brushed_motor_stop();
    // vTaskDelay(1000/portTICK_RATE_MS);
    //
    // // works!
    // brushed_motor_turn_right(90.0);
    // vTaskDelay(1000/portTICK_RATE_MS);
    //
    // brushed_motor_stop();
    // vTaskDelay(1000/portTICK_RATE_MS);
    //
    // // works!
    // brushed_motor_turn_left(90.0);
    // vTaskDelay(1000/portTICK_RATE_MS);
    //
    // // works!
    // brushed_motor_stop();
    // vTaskDelay(1000/portTICK_RATE_MS);
    }
}
/////////////////////////////////////////////////////
typedef struct {
    int type;  // the type of timer's event
    int timer_group;
    int timer_idx;
    uint64_t timer_counter_value;
} timer_event_t;

xQueueHandle timer_queue;

void IRAM_ATTR timer_group0_isr(void *para){
    int timer_idx = (int) para;

    /* Retrieve the interrupt status and the counter value
       from the timer that reported the interrupt */
    uint32_t intr_status = TIMERG0.int_st_timers.val;
    TIMERG0.hw_timer[timer_idx].update = 1;
    uint64_t timer_counter_value =
        ((uint64_t) TIMERG0.hw_timer[timer_idx].cnt_high) << 32
        | TIMERG0.hw_timer[timer_idx].cnt_low;

    /* Prepare basic event data
       that will be then sent back to the main program task */
    timer_event_t evt;
    evt.timer_group = 0;
    evt.timer_idx = timer_idx;
    evt.timer_counter_value = timer_counter_value;

    /* Clear the interrupt
       and update the alarm time for the timer with without reload */
    if ((intr_status & BIT(timer_idx)) && timer_idx == TIMER_0) {
        evt.type = TEST_WITHOUT_RELOAD;
        TIMERG0.int_clr_timers.t0 = 1;
        timer_counter_value += (uint64_t) (TIMER_INTERVAL0_SEC * TIMER_SCALE);
        TIMERG0.hw_timer[timer_idx].alarm_high = (uint32_t) (timer_counter_value >> 32);
        TIMERG0.hw_timer[timer_idx].alarm_low = (uint32_t) timer_counter_value;
    } else if ((intr_status & BIT(timer_idx)) && timer_idx == TIMER_1) {
        evt.type = TEST_WITH_RELOAD;
        TIMERG0.int_clr_timers.t1 = 1;
    } else {
        evt.type = -1; // not supported even type
    }

    /* After the alarm has been triggered
      we need enable it again, so it is triggered the next time */
    TIMERG0.hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN;

    /* Now just send the event data back to the main program task */
    xQueueSendFromISR(timer_queue, &evt, NULL);
}

static void example_tg0_timer_init(int timer_idx) {
    /* Select and initialize basic parameters of the timer */
    timer_config_t config;
    config.divider = TIMER_DIVIDER;
    config.counter_dir = TIMER_COUNT_UP;
    config.counter_en = TIMER_PAUSE;
    config.alarm_en = TIMER_ALARM_DIS;
    config.intr_type = TIMER_INTR_LEVEL;
    timer_init(TIMER_GROUP_0, timer_idx, &config);

    /* Timer's counter will initially start from value below.
       Also, if auto_reload is set, this value will be automatically reload on alarm */
    timer_set_counter_value(TIMER_GROUP_0, timer_idx, 0x00000000ULL);

    /* Configure the alarm value and the interrupt on alarm. */
    // timer_set_alarm_value(TIMER_GROUP_0, timer_idx, timer_interval_sec * TIMER_SCALE);
    // timer_enable_intr(TIMER_GROUP_0, timer_idx);
    // timer_isr_register(TIMER_GROUP_0, timer_idx, timer_group0_isr,
        // (void *) timer_idx, ESP_INTR_FLAG_IRAM, NULL);

    // timer_start(TIMER_GROUP_0, timer_idx);
}

/////////////////////////////////////////////////////
static void setLED() {
  ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, 2000);
  ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
}

/////////////////////////////////////////////////////
static void check_efuse() {
    //Check TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

static void print_char_val_type(esp_adc_cal_value_t val_type) {
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

/////////////////////////////////////////////////////
static int getState(uint32_t adc_reading) {
  if (adc_reading < 1500) return HIGH;
    // according to website, voltage dips when something is near & "sensor is much more sensitive to the white paper than the black. The black surface absorbs more light from the LED, meaning less is reflected back to the phototransistor." overall, voltage output is less than 1.5V (from graph) for white (dips more since its more sensitive to white) 
  else return LOW;
}

// static uint32_t measureTimeForRisingEdges (uint32_t adc_reading) {
//   uint32_t time = 0;
//   int state;
//   if(adc_reading < 1500) state = HIGH;
//   else state = LOW;
//
// }

/////////////////////////////////////////////////////
void app_main(){
    //Check if Two Point or Vref are burned into eFuse
    check_efuse();

    //Configure ADC
    if (unit == ADC_UNIT_1) {
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(channel, atten);
    } else {
        adc2_config_channel_atten((adc2_channel_t)channel, atten);
    }
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);

    //Initialize led
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
    ledc_fade_func_install(0);

    //Configure timer
    timer_queue = xQueueCreate(10, sizeof(timer_event_t));
    example_tg0_timer_init(TIMER_0);

    //More Motor Stuff
    printf("Testing brushed motor...\n");
    xTaskCreate(mcpwm_example_brushed_motor_control, "mcpwm_example_brushed_motor_control", 4096, NULL, 5, NULL);

    int prevState = LOW;
    int risingEdgeCount = 0;
    double counter_time_sec = 0;
    double speed = 0;
    double distance = 3.1415 * 25.75 * 0.1 * 0.5;  // in centimeters

    setLED();
    while (1) {
        int adc_reading = 0;
        //Multisampling
        for (int i = 0; i < NO_OF_SAMPLES; i++) {
            if (unit == ADC_UNIT_1) {
                adc_reading += adc1_get_raw((adc1_channel_t)channel);
            } else {
                int raw;
                adc2_get_raw((adc2_channel_t)channel, ADC_WIDTH_BIT_12, &raw);
                adc_reading += raw;
            }
        }
        adc_reading /= NO_OF_SAMPLES;
        // adc2_get_raw((adc2_channel_t)channel, ADC_WIDTH_BIT_12, &adc_reading);
        // printf("Raw: %d\n", adc_reading);
        // uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
        int state = getState(adc_reading);
        if(state == HIGH && prevState == LOW) {
          // from LOW to HIGH
          if(risingEdgeCount == 0) {
            timer_start(TIMER_GROUP_0, TIMER_0);
          } else if (risingEdgeCount == 1) {
            timer_pause(TIMER_GROUP_0, TIMER_0);
            esp_err_t ret = timer_get_counter_time_sec(TIMER_GROUP_0, TIMER_0, &counter_time_sec);
            speed = distance / counter_time_sec;
            timer_set_counter_value(TIMER_GROUP_0, TIMER_0, 0x00000000ULL);
            timer_start(TIMER_GROUP_0, TIMER_0);
            risingEdgeCount = 0;
            counter_time_sec = 0;
            printf("Speed: %f cm/s\n", speed);
          }
        } else if (state == LOW && prevState == HIGH) {
          // from HIGH to LOW
          risingEdgeCount = 1;
        }
        // printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);
        // uint32_t dist_mm = adc_reading * 5 + 300;
        // printf("Distance: %dmm\n", dist_mm);
        prevState = state;
        vTaskDelay(1);
    }
}
