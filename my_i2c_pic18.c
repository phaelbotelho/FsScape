/* 
 * File:   my_i2c_pic18.c
 * Author: raphael.pereira
 *
 * Created on December 4, 2023, 12:01 PM
 */

#include "main.h"

#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "my_clock.h"
#include "my_i2c_pic18.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
#include "bitwise.h"

// Ported from: https://forum.microchip.com/s/topic/a5C3l000000MNpNEAW/t321653?comment=P-2424511

/** Private defines ***********************************************************/
#define Lo(x) ((x) & 0xff)
#define Hi(x) ((x) >> 8)

//-------------------Variables-------------------
uint16_t I2Cflags;
//-----------------------------------------------

//----------------Function Prototypes-------------------
void I2C_HWini(void);
void I2C_ModuleStart(uint32_t clock_output);
void I2C_ModuleStop();
void I2C_SWini(void);
int16_t I2C2_M_BusReset(void);
void I2C2_M_ClearErrors(void);
int16_t I2C2_M_Poll(uint8_t);
int16_t I2C2_M_Read(uint8_t, uint8_t, int16_t, char *);
int16_t I2C2_M_ReadByte(uint8_t);
int16_t I2C2_M_Read_Single(uint8_t DevAddr, uint8_t SubAddr, uint8_t *value);
int16_t I2C2_M_RecoverBus(void);
int16_t I2C2_M_Restart(void);
int16_t I2C2_M_Start(void);
int16_t I2C2_M_Stop(void);
int16_t I2C2_M_Write(uint8_t, uint8_t, int16_t, char *);
int16_t I2C2_M_Write24(uint8_t, uint8_t, int16_t, char *);
int16_t I2C2_M_WriteByte(char);
int16_t I2C2_M_Write_Single(uint8_t DevAddr, uint8_t SubAddr, uint8_t value);
void I2C2_M_ClearBus();

