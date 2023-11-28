/*
Engenharia de Computação - UPF
Comunicação de dados em Aplicações Embarcadas
Marcelo Trindade Rebonatto
28/10/2023
Server Inicial BLE
Adaptado de Based on Neil Kolban example for IDF: 
    https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "models/MyCharacteristicCallbacks.cpp"
#include "models/MyServerCallbacks.cpp"

#include "constants/characteristics.h"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID            "4fafc201-1fb5-459e-8fcc-c5c9c331914b"


//Descritor para a característica de notificação
BLEDescriptor notifyDescriptor(BLEUUID((uint16_t)0x2902));

BLECharacteristic *pCharacteristic; /* Objeto para uma Caracteristica */

int valueToBeNotified = 0;

void setup() {
    delay(1000);
    Serial.begin(9600);
    BLEServer *pServer;                 /* Objeto para o Servidor BLE */
    BLEService *pService;               /* Objeto para o Servico */
    BLEAdvertising *pAdvertising;       /* Objeto para anuncio de Servidor */

    /* Servidor */
    Serial.println("Iniciando o Servidor BLE");

    BLEDevice::init("Homero BLE");
   
    pServer = BLEDevice::createServer();

    /* Criando o Serviço */
    pService = pServer->createService(SERVICE_UUID);
    
    /* Criando e Ajustando a caracteristica */
    pCharacteristic = pService->createCharacteristic(
                          CHARACTERISTIC_UUID,
                          BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | 
                          BLECharacteristic::PROPERTY_NOTIFY
                          );

    pCharacteristic->setValue("Hello World de BLE Homero");

    /* Adicionando funções de Callback */
    // Adiciona funcionalidades de manipulação da característica
    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

    // Adiciona funcionalidades de manipulação do servidor
    pServer->setCallbacks(new MyServerCallbacks());

    Serial.println("Caracteristica definida!");

    /* Iniciando o Servico */
    pService->start();

    /* Criando e configurando o anuncio */
    pAdvertising = BLEDevice::getAdvertising();
    // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    /* Inicia o anúncio */
    BLEDevice::startAdvertising();
    Serial.println("Anuncio configurado e iniciado. Pode-se conectar e ler do Cliente");

    notifyDescriptor.setValue("Valor incrementado");
    pCharacteristic->addDescriptor(&notifyDescriptor);
}

void loop() {
    delay(random(1993, 2017));

    //Comentado para o funcionamento com o aplicativo
    //pCharacteristic->setValue(valueToBeNotified);
    pCharacteristic->notify();

    valueToBeNotified++;

}