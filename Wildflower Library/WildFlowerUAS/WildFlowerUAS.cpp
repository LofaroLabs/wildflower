//************************************************************************************************
//-------------------------------------Header Files-----------------------------------------------
//************************************************************************************************

#include "Arduino.h"
#include "WildFlowerUAS.h"

//************************************************************************************************
//---------------------------------------Define Constants-----------------------------------------
//************************************************************************************************

/*--I2C addresses--*/
#define VL53L0X_ADR 0x30                //newly assigned I2C address for Long-Range LIDAR
#define VL6180X_ADR 0x29                //Standard I2C address for Short-Range LIDAR
#define BNO055_ADR 0x28                 //IMU Standard address

/*--SHUTDOWN PINS--*/
#define IMU_XSHUT 10                                //pin to reset IMU
#define VL6180X_XSHUT 11                            //pin to reset Short-Range LIDAR

//*************************************************************************************************
//---------------------------------Initialize Class Instances--------------------------------------
//*************************************************************************************************

/*--Sensors--*/
Adafruit_VL53L0X LR = Adafruit_VL53L0X();           //class for Long-Range LIDAR
Adafruit_VL6180X CR = Adafruit_VL6180X();           //class for Close-Range LIDAR
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);    //class for IMU


//*************************************************************************************************
//---------------------------------Initialize Global Variables-------------------------------------
//*************************************************************************************************

VL53L0X_RangingMeasurementData_t LongRangeLIDARData;      //Long-Range LIDAR data object
int LR_Lidar_Address = 0x29; 

//*************************************************************************************************
//---------------------------------Global Structure Initializations--------------------------------
//*************************************************************************************************

struct TxStruct TxData;
struct TxStruct RxData;
struct LidarStruct Lidar;

//*************************************************************************************************
//-----------------------------------------SENSORS CLASS-------------------------------------------
//*************************************************************************************************

//*************************************************************************************************
//-------------------------------------SENSORS PUBLIC METHODS--------------------------------------
//*************************************************************************************************

/*------------------------------SENSORS Constructor Method-------------------------------*/
SENSORS::SENSORS(void)
{

}

/*------------------------------SENSORS Initialize Method-------------------------------*/
int SENSORS::Initialize(void)
{

  Serial.begin(9600);
  
  //begin communication through I2C
  Wire.begin();
    
  //Setup the I2C addresses and VL53L0X
  SENSORS::SetupI2CAddresses();

  //Setup the other two sensors
  SENSORS::SetupSensors();

  return 1;
}

/*------------------------------Read IMU Data Method-------------------------------*/
void SENSORS::ReadIMU(void)
{
    //measure from IMU
    //could add VECTOR_ACCELEROMETER, VECTOR_MAGNETOMETER,VECTOR_GRAVITY...

    //create sensor events from adafruit driver
    sensors_event_t orientation , angularVelocity , linearAcceleration, magnetometer, accelerometer, gravity;

    //record the data values from the sensor
    bno.getEvent(&orientation, Adafruit_BNO055::VECTOR_EULER);                //orientation
    bno.getEvent(&angularVelocity, Adafruit_BNO055::VECTOR_GYROSCOPE);        //angular velocity
    bno.getEvent(&linearAcceleration, Adafruit_BNO055::VECTOR_LINEARACCEL);   //;omear acceleration
    bno.getEvent(&magnetometer, Adafruit_BNO055::VECTOR_MAGNETOMETER);        //linear magnetometer data
    bno.getEvent(&accelerometer, Adafruit_BNO055::VECTOR_ACCELEROMETER);      //linear accelerometer data
    bno.getEvent(&gravity, Adafruit_BNO055::VECTOR_GRAVITY);                  //linear gravity (from accelerometer)

    //print the results through the previously written UDF
    SENSORS::printEvent(&orientation);
    SENSORS::printEvent(&angularVelocity);
    SENSORS::printEvent(&linearAcceleration);
    SENSORS::printEvent(&magnetometer);
    SENSORS::printEvent(&accelerometer);
    SENSORS::printEvent(&gravity);

    //read values to the structure
    TxData.Position.x = (double)orientation.orientation.x;
    TxData.Position.y = (double)orientation.orientation.y;
    TxData.Position.z = (double)orientation.orientation.z;

    TxData.Rotation.x = (double)angularVelocity.gyro.x;
    TxData.Rotation.y = (double)angularVelocity.gyro.y;
    TxData.Rotation.z = (double)angularVelocity.gyro.z;

    //TxData.Mode = (uint16_t)1;

    //get board temperature as well
    int8_t boardTemp = bno.getTemp();

    //print temperature
    Serial.print(F("temperature: "));
    Serial.println(boardTemp);

    //create unsigned byte integer values 
    uint8_t system, gyro, accel, mag = 0;

    //get calibration data
    bno.getCalibration(&system, &gyro, &accel, &mag);

    //print the calibration data to the user
    Serial.print("Calibration: Sys=");
    Serial.print(system);
    Serial.print(" Gyro=");
    Serial.print(gyro);
    Serial.print(" Accel=");
    Serial.print(accel);
    Serial.print(" Mag=");
    Serial.println(mag);
}

