/*
 * File:   newmain.c
 * Author: David Olide
 *
 * Created on 3 de febrero de 2017, 12:16 PM
 */
//512 pulsos por reveoluci�n

#include <xc.h>
#include"pic18f25k80.h"
#include"configuration_bits.h"

#define max 16


unsigned int secuencia[]={0x07, 0x03, 0x0B, 0x09, 0x0D, 0x0C, 0x0E, 0x06};
unsigned int cont1s=0;
unsigned char cont5s=0;
unsigned char i=0;
unsigned char j=0;
unsigned char k=0,l=0,m=0;
unsigned char isr=0;
unsigned char voltaje,conv=0,conv2=0;
unsigned char g=0;
unsigned char rx[]={"               "};

unsigned char done[]={"DONE\n"};
//unsigned char p[]{"               "}
unsigned char ccw=1,on=0,terminoEvaluacion=0;
int rps=0;
int grados=0;
//////

void high_priority interrupt delay(void){

    if(TMR0IE&&TMR0IF)
    {
        TMR0IF=0;
        TMR0L=56;
        cont1s++;
        j++;
        //if(j>=3+voltaje/2)
        if(j>=(rps))//tiempo minimo de 600us por paso, 600us*4096pasos=2.4576segundos por revoluci�n velocidad m�xima
        //if(j>=61)
        {

        isr=1;
        }
    }

    if(cont1s>=5000){
      //RBx (led)e toggle
      cont1s=0;
      cont5s++;
    }
    else if(cont5s>=5){
      GO_DONE;
      cont5s=0;
    }
    if (RC1IF == 1 && RC1IE == 1) {
//
       RC1IF = 0;
       rx[k++]=RCREG1;
       //p[]=rx[];
       if(RCREG1=='\n')
       {
        conv=1;
        k=0;
       }

   }
}
void low_priority interrupt adc(void){
    if(ADIE&&(ADIF))
    {
        ADIF=0;

        voltaje=ADRESH;
    }
//	if ((TX1IE==1) && (TX1IF==1))
//	{
//		TX1IF=0;
//    		TXREG1=mensaje[m++];
//		if (mensaje[m]==0)
//		{
//			TX1IE=0;
//
//		}
//	}

}

void init(void)
{
    /////////////////////////////////////
    TXSTA1 = 0b00100000;
    RCSTA1 = 0b10010000;
    BAUDCON1=0b00000000;
    RC1IE = 1;
    RC1IP = 1;
    //TX1IE = 0;
    //TX1IP = 1;
    SPBRG1 = 12;
    RC1IF=1;
    //TX1IF=0;



    ////////////////////////////////////////


    GIE=1;
    GIEL=1;
    IPEN=1;	//Habilita niveles de interrupcion

    TMR0IP=1;   //Configura prioridad alta para TRM0
    TMR0IE=1;   //Habilita interrupci�n para TMR0
    TMR0IF=1;//OVERFLOW

    T0CON=0xC0;//2:1, 200us para la interrupci�n,
    TMR0L=56;


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

void getDatos(void)
{

    if(rx[0]=='T'&&rx[1]=='E'&&rx[2]=='M'&&rx[3]=='P'&&rx[4]=='L'&&rx[5]=='I'&&rx[6]=='M'&&rx[7]=='I'&&rx[8]=='T')
    {
        on=1;

        conv2=1;
    }
    if(rx[0]=='O'&&rx[1]=='N')
    {
        on=1;
        m=0;
        while(m<6)
        {
            if(TXIF==1)
            {
                TXIF=0;
                TXREG1=done[m++];
            }
        }
        conv2=1;


    }
    if(rx[0]=='O'&&rx[1]=='F'&&rx[2]=='F'&&on==1)
    {
        on=0;
        m=0;
        while(m<6)
        {
            if(TXIF==1)
            {
                TXIF=0;
                TXREG1=done[m++];
            }
        }
        conv2=1;
    }
    if(rx[0]=='R'&&rx[1]=='P'&&rx[2]=='S'&&rx[3]==':')
    {
            if(rx[6]=='.')
            {
                rps=(rx[4]-48)*100;
                rps=rps+(rx[5]-48)*10;
                rps=rps+(rx[7]-48);
                rps=732/rps;

                        m=0;
        while(m<6)
        {
            if(TXIF==1)
            {
                TXIF=0;
                TXREG1=done[m++];
            }
        }

                conv2=1;
            }

            if(rx[5]=='.')
            {
                rps=(rx[4]-48)*10;
                rps=rps+(rx[6]-48);
                rps=732/rps;

                        m=0;
        while(m<6)
        {
            if(TXIF==1)
            {
                TXIF=0;
                TXREG1=done[m++];
            }
        }

                conv2=1;
           }
    }
    if(rx[0]=='S'&&rx[1]=='T'&&rx[2]=='E'&&rx[3]=='P'&&rx[4]=='C'&&rx[5]=='W'&&rx[6]==':')
        {
                grados=(rx[7]-0x30)*100;
                grados=grados+(rx[8]-0x30)*10;
                grados=grados+(rx[9]-0x30);
                grados=grados*512/45;
                g=1;
                        m=0;
//        while(m<6)
//        {
//            if(TXIF==1)
//            {
//                TXIF=0;
//                TXREG1=done[m++];
//            }
//        }

                conv2=1;
        }
}

void clear(void)
{
        rx[0]=' ';
        rx[1]=' ';
        rx[2]=' ';
        rx[3]=' ';
        rx[4]=' ';
        rx[5]=' ';
        rx[6]=' ';
        rx[7]=' ';
        rx[8]=' ';
        rx[9]=' ';
        rx[10]=' ';
        rx[11]=' ';
        rx[12]=' ';
        rx[13]=' ';
        rx[14]=' ';
        rx[15]=' ';
}


void main(void) {




    init();
    while(1)
    {
      if(templimit<t){
          //if(isr==1)
          if(conv=1)
          {
              getDatos();
              conv=0;

          }
          if(conv2==1&&on==0)
          {
              conv2=0;
              clear();
          }

          if(isr==1&&on==1)
              {
                  if(conv2==1)
                  {
                      clear();
                      conv2=0;
                  }
              isr=0;
              j=0;
              if(ccw==1)
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
  //        if(on==1&&g==1&&)
  //        {
  //            g=0;
  //                            if(conv2==1)
  //                {
  //                    clear();
  //                    conv2=0;
  //                }
  //        }
          if(on==0&&g==1)
          {
              unsigned char temp;
              if(conv2==1)
                  {
                      clear();
                      conv2=0;
                  }
              for(temp=0;temp<=4096;temp++)
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
          g=0;

      }


      }
    }
    else{

      if(ADRESH=!voltaje){
        voltaje=ADRESH;
        PORTB=0;
        warning=2;
        TXIE=1;
      }
    }
}