int16_t I2C_Mem_Write(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
int16_t I2C_Mem_Read(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//------------------------------------------------------


void I2C_HWini(void)
{
    //-----Set pin drive modes-----
    //I2C - drive outputs so we can manually clear lines
    I2C_SCL_TRIS = 1; //Start with bus in idle mode - both lines high
    I2C_SDA_TRIS = 1;
}

void I2C_ModuleStart(uint32_t clock_output)
{
    SSP1STAT &= 0x3F; // Power on state
    SSP1CON2 = 0x00; // Power on state
    
    // Control slew rate according the speed.
    if(clock_output == 400000UL)
    {
        SSP1STAT |= 0b00000000; // Slew rate on.
    }
    else
    {
        SSP1STAT |= 0b10000000; // Slew rate off.
    }
    
    SSP1CON1 = 0b00001000; // Select serial mode.
    SSP1ADD = (uint8_t) ((uint32_t)CLOCK_PeripheralFrequencyGet() / (uint32_t)clock_output) - 1; // Clock = FOSC/(4 * (SSP1ADD + 1)) Therefore SSP1ADD = (FCY/FSCL) -1.
    
    SSP1CON1 |= 0b00100000; // Enable synchronous serial port
}

void I2C_ModuleStop()
{
    SSP1CON1bits.SSPEN = 0; // Disable the MSSP module.
}

void I2C_SWini(void)
{
    I2Cflags = 0;
    SetI2C2BusDirty; //I2C bus in unknown state, go ahead and clear it
}

//Reset the I2C bus - called by I2C2_M_RecoverBus()
//This routine will verify that SCL can be set HIGH, then free SDA by clocking until SDA goes HIGH.
//Then the bus will be reset by issuing a START and STOP condition to restart the I2C bus.
//This should clear any devices hung on incomplete I2C transfers.
//
//Note I2C module must not be active or this routine will not work
//Returns:
//I2C_OK
//I2C_Err_SCL_low
//I2C_Err_SDA_low
//*******************************************************************************
int16_t I2C2_M_BusReset()
{
    int16_t i;
    
    //Start with lines high - sets SCL high if not already there
    I2C_SCL_SetDigitalInput();
    I2C_SDA_SetDigitalInput();
    __delay_us(5); //Need 5uS delay
    
    if(I2C_SCL_GetValue() == 0) //Read if line actually went high
    {
        return I2C_Err_SCL_low; //SCL stuck low - is the pullup resistor loaded?
    }
    //SCL ok, toggle until SDA goes high.
    i = 10;
    
    I2C_SCL_SetDigitalOutput();
    while(i > 0)
    {
        if(I2C_SDA_GetValue() == 1) //If SDA is high, then we are done
        {
            break;
        }
        I2C_SCL_SetLow(); //SCL low
        __delay_us(1); //Need 5uS delay
        I2C_SCL_SetHigh(); //SCL high
        __delay_us(1); //Need 5uS delay
        i--;
    }
    
    I2C_SCL_SetDigitalInput();
    I2C_SDA_SetDigitalInput();
    
    if(!I2C_SDA_GetValue() && !I2C_SCL_GetValue()) //We are ok if SCL and SDA high
    {
        return I2C_Err_SDA_low;
    }
    
    I2C_SDA_SetDigitalOutput();
    I2C_SDA_SetLow(); //SDA LOW while SCL HIGH -> START
    __delay_us(1); //Need 5uS delay
    I2C_SDA_SetHigh(); //SDA HIGH while SCL HIGH -> STOP
    __delay_us(1); //Need 5uS delay
    I2C_SCL_SetDigitalInput();
    I2C_SDA_SetDigitalInput();
    return I2C_OK;
}

#if 0
int16_t I2C2_M_BusReset()
{
    int16_t i;

    //Start with lines high - sets SCL high if not already there
    //I2C2_SCL_GetValue(); LATFbits.LATF5 = 1;	//PORTFbits.RF5 = 1 is equivalent
    //I2C2_SDA_GetValue(); LATGbits.LATG3 = 1;
    I2C_SCL_SetDigitalOutput();
    I2C_SCL_SetLow();
    I2C_SDA_SetDigitalOutput();
    I2C_SDA_SetLow();

    __delay_us(5); //Need 5uS delay
    I2C_SCL_SetDigitalInput();
    I2C_SDA_SetDigitalInput();
    __delay_us(5); //Need 5uS delay
    
    if(I2C_SCL_GetValue() == 0) //Read if line actually went high
    {
        return I2C_Err_SCL_low; //SCL stuck low - is the pullup resistor loaded?
    }
    //SCL ok, toggle until SDA goes high.
    i = 10;
    
    I2C_SCL_SetDigitalOutput();
    while(i > 0)
    {
        if(I2C_SDA_GetValue() == 1) //If SDA is high, then we are done
        {
            break;
        }
        I2C_SCL_SetLow(); //SCL low
        __delay_us(1); //Need 5uS delay
        I2C_SCL_SetHigh(); //SCL high
        __delay_us(1); //Need 5uS delay
        i--;
    }
    
    I2C_SCL_SetDigitalInput();
    I2C_SDA_SetDigitalInput();
    
    if(!I2C_SDA_GetValue() && !I2C_SCL_GetValue()) //We are ok if SCL and SDA high
    {
        return I2C_Err_SDA_low;
    }
    
    I2C_SDA_SetDigitalOutput();
    //I2C_SCL_SetDigitalOutput();
    
    I2C_SDA_SetLow(); //SDA LOW while SCL HIGH -> START
    __delay_us(1); //Need 5uS delay
    I2C_SDA_SetHigh(); //SDA HIGH while SCL HIGH -> STOP
    __delay_us(1); //Need 5uS delay
    I2C_SCL_SetDigitalInput();
    I2C_SDA_SetDigitalInput();
    return I2C_OK;
}
#endif

//Clear any errors that may have occurred
void I2C2_M_ClearErrors()
{
    SSP1CON2bits.RCEN1 = 0; //Cancel receive request
    SSP1CON1bits.WCOL1 = 0; //Clear write-collision flag
    PIR2bits.BCL1IF = 0; //Clear bus-collision flag
}

//Poll an I2C device to see if it is alive
//This should be done periodically, say every 1 second
//Also does error recovery of the I2C bus here, if indicated
//Returns:
//I2C_OK
//I2C_Err_BadAddr
//I2C_Err_CommFail
//I2C_Err_Hardware

int16_t I2C2_M_Poll(uint8_t DevAddr)
{
    int retval;
    uint8_t SlaveAddr;

    SlaveAddr = DevAddr | 0;

    if(IsI2C2BusDirty)
    {
        I2C2_M_ClearErrors();
        if(I2C2_M_RecoverBus() == I2C_OK)
        {//Recovered
            ClrI2C2BusDirty;
        } else
        {
            return I2C_Err_Hardware;
        }
    }

    if(I2C2_M_Start() == I2C_OK)
    {
        retval = I2C2_M_WriteByte((char) SlaveAddr);
        if(I2C2_M_Stop() == I2C_OK) //Even if we have an error sending, try to close I2C
        {
            if(retval == I2C_ACK)
            {
                return I2C_OK;
            } else if(retval == I2C_Err_NAK)
            {
                return I2C_Err_BadAddr; //Check that correct device address is being used
            } else
            {
                return I2C_Err_CommFail;
            }

        }
    }
    //Get here then we had an error
    SetI2C2BusDirty; //Set error flag
    return I2C_Err_CommFail;
}

//High level function.  Reads data from target into buffer
//Returns:
//I2C_Ok
//I2C_Err_BadAddr
//I2C_Err_BusDirty
//I2C_Err_CommFail
int16_t I2C2_M_Read(uint8_t DevAddr, uint8_t SubAddr, int16_t uint8_tCnt, char *buffer)
{
    uint8_t SlaveAddr;
    int16_t retval;
    int16_t i;

    if(IsI2C2BusDirty) //Ignore requests until Poll cmd is called to fix err.
        return I2C_Err_BusDirty;

    if(I2C2_M_Start() != I2C_OK) //Start
    {//Failed to open bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    SlaveAddr = DevAddr; //Device Address + Write bit
    retval = I2C2_M_WriteByte((char) SlaveAddr);
    if(retval == I2C_Err_NAK)
    {//Bad Slave Address or I2C slave device stopped responding
        I2C2_M_Stop();
        SetI2C2BusDirty; //Will reset slave device
        return I2C_Err_BadAddr;
    } else if(retval < 0)
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_WriteByte((char) SubAddr) != I2C_OK) //Sub Addr
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_Restart() != I2C_OK) //Repeated start - switch to read mode
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    SlaveAddr = DevAddr + 1; //Device Address + Read bit
    if(I2C2_M_WriteByte((char) SlaveAddr) != I2C_OK) //Slave Addr
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    for(i = 0; i < uint8_tCnt; i++) //Data
    {
        if(i == (uint8_tCnt - 1))
        {
            retval = I2C2_M_ReadByte(I2C_M_NACK); //NACK on last uint8_t so slave knows this is it
        } else
        {
            retval = I2C2_M_ReadByte(I2C_M_ACK);
        }
        if(retval >= 0)
        {
            //buffer[i] = retval;
        } else
        {//Error while reading uint8_t.  Close connection and set error flag.
            I2C2_M_Stop();
            SetI2C2BusDirty;
            return I2C_Err_CommFail;
        }
    }

    if(I2C2_M_Stop() != I2C_OK)
    {//Failed to close bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    return I2C_OK; //Success
}

//Initiates read of one uint8_t from slave on I2C bus
//Slave must already be addressed, and in read mode
//Waits until completed before returning
//*Caution* Slave can cause a timeout by clock stretching too long
//Returns:
//0x0000-0x00FF Read value stored in low uint8_t (returned integer will always be positive)
//  Error status is indicated by negative return values
//I2C_Err_Overflow
//I2C_Err_RcvTimeout (will happen if slave is clock stretching, or SCL suddenly shorted to ground)
//I2C_Err_SCL_stucklow.  SDA stuck low cannot be detected here.

int16_t I2C2_M_ReadByte(uint8_t ACKflag)
{
    int16_t t;

    if(ACKflag == I2C_M_NACK) //Set state in preparation for TX below
    {
        SSP1CON2bits.ACKDT1 = 1; //NACK
    } else
    {
        SSP1CON2bits.ACKDT1 = 0; //ACK
    }

    SSP1CON2bits.RCEN1 = 1; //Start receive
    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=16MIPS) and 8 bits, I expect <=320.
    //We could wait for RCEN to be cleared, but are really interested in incoming uint8_t, so look for I2C2STAT.RBF
    while(!SSP1STATbits.BF1) //HW cleared when receive complete
    {
        t++;
        if(t > 8000)
        {//SCL stuck low
            //RCEN cannot be cleared in SW. Will need to reset I2C interface, or wait until SCL goes high.
            return I2C_Err_RcvTimeout;
        }
    }//Tested: t=30
    //I2C2STATbits.RBF will likely be set

    //As the master we must ACK or NACK every uint8_t, so slave knows if it will send another uint8_t.
    //We have set the bit above, just need to send it
    SSP1CON2bits.ACKEN1 = 1; //Send ACK bit now
    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=16MIPS), I expect <=40.
    while(SSP1CON2bits.ACKEN1) //HW cleared when complete
    {
        t++;
        if(t > 1000)
        {//This will timeout if SCL stuck low
            //ACKEN cannot be cleared in SW. I2C interface must be reset after this error.
            return I2C_Err_SCL_low;
        }
    }//Tested: t=4
    if(SSP1CON1bits.SSPOV1) //If an overflow occurred, it means we received a new uint8_t before reading last one
    {
        SSP1CON1bits.SSPOV1 = 0;
        return I2C_Err_Overflow;
    }

    return SSP1BUF; //Reading this register clears RBF
}

