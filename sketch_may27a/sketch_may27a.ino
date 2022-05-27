#include <ArduinoBLE.h>

void setup() { 
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("BLE Fail");
    while (1);
  }

  Serial.println("Ready to scan");
  BLE.scanForUuid("180d"); 
}

void loop() {
  BLEDevice foundDevice = BLE.available();
  
  if (foundDevice){
    Serial.println("Available"); 
  }
  
   if (foundDevice.advertisedServiceUuid() == "180d") {
    BLE.stopScan();
    foundDevice.connect();
    
    Serial.println(foundDevice.localName());
    Serial.println("Connecting");
    
    while (foundDevice.connected()){
      Serial.println("Connected");
      delay(1000); 
    }
    
  }
  
  Serial.println("Disconected");
  BLE.scan();
  delay(1000); 
}
