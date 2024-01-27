/* 
 * File:   my_i2c_pic18.h
 * Author: raphael.pereira
 *
 * Created on December 4, 2023, 12:01 PM
 */

#ifndef MY_I2C_PIC18_H
#define	MY_I2C_PIC18_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

// Ported from: https://forum.microchip.com/s/topic/a5C3l000000MNpNEAW/t321653?comment=P-2424511

//--------------------Constants--------------------
//Used for I2C2_M_RcvByte()
#define I2C_M_ACK	0
#define I2C_M_NACK	1

//Return values.  Errors must be negative.
#define I2C_OK				0		//Success
#define I2C_ACK				0		//ACK, same as OK
#define I2C_Err_Hardware	-1		//Hardware error with I2C bus, inspect PCB
#define I2C_Err_SCL_low		-2		//Clock line stuck low - HW problem on PCB, or I2C slave holding line low
#define I2C_Err_SDA_low		-3		//Data line stuck low
#define I2C_Err_BCL			-4		//Bus collision detected during master operation. Reset I2C interface.
#define I2C_Err_IWCOL		-5		//Attempted to write to I2CxTRN while byte still qued for sending
#define I2C_Err_NAK			-6		//Slave refused/ignored byte sent by master - could re-send byte
#define I2C_Err_TBF			-7		//Transmit buffer full - a byte already qued for sending. Indicates programming error.
#define I2C_Err_Overflow	-9		//Received new byte without processing previous one
#define I2C_Err_RcvTimeout	-10		//Timeout while waiting for byte from slave
#define I2C_Err_BusDirty	-100	//Need to reset I2C bus before high level routines will work
#define I2C_Err_TimeoutHW	-101	//Timeout, unknown reason
#define I2C_Err_CommFail	-102	//General communications failure
#define I2C_Err_BadAddr		-103	//Bad device address or device stopped responding
    

//--------------------Structs----------------------
//--------------------Variables--------------------
//--------------------Functions--------------------
extern void I2C_HWini(void);
extern void I2C_ModuleStart(uint32_t);
extern void I2C_SWini(void);
extern int16_t I2C2_M_BusReset(void);
extern void I2C2_M_ClearErrors(void);
extern int16_t I2C2_M_Poll(uint8_t);
extern int16_t I2C2_M_Read(uint8_t, uint8_t, int16_t, char *);
extern int16_t I2C2_M_ReadByte(uint8_t);
extern int16_t I2C2_M_Read_Single(uint8_t DevAddr, uint8_t SubAddr, uint8_t* value);
extern int16_t I2C2_M_RecoverBus(void);
extern int16_t I2C2_M_Restart(void);
extern int16_t I2C2_M_Start(void);
extern int16_t I2C2_M_Stop(void);
extern int16_t I2C2_M_Write(uint8_t, uint8_t, int16_t, char *);
extern int16_t I2C2_M_Write24(uint8_t, uint8_t, int16_t, char *);
extern int16_t I2C2_M_WriteByte(char);
extern int16_t I2C2_M_Write_Single(uint8_t DevAddr, uint8_t SubAddr, uint8_t value);
extern void I2C2_M_ClearBus();

extern int16_t I2C_Mem_Write(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
extern int16_t I2C_Mem_Read(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);

//-------------------Macros-------------------
#define SetI2C2BusDirty	I2Cflags |=  0x0001
#define ClrI2C2BusDirty	I2Cflags &= ~0x0001
#define IsI2C2BusDirty	(I2Cflags & 0x0001)


#ifdef	__cplusplus
}
#endif

#endif	/* MY_I2C_PIC18_H */

