#include <SoftwareSerial.h> //Librería que permite establecer comunicación serie en otros pins

//Aquí conectamos los pins RXD,TDX y KEY del módulo Bluetooth.
SoftwareSerial BT(8, 9); //8 RX, 9 TX.
#define KEY_PIN 7        //7 pin KEY nos permite entrar en modo comandos AT


void enviar_comando_AT(String comando) {
  Serial.println(comando);
  BT.println(comando); delay(250);

  while (BT.available())
  {
    Serial.print(char(BT.read()));
  }

}

void setup()
{
  // Entramos en modo comandos AT para configurar nuestro módulo bluetooth
  pinMode(KEY_PIN, OUTPUT);
  digitalWrite(KEY_PIN, HIGH); delay(500);

  BT.begin(9600);     //Velocidad del puerto del módulo Bluetooth
  Serial.begin(9600); //Abrimos la comunicación serie con el PC y establecemos velocidad

  Serial.println("Configuracion AT");
  enviar_comando_AT("AT");

  Serial.println("Version:");
  enviar_comando_AT("AT+VERSION");

  Serial.println("Nombre dispositivo:");
  enviar_comando_AT("AT+NAME=test_arduino");

  //Cerramos el modo comandos AT
  digitalWrite(KEY_PIN, LOW); delay(500);

}


// Este loop() sencillo únicamente permite recibir o enviar datos por el puerto serie del módulo bluetooth
void loop()
{
  if (BT.available())
  {
    Serial.write(BT.read());
  }

  if (Serial.available())
  {
    BT.write(Serial.read());
  }
}
