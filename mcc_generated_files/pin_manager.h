/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F26K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set FLASH_CS aliases
#define FLASH_CS_TRIS                 TRISCbits.TRISC0
#define FLASH_CS_LAT                  LATCbits.LATC0
#define FLASH_CS_PORT                 PORTCbits.RC0
#define FLASH_CS_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define FLASH_CS_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define FLASH_CS_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define FLASH_CS_GetValue()           PORTCbits.RC0
#define FLASH_CS_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define FLASH_CS_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set FLASH_RST aliases
#define FLASH_RST_TRIS                 TRISCbits.TRISC2
#define FLASH_RST_LAT                  LATCbits.LATC2
#define FLASH_RST_PORT                 PORTCbits.RC2
#define FLASH_RST_ANS                  ANSELCbits.ANSC2
#define FLASH_RST_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define FLASH_RST_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define FLASH_RST_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define FLASH_RST_GetValue()           PORTCbits.RC2
#define FLASH_RST_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define FLASH_RST_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define FLASH_RST_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define FLASH_RST_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set I2C_SCL aliases
#define I2C_SCL_TRIS                 TRISCbits.TRISC3
#define I2C_SCL_LAT                  LATCbits.LATC3
#define I2C_SCL_PORT                 PORTCbits.RC3
#define I2C_SCL_ANS                  ANSELCbits.ANSC3
#define I2C_SCL_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define I2C_SCL_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define I2C_SCL_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define I2C_SCL_GetValue()           PORTCbits.RC3
#define I2C_SCL_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define I2C_SCL_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define I2C_SCL_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define I2C_SCL_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set I2C_SDA aliases
#define I2C_SDA_TRIS                 TRISCbits.TRISC4
#define I2C_SDA_LAT                  LATCbits.LATC4
#define I2C_SDA_PORT                 PORTCbits.RC4
#define I2C_SDA_ANS                  ANSELCbits.ANSC4
#define I2C_SDA_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define I2C_SDA_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define I2C_SDA_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define I2C_SDA_GetValue()           PORTCbits.RC4
#define I2C_SDA_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define I2C_SDA_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define I2C_SDA_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define I2C_SDA_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/