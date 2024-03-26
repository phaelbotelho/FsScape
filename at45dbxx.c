/* 
 * File:   at45dbxx.h
 * Author: Raphael
 *
 * Created on January 11, 2024, 9:23 PM
 */

#include "main.h"

#include <stdint.h>
#include <stdbool.h>

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/spi2.h"

#include "at45dbxx.h"
#include "millis.h"


//#include "my_spi.h" // Contains a modified version of spi exchange that can work with uint32_t.

// Ported from: https://github.com/nimaltd/45dbxxx/blob/master/45dbxx.c
// Referred in: https://github.com/nimaltd/45dbxxx/blob/master/45dbxx.c
//              https://github.com/zootboy/micro/blob/master/stm32/lcd_test/stm32radio-read-only/stm32radio_examples/examples/5_media_ogg/at45dbxx.c
//              https://github.com/zootboy/micro/blob/master/stm32/lcd_test/stm32radio-read-only/stm32radio_examples/examples/5_media_ogg/at45dbxx.h
//              https://github.com/coocox/cox/blob/master/CoX/Driver/Memory_Flash_Atmel/AT45DB161/AT45DB161_Single/doc/txt/AT45DB161_single.c
//              https://github.com/nimaltd/45dbxxx
//              https://github.com/Omnisense/AT45DB/blob/master/AT45DB.h
//              https://github.com/projectara/flashrom/blob/master/at45db.c
//              https://github.com/grepz/STM32_bl/tree/master
//              https://github.com/grepz/STM32_bl/blob/master/at45db.c


//################################################################################################################
//################################################################################################################

// If any memory was defined define a 4Mb memory as standard.

#if defined(AT45DB021E) || defined(AT45DB041E) || defined(AT45DB081E) || \
    defined(AT45DB161E) || defined(AT45DB321E) || defined(AT45DB641E)
#else
    #define AT45DB041E // 4Mb of memory.
#endif

#if !defined(PAGESIZE_256_BYTES) || !defined(PAGESIZE_264_BYTES)
#define PAGESIZE_256_BYTES
#endif


/*
#define numBLOCK 256 // Total of blocks for a 4Mb
#define numSECTORS 8 // Total sectors per block
#define numPAGES 2048 // Total pages per sector
#define numBYTES 256 // Totral bytes per page.
#define numSECTORSIZE 4096
*/

//################################################################################################################
//################################################################################################################

AT45dbxx_t AT45dbxx;

//################################################################################################################
//################################################################################################################

bool AT45dbxx_Init(void);
void AT45DB_Reset(void);
void AT45DB_ReadID(WAT45DBID_t *my_AT45dbxx);
uint8_t AT45dbxx_ReadStatus(void);
uint8_t AT45dbxx_WaitBusy(void);
void AT45dbxx_Resume(void);
void AT45dbxx_PowerDown(void);
uint8_t AT45dbxx_EraseChip(void);
uint8_t AT45dbxx_ErasePage(uint16_t page);
uint8_t AT45dbxx_WritePage(uint8_t *Data, uint16_t len, uint16_t page);
uint8_t AT45dbxx_ReadPage(uint8_t* Data, uint16_t len, uint16_t page);

void AT45dbxx_Read(uint32_t startPage, uint8_t offset, uint32_t size, uint8_t *rData);
void AT45dbxx_Write(uint32_t page, uint16_t offset, uint32_t size, uint8_t *data);
void AT45dbxx_FastRead(uint32_t startPage, uint8_t offset, uint32_t size, uint8_t *rData);

uint8_t AT45dbxx_ChangePagesize(uint8_t _pagesize);

//################################################################################################################
//################################################################################################################

void AT45DB_Reset(void)
{
    uint8_t tData[4];
    tData[0] = AT45DB_SOFT_RESET; // Send the command to enable Reset
    tData[1] = 0x00; // Send the command to Reset
    tData[2] = 0x00; // Send the command to Reset
    tData[3] = 0x00; // Send the command to Reset

    FLASH_CS_SetLow();
    SPI2_WriteBlock(tData, 4); // Just send data.
    __delay_ms(1);
    FLASH_CS_SetHigh();
}
//################################################################################################################

/* Need to be corrected
 * void AT45DB_ReadID(WAT45DBID_t *my_AT45dbxx)
{
    volatile uint8_t rData[5];
    
    FLASH_CS_SetLow();
    rData[0] = SPI2_ExchangeByte(AT45DB_RDDEVID); // Send the command to Read JEDEC ID
    SPI2_ReadBlock(rData, 5); // Just receive data.
    FLASH_CS_SetHigh();
    
    my_AT45dbxx->jedecID = ((uint32_t)(rData[3]) << 24 |(uint32_t)(rData[2]) << 16 | (uint32_t)(rData[1]) << 8 | (uint32_t)(rData[0]));
                    // MFN ID          :            MEM ID         :            CAPACITY ID           :        dummy
}*/
//################################################################################################################

