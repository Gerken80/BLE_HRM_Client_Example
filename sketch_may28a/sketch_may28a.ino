
uint32_t testData = 0xFF00FF06;
uint16_t heartRate16;
uint8_t heartRate8;


void setup() {
  bool HRDataSize16;
  
  startSerial();
  Serial.println(testData, BIN);
  Serial.println(testData, HEX);
  HRDataSize16 = flagData(testData);
  if (!HRDataSize16){
    heartRate8 = testData >> 8;
    Serial.print("8 bit Heart rate is: ");
    Serial.println(heartRate8, DEC);
  } else {
    heartRate16 = testData >> 8;
    Serial.print("16 bit Heart rate is: ");
    Serial.println(heartRate16, DEC);
}
}

void loop() {

}

void startSerial(){
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Serial Connection Established");
  Serial.println();
}

bool flagData(uint8_t testData){
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
  return HRValueFormat;
}
