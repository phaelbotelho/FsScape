/* 
 * File:   at45dbxx.h
 * Author: Raphael
 *
 * Created on January 11, 2024, 9:23 PM
 */

#ifndef AT45DBXX_H
#define	AT45DBXX_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
    
    
/* Read commands */
#define AT45DB_RDMN          0xd2 /* Main Memory Page Read */
#define AT45DB_RDARRY        0xe8 /* Continuous Array Read (Legacy Command) */
#define AT45DB_RDARRAYLF     0x03 /* Continuous Array Read (Low Frequency) */
#define AT45DB_RDARRAYHF     0x0b /* Continuous Array Read (High Frequency) */
#define AT45DB_RDBF1LF       0xd1 /* Buffer 1 Read (Low Frequency) */
#define AT45DB_RDBF2LF       0xd3 /* Buffer 2 Read (Low Frequency) */
#define AT45DB_RDBF1         0xd4 /* Buffer 1 Read */
#define AT45DB_RDBF2         0xd6 /* Buffer 2 Read */

/* Program and Erase Commands */
#define AT45DB_WRBF1         0x84 /* Buffer 1 Write */
#define AT45DB_WRBF2         0x87 /* Buffer 2 Write */
#define AT45DB_BF1TOMNE      0x83 /* Buffer 1 to Main Memory Page Program with Built-in Erase */
#define AT45DB_BF2TOMNE      0x86 /* Buffer 2 to Main Memory Page Program with Built-in Erase */
#define AT45DB_BF1TOMN       0x88 /* Buffer 1 to Main Memory Page Program without Built-in Erase */
#define AT45DB_BF2TOMN       0x89 /* Buffer 2 to Main Memory Page Program without Built-in Erase  */
#define AT45DB_PGERASE       0x81 /* Page Erase */
#define AT45DB_BLKERASE      0x50 /* Block Erase */
#define AT45DB_SECTERASE     0x7c /* Sector Erase */
#define AT45DB_CHIPERASE1    0xc7 /* Chip Erase - byte 1 */
#define AT45DB_CHIPERASE2    0x94 /* Chip Erase - byte 2 */
#define AT45DB_CHIPERASE3    0x80 /* Chip Erase - byte 3 */
#define AT45DB_CHIPERASE4    0x9a /* Chip Erase - byte 4 */
#define AT45DB_MNTHRUBF1     0x82 /* Main Memory Page Program Through Buffer 1 */
#define AT45DB_MNTHRUBF2     0x85 /* Main Memory Page Program Through Buffer 2 */

/* Protection and Security Commands */
#define AT45DB_ENABPROT1     0x3d /* Enable Sector Protection - byte 1 */
#define AT45DB_ENABPROT2     0x2a /* Enable Sector Protection - byte 2 */
#define AT45DB_ENABPROT3     0x7f /* Enable Sector Protection - byte 3 */
#define AT45DB_ENABPROT4     0xa9 /* Enable Sector Protection - byte 4 */
#define AT45DB_DISABPROT1    0x3d /* Disable Sector Protection - byte 1 */
#define AT45DB_DISABPROT2    0x2a /* Disable Sector Protection - byte 2 */
#define AT45DB_DISABPROT3    0x7f /* Disable Sector Protection - byte 3 */
#define AT45DB_DISABPROT4    0x9a /* Disable Sector Protection - byte 4 */
#define AT45DB_ERASEPROT1    0x3d /* Erase Sector Protection Register - byte 1 */
#define AT45DB_ERASEPROT2    0x2a /* Erase Sector Protection Register - byte 2 */
#define AT45DB_ERASEPROT3    0x7f /* Erase Sector Protection Register - byte 3 */
#define AT45DB_ERASEPROT4    0xcf /* Erase Sector Protection Register - byte 4 */
#define AT45DB_PROGPROT1     0x3d /* Program Sector Protection Register - byte 1 */
#define AT45DB_PROGPROT2     0x2a /* Program Sector Protection Register - byte 2 */
#define AT45DB_PROGPROT3     0x7f /* Program Sector Protection Register - byte 3 */
#define AT45DB_PROGPROT4     0xfc /* Program Sector Protection Register - byte 4 */
#define AT45DB_RDPROT        0x32 /* Read Sector Protection Register */
#define AT45DB_LOCKDOWN1     0x3d /* Sector Lockdown - byte 1 */
#define AT45DB_LOCKDOWN2     0x2a /* Sector Lockdown - byte 2 */
#define AT45DB_LOCKDOWN3     0x7f /* Sector Lockdown - byte 3 */
#define AT45DB_LOCKDOWN4     0x30 /* Sector Lockdown - byte 4 */
#define AT45DB_RDLOCKDOWN    0x35 /* Read Sector Lockdown Register  */
#define AT45DB_PROGSEC1      0x9b /* Program Security Register - byte 1 */
#define AT45DB_PROGSEC2      0x00 /* Program Security Register - byte 2 */
#define AT45DB_PROGSEC3      0x00 /* Program Security Register - byte 3 */
#define AT45DB_PROGSEC4      0x00 /* Program Security Register - byte 4 */
#define AT45DB_RDSEC         0x77 /* Read Security Register */

