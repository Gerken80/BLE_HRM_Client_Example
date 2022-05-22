#include <ArduinoBLE.h>


void setup() {
Serial.begin(9600);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!"); // Change this to error light
  while (1);
  }

  BLE.scanForUuid("180d");
}

void loop() {
  // check if a peripheral has been discovered and allocate it
  BLEDevice hrperipheral = BLE.available();

  if (hrperipheral) {
  
    // discovered a peripheral, print out address, local name, and advertised service
    Serial.print(hrperipheral.localName());
    // Check if the peripheral is a hr monitor (uuid check)

    if (hrperipheral.advertisedServiceUuid() == "180d") {
      // stop scanning
      BLE.stopScan();
      Serial.println("got hr device scan stopped");

      // Start monitoring
      monitorSensor(hrperipheral);

      // peripheral disconnected, start scanning again
      BLE.scan();
    }
  }
  delay(500);
}


void monitorSensor(BLEDevice hrperipheral) {
//   connect to the peripheral
  Serial.println("Connecting ...");
  if (hrperipheral.connect()) {
    Serial.println("Connected");

  } else {
    Serial.println("Failed to connect!");
    return;
  } 

  // discover peripheral attributes
    Serial.println("Discovering attributes ...");
    if (hrperipheral.discoverAttributes()) {
      Serial.println("Attributes discovered");
    } else {
      Serial.println("Attribute discovery failed!");
      hrperipheral.disconnect();
      return;
    }
    
  // retrieve the HR characteristic
  BLECharacteristic heartrateCharacteristic = hrperipheral.characteristic("2a37");


if (heartrateCharacteristic.canWrite()){
   Serial.println("canWrite");}

if (heartrateCharacteristic.subscribe()){
   Serial.println("Subscribed");}
uint16_t rawdata; 
  while (hrperipheral.connected()) {
     if(heartrateCharacteristic.valueUpdated()){
      Serial.println("valueUpdated");}
      heartrateCharacteristic.readValue(rawdata);
      Serial.print("uint16_t Binary : ");
      Serial.println(rawdata, BIN);
uint8_t hr;
      hr = rawdata >> 8;
      Serial.print("uint8_t Binary  : ");
      Serial.println(hr, BIN);
      Serial.print("uint8_t Decimal : ");
      Serial.println(hr, DEC);
     delay(1000);
  }
  delay(500);
  Serial.println("Sensor disconnected!");
}
