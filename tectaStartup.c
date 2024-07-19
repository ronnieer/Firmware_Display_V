#include "general_data_header.h"

/*
=======================================================================================================================================================================================================
========================  SCROLL T  E  C  T  A IN AT LINE 1 AND THEN TYPE IT IN LARGE CHARACTERS  =====================================================================================================
=======================================================================================================================================================================================================
*/

bool isCharacterSizeSmall;
uint16_t maxLuminanceDisplayStartup = 4500;

void tectaStartupScroll(void){
    typeTECTA_InLargeCharacters();
    fadeTECTA_InLargeCharactersOut();
    twinkleTECTA_InLargeYellowCharacters();
    typeAplifierNumberInGreenCharacters();
    prepareStandardOperation();
}

void typeTECTA_InLargeCharacters(void){
    isCharacterSizeSmall = true;
    colors = 0x01;
    typeA_LargeCharacter('T', 0, maxLuminanceDisplayStartup);
    typeA_LargeCharacter('E', 1, maxLuminanceDisplayStartup);
    typeA_LargeCharacter('C', 2, maxLuminanceDisplayStartup);
    typeA_LargeCharacter('T', 3, maxLuminanceDisplayStartup);
    typeA_LargeCharacter('A', 4, maxLuminanceDisplayStartup);
}

/*
=======================================================================================================================================================================================================
========================  FADE RED TECTA IN LARGE CHARACTERS OUT  =====================================================================================================================================
=======================================================================================================================================================================================================
*/

void fadeTECTA_InLargeCharactersOut(void){
    char string[11];
    uint16_t result;
    uint8_t repeats = 0;
    colors = 0x01;
    while(true){
        isCharacterSizeSmall = false;
        result = (uint16_t)(maxLuminanceDisplayStartup - (double)((maxLuminanceDisplayStartup - 100) * (1 - cos((double)(3.14 / 2 / 150 * repeats)))));
        strcpy(string, "<=8945<=01");
        runHub75Row2Start(string, result);
        strcpy(string, ">?:;67>?23");
        runHub75Row3Start(string, result);            
        if(repeats > 150) break;
        repeats++; 
        vTaskDelay(10 / portTICK_PERIOD_MS); 
    }    
}

/*
=======================================================================================================================================================================================================
========================  TWINKLE TECTA IN LARGE YELLOW CHARACTERS  ===================================================================================================================================
=======================================================================================================================================================================================================
*/

void twinkleTECTA_InLargeYellowCharacters(void){
    uint16_t sineResult; 
    uint8_t repeats = 0;
    char string[11];
    colors = 0x03;
    while(true){
        sineResult = maxLuminanceDisplayStartup - (maxLuminanceDisplayStartup - 100) * (double)cos((double)(3.14 / 2 / 150 * repeats));
        strcpy(string, "<=8945<=01");
        runHub75Row2Start(string, sineResult);
        strcpy(string, ">?:;67>?23");
        runHub75Row3Start(string, sineResult);            
        if(repeats > 150) break;
        repeats++;  
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }   
    repeats = 0;
    while(true){
        sineResult = maxLuminanceDisplayStartup - (maxLuminanceDisplayStartup - 100) * (double)(1 - cos((double)(3.14 / 2 / 150 * repeats)));
        strcpy(string, "<=8945<=01");
        runHub75Row2Start(string, sineResult);
        strcpy(string, ">?:;67>?23");
        runHub75Row3Start(string, sineResult);            
        if(repeats > 150) break;
        repeats++;  
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }           
}

/*
=======================================================================================================================================================================================================
========================  INCREASE MESSAGE "Valve Pre Amplifier A1003" IN GREAN CHARACTERS AT THE DISPLAY  ============================================================================================
=======================================================================================================================================================================================================
*/
    
