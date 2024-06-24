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

 // BLE.scanForName("Polar H10 B19EF220");

}
void loop() {
 // begin initialization
 

    // start scanning for peripheral
  BLE.scanForName("Polar H10 B19EF220");

  

  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    BLE.stopScan();
    
    Serial.println("Connecting ...");

    if (peripheral.connect()) {
      Serial.println("Connected");
      
    } else {
      Serial.println("Failed to connect!");
      return;
    }

    // discover peripheral attributes
    Serial.println("Discovering attributes ...");
    if (peripheral.discoverAttributes()) {
      Serial.println("Attributes discovered");
    } else {
      Serial.println("Attribute discovery failed!");
      peripheral.disconnect();
      return;
    }

    BLEService PMDservice = peripheral.service("FB005C80-02E7-F387-1CAD-8ACD2D8DF0C8");
    

    if (PMDservice) {
      Serial.println("Yep");
      BLECharacteristic control = peripheral.characteristic("FB005C81-02E7-F387-1CAD-8ACD2D8DF0C8");
      BLECharacteristic data = peripheral.characteristic("FB005C82-02E7-F387-1CAD-8ACD2D8DF0C8");
      BLEDescriptor des = data.descriptor(0);
      data.subscribe();


      if (control) {
        uint8_t b[2] = {0x02, 0x00};
        uint8_t c[10] = {0,0,0,0,0,0,0,0,0,0};
        byte a;
        
        des.readValue(a);
        Serial.println(a);
        
        des.readValue(a);
        Serial.println(a);
        control.writeValue(b,2);
        data.readValue(c, 10);
        
        while(1){
        Serial.println(c[0], HEX);
        Serial.println(c[1], HEX);
        Serial.println(c[2], HEX);
        Serial.println(c[3], HEX);
        Serial.println(c[4], HEX);
        Serial.println(c[5], HEX);
        Serial.println(c[6], HEX);
        Serial.println(c[7], HEX);
        Serial.println(c[8], HEX);
        Serial.println(c[9], HEX);
        }
        peripheral.disconnect();
        delay(10000);
      } else {
        Serial.println("Peripheral does NOT have battery level characteristic");
      }
    } else {
      Serial.println("Peripheral does NOT have battery service");
    }

  }
}

void startSerial() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("-----------------------------");
  Serial.println("Serial Connection Established");
  Serial.println("-----------------------------");
}
