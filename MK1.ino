// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>
#include <SoftwareSerial.h>

SoftwareSerial ble(5, 6); // RX, TX  


void setup() {
  Serial.begin(115200);
  ble.begin(9600);
  while (!Serial);

  Serial.println("CAN Receiver Callback");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(100E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  CAN.onReceive(onReceive);

  startup();

}

void loop() {
  query(); 
  delay(15);
  endSignal();
  delay(100);
}

void startup() {
  sendLogStageInitial();
  delay(30);
  getPlcData();
  delay(120);
  setPlcStage1();
  delay(30);
  setPlcStage2();
  delay(30);
  setPlcStage3();
  delay(30);
  sendLogStageA();
  delay(120);
}

void danfossProbe() {
  CAN.beginExtendedPacket(0xCDB32F1);
  CAN.write(0x32);
  CAN.write(0x02);
  CAN.write(0x84);
  CAN.write(0x01);
  CAN.endPacket();  
  
  CAN.beginExtendedPacket(0x1BC78FFF);
  CAN.write(0x03);
  CAN.write(0x22);
  CAN.write(0xF0);
  CAN.write(0x10);
  CAN.endPacket();
}

void getPlcData() {
  Serial.println("send get PLC DATA QUERY");
  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05);
  CAN.write(0x02);
  CAN.write(0x1A);
  CAN.write(0x8A);
  CAN.endPacket();
  delay(5);
  endSignal();
}


void setPlcStage1() {
  Serial.println("send get PLC DATA QUERY");
  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05);
  CAN.write(0x02);
  CAN.write(0x10);
  CAN.write(0x87);
  CAN.endPacket();
}


void setPlcStage2() {
  Serial.println("send get PLC DATA QUERY");
  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05);
  CAN.write(0x02);
  CAN.write(0x27);
  CAN.write(0x01);
  CAN.endPacket();
}

void setPlcStage3() {
  Serial.println("send get PLC DATA QUERY");
  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05);
  CAN.write(0x02);
  CAN.write(0x27);
  CAN.write(0xFA);
  CAN.endPacket();
}

void sendLogStageA() {
  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05); 
  CAN.write(0x10); 
  CAN.write(0x2A); 
  CAN.write(0x27);  
  CAN.write(0xFB); 
  CAN.write(0x18); 
  CAN.write(0x8B); 
  CAN.write(0x28);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05); 
  CAN.write(0x21); 
  CAN.write(0xD6); 
  CAN.write(0x28);  
  CAN.write(0xE7); 
  CAN.write(0x23); 
  CAN.write(0x77); 
  CAN.write(0x1D);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05); 
  CAN.write(0x22); 
  CAN.write(0x92); 
  CAN.write(0x0D);  
  CAN.write(0xC7); 
  CAN.write(0x2F); 
  CAN.write(0xC4); 
  CAN.write(0x14);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05); 
  CAN.write(0x23); 
  CAN.write(0x6D); 
  CAN.write(0x1C);  
  CAN.write(0x96); 
  CAN.write(0x0E); 
  CAN.write(0x98); 
  CAN.write(0x4C);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05); 
  CAN.write(0x24); 
  CAN.write(0x40); 
  CAN.write(0x79);  
  CAN.write(0x66); 
  CAN.write(0x0F); 
  CAN.write(0x7E); 
  CAN.write(0x79);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05); 
  CAN.write(0x25); 
  CAN.write(0x02); 
  CAN.write(0xDA);  
  CAN.write(0x49); 
  CAN.write(0xA6); 
  CAN.write(0xAE); 
  CAN.write(0xC2);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05); 
  CAN.write(0x26); 
  CAN.write(0x92); 
  CAN.write(0x87);  
  CAN.write(0xCC); 
  CAN.write(0x68); 
  CAN.write(0x48); 
  CAN.write(0x6E);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05); 
  CAN.write(0x27); 
  CAN.write(0x40); 
  CAN.endPacket();

}


void sendLogStageInitial() {
  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05);
  CAN.write(0x10);
  CAN.write(0x1A);
  CAN.write(0x2C);
  CAN.write(0xD0);
  CAN.write(0xA0);
  CAN.write(0x01);
  CAN.write(0x20);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05);
  CAN.write(0x21);
  CAN.write(0x00);
  CAN.write(0x46);
  CAN.write(0x68);
  CAN.write(0x00);
  CAN.write(0x0C);
  CAN.write(0xA0);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05);
  CAN.write(0x22);
  CAN.write(0x02);
  CAN.write(0x20);
  CAN.write(0x00);
  CAN.write(0x46);
  CAN.write(0x7A);
  CAN.write(0x00);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05);
  CAN.write(0x23);
  CAN.write(0x02);
  CAN.write(0xA0);
  CAN.write(0x03);
  CAN.write(0x20);
  CAN.write(0x00);
  CAN.write(0x46);
  CAN.endPacket();

  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(0x05);
  CAN.write(0x24);
  CAN.write(0x80);
  CAN.write(0x00);
  CAN.write(0x02);
  CAN.endPacket();

}


void query() {
  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(5);   //05
  CAN.write(2);   //02
  CAN.write(33);  //21
  CAN.write(208); //D0
  CAN.endPacket();
}


void endSignal() {
  CAN.beginExtendedPacket(0xCDA00F1);
  CAN.write(5);   //05
  CAN.write(48);  //30
  CAN.write(0);   //00
  CAN.write(0);   //00
  CAN.endPacket();
}


void onReceive(int packetSize) {

  
  // received a packet
  Serial.print("Received ");

  if (CAN.packetExtended()) {
    Serial.print("extended ");
  }

  if (CAN.packetRtr()) {
    // Remote transmission request, packet contains no data
    Serial.print("RTR ");
  }

  long id = CAN.packetId();
  Serial.print("packet with id 0x");
  Serial.print(id, HEX);


  if (CAN.packetRtr()) {
    Serial.print(" and requested length ");
    Serial.println(CAN.packetDlc());
  } else {
    Serial.print(" and length ");
    Serial.println(packetSize);
      
    ble.print(id,HEX);
    ble.write("#");
    ble.print(packetSize,HEX);
    

    // only print packet data for non-RTR packets
    while (CAN.available()) {
      
      int part = CAN.read();
      Serial.print(part,HEX);
      Serial.print(",");
      
      ble.write(":");
      ble.print(part,HEX);

    }
    Serial.println();
  }
  ble.write("~");

  Serial.println();
  //delay(100);

}
