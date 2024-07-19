#include "general_data_header.h"

uint8_t colors;
uint16_t ENATime;

/*
=======================================================================================================================================================================================================
========================  DISPLAY UPPDATE LOOP  =======================================================================================================================================================
=======================================================================================================================================================================================================
*/

void runHub75(void){
    while(true){
        runHub75Row1();
        runHub75Row2();
        runHub75Row3();
        runHub75Row4();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY ROW ONE ROUTINE  ====================================================================================================================================================
=======================================================================================================================================================================================================
*/

void runHub75Row1(void){
    for(uint8_t characterLineIndex = 0; characterLineIndex < 8; characterLineIndex++){
        clkPulseX2();
        for(uint8_t characterIndex = 0; characterIndex < 10; characterIndex++){
            for(uint8_t characterLinePixelsIndex = 0; characterLinePixelsIndex < 6; characterLinePixelsIndex++){
                rowsAtHUB75(characterLineIndex);
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
        HUB75_ENATime();
    }
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY ROW TWO ROUTINE  ====================================================================================================================================================
=======================================================================================================================================================================================================
*/

void runHub75Row2(void){
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
        HUB75_ENATime();
    }
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY ROW THREE ROUTINE  ==================================================================================================================================================
=======================================================================================================================================================================================================
*/

void runHub75Row3(void){
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
        HUB75_ENATime();
    }
}

/*
=======================================================================================================================================================================================================
========================  DISPLAY ROW FOUR ROUTINE  ===================================================================================================================================================
=======================================================================================================================================================================================================
*/

void runHub75Row4(void){
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
        HUB75_ENATime();
    }
}    
