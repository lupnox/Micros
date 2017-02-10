/* 
 * File:   main.cpp
 * Author: Erick Martínez Villa A01226202
 * Practica: 1
 * Created on 31 de enero de 2017, 10:49 PM
 */

#include <xc.h>
#include <configuration_bits.h>
#include <pic18f25k80.h>
unsigned char flag;   

void delay();

int main(void) {

    TRISC=0x10;
    
    while(1){
        LATC=0b00001110; //0000 1110
        delay();
        LATC=0b00001101;//0000 1101
        delay();
        LATC=0b00001011;//0000 1011
        delay();
        LATC=0b00000111;//0000 0001
        delay();
        if(flag==1){
            LATC=0b00001011;//0000 1011
            delay();
            LATC=0b00001101;//0000 1011
            delay();
        }
    }
}

void delay()
{
    TMR0L=0;    
    T0CON=0x84;
    while(TMR0<62500){
        if(RC4==1){
            flag=1;
        }
        else{
            flag=0;
        }
    }
    T0CON=0;
    TMR0=0;
}