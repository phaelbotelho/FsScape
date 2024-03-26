/* 
 * File:   fsscape.c
 * Author: raphael.pereira
 *
 * Created on January 26, 2024, 3:00 PM
 */


/*******************************************************************************
                               ### PRIVATE ###
*******************************************************************************/

/* ---------------------------# STD INCLUDES #------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* ---------------------------# MCC INCLUDES #------------------------------- */

/* --------------------------# LOCAL INCLUDES #------------------------------ */
#include "fsscape.h"
#include "my_i2c_pic18.h"
#include "crc32.h"
/* -------------------------------------------------------------------------- */


/* ------------------------# CONSTANTS AND MACROS #-------------------------- */
typedef enum
{
    I2C,
    SPI,
    SERIAL,
    PARALLEL,
}FsScape_interface_style_tag;
/* -------------------------------------------------------------------------- */


/* ------------------------------# TYPEDEFS #-------------------------------- */
/* -------------------------------------------------------------------------- */

/* --------------------------# LOCAL VARIABLES #----------------------------- */
uint8_t FsScape_i2c_SRAM_addr = 0;
uint8_t FsScape_i2c_EEPROM_addr = 0;
uint8_t FsScape_i2c_FLASH_addr = 0;

// This could not be alterated in code time.
const FsScape_interface_style_tag FsScape_SRAM_interface_style = I2C;
const FsScape_interface_style_tag FsScape_EEPROM_interface_style = I2C;
const FsScape_interface_style_tag FsScape_FLASH_interface_style = SPI;

fsscape_SRAM_index_addr_tag fsscape_SRAM_index_addr;
/* -------------------------------------------------------------------------- */


/* ----------------------------# PROTOTYPES #-------------------------------- */
// Interact with the SRAM
int16_t FsScape_get_index_SRAM(uint32_t *address);
int16_t FsScape_set_index_SRAM(uint32_t address_value);
int16_t FsScape_get_index_addr_SRAM();
int16_t FsScape_set_index_addr_SRAM(uint8_t address_value);
int16_t FsScape_get_index_crc_SRAM(uint32_t *crc);
int16_t FsScape_set_index_crc_SRAM(uint32_t crc_value);
uint32_t FsScape_check_index_crc(uint32_t crc_value);
uint32_t olameu_mundo(uint32_t crc_value);


// Interact with the EEPROM
int16_t FsScape_get_index_EEPROM(fsscape_Address_tag *address);
int16_t FsScape_set_index_EEPROM(fsscape_Address_tag address_value);
int16_t FsScape_get_index_addr_EEPROM(fsscape_Address_tag *address);
int16_t FsScape_set_index_addr_EEPROM(fsscape_Address_tag address_value);
// Interact with the FLASH
int16_t FsScape_get_index_FLASH(fsscape_Address_tag *address);
int16_t FsScape_set_index_FLASH(fsscape_Address_tag address_value);
int16_t FsScape_get_index_addr_FLASH(fsscape_Address_tag *address);
int16_t FsScape_set_index_addr_FLASH(fsscape_Address_tag address_value);
// Interact with the configured ways to save the index and return the index automatically.
int16_t FsScape_get_index_auto(fsscape_Address_tag *address);
//int16_t FsScape_set_index_auto(fsscape_Address_tag address_value);



#if 0
// Interact with the SRAM
uint8_t FsScape_i2c_config_SRAM(uint8_t *i2cmodule, uint8_t address);
uint8_t FsScape_get_i2c_addr_SRAM();
void FsScape_set_i2c_addr_SRAM(uint8_t address);
//uint8_t FsScape_get_spi_config_SRAM(uint8_t *i2cmodule, uint8_t *CS_PIN, uint8_t CS_PIN_BIT);
//void FsScape_set_spi_addr_SRAM(uint8_t *CS_PIN, uint8_t CS_PIN_BIT);

// Interact with the EEPROM
uint8_t FsScape_get_i2c_addr_EEPROM(uint8_t address);
void FsScape_set_i2c_addr_EEPROM(uint8_t address);
//void FsScape_set_spi_addr_EEPROM(uint8_t *CS_PIN, uint8_t CS_PIN_BIT);
// Interact with the FLASH
uint8_t FsScape_get_i2c_addr_FLASH(uint8_t address);
void FsScape_set_i2c_addr_FLASH(uint8_t address);
void FsScape_set_spi_addr_FLASH(uint8_t *CS_PIN, uint8_t CS_PIN_BIT);
#endif


/* -------------------------------------------------------------------------- */
//I2C_Mem_Write(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//I2C_Mem_Read(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

int16_t FsScape_get_index_SRAM(uint32_t *address)
{
    volatile uint32_t *data = address;
    int16_t value = 0;
    uint8_t _address[4];
    
    value = I2C_Mem_Read(FSSCAPE_SRAM_I2C_ADDR, FSSCAPE_SRAM_IDX_ADDR, 1, _address, 4, 0);
    
    if(value == I2C_OK)
    {
        // Calcula o �ndice usando os dados lidos
        *address = ((uint32_t)_address[3] << 24) | ((uint32_t)_address[2] << 16) | ((uint32_t)_address[1] << 8) | _address[0];
    }
    
    return value;    
}

int16_t FsScape_set_index_SRAM(uint32_t address_value)
{
    uint8_t _address[4];
    
    _address[0] = (uint8_t)(address_value);
    _address[1] = (uint8_t)(address_value >> 8);
    _address[2] = (uint8_t)(address_value >> 16);
    _address[3] = (uint8_t)(address_value >> 24);
    
    return I2C_Mem_Write(FSSCAPE_SRAM_I2C_ADDR, FSSCAPE_SRAM_IDX_ADDR, 1, _address, 4, 0);
}

int16_t FsScape_get_index_addr_SRAM()
{
    
}

int16_t FsScape_set_index_addr_SRAM(uint8_t address_value)
{
    
}

int16_t FsScape_get_index_crc_SRAM(uint32_t *crc)
{
    volatile uint32_t *data = crc;
    int16_t value = 0;
    uint8_t _address[4];
    
    value = I2C_Mem_Read(FSSCAPE_SRAM_I2C_ADDR, FSSCAPE_SRAM_IDX_CHK_ADDR, 1, _address, 4, 0);
    
    if(value == I2C_OK)
    {
        // Calcula o �ndice usando os dados lidos
        *crc = ((uint32_t)_address[3] << 24) | ((uint32_t)_address[2] << 16) | ((uint32_t)_address[1] << 8) | _address[0];
    }
    
    return value;   
}

int16_t FsScape_set_index_crc_SRAM(uint32_t crc_value)
{
    uint8_t _address[4];
    
    _address[0] = (uint8_t)(crc_value);
    _address[1] = (uint8_t)(crc_value >> 8);
    _address[2] = (uint8_t)(crc_value >> 16);
    _address[3] = (uint8_t)(crc_value >> 24);
    
    return I2C_Mem_Write(FSSCAPE_SRAM_I2C_ADDR, FSSCAPE_SRAM_IDX_CHK_ADDR, 1, _address, 4, 0);
}

uint32_t FsScape_check_index_crc(uint32_t crc_value)
{
    uint8_t _address[4];
    volatile uint32_t crc_computed;
    
    _address[3] = (uint8_t)(crc_value);
    _address[2] = (uint8_t)(crc_value >> 8);
    _address[1] = (uint8_t)(crc_value >> 16);
    _address[0] = (uint8_t)(crc_value >> 24);
    
    crc_computed = calculate_crc32_buffer(_address, 4);
    
    return crc_computed;
}
