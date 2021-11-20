/*
 * File:   newmain.c
 * Author: Shri
 *
 * Created on 5 August, 2020, 9:06 AM
 */


#include <xc.h>

void main(void) {
    PORTA = 0xFF;
    WREG = 0x25;
    return;
}
