1. PLACE FILE IN LIBRARIES FOLDER FOR ARDUINO
	-If on Windows 10, the folder should be at "C:\Users\Username\Documents\Arduino\libraries\".

2. CLASSES TO CALL and METHODS 
	SENSORS
		SENSORS(void);
			-Creates a class instance.
		void Initialize(void)	
			-Initializes the sensors to be able to read data.
		void ReadIMU(void)
			-Reads data from IMU and stores it into global variables.
		void ReadCloseRangeLIDAR(void)
			-Reads data from the close-range LIDAR and stores it in a global variable.
		void ReadLongRangeLIDAR(void)
			-Reads data from the long-range LIDAR and stores it in a global variable.
	UAS_WiFi
		UAS_WiFi(void);
			-Creates a class instance 
		void Initialize(const char ssid[], const char pass[], unsigned int localPort);
			-Initializes WiFi connections, prints the status, and begins listening on the specified port for packets transmitted through UDP.
		void Send(const char message[], unsigned int port);
			-Sends the message through UDP on the specified port. 
		void Receive(void);
			-Listens to specified port in Initialize for commands transmitted from the ground station.

3. IMPORTANT GLOBAL VARIABLES 
	I2C Addressing
		-VL6180X_ADR
			-Long-Range LIDAR address set to 0x29.
		-VL53L0X_ADR
			-Close-Range LIDAR address set to 0x30.
		-BNO055_ADR 
			-IMU adress set to 0x28.
	Sensor XSHUT Pins 
		-VL6180X_XSHUT
			-XSHUT pin for Long-Range LIDAR, which is 11.
		-BNO055_XSHUT
			-XSHUT pin for IMU, which is 10.

	IMU Return Data

	Long-Range LIDAR Return Data

	Close-Range LIDAR Return Data
	