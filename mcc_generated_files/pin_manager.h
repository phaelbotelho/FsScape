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

// get/set SPI2_SCK aliases
#define SPI2_SCK_TRIS                 TRISBbits.TRISB1
#define SPI2_SCK_LAT                  LATBbits.LATB1
#define SPI2_SCK_PORT                 PORTBbits.RB1
#define SPI2_SCK_WPU                  WPUBbits.WPUB1
#define SPI2_SCK_ANS                  ANSELBbits.ANSB1
#define SPI2_SCK_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define SPI2_SCK_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define SPI2_SCK_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define SPI2_SCK_GetValue()           PORTBbits.RB1
#define SPI2_SCK_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define SPI2_SCK_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define SPI2_SCK_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define SPI2_SCK_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define SPI2_SCK_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define SPI2_SCK_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set SPI2_MISO aliases
#define SPI2_MISO_TRIS                 TRISBbits.TRISB2
#define SPI2_MISO_LAT                  LATBbits.LATB2
#define SPI2_MISO_PORT                 PORTBbits.RB2
#define SPI2_MISO_WPU                  WPUBbits.WPUB2
#define SPI2_MISO_ANS                  ANSELBbits.ANSB2
#define SPI2_MISO_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define SPI2_MISO_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define SPI2_MISO_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define SPI2_MISO_GetValue()           PORTBbits.RB2
#define SPI2_MISO_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define SPI2_MISO_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define SPI2_MISO_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define SPI2_MISO_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define SPI2_MISO_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define SPI2_MISO_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set SPI2_MOSI aliases
#define SPI2_MOSI_TRIS                 TRISBbits.TRISB3
#define SPI2_MOSI_LAT                  LATBbits.LATB3
#define SPI2_MOSI_PORT                 PORTBbits.RB3
#define SPI2_MOSI_WPU                  WPUBbits.WPUB3
#define SPI2_MOSI_ANS                  ANSELBbits.ANSB3
#define SPI2_MOSI_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define SPI2_MOSI_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define SPI2_MOSI_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define SPI2_MOSI_GetValue()           PORTBbits.RB3
#define SPI2_MOSI_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define SPI2_MOSI_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define SPI2_MOSI_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define SPI2_MOSI_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define SPI2_MOSI_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define SPI2_MOSI_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set FLASH_RST aliases
#define FLASH_RST_TRIS                 TRISBbits.TRISB4
#define FLASH_RST_LAT                  LATBbits.LATB4
#define FLASH_RST_PORT                 PORTBbits.RB4
#define FLASH_RST_WPU                  WPUBbits.WPUB4
#define FLASH_RST_ANS                  ANSELBbits.ANSB4
#define FLASH_RST_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define FLASH_RST_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define FLASH_RST_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define FLASH_RST_GetValue()           PORTBbits.RB4
#define FLASH_RST_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define FLASH_RST_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define FLASH_RST_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define FLASH_RST_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define FLASH_RST_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define FLASH_RST_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set FLASH_CS aliases
#define FLASH_CS_TRIS                 TRISBbits.TRISB5
#define FLASH_CS_LAT                  LATBbits.LATB5
#define FLASH_CS_PORT                 PORTBbits.RB5
#define FLASH_CS_WPU                  WPUBbits.WPUB5
#define FLASH_CS_ANS                  ANSELBbits.ANSB5
#define FLASH_CS_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define FLASH_CS_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define FLASH_CS_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define FLASH_CS_GetValue()           PORTBbits.RB5
#define FLASH_CS_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define FLASH_CS_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define FLASH_CS_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define FLASH_CS_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define FLASH_CS_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define FLASH_CS_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set I2C1_SCL aliases
#define I2C1_SCL_TRIS                 TRISCbits.TRISC3
#define I2C1_SCL_LAT                  LATCbits.LATC3
#define I2C1_SCL_PORT                 PORTCbits.RC3
#define I2C1_SCL_ANS                  ANSELCbits.ANSC3
#define I2C1_SCL_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define I2C1_SCL_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define I2C1_SCL_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define I2C1_SCL_GetValue()           PORTCbits.RC3
#define I2C1_SCL_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define I2C1_SCL_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define I2C1_SCL_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define I2C1_SCL_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set I2C1_SDA aliases
#define I2C1_SDA_TRIS                 TRISCbits.TRISC4
#define I2C1_SDA_LAT                  LATCbits.LATC4
#define I2C1_SDA_PORT                 PORTCbits.RC4
#define I2C1_SDA_ANS                  ANSELCbits.ANSC4
#define I2C1_SDA_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define I2C1_SDA_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define I2C1_SDA_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define I2C1_SDA_GetValue()           PORTCbits.RC4
#define I2C1_SDA_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define I2C1_SDA_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define I2C1_SDA_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define I2C1_SDA_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

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