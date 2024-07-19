#include "general_data_header.h"

char myTotalString[64];

/*
=======================================================================================================================================================================================================
========================  CALCULATE DISPLAY STARTUPP BRIGHTNESS  ======================================================================================================================================
=======================================================================================================================================================================================================
*/

void ADC_AverageInit(void){
    int16_t ADC_PreReading = ADC_LightSensor();
    if(ADC_PreReading < 0) ADC_PreReading = 0;
    ENATime = 0;
    //ADC_ImAverage = 0; 
    for(uint8_t avrIndex = 0; avrIndex < 45; avrIndex++){
        ADC_Average[avrIndex] = ADC_PreReading;
    }
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY BRIGHTNESS ADC SETUPP ===============================================================================================================================================
=======================================================================================================================================================================================================
*/

uint16_t ADC_LightSensor(void){
    //-------------ADC1 Init---------------//    
    adc_oneshot_unit_handle_t adc2_handle;
    adc_oneshot_unit_init_cfg_t init_config2 = {
        .unit_id = ADC_UNIT_2,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };   
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config2, &adc2_handle));

    //-------------ADC1 Config---------------//
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc2_handle, ADC_CHANNEL_6, &config));

    static int ADC_Reading;
    ESP_ERROR_CHECK(adc_oneshot_read(adc2_handle, ADC_CHANNEL_6, &ADC_Reading));
    ESP_ERROR_CHECK(adc_oneshot_del_unit(adc2_handle));
    return (uint16_t)ADC_Reading;
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY SPI RECEIVER SETUPP  ================================================================================================================================================
=======================================================================================================================================================================================================
*/

void spiBusReciever(void){  
    runSPI_Loop();   
}

/*
=======================================================================================================================================================================================================
========================  INITIALIZE LED_D_DATA STRING VARIABLES  =====================================================================================================================================
=======================================================================================================================================================================================================
*/

void initLED_D_Data(char LED_D_Data[8][11]){
    strcpy(LED_D_Data[LED_D_SOT], "");
    strcpy(LED_D_Data[LED_D_LINE_1], "");
    strcpy(LED_D_Data[LED_D_LINE_2], "");
    strcpy(LED_D_Data[LED_D_LINE_3], "");
    strcpy(LED_D_Data[LED_D_LINE_4], "");
    strcpy(LED_D_Data[LED_D_COLOR], "");
    strcpy(LED_D_Data[LED_D_LUM_AVG], "");
    strcpy(LED_D_Data[LED_D_EOT], "");    
}

/*
=======================================================================================================================================================================================================
========================  SPI MESSAGE SPLITTER  =======================================================================================================================================================
=======================================================================================================================================================================================================
*/