//High level function.  Reads single byte from target into buffer
//Returns:
//I2C_Ok
//I2C_Err_BadAddr
//I2C_Err_BusDirty
//I2C_Err_CommFail
int16_t I2C2_M_Read_Single(uint8_t DevAddr, uint8_t SubAddr, uint8_t *value)
{
    uint8_t SlaveAddr;
    volatile int16_t retval;

    I2C2_M_Start(); //Start

    retval = I2C2_M_WriteByte((char) DevAddr);

    if(retval == I2C_Err_NAK)
    {//Bad Slave Address or I2C slave device stopped responding
        I2C2_M_Stop();
        SetI2C2BusDirty; //Will reset slave device
        return I2C_Err_BadAddr;
    }
    else if(retval < 0)
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_WriteByte((char) SubAddr) != I2C_OK) //Sub Addr
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_Restart() != I2C_OK) //Repeated start - switch to read mode
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    SlaveAddr = DevAddr + 0x01; //Device Address + Read bit
    if(I2C2_M_WriteByte((char) SlaveAddr) != I2C_OK) //Slave Addr
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    
    retval = I2C2_M_ReadByte(I2C_M_NACK); //NACK on last byte so slave knows this is it
    
    if(retval >= 0)
    {
        *value = retval;
    }
    else
    {//Error while reading byte.  Close connection and set error flag.
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_Stop() != I2C_OK)
    {//Failed to close bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    return I2C_OK; //Success
}

