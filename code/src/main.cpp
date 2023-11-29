#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <vector>

#include "models/MyServerCallbacks.cpp"

#include "constants/characteristics.h"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID            "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

BLECharacteristic *rwCharacteristic, *notifyCharacteristic, *readNotificationCharacteristic, *writeListCharacteristic, *readListCharacteristic;

std::vector<String> values{"Primeiro valor", "Segundo valor", "Terceiro valor", "Quarto valor", "Quinto valor", "Sexto valor", "Setimo valor", "Oitavo valor", "Nono valor", "Decimo valor"};

class RwCharacteristicCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0)
        {
            pCharacteristic->setValue(value);
        }
        if(pCharacteristic == writeListCharacteristic){
            readListCharacteristic->setValue(values[(int)value]);
        }
    }
};


//Descritor para a característica de notificação
BLEDescriptor notifyDescriptor(BLEUUID((uint16_t)0x2902));




int valueToBeNotified = 0, listIndex = 0;

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
    
    //#region Configuração das características
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
    readNotificationCharacteristic = pService->createCharacteristic(
                              READ_NOTIFICATION_CHARACTERISTIC,
                              BLECharacteristic::PROPERTY_READ
                              );
    notifyCharacteristic->setValue(valueToBeNotified);
    notifyCharacteristic->addDescriptor(&notifyDescriptor);

    //Lista
    writeListCharacteristic = pService->createCharacteristic(
                            WRITE_LIST_CHARACTERISTIC,BLECharacteristic::PROPERTY_WRITE
                            );
    readListCharacteristic = pService->createCharacteristic(
                            READ_LIST_CHARACTERISTIC,BLECharacteristic::PROPERTY_READ
                            );
    //#endregion
    



    /* Adicionando funções de Callback */
    rwCharacteristic->setCallbacks(new RwCharacteristicCallbacks());
    writeListCharacteristic->setCallbacks(new RwCharacteristicCallbacks());

    // Adiciona funcionalidades de manipulação do servidor
    pServer->setCallbacks(new MyServerCallbacks());


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
    
    if(valueToBeNotified % 5 == 0){
        readNotificationCharacteristic->setValue(valueToBeNotified);
        notifyCharacteristic->notify();
    }

    valueToBeNotified++;
}