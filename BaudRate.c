//Función para cambiar el baud rate
//SYNC=0 BRGH=1 BRG16=0
void baud_config(unsigned int baud){
  switch(baud){
  case 2400:
  SPBRG=207;
  break;

  case 9600:
  SPBRG=51;
  break;

  case 19200:
  SPBRG=25;
  break;

  case 57600:
  SPBRG=8;
  break;
  }
}
