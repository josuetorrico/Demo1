/* uC code for maze robot */

// DXL device serial bus definition:
#define DXL_BUS_SERIAL 1 // for OpenCM9.04

// Dynamixel ID definitions:
#define J_ID1 1
#define J_ID2 2

Dynamixel Dxl(DXL_BUS_SERIAL1);

// input pin values:
const int APin = 0
const int DPin = 1

// safety limit (10 seconds):
const int Limit = 100;

// safety variables:
int Safety = Limit;
int packetCount = 0;

// motor velocities:
leftVel = 0;
rightVel = 0;

//USB max packet data is maximum 64byte, so nCount can not exceeds 64 bytes
void USBItr(byte* packetbuf, byte size) {

  // GET DATA:

  if (packetCount == packetbuf[0])
    Safety--;
  else
    Safety = Limit;

  packetCount = packetbuf[0];

  // Read line value (0-4095 for 3.3 V):
  int LineSensor = analogRead(APin);

  // Read bumper value:
  int BumperSensor = digitalRead(DPin);


  // RETURN SENSORS:

  // Send data over USB:
  SerialUSB.print("l:");
  SerialUSB.println(LineSensor);

  // Send data over USB:
  SerialUSB.print("b:");
  SerialUSB.println(BumperSensor);


  // SET MOTORS/MEMORY:

  leftSpeed = packetbuf[1];
  rightSpeed = packetbuf[2];

}

void setup() {

  // USB interrupt setup:
  SerialUSB.attachInterrupt(USBItr);

  // Set pin 0 line sensor analog input:
  pinMode(APin, INPUT_ANALOG);

  // Set pin 1 bumper digital input:
  pinMode(DPin, INPUT_PULLUP);

  // Dynamixel baud rate 1Mbps (#3)
  Dxl.begin(3);
  Dxl.wheelMode(J_ID1);
  Dxl.wheelMode(J_ID2);

  // Send reset/reset button pressed data over USB:
  SerialUSB.println("Reset");

  // Delay for 2 seconds:
  delay(2000);

}

void loop() {

  if (Safety > 0)
  {
    Dxl.goalSpeed(J_ID1, leftVel);
    Dxl.goalSpeed(J_ID2, rightVel);
  }
  else
  {
    Dxl.goalSpeed(J_ID1, 0);
    Dxl.goalSpeed(J_ID2, 0);
  }

  // Delay for 0.1 seconds:
  delay(100);

}

