//Librerias de MQTT
#if defined(ARDUINO_SAMD_MKR1000) or defined(ESP8266)
#define __SKIP_ESP32__
#endif

#if defined(ESP32)
#define __ESP32_MQTT_H__
#endif

#ifdef __ESP32_MQTT_H__
#include "esp32-mqtt.h"
#include <MQTT.h>
#include <MQTTClient.h>
//Librerias de wifi y google cloud
#include <Arduino.h>
#include <jwt.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>
//Librerias Bluetooth
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
//Libreria JSON
#include <ArduinoJson.h>

int tiempo = 3; //Tiempo del escaneo en segundos
int tamano = 4; // Tamaño de la matriz a recorrer
BLEScan* Sondeo; // Creacion de un escaner
int dato1, dato2, dato3, dato4; //señales(dB) de cada baliza
String direccion; //direccion MAC

//PINES GPIO MOTOR 1
int motor1Pin1 = 21; 
int motor1Pin2 = 19; 

//PINES MOTOR 2
int motor2Pin1 = 23; 
int motor2Pin2 = 22; 

 
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      
      direccion = advertisedDevice.getAddress().toString().c_str();  // Guarda la direccion actual
      if(direccion == "98:f4:ab:6e:56:22"){     //Comprueba que la dirrecion actual es la de la baliza, si es asi, guarda la señal BALIZA 1
        dato1 = advertisedDevice.getRSSI();
        Serial.printf("BALIZA 1 // Dirección: %s // Señal: %d \n\n", advertisedDevice.getAddress().toString().c_str(), dato1);
      }
      if(direccion == "98:f4:ab:6d:7c:ba"){     //Comprueba que la dirrecion actual es la de la baliza, si es asi, guarda la señal BALIZA 2
        dato2 = advertisedDevice.getRSSI();
        Serial.printf("BALIZA 2 // Dirección: %s // Señal: %d \n\n", advertisedDevice.getAddress().toString().c_str(), dato2);  
      }
      if(direccion == "fc:f5:c4:0f:66:22"){     //Comprueba que la dirrecion actual es la de la baliza, si es asi, guarda la señal BALIZA 3
        dato3 = advertisedDevice.getRSSI(); 
        Serial.printf("BALIZA 3 // Dirección: %s // Señal: %d \n\n", advertisedDevice.getAddress().toString().c_str(), dato3); 
      }
      if(direccion == "24:62:ab:d5:21:9e"){     //Comprueba que la dirrecion actual es la de la baliza, si es asi, guarda la señal BALIZA 4
        dato4 = advertisedDevice.getRSSI();  
        Serial.printf("BALIZA 4 // Dirección: %s // Señal: %d \n\n", advertisedDevice.getAddress().toString().c_str(), dato4);
      }
    }
};

void setup() {

  //Establecer los pines de salida
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  Serial.begin(115200); 
  setupCloudIoT(); //Conectar con google cloud

}

