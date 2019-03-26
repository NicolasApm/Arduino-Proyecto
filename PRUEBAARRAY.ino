#define DEBUG_ARRAY(a) {for (int index = 0; index < sizeof(a) / sizeof(a[0]); index++)   {Serial.print(a[index]); Serial.print('\t');} Serial.println();};
//#include <SoftwareSerial.h>//libreria para recibir datos serial arduino uno
#define ModBluetooth Serial3//libreria para recibir datos serial arduino due pines 14 tx y 15rx
#include <Keypad.h>//libreria de teclado arduino

//SoftwareSerial ModBluetooth(2, 3); // RX | TX comunicacion modulo bluetooth

String str = "";
String Salida;
String Error = "ErrorLength";

int b = 0;
int count = 0;
int value = 0;

char array2[32];
char My_Array[16];
char C;

const int dataLength = 0 ;
const int inputPin = 12;
const byte rowsCount = 4;
const byte columsCount = 4;

char keys[rowsCount][columsCount] = {
  { '1', '2', '3', 'a' },
  { '4', '5', '6', 'b' },
  { '7', '8', '9', 'c' },
  { '#', '0', '*', 'd' }
};

byte rowPins[rowsCount] = { 11, 10, 9, 8 };//error de conversion base 64 (no pueden ser const)
byte columnPins[columsCount] = { 7, 6, 5, 4 };//error de conversion base 64 (no pueden ser const)

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
  /*if (Serial.available() > 0) //
    {
    //GameInsertData();
    }*/
  //preguntar si se reciben datos por el bluetooth
  if (ModBluetooth.available()) {
    //logica donde se recibe la longitud y se devuelve un string con la secuencia separada por ,
    GameCompare();
  }
}

//Funcion para concatenar datos agrupados por ,
void GameInsertData(int value1) {
  /*cuando el boton de captura de datos se oprime cambia de estado y se agrupan los datos
     en la variable salida (separados por ,)
  */
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
      Salida += array2[i];//concatenar datos de salida
    }
    //mostrar datos de salida
    Serial.print(Salida);

    count = 0;
  }
  else  My_Array[count++] = C;

}
/*la longitud de las secuencias del juego viene acompañado de un bit para diferenciar en caso
   de que se repitan. se agrupa en la variable str.
*/
void GameCompare() {
  str = ModBluetooth.readString();//variable de lectura de datos blutooth tipo string
  //nivel 1 de juego secuencia colores
  if (str.equals("41")) {
    // String Salida = "a,f,k,p";
    Serial.print(Salida);
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  //nivel 2 de juego secuencia colores
  else if (str.equals("42")) {
    // String Salida = "f,g,k,p";
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  //nivel 3 de juego secuencia colores
  else if (str.equals("53")) {
    // Salida = "a,k,j,l,p";
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  //nivel 1 de juego numeros
  else if (str.equals("3a")) {
    //Salida = "1,2,3";
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  //nivel 2 de juego numeros
  else if (str.equals("4b")) {
    //Salida = "1,2,3";
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  //nivel 3 de juego numeros
  else if (str.equals("5c")) {
    //Salida = "1,2,3";
    ModBluetooth.print(Salida);
    ModBluetooth.print("#");
  }
  else {
    ModBluetooth.print(Error);
    ModBluetooth.print("#");
  }
  //limpiar bariable de envio de datos
  Salida = "";
}
//funcion para encendido de leds
//
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
      Serial.print("a");
      break;
    case 'b':
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
//Funcion para preguntar por el estado del boton capturador de datos para enviar
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
