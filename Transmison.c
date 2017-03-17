//Función de transmisión de mensajes según comando por medio de comunicación

TXSTA=0b00101100;
unsigned char msg1[]={68, 79, 9, 13, 10};
unsigned char msg2[]={79,86,69,82,84,69,77,80,69,82,65,84,85,82,69,32,68,68,69,84,69,67,84,69,68,33,13,10}
unsigned char warning=0;
unsigned char cursor=0;
//En ISR
//Habilitar TXIE en el main
if(TXIE==1&&TXIF==1){
  if(warning==1){
    TXREG=msg1[cursor++];
    if(cursor>4){
      TXIE=0;
      cursor=0;
      warning=0;
    }
  }
  else if(warning==2){
    TXREG=msg1[cursor++];
    if(cursor>26){
      TXIE=0;
      cursor=0;
      warning=0;
    }
  }
  else{
    TXIE=0;
    cursor=0;
    warning=0;
  }
}
