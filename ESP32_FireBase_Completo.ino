#include <WiFi.h>
#include "FirebaseESP8266.h"


#define FIREBASE_HOST "jtoobe-esp-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "P5WeqXq01lsIiRfEcumQUc1vNbaX31GBX9VAvwcr"
#define WIFI_SSID "veterinarialascamelias"
#define WIFI_PASSWORD "cocorumba"

FirebaseData firebaseData;
String ruta = "/ESP32";


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectado al Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Conectado con IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);


  //----------------------------------------------
  //---------------Eliminar datos-----------------
  //----------------------------------------------

  Firebase.deleteNode(firebaseData, ruta + "/hijo");


  //----------------------------------------------
  //-------------Escritura de datos---------------
  // Usando la instruccion setXXXXX lo que hace 
  // es sobreescribir el dato existente
  //----------------------------------------------

  // Escribe un entero
  Firebase.setInt(firebaseData, ruta + "/numerico", 123);


  // Escribe un decimal;
  Firebase.setFloat(firebaseData, ruta + "/numerico", 123.55);

  // Escribe un binario
  Firebase.setBool(firebaseData, ruta + "/logico", true);

  // Escribe un texto
  Firebase.setString(firebaseData, ruta + "/texto", "Hola mundo");

  // Escribe un JSON
  String cadena = "Hola mundo con JSON";
  float numerico = 876.45;
  bool logico = true;

  FirebaseJson json;
  json.add("numerico", String(numerico));
  json.add("logico", String (logico));
  json.add("texto", cadena);
  Firebase.setJSON(firebaseData, ruta + "/json", json);



  //----------------------------------------------
  //---------------Lectura de datos---------------
  //----------------------------------------------

  //leer Entero
  Firebase.getInt(firebaseData, ruta + "/json/logico");
  Serial.println(firebaseData.intData());

  //leer Decimal
  Firebase.getFloat(firebaseData, ruta + "/json/numerico");
  Serial.println(firebaseData.floatData());

  //leer Texto
  Firebase.getString(firebaseData, ruta + "/json/texto");
  Serial.println(firebaseData.stringData());

  //leer JSON
  Firebase.getJSON(firebaseData, ruta + "/json");
  if (firebaseData.dataType() == "json") {
    Serial.println("JSON obtenido de Firebase:");
    Serial.println(firebaseData.jsonString());
  } else {
    Serial.println("Error al obtener valores del JSON");
  }





  //Serial.println(firebaseData.jsonData());

  //----------------------------------------------
  //----------------Push de datos-----------------
  // Usando la instruccion pushXXXXX lo que hace 
  // es insertar un nuevo dato en el nodo con una clave unica
  //----------------------------------------------

  //push Entero
  Firebase.pushInt(firebaseData, ruta + "/Push/entero", 123);

  //push Decimal
  Firebase.pushFloat(firebaseData, ruta + "/Push/entero", 123.55);

  //push String
  Firebase.pushString(firebaseData, ruta + "/Push/text", "asdsd");

  //push Binario
  Firebase.pushBool(firebaseData, ruta + "/Push/logico", false);

  //push JSON
  String JSONdata = "{\"numerico\":" + String(123) + ", \"logico\":" + String (true) + ", \"texto\":\"" + "Hola mundo JSON con push" + "\"}";
  //Firebase.pushJSON(firebaseData, ruta + "/Push/JSON", JSONdata);

  FirebaseJson jsonPush;
  jsonPush.add("numerico", String(numerico));
  jsonPush.add("logico", String (logico));
  jsonPush.add("texto", "Hola mundo JSON con push");
  Firebase.setJSON(firebaseData, ruta + "/Push/json", jsonPush);



  //----------------------------------------------
  //---------------Lectura de datos Push ---------
  //----------------------------------------------
  //leer JSON
  Firebase.getJSON(firebaseData, ruta + "/Push/entero");
  if (firebaseData.dataType() == "json") {
    Serial.println("JSON obtenido de Firebase:");
    Serial.println(firebaseData.jsonString());
  } else {
    Serial.println("Error al obtener valores del JSON push");
  }


  //----------------------------------------------
  //------------------Streaming-------------------
  //----------------------------------------------

  //streaming
  //Serial.println("Inicio de streaming");
  //Serial.println("RUTA: "+ruta + "/hijo/entero");
  //Firebase.beginStream(firebaseData, ruta + "/hijo/texto");

  //----------------------------------------------
  //-------------Finaliza la conexion-------------
  //----------------------------------------------

  //Firebase.end(firebaseData);
}

void loop()
{
  /*
    Firebase.setInt(firebaseData, ruta + "/numerico", 123);
    delay(1000);
    // Escribe un decimal;
    Firebase.setFloat(firebaseData, ruta + "/numerico", 123.55);
    delay(1000);
    // Escribe un binario
    Firebase.setBool(firebaseData, ruta + "/logico", false);
    delay(1000);
    Firebase.setBool(firebaseData, ruta + "/logico", true);
    delay(1000);
    // Escribe un texto corto
    Firebase.setString(firebaseData, ruta + "/texto", "Hola mundo");
    delay(1000);
    Firebase.setString(firebaseData, ruta + "/texto", "Hola enrique");
    delay(1000);*/

  /* Firebase.getInt(firebaseData, ruta + "/hijo/logico");
    Serial.println(firebaseData.intData());
    delay(1000);

    //leer Decimal
    Firebase.getFloat(firebaseData, ruta + "/hijo/numerico");
    Serial.println(firebaseData.floatData());
    delay(1000);

    //leer Texto
    Firebase.getString(firebaseData, ruta + "/hijo/texto");
    Serial.println(firebaseData.stringData());
    delay(1000);*/

  //----------------------------------------------
  //--------------Streaming de datos--------------
  //----------------------------------------------
  /*
    Firebase.readStream(firebaseData);
    if (firebaseData.streamAvailable())
    {
        Serial.println(firebaseData.stringData()); // El tipo de dato debe coincidir con el dato cargado en la nube
        delay(50);                                 // El delay es para que solo se haga una lectura, caso contrario repetira la lectura varias veces,
    }                                              // Si el loop es mas largo, no se requiere este delay.
    } */
}
