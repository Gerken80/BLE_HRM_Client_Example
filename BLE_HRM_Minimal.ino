/*
 * Gerken80
 * 23 May 2022
 * 
 * Absolute minimum code I could use to get my Garmin Fenix 6X Pro to 
 * display Heart Rate on the Serial Monitor.
 * 
 * There is no error handeling in this code, so it would not be reliable.
 * It does however, make it easy to work out what  is going on!
 * 
 * The data is sent in 2 bytes, 16 bits "XXXX YYYY". It is the high byte "XXXX", that contains 
 * the heart rate value.
 */

#include <ArduinoBLE.h>
  
void setup() {
  
  Serial.begin(9600);

  BLE.begin();

  BLE.scanForUuid("180d");
 
}

void loop() {
  
  BLEDevice HRMservice = BLE.available();
  
  if (HRMservice){
    
    BLE.stopScan();
    HRMservice.connect();
    HRMservice.discoverAttributes();
    
    BLECharacteristic HRMchar = HRMservice.characteristic("2a37");
    HRMchar.subscribe();
    
    uint16_t HRMrawData;
    uint8_t HRMdata;
    
    while (HRMservice.connected()){
      
      HRMchar.readValue(HRMrawData);
      HRMdata = highByte(HRMrawData);
      
      Serial.println(HRMdata, DEC);
      
      delay(1000);
    }
  }
  
    BLE.scan();
    delay(100);
}
