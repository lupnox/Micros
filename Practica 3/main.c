/*Programa para tercera practica del laboratorio de micros creado por Erick Martínez Villa A01226202*/

#include configuration_bits.h
#include <xc.h>
#include"pic18f25k80.h"
void delay(int voltage);
unsigned char counter=0;
unsigned char data;
unsigned int secuencia[]={0x07, 0x03, 0x0B, 0x09, 0x0D, 0x0C, 0x0E, 0x06};


void interrupt ISR(void){
TMR0IF = 0;             //Clears T0 interrupt flags
counter++;
TMR0L = 155; //Timer start value
TMR0ON = 1; //re enables timer
}

void delay(int voltage)
{
    unsigned int idle_time;
    /*Configuration of the timer to run as properly for our application
     Timer enabled
     8-bit timer configured
     Internal instruction cycle clock
     low-to-high transition
     prescaler assigned
     1:2 prescaler value (to get 1 micro-seconds for every change in the timer)*/

    T0CON = 0xD8;
    TMR0L = 155; //Timer start value

    idle_time=((timeParameter)*900)/255;

    TMR0ON=1;
    while(counter < idle_time){
    }

    TMR0ON = 0; //disable the timer
    counter=0;
}

void main(void){
  GIE=1;
  TMR0IE=1;
  ADCON0=0b00100100; //Choose AN9 channel for the ADC
  ADCON1=0; //Single line converter
  ADCON2=0b00010001; //Set left justification, 4TAD and Fosc/8 to measure the voltage every 4uS
  ADON=1;//Enables ADC
  TRISB=0xF0; //Set pins RB0:3 as digital output for the pin

  unsigned char k=0;

      while(1){
        GO_DONE=1;
        data=ADRESH;
        if (RB5==0){  //por default es pin de entrada
          PORTB=secuencia[k++];
          if (k==7) k=0;
          delay(data);
      }
      else{
        PORTB=secuencia[k--];
        if (k==0) i=7;
        delay(data);
      }

      }
}
