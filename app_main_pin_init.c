#include "general_data_header.h"

void pinInit(void){
    gpio_reset_pin(ROW0_PIN);
    gpio_set_direction(ROW0_PIN, GPIO_MODE_OUTPUT);
    gpio_reset_pin(ROW1_PIN);
    gpio_set_direction(ROW1_PIN, GPIO_MODE_OUTPUT);
    gpio_reset_pin(ROW2_PIN);
    gpio_set_direction(ROW2_PIN, GPIO_MODE_OUTPUT);
    gpio_reset_pin(ROW3_PIN);
    gpio_set_direction(ROW3_PIN, GPIO_MODE_OUTPUT);   

    gpio_reset_pin(RED_U);
    gpio_set_direction(RED_U, GPIO_MODE_OUTPUT);   
    gpio_reset_pin(BLUE_U);
    gpio_set_direction(BLUE_U, GPIO_MODE_OUTPUT);   
    gpio_reset_pin(GREEN_U);
    gpio_set_direction(GREEN_U, GPIO_MODE_OUTPUT);

    gpio_reset_pin(RED_L);
    gpio_set_direction(RED_L, GPIO_MODE_OUTPUT);   
    gpio_reset_pin(BLUE_L);
    gpio_set_direction(BLUE_L, GPIO_MODE_OUTPUT);   
    gpio_reset_pin(GREEN_L);
    gpio_set_direction(GREEN_L, GPIO_MODE_OUTPUT);  

    gpio_reset_pin(D_CLK);
    gpio_set_direction(D_CLK, GPIO_MODE_OUTPUT);   
    gpio_reset_pin(D_STB);
    gpio_set_direction(D_STB, GPIO_MODE_OUTPUT);   
    gpio_reset_pin(D_ENA);
    gpio_set_direction(D_ENA, GPIO_MODE_OUTPUT);   

    gpio_reset_pin(BRIGHT_PWM);
    gpio_set_direction(BRIGHT_PWM, GPIO_MODE_OUTPUT);    

    gpio_reset_pin(GPIO_SCLK);
    gpio_set_direction(GPIO_SCLK, GPIO_PULLUP_ONLY);   
    gpio_reset_pin(GPIO_MOSI);
    gpio_set_direction(GPIO_MOSI, GPIO_PULLUP_ONLY);   
    gpio_reset_pin(GPIO_CS);
    gpio_set_direction(GPIO_CS, GPIO_PULLUP_ONLY);      

    gpio_reset_pin(PHOTO_ADC_INPUT);
    gpio_set_direction(PHOTO_ADC_INPUT, GPIO_MODE_INPUT);   
    gpio_set_direction(PHOTO_ADC_INPUT, GPIO_FLOATING);

    gpio_set_level(ROW0_PIN, 0);
    gpio_set_level(ROW1_PIN, 0);
    gpio_set_level(ROW2_PIN, 0);
    gpio_set_level(ROW3_PIN, 0);

    gpio_set_level(RED_U, 0);
    gpio_set_level(BLUE_U, 0);
    gpio_set_level(GREEN_U, 0);

    gpio_set_level(RED_L, 0);
    gpio_set_level(BLUE_L, 0);
    gpio_set_level(GREEN_L, 0);    

    gpio_set_level(D_CLK, 0);
    gpio_set_level(D_STB, 0);
    gpio_set_level(D_ENA, 1);      

    gpio_set_level(BRIGHT_PWM, 0);
}