/* Additional commands */
#define AT45DB_MNTOBF1XFR    0x53 /* Main Memory Page to Buffer 1 Transfer */
#define AT45DB_MNTOBF2XFR    0x55 /* Main Memory Page to Buffer 2 Transfer */
#define AT45DB_MNBF1CMP      0x60 /* Main Memory Page to Buffer 1 Compare  */
#define AT45DB_MNBF2CMP      0x61 /* Main Memory Page to Buffer 2 Compare */
#define AT45DB_AUTOWRBF1     0x58 /* Auto Page Rewrite through Buffer 1 */
#define AT45DB_AUTOWRBF2     0x59 /* Auto Page Rewrite through Buffer 2 */
#define AT45DB_PWRDOWN       0xb9 /* Deep Power-down */
#define AT45DB_RESUME        0xab /* Resume from Deep Power-down */
#define AT45DB_RDSR          0xd7 /* Status Register Read */
#define AT45DB_RDDEVID       0x9f /* Manufacturer and Device ID Read */

#define AT45DB_MANUFACTURER  0x1f /* Manufacturer ID: Atmel */
#define AT45DB_DEVID1_CAPMSK 0x1f /* Bits 0-4: Capacity */
#define AT45DB_DEVID1_1MBIT  0x02 /* xxx0 0010 = 1Mbit AT45DB011 */
#define AT45DB_DEVID1_2MBIT  0x03 /* xxx0 0012 = 2Mbit AT45DB021 */
#define AT45DB_DEVID1_4MBIT  0x04 /* xxx0 0100 = 4Mbit AT45DB041 */
#define AT45DB_DEVID1_8MBIT  0x05 /* xxx0 0101 = 8Mbit AT45DB081 */
#define AT45DB_DEVID1_16MBIT 0x06 /* xxx0 0110 = 16Mbit AT45DB161 */
#define AT45DB_DEVID1_32MBIT 0x07 /* xxx0 0111 = 32Mbit AT45DB321 */
#define AT45DB_DEVID1_64MBIT 0x08 /* xxx0 1000 = 32Mbit AT45DB641 */
#define AT45DB_DEVID1_FAMMSK 0xe0 /* Bits 5-7: Family */
#define AT45DB_DEVID1_DFLASH 0x20 /* 001x xxxx = Dataflash */
#define AT45DB_DEVID1_AT26DF 0x40 /* 010x xxxx = AT26DFxxx series (Not supported) */
#define AT45DB_DEVID2_VERMSK 0x1f /* Bits 0-4: MLC mask */
#define AT45DB_DEVID2_MLCMSK 0xe0 /* Bits 5-7: MLC mask */

#define AT45DB_SOFT_RESET    0xF0 /* Bits 5-7: MLC mask */
    

/* Status register bit definitions */
#define AT45DB_SR_RDY       (1 << 7) /* Bit 7: RDY/ Not BUSY */
#define AT45DB_SR_COMP      (1 << 6) /* Bit 6: COMP */
#define AT45DB_SR_PROTECT   (1 << 1) /* Bit 1: PROTECT */
#define AT45DB_SR_PGSIZE    (1 << 0) /* Bit 0: PAGE_SIZE */
    
#define DEVICE_ID_JEDEC 0x1F2400 // For a 4Mbit memory chip.
    
#define AT45dbxx_WAIT_TIMEOUT 10000
    
    
#define PAGESIZE_256BYTES 0xA6
#define PAGESIZE_264BYTES 0xA7
    
    
#define ARRAYLEN(x) (sizeof(x) / sizeof((x)[0]))

    
typedef struct
{
	uint8_t		FlashSize_MBit;	
	uint16_t	PageSize;
	uint16_t	Pages;
	uint8_t		Shift;
}AT45dbxx_t;
    
extern AT45dbxx_t AT45dbxx;
    
typedef union {
    struct {
        uint8_t flashSize;
        uint8_t flashType;
        uint8_t manufacturerID;
        uint8_t dummy;
    };
    uint32_t jedecID;
} WAT45DBID_t;


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
    
    
    /*void W25Q_Read(uint32_t startPage, uint8_t offset, uint32_t size, uint8_t *rData);
    void W25Q_FastRead(uint32_t startPage, uint8_t offset, uint32_t size, uint8_t *rData);
    
    void W25Q_Erase_Sector(uint16_t numsector);
    
    void W25Q_Write_Clean(uint32_t page, uint16_t offset, uint32_t size, uint8_t *data);
    void W25Q_Write(uint32_t page, uint16_t offset, uint32_t size, uint8_t *data);
    
    uint8_t W25Q_Read_Byte(uint32_t Addr);
    void W25Q_Write_Byte(uint32_t Addr, uint8_t data);
    
    void W25Q_Write_NUM(uint32_t page, uint16_t offset, float data);
    float W25Q_Read_NUM(uint32_t page, uint16_t offset);
    
    void W25Q_Write_32B(uint32_t page, uint16_t offset, uint32_t size, uint32_t *data);
    void W25Q_Read_32B(uint32_t page, uint16_t offset, uint32_t size, uint32_t *data);*/

#ifdef	__cplusplus
}
#endif

#endif	/* AT45DBXX_H */

