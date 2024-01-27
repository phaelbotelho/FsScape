/* 
 * File:   main.h
 * Author: raphael.pereira
 *
 * Created on July 27, 2022, 2:50 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include "my_clock.h"

#define OWN_ADDRESS 0x9996    // 802.15.4 short address of the Client (this node)
#define GW_ADDRESS 0x8266    // 802.15.4 short address of the Gateway

#define OWN_A_MSB 0x99
#define msg_n '9'

#define SHORT_CONNECT_INTERVAL 0x05
#define LONG_CONNECT_INTERVAL 0x17
#define SLEEP_INTERVAL 0xC8 // 0x05 = 15 s; 0x17 = 60 s; 0x64 = 5 min; 0xA5 = 7 min; 0xC8 = 10 min

void example1();
void example2();
void example3();

void handle_tx();
void handle_rx();

void mrf_set_timed_sleep();


#endif	/* MAIN_H */

