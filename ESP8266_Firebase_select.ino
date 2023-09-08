/*

Ejemplo para recuperar un dato de la base

*/

#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

/* 1. Definir las credenciales de WiFi */
#define WIFI_SSID "<Red WiFi>"
#define WIFI_PASSWORD "<passwd>"

/* 2. Define las credenciales de Firebase */
#define FIREBASE_HOST "<datos de la base>" //<databaseName>.firebaseio.com o <databaseName>.<region>.firebasedatabase.app
#define FIREBASE_AUTH "<passwd>"
 
FirebaseData firebaseData1;
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

  if (!Firebase.beginStream(firebaseData1, "/ejemplo"))     // base y dato a recuperar
  {
      Serial.println("Could not begin stream");
      Serial.println("REASON: " + firebaseData1.errorReason());
      Serial.println();
  }

}

void loop() {
  if (!Firebase.readStream(firebaseData1))
    {
        Serial.println();
        Serial.println("Can't read stream data");
        Serial.println("REASON: " + firebaseData1.errorReason());
        Serial.println();
    }

    if (firebaseData1.streamTimeout())
    {
        Serial.println();
        Serial.println("Stream timeout, resume streaming...");
        Serial.println();
    }

    if (firebaseData1.streamAvailable())
    {

        // muestro por el monitor serial el dato recuperado
        String res = firebaseData1.dataType() ;
        Serial.println(res);
        int numero = firebaseData1.intData();
        Serial.println(numero);
        if (firebaseData1.dataType() == "boolean")
        {
            bool data = firebaseData1.boolData();
            Serial.println(data);
        }
    }

}
