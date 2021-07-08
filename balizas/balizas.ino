/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/
//importo las bibliotecas necesarias para las capacidades BLE.
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

//Luego, debe definir un UUID para el servicio y la característica.
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  // inicia la comunicación en serie a una velocidad de 115200 baudios.
  Serial.begin(115200);
  Serial.println("¡Iniciando la baliza BLE!");
  //esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_N12); N9 N6 N3 N0 P3 P6 P9 -12dBm a +9dBm

  //Luego, crea un dispositivo BLE con un nombre determinado
  BLEDevice::init("ESP32-4");
  BLEServer *pServer = BLEDevice::createServer();   //configura el dispositivo BLE como servidor
  BLEService *pService = pServer->createService(SERVICE_UUID);    //crea un servicio para el servidor BLE con el UUID definido anteriormente.

  //Luego, establece la característica para ese servicio. 
  //También utiliza el UUID definido anteriormente y debe pasar como argumentos las propiedades de la característica. 
  //En este caso, es: LEER y ESCRIBIR.
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  //Despues de crear la caracteristica, se puede ajustar su valor
  pCharacteristic->setValue("Soy una baliza BLE");
  //Iniciar el sistema
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  //Funciones que ayudan con las conexiones a los moviles
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("¡Caracteristica definida!¡Ahora puedes leerla en tu movil!");
}

void loop() {
  delay(2000);
}
