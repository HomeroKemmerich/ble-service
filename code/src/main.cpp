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

BLECharacteristic *rwCharacteristic, *notifyCharacteristic;


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
    
    //Leitura e escrita
    rwCharacteristic = pService->createCharacteristic(
                          RW_CHARACTERISTIC,
                          BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
                          );

    rwCharacteristic->setValue("Primeiro valor");

    //Notificação
    notifyCharacteristic = pService->createCharacteristic(
                              NOTIFY_CHARACTERISTIC,
                              BLECharacteristic::PROPERTY_NOTIFY
                              );
    notifyCharacteristic->setValue(valueToBeNotified);
    notifyCharacteristic->addDescriptor(&notifyDescriptor);



    /* Adicionando funções de Callback */
    // Adiciona funcionalidades de manipulação da característica
    rwCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

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
}

void loop() {
    delay(random(1993, 2017));

    notifyCharacteristic->setValue(valueToBeNotified);
    
    if(valueToBeNotified % 5 == 0){
        notifyCharacteristic->notify();
    }

    valueToBeNotified++;
}