/*------------------------------Read Close-Range LIDAR Method-------------------------------*/
void SENSORS::ReadCloseRangeLIDAR(void)
{
    //read lux data from close-range lidar
  float lux = CR.readLux(VL6180X_ALS_GAIN_1);
  Lidar.CloseRangeLUX = lux;

  //print the lux value recorded
  Serial.print("Close-Range LIDAR Lux: "); 
  Serial.println(lux);
  
  //read the range and status of the lidar
  uint8_t range = CR.readRange();
  uint8_t status = CR.readRangeStatus();

  //print data if there is no error
  if (status == VL6180X_ERROR_NONE) {
    Serial.print("Close-Range LIDAR Distance (mm): "); 
    Serial.println(range);
    Lidar.CloseRange = (float)range;
  }

  //if some error, print the error that occured
  if  ((status >= VL6180X_ERROR_SYSERR_1) && (status <= VL6180X_ERROR_SYSERR_5))  //system error
  {
    Serial.println("System error");
  }
  else if (status == VL6180X_ERROR_ECEFAIL)                                       //ECE failure
  {
    Serial.println("ECE failure");
  }
  else if (status == VL6180X_ERROR_NOCONVERGE)                                    //no beam convergence 
  {
    Serial.println("No convergence");
  }
  else if (status == VL6180X_ERROR_RANGEIGNORE)                                   //range not being used
  {
    Serial.println("Ignoring range");
  }
  else if (status == VL6180X_ERROR_SNR)                                           //error due to noise
  {
    Serial.println("Signal/Noise error");
  }
  else if (status == VL6180X_ERROR_RAWUFLOW)                                      //data underflow 
  {
    Serial.println("Raw reading underflow");
  }
  else if (status == VL6180X_ERROR_RAWOFLOW)                                      //data overflow
  {
    Serial.println("Raw reading overflow");
  }
  else if (status == VL6180X_ERROR_RANGEUFLOW)                                    //range underflow
  {
    Serial.println("Range reading underflow");
  }
  else if (status == VL6180X_ERROR_RANGEOFLOW)                                    //range overflow
  {
    Serial.println("Range reading overflow");
  }
}

/*------------------------------Read Long-Range LIDAR Method-------------------------------*/
void SENSORS::ReadLongRangeLIDAR(void)
{
    //measure from VL53L0X sensor
  LR.rangingTest(&LongRangeLIDARData, false);

  //if data is valid
  if (LongRangeLIDARData.RangeStatus != 4)       
  {  
    //print the data
    Serial.print("Long Range LIDAR: Distance (mm): "); 
    Serial.println(LongRangeLIDARData.RangeMilliMeter);
    Lidar.LongRange = (float)LongRangeLIDARData.RangeMilliMeter;
  } 

  //if data is incorrect
  else 
  {
    //print error to the user
    Serial.println("Long Range LIDAR: out of range ");
  }
}

