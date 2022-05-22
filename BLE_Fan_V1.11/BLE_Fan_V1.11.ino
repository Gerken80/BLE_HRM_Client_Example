#include <ArduinoBLE.h>

//Gerken80
//22 May 2022

void setup() {
  
  Serial.begin(9600);

  //Start BLE.
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
  while (1);
  }

  // BLE.scanForUuid looks only for a heart rate service. If found returns '1' "180d" is the BLE UUID for HRM(heart rate monitor) service.
  // Continualy scans until BLE.stopScan is given.
  BLE.scanForUuid("180d");
}

void loop() {

  // The heart rate data will be sent in the highest 8 bits of the unsigned 16 bit integer.
  // We will store extract them and store them in the unsigned 8 bit interger later.
  uint16_t rawdata;
  uint8_t hr;
  
  //Sets 'BLEclient' to be the BLEDevice returned by BLE.available, if we found a UUID on the scan 
  // If nothing found it leaves it alone.
  BLEDevice BLEclient = BLE.available();

  // If we have been succesfull in finding the HRM, and it is now BLEClient we will print some info about it.
  // If not just delay a while and try again.
  if (BLEclient) {
    // Stop the scan then print the advertised local name of the HRM we connected to.
    BLE.stopScan();
    
    Serial.println(BLEclient.localName());

    //Connect
    if (BLEclient.connect()) {
      Serial.println("Connected");

    //Find out what charicteristics we can use, we need to discover before we can use.
    if (BLEclient.discoverAttributes()){
      Serial.println("Attributes discovered");
    }else{
      BLE.disconnect();
    }
      
      
      // "2a37" is a standard BLE characteristic that sends the heart rate data within the '180d' service
      BLECharacteristic heartrateCharacteristic = BLEclient.characteristic("2a37");

      
      if (heartrateCharacteristic.subscribe()){
        Serial.println("Subscribed");}
        
      // While connected read HRM data. If disconenected restart scan, delay and start over.  
      while (BLEclient.connected()) {
        heartrateCharacteristic.readValue(rawdata);
        //Print the full 16 bits in binary so you can visualise the date that is being received
        Serial.print("uint16_t Binary : ");
        Serial.println(rawdata, BIN);

        // bit shift to the right 8 bits so the data we want is located where we need it.
        // this can also be done like this
        // highByte(rawdata);
        hr = rawdata >> 8;

        //Print the actual heart rate data we need to screen binary and decimal.
        Serial.print("uint8_t Binary  : ");
        Serial.println(hr, BIN);
        Serial.print("uint8_t Decimal : ");
        Serial.println(hr, DEC);

       //Wait some then repeat.
        delay(1000);
      }
      delay(500);
      Serial.println("Sensor disconnected!");
      BLE.scan();
    } else {
      Serial.println("Failed to connect!");
      BLE.scan();
    }
    
  }
  
  delay(500);
}






   