//Attempt to recover after I2C error
//Returns:
//I2C_OK
//I2C_Err_Hardware
int16_t I2C2_M_RecoverBus()
{
    int16_t status;
    //	//Level 1: reset the I2C hardware on our side
    //	I2C2CONbits.I2CEN = 0;
    //	Nop();
    //	I2C2CONbits.I2CEN = 1;

    //Level 2: reset devices on I2C network
    //Disable I2C so we can toggle pins
    SSP1CON1bits.SSPEN1 = 0;
    status = I2C2_M_BusReset();
    if(status > 0)
    {//Fatal I2C error, nothing we can do about it
        return I2C_Err_Hardware;
    }
    //That worked, bring I2C back online
    SSP1CON1bits.SSPEN1 = 1;

    return I2C_OK;
}

//Initiates repeated start sequence on I2C bus
//Waits until completed before returning
//Returns:
//I2C_OK
//I2C_Err_BCL
//I2C_Err_SCL_low.  SDA stuck low cannot be detected here.
int16_t I2C2_M_Restart()
{
    int16_t t;

    SSP1CON2bits.RSEN1 = 1; //Initiate restart condition
    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=32Mhz;16MIPS), I expect <=40.
    while(SSP1CON2bits.RSEN1) //HW cleared when complete
    {
        t++;
        if(t > 1000)
        {//Will timeout if SCL stuck low
            //RSEN cannot be cleared in SW. Will need to reset I2C interface.
            return I2C_Err_SCL_low;
        }
    }//Tested: t=5

    if(PIR2bits.BCL1IF)
    {//SDA stuck low
        PIR2bits.BCL1IF = 0; //Clear error to regain control of I2C
        return I2C_Err_BCL;
    }

    return I2C_OK;
}