//*************************************************************************************************
//----------------------------------SENSORS PRIVATE METHODS----------------------------------------
//*************************************************************************************************

/*------------------------------Setup Peripherals I2C Addresses Method----------------------------*/
void SENSORS::SetupI2CAddresses(void)
{
    //notify user that this is the initial I2C Scan
    Serial.println("Initial I2C address scan");
    
    //scan for initial addresses
    SENSORS::I2C_Scan();
    
    //initialize pinmodes
    Serial.println("XSHUT pins initialized");
    pinMode(IMU_XSHUT, OUTPUT);
    pinMode(VL6180X_XSHUT, OUTPUT);

    //set XSHUT on other sensors to HIGH
    digitalWrite(IMU_XSHUT, HIGH);
    digitalWrite(VL6180X_XSHUT, HIGH);
    delay(10);

    //set XSHUT LOW TO RESET SENSORS
    Serial.println("Sensors are in reset mode..");
    digitalWrite(IMU_XSHUT, LOW);
    digitalWrite(VL6180X_XSHUT, LOW);

    //print to user verifying that all sensors are off
    Serial.println("Verifying that all sensors are off other than Long-Range LIDAR");

    //verify that sensors are off
    SENSORS::I2C_Scan();

    //reset the VL53L0X's address
    Serial.println("Initializing Long-Range LIDAR");
    if (!LR.begin(LR_Lidar_Address))
    {
        Serial.println("Long-range LIDAR failed to initialize");
    }
    else
    {
        Serial.println("Long-range LIDAR initialized");
    }

    //if Long-Range LIDAR address is 0x29, reset the address
    if (LR_Lidar_Address == 0x29)
    {
        Serial.println("Setting LIDAR's new address");
        LR.setAddress(VL53L0X_ADR);
    }
    delay(1000);

    //print to user that the new value has been set
    Serial.println("Verifying that the new I2C address has been set");

    //verify the addresses were set
    SENSORS::I2C_Scan();

    //set other sensors HIGH to use them
    Serial.println("Sensors exiting reset mode..");
    digitalWrite(IMU_XSHUT, HIGH);
    digitalWrite(VL6180X_XSHUT, HIGH);
    delay(1000);

    //print the hardware status to user
    Serial.println("Scanning I2C addresses now with all sensors on");

    //verify that sensors are all on
    SENSORS::I2C_Scan();
}

/*------------------------------Initialize and Configure Sensors Method-------------------------------*/
void SENSORS::SetupSensors(void)
{
    //setup adafruit driver for VL6180X

    //initialize byte named modelID 
    byte modelID;               

    //print to user
    Serial.println("Configuring Close-Range LIDAR to Adafruit Firmware...");

    //set register value for modelID to 0x00B4 at register 0x00 for model ID (initializing sensor in adafruit driver requires this to be set)
    //and this value is wiped within the reset process when setting the I2C address for the long-range lidar
    Wire.beginTransmission(0x29);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.write(0xB4);
    Wire.endTransmission();

    //short delay
    delay(500);
    
    //read register value to verify functionality
    Wire.beginTransmission(0x29);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(0x29, 1);
    modelID = Wire.read();

    //short delay
    delay(500);

    //display register value
    Serial.println("The value returned is: " + String(modelID));

    //now initialize the close-range lidar through Adafruit drivers
    Serial.println("Initializing Adafruit VL6180x!");
    if (! CR.begin()) {
        Serial.println("Failed to find sensor");
        while (1);
    }
    Serial.println("Close-Range LIDAR Initialized!");

    //short led
    delay(500);

    
    //begin communication with the IMU
    if (!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("BNO055 not detected.");
        while (1);
    }

    //create a long delay
    delay(5000);
}