void splitLED_D_DataItemschar(char LED_D_Data[8][11]){
    uint8_t LED_CharIndex = 0;
    uint8_t stringCharIndex = 0;
    uint8_t LED_LineIndex = 0;
    uint8_t LED_CharLen = strlen(myTotalString);
    uint8_t numberOfSeparators = 0;

    printf("myTotalString: %s\r\n", myTotalString);
    while(true){
        if(myTotalString[stringCharIndex] != ';'){
            LED_D_Data[LED_LineIndex][LED_CharIndex] = myTotalString[stringCharIndex];
            stringCharIndex++;
            LED_CharIndex++;
        }
        else{
            numberOfSeparators++;
            stringCharIndex++;
            LED_D_Data[LED_LineIndex][LED_CharIndex] = '\0';
            LED_CharIndex++;
            LED_LineIndex++;
            LED_CharIndex = 0;
        }
        if(stringCharIndex > LED_CharLen) break;
    }
    printf("LED_D_LUM_AVG: %s\n\r", LED_D_Data[LED_D_LUM_AVG]);
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY FILLOUT WITH SPACES TO FILL REST CHARACTERS AT THE LED DISPLAY  =====================================================================================================
=======================================================================================================================================================================================================
*/

void fillOutWithSpoace(char LED_D_Data[8][11]){
    for(uint8_t LED_LineIndex = 1; LED_LineIndex < 7; LED_LineIndex++){
        uint8_t LED_D_DataLength = (uint8_t)strlen(LED_D_Data[LED_LineIndex]);
        for(uint8_t byteIndex = 0; byteIndex < 11; byteIndex++){
            if(byteIndex >= LED_D_DataLength) LED_D_Data[LED_LineIndex][byteIndex] = ' ';
            if(byteIndex == 10) LED_D_Data[LED_LineIndex][10] = '\0';
        }
    }
}

/*
=======================================================================================================================================================================================================
========================  CALCULATE THE SUM FOR AVERAGING  ============================================================================================================================================
=======================================================================================================================================================================================================
*/

uint16_t calculateNumberOfLumAVG(char LED_D_Data[8][11]){
    uint16_t summ = 0;
    for(uint8_t byteIndex = 0; byteIndex < 2; byteIndex++){
        summ = summ * 10 + LED_D_Data[LED_D_LUM_AVG][byteIndex] - 48;
    }
    return summ;   
}

/*
=======================================================================================================================================================================================================
========================  MOVE THE ELEMENTS FOR SUM FOR EACH NEW SAMPLE  ==============================================================================================================================
=======================================================================================================================================================================================================
*/

void moveAverageElements(uint8_t ADC_NumberOfAverages){
    for(uint8_t avrIndex = ADC_NumberOfAverages - 1; avrIndex > 0; avrIndex--){
        ADC_Average[avrIndex] = ADC_Average[avrIndex - 1];
    }
}

/*
=======================================================================================================================================================================================================
========================  CALCULATE THE AVERAGE FOR SAMPLES  ==========================================================================================================================================
=======================================================================================================================================================================================================
*/

uint16_t calculateAverage(uint8_t ADC_NumberOfAverages){
    uint32_t ADC_AVG_Sum = 0;
    for(uint8_t avrIndex = 0; avrIndex < ADC_NumberOfAverages; avrIndex++){
        ADC_AVG_Sum = ADC_AVG_Sum + ADC_Average[avrIndex];
    }
    if(ADC_NumberOfAverages == 0) ADC_NumberOfAverages = 1;
    return (uint16_t)(ADC_AVG_Sum / ADC_NumberOfAverages);
}

/*
=======================================================================================================================================================================================================
========================  SET COLOR NUMBER MATCHING COLOR STRING  =====================================================================================================================================
=======================================================================================================================================================================================================
*/

void HUB75_ColorData(char LED_D_Data[8][11]){
    if(strstr(LED_D_Data[LED_D_COLOR], "BLACK")) colors = 0x00;
    else if(strstr(LED_D_Data[LED_D_COLOR], "RED")) colors = 0x01;
    else if(strstr(LED_D_Data[LED_D_COLOR], "GREEN")) colors = 0x02;
    else if(strstr(LED_D_Data[LED_D_COLOR], "YELLOW")) colors = 0x03;
    else if(strstr(LED_D_Data[LED_D_COLOR], "BLUE")) colors = 0x04;
    else if(strstr(LED_D_Data[LED_D_COLOR], "MAGENTA")) colors = 0x05;
    else if(strstr(LED_D_Data[LED_D_COLOR], "CYAN")) colors = 0x06;
    else if(strstr(LED_D_Data[LED_D_COLOR], "WHITE")) colors = 0x07;
}

/*
=======================================================================================================================================================================================================
========================  CREATE BLOCKS OF TEXT IMAGES FOR PRINTING AT CORE 1  ========================================================================================================================
=======================================================================================================================================================================================================
*/

void HUB75_Block1_Print(char LED_D_Data[8][11]){
    for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
        for(int characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
            char myCharacter = (int)LED_D_Data[LED_D_LINE_1][characterIndex];
            characterBoxLine_1[characterIndex][characterLineIndex] = myCharacters[(int)myCharacter][characterLineIndex];
        }
    }
}

void HUB75_Block2_Print(char LED_D_Data[8][11]){
    for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
        for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
            int myCharacter = (int)LED_D_Data[LED_D_LINE_2][characterIndex];
            characterBoxLine_2[characterIndex][characterLineIndex] = myCharacters[(int)myCharacter][characterLineIndex];
        }
    }    
}

void HUB75_Block3_Print(char LED_D_Data[8][11]){
    for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
        for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
            int myCharacter = (int)LED_D_Data[LED_D_LINE_3][characterIndex];
            characterBoxLine_3[characterIndex][characterLineIndex] = myCharacters[(int)myCharacter][characterLineIndex];
        }
    }  
}

void HUB75_Block4_Print(char LED_D_Data[8][11]){
    for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
        for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
            int myCharacter = (int)LED_D_Data[LED_D_LINE_4][characterIndex];
            characterBoxLine_4[characterIndex][characterLineIndex] = myCharacters[(int)myCharacter][characterLineIndex];
        }
    }   
}

/*
=======================================================================================================================================================================================================
========================  CALCULATIONS FOR HUB75 ENABLE TIME  =========================================================================================================================================
=======================================================================================================================================================================================================
*/


void calculate_ftENATime(void){
    if(ENATime < 7) ENATime = 7;
    else if(ENATime > 1700) ENATime = 1700;
    ftENATime = 0;
    ftENATime = (float)(pow(ENATime, 2) / 2000);
}


void HUB75_ENATime(void){    
    gpio_set_level(BRIGHT_PWM, 1);
    gpio_set_level(D_ENA, 0);
    uint16_t number = 0;
    while(true){
        number++;
        if(number > ftENATime) break;
    }
    gpio_set_level(BRIGHT_PWM, 0);
    gpio_set_level(D_ENA, 1);
}