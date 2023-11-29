#include <Arduino.h>
#include <BLEDevice.h>

class WListCharacteristicCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *writeCharacteristic, BLECharacteristic *readCharacteristic)
    {
        std::string value = writeCharacteristic->getValue();
        readCharacteristic->setValue(value);
    }
};