/*------------------------------I2C Address Scanner Method-------------------------------*/
void SENSORS::I2C_Scan(void)
{
    //for loop used for scanning for I2C addresses
  for (int looper = 0; looper<3; looper++)
  {
    //initializing variables used
    byte error, address;
    int nDevices;

    //print to user that scanning is beginning
    Serial.println("Scanning...");

    //set device count to 0
    nDevices = 0;

    //start nested loop to scan from 0x01 to 0x7F
    for (address = 1; address < 127; address++)
    {
      //begin I2C transmission
      Wire.beginTransmission(address);

      //end I2C tranmission
      error = Wire.endTransmission();

      //if there was no error, print the address
      if (error == 0) {
        Serial.print("I2C device found at address 0x");
        if (address < 16)
          Serial.print("0");
        Serial.println(address, HEX);

        //assign LR_Lidar_Address to 0x30 if this exists (to not reinitialize the sensor if it is already set)
        if (address == 0x30)
        {
          LR_Lidar_Address = 0x30;
        }

        //increment device count 
        nDevices++;
      }

      //if there is an error from Wire, print that the device is unknown
      else if (error == 4) {
        Serial.print("Unknown error at address 0x");
        if (address < 16)
          Serial.print("0");
        Serial.println(address, HEX);
      }
    }

    //print if the scan if complete
    if (nDevices == 0)
      Serial.println("No I2C devices found");
    else
      Serial.println("done");

    //delay for next step
    delay(500);
  }
}


/*------------------------------Print IMU Event Method-------------------------------*/
void SENSORS::printEvent(sensors_event_t* event)
{
    //initialize recording variables (dummy values)
    double x = -1000000, y = -1000000 , z = -1000000; 

    //read event type and assign the appropriate values
    if (event->type == SENSOR_TYPE_ACCELEROMETER) 
    {
        Serial.print("Accl:");
        x = event->acceleration.x;
        y = event->acceleration.y;
        z = event->acceleration.z;
    }
    else if (event->type == SENSOR_TYPE_ORIENTATION) 
    {
        Serial.print("Orient:");
        x = event->orientation.x;
        y = event->orientation.y;
        z = event->orientation.z;
    }
    else if (event->type == SENSOR_TYPE_MAGNETIC_FIELD) 
    {
        Serial.print("Mag:");
        x = event->magnetic.x;
        y = event->magnetic.y;
        z = event->magnetic.z;
    }
    else if (event->type == SENSOR_TYPE_GYROSCOPE) 
    {
        Serial.print("Gyro:");
        x = event->gyro.x;
        y = event->gyro.y;
        z = event->gyro.z;
    }
    else if (event->type == SENSOR_TYPE_ROTATION_VECTOR) 
    {
        Serial.print("Rot:");
        x = event->gyro.x;
        y = event->gyro.y;
        z = event->gyro.z;
    }
    else if (event->type == SENSOR_TYPE_LINEAR_ACCELERATION) 
    {
        Serial.print("Linear:");
        x = event->acceleration.x;
        y = event->acceleration.y;
        z = event->acceleration.z;
    }
    else 
    {
        Serial.print("Unknown:");
    }

    //print the values to the user
    Serial.print("\tx= ");
    Serial.print(x);
    Serial.print(" |\ty= ");
    Serial.print(y);
    Serial.print(" |\tz= ");
    Serial.println(z);
}


//**************************************************************************************
//---------------------------------WiFi Class Methods----------------------------------
//**************************************************************************************

//**************************************************************************************
//--------------------------------WiFi Global Variables---------------------------------
//**************************************************************************************

//global variables used
int status = WL_IDLE_STATUS;
int keyIndex = 0;                   // your network key Index number (needed only for WEP)
IPAddress remoteIp;
char packetBuffer[255];             //buffer to hold incoming packet
char ReplyBuffer[] = "OK";          // a string to send back
WiFiUDP Udp;
unsigned int TxPort; 

//**************************************************************************************
//--------------------------------WiFi Public Methods----------------------------------
//**************************************************************************************

/*------------------------------WiFi Constructor Method-------------------------------*/
UAS_WiFi::UAS_WiFi(void)
{

}

