/* 
 * File:   my_i2c.c
 * Author: raphael.pereira
 *
 * Created on September 15, 2022, 11:41 AM
 */
#include <stdint.h>

#include "my_i2c.h"
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/clock.h"
#include "mcc_generated_files/system.h"
#include "main.h"
#include "mcc_generated_files/pin_manager.h"
#include <libpic30.h>

//-------------------Variables-------------------
uint16_t I2Cflags;
//-------------------Variables-------------------

//----------------Function Prototypes-------------------
void I2C_HWini(void);
void I2C_ModuleStart(uint32_t clock_output);
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
//----------------Function Prototypes-------------------

void I2C_HWini()
{
    //-----Set pin drive modes-----
    //I2C - drive outputs so we can manually clear lines
    LATFbits.LATF5 = 1; //Start with bus in idle mode - both lines high
    LATFbits.LATF4 = 1;
    ODCFbits.ODF5 = 1; //Open drain mode
    ODCFbits.ODF4 = 1;
    TRISFbits.TRISF5 = 0; //SCL1 output
    TRISFbits.TRISF4 = 0; //SDA1 output
}

void I2C_ModuleStart(uint32_t clock_output)
{
    //Set up I2C for 400kHz operation on I2C port 1 (pins 56,57) on PIC24FJ256GA110
    I2C2CON = 0x1000; //Set all bits to known state
    I2C2CONbits.I2CEN = 0; //Disable until everything set up. Pins will be std IO.
    I2C2BRG = (((CLOCK_PeripheralFrequencyGet() / clock_output) - (CLOCK_PeripheralFrequencyGet() / 10000000)) - 1); // Clock = (Fcy)/(I2CxBRG+1+(Fcy/10000000))
    //I2C2BRG = 37;	//I2C2BRG = (Fcy/Fscl-FCY/10E6)-1 = (16E6/400E3-16E6/10E6)-1 = 40-1.6-1 = 37.4. Actual Fscl=404kHz.
    I2C2CONbits.DISSLW = 0; //Enable slew rate control for 400kHz operation
    IFS3bits. MI2C2IF = 0; //Clear I2C master int16_t flag
    I2C2CONbits.I2CEN = 1; //Enable I2C

    //For interrupt driven code
    //IEC1bits.MI2C2IE = 1;									//Enable I2C master interrupt
}

void I2C_SWini()
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
    //I2C2_SCL_GetValue(); LATFbits.LATF5 = 1;	//PORTFbits.RF5 = 1 is equivalent
    //I2C2_SDA_GetValue(); LATGbits.LATG3 = 1;
    I2C2_SCL_SetDigitalOutput();
    I2C2_SCL_SetHigh();
    I2C2_SDA_SetDigitalOutput();
    I2C2_SDA_SetHigh();

    __delay_us(1); //Need 5uS delay
    if(I2C2_SCL_GetValue() == 0) //Read if line actually went high
    {
        return I2C_Err_SCL_low; //SCL stuck low - is the pullup resistor loaded?
    }
    //SCL ok, toggle until SDA goes high.
    i = 10;
    while(i > 0)
    {
        if(I2C2_SDA_GetValue() == 1) //If SDA is high, then we are done
        {
            break;
        }
        I2C2_SCL_SetLow(); //SCL low
        __delay_us(1); //Need 5uS delay
        I2C2_SCL_SetHigh(); //SCL high
        __delay_us(1); //Need 5uS delay
        i--;
    }
    if((PORTG & 0x000C) != 0x000C) //We are ok if SCL and SDA high
    {
        return I2C_Err_SDA_low;
    }

    I2C2_SDA_SetLow(); //SDA LOW while SCL HIGH -> START
    __delay_us(1); //Need 5uS delay
    I2C2_SDA_SetHigh(); //SDA HIGH while SCL HIGH -> STOP
    __delay_us(1); //Need 5uS delay
    I2C2_SCL_SetDigitalInput();
    I2C2_SDA_SetDigitalInput();
    return I2C_OK;
}

//Clear any errors that may have occurred

