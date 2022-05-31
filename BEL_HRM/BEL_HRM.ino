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
        flagData(HRMarray[0]);
        delay(5000);
      }
    }
  }

  BLE.scan();
  delay(1000);
}

void flagData(uint8_t testData){
  bool HRValueFormat;
  bool sensorContactDetected;
  bool sensorContactSupported;
  bool energyExpendedSupported;
  bool RRIntervalsPresent;
  bool reserved5;
  bool reserved6;
  bool reserved7;
  
  HRValueFormat = bitRead(testData, 0);
  sensorContactDetected = bitRead(testData, 1);
  sensorContactSupported = bitRead(testData, 2);
  energyExpendedSupported = bitRead(testData, 3);
  RRIntervalsPresent = bitRead(testData, 4);

  Serial.println("------------------FLAG DATA----------------");
  switch (HRValueFormat) {
    case 0:
      Serial.println("Heart Rate Value set to uint8_t");
    break;
    case 1:
      Serial.println("Heart Rate Value set to unit16_t");
     break;
  }

  switch (sensorContactDetected) {
    case 0:
      Serial.println("Sensor Contact Not Detected");
    break;
    case 1:
      Serial.println("Sensor Contact Is Detected");
     break;
  }

  switch (sensorContactSupported) {
    case 0:
      Serial.println("Sensor Contact Is Not Supported");
    break;
    case 1:
      Serial.println("Sensor Contact Is Supported");
     break;
  }

  switch (energyExpendedSupported) {
    case 0:
      Serial.println("Energy Expended Is Not Supported");
    break;
    case 1:
      Serial.println("Energy Expended Is Supported");
     break;
  }

    switch (RRIntervalsPresent) {
    case 0:
      Serial.println("RR Intervals Are Not Present");
    break;
    case 1:
      Serial.println("RR Intervals Not Present");
     break;
  }
  Serial.println("-------------------------------------------------");
}


void startSerial() {
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("-----------------------------");
  Serial.println("Serial Connection Established");
  Serial.println("-----------------------------");
}