//Initiates start sequence on I2C bus
//Waits until completed before returning
//Returns:
//I2C_OK
//I2C_Err_BCL
//I2C_Err_IWCOL
//I2C_Err_TimeoutHW
int16_t I2C2_M_Start()
{
    int16_t t;

    SSP1CON2bits.SEN1 = 1; //Initiate Start condition
    Nop();
    if(PIR2bits.BCL1IF)
    {//SCL or SDA stuck low
        SSP1CON2bits.SEN1 = 0; //Cancel request (will still be set if we had previous BCL)
        PIR2bits.BCL1IF = 0; //Clear error to regain control of I2C
        return I2C_Err_BCL;
    }
    if(SSP1CON1bits.WCOL1)
    {//Not sure how this happens but it occurred once, so trap here
        SSP1CON2bits.SEN1 = 0; //Clear just in case set
        SSP1CON1bits.WCOL1 = 0; //Clear error
        return I2C_Err_IWCOL;
    }

    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=32Mhz;16MIPS), I expect <=40.
    while(SSP1CON2bits.SEN1) //HW cleared when complete
    {
        t++;
        if(t > 1000)
        {//Since SCL and SDA errors are trapped by BCL error above, this should never happen
            return I2C_Err_TimeoutHW;
        }
    }//Tested: t=3.  I2C2STATbits.S will be set indicating start bit detected.

    //If a second start request is issued after first one, the I2C module will instead:
    //generate a stop request, clear SEN, and flag BCL.  Test for BCL here.
    if(PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0; //Clear error to regain control of I2C
        return I2C_Err_BCL;
    }

    return I2C_OK;
}

//Initiates stop sequence on I2C bus
//Waits until completed before returning
//Returns:
//I2C_OK
//I2C_Err_BCL
//I2C_Err_SCL_low.  SDA stuck low cannot be detected here.
int16_t I2C2_M_Stop()
{
    int16_t t;

    SSP1CON2bits.PEN1 = 1; //Initiate stop condition
    Nop();
    if(PIR2bits.BCL1IF)
    {//Not sure if this can ever happen here
        PIR2bits.BCL1IF = 0; //Clear error
        return I2C_Err_BCL; //Will need to reset I2C interface.
    }

    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=16MIPS), I expect <=40.
    while(SSP1CON2bits.PEN1) //HW cleared when complete
    {
        t++;
        if(t > 1000)
        {//Will timeout if SCL stuck low
            //PEN cannot be cleared in SW. Will need to reset I2C interface.
            return I2C_Err_SCL_low;
        }
    }//Tested: t=5
    return I2C_OK;
}