void I2C2_M_ClearErrors()
{
    I2C2CONbits.RCEN = 0; //Cancel receive request
    I2C2STATbits.IWCOL = 0; //Clear write-collision flag
    I2C2STATbits.BCL = 0; //Clear bus-collision flag
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
            buffer[i] = retval;
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
        I2C2CONbits.ACKDT = 1; //NACK
    } else
    {
        I2C2CONbits.ACKDT = 0; //ACK
    }

    I2C2CONbits.RCEN = 1; //Start receive
    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=16MIPS) and 8 bits, I expect <=320.
    //We could wait for RCEN to be cleared, but are really interested in incoming uint8_t, so look for I2C2STAT.RBF
    while(!I2C2STATbits.RBF) //HW cleared when receive complete
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
    I2C2CONbits.ACKEN = 1; //Send ACK bit now
    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=16MIPS), I expect <=40.
    while(I2C2CONbits.ACKEN) //HW cleared when complete
    {
        t++;
        if(t > 1000)
        {//This will timeout if SCL stuck low
            //ACKEN cannot be cleared in SW. I2C interface must be reset after this error.
            return I2C_Err_SCL_low;
        }
    }//Tested: t=4
    if(I2C2STATbits.I2COV) //If an overflow occurred, it means we received a new uint8_t before reading last one
    {
        I2C2STATbits.I2COV = 0;
        return I2C_Err_Overflow;
    }

    return I2C2RCV; //Reading this register clears RBF
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
    } else
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
    I2C2CONbits.I2CEN = 0;
    status = I2C2_M_BusReset();
    if(status > 0)
    {//Fatal I2C error, nothing we can do about it
        return I2C_Err_Hardware;
    }
    //That worked, bring I2C back online
    I2C2CONbits.I2CEN = 1;

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

    I2C2CONbits.RSEN = 1; //Initiate restart condition
    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=32Mhz;16MIPS), I expect <=40.
    while(I2C2CONbits.RSEN) //HW cleared when complete
    {
        t++;
        if(t > 1000)
        {//Will timeout if SCL stuck low
            //RSEN cannot be cleared in SW. Will need to reset I2C interface.
            return I2C_Err_SCL_low;
        }
    }//Tested: t=5

    if(I2C2STATbits.BCL)
    {//SDA stuck low
        I2C2STATbits.BCL = 0; //Clear error to regain control of I2C
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

    I2C2CONbits.SEN = 1; //Initiate Start condition
    Nop();
    if(I2C2STATbits.BCL)
    {//SCL or SDA stuck low
        I2C2CONbits.SEN = 0; //Cancel request (will still be set if we had previous BCL)
        I2C2STATbits.BCL = 0; //Clear error to regain control of I2C
        return I2C_Err_BCL;
    }
    if(I2C2STATbits.IWCOL)
    {//Not sure how this happens but it occurred once, so trap here
        I2C2CONbits.SEN = 0; //Clear just in case set
        I2C2STATbits.IWCOL = 0; //Clear error
        return I2C_Err_IWCOL;
    }

    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=32Mhz;16MIPS), I expect <=40.
    while(I2C2CONbits.SEN) //HW cleared when complete
    {
        t++;
        if(t > 1000)
        {//Since SCL and SDA errors are trapped by BCL error above, this should never happen
            return I2C_Err_TimeoutHW;
        }
    }//Tested: t=3.  I2C2STATbits.S will be set indicating start bit detected.

    //If a second start request is issued after first one, the I2C module will instead:
    //generate a stop request, clear SEN, and flag BCL.  Test for BCL here.
    if(I2C2STATbits.BCL)
    {
        I2C2STATbits.BCL = 0; //Clear error to regain control of I2C
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

    I2C2CONbits.PEN = 1; //Initiate stop condition
    Nop();
    if(I2C2STATbits.BCL)
    {//Not sure if this can ever happen here
        I2C2STATbits.BCL = 0; //Clear error
        return I2C_Err_BCL; //Will need to reset I2C interface.
    }

    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=16MIPS), I expect <=40.
    while(I2C2CONbits.PEN) //HW cleared when complete
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

    if(I2C2STATbits.TBF) //Is there already a uint8_t waiting to send?
    {
        return I2C_Err_TBF;
    }

    I2C2TRN = cData; //Send uint8_t
    //Transmission takes several clock cycles to complete.  As a result we won't see BCL error for a while.
    t = 0; //Timeout is processor speed dependent.  @(4*8Mhz=32Mhz;16MIPS) and 8 bits, I expect <=320.

    while(I2C2STATbits.TRSTAT) //HW cleared when TX complete
    {
        t++;

        if(t > 8000)
        {//This is bad because TRSTAT will still be set
            return I2C_Err_SCL_low; //Must reset I2C interface, and possibly slave devices
        }
    }//Testing: t=31

    if(I2C2STATbits.BCL)
    {
        I2C2STATbits.BCL = 0; //Clear error to regain control of I2C
        return I2C_Err_BCL;
    }

    //Done, now how did slave respond?
    if(I2C2STATbits.ACKSTAT) //1=NACK
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
        I2C2_SCL_SetDigitalOutput();
        I2C2_SCL_SetDigitalInput();
    }
}