void typeAplifierNumberInGreenCharacters(void){
    uint16_t result;
    uint8_t repeats = 0;
    char string[11];
    colors = 0x02;
    while(true){
        uint16_t result = (uint16_t)(maxLuminanceDisplayStartup - (double)((maxLuminanceDisplayStartup - 100) * cos((double)(3.14 / 2 / 150 * repeats))));
        isCharacterSizeSmall = true;
        strcpy(string, "Valve Pre-");
        runHub75Row1Start(string, result);   
        strcpy(string, "Amplfier  ");
        runHub75Row2Start(string, result);   
        strcpy(string, "          ");
        runHub75Row3Start(string, result);
        strcpy(string, "A1003     ");
        runHub75Row4Start(string, result);
        vTaskDelay(10 / portTICK_PERIOD_MS); 
        if(repeats > 150) break;
        repeats++; 
    }

/*
=======================================================================================================================================================================================================
========================  DWELL OUTPUT "Valve Pre Amplifier A1003" AT THE DISPLAY WITH BRIGHTNESS AT NO CHANGE  =======================================================================================
=======================================================================================================================================================================================================
*/

    repeats = 0;
    while(true){
        result = maxLuminanceDisplayStartup;
        uint16_t dummy = (uint16_t)(maxLuminanceDisplayStartup - (double)((maxLuminanceDisplayStartup - 100) * cos((double)(3.14 / 2 / 150 * repeats))));
        dummy = dummy;
        isCharacterSizeSmall = true;
        strcpy(string, "Valve Pre-");
        runHub75Row1Start(string, result);   
        strcpy(string, "Amplfier  ");
        runHub75Row2Start(string, result);   
        strcpy(string, "          ");
        runHub75Row3Start(string, result);
        strcpy(string, "A1003     ");
        runHub75Row4Start(string, result);
        vTaskDelay(10 / portTICK_PERIOD_MS); 
        if(repeats > 150) break;
        repeats++; 
    }

/*
=======================================================================================================================================================================================================
========================  DECREASE MESSAGE "Valve Pre Amplifier A1003" IN GREAN CHARACTERS AT THE DISPLAY  ============================================================================================
=======================================================================================================================================================================================================
*/

    repeats = 0;
    while(true) {  
        result = (uint16_t)(maxLuminanceDisplayStartup - (double)((maxLuminanceDisplayStartup - 100) * (1 - cos((double)(3.14 / 2 / 150 * repeats)))));
        isCharacterSizeSmall = true;
        strcpy(string, "Valve Pre-");
        runHub75Row1Start(string, result);   
        strcpy(string, "Amplfier  ");
        runHub75Row2Start(string, result);   
        strcpy(string, "          ");
        runHub75Row3Start(string, result);
        strcpy(string, "A1003     ");
        runHub75Row4Start(string, result);
        vTaskDelay(10 / portTICK_PERIOD_MS);         
        if(repeats > 150) break;
        repeats++;   
    }  
}

/*
=======================================================================================================================================================================================================
========================  CLEAR DISPLAY AND GIVE CONTROLL TO STADARD OPERATION  =======================================================================================================================
=======================================================================================================================================================================================================
*/

void prepareStandardOperation(void){
    char LED_D_Data[8][11];
    strcpy(LED_D_Data[LED_D_LINE_1], "          ");
    strcpy(LED_D_Data[LED_D_LINE_2], "          ");
    strcpy(LED_D_Data[LED_D_LINE_3], "          ");
    strcpy(LED_D_Data[LED_D_LINE_4], "          ");
    strcpy(LED_D_Data[LED_D_LUM_AVG], "10");
    strcpy(LED_D_Data[LED_D_COLOR], "GREEN"); 
    HUB75_ColorData(LED_D_Data);
    HUB75_Block1_Print(LED_D_Data);
    HUB75_Block2_Print(LED_D_Data);
    HUB75_Block3_Print(LED_D_Data);
    HUB75_Block4_Print(LED_D_Data); 
    runHub75Row1();
    runHub75Row2();
    runHub75Row3();
    runHub75Row4();    
    vTaskDelay(10 / portTICK_PERIOD_MS);        
}   

/*
=======================================================================================================================================================================================================
========================  EACH CHARACTER SCROLL IN AND THEN TYPE LARGE CHARACTERS  ====================================================================================================================
=======================================================================================================================================================================================================
*/

