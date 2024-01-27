/* 
 * File:   bitwise.h
 * Author: raphael.pereira
 *
 * Created on August 29, 2023, 2:55 PM
 */

#ifndef BITWISE_H
#define	BITWISE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
    
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

#ifdef	__cplusplus
}
#endif

#endif	/* BITWISE_H */