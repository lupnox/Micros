/*
 * File:   newmain.c
 * Author: David Olide
 *
 * Created on 3 de febrero de 2017, 12:16 PM
 */
//512 pulsos por reveolución

#include <xc.h>
#include"pic18f25k80.h"
#include"configuration_bits.h"

unsigned int secuencia[]={0x07, 0x03, 0x0B, 0x09, 0x0D, 0x0C, 0x0E, 0x06};//secuancia del motor a pasos
unsigned char i=0;
unsigned char j=0;
unsigned char isr=0;
unsigned char voltaje;

void high_priority interrupt delay(void){

    if(TMR0IE&&TMR0IF)
    {
        TMR0IF=0;
        TMR0L=44;
        GO_DONE=1;
        j++;

        if(j>=(3+voltaje*3/255))//tiempo minimo de 642us por paso, 642us*4096pasos=2.6296segundos por revolución velocidad máxima

        {

        isr=1;
        }
    }
    if(ADIE&&(ADIF))
    {
        ADIF=0;

        voltaje=ADRESH;

        

    }
        
}

void init(void)
{
    //TMR0=0;

    GIE=1;
    IPEN=1;	//Habilita niveles de interrupcion

    TMR0IP=1;   //Configura prioridad alta para TRM0
    TMR0IE=1;   //Habilita interrupción para TMR0
    TMR0IF=1;//OVERFLOW
    
    T0CON=0xC0;//prescaler 2:1
    TMR0L=44;//precargar un 44 para desbordar el timer en 212us

    
    ANSEL8=0;
    ANSEL10=0;
    ANSEL9=1;
    

    
    ADIF=1;///CONVERTION COMPLETED
    ADIE=1;//ENABLE INTERRUPT
    ADIP=0;//0=LOW PRIORITY, 1=HIGH PRIORITY
    ADCON0=0b00100100;
    ADCON1=0;
    ADCON2=0b00001001;
    ADON=1;//PRENDER ADC

    
    TRISB=0xF0;
}
  


    
void main(void) {
    

    
    


    init();
    while(1)
    {

        if(isr==1)
        {

            isr=0;
            j=0;
            if(RB5==0)
            {
            
        
            PORTB=secuencia[i];

            i++;
               if(i>=7)
                  {
                  i=0;   
                  }
            }
        else
        {
        PORTB=secuencia[i];

        i--;
           if(i<=0)
           {
           i=7;   
           }


        }
        


        }
        
        
    }
}