/* 
 * File:   fsscape.h
 * Author: raphael.pereira
 *
 * Created on January 26, 2024, 3:00 PM
 */

#ifndef FSSCAPE_H
#define	FSSCAPE_H

#ifdef	__cplusplus
extern "C" {
#endif

/* ------------------------------# INCLUDES #-------------------------------- */
#include <stdint.h>
/* -------------------------------------------------------------------------- */

/* ------------------------# CONSTANTS AND MACROS #-------------------------- */

// ************************************
// Start JEDEC ID definitions
// ************************************
// Flash manufacturers
#define ADESTO_ID     0x1F
#define ST_ID         0x20
#define WINBOND_ID    0xEF
#define SPANSION_ID   0x01
#define SHARP_ID      0xB0
#define SANYO_ID      0x62
#define MACRONIX_ID   0xC2
#define INTEL_ID      0x89
#define GIGADEVICE_ID 0xC8
#define FUJITSU_ID    0x04
#define ALLIANCE_ID   0x52
    
// Flash type JEDEC ID
//#define 

// Flash size JEDEC ID
//#define 

// ************************************
// End JEDEC ID definitions
// ************************************


    
/* -------------------------------------------------------------------------- */

/* ------------------------------# TYPEDEFS #-------------------------------- */
// This typedef allow to access the flash memory in two different ways.
// The classic method of page address and an offset.
// And the direct position address.
// The long address can accept memories with maximum of 4,294,967,295 bytes.
// Equivalent to 4.29 GBytes, more than enough for that application.
typedef struct
{
    uint32_t ui32long_address;  // long address can accept memories of 4.29 GBytes.
    uint32_t ui8Page;       // Can handle device with 4,294,967,295 pages.
    uint16_t ui8ByteOffset; // To accept pages with size other than 256/264 bytes.
}fsscape_Address_tag;

// Struct to access the characteristics of the detected memory.
typedef struct
{
	uint8_t		ui8FlashSize_MBit;	
	uint16_t	ui16PageSize;
	uint16_t	ui16Pages;
	uint8_t		ui8Shift;
}fsscape_MemoryStyle_tag;

// Struct to access the memory JEDEC ID.
typedef union {
    struct {
        uint8_t ui8flashSize;
        uint8_t ui8flashType;
        uint8_t ui8manufacturerID;
        uint8_t ui8dummy;
    };
    uint32_t ui32jedecID;
}fsscape_JEDECID_tag;

typedef union {
    uint8_t ui8addr[4];
    uint32_t ui32addr;
}fsscape_SRAM_index_addr_tag;
/* -------------------------------------------------------------------------- */

/* ------------------------------# DEFINES #--------------------------------- */
#define FSSCAPE_SRAM_I2C_ADDR 0xDE
#define FSSCAPE_SRAM_IDX_ADDR 0x20
#define FSSCAPE_SRAM_IDX_SIZE 4 // Size in bytes.
#define FSSCAPE_SRAM_IDX_CHK_ADDR (FSSCAPE_SRAM_IDX_ADDR + FSSCAPE_SRAM_IDX_SIZE)


#ifdef	__cplusplus
}
#endif

#endif	/* FSSCAPE_H */

