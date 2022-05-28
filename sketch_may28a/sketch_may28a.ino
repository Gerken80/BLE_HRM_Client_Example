uint32_t testData = 0b1000000110000110;
uint16_t heartRate16;
uint8_t heartRate8;
bool HRValueFormat;
bool sensorContactDetected;
bool sensorContactSupported;
bool energyExpendedSupported;
bool RRIntervalsPresent;
bool reserved5;
bool reserved6;
bool reserved7;

void setup() {
  startSerial();
  Serial.println(testData, BIN);
  flagData(testData);
}

void loop() {

}

void startSerial(){
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Serial Connection Established");
  Serial.println();
}

void flagData(uint8_t testData){
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
