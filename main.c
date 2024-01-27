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

#include "millis.h"
#include "at45dbxx.h"
#include "my_i2c_pic18.h"
#include "fsscape.h"


extern AT45dbxx_t AT45dbxx;
WAT45DBID_t myi_AT45dbxx;

/*
                         Main application
 */
void main(void)
{
    uint8_t valorestx[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    uint8_t valoresrx[254] = {0};
    volatile uint8_t valor = 0;
    volatile uint8_t valor2 = 0;
    
    // Initialize the device
    SYSTEM_Initialize();
    FLASH_CS_SetHigh();
    
    TMR1_SetInterruptHandler(increment_interrupt);
    //INT0_SetInterruptHandler();
    //INT1_SetInterruptHandler(Sleep_pic);
    
    RCONbits.SBOREN = 0;
    
    SPI1_Open(SPI1_DEFAULT);
    
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
    
    oldtime = millis();
    oldtime = millis();
    oldtime = millis();
    
    valor = AT45dbxx_Init();
    
    valor = AT45dbxx_ReadPage(valoresrx, 25, 0);
    
    valor = AT45dbxx_EraseChip();
    
    valor = AT45dbxx_ReadPage(valoresrx, 25, 0);
    
    valor = AT45dbxx_WritePage(valorestx, 9, 0);
    
    valor = AT45dbxx_ReadPage(valoresrx, 25, 0);
    
    //AT45dbxx_ChangePagesize(PAGESIZE_264BYTES);
    valor = AT45dbxx_Init();
    
    NOP();
    
    while(1)
    {
        
    }
}
/**
 End of File
*/