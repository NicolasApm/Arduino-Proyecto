#define DEBUG_ARRAY(a) {for (int index = 0; index < sizeof(a) / sizeof(a[0]); index++)   {Serial.print(a[index]); Serial.print('\t');} Serial.println();};
#include <SoftwareSerial.h>

SoftwareSerial ModBluetooth(2, 3); // RX | TX

String str = "";
String Salida;
const int dataLength =0 ;
String Error="ErrorLength";
String data [dataLength];
String SerialString="";
const char separator = ',';
int b=0;
//int data[dataLength];

char VarChar;
void setup()
{
  ModBluetooth.begin(9600);
  Serial.begin(9600);
}

void loop()
{
      if (Serial.available() >= 0) {
    //Se crea una variable que servirá como buffer
    String bufferString = "";
        String bufferString2 = "";

    /*
     * Se le indica a Arduino que mientras haya datos
     * disponibles para ser leídos en el puerto serie
     * se mantenga concatenando los caracteres en la
     * variable bufferString
     */
    while (Serial.available() > 0) {
      bufferString += (char)Serial.read();
    }
    //Se imprime el contenido del buffer
    bufferString2+=bufferString+',';
    Serial.print(bufferString2);
  } 
        
    /*if (ModBluetooth.available()){
    GameCompare();}*/
}

void GameCompare(){
//str = Serial.readStringUntil('\n');
    str = ModBluetooth.readStringUntil('\n');
    for (int i = 0; i < 2 ; i++)
    {
      int index = str.indexOf(separator);
      //data[i] = str.substring(0, index).toInt();
      //data[i] = str.substring(0, index);
      data[i] = str.substring(0, index);
      str = str.substring(index + 1);
    }
    
   // DEBUG_ARRAY(data[0]+""+data[2]);
    if (data[0].equals("5")&&data[2].equals("a")) {
      Salida="11,22,33,44,a";
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      ModBluetooth.print(Salida);
      ModBluetooth.print("#");  
    }
    else if (data[0].equals("5")&&data[2].equals("b")) {
      Salida="22,23,33,34,b";
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      ModBluetooth.print(Salida);
      ModBluetooth.print("#");  
    }
      else if (data[0].equals("5")&&data[2].equals("c")) {
      Salida="11,33,32,34,c";
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      ModBluetooth.print(Salida);
      ModBluetooth.print("#");  
    }

    else{
      ModBluetooth.print(Error);
      ModBluetooth.print("#");
      } 

      //else{DEBUG_ARRAY("eroor")}
    
    //DEBUG_ARRAY(data);
}
