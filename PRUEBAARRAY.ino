#define DEBUG_ARRAY(a) {for (int index = 0; index < sizeof(a) / sizeof(a[0]); index++)   {Serial.print(a[index]); Serial.print('\t');} Serial.println();};
#include <SoftwareSerial.h>
#include <Keypad.h>

SoftwareSerial ModBluetooth(2, 3); // RX | TX

String str = "";
String Salida;
String Error = "ErrorLength";

int b = 0;
int count = 0;
int value = 0;

const int dataLength = 0 ;
const int inputPin = 12;
const byte rowsCount = 4;
const byte columsCount = 4;
const byte rowPins[rowsCount] = { 11, 10, 9, 8 };
const byte columnPins[columsCount] = { 7, 6, 5, 4 };

char array2[32];
char My_Array[16];
char C;
char keys[rowsCount][columsCount] = {
  { '1', '2', '3', 'a' },
  { '4', '5', '6', 'b' },
  { '7', '8', '9', 'c' },
  { '*', '0', '#', 'd' }
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);
void setup()
{

  pinMode(inputPin, INPUT);
  ModBluetooth.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  //
  //cuando se presiona una tecla se guarda en la variable C tipo char
  C = keypad.getKey();
  //Boton para captura de datos
  button();
  if (C) {
    //Encender leds de botones
    OnLeds(C);
    //Iniciar logica de captura de datos
    GameInsertData(value);
  }

  /*if (Serial.available() > 0) //something is there to be read
    {
    //GameInsertData();
    }*/

  if (ModBluetooth.available()) {
    GameCompare();
  }
}

void GameInsertData(int value1) {

  if (value1 == LOW)
  {
    value1 = HIGH;
    int i = 0;
    for (int i = 0; i < sizeof(My_Array); i++) {
      //Serial.print(My_Array[i]);
    }
    int b = 0;
    for (int i = 0; i < count; i++) {
      array2[b++] = My_Array[i];
      array2[b++] = ',';
    }
    for (int i = 0; i < (count * 2) - 1; i++) {
      //Serial.print(array2[i]);
      Salida += array2[i];
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
  else if (str.equals("3a")) {
    //Salida = "1,2,3";
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  else if (str.equals("4b")) {
    //Salida = "1,2,3";
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
   else if (str.equals("5c")) {
    //Salida = "1,2,3";
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
  Salida = "";
}

void OnLeds(char C) {
  switch (C) {
    case '1':
      Serial.print("1");
      break;
    case '2':
      Serial.print("2");
      break;
    case '3':
      Serial.print("3");
      break;
    case '4':
      Serial.print("4");
      break;
    case '5':
      Serial.print("5");
      break;
    case '6':
      Serial.print("6");
      break;
    case '7':
      Serial.print("7");
      break;
    case '8':
      Serial.print("8");
      break;
    case '9':
      Serial.print("9");
      break;
    case '0':
      Serial.print("0");
      break;
    case 'a':
      Serial.print("b");
      break;
    case 'c':
      Serial.print("c");
      break;
    case 'd':
      Serial.print("d");
      break;
    case '*':
      Serial.print("*");
      break;
    case '#':
      Serial.print("#");
      break;
  }
}
//nuevo
void button() {
  value = digitalRead(inputPin);
  //lectura digital de pin
  delay (100);
  if (value == HIGH) {
    //Serial.println("Encendido");
  }
  else {
    delay (300);
    value = LOW;
    //Serial.println("Apagado");
    GameInsertData(value);
    value = 0;
  }
  //delay(1000);
}
