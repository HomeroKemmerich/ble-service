#include <Arduino.h>
#include <BLEServer.h>
#include <BLEDevice.h>

class MyServerCallbacks: public BLEServerCallbacks {
    void onDisconnect(BLEServer* pServer) {
        Serial.println("Cliente desconectado");
        BLEDevice::startAdvertising();
    };
};