#define DEBUG_ARRAY(a) {for (int index = 0; index < sizeof(a) / sizeof(a[0]); index++)   {Serial.print(a[index]); Serial.print('\t');} Serial.println();};
#include <SoftwareSerial.h>

SoftwareSerial ModBluetooth(2, 3); // RX | TX

String str = "";
String Salida;
const int dataLength = 0 ;
String Error = "ErrorLength";
String data [dataLength];
String SerialString = "";
const char separator = ',';
char array2[32];
char My_Array[16];
int b = 0;
int count = 0;

void setup()
{
  ModBluetooth.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0) //something is there to be read
  {
GameInsertData();
  }

  if (ModBluetooth.available()) {
    GameCompare();
  }
}


void GameInsertData() {
  char C = Serial.read();

  if (C == '.')
  {
    int i = 0;
    /*while (i != count)
      {
      //Serial.print(My_Array[i++]);
      My_Array[i++];
      }*/

    for (int i = 0; i < sizeof(My_Array); i++) {
      //Serial.print(My_Array[i]);
    }
    int b = 0;
    for (int i = 0; i < count; i++) {


      array2[b++] = My_Array[i];
      array2[b++] = ',';

    }
    //  for (int i = 0; i < sizeof(array2); i++) {
    //Serial.print(array2[i-1]);
    //}
    for (int i = 0; i < (count * 2) - 1; i++) {
      //Serial.print(array2[i]);
       Salida+=array2[i];
    }
   Serial.print(Salida);
   count = 0;
  }
  else  My_Array[count++] = C;

}

void GameCompare() {

  str = ModBluetooth.readString();

  if (str.equals("41")) {
   // String Salida = "a,f,k,p";
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    Serial.print(Salida);
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  else if (str.equals("42")) {
   // String Salida = "f,g,k,p";
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  else if (str.equals("53")) {
   // Salida = "a,k,j,l,p";
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }

  else {
    ModBluetooth.print(Error);
    ModBluetooth.print("#");
  }
  Salida="";

  //else{DEBUG_ARRAY("eroor")}

  //DEBUG_ARRAY(data);
}
