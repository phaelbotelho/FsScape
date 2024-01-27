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
/* -------------------------------------------------------------------------- */


/* ----------------------------# PROTOTYPES #-------------------------------- */
// Interact with the SRAM
int16_t FsScape_get_index_SRAM(fsscape_Address_tag *address);
int16_t FsScape_set_index_SRAM(fsscape_Address_tag address_value);
int16_t FsScape_get_index_addr_SRAM(fsscape_Address_tag *address);
int16_t FsScape_set_index_addr_SRAM(fsscape_Address_tag address_value);
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
int16_t FsScape_set_index_auto(fsscape_Address_tag address_value);




// Interact with the SRAM
uint8_t FsScape_i2c_config_SRAM(uint8_t *i2cmodule, uint8_t address);
uint8_t FsScape_get_i2c_addr_SRAM();
void FsScape_set_i2c_addr_SRAM(uint8_t address);
uint8_t FsScape_get_spi_config_SRAM(uint8_t *i2cmodule, uint8_t *CS_PIN, uint8_t CS_PIN_BIT);
void FsScape_set_spi_addr_SRAM(uint8_t *CS_PIN, uint8_t CS_PIN_BIT);

// Interact with the EEPROM
uint8_t FsScape_get_i2c_addr_EEPROM(uint8_t address);
void FsScape_set_i2c_addr_EEPROM(uint8_t address);
void FsScape_set_spi_addr_EEPROM(uint8_t *CS_PIN, uint8_t CS_PIN_BIT);
// Interact with the FLASH
uint8_t FsScape_get_i2c_addr_FLASH(uint8_t address);
void FsScape_set_i2c_addr_FLASH(uint8_t address);
void FsScape_set_spi_addr_FLASH(uint8_t *CS_PIN, uint8_t CS_PIN_BIT);



/* -------------------------------------------------------------------------- */


