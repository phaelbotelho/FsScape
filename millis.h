/* 
 * File:   millis.h
 * Author: raphael.pereira
 *
 * Created on July 27, 2022, 2:35 PM
 */

#ifndef MILLIS_H
#define	MILLIS_H

#include <stdint.h>

#include "mcc_generated_files/tmr1.h"

//volatile uint8_t timer0ReloadVal;

uint32_t millis();
uint32_t micros_from_interrupt();
uint32_t micros();
uint32_t millis_from_interrupt();
void increment_interrupt();

#endif	/* MILLIS_H */