void typeA_LargeCharacter(char character, uint8_t charNumber, uint16_t brightDelayNumber){
    isCharacterSizeSmall = false;
    int8_t x_Pos = 57;
    uint8_t numberOfClockPulses = 0;
    uint8_t repeats = 0;
    char charBoxLine_1[8];
    char string[11];
    while(true){
        for(int characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
            charBoxLine_1[characterLineIndex] = myCharacters[(int)character][characterLineIndex];
        }
        while(true){
            for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
                numberOfClockPulses = x_Pos;
                while(true){
                    if(numberOfClockPulses == 0) break;
                    clkPulse();
                    numberOfClockPulses--;
                }
                
                for(uint8_t characterLinePixelsIndex = 0; characterLinePixelsIndex < 6; characterLinePixelsIndex++){
                    rowsAtHUB75(characterLineIndex);
                    uint8_t lineOfPixels = charBoxLine_1[characterLineIndex];
                    if(((lineOfPixels >> characterLinePixelsIndex) & 0x01) == 0x01){
                        textColorSet(display_U);
                    }
                    else{
                        backgroundColorSet();      
                    }
                    clkPulse();
                }            
                backgroundColorSet();
                uint8_t remainingNumberOfClockpulses = 0;
                while(true){
                    if(remainingNumberOfClockpulses >= 58 - x_Pos) break;
                    clkPulse();
                    remainingNumberOfClockpulses++;
                }
                numberOfClockPulses = 0;
                remainingNumberOfClockpulses = 0;
                strobe();
                gpio_set_level(D_ENA, 0);
                for(uint16_t delay = 0; delay < brightDelayNumber; delay++){}
                gpio_set_level(D_ENA, 1);
            }
            if(charNumber == 0){
                strcpy(string, "          ");
                runHub75Row2Start(string, brightDelayNumber);
                strcpy(string, "          ");
                runHub75Row3Start(string, brightDelayNumber);
            }   
            else if(charNumber == 1){
                strcpy(string, "<=        ");
                runHub75Row2Start(string, brightDelayNumber);
                strcpy(string, ">?        ");
                runHub75Row3Start(string, brightDelayNumber);
            }
            else if(charNumber == 2){
                strcpy(string, "<=89      ");
                runHub75Row2Start(string, brightDelayNumber);
                strcpy(string, ">?:;      ");
                runHub75Row3Start(string, brightDelayNumber);
            }    
            else if(charNumber == 3){
                strcpy(string, "<=8945    ");
                runHub75Row2Start(string, brightDelayNumber);
                strcpy(string, ">?:;67    ");
                runHub75Row3Start(string, brightDelayNumber);
            }    
            else if(charNumber == 4){
                strcpy(string, "<=8945<=  ");
                runHub75Row2Start(string, brightDelayNumber);
                strcpy(string, ">?:;67>?  ");
                runHub75Row3Start(string, brightDelayNumber);
            }
            else if(charNumber == 4){
                strcpy(string, "<=8945<=01");
                runHub75Row2Start(string, brightDelayNumber);
                strcpy(string, ">?:;67>?23");
                runHub75Row3Start(string, brightDelayNumber);
            }              
            if(repeats > 0) break;
            repeats++;
        }
        x_Pos--;
        repeats = 0;
        if(x_Pos <= 12 * charNumber){
            charNumber++;
            x_Pos = 57;
            break;
        } 
    }
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY ROW ONE BUILD ROUTINE  ==============================================================================================================================================
=======================================================================================================================================================================================================
*/

void runHub75Row1Start(char string[11], uint16_t brightDelayNumber){
    for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
        for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
            int myCharacter = (int)string[characterIndex];
            if(isCharacterSizeSmall == false) characterBoxLine_1[characterIndex][characterLineIndex] = myLargeCharacters[(int)myCharacter][characterLineIndex];
            else characterBoxLine_1[characterIndex][characterLineIndex] = myCharacters[(int)myCharacter][characterLineIndex];
        }
    }      
    for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
        clkPulseX2();
        for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
            for(uint8_t characterLinePixelsIndex = 0; characterLinePixelsIndex < 6; characterLinePixelsIndex++){
                rowsAtHUB75(characterLineIndex + 0); 
                uint8_t lineOfPixels = characterBoxLine_1[characterIndex][characterLineIndex];
                if(((lineOfPixels >> characterLinePixelsIndex) & 0x01) == 0x01){
                    textColorSet(display_U);
                }
                else{
                    backgroundColorSet();    
                }                        
                clkPulse();
            }            
        }
        backgroundColorSet();
        clkPulseX2();
        strobe();
        gpio_set_level(D_ENA, 0);
        for(uint16_t delay = 0; delay < brightDelayNumber; delay++){}
        gpio_set_level(D_ENA, 1);
    }
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY ROW TWO BUILD ROUTINE - FOR LARGE CHARACTERS  =======================================================================================================================
=======================================================================================================================================================================================================
*/

