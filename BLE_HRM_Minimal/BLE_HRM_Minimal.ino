/*
 * Gerken80
 * 31 May 2022
 * 
 * Minimum code I could use to get my Garmin Fenix 6X Pro, and Iphone using BLE Advertiser to 
 * display Heart Rate on the Serial Monitor.
 * 
 * There is not much error handeling in this code, so it would not be reliable.
 * It does however, make it easy to work out what is going on!
 * 
 * The Heart rate is located in the second, and third Least Significant Bytes if over 255BPM.
 * The Lowest Byte contains Flag Data that tells you what is included in the remaining bytes.
 */

#include <ArduinoBLE.h>

void setup() {

  startSerial();

  BLE.begin();

  BLE.scanForUuid("180d");
}

void loop() {
  BLEDevice HRMservice = BLE.available();

  if (HRMservice) {
    if (HRMservice.advertisedServiceUuid() == "180d") {
      BLE.stopScan();
      HRMservice.connect();
      HRMservice.discoverAttributes();

      BLECharacteristic HRMcharacteristic = HRMservice.characteristic("2a37");
      HRMcharacteristic.subscribe();
      
      while (HRMservice.connected()) {
        uint8_t byteArrayLength = HRMcharacteristic.valueLength();
        Serial.println();
        Serial.print("Bytes: ");
        Serial.println(byteArrayLength, DEC);
        uint8_t HRMarray[byteArrayLength];
        HRMcharacteristic.readValue(HRMarray, byteArrayLength);

        for (int i = 0; i < byteArrayLength; i++) {
          Serial.println("HEX         BIN         DEC");
          Serial.print(HRMarray[i], HEX);
          Serial.print("              ");
          Serial.print(HRMarray[i], BIN);
          Serial.print("              ");
          Serial.println(HRMarray[i], DEC);
        }
        delay(1000);
      }
    }
  }

  BLE.scan();
  delay(1000);
}

void startSerial() {
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("-----------------------------");
  Serial.println("Serial Connection Established");
  Serial.println("-----------------------------");
}
