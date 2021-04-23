#include "WildFlowerUAS.h"
#include "NETWORK_INFO.h"

const char ssid[] = NETWORK_SSID;
const char pass[] = NETWORK_PASS;
unsigned int localPort = RX_PORT;
unsigned int remotePort = TX_PORT;

UAS_WiFi WIFI_MODULE = UAS_WiFi();

void setup() 
{
  WIFI_MODULE.Initialize(ssid, pass, localPort, remotePort);
}

void loop() 
{
  WIFI_MODULE.Receive();
  Serial.println("Now sending packet....");
  WIFI_MODULE.Send();
  Serial.println("Packet Sent");
}
