//Sketch de programa para controlar motor stepper por medio de comunicación serial

unsigned int secuencia[]={0x07, 0x03, 0x0B, 0x09, 0x0D, 0x0C, 0x0E, 0x06}; //Secuencia para el motor a pasos
unsigned char temp; //Initializes a variable of reference to compare the analog signal

void delay(unsigned char voltaje){
    /*Configuration of the timer to run as properly for our application
     Timer enabled
     16-bit timer configured
     Internal instruction cycle clock
     low-to-high transition
     prescaler assigned
     1:2 prescaler value (to get 1 micro-seconds for every change in the timer)*/
     cuenta=(((int)voltaje*10/255)*22)+1000; //Math operation that takes the ADC data and calculates the apropiate dalay time for the speed
     TMR0L=0; //No data loaded when the timer starts
     T0CON=0x80; //Timer configuration
     while(TMR0<=cuenta){ //Goes between 1 and 1.22 miliseconds
     }
     TMR0=0;//Turns timer off
     T0CON=0; //Clears the timer memory
}

void main(void) {
    ANSEL8=0; //Set RB1 as digital
    ANSEL10=0; //Sets RB0

    ADCON0=0b00100100; //Choose AN9 channel for the ADC
    ADCON1=0; //Single line converter
    ADCON2=0b00010001; //Set left justification, 4TAD and Fosc/8 to measure the voltage every 4uS

    ADON=1;//Enables ADC

    TRISB=0xF0; //Set pins RB0:3 as digital output to drive the motor
    GO_DONE=1; //Continuosly starts the ADC so we always have a reading
    while(1){

        if( ADRESH<temp){
          if(state==1){
            if(dir==0) //Si el boton se presiona gira a la derecha
            {
                PORTB=secuencia[i++]; //Asigna la secuencia
                delay(vel);
                if(i>=7) {i=0;}
            }
            else //Si el boton no esta presionado gira a la izquierda
            {
                PORTB=secuencia[i--]; //Asigna la secuencia
                delay(vel);
                if(i<=0){i=7;}
            }
          }
          else{
            while(step<grad){
              if(dir==0) //Si el boton se presiona gira a la derecha
              {
                  PORTB=secuencia[i++]; //Asigna la secuencia
                  step++;
                  delay(vel);
                  if(i>=7) {i=0;}
              }
              else //Si el boton no esta presionado gira a la izquierda
              {
                  PORTB=secuencia[i--]; //Asigna la secuencia
                  step++;
                  delay(vel);
                  if(i<=0){i=7;}
              }
          }
          step=0;
        }
      else{
        PORTB=0;
        message="Overtemperature detected";
      }
}
