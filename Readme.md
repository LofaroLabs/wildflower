<!DOCTYPE HTML>
<html lang="en-US">
  <head>
    <meta charset="UTF-8">
  </head>
  <body>
    <!--Main Header-->
    <h1> Project Wildflower UAS </h1>
    <!--Logos-->
    <p float="left">
      <img src="Images\Logos\LofaroLabsLogo.svg" alt="Lofaro Labs Logo" height="150px">
      <img src="Images\Logos\Project_Wildflower.svg" alt="Project Wildflower Logo" height="150px">
    </p>
    <!--Link Bar-->
    <div id="NavBar">
      <p>  
        <a href="#Introduction" target="_blank">Approach</a>
         | 
        <a href="#PCBAndPowerSystems" target="_blank">PCB & Power Systems</a>
         | 
        <a href="#SoftwareAndPsuedocode">Software & Psuedocode</a>
         | 
        <a href="#BriefHistoryofArduino">Brief History of Arduino</a>
         | 
        <a href="#SensorsAndMotorDrivers">Sensors & Motor Drivers</a>
         | 
        <a href="#Results">Results</a>
         | 
        <a href="#Conclusion">Conclusion</a>
         | 
        <a href="#References">References</a>
         | 
        <a href="#ProjectPresentation">Project Presentation</a>
         | 
        <a href="https://www.youtube.com/watch?v=GgbFuCZchfk" target="_blank">Project Presentation on YouTube</a>
         | 
        <a href="http://lofarolabs.com/" target="_blank">Lofaro Labs Website</a>
    </div>
    <!--Section 0: Abstract-->
    <div>
      <p> 
        &nbsp;&nbsp;&nbsp;&nbsp;Since the turn of the millennium, unmanned aerial vehicles (UAVs) have gone from being used for highly specialized applications to becoming one of the primary approaches to mission success within the defense sector. UAVs are unmatched in terms of mission success versus collateral damage - and as production costs continue to rapidly fall, it is only natural that UAVs will continue to become a more common tool of militaries around the world. One of the most recent developments in the world of UAVs has been the growing consumer market for ultralight unmanned aerial systems (UAS). Some commercial products have demonstrated the viability and flexibility of inexpensive, open source, ultralight UAS systems. Unfortunately, most consumer products on the market cannot be approved for high security applications due to the inherent security risks posed by foreign-manufactured products. Therefore, the defense industry has need of an American-made ultralight UAS if it wants to pursue the potential applications that this technology allows. 
      </p>
      <p>
        &nbsp;&nbsp;&nbsp;&nbsp;This paper entails the results of our research and development work over the past 9 months. We are proud to present the results of our testing on a brushed-motor, unmanned aerial system (UAS) quadcopter designed in preparation of developing a brushless quadcopter in the future. Beginning in September of 2020, we began to perform research on designing a lightweight quadcopter out of a single printed circuit board (PCB) in order to meet the need for a quality, domestically produced UAS. Today, a great number of quadcopters are produced in foreign countries or with foreign programmed components. While many of these common quadcopters have demonstrated the general usefulness and cost-efficiency of their use, their foreign origins make them unusable by the federal government and military sectors due to concerns over information safety. Data concerning their activities is often sent to and kept on insecure servers[CNN and OSTI.gov, second not quoted], and can provide easy access points for malicious entities to otherwise secure systems when allowed to connect[Avast]. 
      </p>
      <p>
        &nbsp;&nbsp;&nbsp;&nbsp; As a result, our project was designed to fill this gap by providing a secure, American made UAS capable of remote operations. This paper covers the design process, creation, and testing of our quadcopter over the past two semesters. Our section on the PCB & Power System Design describes the design choices we made in structuring our board, as well as our choice of using a dual power system to power the motors and microcontroller separately. The Software & Pseudocode section goes over the general flow of our real time system, and is followed by a Brief History of Arduino. Sensors and Motor Drivers describe the input and output devices we thought best fitting for our UAS. The control systems elaborates further on our real time system. Finally, the Unit Testing and Results slide show the results of our research as we make the Wildflower hover and tilt at will, bringing us to our conclusion.
      </p>
      <hr>
    </div>
    <!--Section 1: Introduction-->
    <div id="Introduction">
      <h1>Approach</h1>
      <h3>The Problem</h3>
      <p> 
        &nbsp;&nbsp;&nbsp;&nbsp;The idea for the Wildflower arose from the desire for an American designed and programmed quadcopter in a market saturated with foreign-made quadcopters. The need for American Unmanned Aerial Systems (UAS) has been apparent for several years. In August 2017, “the Army banned the use of DJI drones citing ‘cyber vulnerabilities’” [1,2]. In May 2018, the DoD followed suit, banning not only the purchase of DJI drones, but the purchase of all commercial off-the-shelf (COTS) drones” [3,4]. Shortly after, several alarming vulnerabilities were discovered involving the DJI Go Phone application [5]. Such vulnerabilities included “access to facial recognition data (even when the system was off)” [5]. It’s not a far stretch to assume that the ban on government funding for blacklisted drones may soon extend to universities that receive government grants.
      </p>
      <p>
        &nbsp;&nbsp;&nbsp;&nbsp;The COTS ban, while seemingly necessary, has left a lot of government employees and contractors with a job to do without the tools to do it. There have never been many US-made drones available on the market, but the pool of eligible candidates dwindles further when the drones containing foreign software are excluded. While there currently exists a number of American based alternatives for remote controlled unmanned aerial systems, such systems often cannot be used out-of-the-box for important security or government related tasks. For example, many of these UASs are not easily configurable, having been made for the general public to enjoy. Additionally, the communications methods for these systems might not be securable, posing a risk of malicious infiltration into crucial US government and military organizations. 
      </p>
      <h3>The Solution</h3>
      <p>
        &nbsp;&nbsp;&nbsp;&nbsp; Dr. Lofaro’s initial idea for the Wildflower was conceived as a direct result of his inability to use certain UAS’s for his work at the Naval Research Lab. Our project aims to fill this gap by providing a trustworthy and easily modifiable aerial system designed in a way that allows easy debugging and testing for those who use it. We make use of a VL6180x short-range light detection and ranging (LIDAR) sensor, a VL53L0x long-range LIDAR sensor, and a BNO055 inertial measurement unit (IMU) sensor to feed all of the information we need to our Adafruit Feather M0 microcontroller (MCU) with embedded ATWINC1500 Wifi chip, in order to keep it airborne and mobile. We communicate commands to the Feather over wi-fi and through a ground station that can be easily installed on a user’s computer, allowing for increased portability and relatively straightforward setup and teardown when moving from one area of use to another or starting to use it for the first time. 
      </p>
      <hr>
    </div>
    <!--Section 2: PCB & Power Systems-->
    <div id="PCBAndPowerSystems">
      <h1>PCB & Power Systems</h1>
      <div>
        <p> 
          &nbsp;&nbsp;&nbsp;&nbsp;The circuit board for the UAS design consists of a 51x51mm body with four 10mm arms connected to circular motor mounting points which are 19mm in diameter. The motors and rotors are mounted on the outer circle of the PCB connected to the quadrotor’s arms, while some of the heavier electronics are placed towards the center of the PCB for stability. 
        </p>
        <!--PCB-->
        <img src="Images\Photos\UAS_PCB.png" alt="Final PCB">
        <!--Schematic-->
        <img src="Images\Photos\UAS_Schematic.png" alt="Final Schematic"height="350px">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;The UAS PCB circuitry consists of a battery to supply power to the circuit. Two switches are applied in parallel with the battery to function as on/off switches to the motors and the microcontroller respectively. From the on/off switch, power is supplied to the microcontroller through a 3.3V voltage regulator at 300milliamperes. This voltage regulator was chosen since the recommended voltage input to the Feather is 3 to 5 volts and the recommended current that is input to the Feather is 250 milliamperes to 400 milliamperes. The microcontroller then uses the 3.3-volt output pin to supply power to the close-range lidar sensor, the long-range lidar sensor, and the inertial measurement unit (IMU).  Power is supplied to the motors using a single metal-oxide-semiconductor field-effect transistor (MOSFET), rather than using an H-bridge circuit for simplicity. The power supplied from the battery is supplied to the drain terminal of the MOSFET and the source MOSFET is connected to the motors. The amount of power supplied to the motors is manipulated by pulse-width modulation of the gate terminal of the MOSFET. When applying a signal from the Feather to the MOSFET with a high duty cycle, the drain current will increase; however, the opposite will occur when the input signal has a low duty cycle. The drain current of a MOSFET acting in the saturation region can be calculated by the following equation:
        </p>
        <!--Drain Current Equation-->
        <img src="Images\Photos\Transconductance_Equation.png" alt="Drain Current Equation for MOSFET in the triode region">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;The transconductance parameter is the portion of this equation that dictates the amount of drain current based on the input voltage; thus, choosing a MOSFET with the correct transconductance parameter was critical. Another critical criterion that had to be met was having a low threshold voltage. With a low threshold voltage, the triode region of the MOSFET is entered with a low gate to source voltage. Since the gate to source voltage will at most be equivalent to the drain to source voltage in our case, the closest that our MOSFET will act to the triode region Is on the bound of the triode and saturation regions. For all of these reasons, we have chosen to use the SI2342DS. Shown below, this model of MOSFET will allow a large drain current to pass through MOSFET from the battery to the motor when a large gate voltage is applied; however, the opposite will occur when the gate to source voltage is lower than or equal to the threshold voltage. 
        </p>
        <!--Image of the FET graph-->
        <img src="Images\Graphs\DrainToSourceVoltageVersusDrainCurrentMOSFET.png" alt="MOSFET Drain to Source Voltage Versus Drain Current" height="250px" width="300px">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;Finally, the node connected to the motor inputs is also connected to a decoupling capacitor. This capacitor will cancel out some of the impedance caused by the inductive load of the motor as well as filter out any high frequency signal components. 
        </p>
        <hr>
      </div>
    </div>
    <!--Section 3: Software and Psuedocode-->
    <div id="SoftwareAndPsuedocode">
      <h1>Software & Psuedocode</h1>
      <div>
        <p> 
          &nbsp;&nbsp;&nbsp;&nbsp;The Adafruit Feather M0 microcontroller uses the on-board RF module, the ATWINC1500, to communicate with the ground station over a 2.4 gigahertz WiFi network. The Feather communicates with the on-board ATWINC1500 module using serial peripheral interface (SPI) communication. The RF module then connects to the same WiFi network to which the ground station is connected. The communication between the microcontroller and the ground station is done by transmitting packets using User Datagram Protocol (UDP). UDP was chosen over Transmission Control Protocol (TCP) since UDP is a faster communication method. This is due to UDP being a connectionless protocol; thus, the setup and retransmission times of UDP are much quicker than that of TCP. The tradeoff of that UDP is more error prone since it does not use include sequencing numbers. Since we are not transmitting large files, any transmission error is accounted for by built-in selective repeat ARQ (Automatic Repeat Request).  The UDP packets are sent from the ground station to the microcontroller on port 2390 and packets received from the microcontroller are obtained from port 3000. 
        </p>
        <!--Place Communications Diagram-->
        <img src="Images\Diagrams\CommunicationDiagram.svg">
        <!--Place GUI-->
        <img src="Images\Photos\GroundStationGUI.png" alt="Ground Station GUI" height="250px" width="600px">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;The data being transmitted is in the format of a strings. Functions on the host and client side are implemented to format and parse strings to and from data structures. When the data is received by the microcontroller in the correct format, another string is transmitted, which serves as format-based Stop-and-wait ARQ. If the acknowledgment is not received by the ground station, the packet is then retransmitted until reaching a timeout value. The combination of this software implementation of format-based Stop-and-Wait ARQ, the built-in Selective Repeat ARQ of UDP, and the small data quantity serve as an error-limiting provide more reliable transmission while still maintaining high transfer rates. 
        </p>
        <!--Software Flow Chart-->
        <img src="Images\Diagrams\Peripheral_Software_Flowchart.svg" alt="Software Flowchart">
        <!--UML Diagram-->
        <img src="Images\Diagrams\UML_Class_Diagram.svg" alt="UML Diagram">
        <hr>
      </div>
    </div>
    <!--Section 4: Brief History of Arduino-->
    <div id="BriefHistoryofArduino">
      <h1>Brief History of Arduino</h1>
      <div>
        <p> 
          &nbsp;&nbsp;&nbsp;&nbsp;Arduino, as it is known today, is a forked version of an open-source programming project called Wiring. Wiring was started in 2003 by grad student Hernando Barragán for his Master's thesis at the Interaction Design Institute in Ivrea. His idea was to create "a microcontroller-based hardware controller platform that was simple enough to program that it could be used by artists"[6] without needing to know the specific programming syntax for the board that said code was running on. This enables users to implement the same code (with some minor tweaking to pin numbers) to run a program on a variety of boards. So, we designd our code to be Arduino compliant, without any bit banging or direct processor level interaction, so that it can be easily modified by the average user and so it can go on any microcontroller. 
        </p>
        <hr>
      </div>
    </div>
    <!--Section 5: Sensors & Motor Drivers-->
    <div id="SensorsAndMotorDrivers">
      <h1>Sensors & Motor Drivers</h1>
      <div>
        <p> 
          &nbsp;&nbsp;&nbsp;&nbsp;Onboard sensors are used to maintain a specific angle. The BNO055 IMU not only keeps track of our angle relative to the start-up orientation, but it also is able to determine angular velocity and linear acceleration of the Wildflower whenever we need it. Said orientation, velocity, and acceleration inputs are fed into our PID so that it can adjust the motors spin speed to reach the desired orientation of our UAS. We adjust the desired orientation via UDP communications with our ground station. 
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;The Wildflower makes use of three different sensors to help keep it in a user-specified location and orientation. The first is the BNO055 inertial measurement unit, which is capable of tracking the UAS’s absolute orientation, angular velocity, and linear acceleration, of which we need in order to make our PID controller work. The absolute orientation provides the provides the proportional section of our PID formula, representing the base difference that our UAS needs to rotate in order to meet the desired orientation. The velocity is used in part of the derivative contribution to the formula so we can see the rate at which it’s rotating about an axis and increase or decrease the rotational force being applied in order to reach that point in a timely manner while minimizing overshoot. The recordings of both can be stored onboard and used with some averaging to give us the integrational part of our formula. This completes our PID function, giving us the appropriate forces, we need to apply on each axis to reach our goal. Said forces are then fed into a function which converts them into values which tell the motors at what rate they should spin in order to best achieve the desired state. 
        </p>
        <!--Peripheral Circuit-->
        <img src="Images\Diagrams\SensorBlockDiagram.svg" alt="Peripheral Circuitry">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;The other two sensors are LIDARs specified to work at different ranges, with one being our long range one and the other being our close range one. The long one is rated for a range of 50 mm to 1200 mm, allowing us to determine how high off the ground we have ascended (our altitude) to a degree. Its primary purpose is helping the Wildflower maintain a specified height. The second one has an effective range of 5 mm to 100 mm, which aids in landing to ensure that we don’t drop too quickly. 
        </p>
        <hr>
      </div>
    </div>
    <!--Section 6: Results-->
    <div id="Results">
      <h1>Results</h1>
      <div>
        <p> 
          &nbsp;&nbsp;&nbsp;&nbsp;The first unit test we performed was a single motor thrust measurement. After the move from the brushless DC motors to the brushed DC motors was made, it was important to establish a new thrust capability threshold for the new motors. To accomplish this, a single motor was mounted in putty to a kitchen scale. The motor was hooked up to a desktop power supply and the propeller was switched in order to have the motor trust against the scale. Voltage was ramped up until the maximum output of the battery was reached resulting in a maximum of 18 grams of thrust. This gave the final four motor drone a potential 72 grams of maximum thrust. 
        </p>
        <!--Single Motor Testing Image-->
        <img src="Images\Photos\SIngle Motor Testing.png" alt="Single Motor Testing Image">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;After the drone had been fully assembled and all the sensors individually tested, a full drone thrust test was performed. The first interaction of this test involved mounting the drone in its normal flying position to a kitchen scale using a mount secured to the base of the drone. This test resulted in false readings as the propeller wash interfered with the scales measurements and needed to be reperformed. The second test involved inverting the drone and attaching it to an even higher secure mount. The inverted position significantly reduced propeller wash intensity and the higher mount ensured plenty of clearance between the drone and the scale. This resulted in a successful measurement of full drone thrust at 68 grams. The loss of thrust power between the single motor test and the full drone test is was due to the introduction of the motor arms to the air column of the propellers. This resulted in a 5% loss of thrust per motor.  
        </p>
        <!--All Motor Testing Image-->
        <img src="Images\Photos\Full Thrust Testing.png" alt="All Motor Thrust Test"> 
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;After establishing our maximum thrust, our average flight time could be determined based on power draw from the stationary hovering drone. This was determined to be 8.73A in total current draw at 3.7V. Given that our battery has a max charge of 2.6Ah and that the battery will drop below the required output voltage at 20% charge, we determined that an average flight time of 14 minutes would be achievable.  
        </p>
        <!--Flight Time Testing-->
        <img src="Images\Photos\Flight Time Test.png" alt="Flight Time Testing Image">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;Approaching the initial hover test came with a few hurdles. Although we were sure we could get the blades to spin, we did not have a sufficient rig to ensure the drone’s movement would be isolated to the z-axis. A rig was constructed using spare lumber and two steel rods to act as stationary mounts. Hooked around the mounts were two lightweight hanging screws threaded with wire. The wire was then attached to the drone and third rod was added to ensure only a single degree of motion would be achievable. With the rod created and the drone placed in it, the battery terminals were connected to a desktop power supply in order to not waste batteries for the tests.  
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;The initial hover test was conducted with the power being directly fed into the motor system, fully bypassing the control hardware. This initial test was a structural one to ensure basic flight could be achieved as well as a stress test for the design overall and the motor mounts. This initial test showed that at the battery's max voltage, the original motor mount design failed catastrophically. Approximately three seconds after flight was achieved one of the motors was violently wrested from its mount. This resulted in a redesign of the motor mounts to ensure proper hover. The reworked motor mounts were tested a second time using the single dimension rig. This second test resulted in successful takeoff and flight maintenance. Although altitude was not actively controlled, it was limited by the cables connecting the drone to the desktop power supply.  As the voltage to the drone was slowly lowered, it successfully made a gentle landing on the rig, showing that the motors do not sudden cut out at the drone had the ability to safety land from altitude.  
        </p>
        <!--Takeoff and landing test-->
        <img src="Images\Photos\Takeoff and Landing Testing.png" alt="Takeoff and Landing test">
         <p>
          &nbsp;&nbsp;&nbsp;&nbsp;The first altitude control test involved the same test rig setup but this time the full sensor package was powered, and the control system was installed. There was a delay in initial takeoff as the spin up process took a bit longer than anticipated. Ultimately it took 1.7 seconds for the prototype to reach an altitude of 400m from a cold start. During the flight the climb rate of the drone adjusted during the sensor overlap between our short- and long-range LIDARs. This sensor overlap meant that as it approached the final altitude, the sensor differences resulted in a delay in actually reaching the desired altitude.  
        </p>
        <!--Takeoff Time to 400mm graph-->
        <img src="Images\Graphs\Takeoff Time 400.png" alt="Takeoff Time Graph">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp; Once it was established that the drone could successfully takeoff, a unit step altitude test was performed. This involved establishing stable flight at an altitude of 50mm and then adjusting the setting to a new height of 70mm. In the execution of this maneuver, the drone initially lost altitude before beginning to climb due to a temporary loss of synchronization between motors. The unit then overshot the desired altitude and took three cycles before it could finally correct to the desired altitude.  
        </p>
        <!--Unit Step Graph-->
        <img src="Images\Graphs\Unit Step Altitude.png" alt="Unit Step Graph">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;Testing continued with single axis motion testing. This was important to establish independent axis control by the programming and hardware. By placing the unit in the single axis test unit and having it store small data runs on the onboard memory, data was captured on stabilization following an outside force applied to the hovering drone. The unit was rocked in the roll position and the roll angle was captured for 5 seconds. In this time after the initial velocity of the force wore off, the resonance in the test rig wiring interfered with the drone. But after that too wore off the drone successfully entered system resonance. Although this means that it was never perfectly still, it did show that with gain adjustments in the PID program that resonance should be able to be eliminated.  
        </p>
        <!--Single Axis Motion Testing-->
        <img src="Images\Photos\Altitude-Test-Unit.png" alt="Single Axis Motion Testing Setup">
        <!--Roll Angle Recovery Graph-->
        <img src="Images\Graphs\Roll Angle.png" alt="Roll Angle Graph">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;  The communication system of our UAS introduces latency within the system; thus, a unit test for communication latency must be performed to determine appropriate data refresh rates from our ground control station and our UAS module. The latency test was performed for an entire data refresh cycle. This cycle consists multiple actions. The first of these actions is an initial transmit of data from the ground station to the UAS. This transmit then waits for an acknowledgement. If the acknowledgement is not received, a timeout value is reached and the cycle progresses. If an acknowledgment is received, then the cycle will progress. The next portion of the information exchange cycle is where the data read from the UAS’s onboard sensors is transmitted the ground station, which listens on the specified port for incoming datagram packets.  This data is then received in string format, parsed, and placed within data structures.  
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;The entire cycles latency was measured from the ground station by measuring the system time at the beginning of the first stage of our data communication cycle and at the end of the data communication cycle. These two measured system times were subtracted to find the difference in milliseconds. After running 102 data communication samples, the data was exported to an Excel file. The graph and data analytics demonstrated below were generated within Microsoft Excel. 
        </p>
        <!--Latency Graph-->
        <img src="Images\Graphs\LatencyPlot.svg" alt="Latency Test Graph">
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp; The average transmit-receive latency was 540.245 milliseconds. Since User Datagram Protocol has limited error checking, the communication speeds are highly variable. This is apparent on the graph, which shows that most of the transmissions required around 255 milliseconds; however, due to the outliers, the average was increased to double that. The standard deviation is 512.995 milliseconds, which shows that based on a normalized Gaussian distribution, the 68.2% of our data lies within the one an interval of 512.995 milliseconds from our mean latency of 540.245 milliseconds.  
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp; The main benefactors of our project would most likely be those who require unmanned aerial systems for security applications (such as the United States government or private security industry,) or anyone who wants an unmanned aerial system designed with transparency in mind. Creating a successful product could inspire other engineers to design more domestically based aerial systems, resulting in more quality products of domestic origin. 
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp; The Wildflower has great potential for use inside the government sector, particularly because of the need for secure and domestic UAVs if the government wishes to use them at all. However, the future researchers will implement other functionalities on the Wildflower, allowing it to be used in a wide array of applications through attachable modules.. 
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp; The final design will have some form of replaceable arms with designated break points
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp; The Project Wildflower UAS is currently a PCB that can hover and maintain stability amongst a single axis. The PCB and brushed DC motor circuitry have been completed and we are able to communicate with the UAS through UDP over WiFi. The information sent from the ground station to the UAS serves as control information for the UAS, while the return data to the ground station serves as data from the sensors. Altogether, the communication system is fully functional. The UAS’s onboard sensors are also functioning entirely. The microcontroller can communicate with the sensors via I2C protocol. The data is then stored on the microcontroller in a data structure. Research and prototype boards have also been designed for further development with brushless DC motors in the future.  
        </p>
        <hr>
      </div>
    </div>
    <!--Section 7: Conclusion-->
    <div id="Conclusion">
      <h1>Conclusion</h1>
      <div>
        <p> 
          &nbsp;&nbsp;&nbsp;&nbsp;This course provided our team with an incredible opportunity to learn about the many facets of designing and building an electrical engineering project. Starting out, there was not a single person on our entire team who knew how to do more than one or two of the skills out of the many that this project required. Dr. Lofaro was an incredible mentor throughout our entire learning process, sometimes devoting an entire hour of our weekly meetings to explaining a concept. We have developed many skills and methods during the course of this senior design project that we will be able to apply to our careers and even our personal lives. 
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;First, we learned an incredible amount about PCB design. Prior to this semester, none of us had really done much in the way of designing circuits on a PCB. The few of us that had had done so as part of a course that they had taken in the EE program. Throughout the semester, several of our team members developed and honed their skills through prototype development. Our team made four BLDC boards and three brushed DC boards. 
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;The first few boards that we developed were really rough. We made a lot of design mistakes, things were not organized, and we left empty spaces on a board that was meant to be as tiny as possible in order to reduce the gross weight of the drone. Our biggest mistake in maximizing the “real estate” of the board was in using the Auto-Routing tool in EagleCAD, which made more of a mess than we ever could have made by hand. That was an important lesson to learn about apparent ease of use versus knowing how to do things manually. As we continued on, our board prototypes got better and better. We moved on from boards which could operate one BLDC motor to boards that could operate all four BLDCs. When we decided that we needed to switch away from BLDC motors and instead use brushed DC motors, we had already developed the PCB layout skills necessary to produce those brushed boards incredibly easily. 
        </p>
        <p>
          &nbsp;&nbsp;&nbsp;&nbsp;Our team also learned about the Agile Iterative Process and the V-Model Unit Testing Process. At the start of the semester, none of us had ever heard of either of these processes. By the end of the semester, we are well versed in their applications. This is important because some workplaces operate using the Agile Iterative Process, so knowing how it works would give our group members an advantage applying to such organizations. The Agile Iterative Process also taught us about keeping up on our tasks. Although one of the main benefits of Agile is that multiple tasks can be completed in parallel, we did not have the luxury of slacking off due to the ECE492/3 project backlog. Since we already knew what we had to start and when we had to start it, we were all kept accountable for any missed work that would impede the progress of future iterations of the project. 
        </p>
        <hr>
      </div>
    </div>
    <!--Section 8: References-->
    <div id="References">
      <h1>References</h1>
      <div>
        <p> 
          [1] “How U.S. agencies’ trust in untested software opened the door to hackers - POLITICO.” <a href="https://www.politico.com/news/2020/12/19/how-federal-hack-happened-448602">https://www.politico.com/news/2020/12/19/how-federal-hack-happened-448602</a> (<em>accessed Apr. 29, 2021</em>). 
        </p>
        <p>
          [2] S. H. Stone Mike, “U.S. Justice Department seeks to curb risks of foreign-made drones,” <em>Reuters</em>, Oct. 08, 2020. 
        </p>
        <p>
          [3] J. Daniels, “US Army reportedly bans Chinese-made drone, citing ‘cyber vulnerabilities,’” CNBC, Aug. 04, 2017.<a href="https://www.cnbc.com/2017/08/04/us-army-bans-chinese-made-drone-citing-cyber-vulnerabilities.html"> https://www.cnbc.com/2017/08/04/us-army-bans-chinese-made-drone-citing-cyber-vulnerabilities.html </a> (<em>accessed Apr. 30, 2021</em>). 
        </p>
        <p>
          [4] “Statement Regarding Commercial Drones Security Issues | Research and Creative Activity | NDSU.” <a href="https://www.ndsu.edu/research/for_researchers/unmanned_aircraft_systems/statement_regarding_commercial_drones_security_issues/">https://www.ndsu.edu/research/for_researchers/unmanned_aircraft_systems/statement_regarding_commercial_drones_security_issues/ </a> (<em>accessed Apr. 22, 2021</em>). 
        </p>
        <p>
          [5] M. McNabb, “No Department of Justice Funds for DJI Drones: DOJ Makes the Ban Official, but Some Federal Agencies May Suffer,” DRONELIFE, Oct. 09, 2020. <a href="https://dronelife.com/2020/10/09/no-federal-funds-for-dji-drones-doj-makes-the-ban-official-but-some-federal-agencies-may-suffer/">https://dronelife.com/2020/10/09/no-federal-funds-for-dji-drones-doj-makes-the-ban-official-but-some-federal-agencies-may-suffer/ </a>(<em>accessed Apr. 30, 2021</em>). 
        </p>
        <hr>
      </div>
    </div>
    <!--Project Presentation-->
    <div id="ProjectPresentation">
      <h1> Our Project Presentation</h1>
      <h3>QR Code to Project Wildflower Presentation on YouTube</h3>
      <img src="" alt="YouTube Presentation QR Code">
      <ul>
        <li><a href="" target="_blank">Project Wildflower Presentation (GitHub)</a></li>
        <li><a href="" target="_blank">Project Wildflower Presentation (YouTube)</a></li>
      </ul>    
    </div>
    <!--Copyright Information-->
    <footer> <small>&copy; Copyright 2021, Lofaro Labs</small> </footer>
    </body>
</html>
