/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F26K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/spi1.h"

#include "millis.h"
#include "at45dbxx.h"
#include "my_i2c_pic18.h"
#include "fsscape.h"


extern AT45dbxx_t AT45dbxx; // Global memory access
WAT45DBID_t myi_AT45dbxx; // 

/*
                         Main application
 */
void main(void)
{
    //uint8_t valorestx[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char valorestx[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
    uint8_t valoresrx[254] = {0};
    volatile uint8_t valor = 0;
    volatile uint8_t valor2 = 0;
    volatile int16_t bus_reset;
    volatile uint8_t temp = 0;
    volatile uint8_t temp2 = 0;
    
    // Initialize the device
    SYSTEM_Initialize();
    FLASH_CS_SetHigh();
    
    TMR1_SetInterruptHandler(increment_interrupt);
    //INT0_SetInterruptHandler();
    //INT1_SetInterruptHandler(Sleep_pic);
    
    RCONbits.SBOREN = 0;
    
    //SPI1_Open(SPI1_DEFAULT);
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    uint32_t oldtime;
    fsscape_SRAM_index_addr_tag endereco_atual;
    
    endereco_atual.ui32addr = 0;
    uint8_t teste[4];
    uint32_t adressme = 0;
    
    oldtime = millis();
    
    printf("Sistema Iniciado\n");
    
#if 0
    I2C_HWini();
    I2C_ModuleStart(400000UL); // Init I2C module with 100kHz.
    bus_reset = I2C2_M_BusReset();
    printf("Init i2c bus_reset: %i\n", bus_reset);
    
    
    if(I2C2_M_Poll(FSSCAPE_SRAM_I2C_ADDR) == I2C_ACK)
    {
        printf("O sistema identificou a memoria SRAM!!!\n");
    }
    else
    {
        printf("Ha algo de errado com a memoria SRAM!!!\n");
    }
    
    
    
    //I2C2_M_Write_Single(0xDE, 0x20, 1);
    /*I2C2_M_Read_Single(0xDE, 0x20, &valor2);
    printf("Valor do Endereco 0x20: %i\n", valor2);
    //I2C2_M_Write_Single(0xDE, 0x21, 2);
    I2C2_M_Read_Single(0xDE, 0x21, &valor2);
    printf("Valor do Endereco 0x21: %i\n", valor2);
    //I2C2_M_Write_Single(0xDE, 0x22, 3);
    I2C2_M_Read_Single(0xDE, 0x22, &valor2);
    printf("Valor do Endereco 0x22: %i\n", valor2);
    //I2C2_M_Write_Single(0xDE, 0x23, 4);
    I2C2_M_Read_Single(0xDE, 0x23, &valor2);
    printf("Valor do Endereco 0x23: %i\n", valor2);*/
    
    
    printf("Verificando o ponteiro de enderecamento...\n");
    FsScape_get_index_SRAM(&adressme);
    printf("O ponteiro encontrado foi: %lu\n", adressme);
    
    printf("Alterando o endereço para: 0x12345678\n");
    adressme = 0x12345678;
    FsScape_set_index_SRAM(adressme);
    
    
    printf("Verificando o novo ponteiro\n");
    FsScape_get_index_SRAM(&adressme);
    printf("O ponteiro encontrado foi: 0x%lX\n", adressme);
    
    I2C_ModuleStop();
#endif
    
#if 1
    
    char aux[30] = {0};
    char oi[30] = {"ola mundo"};
    
    SPI2_Initialize();
    SPI2_Open(SPI1_DEFAULT);
    
    valor = AT45dbxx_Init();
    
    printf("Memory Found with JEDECID: Total size:%iMbit, Page size: %iBytes, N. pages: %i, Shift: %i\n", AT45dbxx.FlashSize_MBit, AT45dbxx.PageSize, AT45dbxx.Pages, AT45dbxx.Shift);
    
    //valor = AT45dbxx_EraseChip();
    //valor = AT45dbxx_EraseChip();
    //valor = AT45dbxx_EraseChip();
    //valor = AT45dbxx_WritePage(valorestx, 11, 0);
    valor = AT45dbxx_ReadPage(valoresrx, 11, 0);
    
    sprintf(aux, "%s", valoresrx);
    
    printf("Leitura de buffer: %s\n", aux);
    printf("Fim do programa");
#endif
    
    while(1)
    {
        
    }
}
/**
 End of File
*/