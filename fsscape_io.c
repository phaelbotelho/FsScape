/* 
 * File:   fsscape_io.c
 * Author: raphael.pereira
 *
 * Created on January 26, 2024, 4:36 PM
 */


/*******************************************************************************
                               ### PRIVATE ###
*******************************************************************************/

/* ---------------------------# STD INCLUDES #------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/* ---------------------------# MCC INCLUDES #------------------------------- */
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/interrupt_manager.h"
/* --------------------------# LOCAL INCLUDES #------------------------------ */
#include "fsscape_io.h"
#include "my_i2c_pic18.h"
/* -------------------------------------------------------------------------- */


/* ------------------------# CONSTANTS AND MACROS #-------------------------- */
/* -------------------------------------------------------------------------- */


/* ------------------------------# TYPEDEFS #-------------------------------- */
/* -------------------------------------------------------------------------- */


/* ----------------------------# PROTOTYPES #-------------------------------- */
int16_t FsScape_get_index_fromSRAM(uint32_t *address);

void FsScape_Delay(uint32_t time)
{
    //__delay_ms(time);
}

void FsScape_ConfigureCS(uint16_t *CS_pin, uint16_t *CS_pin_bit)
{
    
}

void FsScape_csLOW(void)
{
    //FsScape_CS = 0;
}

void FsScape_csHIGH(void)
{
    //FsScape_CS = 1;
}

void FsScape_SPI_Write(uint8_t *data, uint8_t len)
{
    //HAL_SPI_Transmit(&W25Q_SPI, data, len, 2000);
}

void FsScape_SPI_Read(uint8_t *data, uint32_t len)
{
    //HAL_SPI_Receive(&W25Q_SPI, data, len, 5000);
}

/* -------------------------------------------------------------------------- */