unsigned long lastMillis = 0;
void loop() {
  
   int baliza1[tamano][tamano];
   int baliza2[tamano][tamano];
   int baliza3[tamano][tamano];  
   int baliza4[tamano][tamano];
   int giro = 0;
   
   for (int i=0; i < tamano; i++)
    {
      for (int j=0; j < tamano; j++)
        { 
          /*----------------------- ESCANEA Y GUARDA LOS DATOS ---------------------------------------------*/
          if(giro!=1){
            Serial.print("Escaneando: Pos [");
            Serial.print(i);
            Serial.print(" - ");
            Serial.print(j);
            Serial.println("]");
          }else{
            Serial.print("Escaneando: Pos [");
            Serial.print(i);
            Serial.print(" - ");
            Serial.print(tamano-j-1);
            Serial.println("]"); 
          }
         
          BLEDevice::init("");
          Sondeo = BLEDevice::getScan(); // Realizar un sondeo.
          Sondeo->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
          Sondeo->setActiveScan(true); // Activar escaner consume mas energia.
          Sondeo->setInterval(100);
          Sondeo->setWindow(99); // debe ser menor/igual al valor setInterval.
          
          Sondeo->start(tiempo, false); // Escanea señales Bluetooth durante 3 segundos y las muestra. 
           /*Guarda la señal de cada baliza en su matriz*/
          if(giro!=1){ 
            baliza1[i][j] = dato1;
            baliza2[i][j] = dato2;  
            baliza3[i][j] = dato3;
            baliza4[i][j] = dato4;
          }else{
            baliza1[i][tamano-j-1] = dato1;
            baliza2[i][tamano-j-1] = dato2;  
            baliza3[i][tamano-j-1] = dato3;
            baliza4[i][tamano-j-1] = dato4;
          }
                  
          Sondeo->clearResults(); // Libera memoria del buffer para escanear.
          delay(1000);
         /*----------------------------------------------------------------------------*/
         /*------------------------------ RECORRIDO DEL ROBOT-----------------------------------*/
          if(j!= tamano-1){
            // Mueve el robot
            Serial.println("AVANZA");
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, HIGH); 
            digitalWrite(motor2Pin1, LOW);
            digitalWrite(motor2Pin2, HIGH); 
            delay(2000); 
            // Detiene el robot
            Serial.println("PARA");
            digitalWrite(motor1Pin1, LOW);
            digitalWrite(motor1Pin2, LOW);
            digitalWrite(motor2Pin1, LOW);
            digitalWrite(motor2Pin2, LOW);
            delay(1000);   
          }

          //Gira a la derecha o a la izquierda para recorerrer la matriz
          if(j == tamano-1 && i != tamano-1){  
            if(giro == 0){
              Serial.println("DERECHA");
              digitalWrite(motor1Pin1, LOW);
              digitalWrite(motor1Pin2, HIGH);
              delay(2000);
              digitalWrite(motor1Pin1, LOW);
              digitalWrite(motor1Pin2, LOW);
              delay(1000);
              digitalWrite(motor1Pin1, LOW);
              digitalWrite(motor1Pin2, HIGH); 
              digitalWrite(motor2Pin1, LOW);
              digitalWrite(motor2Pin2, HIGH); 
              delay(2000);
              digitalWrite(motor1Pin1, LOW);
              digitalWrite(motor1Pin2, LOW);
              digitalWrite(motor2Pin1, LOW);
              digitalWrite(motor2Pin2, LOW);
              delay(1000);
              digitalWrite(motor1Pin1, LOW);
              digitalWrite(motor1Pin2, HIGH);
              delay(2000);
              digitalWrite(motor1Pin1, LOW);
              digitalWrite(motor1Pin2, LOW);
              delay(1000);
              giro++; 
            }else{
              Serial.println("IZQUIEDA");
              digitalWrite(motor2Pin1, LOW);
              digitalWrite(motor2Pin2, HIGH);
              delay(2000);
              digitalWrite(motor2Pin1, LOW);
              digitalWrite(motor2Pin2, LOW);
              delay(1000);
              digitalWrite(motor1Pin1, LOW);
              digitalWrite(motor1Pin2, HIGH); 
              digitalWrite(motor2Pin1, LOW);
              digitalWrite(motor2Pin2, HIGH); 
              delay(2000);
              digitalWrite(motor1Pin1, LOW);
              digitalWrite(motor1Pin2, LOW);
              digitalWrite(motor2Pin1, LOW);
              digitalWrite(motor2Pin2, LOW);
              delay(1000);
              digitalWrite(motor2Pin1, LOW);
              digitalWrite(motor2Pin2, HIGH);
              delay(2000);
              digitalWrite(motor2Pin1, LOW);
              digitalWrite(motor2Pin2, LOW);
              delay(1000);
              giro = 0;
            }
          }
        }
    }
    /*----------------------------------------------------------------------------*/
    

    mqtt->loop();
    delay(10);  // <- fixes some issues with WiFi stability

    if (!mqttClient->connected()) {
      connect();
    }

    if (millis() - lastMillis > 10000) {
      lastMillis = millis();
     
      for (int i=0; i < tamano; i++){
        for (int j=0; j < tamano; j++){ 
          String json;
          DynamicJsonDocument doc(3000);
          doc["coord-x"] = i;
          doc["coord-y"] = j;
          doc["N-baliza"] = 4;
          JsonArray arr = doc.createNestedArray("balizas");
          if(dato1!= NULL){
            JsonObject obj = arr.createNestedObject();
            obj["id-abliza"] = "1";
            obj["pos-x"] = "14";
            obj["pos-y"] = "0";
            obj["distancia"]  =  sqrt(pow((i-14), 2) + pow((j-0), 2));
            obj["señal"] = baliza1[i][j];
          }
          if(dato2!= NULL){
            JsonObject obj2 = arr.createNestedObject();
            obj2["id-abliza"] = "2";
            obj2["pos-x"] = 1;
            obj2["pos-y"] = 1;
            obj2["distancia"]  =  sqrt(pow((i-14), 2) + pow((j-0), 2));
            obj2["señal"] = baliza2[i][j];
          }
          if(dato3!= NULL){
            JsonObject obj3 = arr.createNestedObject();            
            obj3["id-abliza"] = "3";
            obj3["pos-x"] = 1;
            obj3["pos-y"] = 1;
            obj3["distancia"]  =  sqrt(pow((i-14), 2) + pow((j-0), 2));
            obj3["señal"] = baliza3[i][j];
          }
          if(dato4 != NULL){
            JsonObject obj4 = arr.createNestedObject();
            obj4["id-abliza"] = "4";
            obj4["pos-x"] = 1;
            obj4["pos-y"] = 1;
            obj4["distancia"]  =  sqrt(pow((i-14), 2) + pow((j-0), 2));            
            obj4["señal"] = baliza4[i][j];
          }
          if(dato1 == NULL && dato2 == NULL && dato3 == NULL && dato4 == NULL){
            String mensaje=String("No hay datos disponibles en las coordenadas (")+i+String(",")+j+String(")");
            Serial.println(mensaje); 
          }
          serializeJson(doc, json);
          Serial.println(json);
          publishTelemetry(json); 
          delay(1000);  
        }
      }
   }

  
    /*VACIAR LOS ARRAYS*/
    memset(baliza1, 0, sizeof baliza1);
    memset(baliza2, 0, sizeof baliza2);
    memset(baliza3, 0, sizeof baliza3);
    memset(baliza4, 0, sizeof baliza4);
}
#endif