void runHub75Row2Start(char string[11], uint16_t brightDelayNumber){
    for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
        for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
            int myCharacter = (int)string[characterIndex];
            if(isCharacterSizeSmall == false) characterBoxLine_2[characterIndex][characterLineIndex] = myLargeCharacters[(int)myCharacter][characterLineIndex];
            else characterBoxLine_2[characterIndex][characterLineIndex] = myCharacters[(int)myCharacter][characterLineIndex];            
        }
    }      
    for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
        clkPulseX2();
        for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
            for(uint8_t characterLinePixelsIndex = 0; characterLinePixelsIndex < 6; characterLinePixelsIndex++){
                rowsAtHUB75(characterLineIndex + 8); 
                uint8_t lineOfPixels = characterBoxLine_2[characterIndex][characterLineIndex];
                if(((lineOfPixels >> characterLinePixelsIndex) & 0x01) == 0x01){
                    textColorSet(display_U);
                }
                else{
                    backgroundColorSet();    
                }                        
                clkPulse();
            }            
        }
        backgroundColorSet();
        clkPulseX2();
        strobe();
        gpio_set_level(D_ENA, 0);
        for(uint16_t delay = 0; delay < brightDelayNumber; delay++){}
        gpio_set_level(D_ENA, 1);
    }
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY ROW THREE BUILD ROUTINE - FOR LARGE CHARACTERS  =====================================================================================================================
=======================================================================================================================================================================================================
*/

void runHub75Row3Start(char string[11], uint16_t brightDelayNumber){
    for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
        for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
            int myCharacter = (int)string[characterIndex];
            if(isCharacterSizeSmall == false) characterBoxLine_3[characterIndex][characterLineIndex] = myLargeCharacters[(int)myCharacter][characterLineIndex];
            else characterBoxLine_3[characterIndex][characterLineIndex] = myCharacters[(int)myCharacter][characterLineIndex];            
        }
    }     
    for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
        clkPulseX2();
        for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
            for(uint8_t characterLinePixelsIndex = 0; characterLinePixelsIndex < 6; characterLinePixelsIndex++){
                rowsAtHUB75(characterLineIndex);  
                uint8_t lineOfPixels = characterBoxLine_3[characterIndex][characterLineIndex];
                if(((lineOfPixels >> characterLinePixelsIndex) & 0x01) == 0x01){
                    textColorSet(display_L);
                }
                else{
                    backgroundColorSet();    
                }                        
                clkPulse();
            }            
        }
        backgroundColorSet();
        clkPulseX2();
        strobe();
        gpio_set_level(D_ENA, 0);
        for(uint16_t delay = 0; delay < brightDelayNumber; delay++){}
        gpio_set_level(D_ENA, 1);
    }
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY ROW FOUR BUILD ROUTINE - FOR LARGE CHARACTERS  ======================================================================================================================
=======================================================================================================================================================================================================
*/

void runHub75Row4Start(char string[11], uint16_t brightDelayNumber){
    for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
        for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
            int myCharacter = (int)string[characterIndex];
            if(isCharacterSizeSmall == false) characterBoxLine_4[characterIndex][characterLineIndex] = myLargeCharacters[(int)myCharacter][characterLineIndex];
            else characterBoxLine_4[characterIndex][characterLineIndex] = myCharacters[(int)myCharacter][characterLineIndex];            
        }
    }      
    for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
        clkPulseX2();
        for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
            for(uint8_t characterLinePixelsIndex = 0; characterLinePixelsIndex < 6; characterLinePixelsIndex++){
                rowsAtHUB75(characterLineIndex + 8); 
                uint8_t lineOfPixels = characterBoxLine_4[characterIndex][characterLineIndex];
                if(((lineOfPixels >> characterLinePixelsIndex) & 0x01) == 0x01){
                    textColorSet(display_L);
                }
                else{
                    backgroundColorSet();    
                }                        
                clkPulse();
            }            
        }
        backgroundColorSet();
        clkPulseX2();
        strobe();
        gpio_set_level(D_ENA, 0);
        for(uint16_t delay = 0; delay < brightDelayNumber; delay++){}
        gpio_set_level(D_ENA, 1);
    }
}