uint8_t AT45dbxx_ReadStatus(void)
{
    uint8_t status = 0;
    FLASH_CS_SetLow();
    status = SPI2_ExchangeByte(0xd7);
    status = SPI2_ExchangeByte(0x00);
    FLASH_CS_SetHigh();
    return status;
}
//################################################################################################################

uint8_t AT45dbxx_WaitBusy(void)
{
    uint8_t status;
    uint16_t timeout = 0;
    FLASH_CS_SetLow();
    status = SPI2_ExchangeByte(0xd7);
    status = SPI2_ExchangeByte(0x00);
    FLASH_CS_SetHigh();
    
    while(((status & 0x80) == 0))
    {
        __delay_ms(1);
        FLASH_CS_SetLow();
        status = SPI2_ExchangeByte(0xd7);
        status = SPI2_ExchangeByte(0x00);
        FLASH_CS_SetHigh();
        timeout++;
        
        if(timeout > AT45dbxx_WAIT_TIMEOUT)
        {
            return true;
        }
    }
    
    return false;
}
//################################################################################################################

void AT45dbxx_Resume(void)
{
    FLASH_CS_SetLow();
    SPI2_WriteByte(AT45DB_RESUME);
    FLASH_CS_SetHigh();
}
//################################################################################################################

void AT45dbxx_PowerDown(void)
{
    FLASH_CS_SetLow();
    SPI2_WriteByte(AT45DB_PWRDOWN);
    FLASH_CS_SetHigh();
}
//################################################################################################################

bool AT45dbxx_Init(void)
{
    FLASH_CS_SetHigh();
    
    FLASH_RST_SetLow();
    __delay_ms(5);
    FLASH_RST_SetHigh();
    __delay_ms(5);

    uint8_t Temp0 = 0, Temp1 = 0, Temp2 = 0;
    
#if defined(PAGESIZE_256_BYTES)
    //AT45dbxx_ChangePagesize(PAGESIZE_256BYTES); // Configure the page and the buffer to 256 bytes.
#endif
    
    FLASH_CS_SetLow();
    Temp0 = SPI2_ExchangeByte(AT45DB_RDDEVID); // Dummy read.
    Temp0 = SPI2_ExchangeByte(0xa5);
    Temp1 = SPI2_ExchangeByte(0xa5);
    FLASH_CS_SetHigh();

    Temp2 = AT45dbxx_ReadStatus();

    if(Temp0 == 0x1F)
    {
        switch(Temp1 & 0x1F)
        {
            case 0x03: //	AT45db021
                AT45dbxx.FlashSize_MBit = 2;
                AT45dbxx.Pages = 1024;
                if(Temp2 & 0x01)
                {
                    AT45dbxx.Shift = 0;
                    AT45dbxx.PageSize = 256;
                } else
                {
                    AT45dbxx.Shift = 9;
                    AT45dbxx.PageSize = 264;
                }
                break;
            case 0x04: //	AT45db041
                AT45dbxx.FlashSize_MBit = 4;
                AT45dbxx.Pages = 2048;
                if(Temp2 & 0x01)
                {
                    AT45dbxx.Shift = 0;
                    AT45dbxx.PageSize = 256;
                } else
                {
                    AT45dbxx.Shift = 9;
                    AT45dbxx.PageSize = 264;
                }
                break;
            case 0x05: //	AT45db081
                AT45dbxx.FlashSize_MBit = 8;
                AT45dbxx.Pages = 4096;
                if(Temp2 & 0x01)
                {
                    AT45dbxx.Shift = 0;
                    AT45dbxx.PageSize = 256;
                } else
                {
                    AT45dbxx.Shift = 9;
                    AT45dbxx.PageSize = 264;
                }
                break;
            case 0x06: //	AT45db161
                AT45dbxx.FlashSize_MBit = 16;
                AT45dbxx.Pages = 4096;
                if(Temp2 & 0x01)
                {
                    AT45dbxx.Shift = 0;
                    AT45dbxx.PageSize = 512;
                } else
                {
                    AT45dbxx.Shift = 10;
                    AT45dbxx.PageSize = 528;
                }
                break;
            case 0x07: //	AT45db321
                AT45dbxx.FlashSize_MBit = 32;
                AT45dbxx.Pages = 8192;
                if(Temp2 & 0x01)
                {
                    AT45dbxx.Shift = 0;
                    AT45dbxx.PageSize = 512;
                } else
                {
                    AT45dbxx.Shift = 10;
                    AT45dbxx.PageSize = 528;
                }
                break;
            case 0x08: //	AT45db641
                AT45dbxx.FlashSize_MBit = 64;
                AT45dbxx.Pages = 8192;
                if(Temp2 & 0x01)
                {
                    AT45dbxx.Shift = 0;
                    AT45dbxx.PageSize = 1024;
                } else
                {
                    AT45dbxx.Shift = 11;
                    AT45dbxx.PageSize = 1056;
                }
                break;
        }

        return false;
    }
    else
    {
        return true;
    }
}
//################################################################################################################

