/* 
 * File:   my_clock.h
 * Author: raphael.pereira
 *
 * Created on December 4, 2023, 12:25 PM
 */

#ifndef MY_CLOCK_H
#define	MY_CLOCK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "mcc_generated_files/device_config.h"

#ifndef CLOCK_SystemFrequencyGet
#define CLOCK_SystemFrequencyGet()        (_XTAL_FREQ)
#endif

#ifndef CLOCK_PeripheralFrequencyGet
#if defined (__XC16__)
#define CLOCK_PeripheralFrequencyGet()    (CLOCK_SystemFrequencyGet() / 2)
#define FCY (CLOCK_SystemFrequencyGet() / 2)
#elif defined (__XC8)
#define CLOCK_PeripheralFrequencyGet()    (CLOCK_SystemFrequencyGet() / 4)
#define FCY CLOCK_PeripheralFrequencyGet()
#endif
#endif

#ifndef CLOCK_InstructionFrequencyGet
#if defined (__XC16__)
#define CLOCK_InstructionFrequencyGet()    (CLOCK_SystemFrequencyGet() / 2)
#elif defined (__XC8)
#define CLOCK_InstructionFrequencyGet()    (CLOCK_SystemFrequencyGet() / 4)
#endif
#endif
    
#ifdef	__cplusplus
}
#endif

#endif	/* MY_CLOCK_H */