/*------------------------------WiFi Send Method--------------------------------------*/
void UAS_WiFi::Send(void)
{
    String RxString = ConstructString();
    
    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(remoteIp, TxPort);
    Udp.write(RxString.c_str());
    Udp.endPacket();
}

/*---------------------------------WiFi Receive Method-------------------------------*/
void UAS_WiFi::Receive(void)
{
    //initialize variables
    int stat = 0;
    int packetSize;

    //infinite loop to receive value
    while (!stat)
    {
        //get packet size
        packetSize = Udp.parsePacket();

        //if a packet was received
        if (packetSize)
        {
        //give inforomation
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        remoteIp = Udp.remoteIP();
        Serial.print(remoteIp);
        Serial.print(", port ");
        Serial.println(Udp.remotePort());
    
        // read the packet into packetBufffer
        int len = Udp.read(packetBuffer, 255);

        //If packet is too large, clear 
        if (len > 0) packetBuffer[len] = 0;

        //print contents
        Serial.println("Contents:");
        Serial.println(packetBuffer);
    
        // send a reply, to the IP address and port that sent us the packet we received
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(ReplyBuffer);
        Udp.endPacket();
        stat = 1;

        //part string into struct
        String strBuffer = String(packetBuffer);
        ParseString(strBuffer);
        } 
    }
}


/*----------------------------------WiFi Initialize Method-----------------------------------*/
void UAS_WiFi::Initialize(const char ssid[], const char pass[], unsigned int localPort, unsigned int remotePort)
{
    //configure arduino library for adafruit board
    WiFi.setPins(8,7,4,2);
    delay(1000);

    TxPort = remotePort;
    
    //initialize serial communication
    Serial.begin(9600);

    // check for the presence of the WiFi shield:
    if (WiFi.status() == WL_NO_SHIELD) 
    {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true);
    }

    // attempt to connect to WiFi network:
    while ( status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }
    Serial.println("Connected to wifi");
    UAS_WiFi::printWiFiStatus();

    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:
    Udp.begin(localPort);
    Serial.println("Connection Found!");
    return;
}

//**************************************************************************************
//--------------------------------WiFi Private Methods----------------------------------
//**************************************************************************************

/*------------------------------Print WiFi Status  Method-------------------------------*/
void UAS_WiFi::printWiFiStatus(void)
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

/*------------------------------WiFi String Construction Method-------------------------------*/
String UAS_WiFi::ConstructString(void)
{
  String Data;
  Data = String(TxData.Position.x)+" "+String(TxData.Position.y)+" "+String(TxData.Position.z)+" "+String(TxData.Rotation.x)+" "+String(TxData.Rotation.y)+" "+String(TxData.Rotation.z)+" "+String(TxData.Mode)+"\n";

  return Data;
}

/*------------------------------WiFi Parse String Method-------------------------------*/
void UAS_WiFi::ParseString(String RxString)
{
  int len = RxString.length();
  int inc = 0;
  String strBuf;
  
  for (int i = 0; i < len; i++)
  {
    if (RxString[i] == ' ')
    {
      if (inc == 0)
      {
        RxData.Position.x = strBuf.toDouble();
      }
      else if (inc == 1)
      {
        RxData.Position.y = strBuf.toDouble();
      }
      else if (inc == 2)
      {
        RxData.Position.z = strBuf.toDouble();
      }
      else if (inc == 3)
      {
        RxData.Rotation.x = strBuf.toDouble();
      }
      else if (inc == 4)
      {
        RxData.Rotation.y = strBuf.toDouble();
      }
      else if (inc == 5)
      {
        RxData.Rotation.z = strBuf.toDouble();
      }
      
      strBuf = "";
      inc++;
    }
    else if (RxString[i] == '\n')
    {
      RxData.Mode = (uint16_t)strBuf.toInt();
      
      strBuf = "";
      inc = 0;
    }
    else 
    {
      strBuf.concat(RxString[i]);
    }
  }
}