uint8_t AT45dbxx_EraseChip(void)
{
    //AT45dbxx_Resume();
    
    if(AT45dbxx_WaitBusy())
    {
        return true;
    }
    
    FLASH_CS_SetLow();
    SPI2_ExchangeByte(0xc7);
    SPI2_ExchangeByte(0x94);
    SPI2_ExchangeByte(0x80);
    SPI2_ExchangeByte(0x9a);
    FLASH_CS_SetHigh();
    
    if(AT45dbxx_WaitBusy())
    {
        return true;
    }
    
    return false;
}
//################################################################################################################

uint8_t AT45dbxx_ErasePage(uint16_t page)
{
    page = page << AT45dbxx.Shift;

    //AT45dbxx_Resume();
    
    if(AT45dbxx_WaitBusy())
    {
        return true;
    }

    FLASH_CS_SetLow();
    SPI2_ExchangeByte(AT45DB_PGERASE);
    SPI2_ExchangeByte((page >> 16) & 0xff);
    SPI2_ExchangeByte((page >> 8) & 0xff);
    SPI2_ExchangeByte(page & 0xff);
    FLASH_CS_SetHigh();

    if(AT45dbxx_WaitBusy())
    {
        return true;
    }
    
    return false;
}
//################################################################################################################

uint8_t AT45dbxx_WritePage(uint8_t *Data, uint16_t len, uint16_t page)
{
    page = page << AT45dbxx.Shift;
    
    //AT45dbxx_Resume();
    
    if(AT45dbxx_WaitBusy())
    {
        return true;
    } 
    
    FLASH_CS_SetLow();
    SPI2_ExchangeByte(AT45DB_MNTHRUBF1);
    SPI2_ExchangeByte((page >> 16) & 0xff);
    SPI2_ExchangeByte((page >> 8) & 0xff);
    SPI2_ExchangeByte(page & 0xff);
    SPI2_ExchangeBlock(Data, len);
    FLASH_CS_SetHigh();
    
    if(AT45dbxx_WaitBusy())
    {
        return true;
    }
    
    return false;
}
//################################################################################################################

uint8_t AT45dbxx_ReadPage(uint8_t* Data, uint16_t len, uint16_t page)
{
    page = page << AT45dbxx.Shift;
    
    if(len > AT45dbxx.PageSize)
    {
        len = AT45dbxx.PageSize;
    }
    
    //AT45dbxx_Resume();
    
    if(AT45dbxx_WaitBusy())
    {
        return true;
    }
    
    FLASH_CS_SetLow();
    SPI2_ExchangeByte(AT45DB_RDARRAYHF);
    SPI2_ExchangeByte((page >> 16) & 0xff);
    SPI2_ExchangeByte((page >> 8) & 0xff);
    SPI2_ExchangeByte(page & 0xff);
    SPI2_ExchangeByte(0);
    SPI2_ExchangeBlock(Data, len);
    FLASH_CS_SetHigh();
    
    return false;
}
//################################################################################################################

void AT45dbxx_Read(uint32_t startPage, uint8_t offset, uint32_t size, uint8_t *rData)
{
    
    
}
//################################################################################################################

void AT45dbxx_Write(uint32_t page, uint16_t offset, uint32_t size, uint8_t *data)
{
    
    
}
//################################################################################################################

void AT45dbxx_FastRead(uint32_t startPage, uint8_t offset, uint32_t size, uint8_t *rData)
{
    
    
}
//################################################################################################################

uint8_t AT45dbxx_ChangePagesize(uint8_t _pagesize)
{
    uint8_t tData[4];
    tData[0] = 0x3D; // Send the command to enable Reset
    tData[1] = 0x2A; // Send the command to Reset
    tData[2] = 0x80; // Send the command to Reset
    tData[3] = _pagesize; // Send the command to Reset

    FLASH_CS_SetLow();
    SPI2_WriteBlock(tData, 4); // Just send data.
    FLASH_CS_SetHigh();
}
//################################################################################################################