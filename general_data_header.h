#ifndef general_data_header_H
#define	general_data_header_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "esp_adc/adc_oneshot.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc.h"
#include "soc/soc_caps.h"
#include "driver/gptimer.h"
#include "freertos/queue.h"
#include "character.h"
#include "esp_log.h"
#include "driver/spi_slave.h"
#include "esp_task_wdt.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "soc/rtc_periph.h"
#include "spi_flash_mmap.h"


/*
=======================================================================================================================================================================================================
========================  ESP32 PIN DEFINES  ==========================================================================================================================================================
=======================================================================================================================================================================================================
*/

#define ROW0_PIN 5
#define ROW1_PIN 18
#define ROW2_PIN 19
#define ROW3_PIN 21
#define RED_U 15
#define BLUE_U 2
#define GREEN_U 0
#define RED_L 26
#define BLUE_L 16
#define GREEN_L 17
#define D_CLK 22
#define D_STB 23
#define D_ENA 27
#define BRIGHT_PWM 25

#define GPIO_MISO 13
#define GPIO_SCLK 35
#define GPIO_MOSI 32
#define GPIO_CS 33

#define PHOTO_ADC_INPUT 14


/*
=======================================================================================================================================================================================================
========================  LED_D_DATA LINE DEFINES  ====================================================================================================================================================
=======================================================================================================================================================================================================
*/

#define LED_D_SOT 0
#define LED_D_LINE_1 1
#define LED_D_LINE_2 2
#define LED_D_LINE_3 3
#define LED_D_LINE_4 4
#define LED_D_COLOR 5
#define LED_D_LUM_AVG 6
#define LED_D_EOT 7

/*
=======================================================================================================================================================================================================
========================  START OF TEXT/ END OF TEXT DEFINE  ==========================================================================================================================================
=======================================================================================================================================================================================================
*/

#define SOT 0x02
#define EOT 0x03

/*
=======================================================================================================================================================================================================
========================  DISPLAY UPPER/ LOWER ENUMERATION  ===========================================================================================================================================
=======================================================================================================================================================================================================
*/

typedef enum{
    display_U,
    display_L
}DISPLAY_PART;

/*
=======================================================================================================================================================================================================
========================  GLOBAL VARIABLES  ===========================================================================================================================================================
=======================================================================================================================================================================================================
*/

extern char myTotalString[64];
extern char characterBoxLine_1[11][8], characterBoxLine_2[11][8], characterBoxLine_3[11][8], characterBoxLine_4[11][8];
extern uint8_t colors;
extern int16_t ADC_Average[45];
extern uint16_t ENATime; 
extern spi_host_device_t host;
extern char spiSortBuffer[100];
extern float ftENATime;
extern bool isCharacterSizeSmall;
extern uint16_t maxLuminanceDisplayStartup;

/*
=======================================================================================================================================================================================================
========================  APP MAIN PIN INIT  ==========================================================================================================================================================
=======================================================================================================================================================================================================
*/

extern void pinInit(void);

/*
=======================================================================================================================================================================================================
========================  HUB75 RELATED  ==============================================================================================================================================================
=======================================================================================================================================================================================================
*/

extern void textColorSet(DISPLAY_PART U_L);
extern void rowsAtHUB75(uint8_t characterLineIndex);
extern void backgroundColorSet(void);
extern void strobe(void);
extern void clkPulse(void);
extern void clkPulseX2(void);
extern void displayBrightnesControl(void);
void runHub75(void);
extern void runHub75Row1(void);
extern void runHub75Row2(void);
extern void runHub75Row3(void);
extern void runHub75Row4(void);

/*
=======================================================================================================================================================================================================
========================  SPI RELATED  ================================================================================================================================================================
=======================================================================================================================================================================================================
*/

extern uint16_t ADC_LightSensor(void);
extern void ADC_AverageInit(void);
void spiBusReciever(void);
void initLED_D_Data(char LED_D_Data[8][11]);
void splitLED_D_DataItemschar(char LED_D_Data[8][11]);
void fillOutWithSpoace(char LED_D_Data[8][11]);
uint16_t calculateNumberOfLumAVG(char LED_D_Data[8][11]);
void moveAverageElements(uint8_t ADC_NumberOfAverages);
uint16_t calculateAverage(uint8_t ADC_NumberOfAverages);
extern void HUB75_ColorData(char LED_D_Data[8][11]);
extern void HUB75_Block1_Print(char LED_D_Data[8][11]);
extern void HUB75_Block2_Print(char LED_D_Data[8][11]);
extern void HUB75_Block3_Print(char LED_D_Data[8][11]);
extern void HUB75_Block4_Print(char LED_D_Data[8][11]);
void HUB75_ENATime(void);
void calculate_ftENATime(void);

/*
=======================================================================================================================================================================================================
========================  SPI  ========================================================================================================================================================================
=======================================================================================================================================================================================================
*/

void runSPI_Loop(void);

/*
=======================================================================================================================================================================================================
========================  TECTA STARTUP SCROLL  =======================================================================================================================================================
=======================================================================================================================================================================================================
*/

void typeTECTA_InLargeCharacters(void);
void fadeTECTA_InLargeCharactersOut(void);
void twinkleTECTA_InLargeYellowCharacters(void);
void typeAplifierNumberInGreenCharacters(void);
void prepareStandardOperation(void);
void tectaStartupScroll(void);
void TECTA_FullMessage(void);
void typeA_LargeCharacter(char character, uint8_t charNumber, uint16_t brightDelayNumber);
void runHub75Row1Start(char string[11], uint16_t brightDelayNumber);
void runHub75Row2Start(char string[11], uint16_t brightDelayNumber);
void runHub75Row3Start(char string[11], uint16_t brightDelayNumber);
void runHub75Row4Start(char string[11], uint16_t brightDelayNumber);
void HUB75_Block2_PrintStart(char string[11]);
void HUB75_Block3_PrintStart(char string[11]);

#endif