#include "general_data_header.h"

int16_t ADC_Average[45];

/*
=======================================================================================================================================================================================================
========================  SPI RETREIVING LOOP  ========================================================================================================================================================
=======================================================================================================================================================================================================
*/

void runSPI_Loop(void){
    
	uint8_t ADC_NumberOfAverages;

    //Configuration for the SPI bus
    spi_bus_config_t buscfg={
        .mosi_io_num=GPIO_MOSI,
        .miso_io_num=GPIO_MISO,
        .sclk_io_num=GPIO_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    //Configuration for the SPI slave interface
    spi_slave_interface_config_t slvcfg={
        .mode=1,
        .spics_io_num=GPIO_CS,
        .queue_size=3,
        .flags=0,
    };        
    spi_slave_initialize(SPI2_HOST, &buscfg, &slvcfg, SPI_DMA_DISABLED);//SPI_DMA_CH_AUTO);

    char recvbuf[65]="";
    memset(recvbuf, 0, 64);
    spi_slave_transaction_t t;
    memset(&t, 0, sizeof(t));
    
    while(true) {
        t.length=64*8;
        t.rx_buffer=recvbuf;
        spi_slave_transmit(SPI2_HOST, &t, portMAX_DELAY);
        strcpy(myTotalString, recvbuf);
        char LED_D_Data[8][11];
        initLED_D_Data(LED_D_Data);
        splitLED_D_DataItemschar(LED_D_Data);
        fillOutWithSpoace(LED_D_Data);
        ADC_NumberOfAverages = calculateNumberOfLumAVG(LED_D_Data);         
        ADC_Average[0] = ADC_LightSensor();
        if(ADC_Average[0] < 0) ADC_Average[0] = 0;
        moveAverageElements(ADC_NumberOfAverages);
        ENATime = calculateAverage(ADC_NumberOfAverages);
        // calculate_ftENATime();
        // printf("ADC_NumberOfAverages; %d\r\n", ADC_NumberOfAverages);
        // printf("ADC_Average[0]: %d \r\n", ADC_Average[0]);
        // printf("ENATime: %d \r\n", ENATime);
        if((LED_D_Data[LED_D_SOT][0] == SOT) && (LED_D_Data[LED_D_EOT][0] == EOT)){
            HUB75_ColorData(LED_D_Data);
            HUB75_Block1_Print(LED_D_Data);
            HUB75_Block2_Print(LED_D_Data);
            HUB75_Block3_Print(LED_D_Data);
            HUB75_Block4_Print(LED_D_Data);
        }
    }    
}
