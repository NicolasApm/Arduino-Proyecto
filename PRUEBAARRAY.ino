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
int b = 0;
//int data[dataLength];

char VarChar;
void setup()
{
  ModBluetooth.begin(9600);
  Serial.begin(9600);
}

void loop()
{

  if (ModBluetooth.available()) {
    GameCompare();
  }
}

void GameCompare() {

  str = ModBluetooth.readString();

  if (str.equals("41")) {
    String Salida = "a,f,k,p";
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  else if (str.equals("42")) {
    String Salida = "f,g,k,p";
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  else if (str.equals("53")) {
    Salida = "a,k,j,l,p";
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

  //else{DEBUG_ARRAY("eroor")}

  //DEBUG_ARRAY(data);
}
