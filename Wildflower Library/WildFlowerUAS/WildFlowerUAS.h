#ifndef WildFlowerUAS_h
#define WildFlowerUAS_h

//************************************************************************************************
//-------------------------------------Header Files-----------------------------------------------
//************************************************************************************************

#include "Arduino.h"

//include propper header files
#include <Wire.h>                       //General I2C Library
#include <SPI.h>                        //General SPI library
#include <Adafruit_BNO055.h>            //IMU Libraies
#include <Adafruit_Sensor.h> 
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_VL53L0X.h>           //Long-Range LIDAR Library 
#include <Adafruit_VL6180X.h>           //Short-Range LIDAR Library
#include <Arduino_LSM6DS3.h>            //LIDAR dependency 
#include <WiFi101.h>
#include <WiFiUdp.h>

//*************************************************************************************************
//---------------------------------Structure Definitions-------------------------------------------
//*************************************************************************************************

/*--Used for IMU Sensor Data--*/
struct vector_3D
{
  double x; 
  double y; 
  double z;
};

/*--LIDAR Data--*/
struct LidarStruct 
{
  float CloseRange;
  float CloseRangeLUX;
  float LongRange;
};

/*--Takes Sensor Data--*/
struct TxStruct 
{
  struct vector_3D Position; 
  struct vector_3D Rotation;
  uint16_t Mode;
};

//*************************************************************************************************
//-------------------------------------Exported Global Variables-----------------------------------
//*************************************************************************************************

extern struct TxStruct TxData;
extern struct LidarStruct Lidar;
extern struct TxStruct RxData;

//*************************************************************************************************
//-----------------------------------------Sensor Class--------------------------------------------
//*************************************************************************************************

class SENSORS
{ 
    //public methods
    public:
        SENSORS(void);
        int Initialize(void);
        void ReadIMU(void);
        void ReadCloseRangeLIDAR(void);
        void ReadLongRangeLIDAR(void);

    //private methods
    private:
        void SetupI2CAddresses(void);
        void SetupSensors(void);
        void I2C_Scan(void);
        void printEvent(sensors_event_t* event);
};

//*************************************************************************************************
//-----------------------------------------WiFi Class----------------------------------------------
//*************************************************************************************************

class UAS_WiFi
{
    public: 
        UAS_WiFi(void);
        void Initialize(const char ssid[], const char pass[], unsigned int localPort, unsigned int remotePort);
        void Receive(void);
        void Send(void);

    private:
        void printWiFiStatus(void);
        String ConstructString(void);
        void ParseString(String RxString);
};


#endif
