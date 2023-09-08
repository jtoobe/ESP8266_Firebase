/*
Ejemplo de subida de datos a Firebase

*/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

/* 1. Definir las credenciales de WiFi */
#define WIFI_SSID "<Red WiFi>"
#define WIFI_PASSWORD "<passwd>"

/* 2. Define las credenciales de Firebase */
#define FIREBASE_HOST "<datos de la base>" //<databaseName>.firebaseio.com o <databaseName>.<region>.firebasedatabase.app
#define FIREBASE_AUTH "<passwd>"

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print(".");
      delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}


//Definir objetos de datos de Firebase
FirebaseData firebaseData1; // este es el nombre de la base

int numero = 0;

void loop() {
  numero = numero +1;
  if (Firebase.setInt(firebaseData1, "/ejemplo",numero))   //  "/ejemplo" es el campo donde se alojara el dato enviado
  {
    Serial.println("Datos enviados correctamente");
  }
  else
  {
      Serial.println("Datos enviados con falla");
  }
  delay(2000);
}
