//header files needed
#include "WildFlowerUAS.h"
#include "NETWORK_INFO.h"

//initialize classes
SENSORS sense = SENSORS();
UAS_WiFi comms = UAS_WiFi();

//read from NETWORK_INFO file and configure
const char ssid[] = NETWORK_SSID;
const char pass[] = NETWORK_PASS;
unsigned int localPort = RX_PORT; 
unsigned int remotePort = TX_PORT;

void setup() 
{
  //begin serial communication
  Serial.begin(9600);

  //initialize the sensors
  sense.Initialize();

  //initialize WiFi Communication
  comms.Initialize(ssid, pass, localPort, remotePort);
}

void loop() 
{
  //read from sensors
  sense.ReadIMU();
  sense.ReadCloseRangeLIDAR();
  sense.ReadLongRangeLIDAR();

  //communicate with the ground station
  comms.Receive();
  comms.Send();
}