//High level function.  Writes buffered data to target address.
//Returns:
//I2C_OK
//I2C_Err_BadAddr
//I2C_Err_BusDirty
//I2C_Err_CommFail
int16_t I2C2_M_Write(uint8_t DevAddr, uint8_t SubAddr, int16_t uint8_tCnt, char *buffer)
{
    int16_t i;
    int16_t retval;
    uint8_t SlaveAddr;

    if(IsI2C2BusDirty) //Ignore requests until Poll cmd is called to fix err.
    {
        printf("i2c dirty on first check\n");
        return I2C_Err_BusDirty;
    }

    if(I2C2_M_Start() != 0) //Start
    {//Failed to open bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    SlaveAddr = DevAddr | 0; //Device Address + Write bit
    retval = I2C2_M_WriteByte((char) SlaveAddr);
    if(retval == I2C_Err_NAK)
    {//Bad Slave Address or I2C slave device stopped responding
        I2C2_M_Stop();
        SetI2C2BusDirty; //Will reset slave device
        return I2C_Err_BadAddr;
    } else if(retval < 0)
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_WriteByte((char) SubAddr) != I2C_ACK) //Sub Addr
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    for(i = 0; i < uint8_tCnt; i++) //Data
    {
        if(I2C2_M_WriteByte(buffer[i]) != I2C_ACK)
        {//Error while writing uint8_t.  Close connection and set error flag.
            I2C2_M_Stop();
            SetI2C2BusDirty;
            return I2C_Err_CommFail;
        }
    }

    if(I2C2_M_Stop() != I2C_OK)
    {//Failed to close bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    return I2C_OK;
}

//High level function.  Writes buffered data to target address.
//Returns:
//I2C_OK
//I2C_Err_BadAddr
//I2C_Err_BusDirty
//I2C_Err_CommFail
int16_t I2C2_M_Write24(uint8_t DevAddr, uint8_t SubAddr, int16_t uint8_tCnt, char *buffer)
{
    int16_t i;
    int16_t retval;
    uint8_t SlaveAddr;

    if(IsI2C2BusDirty) //Ignore requests until Poll cmd is called to fix err.
        return I2C_Err_BusDirty;

    if(I2C2_M_Start() != 0) //Start
    {//Failed to open bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    SlaveAddr = DevAddr | 0; //Device Address + Write bit
    retval = I2C2_M_WriteByte((char) SlaveAddr);
    if(retval == I2C_Err_NAK)
    {//Bad Slave Address or I2C slave device stopped responding
        I2C2_M_Stop();
        SetI2C2BusDirty; //Will reset slave device
        return I2C_Err_BadAddr;
    }
    else if(retval < 0)
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_WriteByte((char) SubAddr) != I2C_ACK) //Sub Addr
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    for(i = 0; i < uint8_tCnt; i++) //Data
    {
        if(I2C2_M_WriteByte(buffer[i]) != I2C_ACK)
        {//Error while writing uint8_t.  Close connection and set error flag.
            I2C2_M_Stop();
            SetI2C2BusDirty;
            return I2C_Err_CommFail;
        }
    }

    if(I2C2_M_Stop() != I2C_OK)
    {//Failed to close bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    return I2C_OK;
}

//Sends a uint8_t to a slave
//Waits until completed before returning
//Returns:
//I2C_ACK
//I2C_Err_BCL
//I2C_Err_NAK
//I2C_Err_SCL_low
//I2C_Err_TBF
int16_t I2C2_M_WriteByte(char cData)
{
    int16_t t;

    if(SSP1STATbits.R_NOT_W) //Is there already a uint8_t waiting to send?
    {
        return I2C_Err_TBF;
    }

    SSP1BUF = cData; //Send uint8_t
    //Transmission takes several clock cycles to complete.  As a result we won't see BCL error for a while.
    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=32Mhz;16MIPS) and 8 bits, I expect <=320.

    while(SSP1STATbits.BF1) //HW cleared when TX complete
    {
        t++;

        if(t > 16000)
        {//This is bad because TRSTAT will still be set
            return I2C_Err_SCL_low; //Must reset I2C interface, and possibly slave devices
        }
    }//Testing: t=31

    if(PIR2bits.BCL1IF)
    {
        PIR2bits.BCL1IF = 0; //Clear error to regain control of I2C
        return I2C_Err_BCL;
    }

    //Done, now how did slave respond?
    if(SSP1CON2bits.ACKSTAT1) //1=NACK
        return I2C_Err_NAK; //  NACK
    else
        return I2C_ACK; //  ACK
}

//High level function.  Writes single byte data to target address.
//Returns:
//I2C_OK
//I2C_Err_BadAddr
//I2C_Err_BusDirty
//I2C_Err_CommFail
int16_t I2C2_M_Write_Single(uint8_t DevAddr, uint8_t SubAddr, uint8_t value)
{
    int16_t retval;
    uint8_t SlaveAddr;

    if(IsI2C2BusDirty) //Ignore requests until Poll cmd is called to fix err.
        return I2C_Err_BusDirty;

    if(I2C2_M_Start() != 0) //Start
    {
        //Failed to open bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    SlaveAddr = DevAddr; //Device Address + Write bit
    retval = I2C2_M_WriteByte((char) SlaveAddr);
    if(retval == I2C_Err_NAK)
    {
        //Bad Slave Address or I2C slave device stopped responding
        I2C2_M_Stop();
        SetI2C2BusDirty; //Will reset slave device
        return I2C_Err_BadAddr;
    }
    else if(retval < 0)
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_WriteByte((char) SubAddr) != I2C_ACK) //Sub Addr
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_WriteByte(value) != I2C_ACK)
    {
        //Error while writing byte.  Close connection and set error flag.
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    
    if(I2C2_M_Stop() != I2C_OK)
    {
        //Failed to close bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    return I2C_OK;
}

void I2C2_M_ClearBus()
{
    uint8_t i;
    
    for(i = 0; i < 8; i++)
    {
        I2C_SCL_SetDigitalOutput();
        I2C_SCL_SetDigitalInput();
    }
}

int16_t I2C_Mem_Write(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    //uint32_t _old_millis = millis();
    int16_t i;
    int16_t retval;
    uint8_t SlaveAddr;

    if(IsI2C2BusDirty) //Ignore requests until Poll cmd is called to fix err.
        return I2C_Err_BusDirty;

    if(I2C2_M_Start() != 0) //Start
    {//Failed to open bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    SlaveAddr = DevAddress | 0; //Device Address + Write bit
    retval = I2C2_M_WriteByte((char) SlaveAddr);
    if(retval == I2C_Err_NAK)
    {//Bad Slave Address or I2C slave device stopped responding
        I2C2_M_Stop();
        SetI2C2BusDirty; //Will reset slave device
        return I2C_Err_BadAddr;
    } else if(retval < 0)
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_WriteByte((char) Hi(MemAdress)) != I2C_ACK) //MemAdress High parcel.
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    if(I2C2_M_WriteByte((char) Lo(MemAdress)) != I2C_ACK) //MemAdress Low parcel.
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    for(i = 0; i < Size; i++) //Data
    {
        if(I2C2_M_WriteByte(pData[i]) != I2C_ACK)
        {//Error while writing uint8_t.  Close connection and set error flag.
            I2C2_M_Stop();
            SetI2C2BusDirty;
            return I2C_Err_CommFail;
        }
    }

    if(I2C2_M_Stop() != I2C_OK)
    {//Failed to close bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    return I2C_OK;
}

int16_t I2C_Mem_Read(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    //uint32_t old_millis = millis();
    uint8_t SlaveAddr;
    int16_t retval;
    int16_t i;

    if(IsI2C2BusDirty) //Ignore requests until Poll cmd is called to fix err.
        return I2C_Err_BusDirty;

    if(I2C2_M_Start() != I2C_OK) //Start
    {//Failed to open bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    SlaveAddr = DevAddress; //Device Address + Write bit
    retval = I2C2_M_WriteByte((char) SlaveAddr);
    if(retval == I2C_Err_NAK)
    {//Bad Slave Address or I2C slave device stopped responding
        I2C2_M_Stop();
        SetI2C2BusDirty; //Will reset slave device
        return I2C_Err_BadAddr;
    } else if(retval < 0)
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_WriteByte((char) Hi(MemAdress)) != I2C_OK) //MemAdress High parcel.
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    if(I2C2_M_WriteByte((char) Lo(MemAdress)) != I2C_OK) //MemAdress Low parcel.
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    if(I2C2_M_Restart() != I2C_OK) //Repeated start - switch to read mode
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }

    SlaveAddr = DevAddress + 1; //Device Address + Read bit
    if(I2C2_M_WriteByte((char) SlaveAddr) != I2C_OK) //Slave Addr
    {
        I2C2_M_Stop();
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    for(i = 0; i < Size; i++) //Data
    {
        if(i == (Size - 1))
        {
            retval = I2C2_M_ReadByte(I2C_M_NACK); //NACK on last uint8_t so slave knows this is it
        } else
        {
            retval = I2C2_M_ReadByte(I2C_M_ACK);
        }
        if(retval >= 0)
        {
            pData[i] = (uint8_t)retval;
        } else
        {//Error while reading uint8_t.  Close connection and set error flag.
            I2C2_M_Stop();
            SetI2C2BusDirty;
            return I2C_Err_CommFail;
        }
    }

    if(I2C2_M_Stop() != I2C_OK)
    {//Failed to close bus
        SetI2C2BusDirty;
        return I2C_Err_CommFail;
    }
    return I2C_OK; //Success
}

