/* 
 * File:   millis.c
 * Author: raphael.pereira
 *
 * Created on May 20, 2021, 5:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/interrupt_manager.h"

#include "millis.h"

volatile uint8_t timer_fract = 0;
volatile uint32_t _micros = 0;
volatile uint32_t _millis = 0;
volatile uint32_t timer_overflow_count = 0;

uint32_t micros()
{
    //INTERRUPT_GlobalInterruptDisable();
    //_micros = 1000 * _millis + (1000 * TMR0) / timer0ReloadVal;
    //INTERRUPT_GlobalInterruptEnable();
    
    return (_micros);
}

uint32_t micros_from_interrupt()
{
    //_micros = 1000 * _millis + (1000 * TMR0) / timer0ReloadVal;

    
    return (_micros);
}

uint32_t millis()
{
    volatile uint32_t m;

    // disable interrupts while we read timer0_millis or we might get an
    // inconsistent value (e.g. in the middle of a write to timerx_millis)
    INTERRUPT_GlobalInterruptDisable();
    m = _millis;
    INTERRUPT_GlobalInterruptEnable();
    
    return m;
}

uint32_t millis_from_interrupt()
{
    return _millis;
}

void increment_interrupt()
{
    _millis++;
}
