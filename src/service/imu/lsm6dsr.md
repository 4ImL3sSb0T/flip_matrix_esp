# iNEMO inertial module: always-on 3D accelerometer and 3D gyroscope

![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/6503d9d6cdb8183fc29a1662c65534451ff56ff4eae07ae0b9e271221acbda1a.jpg)


# Features

• Extended full-scale range for gyroscope up to 4000 dps 

High stability over temperature and time 

Smart FIFO up to 9 kbytes 

. Android compliant 

• Auxiliary SPI for OIS data output for gyroscope and accelerometer 

±2/±4/±8/±16 g full scale 

±125/±250/±500/±1000/±2000/±4000 dps full scale 

• Analog supply voltage: 1.71 V to 3.6 V 

SPI / I²C & MIPI I3CSM serial interface with main processor data synchronization 

· Supports sensor synchronization S4S for Qualcomm, full spec compliant (I²C, MIPI I3CSM, SPI) 

. Advanced pedometer, step detector and step counter 

Significant Motion Detection, tilt detection 

• Programmable Finite State Machine: accelerometer, gyroscope, and external sensors 

Standard interrupts: free-fall, wakeup, 6D/4D orientation, click and double-click 

Embedded temperature sensor 

ECOPACK, RoHS and “Green” compliant 


Product status link



LSM6DSR



Product summary


<table><tr><td>Order code</td><td>LSM6DSR</td><td>LSM6DSRTR</td></tr><tr><td>Temp. range [°C]</td><td colspan="2">-40 to +85</td></tr><tr><td>Package</td><td colspan="2">LGA-14L(2.5 x 3.0 x 0.83 mm)</td></tr><tr><td>Packing</td><td>Tray</td><td>Tape &amp; Reel</td></tr></table>


Product label


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/aa7cbb968f4d7baf8e1897851e428d15a5dc2e56006d58481a701be6c5576496.jpg)


# Product resources

AN5358 (LSM6DSR) 

AN5390 (Finite State Machine) 

TN0018 (Design and soldering) 

# Applications

Motion tracking and gesture detection 

Virtual and augmented reality 

OIS for camera applications 

· Sensor hub 

Indoor navigation 

IoT and connected devices 

Sports applications 

Vibration monitoring and compensation 

Drones 

Robotics 

· High-precision systems 

# Description

The LSM6DSR is a system-in-package featuring a 3D digital accelerometer and a 3D digital gyroscope with an extended full-scale range for the gyroscope, up to 4000 dps, and high stability over temperature and time. 

The LSM6DSR supports main OS requirements, offering real, virtual and batch sensors with 9 kbytes with FIFO compression up to three times for dynamic data batching. 

ST’s family of MEMS sensor modules leverages the robust and mature manufacturing processes already used for the production of micromachined accelerometers and gyroscopes. 

The LSM6DSR has a full-scale acceleration range of ±2/±4/±8/±16 g and an angular rate range of ±125/±250/±500/±1000/±2000/±4000 dps. 

The LSM6DSR embeds a broad range of advanced functions supporting Android wearable sensors and programmable sensors (suitable for activity recognition). 

The LSM6DSR is available in a plastic land grid array (LGA) package. 

# 1 Overview

The LSM6DSR is a system-in-package featuring a high-performance 3-axis digital accelerometer and 3-axis digital gyroscope. 

The LSM6DSR delivers best-in-class motion sensing that can detect orientation and gestures in order to empower application developers and consumers with features and capabilities that are more sophisticated than simply orienting their devices to portrait and landscape mode. 

This device is suitable for augmented reality and virtual reality applications as well as Optical Image Stabilization and motion-based gaming controllers as a result of its high stability over temperature and time, combined with superior sensing precision. 

The LSM6DSR fully supports OIS applications using both the gyroscope and accelerometer sensor. The device can output OIS data through a dedicated auxiliary SPI and includes a dedicated configurable signal processing path for OIS. For both the gyroscope and accelerometer, the UI signal processing path is completely independent from that of the OIS and is readable through FIFO. Moreover, self -test and full scale are available for both the UI and OIS chains. 

The event-detection interrupts enable efficient and reliable motion tracking and contextual awareness, implementing hardware recognition of free-fall events, 6D orientation, click and double-click sensing, activity or inactivity, and wakeup events. 

The LSM6DSR supports main OS requirements, offering real, virtual and batch mode sensors. In addition, the LSM6DSR can efficiently run the sensor-related features specified in Android. In particular, the LSM6DSR has been designed to implement hardware features such as significant motion, tilt, pedometer functions, timestamping and to support the data acquisition of an external magnetometer. 

The LSM6DSR offers hardware flexibility to connect the pins with different mode connections to external sensors to expand functionalities such as adding a sensor hub. 

Up to 9 kbytes of FIFO with compression and dynamic allocation of significant data (i.e. external sensors, timestamp, etc.) allows overall power saving of the system. 

Like the entire portfolio of MEMS sensor modules, the LSM6DSR leverages the robust and mature in-house manufacturing processes already used for the production of micromachined accelerometers and gyroscopes. The various sensing elements are manufactured using specialized micromachining processes, while the IC interfaces are developed using CMOS technology that allows the design of a dedicated circuit which is trimmed to better match the characteristics of the sensing element. 

The LSM6DSR is available in a small plastic land grid array (LGA) package of 2.5 x 3.0 x 0.83 mm to address ultra-compact solutions. 

# 2 Embedded low-power features

The LSM6DSR has been designed to be fully compliant with Android, featuring the following on-chip functions: 

9 kbytes data buffering, data can be compressed two or three times 

100% efficiency with flexible configurations and partitioning 

Possibility to store timestamp 

Event-detection interrupts (fully configurable): 

Free-fall 

Wakeup 

6D orientation 

Click and double-click sensing 

Activity/inactivity recognition 

Stationary/Motion detection 

Specific IP blocks with negligible power consumption and high-performance: 

Pedometer functions: step detector and step counters 

Tilt 

Significant Motion Detection 

Finite State Machine (FSM) for accelerometer, gyroscope, and external sensors 

Sensor hub 

Up to 6 total sensors: 2 internal (accelerometer and gyroscope) and 4 external sensors 

S4S data rate synchronization with external trigger for reduced sensor access and enhanced fusion 

# 2.1 Tilt detection

The tilt function helps to detect activity change and has been implemented in hardware using only the accelerometer to achieve targets of both ultra-low power consumption and robustness during the short duration of dynamic accelerations. 

The tilt function is based on a trigger of an event each time the device's tilt changes and can be used with different scenarios, for example: 

Triggers when phone is in a front pants pocket and the user goes from sitting to standing or standing to sitting; 

· Doesn’t trigger when phone is in a front pants pocket and the user is walking, running or going up stairs. 

# 2.2 Significant Motion Detection

The Significant Motion Detection (SMD) function generates an interrupt when a ‘significant motion’, that could be due to a change in user location, is detected. In the LSM6DSR device this function has been implemented in hardware using only the accelerometer. 

SMD functionality can be used in location-based applications in order to receive a notification indicating when the user is changing location. 

# 2.3 Finite State Machine

The LSM6DSR can be configured to generate interrupt signals activated by user-defined motion patterns. To do this, up to 16 embedded finite state machines can be programmed independently for motion detection such as glance gestures, absolute wrist tilt, shake and double-shake detection. 

# Definition of Finite State Machine

A state machine is a mathematical abstraction used to design logic connections. It is a behavioral model composed of a finite number of states and transitions between states, similar to a flow chart in which one can inspect the way logic runs when certain conditions are met. The state machine begins with a start state, goes to different states through transitions dependent on the inputs, and can finally end in a specific state (called stop state). The current state is determined by the past states of the system. The following figure shows a generic state machine. 


Figure 1. Generic state machine


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/8138e36cf06c322ab90c7fdb8d2a3c0154d464dc7811790100f1040fcdb70a4a.jpg)


# Finite State Machine in the LSM6DSR

The LSM6DSR works as a combo accelerometer-gyroscope sensor, generating acceleration and angular rate output data. It is also possible to connect an external sensor (magnetometer) by using the Sensor Hub feature (Mode 2). These data can be used as input of up to 16 programs in the embedded Finite State Machine (Figure 2. State machine in the LSM6DSR). 

All 16 finite state machines are independent: each one has its dedicated memory area and it is independently executed. An interrupt is generated when the end state is reached or when some specific command is performed. 


Figure 2. State machine in the LSM6DSR


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/01e9862a03a0fa65cf77ae62201194ecec82659d46cf04dffa2c4fdf7997f64c.jpg)


# 3 Pin description


Figure 3. Pin connections


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/749f3247fbc905bde87bf331563704094b99dd08ff6cd02d434a3482b513e951.jpg)



Direction of detectable acceleration (top view)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/d2cbd70db94f43a59c85e26a79631b6daa5c04b58b8d4748be37a4248cde7bbd.jpg)



Direction of detectable angular rate (top view)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/9894651c3b3105296dd71f6b794585f37d1c03f59144f9ff17c66b95e87f391c.jpg)


# 3.1 Pin connections

The LSM6DSR offers flexibility to connect the pins in order to have four different mode connections and functionalities. In detail: 

Mode 1: I²C / MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ slave interface or SPI (3- and 4-wire) serial interface is available; 

Mode 2: I²C / MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ slave interface or SPI (3- and 4-wire) serial interface and I²C interface master for external sensor connections are available; 

Mode 3: I²C/ MIPI $| 3 C ^ { \mathsf { S M } }$ slave interface or SPI (3- and 4-wire) serial interface is available for the application processor interface while an auxiliary SPI (3- and 4-wire) serial interface for external sensor connections is available for the gyroscope ONLY; 

Mode 4: I²C / MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ slave interface or SPI (3- and 4-wire) serial interface is available for the application processor interface while an auxiliary SPI (3- and 4-wire) serial interface for external sensor connections is available for the accelerometer and gyroscope. 


Figure 4. LSM6DSR connection modes


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/146e2a92d2371ffcd41118bad21b1f8d9da7e2dffe83270b08078ad949c4b269.jpg)


In the following table each mode is described for the pin connections and function. 


Table 1. Pin description


<table><tr><td>Pin #</td><td>Name</td><td>Mode 1 function</td><td>Mode 2 function</td><td>Mode 3/4 function</td></tr><tr><td>1</td><td>SDO/SA0</td><td>SPI 4-wire interface serial data output (SDO)I2C least significant bit of the device address (SA0)</td><td>SPI 4-wire interface serial data output (SDO)I2C least significant bit of the device address (SA0)</td><td>SPI 4-wire interface serial data output (SDO)I2C least significant bit of the device address (SA0)</td></tr><tr><td>2</td><td>SDx</td><td>Connect to Vdd_IO or GND</td><td>I2C serial data master (MSDA)</td><td>Auxiliary SPI 3/4-wire interface serial data input (SDI) and SPI 3-wire serial data output (SDO)</td></tr><tr><td>3</td><td>SCx</td><td>Connect to Vdd_IO or GND</td><td>I2C serial clock master (MSCL)</td><td>Auxiliary SPI 3/4-wire interface serial port clock (SPC_Aux)</td></tr><tr><td>4</td><td>INT1</td><td colspan="3">Programmable interrupt in I2C and SPI</td></tr><tr><td>5</td><td>Vdd_IO(1)</td><td colspan="3">Power supply for I/O pins</td></tr><tr><td>6</td><td>GND</td><td colspan="3">0 V supply</td></tr><tr><td>7</td><td>GND</td><td colspan="3">0 V supply</td></tr><tr><td>8</td><td>Vdd(1)</td><td colspan="3">Power supply</td></tr><tr><td>9</td><td>INT2</td><td>Programmable interrupt 2 (INT2) / Data enabled (DEN)</td><td>Programmable interrupt 2 (INT2) / Data enabled (DEN) / I2C master external synchronization signal (MDRDY)</td><td>Programmable interrupt 2 (INT2) / Data enabled (DEN)</td></tr><tr><td>10</td><td>OCS_Aux</td><td>Leave unconnected(2)</td><td>Leave unconnected(2)</td><td>Auxiliary SPI 3/4-wire interface enable</td></tr><tr><td>11</td><td>SDO_Aux</td><td>Connect to Vdd_IO or leave unconnected(2)</td><td>Connect to Vdd_IO or leave unconnected(2)</td><td>Auxiliary SPI 3-wire interface: leave unconnected(2)Auxiliary SPI 4-wire interface: serial data output (SDO_Aux)</td></tr><tr><td>12</td><td>CS</td><td>I2C and MIPI I3CSM/SPI mode selection (1: SPI idle mode / I2C and MIPI I3CSM communication enabled; 0: SPI communication mode / I2C and MIPI I3CSM disabled)</td><td>I2C and MIPI I3CSM/SPI mode selection (1: SPI idle mode / I2C and MIPI I3CSM communication enabled; 0: SPI communication mode / I2C and MIPI I3CSM disabled)</td><td>I2C and MIPI I3CSM/SPI mode selection (1: SPI idle mode / I2C and MIPI I3CSM communication enabled; 0: SPI communication mode / I2C, and MIPI I3CSM disabled)</td></tr><tr><td>13</td><td>SCL</td><td>I2C/MIPI I3CSMserial clock (SCL) / SPI serial port clock (SPC)</td><td>I2C/MIPI I3CSMserial clock (SCL) / SPI serial port clock (SPC)</td><td>I2C/MIPI I3CSMserial clock (SCL) / SPI serial port clock (SPC)</td></tr><tr><td>14</td><td>SDA</td><td>I2C/MIPI I3CSMserial data (SDA)SPI serial data input (SDI)3-wire interface serial data output (SDO)</td><td>I2C/MIPI I3CSMserial data (SDA)SPI serial data input (SDI)3-wire interface serial data output (SDO)</td><td>I2C/MIPI I3CSMserial data (SDA)SPI serial data input (SDI)3-wire interface serial data output (SDO)</td></tr></table>


1. Recommended 100 nF filter capacitor. 



2. Leave pin electrically unconnected and soldered to PCB. 


# 4 Module specifications

# 4.1 Mechanical characteristics


1. Typical specifications are not guaranteed. 


@ $\angle 1 . 8 \mathsf { V } , \mathsf { T } = 2 5 ^ { \circ } \mathsf { C } ,$ unless otherwise noted. 


2. Sensitivity values after factory calibration test and trimming. 



Table 2. Mechanical characteristics



3. Subject to change. 


<table><tr><td>Symbol</td><td>Parameter</td><td>Test conditions</td><td>Min.</td><td><eq>Typ.^{(1)}</eq></td><td>Max.</td><td>Unit</td></tr><tr><td rowspan="4">LA_FS</td><td rowspan="4">Linear acceleration measurement range</td><td></td><td></td><td>±2</td><td></td><td rowspan="4">g</td></tr><tr><td></td><td></td><td>±4</td><td></td></tr><tr><td></td><td></td><td>±8</td><td></td></tr><tr><td></td><td></td><td>±16</td><td></td></tr><tr><td rowspan="6">G_FS</td><td rowspan="6">Angular rate measurement range</td><td></td><td></td><td>±125</td><td></td><td rowspan="6">dps</td></tr><tr><td></td><td></td><td>±250</td><td></td></tr><tr><td></td><td></td><td>±500</td><td></td></tr><tr><td></td><td></td><td>±1000</td><td></td></tr><tr><td></td><td></td><td>±2000</td><td></td></tr><tr><td></td><td></td><td>±4000</td><td></td></tr><tr><td rowspan="4">LA_So</td><td rowspan="4">Linear acceleration <eq>sensitivity^{(2)}</eq></td><td>FS = ±2 g</td><td></td><td>0.061</td><td></td><td rowspan="4">mg/LSB</td></tr><tr><td>FS = ±4 g</td><td></td><td>0.122</td><td></td></tr><tr><td>FS = ±8 g</td><td></td><td>0.244</td><td></td></tr><tr><td>FS = ±16 g</td><td></td><td>0.488</td><td></td></tr><tr><td rowspan="6">G_So</td><td rowspan="6">Angular rate <eq>sensitivity^{(2)}</eq></td><td>FS = ±125 dps</td><td></td><td>4.375</td><td></td><td rowspan="6">mdps/LSB</td></tr><tr><td>FS = ±250 dps</td><td></td><td>8.75</td><td></td></tr><tr><td>FS = ±500 dps</td><td></td><td>17.50</td><td></td></tr><tr><td>FS = ±1000 dps</td><td></td><td>35</td><td></td></tr><tr><td>FS = ±2000 dps</td><td></td><td>70</td><td></td></tr><tr><td>FS = ±4000 dps</td><td></td><td>140</td><td></td></tr><tr><td>G_So%</td><td><eq>Sensitivity tolerance^{(3)}</eq></td><td>at component level</td><td></td><td>±1</td><td></td><td>%</td></tr><tr><td>LA_SoDr</td><td>Linear acceleration sensitivity change vs. <eq>temperature^{(4)}</eq></td><td>from -40 °C to +85 °C</td><td></td><td>±0.01</td><td></td><td>%/°C</td></tr><tr><td>G_SoDr</td><td>Angular rate sensitivity change vs. <eq>temperature^{(4)}</eq></td><td>from -40 °C to +85 °C</td><td></td><td>±0.007</td><td></td><td>%/°C</td></tr><tr><td>LA_TyOff</td><td>Linear acceleration zero-g level offset <eq>accuracy^{(5)}</eq></td><td></td><td></td><td>±10</td><td></td><td>mg</td></tr><tr><td>G_TyOff</td><td>Angular rate zero-rate <eq>level^{(5)}</eq></td><td></td><td></td><td>±1</td><td></td><td>dps</td></tr><tr><td>LA_OffDr</td><td>Linear acceleration zero-g level change vs. <eq>temperature^{(4)}</eq></td><td></td><td></td><td>±0.1</td><td></td><td>mg/°C</td></tr><tr><td>G_OffDr</td><td>Angular rate typical zero-rate level change vs. <eq>temperature^{(4)}</eq></td><td></td><td></td><td>±0.005</td><td></td><td>dps/°C</td></tr><tr><td>Rn</td><td>Rate noise density in high-performance <eq>mode^{(6)}</eq></td><td></td><td></td><td>5</td><td></td><td>mdps/√Hz</td></tr><tr><td>RnRMS</td><td>Gyroscope RMS noise in low-power <eq>mode^{(7)}</eq></td><td></td><td></td><td>90</td><td></td><td>mdps</td></tr><tr><td>An</td><td>Acceleration noise density in high-performance <eq>mode^{(8)}</eq></td><td></td><td></td><td>60</td><td></td><td>μg/√Hz</td></tr><tr><td>RMS</td><td>Acceleration RMS noise in low-power <eq>mode^{(9)(10)}</eq></td><td></td><td></td><td>1.8</td><td></td><td>mg(RMS)</td></tr><tr><td rowspan="11">LA_ODR</td><td rowspan="11">Linear acceleration output data rate</td><td rowspan="11"></td><td rowspan="11"></td><td>1.6(11)</td><td rowspan="11"></td><td rowspan="20">Hz</td></tr><tr><td>12.5</td></tr><tr><td>26</td></tr><tr><td>52</td></tr><tr><td>104</td></tr><tr><td>208</td></tr><tr><td>416</td></tr><tr><td>833</td></tr><tr><td>1666</td></tr><tr><td>3332</td></tr><tr><td>6667</td></tr><tr><td rowspan="9">G_ODR</td><td rowspan="9">Angular rate output data rate</td><td rowspan="9"></td><td rowspan="9"></td><td>12.5</td><td rowspan="9"></td></tr><tr><td>26</td></tr><tr><td>52</td></tr><tr><td>104</td></tr><tr><td>208</td></tr><tr><td>416</td></tr><tr><td>833</td></tr><tr><td>1666</td></tr><tr><td>3332</td></tr><tr><td rowspan="3">Vst</td><td>Linear acceleration self-test <eq>output\ change^{(12)}</eq>(13)(14)</td><td></td><td>40</td><td></td><td>1700</td><td>mg</td></tr><tr><td rowspan="2">Angular rate self-test <eq>output\ change^{(15)(16)}</eq></td><td>FS = ±250 dps</td><td>20</td><td></td><td>80</td><td>dps</td></tr><tr><td>FS = ±2000 dps</td><td>150</td><td></td><td>700</td><td>dps</td></tr><tr><td>Top</td><td>Operating temperature range</td><td></td><td>-40</td><td></td><td>+85</td><td>°C</td></tr></table>


4. Measurements are performed in a uniform temperature setup and they are based on characterization data in a limited number of samples. Not measured during final test for production. 



5. Values after factory calibration test and trimming. 



6. Gyroscope rate noise density in high-performance mode is independent of the ODR and FS setting. 



7. Gyroscope RMS noise in low-power mode is independent of the ODR and FS setting. 



8. Accelerometer noise density in high-performance mode is independent of the ODR and full scale. 



9. Accelerometer RMS noise in low-power mode is independent of the ODR. 



10. Noise RMS related to BW = ODR/2. 



11. This ODR is available when the accelerometer is in low-power mode. 



12. The sign of the linear acceleration self-test output change is defined by the STx_XL bits in a dedicated register for all axes. 



13. The linear acceleration self-test output change is defined with the device in stationary condition as the absolute value of: OUTPUT[LSb] (self-test enabled) - OUTPUT[LSb] (self-test disabled). 1LSb = 0.061 mg at ±2 g full scale. 



14. Accelerometer self-test limits are full-scale independent. 



15. The sign of the angular rate self-test output change is defined by the STx_G bits in a dedicated register for all axes. 



16. The angular rate self-test output change is defined with the device in stationary condition as the absolute value of: OUTPUT[LSb] (self-test enabled) - OUTPUT[LSb] (self-test disabled). 1LSb = 70 mdps at ±2000 dps full scale 


# 4.2 Electrical characteristics

@ $\mathsf { V d d } = 1 . 8 \mathsf { V } , \mathsf { T } = 2 5 ^ { \circ } \mathsf { C }$ , unless otherwise noted. 


Table 3. Electrical characteristics


<table><tr><td>Symbol</td><td>Parameter</td><td>Test conditions</td><td>Min.</td><td><eq>Typ.^{(1)}</eq></td><td>Max.</td><td>Unit</td></tr><tr><td>Vdd</td><td>Supply voltage</td><td></td><td>1.71</td><td>1.8</td><td>3.6</td><td>V</td></tr><tr><td>Vdd_IO</td><td>Power supply for I/O</td><td></td><td>1.62</td><td></td><td>3.6</td><td>V</td></tr><tr><td>IddHP</td><td>Gyroscope and accelerometer current consumption in high-performance mode</td><td></td><td></td><td>1.2</td><td></td><td>mA</td></tr><tr><td>IddNM</td><td>Gyroscope and accelerometer current consumption in normal mode</td><td>ODR = 208 Hz</td><td></td><td>0.7</td><td></td><td>mA</td></tr><tr><td>LA_IddHP</td><td>Accelerometer current consumption in high-performance mode</td><td></td><td></td><td>360</td><td></td><td>μA</td></tr><tr><td rowspan="3">LA_IddLM</td><td rowspan="3">Accelerometer current consumption in low-power mode</td><td>ODR = 52 Hz</td><td></td><td>32</td><td></td><td rowspan="3">μA</td></tr><tr><td>ODR = 12.5 Hz</td><td></td><td>11</td><td></td></tr><tr><td>ODR = 1.6 Hz</td><td></td><td>5.5</td><td></td></tr><tr><td>IddPD</td><td>Gyroscope and accelerometer current consumption during power-down</td><td></td><td></td><td>3</td><td></td><td>μA</td></tr><tr><td>Ton</td><td>Turn-on time</td><td></td><td></td><td>35</td><td></td><td>ms</td></tr><tr><td><eq>V_{IH}</eq></td><td>Digital high-level input voltage</td><td></td><td>0.7 * Vdd_IO</td><td></td><td></td><td>V</td></tr><tr><td><eq>V_{IL}</eq></td><td>Digital low-level input voltage</td><td></td><td></td><td></td><td>0.3 * Vdd_IO</td><td>V</td></tr><tr><td><eq>V_{OH}</eq></td><td>Digital high-level output voltage</td><td><eq>I_{OH}=4 mA^{(2)}</eq></td><td>Vdd_IO - 0.2</td><td></td><td></td><td>V</td></tr><tr><td><eq>V_{OL}</eq></td><td>Digital low-level output voltage</td><td><eq>I_{OL}=4 mA^{(2)}</eq></td><td></td><td></td><td>0.2</td><td>V</td></tr><tr><td>Top</td><td>Operating temperature range</td><td></td><td>-40</td><td></td><td>+85</td><td>°C</td></tr></table>

1. Typical specifications are not guaranteed. 

2. 4 mA is the minimum driving capability, i.e. the minimum DC current that can be sourced/sunk by the digital pad in order to guarantee the correct digital output voltage levels $V _ { O H }$ and $V _ { O L }$ . 

# 4.3 Temperature sensor characteristics

@ $\mathsf { V d d } = 1 . 8 \mathsf { V } , \mathsf { T } = 2 5 ^ { \circ } \mathsf { C }$ unless otherwise noted. 


Table 4. Temperature sensor characteristics


<table><tr><td>Symbol</td><td>Parameter</td><td>Test condition</td><td>Min.</td><td><eq>Typ.^{(1)}</eq></td><td>Max.</td><td>Unit</td></tr><tr><td><eq>TODR^{(2)}</eq></td><td>Temperature refresh rate</td><td></td><td></td><td>52</td><td></td><td>Hz</td></tr><tr><td>Toff</td><td><eq>Temperature offset^{(3)}</eq></td><td></td><td>-15</td><td></td><td>+15</td><td>°C</td></tr><tr><td>TSen</td><td>Temperature sensitivity</td><td></td><td></td><td>256</td><td></td><td>LSB/°C</td></tr><tr><td>TST</td><td><eq>Temperature stabilization time^{(4)}</eq></td><td></td><td></td><td></td><td>500</td><td>μs</td></tr><tr><td>T_ADC_res</td><td>Temperature ADC resolution</td><td></td><td></td><td>16</td><td></td><td>bit</td></tr><tr><td>Top</td><td>Operating temperature range</td><td></td><td>-40</td><td></td><td>+85</td><td>°C</td></tr></table>

1. Typical specifications are not guaranteed. 

2. When the accelerometer is in low-power mode and the gyroscope part is turned off, the TODR value is equal to the accelerometer ODR. 

3. The output of the temperature sensor is 0 LSB $( t y p . )$ at $2 5 ^ { \circ } C .$ 

4. Time from power ON to valid output data. Based on characterization data. 

# 4.4 Communication interface characteristics

# 4.4.1 SPI - serial peripheral interface

Subject to general operating conditions for Vdd and Top. 


Table 5. SPI slave timing values (in mode 3)


<table><tr><td rowspan="2">Symbol</td><td rowspan="2">Parameter</td><td colspan="2">Value(1)</td><td rowspan="2">Unit</td></tr><tr><td>Min</td><td>Max</td></tr><tr><td><eq>t_{c(SPC)}</eq></td><td>SPI clock cycle</td><td>100</td><td></td><td>ns</td></tr><tr><td><eq>f_{c(SPC)}</eq></td><td>SPI clock frequency</td><td></td><td>10</td><td>MHz</td></tr><tr><td><eq>t_{su(CS)}</eq></td><td>CS setup time</td><td>5</td><td></td><td rowspan="7">ns</td></tr><tr><td><eq>t_{h(CS)}</eq></td><td>CS hold time</td><td>20</td><td></td></tr><tr><td><eq>t_{su(SI)}</eq></td><td>SDI input setup time</td><td>5</td><td></td></tr><tr><td><eq>t_{h(SI)}</eq></td><td>SDI input hold time</td><td>15</td><td></td></tr><tr><td><eq>t_{v(SO)}</eq></td><td>SDO valid output time</td><td></td><td>50</td></tr><tr><td><eq>t_{h(SO)}</eq></td><td>SDO output hold time</td><td>5</td><td></td></tr><tr><td><eq>t_{dis(SO)}</eq></td><td>SDO output disable time</td><td></td><td>50</td></tr></table>


1. Values are guaranteed at 10 MHz clock frequency for SPI with both 4 and 3 wires, based on characterization results, not tested in production 



Figure 5. SPI slave timing diagram (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/80b2a71afe9a514a8e3e0b94a0e177d0e20e30874c6a95ad1868dbce087a22f9.jpg)



Note: Measurement points are done at 0.3·Vdd_IO and 0.7·Vdd_IO for both input and output ports.


# 4.4.2

# I²C - inter-IC control interface

Subject to general operating conditions for Vdd and Top. 


Table 6. I²C slave timing values


<table><tr><td rowspan="2">Symbol</td><td rowspan="2">Parameter</td><td colspan="2"><eq>I^{2}C fast mode^{(1)(2)}</eq></td><td colspan="2"><eq>I^{2}C fast mode +^{(1)(2)}</eq></td><td rowspan="2">Unit</td></tr><tr><td>Min</td><td>Max</td><td>Min</td><td>Max</td></tr><tr><td><eq>f_{(SCL)}</eq></td><td>SCL clock frequency</td><td>0</td><td>400</td><td>0</td><td>1000</td><td>kHz</td></tr><tr><td><eq>t_{w(SCLL)}</eq></td><td>SCL clock low time</td><td>1.3</td><td></td><td>0.5</td><td></td><td rowspan="2">μs</td></tr><tr><td><eq>t_{w(SCLH)}</eq></td><td>SCL clock high time</td><td>0.6</td><td></td><td>0.26</td><td></td></tr><tr><td><eq>t_{su(SDA)}</eq></td><td>SDA setup time</td><td>100</td><td></td><td>50</td><td></td><td>ns</td></tr><tr><td><eq>t_{h(SDA)}</eq></td><td>SDA data hold time</td><td>0</td><td>0.9</td><td>0</td><td></td><td rowspan="7">μs</td></tr><tr><td><eq>t_{h(ST)}</eq></td><td>START/REPEATED START condition hold time</td><td>0.6</td><td></td><td>0.26</td><td></td></tr><tr><td><eq>t_{su(SR)}</eq></td><td>REPEATED START condition setup time</td><td>0.6</td><td></td><td>0.26</td><td></td></tr><tr><td><eq>t_{su(SP)}</eq></td><td>STOP condition setup time</td><td>0.6</td><td></td><td>0.26</td><td></td></tr><tr><td><eq>t_{w(SP:SR)}</eq></td><td>Bus free time between STOP and START condition</td><td>1.3</td><td></td><td>0.5</td><td></td></tr><tr><td></td><td>Data valid time</td><td></td><td>0.9</td><td></td><td>0.45</td></tr><tr><td></td><td>Data valid acknowledge time</td><td></td><td>0.9</td><td></td><td>0.45</td></tr><tr><td><eq>C_B</eq></td><td>Capacitive load for each bus line</td><td></td><td>400</td><td></td><td>550</td><td>pF</td></tr></table>

1. Data based on standard I²C protocol requirement, not tested in production. 

2. Data for I²C fast mode and I²C fast mode + have been validated by characterization, not tested in production. 


Figure 6. I²C slave timing diagram


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/60b22f81f4197e582927b2b758b69633bd990cc0cef5808895684bad69a3ac72.jpg)



Note: Measurement points are done at 0.3·Vdd_IO and 0.7·Vdd_IO for both ports.


# 4.5 Absolute maximum ratings

Stresses above those listed as “Absolute maximum ratings” may cause permanent damage to the device. This is a stress rating only and functional operation of the device under these conditions is not implied. Exposure to maximum rating conditions for extended periods may affect device reliability. 


Table 7. Absolute maximum ratings


<table><tr><td>Symbol</td><td>Ratings</td><td>Maximum value</td><td>Unit</td></tr><tr><td>Vdd</td><td>Supply voltage</td><td>-0.3 to 4.8</td><td>V</td></tr><tr><td><eq>T_{STG}</eq></td><td>Storage temperature range</td><td>-40 to +125</td><td>°C</td></tr><tr><td>Sg</td><td>Acceleration g for 0.2 ms</td><td>20,000</td><td>g</td></tr><tr><td>ESD</td><td>Electrostatic discharge protection (HBM)</td><td>2</td><td>kV</td></tr><tr><td>Vin</td><td>Input voltage on any control pin(including CS, SCL/SPC, SDA/SDI/SDO, SDO/SA0)</td><td>-0.3 to Vdd_IO +0.3</td><td>V</td></tr></table>


Note: Supply voltage on any pin should never exceed 4.8 V. 


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/dadcb2f8426b0ebfa1321bf1c4cd938c679982238e078326991e2707b5a045d1.jpg)


This device is sensitive to mechanical shock, improper handling can cause permanent damage to the part. 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/f5a3479b05311f96b5b170922045e160f8ff1bde41db403cbb900d0443631698.jpg)


This device is sensitive to electrostatic discharge (ESD), improper handling can cause permanent damage to the part. 

# 4.6 Terminology

# 4.6.1 Sensitivity

Linear acceleration sensitivity can be determined, for example, by applying 1 g acceleration to the device. 

Because the sensor can measure DC accelerations, this can be done easily by pointing the selected axis towards the ground, noting the output value, rotating the sensor 180 degrees (pointing towards the sky) and noting the output value again. By doing so, ±1 g acceleration is applied to the sensor. Subtracting the larger output value from the smaller one, and dividing the result by 2, leads to the actual sensitivity of the sensor. This value changes very little over temperature and over time. The sensitivity tolerance describes the range of sensitivities of a large number of sensors (see Table 2). 

An angular rate gyroscope is a device that produces a positive-going digital output for counterclockwise rotation around the axis considered. Sensitivity describes the gain of the sensor and can be determined by applying a defined angular velocity to it. This value changes very little over temperature and time (see Table 2). 

# 4.6.2 Zero-g and zero-rate level

Linear acceleration zero-g level offset (TyOff) describes the deviation of an actual output signal from the ideal output signal if no acceleration is present. A sensor in a steady state on a horizontal surface will measure 0 g on both the X-axis and Y-axis, whereas the Z-axis will measure 1 g. Ideally, the output is in the middle of the dynamic range of the sensor (content of OUT registers 00h, data expressed as 2’s complement number). A deviation from the ideal value in this case is called zero-g offset. 

Offset is to some extent a result of stress to MEMS sensor and therefore the offset can slightly change after mounting the sensor onto a printed circuit board or exposing it to extensive mechanical stress. Offset changes little over temperature, see “Linear acceleration zero-g level change vs. temperature” in Table 2. The zero-g level tolerance (TyOff) describes the standard deviation of the range of zero-g levels of a group of sensors. 

Zero-rate level describes the actual output signal if there is no angular rate present. The zero-rate level of precise MEMS sensors is, to some extent, a result of stress to the sensor and therefore the zero-rate level can slightly change after mounting the sensor onto a printed circuit board or after exposing it to extensive mechanical stress. This value changes very little over temperature and time (see Table 2). 

# 5 Digital interfaces

# 5.1 I²C/SPI interface

The registers embedded inside the LSM6DSR may be accessed through both the I²C and SPI serial interfaces. The latter may be SW configured to operate either in 3-wire or 4-wire interface mode. The device is compatible with SPI modes 0 and 3. 

The serial interfaces are mapped onto the same pins. To select/exploit the I²C interface, the CS line must be tied high (i.e connected to Vdd_IO). 


Table 8. Serial interface pin description


<table><tr><td>Pin name</td><td>Pin description</td></tr><tr><td>CS</td><td>SPI enableI2C/SPI mode selection (1: SPI idle mode / I2C communication enabled;0: SPI communication mode / I2C disabled)</td></tr><tr><td>SCL/SPC</td><td>I2C Serial Clock (SCL)SPI Serial Port Clock (SPC)</td></tr><tr><td>SDA/SDI/SDO</td><td>I2C Serial Data (SDA)SPI Serial Data Input (SDI)3-wire Interface Serial Data Output (SDO)</td></tr><tr><td>SDO/SA0</td><td>SPI Serial Data Output (SDO)I2C less significant bit of the device address</td></tr></table>

# 5.1.1 I²C serial interface

The LSM6DSR I²C is a bus slave. The I²C is employed to write the data to the registers, whose content can also be read back. 

The relevant I²C terminology is provided in the table below. 


Table 9. I²C terminology


<table><tr><td>Term</td><td>Description</td></tr><tr><td>Transmitter</td><td>The device which sends data to the bus</td></tr><tr><td>Receiver</td><td>The device which receives data from the bus</td></tr><tr><td>Master</td><td>The device which initiates a transfer, generates clock signals and terminates a transfer</td></tr><tr><td>Slave</td><td>The device addressed by the master</td></tr></table>

There are two signals associated with the I²C bus: the serial clock line (SCL) and the Serial DAta line (SDA). The latter is a bidirectional line used for sending and receiving the data to/from the interface. Both the lines must be connected to Vdd_IO through external pull-up resistors. When the bus is free, both the lines are high. 

The I²C interface is implemented with fast mode (400 kHz) I²C standards as well as with fast mode plus (1000 kHz). 

In order to disable the I²C block, (I2C_disable) = 1 must be written in CTRL4_C (13h). 

# 5.1.1.1 I²C operation

The transaction on the bus is started through a START (ST) signal. A START condition is defined as a HIGH to LOW transition on the data line while the SCL line is held HIGH. After this has been transmitted by the master, the bus is considered busy. The next byte of data transmitted after the start condition contains the address of the slave in the first 7 bits and the eighth bit tells whether the master is receiving data from the slave or transmitting data to the slave. When an address is sent, each device in the system compares the first seven bits after a start condition with its address. If they match, the device considers itself addressed by the master. 

The Slave ADdress (SAD) associated to the LSM6DSR is 110101xb. The SDO/SA0 pin can be used to modify the less significant bit of the device address. If the SDO/SA0 pin is connected to the supply voltage, LSb is $\cdot _ { 1 } ,$ (address 1101011b); else if the SDO/SA0 pin is connected to ground, the LSb value is $\mathrm { \dot { \iota } } _ { 0 } { \dot { \iota } }$ (address 1101010b). This solution permits to connect and address two different inertial modules to the same I²C bus. 

Data transfer with acknowledge is mandatory. The transmitter must release the SDA line during the acknowledge pulse. The receiver must then pull the data line LOW so that it remains stable low during the HIGH period of the acknowledge clock pulse. A receiver which has been addressed is obliged to generate an acknowledge after each byte of data received. 

The I²C embedded inside the LSM6DSR behaves like a slave device and the following protocol must be adhered to. After the start condition (ST) a slave address is sent, once a slave acknowledge (SAK) has been returned, an 8-bit sub-address (SUB) is transmitted. The increment of the address is configured by the CTRL3_C (12h) (IF_INC). 

The slave address is completed with a Read/Write bit. If the bit is $" 1 "$ (Read), a repeated START (SR) condition must be issued after the two sub-address bytes; if the bit is $\mathbf { \vec { \omega } }$ (Write) the master will transmit to the slave with direction unchanged. Table 10 explains how the SAD+Read/Write bit pattern is composed, listing all the possible configurations. 


Table 10. SAD+Read/Write patterns


<table><tr><td>Command</td><td>SAD[6:1]</td><td>SAD[0] = SA0</td><td>R/W</td><td>SAD+R/W</td></tr><tr><td>Read</td><td>110101</td><td>0</td><td>1</td><td>11010101 (D5h)</td></tr><tr><td>Write</td><td>110101</td><td>0</td><td>0</td><td>11010100 (D4h)</td></tr><tr><td>Read</td><td>110101</td><td>1</td><td>1</td><td>11010111 (D7h)</td></tr><tr><td>Write</td><td>110101</td><td>1</td><td>0</td><td>11010110 (D6h)</td></tr></table>


Table 11. Transfer when master is writing one byte to slave


<table><tr><td>Master</td><td>ST</td><td>SAD + W</td><td></td><td>SUB</td><td></td><td>DATA</td><td></td><td>SP</td></tr><tr><td>Slave</td><td></td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td>SAK</td><td></td></tr></table>


Table 12. Transfer when master is writing multiple bytes to slave


<table><tr><td>Master</td><td>ST</td><td>SAD + W</td><td></td><td>SUB</td><td></td><td>DATA</td><td></td><td>DATA</td><td></td><td>SP</td></tr><tr><td>Slave</td><td></td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td>SAK</td><td></td></tr></table>


Table 13. Transfer when master is receiving (reading) one byte of data from slave


<table><tr><td>Master</td><td>ST</td><td>SAD + W</td><td></td><td>SUB</td><td></td><td>SR</td><td>SAD + R</td><td></td><td></td><td>NMAK</td><td>SP</td></tr><tr><td>Slave</td><td></td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td></td><td>SAK</td><td>DATA</td><td></td><td></td></tr></table>


Table 14. Transfer when master is receiving (reading) multiple bytes of data from slave


<table><tr><td>Master</td><td>ST</td><td>SAD+W</td><td></td><td>SUB</td><td></td><td>SR</td><td>SAD+R</td><td></td><td></td><td>MAK</td><td></td><td>MAK</td><td></td><td>NMAK</td><td>SP</td></tr><tr><td>Slave</td><td></td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td></td><td>SAK</td><td>DATA</td><td></td><td>DATA</td><td></td><td>DATA</td><td></td><td></td></tr></table>

Data are transmitted in byte format (DATA). Each data transfer contains 8 bits. The number of bytes transferred per transfer is unlimited. Data is transferred with the Most Significant bit (MSb) first. If a slave receiver doesn’t acknowledge the slave address (i.e. it is not able to receive because it is performing some real-time function) the data line must be left HIGH by the slave. The master can then abort the transfer. A LOW to HIGH transition on the SDA line while the SCL line is HIGH is defined as a STOP condition. Each data transfer must be terminated by the generation of a STOP (SP) condition. 

In the presented communication format MAK is master acknowledge and NMAK is no master acknowledge. 

# 5.1.2 SPI bus interface

The LSM6DSR SPI is a bus slave. The SPI allows writing and reading the registers of the device. The serial interface communicates with the application using 4 wires: CS, SPC, SDI and SDO. 


Figure 7. Read and write protocol (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/8b3cc3bc32361fe1cc8cbb9d83b6b1bc02ac467d861079cc9159631468523a39.jpg)


CS is the serial port enable and it is controlled by the SPI master. It goes low at the start of the transmission and goes back high at the end. SPC is the serial port clock and it is controlled by the SPI master. It is stopped high when CS is high (no transmission). SDI and SDO are, respectively, the serial port data input and output. Those lines are driven at the falling edge of SPC and should be captured at the rising edge of SPC. 

Both the read register and write register commands are completed in 16 clock pulses or in multiples of 8 in case of multiple read/write bytes. Bit duration is the time between two falling edges of SPC. The first bit (bit 0) starts at the first falling edge of SPC after the falling edge of CS while the last bit (bit 15, bit 23, ...) starts at the last falling edge of SPC just before the rising edge of CS. 

bit 0: RW bit. When 0, the data DI(7:0) is written into the device. When 1, the data DO(7:0) from the device is read. In latter case, the chip will drive SDO at the start of bit 8. 

bit 1-7: address AD(6:0). This is the address field of the indexed register. 

bit 8-15: data DI(7:0) (write mode). This is the data that is written into the device (MSb first). 

bit 8-15: data DO(7:0) (read mode). This is the data that is read from the device (MSb first). 

In multiple read/write commands further blocks of 8 clock periods will be added. When the CTRL3_C (12h) (IF_INC) bit is ‘0’, the address used to read/write data remains the same for every block. When the CTRL3_C (12h) (IF_INC) bit is ‘1’, the address used to read/write data is increased at every block. 

The function and the behavior of SDI and SDO remain unchanged. 

# 5.1.2.1 SPI read


Figure 8. SPI read protocol (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/0d91535cdc5f2a2c34d0505ea7be0429878f964d49801a150d937aa42317499f.jpg)


The SPI read command is performed with 16 clock pulses. A multiple byte read command is performed by adding blocks of 8 clock pulses to the previous one. 

bit 0: READ bit. The value is 1. 

bit 1-7: address AD(6:0). This is the address field of the indexed register. 

bit 8-15: data DO(7:0) (read mode). This is the data that will be read from the device (MSb first). 

bit 16-...: data DO(...-8). Further data in multiple byte reads. 


Figure 9. Multiple byte SPI read protocol (2-byte example) (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/d418805ef1649834e04823c8c6dbe5c60486a1771a276ea85662322a9e069c65.jpg)


# 5.1.2.2 SPI write


Figure 10. SPI write protocol (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/e3610d424cfa9f0a2dac2cec0652530eb749c71d0143099177b627e864178a5c.jpg)


The SPI write command is performed with 16 clock pulses. A multiple byte write command is performed by adding blocks of 8 clock pulses to the previous one. 

bit 0: WRITE bit. The value is 0. 

bit 1-7: address AD(6:0). This is the address field of the indexed register. 

bit 8-15: data DI(7:0) (write mode). This is the data that is written inside the device (MSb first). 

bit $1 6 \cdots$ : data DI(...-8). Further data in multiple byte writes. 


Figure 11. Multiple byte SPI write protocol (2-byte example) (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/0263cbb0805afbca623b6ca6fa127c4b2a8fc4dbed2c574fd4783089f3d76e11.jpg)


# 5.1.2.3 SPI read in 3-wire mode

A 3-wire mode is entered by setting the CTRL3_C (12h) (SIM) bit equal to ‘1’ (SPI serial interface mode selection). 


Figure 12. SPI read protocol in 3-wire mode (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/8bff6ce5bb95fb4a3aa3eeb7cec5f254d19446d4541c269ff283cfb8381cd43f.jpg)


The SPI read command is performed with 16 clock pulses: 

bit 0: READ bit. The value is 1. 

bit 1-7: address AD(6:0). This is the address field of the indexed register. 

bit 8-15: data DO(7:0) (read mode). This is the data that is read from the device (MSb first). 

A multiple read command is also available in 3-wire mode. 

# 5.2 MIPI I3CSM interface

# 5.2.1 MIPI I3CSM slave interface

The LSM6DSR interface includes a MIPI $1 3 C ^ { \mathsf { S M } }$ SDR only slave interface (compliant with release 1.0 of the specification) with MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ SDR embedded features: 

· CCC command 

. Direct CCC communication (SET and GET) 

· Broadcast CCC communication 

• Private communications 

. Private read and write for single byte 

Multiple read and write 

. In-Band Interrupt request 

Error Detection and Recovery Methods (S0-S6) 

Note: Refer to Section 5.3 I²C/I3C coexistence in LSM6DSR for details concerning the choice of the interface when powering up the device. 

# 5.2.2 MIPI $1 3 C ^ { \mathsf { S M } }$ CCC supported commands

The list of MIPI $| 3 C ^ { \mathsf { S M } }$ CCC commands supported by the device is detailed in the following table. 


Table 15. MIPI $1 3 C ^ { \mathsf { S M } }$ CCC commands


<table><tr><td>Command</td><td>Command code</td><td>Default</td><td>Description</td></tr><tr><td>ENTDAA</td><td>0x07</td><td></td><td>DAA procedure</td></tr><tr><td>SETDASA</td><td>0x87</td><td></td><td>Assign Dynamic Address using Static Address 0x6B/0x6A depending on SDO pin</td></tr><tr><td>ENEC</td><td>0x80 / 0x00</td><td></td><td>Slave activity control (direct and broadcast)</td></tr><tr><td>DISEC</td><td>0x81/ 0x01</td><td></td><td>Slave activity control (direct and broadcast)</td></tr><tr><td>ENTAS0</td><td>0x82 / 0x02</td><td></td><td>Enter activity state (direct and broadcast)</td></tr><tr><td>ENTAS1</td><td>0x83 / 0x03</td><td></td><td>Enter activity state (direct and broadcast)</td></tr><tr><td>ENTAS2</td><td>0x84 / 0x04</td><td></td><td>Enter activity state (direct and broadcast)</td></tr><tr><td>ENTAS3</td><td>0x85 / 0x05</td><td></td><td>Enter activity state (direct and broadcast)</td></tr><tr><td>SETXTIME</td><td>0x98 / 0x28</td><td></td><td>Timing information exchange</td></tr><tr><td>GETXTIME</td><td>0x99</td><td>0x070x000x050x92</td><td>Timing information exchange</td></tr><tr><td>RSTDAA</td><td>0x86 / 0x06</td><td></td><td>Reset the assigned dynamic address (direct and broadcast)</td></tr><tr><td>SETMWL</td><td>0x89 / 0x08</td><td></td><td>Define maximum write length during private write (direct and broadcast)</td></tr><tr><td>SETMRL</td><td>0x8A / 0x09</td><td></td><td>Define maximum read length during private read (direct and broadcast)</td></tr><tr><td>SETNEWDA</td><td>0x88</td><td></td><td>Change dynamic address</td></tr><tr><td>GETMWL</td><td>0x8B</td><td>0x000x08(2 byte)</td><td>Get maximum write length during private write</td></tr><tr><td>GETMRL</td><td>0x8C</td><td>0x000x100x09(3 byte)</td><td>Get maximum read length during private read</td></tr><tr><td>GETPID</td><td>0x8D</td><td>0x020x080x000x6B0x100x0B</td><td>Device ID register</td></tr><tr><td>GETBCR</td><td>0x8E</td><td>0x07(1 byte)</td><td>Bus characteristics register</td></tr><tr><td>GETDCR</td><td>0x8F</td><td>0x00</td><td>MIPI I3CSM device characteristics register</td></tr><tr><td>GETSTATUS</td><td>0x90</td><td>0x000x00(2 byte)</td><td>Status register</td></tr><tr><td>GETMXDS</td><td>0x94</td><td>0x000x38(2 byte)</td><td>Return max data speed</td></tr></table>

# 5.3 I²C/I3C coexistence in LSM6DSR

In the LSM6DSR, the SDA and SCL lines are common to both I²C and I3C. The I²C bus requires anti-spike filters on the SDA and SCL pins that are not compatible with I3C timing. 

The device can be connected to both I²C and I3C or only to the I3C bus depending on the connection of the INT1 pin when the device is powered up: 

INT1 pin floating (internal pull-down): I²C/I3C both active, see Figure 13 

INT1 pin connected to Vdd_IO: only I3C active, see Figure 14 


Figure 13. I²C and I3C both active (INT1 pin not connected)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/f2f54bc075bec935133ee939a639f4f52606903d87f14893b21dda0730973199.jpg)


1. Address assignment (DAA or ENTDA) must be performed with I²C Fast Mode Plus Timing. When the slave is addressed, the I²C slave is disabled and the timing is compatible with I3C specifications. 


Figure 14. Only I3C active (INT1 pin connected to Vdd_IO)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/227f8fdec554ea709c7a2bcc54fb919b3ed7e8ab91088c73ec25c4a6928bee2f.jpg)


1. When the slave is I3C only, the I²C slave is always disabled. The address can be assigned using I3C SDR timing. 

# 5.4 Master I²C interface

If the LSM6DSR is configured in Mode 2, a master I²C line is available. The master serial interface is mapped in the following dedicated pins. 


Table 16. Master I²C pin details


<table><tr><td>Pin name</td><td>Pin description</td></tr><tr><td>MSCL</td><td>I2C serial clock master</td></tr><tr><td>MSDA</td><td>I2C serial data master</td></tr><tr><td>MDRDY</td><td>I2C master external synchronization signal</td></tr></table>

# 5.5 Auxiliary SPI interface

If the LSM6DSR is configured in Mode 3 or Mode 4, the auxiliary SPI is available. The auxiliary SPI interface is mapped to the following dedicated pins. 


Table 17. Auxiliary SPI pin details


<table><tr><td>Pin name</td><td>Pin description</td></tr><tr><td>OCS_Aux</td><td>Auxiliary SPI 3/4-wire enable</td></tr><tr><td>SDx</td><td>Auxiliary SPI 3/4-wire data input (SDI_Aux) and SPI 3-wire data output (SDO_Aux)</td></tr><tr><td>SCx</td><td>Auxiliary SPI 3/4-wire interface serial port clock</td></tr><tr><td>SDO_Aux</td><td>Auxiliary SPI 4-wire data output (SDO_Aux)</td></tr></table>

When the LSM6DSR is configured in Mode 3 or Mode 4, the auxiliary SPI can be connected to a camera module for OIS/EIS support. In this configuration, the auxiliary SPI can write only to the dedicated registers INT_OIS (6Fh), CTRL1_OIS (70h), CTRL2_OIS (71h), CTRL3_OIS (72h). All the registers are accessible in Read mode from both the primary interface and auxiliary SPI. 

Mode 3 is enabled when the OIS_EN_SPI2 bit in CTRL1_OIS (70h) register is set to 1. 

Mode 4 is enabled when both the OIS_EN_SPI2 bit and the Mode4_EN bit in CTRL1_OIS (70h) register are set to 1. 

# 6 Functionality

# 6.1 Operating modes

In the LSM6DSR, the accelerometer and the gyroscope can be turned on/off independently of each other and are allowed to have different ODRs and power modes. 

The LSM6DSR has three operating modes available: 

only accelerometer active and gyroscope in power-down or sleep mode 

• only gyroscope active and accelerometer in power-down 

both accelerometer and gyroscope sensors active with independent ODR 

The accelerometer is activated from power-down by writing ODR_XL[3:0] in CTRL1_XL (10h) while the gyroscope is activated from power-down by writing ODR_G[3:0] in CTRL $\scriptscriptstyle - 2 \_ G$ (11h). For combo-mode the ODRs are totally independent. 

# 6.2 Gyroscope power modes

In the LSM6DSR, the gyroscope can be configured in four different operating modes: power-down, low-power, normal mode and high-performance mode. The operating mode selected depends on the value of the G_HM_MODE bit in CTRL7_G (16h). If G_HM_MODE is set to '0', high-performance mode is valid for all ODRs (from 12.5 Hz up to 6.66 kHz). 

To enable the low-power and normal mode, the G_HM_MODE bit has to be set to $" 1 " .$ Low-power mode is available for lower ODRs (12.5, 26, 52 Hz) while normal mode is available for ODRs equal to 104 and 208 Hz. 

# 6.3 Accelerometer power modes

In the LSM6DSR, the accelerometer can be configured in four different operating modes: power-down, lowpower, normal mode and high-performance mode. The operating mode selected depends on the value of the XL_HM_MODE bit in CTRL6_C (15h). If XL_HM_MODE is set to '0', high-performance mode is valid for all ODRs (from 12.5 Hz up to 6.66 kHz). 

To enable the low-power and normal mode, the XL_HM_MODE bit has to be set to $" 1 " .$ . Low-power mode is available for lower ODRs (1.6, 12.5, 26, 52 Hz) while normal mode is available for ODRs equal to 104 and 208 Hz. 

# 6.4 Block diagram of filters


Figure 15. Block diagram of filters


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/9034d768e947085adf6d63303b3c0a50d4ea82d0bb3eeda27ac10aec43c97cf1.jpg)


# 6.4.1 Block diagrams of the accelerometer filters

In the LSM6DSR, the filtering chain for the accelerometer part is composed of the following: 

. Digital filter (LPF1) 

Composite filter 

Details of the block diagram appear in the following figure. 


Figure 16. Accelerometer UI chain


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/a2085148c91972bde2a56b5a039eb77022abaa629940cc886c216ef8d62e60ed.jpg)



Figure 17. Accelerometer composite filter


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/11441ecabf3abb77e22311a8a49264cc666f9e3f15f0d81758ad9b353e229dec.jpg)


1. The cutoff value of the LPF1 output is ODR/2 when the accelerometer is in high-performance mode and ODR up to 833 Hz. This value is equal to 780 Hz when the accelerometer is in low-power or normal mode. 

Note: Advanced functions include pedometer, step detector and step counter, significant motion detection, tilt function and Finite State Machine. 

The accelerometer filtering chain when Mode 4 is enabled is illustrated in the following figure. 


Figure 18. Accelerometer chain with Mode 4 enabled


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/6ee1bea05e9ed8fd9f7ac8137167455a022de2a60f94ca0901c1c3ea9e6a8af1.jpg)



Note: Mode 4 is enabled when Mode4_EN = 1 and OIS_EN_SPI2 = 1 in CTRL1_OIS (70h).



The configuration of the accelerometer UI chain is not affected by enabling Mode 4.



Accelerometer output values are in registers OUTX_L_A (28h) and OUTX_H_A (29h) through OUTZ_L_A (2Ch) and OUTZ_H_A (2Dh) and ODR at 6.66 kHz.


# 6.4.2 Block diagrams of the gyroscope filters

In the LSM6DSR, the gyroscope filtering chain depends on the mode configuration: 

Mode 1 (for User Interface (UI) and Electronic Image Stabilization (EIS) functionality through primary interface) and Mode 2 


Figure 19. Gyroscope digital chain - Mode 1 (UI/EIS) and Mode 2


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/051df31cff95b6d87c2987d656718a621c7ade121e0a334d8df1c32506bce6eb.jpg)


In this configuration, the gyroscope ODR is selectable from 12.5 Hz up to 6.66 kHz. A low-pass filter (LPF1) is available if the auxiliary SPI is disabled, for more details about the filter characteristics see Table 65. Gyroscope LPF1 bandwidth selection. 

The digital LPF2 filter cannot be configured by the user and its cutoff frequency depends on the selected gyroscope ODR, as indicated in the following table. 


Table 18. Gyroscope LPF2 bandwidth selection


<table><tr><td>Gyroscope ODR [Hz]</td><td>LPF2 cutoff [Hz]</td></tr><tr><td>12.5</td><td>4.3</td></tr><tr><td>26</td><td>8.3</td></tr><tr><td>52</td><td>16.7</td></tr><tr><td>104</td><td>33</td></tr><tr><td>208</td><td>67</td></tr><tr><td>417</td><td>133</td></tr><tr><td>833</td><td>267</td></tr><tr><td>1667</td><td>539</td></tr><tr><td>3333</td><td>1137</td></tr><tr><td>6667</td><td>3333</td></tr></table>

Data can be acquired from the output registers and FIFO over the primary I²C/I3C/SPI interface. 

Mode 3 / Mode 4 (for OIS and EIS functionality) 


Figure 20. Gyroscope digital chain - Mode 3 / Mode 4 (OIS/EIS)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/8efc964d7e9f3dc5d9073a62d76d414bbf228bc36c80ef93a3eb6178b7d48844.jpg)


1. When Mode3/4 is enabled, the LPF1 filter is not available in the gyroscope UI chain. 

2. It is recommended to avoid using the LPF1 filter in Mode1/2 when Mode3/4 is intended to be used. 

3. HP_EN_OIS can be used to select the HPF on the OIS path only if the HPF is not used in the UI chain. If both the HP_EN_G bit and HP_EN_OIS bit are set to 1, the HP filter is applied to the UI chain only. 

Note: When S4S is enabled in the UI chain, the HPF is not available in the OIS chain. 

The auxiliary interface needs to be enabled in CTRL1_OIS (70h). 

In Mode 3/4 configuration, there are two paths: 

the chain for User Interface (UI) where the ODR is selectable from 12.5 Hz up to 6.66 kHz the chain for OIS/EIS where the ODR is at 6.66 kHz and the LPF1 is available. The LPF1 configuration depends on the setting of the FTYPE_[1:0] _OIS bit in register CTRL2_OIS (71h); for more details about the filter characteristics see Table 158. Gyroscope OIS chain digital LPF1 filter bandwidth selection. Gyroscope output values are in registers 22h to 27h with the selected full scale (FS[1:0]_G_OIS bit in CTRL1_OIS (70h)). 

# 6.5 OIS

This paragraph describes OIS functionality and the dedicated accelerometer-gyroscope DSP chain. 

There is a dedicated gyroscope and accelerometer DSP for OIS. 

Other features can be configured: 

Self-test on OIS side 

• DEN on OIS side 

The camera module is completely independent from the application processor as shown in Figure 21. 

The Auxiliary SPI can configure OIS functionality through INT_OIS (6Fh), CTRL1_OIS (70h), CTRL2_OIS (71h), CTRL3_OIS (72h). 

Reading from the Auxiliary SPI is enabled only when the OIS_EN_SPI2 bit in the CTRL1_OIS (70h) register is set to '1'. This bit also turns on the gyroscope OIS chain. 

The Primary Interface can access the OIS control registers (INT_OIS (6Fh), CTRL1_OIS (70h), CTRL2_OIS (71h), CTRL3_OIS (72h)) in read mode. 


Figure 21. Auxiliary SPI full control (a) and enabling primary interface (b)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/398e9f9ea089fb1b3c880cfc2c86da5e28e59ceeb32899496b11275bd3576c40.jpg)



(a)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/5248faf08d3ed7b5c6af433b3bee708c0ea13bcd40fc785a5c9f57fd4a768c94.jpg)



(b)


# 6.6 FIFO

The presence of a FIFO allows consistent power saving for the system since the host processor does not need continuously poll data from the sensor, but It can wake up only when needed and burst the significant data out from the FIFO. 

The LSM6DSR embeds 3 kbytes of data (up to 9 kbytes with the compression feature enabled) in FIFO to store the following data: 

• Gyroscope 

• Accelerometer 

. External sensors (up to 4) 

• Step counter 

. Timestamp 

. Temperature 

Writing data in the FIFO can be configured to be triggered by the: 

Accelerometer / gyroscope data-ready signal 

• Sensor hub data-ready signal 

Step detection signal 

The applications have maximum flexibility in choosing the rate of batching for physical sensors with FIFOdedicated configurations: accelerometer, gyroscope and temperature sensor batch rates can be selected by the user. External sensor writing in FIFO can be triggered by the accelerometer data-ready signal or by an external sensor interrupt. The step counter can be stored in FIFO with associated timestamp each time a step is detected. It is possible to select decimation for timestamp batching in FIFO with a factor of 1, 8, or 32. 

The reconstruction of a FIFO stream is a simple task thanks to the FIFO_DATA_OUT_TAG byte that allows recognizing the meaning of a word in FIFO. 

FIFO allows correct reconstruction of the timestamp information for each sensor stored in FIFO. If a change in the ODR or BDR (Batch Data Rate) configuration is performed, the application can correctly reconstruct the timestamp and know exactly when the change was applied without disabling FIFO batching. FIFO stores information of the new configuration and timestamp in which the change was applied in the device. 

Finally, FIFO embeds a compression algorithm that the user can enable in order to have up to 9 kbyte data stored in FIFO and take advantage of interface communication length for FIFO flushing and communication power consumption. 

The programmable FIFO watermark threshold can be set in FIFO_CTRL1 (07h) and FIFO_CTRL2 (08h) using the WTM[8:0] bits. To monitor the FIFO status, dedicated registers (FIFO_STATUS1 (3Ah), FIFO_STATUS2 (3Bh)) can be read to detect FIFO overrun events, FIFO full status, FIFO empty status, FIFO watermark status and the number of unread samples stored in the FIFO. To generate dedicated interrupts on the INT1 and INT2 pins of these status events, the configuration can be set in INT1_CTRL (0Dh) and INT2_CTRL (0Eh). 

The FIFO buffer can be configured according to six different modes: 

• Bypass mode 

· FIFO mode 

Continuous mode 

. Continuous-to-FIFO mode 

• Bypass-to-continuous mode 

. Bypass-to-FIFO mode 

Each mode is selected by the FIFO_MODE_[2:0] bits in the FIFO_CTRL4 (0Ah) register. 

# 6.6.1 Bypass mode

In Bypass mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 000), the FIFO is not operational and it remains empty. Bypass mode is also used to reset the FIFO when in FIFO mode. 

# 6.6.2 FIFO mode

In FIFO mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 001) data from the output channels are stored in the FIFO until it is full. 

To reset FIFO content, Bypass mode should be selected by writing FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0]) to '000'. After this reset command, it is possible to restart FIFO mode by writing FIFO_CTRL4 (0Ah) (FIFO_MODE_[2:0]) to '001'. 

The FIFO buffer memorizes up to 9 kbytes of data (with compression enabled) but the depth of the FIFO can be resized by setting the WTM [8:0] bits in FIFO_CTRL1 (07h) and FIFO_CTRL2 (08h). If the STOP_ON_WTM bit in FIFO_CTRL2 (08h) is set to '1', FIFO depth is limited up to the WTM [8:0] bits in FIFO_CTRL1 (07h) and FIFO_CTRL2 (08h). 

# 6.6.3 Continuous mode

Continuous mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 110) provides a continuous FIFO update: as new data arrives, the older data is discarded. 

A FIFO threshold flag FIFO_STATUS2 (3Bh)(FIFO_WTM_IA) is asserted when the number of unread samples in FIFO is greater than or equal to FIFO_CTRL1 (07h) and FIFO_CTRL2 (08h)(WTM [8:0]). 

It is possible to route the FIFO_WTM_IA flag to the INT1 pin by writing in register INT1_CTRL (0Dh) (INT1_FIFO_TH) = '1' or to the INT2 pin by writing in register INT2_CTRL (0Eh)(INT2_FIFO_TH) = '1'. 

A full-flag interrupt can be enabled, INT1_CTRL (0Dh)(INT1_FIFO_FULL) = '1' or INT2_CTRL (0Eh) (INT2_FIFO_FULL) = '1', in order to indicate FIFO saturation and eventually read its content all at once. 

If an overrun occurs, at least one of the oldest samples in FIFO has been overwritten and the FIFO_OVR_IA flag in FIFO_STATUS2 (3Bh) is asserted. 

In order to empty the FIFO before it is full, it is also possible to pull from FIFO the number of unread samples available in FIFO_STATUS1 (3Ah) and FIFO_STATUS2 (3Bh)(DIFF_FIFO_[9:0]). 

# 6.6.4 Continuous-to-FIFO mode

In Continuous-to-FIFO mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 011), FIFO behavior changes according to the trigger event detected in one of the following interrupt events: 

. Single tap 

Double tap 

. Wake-up 

Free-fall 

D6D 

When the selected trigger bit is equal to '1', FIFO operates in FIFO mode. 

When the selected trigger bit is equal to '0', FIFO operates in Continuous mode. 

# 6.6.5 Bypass-to-Continuous mode

In Bypass-to-Continuous mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = '100'), data measurement storage inside FIFO operates in Continuous mode when selected triggers are equal to '1', otherwise FIFO content is reset (Bypass mode). 

FIFO behavior changes according to the trigger event detected in one of the following interrupt events: 

. Single tap 

Double tap 

Wake-up 

Free-fall 

D6D 

# 6.6.6 Bypass-to-FIFO mode

In Bypass-to-FIFO mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = '111'), data measurement storage inside FIFO operates in FIFO mode when selected triggers are equal to '1', otherwise FIFO content is reset (Bypass mode). FIFO behavior changes according to the trigger event detected in one of the following interrupt events: 

. Single tap 

• Double tap 

Wake-up 

• Free-fall 

D6D 

# 6.6.7 FIFO reading procedure

The data stored in FIFO are accessible from dedicated registers and each FIFO word is composed of 7 bytes: one tag byte (FIFO_DATA_OUT_TAG (78h)), in order to identify the sensor, and 6 bytes of fixed data (FIFO_DATA_OUT registers from (79h) to (7Eh)). 

The DIFF_FIFO_[9:0] field in the FIFO_STATUS1 (3Ah) and FIFO_STATUS2 (3Bh) registers contains the number of words (1 byte TAG + 6 bytes DATA) collected in FIFO. 

In addition, it is possible to configure a counter of the batch events of accelerometer or gyroscope sensors. The flag COUNTER_BDR_IA in FIFO_STATUS2 (3Bh) alerts that the counter reaches a selectable threshold (CNT_BDR_TH_[10:0] field in COUNTER_BDR_REG1 (0Bh) and COUNTER_BDR_REG2 (0Ch)). This allows triggering the reading of FIFO with the desired latency of one single sensor. The sensor is selectable using the TRIG_COUNTER_BDR bit in COUNTER_BDR_REG1 (0Bh). As for the other FIFO status events, the flag COUNTER_BDR_IA can be routed on the INT1 or INT2 pins by asserting the corresponding bits (INT1_CNT_BDR of INT1_CTRL (0Dh)) and INT2_CNT_BDR of INT2_CTRL (0Eh)). 

In order to maximize the amount of accelerometer and gyroscope data in FIFO, the user can enable the compression algorithm by setting to 1 both the FIFO_COMPR_EN bit in EMB_FUNC_EN_B (05h) (embedded functions registers bank) and the FIFO_COMPR_RT_EN bit in FIFO_CTRL2 (08h). When compression is enabled, it is also possible to force writing non-compressed data at a selectable rate using the UNCOPTR_RATE_[1:0] field in FIFO_CTRL2 (08h). 

Meta information about accelerometer and gyroscope sensor configuration changes can be managed by enabling the ODR_CHG_EN bit in FIFO_CTRL2 (08h). 

# 7 Application hints

# 7.1 LSM6DSR electrical connections in Mode 1


Figure 22. LSM6DSR electrical connections in Mode 1


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/91d169ad297920e84f84c9cabb1cbfd6aca209d88154d4a87041d2796470436e.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/e5dedfad132dcba740abbc82b0a7d054d87025f89a213b387a4bbc833d1a5051.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/98c6716021f3a6910ed1501bd8cb9eaed0eeb7ddbd8e45e236396a851e942dbd.jpg)



Pull-up to be added Rpu=10kOhm


# 1. Leave pin electrically unconnected and soldered to PCB.

The device core is supplied through the Vdd line. Power supply decoupling capacitors (C1, C2 = 100 nF ceramic) should be placed as near as possible to the supply pin of the device (common design practice). 

The functionality of the device and the measured acceleration/angular rate data is selectable and accessible through the SPI/I²C/MIPI $1 3 C ^ { \mathsf { S M } }$ interface. 

The functions, the threshold and the timing of the two interrupt pins for each sensor can be completely programmed by the user through the SPI/I²C/MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ interface. 

# 7.2 LSM6DSR electrical connections in Mode 2


Figure 23. LSM6DSR electrical connections in Mode 2


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/8dc6391184bfba0a4ff2d38982244f0082337d87bec9dcefe202771a5b5a04e7.jpg)



Pull-up to be added Rpu=10kOhm


1. Leave pin electrically unconnected and soldered to PCB. 

The device core is supplied through the Vdd line. Power supply decoupling capacitors (C1, C2 = 100 nF ceramic) should be placed as near as possible to the supply pin of the device (common design practice). 

The functionality of the device and the measured acceleration/angular rate data is selectable and accessible through the SPI/I²C/MIPI $1 3 C ^ { \mathsf { S M } }$ primary interface. 

The functions, the threshold and the timing of the two interrupt pins for each sensor can be completely programmed by the user through the SPI/I²C/MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ primary interface. 

# 7.3 LSM6DSR electrical connections in Mode 3 and Mode 4


Figure 24. LSM6DSR electrical connections in Mode 3 and Mode 4 (auxiliary 3/4-wire SPI)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/5be952fc06f83e0c5ac4880b017fdb406dfa008cfa6bca1c6c425bc50dcf2fcb.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/75103275053b6210ef27b3209425488a325e3336099d3d5881aa142005e32e4e.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/93879817e8334558731034e9b10dc151862fb3155cb4ed253e6e9ae02584f9e4.jpg)


1. Leave pin electrically unconnected and soldered to PCB. 

Note: When Mode 3 and 4 are used, the pull-up on pins 10 and 11 can be disabled (refer to Table 19. Internal pin status). To avoid leakage current, it is recommended to add pull-up resistors on the SPI lines unless the SPI master can be left on while the OIS system is off. 

The device core is supplied through the Vdd line. Power supply decoupling capacitors (C1, C2 = 100 nF ceramic) should be placed as near as possible to the supply pin of the device (common design practice). 

The functionality of the device is selectable and accessible through the SPI/I²C/MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ primary interface. 

Measured acceleration/angular rate data is selectable and accessible through the SPI/I²C/MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ primary interface and auxiliary SPI. 

The functions, the threshold and the timing of the two interrupt pins for each sensor can be completely programmed by the user through the SPI/I²C/MIPI I3CSM interface. 


Table 19. Internal pin status


<table><tr><td>pin#</td><td>Name</td><td>Mode 1 function</td><td>Mode 2 function</td><td>Mode 3 / Mode 4 function</td><td>Pin status Mode 1</td><td>Pin status Mode 2</td><td>Pin status Mode <eq>{3/4}^{\left( 1\right) }</eq></td></tr><tr><td rowspan="2">1</td><td>SDO</td><td>SPI 4-wire interface serial data output (SDO)</td><td>SPI 4-wire interface serial data output (SDO)</td><td>SPI 4-wire interface serial data output (SDO)</td><td rowspan="2">Default: input without pull-up.Pull-up is enabled if bit SDO_PU_EN = 1 in reg 02h.</td><td rowspan="2">Default: input without pull-up.Pull-up is enabled if bit SDO_PU_EN = 1 in reg 02h.</td><td rowspan="2">Default: Input without pull-up.Pull-up is enabled if bit SDO_PU_EN = 1 in reg 02h.</td></tr><tr><td>SA0</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> least significant bit of the device address (SA0)MIPI I3CSMleast significant bit of the static address (SA0)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> least significant bit of the device address (SA0)MIPI I3CSMleast significant bit of the static address (SA0)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> least significant bit of the device address (SA0)MIPI I3CSMleast significant bit of the static address (SA0)</td></tr><tr><td>2</td><td>SDx</td><td>Connect to Vdd_IO or GND</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> serial data master (MSDA)</td><td>Auxiliary SPI 3/4-wire interface serial data input (SDI) and SPI 3-wire serial data output (SDO)</td><td>Default: input without pull-up.Pull-up is enabled if bit SHUB_PU_EN = 1 in reg 14h in sensor hub registers (see Note to enable pull-up).</td><td>Default: input without pull-up.Pull-up is enabled if bit SHUB_PU_EN = 1 in reg 14h in sensor hub registers (see Note to enable pull-up).</td><td>Default: input without pull-up.Pull-up is enabled if bit SHUB_PU_EN = 1 in reg 14h in sensor hub registers (see Note to enable pull-up).</td></tr><tr><td>3</td><td>SCx</td><td>Connect to Vdd_IO or GND</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> serial clock master (MSCL)</td><td>Auxiliary SPI 3/4-wire interface serial port clock (SPC_Aux)</td><td>Default: input without pull-up.Pull-up is enabled if bit SHUB_PU_EN = 1 in reg 14h in sensor hub registers (see Note to enable pull-up).</td><td>Default: input without pull-up.Pull-up is enabled if bit SHUB_PU_EN = 1 in reg 14h in sensor hub registers (see Note to enable pull-up).</td><td>Default: input without pull-up.Pull-up is enabled if bit SHUB_PU_EN = 2 in reg 14h in sensor hub registers (see Note to enable pull-up)</td></tr><tr><td>4</td><td>INT1</td><td>Programmable interrupt 1 / If device is used as MIPI <eq>{\mathrm{{I3CSM}}}^{ \circledR }</eq> pure slave, this pin must be set to '1'.</td><td>Programmable interrupt 1 / If device is used as MIPI <eq>{\mathrm{{I3CSM}}}^{ \circledR }</eq> pure slave, this pin must be set to '1'.</td><td>Programmable interrupt 1 / If device is used as MIPI <eq>{\mathrm{{I3CSM}}}^{ \circledR }</eq> pure slave, this pin must be set to '1'.</td><td>Default: input with pull-down(2)</td><td>Default: input with pull-down(2)</td><td>Default: input with pull-down(2)</td></tr><tr><td>5</td><td>Vdd_IO</td><td>Power supply for I/O pins</td><td>Power supply for I/O pins</td><td>Power supply for I/O pins</td><td></td><td></td><td></td></tr><tr><td>6</td><td>GND</td><td>0 V supply</td><td>0 V supply</td><td>0 V supply</td><td></td><td></td><td></td></tr><tr><td>7</td><td>GND</td><td>0 V supply</td><td>0 V supply</td><td>0 V supply</td><td></td><td></td><td></td></tr><tr><td>8</td><td>Vdd</td><td>Power supply</td><td>Power supply</td><td>Power supply</td><td></td><td></td><td></td></tr><tr><td>9</td><td>INT2</td><td>Programmable interrupt 2 (INT2) / Data enabled (DEN)</td><td>Programmable interrupt 2 (INT2) / Data enabled (DEN) / <eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> master external synchronization signal (MDRDY)</td><td>Programmable interrupt 2 (INT2) / Data enabled (DEN)</td><td>Default: output forced to ground</td><td>Default: output forced to ground</td><td>Default: output forced to ground</td></tr><tr><td>10</td><td>OCS_Aux</td><td>Leave unconnected</td><td>Leave unconnected</td><td>Auxiliary SPI 3/4-wire interface enabled</td><td>Default: input with pull-up.Pull-up is disabled if bit OIS_PU_DIS = 1 in reg 02h.</td><td>Default: input with pull-up.Pull-up is disabled if bit OIS_PU_DIS = 1 in reg 02h.</td><td>Default: input without pull-up (regardless of the value of bit OIS_PU_DIS in reg 02h.)</td></tr><tr><td>11</td><td>SDO_Aux</td><td>Connect to Vdd_IO or leave unconnected</td><td>Connect to Vdd_IO or leave unconnected</td><td>Auxiliary SPI 3- wire interface: leave unconnected / Auxiliary SPI 4-wire interface: serial data output (SDO_Aux)</td><td>Default: input with pull-up.Pull-up is disabled if bit OIS_PU_DIS = 1 in reg 02h.</td><td>Default: input with pull-up.Pull-up is disabled if bit OIS_PU_DIS = 1 in reg 02h.</td><td>Default: input without pull-up.Pull-up is enabled if bit SIM_OIS = 1 (Aux_SPI 3-wire) in reg 70h and bit OIS_PU_DIS = 0 in reg 02h.</td></tr><tr><td>12</td><td>CS</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}/\mathrm{{SPI}}</eq> mode selection (1:SPI idle mode / <eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> communication enabled; 0: SPI communication mode / <eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> disabled)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}/\mathrm{{SPI}}</eq> mode selection (1:SPI idle mode / <eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> communication enabled; 0: SPI communication mode / <eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> disabled)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}/\mathrm{{SPI}}</eq> mode selection(1:SPI idle mode / <eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> communication enabled; 0: SPI communication mode / <eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> disabled)</td><td>Default: input with pull-up.Pull-up is disabled if bit I2C_disable = 1 in reg 13h and I3C_disable = 1 in reg 18h.</td><td>Default: input with pull-up.Pull-up is disabled if bit I2C_disable = 1 in reg 13h and I3C_disable = 1 in reg 18h.</td><td>Default: input with pull-up.Pull-up is disabled if bit I2C_disable = 1 in reg 13h and I3C_disable = 1 in reg 18h.</td></tr><tr><td>pin#</td><td>Name</td><td>Mode 1 function</td><td>Mode 2 function</td><td>Mode 3 / Mode 4 function</td><td>Pin status Mode 1</td><td>Pin status Mode 2</td><td>Pin status Mode <eq>3/4^{(1)}</eq></td></tr><tr><td>13</td><td>SCL</td><td><eq>I^2C/MIPI I3C^{SM} serial clock (SCL) / SPI serial port clock (SPC)</eq></td><td><eq>I^2C/MIPI I3C^{SM} serial clock (SCL) / SPI serial port clock (SPC)</eq></td><td><eq>I^2C/MIPI I3C^{SM} serial clock (SCL) / SPI serial port clock (SPC)</eq></td><td>Default: input without pull-up</td><td>Default: input without pull-up</td><td>Default: input without pull-up</td></tr><tr><td>14</td><td>SDA</td><td><eq>I^2C/MIPI I3C^{SM} serial data (SDA) / SPI serial data input (SDI) / 3-wire interface serial data output (SDO)</eq></td><td><eq>I^2C/MIPI I3C^{SM} serial data (SDA) / SPI serial data input (SDI) / 3-wire interface serial data output (SDO)</eq></td><td><eq>I^2C/MIPI I3C^{SM} serial data (SDA) / SPI serial data input (SDI) / 3-wire interface serial data output (SDO)</eq></td><td>Default: input without pull-up</td><td>Default: input without pull-up</td><td>Default:input without pull-up</td></tr></table>

1. Mode 3 is enabled when the OIS_EN_SPI2 bit in the CTRL1_OIS (70h) register is set to 1. Mode 4 is enabled when both the OIS_EN_SPI2 bit and the Mode4_EN bit in the CTRL1_OIS (70h) register are set to 1. 

2. INT1 must be set to '0' or left unconnected during power-on if the I²C/SPI interfaces are used. 

Internal pull-up value is from 30 kΩ to 50 kΩ, depending on Vdd_IO. 

Note: The procedure to enable the pull-up on pins 2 and 3 is as follows: 

1. From the primary I²C/I3C/SPI interface : write 40h in register at address 01h (enable access to the sensor hub registers) 

2. From the primary I²C/I3C/SPI interface : write 08h in register at address 14h (enable the pull-up on pins 2 and 3) 

3. From the primary I²C/I3C/SPI interface : write 00h in register at address 01h (disable access to the sensor hub registers) 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/6219b1568cd9c6f341ad1d01db0030e7da8b95287af8c5d58260bdeb38ac3c2f.jpg)


# 8 Register mapping

The table given below provides a list of the 8/16-bit registers embedded in the device and the corresponding addresses. 


Table 20. Registers address map


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>FUNC_CFG_ACCESS</td><td>RW</td><td>01</td><td>00000001</td><td>00000000</td><td></td></tr><tr><td>PIN_CTRL</td><td>RW</td><td>02</td><td>00000010</td><td>00111111</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>03</td><td></td><td></td><td></td></tr><tr><td>S4S_TPH_L</td><td>RW</td><td>04</td><td>00000100</td><td>00000000</td><td></td></tr><tr><td>S4S_TPH_H</td><td>RW</td><td>05</td><td>00000101</td><td>00000000</td><td></td></tr><tr><td>S4S_RR</td><td>RW</td><td>06</td><td>00000110</td><td>00000000</td><td></td></tr><tr><td>FIFO_CTRL1</td><td>RW</td><td>07</td><td>00000111</td><td>00000000</td><td></td></tr><tr><td>FIFO_CTRL2</td><td>RW</td><td>08</td><td>00001000</td><td>00000000</td><td></td></tr><tr><td>FIFO_CTRL3</td><td>RW</td><td>09</td><td>00001001</td><td>00000000</td><td></td></tr><tr><td>FIFO_CTRL4</td><td>RW</td><td>0A</td><td>00001010</td><td>00000000</td><td></td></tr><tr><td>COUNTER_BDR_REG1</td><td>RW</td><td>0B</td><td>00001011</td><td>00000000</td><td></td></tr><tr><td>COUNTER_BDR_REG2</td><td>RW</td><td>0C</td><td>00001100</td><td>00000000</td><td></td></tr><tr><td>INT1_CTRL</td><td>RW</td><td>0D</td><td>00001101</td><td>00000000</td><td></td></tr><tr><td>INT2_CTRL</td><td>RW</td><td>0E</td><td>00001110</td><td>00000000</td><td></td></tr><tr><td>WHO_AM_I</td><td>R</td><td>0F</td><td>00001111</td><td>01101011</td><td>R (SPI2)</td></tr><tr><td>CTRL1_XL</td><td>RW</td><td>10</td><td>00010000</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL2_G</td><td>RW</td><td>11</td><td>00010001</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL3_C</td><td>RW</td><td>12</td><td>00010010</td><td>00000100</td><td>R (SPI2)</td></tr><tr><td>CTRL4_C</td><td>RW</td><td>13</td><td>00010011</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL5_C</td><td>RW</td><td>14</td><td>00010100</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL6_C</td><td>RW</td><td>15</td><td>00010101</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL7_G</td><td>RW</td><td>16</td><td>00010110</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL8_XL</td><td>RW</td><td>17</td><td>00010111</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL9_XL</td><td>RW</td><td>18</td><td>00011000</td><td>11100000</td><td>R (SPI2)</td></tr><tr><td>CTRL10_C</td><td>RW</td><td>19</td><td>00011001</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>ALL_INT_SRC</td><td>R</td><td>1A</td><td>00011010</td><td>output</td><td></td></tr><tr><td>WAKE_UP_SRC</td><td>R</td><td>1B</td><td>00011011</td><td>output</td><td></td></tr><tr><td>TAP_SRC</td><td>R</td><td>1C</td><td>00011100</td><td>output</td><td></td></tr><tr><td>D6D_SRC</td><td>R</td><td>1D</td><td>00011101</td><td>output</td><td></td></tr><tr><td>STATUS_REG<eq>^{(1)}</eq>/STATUS_SPIAux<eq>^{(2)}</eq></td><td>R</td><td>1E</td><td>00011110</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>1F</td><td></td><td></td><td></td></tr><tr><td>OUT_TEMP_L</td><td>R</td><td>20</td><td>00100000</td><td>output</td><td></td></tr><tr><td>OUT_TEMP_H</td><td>R</td><td>21</td><td>00100001</td><td>output</td><td></td></tr><tr><td>OUTX_L_G</td><td>R</td><td>22</td><td>00100010</td><td>output</td><td></td></tr><tr><td>OUTX_H_G</td><td>R</td><td>23</td><td>00100011</td><td>output</td><td></td></tr><tr><td>OUTY_L_G</td><td>R</td><td>24</td><td>00100100</td><td>output</td><td></td></tr><tr><td>OUTY_H_G</td><td>R</td><td>25</td><td>00100101</td><td>output</td><td></td></tr><tr><td>OUTZ_L_G</td><td>R</td><td>26</td><td>00100110</td><td>output</td><td></td></tr><tr><td>OUTZ_H_G</td><td>R</td><td>27</td><td>00100111</td><td>output</td><td></td></tr><tr><td>OUTX_L_A</td><td>R</td><td>28</td><td>00101000</td><td>output</td><td></td></tr><tr><td>OUTX_H_A</td><td>R</td><td>29</td><td>00101001</td><td>output</td><td></td></tr><tr><td>OUTY_L_A</td><td>R</td><td>2A</td><td>00101010</td><td>output</td><td></td></tr><tr><td>OUTY_H_A</td><td>R</td><td>2B</td><td>00101011</td><td>output</td><td></td></tr><tr><td>OUTZ_L_A</td><td>R</td><td>2C</td><td>00101100</td><td>output</td><td></td></tr><tr><td>OUTZ_H_A</td><td>R</td><td>2D</td><td>00101101</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>2E-34</td><td></td><td></td><td></td></tr><tr><td>EMB_FUNC_STATUS_MAINPAGE</td><td>R</td><td>35</td><td>00110101</td><td>output</td><td></td></tr><tr><td>FSM_STATUS_A_MAINPAGE</td><td>R</td><td>36</td><td>00110110</td><td>output</td><td></td></tr><tr><td>FSM_STATUS_B_MAINPAGE</td><td>R</td><td>37</td><td>00110111</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>38</td><td>00111000</td><td></td><td></td></tr><tr><td>STATUS_MASTER_MAINPAGE</td><td>R</td><td>39</td><td>00111001</td><td>output</td><td></td></tr><tr><td>FIFO_STATUS1</td><td>R</td><td>3A</td><td>00111010</td><td>output</td><td></td></tr><tr><td>FIFO_STATUS2</td><td>R</td><td>3B</td><td>00111011</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>3C-3F</td><td></td><td></td><td></td></tr><tr><td>TIMESTAMP0</td><td>R</td><td>40</td><td>01000000</td><td>output</td><td>R (SPI2)</td></tr><tr><td>TIMESTAMP1</td><td>R</td><td>41</td><td>01000001</td><td>output</td><td>R (SPI2)</td></tr><tr><td>TIMESTAMP2</td><td>R</td><td>42</td><td>01000010</td><td>output</td><td>R (SPI2)</td></tr><tr><td>TIMESTAMP3</td><td>R</td><td>43</td><td>01000011</td><td>output</td><td>R (SPI2)</td></tr><tr><td>RESERVED</td><td>-</td><td>44-55</td><td></td><td></td><td></td></tr><tr><td>TAP_CFG0</td><td>RW</td><td>56</td><td>01010110</td><td>00000000</td><td></td></tr><tr><td>TAP_CFG1</td><td>RW</td><td>57</td><td>01010111</td><td>00000000</td><td></td></tr><tr><td>TAP_CFG2</td><td>RW</td><td>58</td><td>01011000</td><td>00000000</td><td></td></tr><tr><td>TAP_THS_6D</td><td>RW</td><td>59</td><td>01011001</td><td>00000000</td><td></td></tr><tr><td>INT_DUR2</td><td>RW</td><td>5A</td><td>01011010</td><td>00000000</td><td></td></tr><tr><td>WAKE_UP_THS</td><td>RW</td><td>5B</td><td>01011011</td><td>00000000</td><td></td></tr><tr><td>WAKE_UP_DUR</td><td>RW</td><td>5C</td><td>01011100</td><td>00000000</td><td></td></tr><tr><td>FREE_FALL</td><td>RW</td><td>5D</td><td>01011101</td><td>00000000</td><td></td></tr><tr><td>MD1_CFG</td><td>RW</td><td>5E</td><td>01011110</td><td>00000000</td><td></td></tr><tr><td>MD2_CFG</td><td>RW</td><td>5F</td><td>01011111</td><td>00000000</td><td></td></tr><tr><td>S4S_ST_CMD_CODE</td><td>RW</td><td>60</td><td>01100000</td><td>00000000</td><td></td></tr><tr><td>S4S_DT_REG</td><td>RW</td><td>61</td><td>01100001</td><td>00000000</td><td></td></tr><tr><td>I3C_BUS_AVB</td><td>RW</td><td>62</td><td>01100010</td><td>00000000</td><td></td></tr><tr><td>INTERNAL_FREQ_FINE</td><td>R</td><td>63</td><td>01100011</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>64-6E</td><td></td><td></td><td></td></tr><tr><td>INT_OIS</td><td>R</td><td>6F</td><td>01101111</td><td>00000000</td><td>RW (SPI2)</td></tr><tr><td>CTRL1_OIS</td><td>R</td><td>70</td><td>01110000</td><td>00000000</td><td>RW (SPI2)</td></tr><tr><td>CTRL2_OIS</td><td>R</td><td>71</td><td>01110001</td><td>00000000</td><td>RW (SPI2)</td></tr><tr><td>CTRL3_OIS</td><td>R</td><td>72</td><td>01110010</td><td>00000000</td><td>RW (SPI2)</td></tr><tr><td>X_OFS_USR</td><td>RW</td><td>73</td><td>01110011</td><td>00000000</td><td></td></tr><tr><td>Y_OFS_USR</td><td>RW</td><td>74</td><td>01110100</td><td>00000000</td><td></td></tr><tr><td>Z_OFS_USR</td><td>RW</td><td>75</td><td>01110101</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>76-77</td><td></td><td></td><td></td></tr><tr><td>FIFO_DATA_OUT_TAG</td><td>R</td><td>78</td><td>01111000</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_X_L</td><td>R</td><td>79</td><td>01111001</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_X_H</td><td>R</td><td>7A</td><td>01111010</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_Y_L</td><td>R</td><td>7B</td><td>01111011</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_Y_H</td><td>R</td><td>7C</td><td>01111100</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_Z_L</td><td>R</td><td>7D</td><td>01111101</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_Z_H</td><td>R</td><td>7E</td><td>01111110</td><td>output</td><td></td></tr></table>

1. This register status is read using the primary interface for user interface data. 

2. This register status is read using the auxiliary SPI for OIS data. 

# 9 Register description

The device contains a set of registers which are used to control its behavior and to retrieve linear acceleration, angular rate and temperature data. The register addresses, made up of 7 bits, are used to identify them and to write the data through the serial interface. 

# 9.1 FUNC_CFG_ACCESS (01h)

Enable embedded functions register (r/w) 


Table 21. FUNC_CFG_ACCESS register


<table><tr><td>FUNC_CFG_ACCESS</td><td>SHUB_REG_ACCESS</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 22. FUNC_CFG_ACCESS register description


<table><tr><td>FUNC_CFG_ACCESS</td><td>Enable access to the embedded functions configuration registers.Default value: <eq>0^{(1)}</eq></td></tr><tr><td>SHUB_REG_ACCESS</td><td>Enable access to the sensor hub (<eq>I^{2}C</eq> master) registers.Default value: <eq>0^{(2)}</eq></td></tr></table>

1. Details concerning the embedded functions configuration registers are available in Section 10 Embedded functions register mapping and Section 11 Embedded functions register description. 

2. Details concerning the sensor hub registers are available in Section 14 Sensor hub register mapping and Section 15 Sensor hub register description. 

# 9.2 PIN_CTRL (02h)

SDO, OCS_AUX, SDO_AUX pins pull-up enable/disable register (r/w) 


Table 23. PIN_CTRL register


<table><tr><td>OIS_PU_DIS</td><td>SDO_PU_EN</td><td><eq>1^{(1)}</eq></td><td><eq>1^{(1)}</eq></td><td><eq>1^{(1)}</eq></td><td><eq>1^{(1)}</eq></td><td><eq>1^{(1)}</eq></td><td><eq>1^{(1)}</eq></td></tr></table>


1. This bit must be set to '1' for the correct operation of the device. 



Table 24. PIN_CTRL register description


<table><tr><td>OIS_PU_DIS</td><td>Disable pull-up on both OCS_Aux and SDO_Aux pins. Default value: 0(0: OCS_Aux and SDO_Aux pins with pull-up;1: OCS_Aux and SDO_Aux pins pull-up disconnected)</td></tr><tr><td>SDO_PU_EN</td><td>Enable pull-up on SDO pin. Default value: 0(0: SDO pin pull-up disconnected (default); 1: SDO pin with pull-up)</td></tr></table>

# 9.3 S4S_TPH_L (04h)

Sensor synchronization time frame register (r/w) 


Table 25. S4S_TPH_L register


<table><tr><td>TPH_H_SEL</td><td>TPH_L_6</td><td>TPH_L_5</td><td>TPH_L_4</td><td>TPH_L_3</td><td>TPH_L_2</td><td>TPH_L_1</td><td>TPH_L_0</td></tr></table>


Table 26. S4S_TPH_L register description


<table><tr><td>TPH_H_SEL</td><td>Chooses if the TPH formula must be taken into account (see equation below).</td></tr><tr><td>TPH_L_[6:0]</td><td>S4S timeframe expressed in number of samples as described in the equation below.If TPH_H_SEL=0 and TPH_L_[6:0] = d0, S4S is disabled.</td></tr></table>

When TPH_H_SEL = 0: TPH [#Samples] = 2 x TPHL 

When TPH_H_SEL = 1: TPH [#Samples] = 2 x (TPH_L + 256 x TPH_H) 

# 9.4 S4S_TPH_H (05h)

Sensor synchronization time frame register (r/w) 


Table 27. S4S_TPH_H register


<table><tr><td>TPH_H_7</td><td>TPH_H_6</td><td>TPH_H_5</td><td>TPH_H_4</td><td>TPH_H_3</td><td>TPH_H_2</td><td>TPH_H_1</td><td>TPH_H_0</td></tr></table>


Table 28. S4S_TPH_H register description


<table><tr><td>TPH_H_[7:0]</td><td>S4S time frame expressed in number of samples. Only if the TPH_H_SEL bit in S4S_TPH_L (04h) is high, is the value of this register taken into account as described in the equation in S4S_TPH_L (04h)</td></tr></table>

# 9.5 S4S_RR (06h)

Sensor synchronization resolution ratio register (r/w) 


Table 29. S4S_RR register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>RR_1</td><td>RR_0</td></tr></table>

1. This bit must be set to '0' for the correct operation of the device. 


Table 30. S4S_RR register description


<table><tr><td>RR_[1:0]</td><td>(00: S4S, DT resolution <eq>2^{11}</eq>;01: S4S, DT resolution <eq>2^{12}</eq>;10: S4S, DT resolution <eq>2^{13}</eq>;11: S4S, DT resolution <eq>2^{14}</eq>)</td></tr></table>

# 9.6 FIFO_CTRL1 (07h)

FIFO control register 1 (r/w) 


Table 31. FIFO_CTRL1 register


<table><tr><td>WTM7</td><td>WTM6</td><td>WTM5</td><td>WTM4</td><td>WTM3</td><td>WTM2</td><td>WTM1</td><td>WTM0</td></tr></table>


Table 32. FIFO_CTRL1 register description


<table><tr><td>WTM[7:0]</td><td>FIFO watermark threshold, in conjunction with WTM8 in FIFO_CTRL2 (08h).1 LSB = 1 sensor (6 bytes) + TAG (1 byte) written in FIFOWatermark flag rises when the number of bytes written in the FIFO is greater than or equal to the threshold level.</td></tr></table>

# 9.7 FIFO_CTRL2 (08h)

FIFO control register 2 (r/w) 


Table 33. FIFO_CTRL2 register


<table><tr><td>STOP_ON_WTM</td><td>FIFO_COMPR_RT_EN</td><td><eq>0^{(1)}</eq></td><td>ODRCHG_EN</td><td><eq>0^{(1)}</eq></td><td>UNCOPTR_RATE_1</td><td>UNCOPTR_RATE_0</td><td>WTM8</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 34. FIFO_CTRL2 register


<table><tr><td>STOP_ON_WTM</td><td>Sensing chain FIFO stop values memorization at threshold level(0: FIFO depth is not limited (default);1: FIFO depth is limited to the threshold level, defined inFIFO_CTRL1(07h)andFIFO_CTRL2(08h)</td></tr><tr><td>FIFO_COMPR_RT_EN<eq>^{(1)}</eq></td><td>Enables/Disables compression algorithm runtime</td></tr><tr><td>ODRCHG_EN</td><td>Enables ODR CHANGE virtual sensor to be batched in FIFO</td></tr><tr><td>UNCOPTR_RATE_[1:0]</td><td>This field configures the compression algorithm to write non-compressed data at each rate.(0: Non-compressed data writing is not forced;1: Non-compressed data every 8 batch data rate;2: Non-compressed data every 16 batch data rate;3: Non-compressed data every 32 batch data rate)</td></tr><tr><td>WTM8</td><td>FIFO watermark threshold, in conjunction with WTM[7:0]inFIFO_CTRL1(07h).1 LSB = 1 sensor (6 bytes) + TAG (1 byte) written in FIFOWatermark flag rises when the number of bytes written in FIFO is greater than or equal to the threshold level.</td></tr></table>


1. This bit is effective if the FIFO_COMPR_EN bit of EMB_FUNC_EN_B (05h) is set to 1. 


# 9.8 FIFO_CTRL3 (09h)

FIFO control register 3 (r/w) 


Table 35. FIFO_CTRL3 register


<table><tr><td>BDR_GY_3</td><td>BDR_GY_2</td><td>BDR_GY_1</td><td>BDR_GY_0</td><td>BDR_XL_3</td><td>BDR_XL_2</td><td>BDR_XL_1</td><td>BDR_XL_0</td></tr></table>


Table 36. FIFO_CTRL3 register description


<table><tr><td>BDR_GY_[3:0]</td><td>Selects Batch Data Rate (write frequency in FIFO) for gyroscope data.(0000: Gyro not batched in FIFO (default);0001: 12.5 Hz;0010: 26 Hz;0011: 52 Hz;0100: 104 Hz;0101: 208 Hz;0110: 417 Hz;0111: 833 Hz;1000: 1667 Hz;1001: 3333 Hz;1010: 6667 Hz;1011: 6.5 Hz;1100-1111: not allowed)</td></tr><tr><td>BDR_XL_[3:0]</td><td>Selects Batch Data Rate (write frequency in FIFO) for accelerometer data.(0000: Accelerometer not batched in FIFO (default);0001: 12.5 Hz;0010: 26 Hz;0011: 52 Hz;0100: 104 Hz;0101: 208 Hz;0110: 417 Hz;0111: 833 Hz;1000: 1667 Hz;1000: 3333 Hz;1010: 6667 Hz;1011: 1.6 Hz;1100-1111: not allowed)</td></tr></table>

# 9.9 FIFO_CTRL4 (0Ah)

FIFO control register 4 (r/w) 


Table 37. FIFO_CTRL4 register


<table><tr><td>DEC_TS_BATCH_1</td><td>DEC_TS_BATCH_0</td><td>ODR_TBATCH_1</td><td>ODR_TBATCH_0</td><td><eq>0^{(1)}</eq></td><td>FIFO_MODE2</td><td>FIFO_MODE1</td><td>FIFO_MODE0</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 38. FIFO_CTRL4 register description


<table><tr><td>DEC_TS_BATCH_[1:0]</td><td>Selects decimation for timestamp batching in FIFO. Write rate will be the maximum rate between XL and GYRO BDR divided by decimation decoder.(00: Timestamp not batched in FIFO (default);01: Decimation 1: max(BDR_XL[Hz],BDR_GY[Hz]) [Hz];10: Decimation 8: max(BDR_XL[Hz],BDR_GY[Hz])/8 [Hz];11: Decimation 32: max(BDR_XL[Hz],BDR_GY[Hz])/32 [Hz])</td></tr><tr><td>ODR_T_BATCH_[1:0]</td><td>Selects batch data rate (write frequency in FIFO) for temperature data(00: Temperature not batched in FIFO (default);01: 1.6 Hz;10: 12.5 Hz;11: 52 Hz)</td></tr><tr><td>FIFO_MODE[2:0]</td><td>FIFO mode selection(000: Bypass mode: FIFO disabled;001: FIFO mode: stops collecting data when FIFO is full;010: Reserved;011: Continuous-to-FIFO mode: Continuous mode until trigger is deasserted, then FIFO mode;100: Bypass-to-Continuous mode: Bypass mode until trigger is deasserted, then Continuous mode;101: Reserved;110: Continuous mode: if the FIFO is full, the new sample overwrites the older one;111: Bypass-to-FIFO mode: Bypass mode until trigger is deasserted, then FIFO mode.)</td></tr></table>

# 9.10 COUNTER_BDR_REG1 (0Bh)

Counter batch data rate register 1 (r/w) 


Table 39. COUNTER_BDR_REG1 register


<table><tr><td>dataready_pulsed</td><td>RST_COUNTER_BDR</td><td>TRIG_COUNTER_BDR</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>CNT_BDR_TH_10</td><td>CNT_BDR_TH_9</td><td>CNT_BDR_TH_8</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 40. COUNTER_BDR_REG1 register description


<table><tr><td>dataready_pulsed</td><td>Enables pulsed data-ready mode(0: Data-ready latched mode (returns to 0 only after an interface reading) (default);1: Data-ready pulsed mode (the data ready pulses are 75 μs long)</td></tr><tr><td>RST_COUNTER_BDR</td><td>Resets the internal counter of batch events for a single sensor.This bit is automatically reset to zero if it was set to ‘1’.</td></tr><tr><td>TRIG_COUNTER_BDR</td><td>Selects the trigger for the internal counter of batch events between XL and gyro.(0: XL batch event;1: GYRO batch event)</td></tr><tr><td>CNT_BDR_TH_[10:8]</td><td>In conjunction with CNT_BDR_TH_[7:0] in COUNTER_BDR_REG2 (0Ch), sets the threshold for the internal counter of batch events. When this counter reaches the threshold, the counter is reset and the COUNTER_BDR_IA flag in FIFO_STATUS2 (3Bh) is set to ‘1’.</td></tr></table>

# 9.11 COUNTER_BDR_REG2 (0Ch)

Counter batch data rate register 2 (r/w) 


Table 41. COUNTER_BDR_REG2 register


<table><tr><td>CNT_BDR_TH_7</td><td>CNT_BDR_TH_6</td><td>CNT_BDR_TH_5</td><td>CNT_BDR_TH_4</td><td>CNT_BDR_TH_3</td><td>CNT_BDR_TH_2</td><td>CNT_BDR_TH_1</td><td>CNT_BDR_TH_0</td></tr></table>


Table 42. COUNTER_BDR_REG2 register description


<table><tr><td>CNT_BDR_TH_[7:0]</td><td>In conjunction with CNT_BDR_TH_[10:8] in COUNTER_BDR_REG1 (0Bh), sets the threshold for the internal counter of batch events. When this counter reaches the threshold, the counter is reset and the COUNTER_BDR_IA flag in FIFO_STATUS2 (3Bh) is set to ‘1’.</td></tr></table>

# 9.12 INT1_CTRL (0Dh)

INT1 pin control register (r/w) 

Each bit in this register enables a signal to be carried over INT1 when the MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ dynamic address is not assigned (I²C or SPI is used). Some bits can be also used to trigger an IBI (In-Band Interrupt) when the MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ interface is used.. The output of the pad will be the OR combination of the signals selected here and in register MD1_CFG (5Eh). 


Table 43. INT1_CTRL register


<table><tr><td>DEN_DRDY_flag</td><td>INT1_CNT_BDR</td><td>INT1_FIFO_FULL</td><td>INT1_FIFO_OVR</td><td>INT1_FIFO_TH</td><td>INT1_BOOT</td><td>INT1_DRDY_G</td><td>INT1_DRDY_XL</td></tr></table>


Table 44. INT1_CTRL register description


<table><tr><td>DEN_DRDY_flag</td><td>Sends DEN_DRDY (DEN stamped on Sensor Data flag) to INT1 pin.</td></tr><tr><td>INT1_CNT_BDR</td><td>Enables COUNTER_BDR_IA interrupt on INT1.</td></tr><tr><td>INT1_FIFO_FULL</td><td>Enables FIFO full flag interrupt on INT1 pin.It can be also used to trigger an IBI when the MIPI <eq>I3C^{SM}</eq> interface is used.</td></tr><tr><td>INT1_FIFO_OVR</td><td>Enables FIFO overrun interrupt on INT1 pin.It can be also used to trigger an IBI when the MIPI <eq>I3C^{SM}</eq> interface is used.</td></tr><tr><td>INT1_FIFO_TH</td><td>Enables FIFO threshold interrupt on INT1 pin.It can be also used to trigger an IBI when the MIPI <eq>I3C^{SM}</eq> interface is used.</td></tr><tr><td>INT1_BOOT</td><td>Enables boot status on INT1 pin.</td></tr><tr><td>INT1_DRDY_G</td><td>Enables gyroscope data-ready interrupt on INT1 pin.It can be also used to trigger an IBI when the MIPI <eq>I3C^{SM}</eq> interface is used.</td></tr><tr><td>INT1_DRDY_XL</td><td>Enables accelerometer data-ready interrupt on INT1 pin.It can be also used to trigger an IBI when the MIPI <eq>I3C^{SM}</eq> interface is used.</td></tr></table>

# 9.13 INT2_CTRL (0Eh)

INT2 pin control register (r/w). 

Each bit in this register enables a signal to be carried over INT2 when the MIPI ${ \mathsf { I } } { \mathsf { 3 C } } ^ { \mathsf { S M } }$ dynamic address in not assigned (I²C or SPI is used). Some bits can be also used to trigger an IBI when the MIPI I3CSM interface is used.. The output of the pad will be the OR combination of the signals selected here and in register MD2_CFG (5Fh). 


Table 45. INT2_CTRL register


<table><tr><td><eq>0^{(1)}</eq></td><td>INT2_CNT_BDR</td><td>INT2_FIFO_FULL</td><td>INT2_FIFO_OVR</td><td>INT2_FIFO_TH</td><td>INT2_DRDY_TEMP</td><td>INT2_DRDY_G</td><td>INT2_DRDY_XL</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 46. INT2_CTRL register description


<table><tr><td>INT2_CNT_BDR</td><td>Enables COUNTER_BDR_IA interrupt on INT2 pin.</td></tr><tr><td>INT2_FIFO_FULL</td><td>Enables FIFO full flag interrupt on INT2 pin.</td></tr><tr><td>INT2_FIFO_OVR</td><td>Enables FIFO overrun interrupt on INT2 pin.</td></tr><tr><td>INT_FIFO_TH</td><td>Enables FIFO threshold interrupt on INT2 pin.</td></tr><tr><td>INT2_DRDY_TEMP</td><td>Enables temperature sensor data-ready interrupt on INT2 pin.It can be also used to trigger an IBI when the MIPI <eq>I3C^{SM}</eq> interface is used and INT2_ON_INT1 = ‘1’ in CTRL4_C (13h).</td></tr><tr><td>INT2_DRDY_G</td><td>Enables gyroscope data-ready interrupt on INT2 pin.</td></tr><tr><td>INT2_DRDY_XL</td><td>Enables accelerometer data-ready interrupt on INT2 pin.</td></tr></table>

# 9.14 WHO_AM_I (0Fh)

WHO_AM_I register (r). This is a read-only register. Its value is fixed at 6Bh. 


Table 47. WhoAmI register


<table><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>0</td><td>1</td><td>1</td></tr></table>

# 9.15 CTRL1_XL (10h)

Accelerometer control register 1 (r/w) 


Table 48. CTRL1_XL register


<table><tr><td>ODR_XL3</td><td>ODR_XL2</td><td>ODR_XL1</td><td>ODR_XL0</td><td>FS1_XL</td><td>FS0_XL</td><td>LPF2_XL_EN</td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 49. CTRL1_XL register description


<table><tr><td>ODR_XL[3:0]</td><td>Accelerometer ODR selection (see Table 50).</td></tr><tr><td>FS[1:0]_XL</td><td>Accelerometer full-scale selection. Default value: 00(00: ±2 g; 01: ±16 g; 10: ±4 g; 11: ±8 g)</td></tr><tr><td>LPF2_XL_EN</td><td>Accelerometer high-resolution selection(0: output from first stage digital filtering selected (default);1: output from LPF2 second filtering stage selected)</td></tr></table>


Table 50. Accelerometer ODR selection


<table><tr><td>ODR_XL3</td><td>ODR_XL2</td><td>ODR_XL1</td><td>ODR_XL0</td><td>ODR selection [Hz] when XL_HM_MODE = 1 in CTRL6_C (15h)</td><td>ODR selection [Hz] when XL_HM_MODE = 0 in CTRL6_C (15h)</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>Power-down</td><td>Power-down</td></tr><tr><td>1</td><td>0</td><td>1</td><td>1</td><td>1.6 Hz (low power only)</td><td>N.A.</td></tr><tr><td>0</td><td>0</td><td>0</td><td>1</td><td>12.5 Hz (low power)</td><td>12.5 Hz (high performance)</td></tr><tr><td>0</td><td>0</td><td>1</td><td>0</td><td>26 Hz (low power)</td><td>26 Hz (high performance)</td></tr><tr><td>0</td><td>0</td><td>1</td><td>1</td><td>52 Hz (low power)</td><td>52 Hz (high performance)</td></tr><tr><td>0</td><td>1</td><td>0</td><td>0</td><td>104 Hz (normal mode)</td><td>104 Hz (high performance)</td></tr><tr><td>0</td><td>1</td><td>0</td><td>1</td><td>208 Hz (normal mode)</td><td>208 Hz (high performance)</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>416 Hz (high performance)</td><td>416 Hz (high performance)</td></tr><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>833 Hz (high performance)</td><td>833 Hz (high performance)</td></tr><tr><td>1</td><td>0</td><td>0</td><td>0</td><td>1.66 kHz (high performance)</td><td>1.66 kHz (high performance)</td></tr><tr><td>1</td><td>0</td><td>0</td><td>1</td><td>3.33 kHz (high performance)</td><td>3.33 kHz (high performance)</td></tr><tr><td>1</td><td>0</td><td>1</td><td>0</td><td>6.66 kHz (high performance)</td><td>6.66 kHz (high performance)</td></tr><tr><td>1</td><td>1</td><td>x</td><td>x</td><td>Not allowed</td><td>Not allowed</td></tr></table>

# 9.16 CTRL2_G (11h)

Gyroscope control register 2 (r/w) 


Table 51. CTRL2_G register


<table><tr><td>ODR_G3</td><td>ODR_G2</td><td>ODR_G1</td><td>ODR_G0</td><td>FS1_G</td><td>FS0_G</td><td>FS_125</td><td>FS_4000</td></tr></table>


Table 52. CTRL2_G register description


<table><tr><td>ODR_G[3:0]</td><td>Gyroscope output data rate selection. Default value: 0000(Refer to Table 53)</td></tr><tr><td>FS[1:0]_G</td><td>Gyroscope chain full-scale selection(00: ±250 dps;01: ±500 dps;10: ±1000 dps;11: ±2000 dps)</td></tr><tr><td>FS_125</td><td>Selects gyro chain full-scale ±125 dps(0: FS selected through bits FS[1:0]_G;1: FS set to ±125 dps)</td></tr><tr><td><eq>FS_{4000}^{(1)}</eq></td><td>Selects gyro chain full-scale ±4000 dps(0: FS selected through bits FS[1:0]_G or FS_125;1: FS set to ±4000 dps)</td></tr></table>


1. This bit has to be set to 0 when the OIS chain is ON (OIS_EN_SPI2 bit =1 in CTRL1_OIS (70h)) 



Table 53. Gyroscope ODR configuration setting


<table><tr><td>ODR_G3</td><td>ODR_G2</td><td>ODR_G1</td><td>ODR_G0</td><td>ODR selection [Hz] when G_HM_MODE = 1 in CTRL7_G (16h)</td><td>ODR selection [Hz] when G_HM_MODE = 0 in CTRL7_G (16h)</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>Power-down</td><td>Power-down</td></tr><tr><td>0</td><td>0</td><td>0</td><td>1</td><td>12.5 Hz (low power)</td><td>12.5 Hz (high performance)</td></tr><tr><td>0</td><td>0</td><td>1</td><td>0</td><td>26 Hz (low power)</td><td>26 Hz (high performance)</td></tr><tr><td>0</td><td>0</td><td>1</td><td>1</td><td>52 Hz (low power)</td><td>52 Hz (high performance)</td></tr><tr><td>0</td><td>1</td><td>0</td><td>0</td><td>104 Hz (normal mode)</td><td>104 Hz (high performance)</td></tr><tr><td>0</td><td>1</td><td>0</td><td>1</td><td>208 Hz (normal mode)</td><td>208 Hz (high performance)</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>416 Hz (high performance)</td><td>416 Hz (high performance)</td></tr><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>833 Hz (high performance)</td><td>833 Hz (high performance)</td></tr><tr><td>1</td><td>0</td><td>0</td><td>0</td><td>1.66 kHz (high performance)</td><td>1.66 kHz (high performance)</td></tr><tr><td>1</td><td>0</td><td>0</td><td>1</td><td>3.33 kHz (high performance)</td><td>3.33 kHz (high performance)</td></tr><tr><td>1</td><td>0</td><td>1</td><td>0</td><td>6.66 kHz (high performance)</td><td>6.66 kHz (high performance)</td></tr><tr><td>1</td><td>0</td><td>1</td><td>1</td><td>Not available</td><td>Not available</td></tr></table>

# 9.17 CTRL3_C (12h)

Control register 3 (r/w) 


Table 54. CTRL3_C register


<table><tr><td>BOOT</td><td>BDU</td><td>H_LACTIVE</td><td>PP_OD</td><td>SIM</td><td>IF_INC</td><td><eq>0^{(1)}</eq></td><td>SW_RESET</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 55. CTRL3_C register description


<table><tr><td>BOOT</td><td>Reboots memory content. Default value: 0(0: normal mode; 1: reboot memory content)Note: the accelerometer must be ON. This bit is automatically cleared.</td></tr><tr><td>BDU</td><td>Block Data Update. Default value: 0(0: continuous update;1: output registers are not updated until MSB and LSB have been read)</td></tr><tr><td>H_LACTIVE</td><td>Interrupt activation level. Default value: 0(0: interrupt output pins active high; 1: interrupt output pins active low</td></tr><tr><td>PP_OD</td><td>Push-pull/open-drain selection on INT1 and INT2 pins. This bit must be set to &#x27;0&#x27; when H_LACTIVE is set to &#x27;1&#x27;.Default value: 0(0: push-pull mode; 1: open-drain mode)</td></tr><tr><td>SIM</td><td>SPI Serial Interface Mode selection. Default value: 0(0: 4-wire interface; 1: 3-wire interface)</td></tr><tr><td>IF_INC</td><td>Register address automatically incremented during a multiple byte access with a serial interface (I2C or SPI).Default value: 1(0: disabled; 1: enabled)</td></tr><tr><td>SW_RESET</td><td>Software reset. Default value: 0(0: normal mode; 1: reset device)This bit is automatically cleared.</td></tr></table>

# 9.18 CTRL4_C (13h)

Control register 4 (r/w) 


Table 56. CTRL4_C register


<table><tr><td><eq>0^{(1)}</eq></td><td>SLEEP_G</td><td>INT2_on_INT1</td><td><eq>0^{(1)}</eq></td><td>DRDY_MASK</td><td>I2C_disable</td><td>LPF1_SEL_G</td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 57. CTRL4_C register description


<table><tr><td>SLEEP_G</td><td>Enables gyroscope Sleep mode. Default value:0(0: disabled; 1: enabled)</td></tr><tr><td>INT2_on_INT1</td><td>All interrupt signals available on INT1 pin enable. Default value: 0(0: interrupt signals divided between INT1 and INT2 pins;1: all interrupt signals in logic or on INT1 pin)</td></tr><tr><td>DRDY_MASK</td><td>Enables data available(0: disabled;1: mask DRDY on pin (both XL &amp; Gyro) until filter settling ends (XL and Gyro independently masked).</td></tr><tr><td>I2C_disable</td><td>Disables I2C interface. Default value: 0(0: SPI, I2C and MIPI I3CSM interfaces enabled (default); 1: I2C interface disabled)</td></tr><tr><td>LPF1_SEL_G</td><td>Enables gyroscope digital LPF1; the bandwidth can be selected through FTYPE[2:0] in CTRL6_C (15h).(0: disabled; 1: enabled)</td></tr></table>

# 9.19 CTRL5_C (14h)

Control register 5 (r/w) 


Table 58. CTRL5_C register


<table><tr><td><eq>0^{(1)}</eq></td><td>ROUNDING1</td><td>ROUNDING0</td><td><eq>0^{(1)}</eq></td><td>ST1_G</td><td>ST0_G</td><td>ST1_XL</td><td>ST0_XL</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 59. CTRL5_C register description


<table><tr><td>ROUNDING[1:0]</td><td>Circular burst-mode (rounding) read of the output registers. Default value: 00(00: no rounding;01: accelerometer only;10: gyroscope only;11: gyroscope + accelerometer)</td></tr><tr><td>ST[1:0]_G</td><td>Angular rate sensor self-test enable. Default value: 00(00: Self-test disabled; Other: refer to Table 60)</td></tr><tr><td>ST[1:0]_XL</td><td>Linear acceleration sensor self-test enable. Default value: 00(00: Self-test disabled; Other: refer to Table 61)</td></tr></table>


Table 60. Angular rate sensor self-test mode selection


<table><tr><td>ST1_G</td><td>ST0_G</td><td>Self-test mode</td></tr><tr><td>0</td><td>0</td><td>Normal mode</td></tr><tr><td>0</td><td>1</td><td>Positive sign self-test</td></tr><tr><td>1</td><td>0</td><td>Not allowed</td></tr><tr><td>1</td><td>1</td><td>Negative sign self-test</td></tr></table>


Table 61. Linear acceleration sensor self-test mode selection


<table><tr><td>ST1_XL</td><td>ST0_XL</td><td>Self-test mode</td></tr><tr><td>0</td><td>0</td><td>Normal mode</td></tr><tr><td>0</td><td>1</td><td>Positive sign self-test</td></tr><tr><td>1</td><td>0</td><td>Negative sign self-test</td></tr><tr><td>1</td><td>1</td><td>Not allowed</td></tr></table>

# 9.20 CTRL6_C (15h)

Control register 6 (r/w) 


Table 62. CTRL6_C register


<table><tr><td>TRIG_EN</td><td>LVL1_EN</td><td>LVL2_EN</td><td>XL_HM_MODE</td><td>USR_OFF_W</td><td>FTYPE_2</td><td>FTYPE_1</td><td>FTYPE_0</td></tr></table>


Table 63. CTRL6_C register description


<table><tr><td>TRIG_EN</td><td>Enables DEN data edge-sensitive trigger mode. Refer to Table 64.</td></tr><tr><td>LVL1_EN</td><td>Enables DEN data level-sensitive trigger mode. Refer to Table 64.</td></tr><tr><td>LVL2_EN</td><td>Enables DEN level-sensitive latched mode. Refer to Table 64.</td></tr><tr><td>XL_HM_MODE</td><td>Disables high-performance operating mode for accelerometer. Default value: 0(0: high-performance operating mode enabled;1: high-performance operating mode disabled)</td></tr><tr><td>USR_OFF_W</td><td>Weight of XL user offset bits of registers X_OFS_USR (73h), Y_OFS_USR (74h), Z_OFS_USR (75h)(0 = <eq>2^{-10}</eq> g/LSB;<eq>1 = 2^{-6}</eq> g/LSB)</td></tr><tr><td>FTYPE[2:0]</td><td>Gyroscope low-pass filter (LPF1) bandwidth selection. Table 65 shows the selectable bandwidth values.</td></tr></table>


Table 64. Trigger mode selection


<table><tr><td>TRIG_EN, LVL1_EN, LVL2_EN</td><td>Trigger mode</td></tr><tr><td>100</td><td>Edge-sensitive trigger mode is selected</td></tr><tr><td>010</td><td>Level-sensitive trigger mode is selected</td></tr><tr><td>011</td><td>Level-sensitive latched mode is selected</td></tr><tr><td>110</td><td>Level-sensitive FIFO enable mode is selected</td></tr></table>


Table 65. Gyroscope LPF1 bandwidth selection


<table><tr><td>FTYPE[2:0]</td><td>12.5 Hz</td><td>26 Hz</td><td>52 Hz</td><td>104 Hz</td><td>208 Hz</td><td>416 Hz</td><td>833 Hz</td><td>1.67 kHz</td><td>3.33 kHz</td><td>6.67 kHz</td></tr><tr><td>000</td><td>4.3</td><td>8.3</td><td>16.7</td><td>33</td><td>67</td><td>133</td><td>222</td><td>274</td><td>292</td><td>297</td></tr><tr><td>001</td><td>4.3</td><td>8.3</td><td>16.7</td><td>33</td><td>67</td><td>128</td><td>186</td><td>212</td><td>220</td><td>223</td></tr><tr><td>010</td><td>4.3</td><td>8.3</td><td>16.7</td><td>33</td><td>67</td><td>112</td><td>140</td><td>150</td><td>153</td><td>154</td></tr><tr><td>011</td><td>4.3</td><td>8.3</td><td>16.7</td><td>33</td><td>67</td><td>134</td><td>260</td><td>390</td><td>451</td><td>470</td></tr><tr><td>100</td><td>4.3</td><td>8.3</td><td>16.7</td><td>34</td><td>62</td><td>86</td><td>96</td><td>90</td><td colspan="2">NA</td></tr><tr><td>101</td><td>4.3</td><td>8.3</td><td>16.9</td><td>31</td><td>43</td><td>48</td><td>49</td><td>50</td><td colspan="2">NA</td></tr><tr><td>110</td><td>4.3</td><td>8.3</td><td>13.4</td><td>19</td><td>23</td><td>24.6</td><td>25</td><td>25</td><td colspan="2">NA</td></tr><tr><td>111</td><td>4.3</td><td>8.3</td><td>9.8</td><td>11.6</td><td>12.2</td><td>12.4</td><td>12.6</td><td>12.6</td><td colspan="2">NA</td></tr></table>

# 9.21 CTRL7_G (16h)

Control register 7 (r/w) 


Table 66. CTRL7_G register


<table><tr><td>G_HM_MODE</td><td>HP_EN_G</td><td>HPM1_G</td><td>HPM0_G</td><td><eq>0^{(1)}</eq></td><td>OIS_ON_EN</td><td>USR_OFF_ON_OUT</td><td>OIS_ON</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 


<table><tr><td>G_HM_MODE</td><td>Disables high-performance operating mode for gyroscope. Default: 0(0: high-performance operating mode enabled;1: high-performance operating mode disabled)</td></tr><tr><td>HP_EN_G</td><td>Enables gyroscope digital high-pass filter. The filter is enabled only if the gyro is in HP mode. Default value: 0(0: HPF disabled; 1: HPF enabled)</td></tr><tr><td>HPM_G[1:0]</td><td>Gyroscope digital HP filter cutoff selection. Default: 00(00 = 16 mHz;01 = 65 mHz;10 = 260 mHz;11 = 1.04 Hz)</td></tr><tr><td>OIS_ON_EN<eq>^{(1)}</eq></td><td>Selects how to enable and disable the OIS chain, after first configuration and enabling through SPI2.(0: OIS chain is enabled/disabled with SPI2 interface;1: OIS chain is enabled/disabled with primary interface)</td></tr><tr><td>USR_OFF_ON_OUT</td><td>Enables accelerometer user offset correction block; it&#x27;s valid for the low-pass path - see Figure 17. Accelerometer composite filter. Default value: 0(0: accelerometer user offset correction block bypassed;1: accelerometer user offset correction block enabled)</td></tr><tr><td>OIS_ON</td><td>Enables/disables the OIS chain from primary interface when the OIS_ON_EN bit is &#x27;1&#x27;.(0: OIS disabled; 1: OIS enabled)</td></tr></table>


1. First, enabling OIS and OIS configurations must be done through SPI2, with OIS_ON_EN and OIS_ON set to '0'. 


# 9.22 CTRL8_XL (17h)

Control register 8 (r/w) 


Table 67. CTRL8_XL register


<table><tr><td>HPCF_XL_2</td><td>HPCF_XL_1</td><td>HPCF_XL_0</td><td>HP_REF_MODE_XL</td><td>FASTSETTL_MODE_XL</td><td>HP_SLOPE_XL_EN</td><td><eq>0^{(1)}</eq></td><td>LOW_PASS_ON_6D</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 


<table><tr><td>HPCF_XL_[2:0]</td><td>Accelerometer LPF2 and HP filter configuration and cutoff setting. Refer to Table 68.</td></tr><tr><td>HP_REF_MODE_XL</td><td>Enables accelerometer high-pass filter reference mode (valid for high-pass path - HP_SLOPE_XL_EN bit must be ‘1’). Default value: 0(0: disabled, 1: enabled<eq>^{(1)}</eq>)</td></tr><tr><td>FASTSETTL_MODE_XL</td><td>Enables accelerometer LPF2 and HPF fast-settling mode. The filter sets the second samples after writing this bit. Active only during device exit from power- down mode. Default value: 0(0: disabled, 1: enabled)</td></tr><tr><td>HP_SLOPE_XL_EN</td><td>Accelerometer slope filter / high-pass filter selection. Refer to Figure 25.</td></tr><tr><td>LOW_PASS_ON_6D</td><td>LPF2 on 6D function selection. Refer to Figure 25. Default value: 0(0: ODR/2 low-pass filtered data sent to 6D interrupt function;1: LPF2 output data sent to 6D interrupt function)</td></tr></table>


1. When enabled, the first output data have to be discarded. 



Table 68. Accelerometer bandwidth configurations


<table><tr><td>Filter type</td><td>HP_SLOPE_XL_EN</td><td>LPF2_XL_EN</td><td>HPCF_XL_[2:0]</td><td>Bandwidth(1)</td></tr><tr><td rowspan="9">Low pass</td><td rowspan="9">0</td><td>0</td><td>-</td><td>ODR/2</td></tr><tr><td rowspan="8">1</td><td>000</td><td>ODR/4</td></tr><tr><td>001</td><td>ODR/10</td></tr><tr><td>010</td><td>ODR/20</td></tr><tr><td>011</td><td>ODR/45</td></tr><tr><td>100</td><td>ODR/100</td></tr><tr><td>101</td><td>ODR/200</td></tr><tr><td>110</td><td>ODR/400</td></tr><tr><td>111</td><td>ODR/800</td></tr><tr><td rowspan="8">High pass</td><td rowspan="8">1</td><td rowspan="8">-</td><td>000</td><td>SLOPE (ODR/4)</td></tr><tr><td>001</td><td>ODR/10</td></tr><tr><td>010</td><td>ODR/20</td></tr><tr><td>011</td><td>ODR/45</td></tr><tr><td>100</td><td>ODR/100</td></tr><tr><td>101</td><td>ODR/200</td></tr><tr><td>110</td><td>ODR/400</td></tr><tr><td>I11</td><td>ODR/800</td></tr></table>


1. Typical value for ODR up to 833 Hz. 



Figure 25. Accelerometer block diagram


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/9f1719fff2a069bcc6549088e4cfd749d97d33b299e4c34e5e7ff6b8465f243e.jpg)


1. The cutoff value of the LPF1 output is ODR/2 when the accelerometer is in high-performance mode and ODR up to 833 Hz. This value is equal to 780 Hz when the accelerometer is in low-power or normal mode. 

# 9.23 CTRL9_XL (18h)

Control register 9 (r/w) 


Table 69. CTRL9_XL register


<table><tr><td>DEN_X</td><td>DEN_Y</td><td>DEN_Z</td><td>DEN_XL_G</td><td>DEN_XL_EN</td><td>DEN_LH</td><td>I3C_disable</td><td>0(1)</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 70. CTRL9_XL register description


<table><tr><td>DEN_X</td><td>DEN value stored in LSB of X-axis. Default value: 1(0: DEN not stored in X-axis LSB; 1: DEN stored in X-axis LSB)</td></tr><tr><td>DEN_Y</td><td>DEN value stored in LSB of Y-axis. Default value: 1(0: DEN not stored in Y-axis LSB; 1: DEN stored in Y-axis LSB)</td></tr><tr><td>DEN_Z</td><td>DEN value stored in LSB of Z-axis. Default value: 1(0: DEN not stored in Z-axis LSB; 1: DEN stored in Z-axis LSB)</td></tr><tr><td>DEN_XL_G</td><td>DEN stamping sensor selection. Default value: 0(0: DEN pin info stamped in the gyroscope axis selected by bits [7:5];1: DEN pin info stamped in the accelerometer axis selected by bits [7:5])</td></tr><tr><td>DEN_XL_EN</td><td>Extends DEN functionality to accelerometer sensor. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>DEN_LH</td><td>DEN active level configuration. Default value: 0(0: active low; 1: active high)</td></tr><tr><td>I3C_disable</td><td>Disables MIPI I3CSMcommunication protocol(1)(0: SPI, I2C, MIPI I3CSMinterfaces enabled (default);1: MIPI I3CSMinterface disabled)</td></tr></table>


1. It is recommended to set this bit to '1' during the initial device configuration phase, when the I3C interface is not used. 


# 9.24 CTRL10_C (19h)

Control register 10 (r/w) 


Table 71. CTRL10_C register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>TIMESTAMP_EN</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 72. CTRL10_C register description


<table><tr><td>TIMESTAMP_EN</td><td>Enables timestamp counter. Default value: 0(0: disabled; 1: enabled)The counter is readable in TIMESTAMP0 (40h), TIMESTAMP1 (41h), TIMESTAMP2 (42h), and TIMESTAMP3 (43h).</td></tr></table>

# 9.25 ALL_INT_SRC (1A)

Source register for all interrupts (r) 


Table 73. ALL_INT_SRC register


<table><tr><td>TIMESTAMP_ENDCOUNT</td><td>0</td><td>SLEEP_CHANGE_IA</td><td>D6D_IA</td><td>DOUBLE_TAP</td><td>SINGLE_TAP</td><td>WU_IA</td><td>FF_IA</td></tr></table>


Table 74. ALL_INT_SRC register description


<table><tr><td>TIMESTAMP_ENDCOUNT</td><td>Alerts timestamp overflow within 6.4 ms</td></tr><tr><td>SLEEP_CHANGE_IA</td><td>Detects change event in activity/inactivity status. Default value: 0(0: change status not detected; 1: change status detected)</td></tr><tr><td>D6D_IA</td><td>Interrupt active for change in position of portrait, landscape, face-up, face-down. Default value: 0(0: change in position not detected; 1: change in position detected)</td></tr><tr><td>DOUBLE_TAP</td><td>Double-tap event status. Default value: 0(0:event not detected, 1: event detected)</td></tr><tr><td>SINGLE_TAP</td><td>Single-tap event status. Default value:0(0: event not detected, 1: event detected)</td></tr><tr><td>WU_IA</td><td>Wake-up event status. Default value: 0(0: event not detected, 1: event detected)</td></tr><tr><td>FF_IA</td><td>Free-fall event status. Default value: 0(0: event not detected, 1: event detected)</td></tr></table>

# 9.26 WAKE_UP_SRC (1Bh)

Wake-up interrupt source register (r) 


Table 75. WAKE_UP_SRC register


<table><tr><td>0</td><td>SLEEP_CHANGE_IA</td><td>FF_IA</td><td>SLEEP_STATE</td><td>WU_IA</td><td>X_WU</td><td>Y_WU</td><td>Z_WU</td></tr></table>


Table 76. WAKE_UP_SRC register description


<table><tr><td>SLEEP_CHANGE_IA</td><td>Detects change event in activity/inactivity status. Default value: 0(0: change status not detected; 1: change status detected)</td></tr><tr><td>FF_IA</td><td>Free-fall event detection status. Default: 0(0: free-fall event not detected; 1: free-fall event detected)</td></tr><tr><td>SLEEP_STATE</td><td>Sleep event status. Default value: 0(0: sleep event not detected; 1: sleep event detected)</td></tr><tr><td>WU_IA</td><td>Wakeup event detection status. Default value: 0(0: wakeup event not detected; 1: wakeup event detected.)</td></tr><tr><td>X_WU</td><td>Wakeup event detection status on X-axis. Default value: 0(0: wakeup event on X-axis not detected; 1: wakeup event on X-axis detected)</td></tr><tr><td>Y_WU</td><td>Wakeup event detection status on Y-axis. Default value: 0(0: wakeup event on Y-axis not detected; 1: wakeup event on Y-axis detected)</td></tr><tr><td>Z_WU</td><td>Wakeup event detection status on Z-axis. Default value: 0(0: wakeup event on Z-axis not detected; 1: wakeup event on Z-axis detected)</td></tr></table>

# 9.27 TAP_SRC (1Ch)

Tap source register (r) 


Table 77. TAP_SRC register


<table><tr><td>0</td><td>TAP_IA</td><td>SINGLE_TAP</td><td>DOUBLE_TAP</td><td>TAP_SIGN</td><td>X_TAP</td><td>Y_TAP</td><td>Z_TAP</td></tr></table>


Table 78. TAP_SRC register description


<table><tr><td>TAP_IA</td><td>Tap event detection status. Default: 0(0: tap event not detected; 1: tap event detected)</td></tr><tr><td>SINGLE_TAP</td><td>Single-tap event status. Default value: 0(0: single tap event not detected; 1: single tap event detected)</td></tr><tr><td>DOUBLE_TAP</td><td>Double-tap event detection status. Default value: 0(0: double-tap event not detected; 1: double-tap event detected.)</td></tr><tr><td>TAP_SIGN</td><td>Sign of acceleration detected by tap event. Default: 0(0: positive sign of acceleration detected by tap event;1: negative sign of acceleration detected by tap event)</td></tr><tr><td>X_TAP</td><td>Tap event detection status on X-axis. Default value: 0(0: tap event on X-axis not detected; 1: tap event on X-axis detected)</td></tr><tr><td>Y_TAP</td><td>Tap event detection status on Y-axis. Default value: 0(0: tap event on Y-axis not detected; 1: tap event on Y-axis detected)</td></tr><tr><td>Z_TAP</td><td>Tap event detection status on Z-axis. Default value: 0(0: tap event on Z-axis not detected; 1: tap event on Z-axis detected)</td></tr></table>

# 9.28 DRD_SRC (1Dh)

Portrait, landscape, face-up and face-down source register (r) 


Table 79. D6D_SRC register


<table><tr><td>DEN_DRDY</td><td>D6D_IA</td><td>ZH</td><td>ZL</td><td>YH</td><td>YL</td><td>XH</td><td>XL</td></tr></table>


Table 80. D6D_SRC register description


<table><tr><td>DEN_DRDY</td><td>DEN data-ready signal. It is set high when data output is related to the data coming from a DEN active condition.<eq>^{(1)}</eq></td></tr><tr><td>D6D_IA</td><td>Interrupt active for change position portrait, landscape, face-up, face-down. Default value: 0(0: change position not detected; 1: change position detected)</td></tr><tr><td>ZH</td><td>Z-axis high event (over threshold). Default value: 0(0: event not detected; 1: event (over threshold) detected)</td></tr><tr><td>ZL</td><td>Z-axis low event (under threshold). Default value: 0(0: event not detected; 1: event (under threshold) detected)</td></tr><tr><td>YH</td><td>Y-axis high event (over threshold). Default value: 0(0: event not detected; 1: event (over-threshold) detected)</td></tr><tr><td>YL</td><td>Y-axis low event (under threshold). Default value: 0(0: event not detected; 1: event (under threshold) detected)</td></tr><tr><td>XH</td><td>X-axis high event (over threshold). Default value: 0(0: event not detected; 1: event (over threshold) detected)</td></tr><tr><td>XL</td><td>X-axis low event (under threshold). Default value: 0(0: event not detected; 1: event (under threshold) detected)</td></tr></table>


1. The DEN data-ready signal can be latched or pulsed depending on the value of the dataready_pulsed bit of the COUNTER_BDR_REG1 (0Bh) register. 


# 9.29 STATUS_REG (1Eh) / STATUS_SPIAux (1Eh)

The STATUS_REG register is read by the primary interface SPI/I²C & MIPI I3CSM (r) 


Table 81. STATUS_REG register


<table><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>TDA</td><td>GDA</td><td>XLDA</td></tr></table>


Table 82. STATUS_REG register description


<table><tr><td>TDA</td><td>Temperature new data available. Default: 0(0: no set of data is available at temperature sensor output;1: a new set of data is available at temperature sensor output)</td></tr><tr><td>GDA</td><td>Gyroscope new data available. Default value: 0(0: no set of data available at gyroscope output;1: a new set of data is available at gyroscope output)</td></tr><tr><td>XLDA</td><td>Accelerometer new data available. Default value: 0(0: no set of data available at accelerometer output;1: a new set of data is available at accelerometer output)</td></tr></table>

The STATUS_SPIAux register is read by the auxiliary SPI. 


Table 83. STATUS_SPIAux register


<table><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>GYRO SETTLING</td><td>GDA</td><td>XLDA</td></tr></table>


Table 84. STATUS_SPIAux register description


<table><tr><td>GYRO_SETTLING</td><td>High when the gyroscope output is in the settling phase</td></tr><tr><td>GDA</td><td>Gyroscope data available (reset when one of the high parts of the output data is read)</td></tr><tr><td>XLDA</td><td>Accelerometer data available (reset when one of the high parts of the output data is read)</td></tr></table>

# 9.30 OUT_TEMP_L (20h), OUT_TEMP_H (21h)

Temperature data output register (r). L and H registers together express a 16-bit word in two’s complement. 


Table 85. OUT_TEMP_L register


<table><tr><td>Temp7</td><td>Temp6</td><td>Temp5</td><td>Temp4</td><td>Temp3</td><td>Temp2</td><td>Temp1</td><td>Temp0</td></tr></table>


Table 86. OUT_TEMP_H register


<table><tr><td>Temp15</td><td>Temp14</td><td>Temp13</td><td>Temp12</td><td>Temp11</td><td>Temp10</td><td>Temp9</td><td>Temp8</td></tr></table>


Table 87. OUT_TEMP register description


<table><tr><td>Temp[15:0]</td><td>Temperature sensor output dataThe value is expressed as two’s complement sign extended on the MSB.</td></tr></table>

# 9.31 OUTX_L_G (22h) and OUTX_H_G (23h)

Angular rate sensor pitch axis (X) angular rate output register (r). The value is expressed as a 16-bit word in two’s complement. 

If this register is read by the primary interface, data are according to the full scale and ODR settings (CTRL2_G (11h)) of gyro user interface. 

If this register is read by the auxiliary interface, data are according to the full scale and ODR (6.66 kHz) settings of the OIS gyro. 


Table 88. OUTX_L_G register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 89. OUTX_H_G register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 90. OUTX_H_G register description


<table><tr><td>D[15:0]</td><td>Pitch axis (X) angular rate valueD[15:0] expressed in two’s complement and its value depends on the interface used:SPI1/I2C/MIPI I3CSM: Gyro UI chain pitch axis outputSPI2: Gyro OIS chain pitch axis output</td></tr></table>

# 9.32 OUTY_L_G (24h) and OUTY_H_G (25h)

Angular rate sensor roll axis (Y) angular rate output register (r). The value is expressed as a 16-bit word in two’s complement. 

If this register is read by the primary interface, data are according to the full scale and ODR settings (CTRL2_G (11h)) of the gyro user interface. 

If this register is read by the auxiliary interface, data are according to the full scale and ODR (6.66 kHz) settings of the OIS gyro. 


Table 91. OUTY_L_G register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 92. OUTY_H_G register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 93. OUTY_H_G register description


<table><tr><td>D[15:0]</td><td>Roll axis (Y) angular rate valueD[15:0] expressed in two’s complement and its value depends on the interface used:SPI1/I2C/MIPI I3CSM: Gyro UI chain roll axis outputSPI2: Gyro OIS chain roll axis output</td></tr></table>

# 9.33 OUTZ_L_G (26h) and OUTZ_H_G (27h)

Angular rate sensor yaw axis (Z) angular rate output register (r). The value is expressed as a 16-bit word in two’s complement. 

If this register is read by the primary interface, data are according to the full scale and ODR settings (CTRL2_G (11h)) of the gyro user interface. 

If this register is read by the auxiliary interface, data are according to the full scale and ODR (6.66 kHz) settings of the OIS gyro. 


Table 94. OUTZ_L_G register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 95. OUTZ_H_G register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 96. OUTZ_H_G register description


<table><tr><td>D[15:0]</td><td>Yaw axis (Z) angular rate valueD[15:0] expressed in two’s complement and its value depends on the interface used:SPI1/I2C/MIPI I3CSM: Gyro UI chain yaw axis outputSPI2: Gyro OIS chain yaw axis output</td></tr></table>

# 9.34 OUTX_L_A (28h) and OUTX_H_A (29h)

Linear acceleration sensor X-axis output register (r). The value is expressed as a 16-bit word in two’s complement. 

If this register is read by the primary interface, data are according to the full-scale and ODR settings (CTRL1_XL (10h)) of the accelerometer user interface. 

If this register is read by the auxiliary interface, data are according to the full-scale and ODR (6.66 kHz) settings of the OIS (CTRL3_OIS (72h)). 


Table 97. OUTX_L_A register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 98. OUTX_H_A register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 99. OUTX_H_A register description


<table><tr><td>D[15:0]</td><td>X-axis linear acceleration value.D[15:0] expressed in two’s complement and its value depends on the interface used:SPI1/I2C/MIPI I3CSM: Accelerometer UI chain X-axis outputSPI2: Accelerometer OIS chain X-axis output</td></tr></table>

# 9.35 OUTY_L_A (2Ah) and OUTY_H_A (2Bh)

Linear acceleration sensor Y-axis output register (r). The value is expressed as a 16-bit word in two’s complement. 

If this register is read by the primary interface, data are according to the full-scale and ODR settings (CTRL1_XL (10h)) of the accelerometer user interface. 

If this register is read by the auxiliary interface, data are according to the full-scale and ODR (6.66 kHz) settings of the OIS (CTRL3_OIS (72h)). 


Table 100. OUTY_L_A register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 101. OUTY_H_A register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 102. OUTY_H_A register description


<table><tr><td>D[15:0]</td><td>Y-axis linear acceleration valueD[15:0] expressed in two’s complement and its value depends on the interface used:SPI1/I2C/MIPI I3CSM: Accelerometer UI chain Y-axis outputSPI2: Accelerometer OIS chain Y-axis output</td></tr></table>

# 9.36 OUTZ_L_A (2Ch) and OUTZ_H_A (2Dh)

Linear acceleration sensor Z-axis output register (r). The value is expressed as a 16-bit word in two’s complement. 

If this register is read by the primary interface, data are according to the full-scale and ODR settings (CTRL1_XL (10h)) of the accelerometer user interface. 

If this register is read by the auxiliary interface, data are according to the full-scale and ODR (6.66 kHz) settings of the OIS (CTRL3_OIS (72h)). 


Table 103. OUTZ_L_A register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 104. OUTZ_H_A register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 105. OUTZ_H_A register description


<table><tr><td>D[15:0]</td><td>Z-axis linear acceleration valueD[15:0] expressed in two’s complement and its value depends on the interface used:SPI1/I2C/MIPI I3CSM: Accelerometer UI chain Z-axis outputSPI2: Accelerometer OIS chain Z-axis output</td></tr></table>

# 9.37 EMB_FUNC_STATUS_MAINPAGE (35h)

Embedded function status register (r) 


Table 106. EMB_FUNC_STATUS_MAINPAGE register


<table><tr><td>IS_FSM_LC</td><td>0</td><td>IS_SIGMOT</td><td>IS_TILT</td><td>IS_STEP_DET</td><td>0</td><td>0</td><td>0</td></tr></table>


Table 107. EMB_FUNC_STATUS_MAINPAGE register description


<table><tr><td>IS_FSM_LC</td><td>Interrupt status bit for FSM long counter timeout interrupt event.(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_SIGMOT</td><td>Interrupt status bit for significant motion detection(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_TILT</td><td>Interrupt status bit for tilt detection(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_STEP_DET</td><td>Interrupt status bit for step detection(1: interrupt detected; 0: no interrupt)</td></tr></table>

# 9.38 FSM_STATUS_A_MAINPAGE (36h)

Finite State Machine status register (r) 


Table 108. FSM_STATUS_A_MAINPAGE register


<table><tr><td>IS_FSM8</td><td>IS_FSM7</td><td>IS_FSM6</td><td>IS_FSM5</td><td>IS_FSM4</td><td>IS_FSM3</td><td>IS_FSM2</td><td>IS_FSM1</td></tr></table>


Table 109. FSM_STATUS_A_MAINPAGE register description


<table><tr><td>IS_FSM8</td><td>Interrupt status bit for FSM8 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM7</td><td>Interrupt status bit for FSM7 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM6</td><td>Interrupt status bit for FSM6 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM5</td><td>Interrupt status bit for FSM5 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM4</td><td>Interrupt status bit for FSM4 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM3</td><td>Interrupt status bit for FSM3 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM2</td><td>Interrupt status bit for FSM2 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM1</td><td>Interrupt status bit for FSM1 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr></table>

# 9.39 FSM_STATUS_B_MAINPAGE (37h)

Finite State Machine status register (r) 


Table 110. FSM_STATUS_B_MAINPAGE register


<table><tr><td>IS_FSM16</td><td>IS_FSM15</td><td>IS_FSM14</td><td>IS_FSM13</td><td>IS_FSM12</td><td>IS_FSM11</td><td>IS_FSM10</td><td>IS_FSM9</td></tr></table>


Table 111. FSM_STATUS_B_MAINPAGE register description


<table><tr><td>IS_FSM16</td><td>Interrupt status bit for FSM16 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM15</td><td>Interrupt status bit for FSM15 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM14</td><td>Interrupt status bit for FSM14 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM13</td><td>Interrupt status bit for FSM13 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM12</td><td>Interrupt status bit for FSM12 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM11</td><td>Interrupt status bit for FSM11 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM10</td><td>Interrupt status bit for FSM10 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM9</td><td>Interrupt status bit for FSM9 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr></table>

# 9.40 STATUS_MASTER_MAINPAGE (39h)

Sensor hub source register (r) 


Table 112. STATUS_MASTER_MAINPAGE register


<table><tr><td>WR_ONCE_DONE</td><td>SLAVE3_NACK</td><td>SLAVE2_NACK</td><td>SLAVE1_NACK</td><td>SLAVE0_NACK</td><td>0</td><td>0</td><td>SENS_HUB_ENDOP</td></tr></table>


Table 113. STATUS_MASTER_MAINPAGE register description


<table><tr><td>WR_ONCE_DONE</td><td>When the bit WRITE_ONCE in MASTER_CONFIG (14h) is configured as 1, this bit is set to 1 when the write operation on slave 0 has been performed and completed. Default value: 0</td></tr><tr><td>SLAVE3_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 3 communication. Default value: 0</td></tr><tr><td>SLAVE2_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 2 communication. Default value: 0</td></tr><tr><td>SLAVE1_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 1 communication. Default value: 0</td></tr><tr><td>SLAVE0_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 0 communication. Default value: 0</td></tr><tr><td>SENS_HUB_ENDOP</td><td>Sensor hub communication status. Default value: 0(0: sensor hub communication not concluded;1: sensor hub communication concluded)</td></tr></table>

# 9.41 FIFO_STATUS1 (3Ah)

FIFO status register 1 (r) 


Table 114. FIFO_STATUS1 register


<table><tr><td>DIFF_FIFO_7</td><td>DIFF_FIFO_6</td><td>DIFF_FIFO_5</td><td>DIFF_FIFO_4</td><td>DIFF_FIFO_3</td><td>DIFF_FIFO_2</td><td>DIFF_FIFO_1</td><td>DIFF_FIFO_0</td></tr></table>


Table 115. FIFO_STATUS1 register description


<table><tr><td>DIFF_FIFO_[7:0]</td><td>Number of unread sensor data (TAG + 6 bytes) stored in FIFOIn conjunction with DIFF_FIFO[9:8] inFIFO_STATUS2(3Bh).</td></tr></table>

# 9.42 FIFO_STATUS2 (3Bh)

FIFO status register 2 (r) 


Table 116. FIFO_STATUS2 register


<table><tr><td>FIFO_WTM_IA</td><td>FIFO_OVR_IA</td><td>FIFO_FULL_IA</td><td>COUNTER_BDR_IA</td><td>FIFO_OVR_LATCHED</td><td>0</td><td>DIFF_FIFO_9</td><td>DIFF_FIFO_8</td></tr></table>


Table 117. FIFO_STATUS2 register description


<table><tr><td>FIFO_WTM_IA</td><td>FIFO watermark status. Default value: 0(0: FIFO filling is lower than WTM;1: FIFO filling is equal to or greater than WTM)Watermark is set through bits WTM[8:0] inFIFO_CTRL1 (07h) andFIFO_CTRL2 (08h).</td></tr><tr><td>FIFO_OVR_IA</td><td>FIFO overrun status. Default value: 0(0: FIFO is not completely filled; 1: FIFO is completely filled)</td></tr><tr><td>FIFO_FULL_IA</td><td>Smart FIFO full status. Default value: 0(0: FIFO is not full; 1: FIFO will be full at the next ODR)</td></tr><tr><td>COUNTER_BDR_IA</td><td>Counter BDR reaches the CNT_BDR_TH_[10:0] threshold set inCOUNTER_BDR_REG1 (0Bh) andCOUNTER_BDR_REG2 (0Ch). Default value: 0This bit is reset when these registers are read.</td></tr><tr><td>FIFO_OVR_LATCHED</td><td>Latched FIFO overrun status. Default value: 0This bit is reset when this register is read.</td></tr><tr><td>DIFF_FIFO_[9:8]</td><td>Number of unread sensor data (TAG + 6 bytes) stored in FIFO. Default value: 00In conjunction with DIFF_FIFO[7:0] inFIFO_STATUS1 (3Ah).</td></tr></table>

# 9.43

# TIMESTAMP0 (40h), TIMESTAMP1 (41h), TIMESTAMP2 (42h), and TIMESTAMP3 (43h)

Timestamp first data output register (r). The value is expressed as a 32-bit word and the bit resolution is 25 µs. 


Table 118. TIMESTAMP3 register


<table><tr><td>D31</td><td>D30</td><td>D29</td><td>D28</td><td>D27</td><td>D26</td><td>D25</td><td>D24</td></tr></table>


Table 119. TIMESTAMP2 register


<table><tr><td>D23</td><td>D22</td><td>D21</td><td>D20</td><td>D19</td><td>D18</td><td>D17</td><td>D16</td></tr></table>


Table 120. TIMESTAMP1 register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 121. TIMESTAMP0 register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>

<table><tr><td>D[31:0]</td><td>Timestamp output registers: 1LSB = 25 μs</td></tr></table>

The formula below can be used to calculate a better estimation of the actual timestamp resolution: 

TS_Res = 1 / (40000 + (0.0015 * INTERNAL_FREQ_FINE * 40000)) 

where INTERNAL_FREQ_FINE is the content of INTERNAL_FREQ_FINE (63h). 

# 9.44 TAP_CFG0 (56h)

Activity/inactivity functions, configuration of filtering, and tap recognition functions (r/w) 


Table 122. TAP_CFG0 register


<table><tr><td><eq>0^{(1)}</eq></td><td>INT_CLR_ON_READ</td><td>SLEEP_STATUS_ON_INT</td><td>SLOPE_FDS</td><td>TAP_X_EN</td><td>TAP_Y_EN</td><td>TAP_Z_EN</td><td>LIR</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 123. TAP_CFG0 register description


<table><tr><td>INT_CLR_ON_READ</td><td>This bit allows immediately clearing the latched interrupts of an event detection upon the read of the corresponding status register. It must be set to 1 together with LIR. Default value: 0(0: latched interrupt signal cleared at the end of the ODR period;1: latched interrupt signal immediately cleared)</td></tr><tr><td>SLEEP_STATUS_ON_INT</td><td>Activity/inactivity interrupt mode configuration.If INT1_SLEEP_CHANGE or INT2_SLEEP_CHANGE bits are enabled, drives the sleep status or sleep change on the INT pins. Default value: 0(0: sleep change notification on INT pins; 1: sleep status reported on INT pins)</td></tr><tr><td>SLOPE_FDS</td><td>HPF or SLOPE filter selection on wake-up and Activity/Inactivity functions. Default value: 0(0: SLOPE filter applied; 1: HPF applied)</td></tr><tr><td>TAP_X_EN</td><td>Enable X direction in tap recognition. Default value: 0(0: X direction disabled; 1: X direction enabled)</td></tr><tr><td>TAP_Y_EN</td><td>Enable Y direction in tap recognition. Default value: 0(0: Y direction disabled; 1: Y direction enabled)</td></tr><tr><td>TAP_Z_EN</td><td>Enable Z direction in tap recognition. Default value: 0(0: Z direction disabled; 1: Z direction enabled)</td></tr><tr><td>LIR</td><td>Latched Interrupt. Default value: 0(0: interrupt request not latched; 1: interrupt request latched)</td></tr></table>

# 9.45 TAP_CFG1 (57h)

Tap configuration register (r/w) 


Table 124. TAP_CFG1 register


<table><tr><td>TAP_PRIORITY_2</td><td>TAP_PRIORITY_1</td><td>TAP_PRIORITY_0</td><td>TAP_THS_X_4</td><td>TAP_THS_X_3</td><td>TAP_THS_X_2</td><td>TAP_THS_X_1</td><td>TAP_THS_X_0</td></tr></table>


Table 125. TAP_CFG1 register description


<table><tr><td>TAP_PRIORITY_[2:0]</td><td>Selection of axis priority for TAP detection (see Table 126)</td></tr><tr><td>TAP_THS_X_[4:0]</td><td>X-axis tap recognition threshold. Default value: 01 LSB = FS_XL / (<eq>2^{5}</eq>)</td></tr></table>


Table 126. TAP priority decoding


<table><tr><td>TAP_PRIORITY_[2:0]</td><td>Max. priority</td><td>Mid. priority</td><td>Min. priority</td></tr><tr><td>000</td><td>X</td><td>Y</td><td>Z</td></tr><tr><td>001</td><td>Y</td><td>X</td><td>Z</td></tr><tr><td>010</td><td>X</td><td>Z</td><td>Y</td></tr><tr><td>011</td><td>Z</td><td>Y</td><td>X</td></tr><tr><td>100</td><td>X</td><td>Y</td><td>Z</td></tr><tr><td>101</td><td>Y</td><td>Z</td><td>X</td></tr><tr><td>110</td><td>Z</td><td>X</td><td>Y</td></tr><tr><td>111</td><td>Z</td><td>Y</td><td>X</td></tr></table>

# 9.46 TAP_CFG2 (58h)

Enables interrupt and inactivity functions, and tap recognition functions (r/w) 


Table 127. TAP_CFG2 register


<table><tr><td>INTERRUPTS_ENABLE</td><td>INACT_EN1</td><td>INACT_EN0</td><td>TAP_THS_Y_4</td><td>TAP_THS_Y_3</td><td>TAP_THS_Y_2</td><td>TAP_THS_Y_1</td><td>TAP_THS_Y_0</td></tr></table>


Table 128. TAP_CFG2 register description


<table><tr><td>INTERRUPTS_ENABLE</td><td>Enable basic interrupts (6D/4D, free-fall, wake-up, tap, inactivity). Default value: 0(0: interrupt disabled; 1: interrupt enabled)</td></tr><tr><td>INACT_EN[1:0]</td><td>Enable activity/inactivity (sleep) function. Default value: 00(00: stationary/motion-only interrupts generated, XL and gyro do not change;01: sets accelerometer ODR to 12.5 Hz (low-power mode), gyro does not change;10: sets accelerometer ODR to 12.5 Hz (low-power mode), gyro to sleep mode;11: sets accelerometer ODR to 12.5 Hz (low-power mode), gyro to power-down mode)</td></tr><tr><td>TAP_THS_Y_[4:0]</td><td>Y-axis tap recognition threshold. Default value: 01 LSB = FS_XL / (<eq>2^{5}</eq>)</td></tr></table>

# 9.47 TAP_THS_6D (59h)

Portrait/landscape position and tap function threshold register (r/w) 


Table 129. TAP_THS_6D register


<table><tr><td>D4D_EN</td><td>SIXD_THS1</td><td>SIXD_THS0</td><td>TAP_THS_Z_4</td><td>TAP_THS_Z_3</td><td>TAP_THS_Z_2</td><td>TAP_THS_Z_1</td><td>TAP_THS_Z_0</td></tr></table>


Table 130. TAP_THS_6D register description


<table><tr><td>D4D_EN</td><td>Enables detection of 4D orientation. Z-axis position detection is disabled. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>SIXD_THS[1:0]</td><td>Threshold for 4D/6D function:(00: 80 degrees (default);01: 70 degrees;10: 60 degrees;11: 50 degrees)</td></tr><tr><td>TAP_THS_Z_[4:0]</td><td>Z-axis recognition threshold. Default value: 01 LSB = FS_XL / (<eq>2^{5}</eq>)</td></tr></table>

# 9.48 INT_DUR2 (5Ah)

Tap recognition function setting register (r/w) 


Table 131. INT_DUR2 register


<table><tr><td>DUR3</td><td>DUR2</td><td>DUR1</td><td>DUR0</td><td>QUIET1</td><td>QUIET0</td><td>SHOCK1</td><td>SHOCK0</td></tr></table>


Table 132. INT_DUR2 register description


<table><tr><td>DUR[3:0]</td><td>Duration of maximum time gap for double-tap recognition. Default: 0000When double-tap recognition is enabled, this register expresses the maximum time between two consecutive detected taps to determine a double-tap event. The default value of these bits is 0000b which corresponds to 16/ODR_XL time. If the DUR[3:0] bits are set to a different value, 1LSB corresponds to 32/ODR_XL time.</td></tr><tr><td>QUIET[1:0]</td><td>Expected quiet time after a tap detection. Default value: 00Quiet time is the time after the first detected tap in which there must not be any overthreshold event. The default value of these bits is 00b which corresponds to 2/ODR_XL time. If the QUIET[1:0] bits are set to a different value, 1LSB corresponds to 4/ODR_XL time.</td></tr><tr><td>SHOCK[1:0]</td><td>Maximum duration of overthreshold event. Default value: 00Maximum duration is the maximum time of an overthreshold signal detection to be recognized as a tap event. The default value of these bits is 00b which corresponds to 4/ODR_XL time. If the SHOCK[1:0] bits are set to a different value, 1LSB corresponds to 8/ODR_XL time.</td></tr></table>

# 9.49 WAKE_UP_THS (5Bh)

Single/double-tap selection and wake-up configuration (r/w) 


Table 133. WAKE_UP_THS register


<table><tr><td>SINGLE_DOUBLE_TAP</td><td>USR_OFF_ON_WU</td><td>WK_THS5</td><td>WK_THS4</td><td>WK_THS3</td><td>WK_THS2</td><td>WK_THS1</td><td>WK_THS0</td></tr></table>


Table 134. WAKE_UP_THS register description


<table><tr><td>SINGLE_DOUBLE_TAP</td><td>Single/double-tap event enable. Default: 0(0: only single-tap event enabled;1: both single and double-tap events enabled)</td></tr><tr><td>USR_OFF_ON_WU</td><td>Sends the low-pass filtered data with user offset correction (instead of high-pass filtered data) to the wakeup function.</td></tr><tr><td>WK_THS[5:0]</td><td>Threshold for wakeup: 1 LSB weight depends on WAKE_THS_W in WAKE_UP_DUR (5Ch). Default value: 000000</td></tr></table>

# 9.50 WAKE_UP_DUR (5Ch)

Free-fall, wakeup and sleep mode functions duration setting register (r/w) 


Table 135. WAKE_UP_DUR register


<table><tr><td>FF_DUR5</td><td>WAKE_DUR1</td><td>WAKE_DUR0</td><td>WAKE_THS_W</td><td>SLEEP_DUR3</td><td>SLEEP_DUR2</td><td>SLEEP_DUR1</td><td>SLEEP_DUR0</td></tr></table>


Table 136. WAKE_UP_DUR register description


<table><tr><td>FF_DUR5</td><td>Free fall duration event. Default: 0For the complete configuration of the free-fall duration, refer to FF_DUR[4:0] in FREE_FALL (5Dh) configuration.1 LSB = 1 ODR_time</td></tr><tr><td>WAKE_DUR[1:0]</td><td>Wake up duration event. Default: 001LSB = 1 ODR_time</td></tr><tr><td>WAKE_THS_W</td><td>Weight of 1 LSB of wakeup threshold. Default: 0(0: 1 LSB =FS_XL / (26);1: 1 LSB = FS_XL / (28))</td></tr><tr><td>SLEEP_DUR[3:0]</td><td>Duration to go in sleep mode. Default value: 0000 (this corresponds to 16 ODR)1 LSB = 512 ODR</td></tr></table>

# 9.51 FREE_FALL (5Dh)

Free-fall function duration setting register (r/w) 


Table 137. FREE_FALL register


<table><tr><td>FF_DUR4</td><td>FF_DUR3</td><td>FF_DUR2</td><td>FF_DUR1</td><td>FF_DUR0</td><td>FF_THS2</td><td>FF_THS1</td><td>FF_THS0</td></tr></table>


Table 138. FREE_FALL register description


<table><tr><td>FF_DUR[4:0]</td><td>Free-fall duration event. Default: 0For the complete configuration of the free fall duration, refer to FF_DUR5 in WAKE_UP_DUR (5Ch) configuration.</td></tr><tr><td>FF_THS[2:0]</td><td>Free-fall threshold setting:(000: 156 mg (default);001: 219 mg;010: 250 mg;011: 312 mg;100: 344 mg;101: 406 mg;110: 469 mg;111: 500 mg)</td></tr></table>

# 9.52 MD1_CFG (5Eh)

Functions routing on INT1 register (r/w) 


Table 139. MD1_CFG register


<table><tr><td>INT1_SLEEP_CHANGE</td><td>INT1_SINGLE_TAP</td><td>INT1_WU</td><td>INT1_FF</td><td>INT1_DOUBLE_TAP</td><td>INT1_6D</td><td>INT1_EMB_FUNC</td><td>INT1_SHUB</td></tr></table>


Table 140. MD1_CFG register description


<table><tr><td><eq>INT1\_SLEEP\_CHANGE^{(1)}</eq></td><td>Routing of activity/inactivity recognition event on INT1. Default: 0(0: routing of activity/inactivity event on INT1 disabled;1: routing of activity/inactivity event on INT1 enabled)</td></tr><tr><td><eq>INT1\_SINGLE\_TAP</eq></td><td>Routing of single-tap recognition event on INT1. Default: 0(0: routing of single-tap event on INT1 disabled;1: routing of single-tap event on INT1 enabled)</td></tr><tr><td><eq>INT1\_WU</eq></td><td>Routing of wakeup event on INT1. Default value: 0(0: routing of wakeup event on INT1 disabled;1: routing of wakeup event on INT1 enabled)</td></tr><tr><td><eq>INT1\_FF</eq></td><td>Routing of free-fall event on INT1. Default value: 0(0: routing of free-fall event on INT1 disabled;1: routing of free-fall event on INT1 enabled)</td></tr><tr><td><eq>INT1\_DOUBLE\_TAP</eq></td><td>Routing of tap event on INT1. Default value: 0(0: routing of double-tap event on INT1 disabled;1: routing of double-tap event on INT1 enabled)</td></tr><tr><td><eq>INT1\_6D</eq></td><td>Routing of 6D event on INT1. Default value: 0(0: routing of 6D event on INT1 disabled;1: routing of 6D event on INT1 enabled)</td></tr><tr><td><eq>INT1\_EMB\_FUNC</eq></td><td>Routing of embedded functions event on INT1. Default value: 0(0: routing of embedded functions event on INT1 disabled;1: routing embedded functions event on INT1 enabled)</td></tr><tr><td><eq>INT1\_SHUB</eq></td><td>Routing of sensor hub communication concluded event on INT1. Default value: 0(0: routing of sensor hub communication concluded event on INT1 disabled;1: routing of sensor hub communication concluded event on INT1 enabled)</td></tr></table>


1. Activity/Inactivity interrupt mode (sleep change or sleep status) depends on the SLEEP_STATUS_ON_INT bit in the TAP_CFG0 (56h) register. 


# 9.53 MD2_CFG (5Fh)

Functions routing on INT2 register (r/w) 


Table 141. MD2_CFG register


<table><tr><td>INT2_SLEEP_CHANGE</td><td>INT2_SINGLE_TAP</td><td>INT2_WU</td><td>INT2_FF</td><td>INT2_DOUBLE_TAP</td><td>INT2_6D</td><td>INT2_EMB_FUNC</td><td>INT2_TIMESTAMP</td></tr></table>


Table 142. MD2_CFG register description


<table><tr><td>INT2_SLEEP_CHANGE(1)</td><td>Routing of activity/inactivity recognition event on INT2. Default: 0(0: routing of activity/inactivity event on INT2 disabled;1: routing of activity/inactivity event on INT2 enabled)</td></tr><tr><td>INT2_SINGLE_TAP</td><td>Single-tap recognition routing on INT2. Default: 0(0: routing of single-tap event on INT2 disabled;1: routing of single-tap event on INT2 enabled)</td></tr><tr><td>INT2_WU</td><td>Routing of wakeup event on INT2. Default value: 0(0: routing of wakeup event on INT2 disabled;1: routing of wake-up event on INT2 enabled)</td></tr><tr><td>INT2_FF</td><td>Routing of free-fall event on INT2. Default value: 0(0: routing of free-fall event on INT2 disabled;1: routing of free-fall event on INT2 enabled)</td></tr><tr><td>INT2_DOUBLE_TAP</td><td>Routing of tap event on INT2. Default value: 0(0: routing of double-tap event on INT2 disabled;1: routing of double-tap event on INT2 enabled)</td></tr><tr><td>INT2_6D</td><td>Routing of 6D event on INT2. Default value: 0(0: routing of 6D event on INT2 disabled;1: routing of 6D event on INT2 enabled)</td></tr><tr><td>INT2_EMB_FUNC</td><td>Routing of embedded functions event on INT2. Default value: 0(0: routing of embedded functions event on INT2 disabled;1: routing embedded functions event on INT2 enabled)</td></tr><tr><td>INT2_TIMESTAMP</td><td>Enables routing on INT2 pin of the alert for timestamp overflow within 6.4 ms.</td></tr></table>


1. Activity/Inactivity interrupt mode (sleep change or sleep status) depends on the SLEEP_STATUS_ON_INT bit in the TAP_CFG0 (56h) register. 


# 9.54 S4S_ST_CMD_CODE (60h)

S4S master command register (r/w) 


Table 143. S4S_ST_CMD_CODE register


<table><tr><td>ST_CMD_CODE7</td><td>ST_CMD_CODE6</td><td>ST_CMD_CODE5</td><td>ST_CMD_CODE4</td><td>ST_CMD_CODE3</td><td>ST_CMD_CODE2</td><td>ST_CMD_CODE1</td><td>ST_CMD_CODE0</td></tr></table>


Table 144. S4S_ST_CMD_CODE register description


<table><tr><td>ST_CMD_CODE[7:0]</td><td>Master command code used for S4S. Default value: 0</td></tr></table>

# 9.55 S4S_DT_REG (61h)

S4S DT register (r/w) 


Table 145. S4S_DT_REG register


<table><tr><td>DT7</td><td>DT6</td><td>DT5</td><td>DT4</td><td>DT3</td><td>DT2</td><td>DT1</td><td>DT0</td></tr></table>


Table 146. S4S_DT_REG register description


<table><tr><td>DT[7:0]</td><td>DT used for S4S. Default value: 0</td></tr></table>

# 9.56 I3C_BUS_AVB (62h)

I3C_BUS_AVB register (r/w) 


Table 147. I3C_BUS_AVB register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>I3C_Bus_Avb_Sel1</td><td>I3C_Bus_Avb_Sel0</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>PD_DIS_INT1</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 148. I3C_BUS_AVB register description


<table><tr><td>I3C_Bus_Avb_Sel[1:0]</td><td>These bits are used to select the bus available time when I3C IBI is used.Default value: 00(00: bus available time equal to 50 μsec (default);01: bus available time equal to 2 μsec;10: bus available time equal to 1 msec;11: bus available time equal to 25 msec)</td></tr><tr><td>PD_DIS_INT1</td><td>This bit allows disabling the INT1 pull-down.(0: Pull-down on INT1 enabled (pull-down is effectively connected only when no interrupts are routed to the INT1 pin or when the I3C dynamic address is assigned);1: Pull-down on INT1 disabled (pull-down not connected))</td></tr></table>

# 9.57 INTERNAL_FREQ_FINE (63h)

Internal frequency register (r) 


Table 149. INTERNAL_FREQ_FINE register


<table><tr><td>FREQ_FINE7</td><td>FREQ_FINE6</td><td>FREQ_FINE5</td><td>FREQ_FINE4</td><td>FREQ_FINE3</td><td>FREQ_FINE2</td><td>FREQ_FINE1</td><td>FREQ_FINE0</td></tr></table>


Table 150. INTERNAL_FREQ_FINE register description


<table><tr><td>FREQ_FINE[7:0]</td><td>Difference in percentage of the effective ODR (and timestamp rate) with respect to the typical. Step: 0.15%. 8-bit format, 2&#x27;s complement.</td></tr></table>

The formula below can be used to calculate a better estimation of the actual ODR: 

ODR_Actual = (6667 + ((0.0015 * INTERNAL_FREQ_FINE) * 6667)) / ODR_Coeff 

<table><tr><td>Selected_ODR</td><td>ODR_Coeff</td></tr><tr><td>12.5</td><td>512</td></tr><tr><td>26</td><td>256</td></tr><tr><td>52</td><td>128</td></tr><tr><td>104</td><td>64</td></tr><tr><td>208</td><td>32</td></tr><tr><td>416</td><td>16</td></tr><tr><td>833</td><td>8</td></tr><tr><td>1667</td><td>4</td></tr><tr><td>3333</td><td>2</td></tr><tr><td>6667</td><td>1</td></tr></table>

The Selected_ODR parameter has to be derived from the ODR_XL selection (Table 50. Accelerometer ODR selection) in order to estimate the accelerometer ODR and from the ODR_G selection (Table 53. Gyroscope ODR configuration setting) in order to estimate the gyroscope ODR. 

# 9.58 INT_OIS (6Fh)

OIS interrupt configuration register and accelerometer self-test enable setting. Primary interface for read-only (r); only Aux SPI can write to this register (r/w). 


Table 151. INT_OIS register


<table><tr><td>INT2_DRDY_OIS</td><td>LVL2_OIS</td><td>DEN_LH_OIS</td><td>-</td><td>-</td><td>0(1)</td><td>ST1_XL_OIS</td><td>ST0_XL_OIS</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 152. INT_OIS register description


<table><tr><td>INT2_DRDY_OIS</td><td>Enables OIS chain DRDY on INT2 pin. This setting has priority over all other INT2 settings.</td></tr><tr><td>LVL2_OIS</td><td>Enables level-sensitive latched mode on the OIS chain. Default value: 0</td></tr><tr><td>DEN_LH_OIS</td><td>Indicates polarity of DEN signal on OIS chain(0: DEN pin is active-low;1: DEN pin is active-high)</td></tr><tr><td>ST[1:0]_XL_OIS</td><td>Selects accelerometer self-test – effective only if XL OIS chain is enabled. Default value: 00(00: Normal mode;01: Positive sign self-test;10: Negative sign self-test;11: not allowed)</td></tr></table>

# 9.59 CTRL1_OIS (70h)

OIS configuration register. Primary interface for read-only (r); only Aux SPI can write to this register (r/w). 


Table 153. CTRL1_OIS register


<table><tr><td><eq>0^{(1)}</eq></td><td>LVL1_OIS</td><td>SIM_OIS</td><td>Mode4_EN</td><td>FS1_G_OIS</td><td>FS0_G_OIS</td><td>FS_125_OIS</td><td>OIS_EN_SPI2</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 154. CTRL1_OIS register description


<table><tr><td>LVL1_OIS</td><td>Enables level-sensitive trigger mode on OIS chain. Default value: 0</td></tr><tr><td>SIM_OIS</td><td>SPI2 3- or 4-wire interface. Default value: 0(0: 4-wire SPI2;1: 3-wire SPI2)</td></tr><tr><td>Mode4_EN</td><td>Enables accelerometer OIS chain. OIS outputs are available through SPI2 in registers OUTX_L_A (28h) and OUTX_H_A (29h) - OUTZ_L_A (2Ch) and OUTZ_H_A (2Dh).Note: OIS_EN_SPI2 must be enabled (i.e. set to ‘1’) to enable also XL OIS chain.</td></tr><tr><td>FS[1:0]_G_OIS</td><td>Selects gyroscope OIS chain full-scale(00: ±250 dps;01: ±500 dps;10: ±1000 dps;11: ±2000 dps)</td></tr><tr><td>FS_125_OIS</td><td>Selects gyroscope OIS chain full-scale ±125 dps(0: FS selected through bits FS[1:0]_OIS_G;1: ±125 dps)</td></tr><tr><td>OIS_EN_SPI2</td><td>Enables OIS chain data processing for gyro in Mode 3 and Mode 4 (mode4_en = 1) and accelerometer data in Mode 4 (mode4_en = 1).When the OIS chain is enabled, the OIS outputs are available through the SPI2 in registers OUTX_L_G (22h) and OUTX_H_G (23h) through OUTZ_L_A (2Ch) and OUTZ_H_A (2Dh) and STATUS_REG (1Eh) / STATUS_SPIAux (1Eh), and LPF1 is dedicated to this chain.</td></tr></table>

DEN mode selection can be done using the LVL1_OIS bit of register CTRL1_OIS (70h) and the LVL2_OIS bit of register INT_OIS (6Fh). 

DEN mode on the OIS path is active in the gyroscope only. 


Table 155. DEN mode selection


<table><tr><td>LVL1_OIS, LVL2_OIS</td><td>DEN mode</td></tr><tr><td>10</td><td>Level-sensitive trigger mode is selected</td></tr><tr><td>11</td><td>Level-sensitive latched mode is selected</td></tr></table>

# 9.60 CTRL2_OIS (71h)

OIS configuration register. Primary interface for read-only (r); only Aux SPI can write to this register (r/w). 


Table 156. CTRL2_OIS register


<table><tr><td>-</td><td>-</td><td>HPM1_OIS</td><td>HPM0_OIS</td><td><eq>0^{(1)}</eq></td><td>FTYPE_1_OIS</td><td>FTYPE_0_OIS</td><td>HP_EN_OIS</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 157. CTRL2_OIS register description


<table><tr><td>HPM[1:0]_OIS</td><td>Selects gyroscope OIS chain digital high-pass filter cutoff. Default value: 00(00: 16 mHz;01: 65 mHz;10: 260 mHz;11: 1.04 Hz)</td></tr><tr><td>FTYPE_[1:0]_OIS</td><td>Selects gyroscope digital LPF1 filter bandwidth. Table 158 shows cutoff and phase values obtained with all configurations.</td></tr><tr><td>HP_EN_OIS</td><td>Enables gyroscope OIS chain digital high-pass filter.</td></tr></table>


Table 158. Gyroscope OIS chain digital LPF1 filter bandwidth selection


<table><tr><td>ODR [Hz]</td><td>LPF1FTYPE_[1:0]_OIS</td><td>Total BW [Hz](phase delay @20 Hz)</td></tr><tr><td rowspan="4">6.66 kHz</td><td>00</td><td>297 Hz (7°)</td></tr><tr><td>01</td><td>222 Hz (9°)</td></tr><tr><td>10</td><td>154 Hz (12°)</td></tr><tr><td>11</td><td>470 Hz (5°)</td></tr></table>

# 9.61 CTRL3_OIS (72h)

OIS configuration register. Primary interface for read-only (r); only Aux SPI can write to this register (r/w). 


Table 159. CTRL3_OIS register


<table><tr><td>FS1_XL_OIS</td><td>FS0_XL_OIS</td><td>FILTER_XL_CONF_OIS_2</td><td>FILTER_XL_CONF_OIS_1</td><td>FILTER_XL_CONF_OIS_0</td><td>ST1_OIS</td><td>ST0_OIS</td><td>ST_OIS_CLAMPDIS</td></tr></table>


Table 160. CTRL3_OIS register description


<table><tr><td>FS[1:0]_XL_OIS</td><td>Selects accelerometer OIS channel full-scale. Default value: 00.(00: ±2 g; 01: ±16 g; 10: ±4 g; 11: ±8 g)</td></tr><tr><td>FILTER_XL_CONF_OIS_[2:0]</td><td>Selects accelerometer OIS channel bandwidth. See Table 161.</td></tr><tr><td>ST[1:0]_OIS</td><td>Selects gyroscope OIS chain self-test. Default value: 00Table 162 lists the output variation when the self-test is enabled and ST_OIS_CLAMPDIS=&#x27;1&#x27;.(00: Normal mode;01: Positive sign self-test;10: Normal mode;11: Negative sign self-test)</td></tr><tr><td>ST_OIS_CLAMPDIS</td><td>Disables OIS chain clamp(0: All OIS chain outputs = 8000h during self-test;1: OIS chain self-test outputs as shown in Table 162.</td></tr></table>


Table 161. Accelerometer OIS channel bandwidth and phase


<table><tr><td>FILTER_XL_CONF_OIS[2:0]</td><td>Typ. overall bandwidth [Hz]</td><td>Typ. overall phase [°]</td></tr><tr><td>000</td><td>631</td><td>-4.20 @ 20 Hz</td></tr><tr><td>001</td><td>295</td><td>-6.35 @ 20 Hz</td></tr><tr><td>010</td><td>140</td><td>-10.6 @ 20 Hz</td></tr><tr><td>011</td><td>68.2</td><td>-18.9 @ 20 Hz</td></tr><tr><td>100</td><td>33.6</td><td>-17.8 @ 10 Hz</td></tr><tr><td>101</td><td>16.7</td><td>-32.2 @ 10 Hz</td></tr><tr><td>110</td><td>8.3</td><td>-26.2 @ 4 Hz</td></tr><tr><td>111</td><td>4.14</td><td>-26.0 @ 2 Hz</td></tr></table>


Table 162. Self-test nominal output variation


<table><tr><td>Full scale</td><td>Output variation [dps]</td></tr><tr><td>±2000</td><td>±400</td></tr><tr><td>±1000</td><td>±200</td></tr><tr><td>±500</td><td>±100</td></tr><tr><td>±250</td><td>±50</td></tr><tr><td>±125</td><td>±25</td></tr></table>

# 9.62 X_OFS_USR (73h)

Accelerometer X-axis user offset correction (r/w). The offset value set in the X_OFS_USR offset register is internally subtracted from the acceleration value measured on the X-axis. 


Table 163. X_OFS_USR register


<table><tr><td>X_OFS_USR_7</td><td>X_OFS_USR_6</td><td>X_OFS_USR_5</td><td>X_OFS_USR_4</td><td>X_OFS_USR_3</td><td>X_OFS_USR_2</td><td>X_OFS_USR_1</td><td>X_OFS_USR_0</td></tr></table>


Table 164. X_OFS_USR register description


<table><tr><td>X_OFS_USR_[7:0]</td><td>Accelerometer X-axis user offset correction expressed in two&#x27;s complement, weight depends on USR_OFF_W in CTRL6_C (15h). The value must be in the range [-127 127].</td></tr></table>

# 9.63 Y_OFS_USR (74h)

Accelerometer Y-axis user offset correction (r/w). The offset value set in the Y_OFS_USR offset register is internally subtracted from the acceleration value measured on the Y-axis. 


Table 165. Y_OFS_USR register


<table><tr><td>Y_OFS_USR_7</td><td>Y_OFS_USR_6</td><td>Y_OFS_USR_5</td><td>Y_OFS_USR_4</td><td>Y_OFS_USR_3</td><td>Y_OFS_USR_2</td><td>Y_OFS_USR_1</td><td>Y_OFS_USR_0</td></tr></table>

<table><tr><td>Y_OFS_USR_[7:0]</td><td>Accelerometer Y-axis user offset calibration expressed in 2&#x27;s complement, weight depends on USR_OFF_W in CTRL6_C (15h). The value must be in the range [-127, +127].</td></tr></table>

# 9.64 Z_OFS_USR (75h)

Accelerometer Z-axis user offset correction (r/w). The offset value set in the Z_OFS_USR offset register is internally subtracted from the acceleration value measured on the Z-axis. 


Table 166. Z_OFS_USR register


<table><tr><td>Z_OFS_USR_7</td><td>Z_OFS_USR_6</td><td>Z_OFS_USR_5</td><td>Z_OFS_USR_4</td><td>Z_OFS_USR_3</td><td>Z_OFS_USR_2</td><td>Z_OFS_USR_1</td><td>Z_OFS_USR_0</td></tr></table>


Table 167. Z_OFS_USR register description


<table><tr><td>Z_OFS_USR_[7:0]</td><td>Accelerometer Z-axis user offset calibration expressed in 2&#x27;s complement, weight depends on USR_OFF_W in CTRL6_C (15h). The value must be in the range [-127, +127].</td></tr></table>

# 9.65 FIFO_DATA_OUT_TAG (78h)

FIFO tag register (r) 


Table 168. FIFO_DATA_OUT_TAG register


<table><tr><td>TAG_SENSOR_4</td><td>TAG_SENSOR_3</td><td>TAG_SENSOR_2</td><td>TAG_SENSOR_1</td><td>TAG_SENSOR_0</td><td>TAG_CNT_1</td><td>TAG_CNT_0</td><td>TAG_PARITY</td></tr></table>


Table 169. FIFO_DATA_OUT_TAG register description


<table><tr><td>TAG_SENSOR_[4:0]</td><td>Identifies the sensor in:FIFO_DATA_OUT_X_L (79h) and FIFO_DATA_OUT_X_H (7Ah), FIFO_DATA_OUT_Y_L (7Bh) andFIFO_DATA_OUT_Y_H (7Ch), and FIFO_DATA_OUT_Z_L (7Dh) and FIFO_DATA_OUT_Z_H (7Eh)For details, refer to Table 170. FIFO tag</td></tr><tr><td>TAG_CNT_[1:0]</td><td>2-bit counter which identifies sensor time slot</td></tr><tr><td>TAG_PARITY</td><td>Parity check of TAG content</td></tr></table>


Table 170. FIFO tag


<table><tr><td>TAG_SENSOR_[4:0]</td><td>Sensor name</td></tr><tr><td>0x01</td><td>Gyroscope NC</td></tr><tr><td>0x02</td><td>Accelerometer NC</td></tr><tr><td>0x03</td><td>Temperature</td></tr><tr><td>0x04</td><td>Timestamp</td></tr><tr><td>0x05</td><td>CFG_Change</td></tr><tr><td>0x06</td><td>Accelerometer NC_T_2</td></tr><tr><td>0x07</td><td>Accelerometer NC_T_1</td></tr><tr><td>0x08</td><td>Accelerometer 2xC</td></tr><tr><td>0x09</td><td>Accelerometer 3xC</td></tr><tr><td>0x0A</td><td>Gyroscope NC_T_2</td></tr><tr><td>0x0B</td><td>Gyroscope NC_T_1</td></tr><tr><td>0x0C</td><td>Gyroscope 2xC</td></tr><tr><td>0x0D</td><td>Gyroscope 3xC</td></tr><tr><td>0x0E</td><td>Sensor Hub Slave 0</td></tr><tr><td>0x0F</td><td>Sensor Hub Slave 1</td></tr><tr><td>0x10</td><td>Sensor Hub Slave 2</td></tr><tr><td>0x11</td><td>Sensor Hub Slave 3</td></tr><tr><td>0x12</td><td>Step Counter</td></tr><tr><td>0x19</td><td>Sensor Hub Nack</td></tr></table>

# 9.66 FIFO_DATA_OUT_X_L (79h) and FIFO_DATA_OUT_X_H (7Ah)

FIFO data output X (r) 


Table 171. FIFO_DATA_OUT_X_H and FIFO_DATA_OUT_X_L registers


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr><tr><td colspan="8"></td></tr><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 172. FIFO_DATA_OUT_X_H and FIFO_DATA_OUT_X_L register description


<table><tr><td>D[15:0]</td><td>FIFO X-axis output</td></tr></table>

# 9.67 FIFO_DATA_OUT_Y_L (7Bh) and FIFO_DATA_OUT_Y_H (7Ch)

FIFO data output Y (r) 


Table 173. FIFO_DATA_OUT_Y_H and FIFO_DATA_OUT_Y_L registers


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 174. FIFO_DATA_OUT_Y_H and FIFO_DATA_OUT_Y_L register description


<table><tr><td>D[15:0]</td><td>FIFO Y-axis output</td></tr></table>

# 9.68 FIFO_DATA_OUT_Z_L (7Dh) and FIFO_DATA_OUT_Z_H (7Eh)

FIFO data output Z (r) 


Table 175. FIFO_DATA_OUT_Z_H and FIFO_DATA_OUT_Z_L registers


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 176. FIFO_DATA_OUT_Z_H and FIFO_DATA_OUT_Z_L register description


<table><tr><td>D[15:0]</td><td>FIFO Z-axis output</td></tr></table>

# 10

# Embedded functions register mapping

The table given below provides a list of the registers for the embedded functions available in the device and the corresponding addresses. Embedded functions registers are accessible when $\mathsf { F U N C \_ C F G \_ E N }$ is set to $" 1 "$ in FUNC_CFG_ACCESS (01h). 


Table 177. Register address map - embedded functions


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>PAGE_SEL</td><td>RW</td><td>02</td><td>00000010</td><td>00000001</td><td></td></tr><tr><td>ADV_PEDO</td><td>RW</td><td>03</td><td>00000011</td><td>00000010</td><td></td></tr><tr><td>EMB_FUNC_EN_A</td><td>RW</td><td>04</td><td>00000100</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_EN_B</td><td>RW</td><td>05</td><td>00000101</td><td>00000000</td><td></td></tr><tr><td>PAGE_ADDRESS</td><td>RW</td><td>08</td><td>00001000</td><td>00000000</td><td></td></tr><tr><td>PAGE_VALUE</td><td>RW</td><td>09</td><td>00001001</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_INT1</td><td>RW</td><td>0A</td><td>00001010</td><td>00000000</td><td></td></tr><tr><td>FSM_INT1_A</td><td>RW</td><td>0B</td><td>00001011</td><td>00000000</td><td></td></tr><tr><td>FSM_INT1_B</td><td>RW</td><td>0C</td><td>00001100</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_INT2</td><td>RW</td><td>0E</td><td>00001110</td><td>00000000</td><td></td></tr><tr><td>FSM_INT2_A</td><td>RW</td><td>0F</td><td>00001111</td><td>01101011</td><td></td></tr><tr><td>FSM_INT2_B</td><td>RW</td><td>10</td><td>00010000</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_STATUS</td><td>R</td><td>12</td><td>00010010</td><td>output</td><td></td></tr><tr><td>FSM_STATUS_A</td><td>R</td><td>13</td><td>00010011</td><td>output</td><td></td></tr><tr><td>FSM_STATUS_B</td><td>R</td><td>14</td><td>00010100</td><td>output</td><td></td></tr><tr><td>PAGE_RW</td><td>RW</td><td>17</td><td>00010111</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>18-43</td><td></td><td></td><td></td></tr><tr><td>EMB_FUNC_FIFO_CFG</td><td>RW</td><td>44</td><td>01000100</td><td>00000000</td><td></td></tr><tr><td>FSM_ENABLE_A</td><td>RW</td><td>46</td><td>01000110</td><td>00000000</td><td></td></tr><tr><td>FSM_ENABLE_B</td><td>RW</td><td>47</td><td>01000111</td><td>00000000</td><td></td></tr><tr><td>FSM_LONG_COUNTER_L</td><td>RW</td><td>48</td><td>01001000</td><td>00000000</td><td></td></tr><tr><td>FSM_LONG_COUNTER_H</td><td>RW</td><td>49</td><td>01001001</td><td>00000000</td><td></td></tr><tr><td>FSM_LONG_COUNTER_CLEAR</td><td>RW</td><td>4A</td><td>01001010</td><td>00000000</td><td></td></tr><tr><td>FSM_OUTS1</td><td>R</td><td>4C</td><td>01001100</td><td>output</td><td></td></tr><tr><td>FSM_OUTS2</td><td>R</td><td>4D</td><td>01001101</td><td>output</td><td></td></tr><tr><td>FSM_OUTS3</td><td>R</td><td>4E</td><td>01001110</td><td>output</td><td></td></tr><tr><td>FSM_OUTS4</td><td>R</td><td>4F</td><td>01001111</td><td>output</td><td></td></tr><tr><td>FSM_OUTS5</td><td>R</td><td>50</td><td>01010000</td><td>output</td><td></td></tr><tr><td>FSM_OUTS6</td><td>R</td><td>51</td><td>01010001</td><td>output</td><td></td></tr><tr><td>FSM_OUTS7</td><td>R</td><td>52</td><td>01010010</td><td>output</td><td></td></tr><tr><td>FSM_OUTS8</td><td>R</td><td>53</td><td>01010011</td><td>output</td><td></td></tr><tr><td>FSM_OUTS9</td><td>R</td><td>54</td><td>01010100</td><td>output</td><td></td></tr><tr><td>FSM_OUTS10</td><td>R</td><td>55</td><td>01010101</td><td>output</td><td></td></tr><tr><td>FSM_OUTS11</td><td>R</td><td>56</td><td>01010110</td><td>output</td><td></td></tr><tr><td>FSM_OUTS12</td><td>R</td><td>57</td><td>01010111</td><td>output</td><td></td></tr><tr><td>FSM_OUTS13</td><td>R</td><td>58</td><td>01011000</td><td>output</td><td></td></tr><tr><td>FSM_OUTS14</td><td>R</td><td>59</td><td>01011001</td><td>output</td><td></td></tr><tr><td>FSM_OUTS15</td><td>R</td><td>5A</td><td>01011010</td><td>output</td><td></td></tr><tr><td>FSM_OUTS16</td><td>R</td><td>5B</td><td>01011011</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>5C-5E</td><td></td><td></td><td></td></tr><tr><td>EMB_FUNC_ODR_CFG_B</td><td>RW</td><td>5F</td><td>01011111</td><td>01001011</td><td></td></tr><tr><td>STEP_COUNTER_L</td><td>R</td><td>62</td><td>01100010</td><td>output</td><td></td></tr><tr><td>STEP_COUNTER_H</td><td>R</td><td>63</td><td>01100011</td><td>output</td><td></td></tr><tr><td>EMB_FUNC_SRC</td><td>RW</td><td>64</td><td>01100100</td><td>output</td><td></td></tr><tr><td>EMB_FUNC_INIT_A</td><td>RW</td><td>66</td><td>01100110</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_INIT_B</td><td>RW</td><td>67</td><td>01100111</td><td>00000000</td><td></td></tr></table>

Registers marked as Reserved must not be changed. Writing to those registers may cause permanent damage to the device. 

The content of the registers that are loaded at boot should not be changed. They contain the factory calibration values. Their content is automatically restored when the device is powered up. 

# 11 Embedded functions register description

# 11.1 PAGE_SEL (02h)

Enable advanced features dedicated page (r/w) 


Table 178. PAGE_SEL register


<table><tr><td>PAGE_SEL3</td><td>PAGE_SEL2</td><td>PAGE_SEL1</td><td>PAGE_SEL0</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td></tr></table>

1. This bit must be set to ${ \bf \ " } O ^ { \prime }$ for the correct operation of the device. 

2. This bit must be set to '1' for the correct operation of the device. 


Table 179. PAGE_SEL register description


<table><tr><td>PAGE_SEL[3:0]</td><td>Select the advanced features dedicated pageDefault value: 0000</td></tr></table>

# 11.2 ADV_PEDO (03h)

Enable/disable pedometer advanced features register (r/w) 


Table 180. EMB_FUNC_EN_A register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>PEDO_FPR_ADF_DIS</td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to ${ \bf \ " } O ^ { \prime }$ for the correct operation of the device. 



Table 181. EMB_FUNC_EN_A register description


<table><tr><td>PEDO_FPR_ADF_DIS</td><td>Disable pedometer false-positive rejection block and advanced detection feature block.Default value: 1(0: Pedometer false-positive rejection block and advanced detection feature block enabled;1: Pedometer false-positive rejection block and advanced detection feature block disabled)</td></tr></table>

# 11.3 EMB_FUNC_EN_A (04h)

Embedded functions enable register (r/w) 


Table 182. EMB_FUNC_EN_A register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>SIGN_MOTION_EN</td><td>TILT_EN</td><td>PEDO_EN</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 183. EMB_FUNC_EN_A register description


<table><tr><td>SIGN_MOTION_EN</td><td>Enable significant motion detection function. Default value: 0(0: significant motion detection function disabled;1: significant motion detection function enabled)</td></tr><tr><td>TILT_EN</td><td>Enable tilt calculation. Default value: 0(0: tilt algorithm disabled;1: tilt algorithm enabled)</td></tr><tr><td>PEDO_EN</td><td>Enable pedometer algorithm. Default value: 0(0: pedometer algorithm disabled;1: pedometer algorithm enabled)</td></tr></table>

# 11.4 EMB_FUNC_EN_B (05h)

Embedded functions enable register (r/w) 


Table 184. EMB_FUNC_EN_B register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>PEDO_ADV_EN</td><td>FIFO_COMPR_EN</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>FSM_EN</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 185. EMB_FUNC_EN_B register description


<table><tr><td>PEDO_ADV_EN</td><td>Enable pedometer false-positive rejection block and advanced detection feature block. Default value: 0(0: Pedometer advanced features block disabled;1: Pedometer advanced features block enabled)</td></tr><tr><td>FIFO_COMPR_EN<eq>^{(1)}</eq></td><td>Enable FIFO compression feature. Default value: 0(0: FIFO compression feature disabled;1: FIFO compression feature enabled)</td></tr><tr><td>FSM_EN</td><td>Enable Finite State Machine (FSM) feature. Default value: 0(0: FSM feature disabled; 1: FSM feature enabled)</td></tr></table>


1. This bit is effective if the FIFO_COMPR_RT_EN bit of FIFO_CTRL2 (08h) is set to 1. 


# 11.5 PAGE_ADDRESS (08h)

Page address register (r/w) 


Table 186. PAGE_ADDRESS register


<table><tr><td>PAGE_ADDR7</td><td>PAGE_ADDR6</td><td>PAGE_ADDR5</td><td>PAGE_ADDR4</td><td>PAGE_ADDR3</td><td>PAGE_ADDR2</td><td>PAGE_ADDR1</td><td>PAGE_ADDR0</td></tr></table>


Table 187. PAGE_ADDRESS register description


<table><tr><td>PAGE_ADDR[7:0]</td><td>After setting the bit PAGE_WRITE / PAGE_READ in register PAGE_RW (17h), this register is used to set the address of the register to be written/read in the advanced features page selected through the bits PAGE_SEL[3:0] in register PAGE_SEL (02h).</td></tr></table>

# 11.6 PAGE_VALUE (09h)

Page value register (r/w) 


Table 188. PAGE_VALUE register


<table><tr><td>PAGE_VALUE7</td><td>PAGE_VALUE6</td><td>PAGE_VALUE5</td><td>PAGE_VALUE4</td><td>PAGE_VALUE3</td><td>PAGE_VALUE2</td><td>PAGE_VALUE1</td><td>PAGE_VALUE0</td></tr></table>


Table 189. PAGE_VALUE register description


<table><tr><td>PAGE_VALUE[7:0]</td><td>These bits are used to write (if the bit PAGE_WRITE = 1 in register PAGE_RW (17h)) or read (if the bit PAGE_READ = 1 in register PAGE_RW (17h)) the data at the address PAGE_ADDR[7:0] of the selected advanced features page.</td></tr></table>

# 11.7 EMB_FUNC_INT1 (0Ah)

INT1 pin control register (r/w) 

Each bit in this register enables a signal to be carried over INT1. The pin's output will supply the OR combination of the selected signals. 


Table 190. EMB_FUNC_INT1 register


<table><tr><td>INT1_FSM_LC</td><td><eq>0^{(1)}</eq></td><td>INT1_SIG_MOT</td><td>INT1_TILT</td><td>INT1_STEP_DETECTOR</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 191. EMB_FUNC_INT1 register description


<table><tr><td><eq>INT1\_FSM\_LC^{(1)}</eq></td><td>Routing of FSM long counter timeout interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_SIG\_MOT^{(1)}</eq></td><td>Routing of significant motion event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_TILT^{(1)}</eq></td><td>Routing of tilt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_STEP\_DETECTOR^{(1)}</eq></td><td>Routing of pedometer step recognition event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr></table>


1. This bit is effective if the INT1_EMB_FUNC bit of MD1_CFG (5Eh) is set to 1. 


# 11.8 FSM_INT1_A (0Bh)

INT1 pin control register (r/w). 

Each bit in this register enables a signal to be carried over INT1. The pin's output will supply the OR combination of the selected signals. 


Table 192. FSM_INT1_A register


<table><tr><td>INT1_FSM8</td><td>INT1_FSM7</td><td>INT1_FSM6</td><td>INT1_FSM5</td><td>INT1_FSM4</td><td>INT1_FSM3</td><td>INT1_FSM2</td><td>INT1_FSM1</td></tr></table>


Table 193. FSM_INT1_A register description


<table><tr><td><eq>INT1\_FSM8^{(1)}</eq></td><td>Routing of FSM8 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM7^{(1)}</eq></td><td>Routing of FSM7 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM6^{(1)}</eq></td><td>Routing of FSM6 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM5^{(1)}</eq></td><td>Routing of FSM5 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM4^{(1)}</eq></td><td>Routing of FSM4 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM3^{(1)}</eq></td><td>Routing of FSM3 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM2^{(1)}</eq></td><td>Routing of FSM2 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM1^{(1)}</eq></td><td>Routing of FSM1 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr></table>


1. This bit is effective if the INT1_EMB_FUNC bit of MD1_CFG (5Eh) is set to 1. 


# 11.9 FSM_INT1_B (0Ch)

INT1 pin control register (r/w). 

Each bit in this register enables a signal to be carried over INT1. The pin's output will supply the OR combination of the selected signals. 


Table 194. FSM_INT1_B register


<table><tr><td>INT1_FSM16</td><td>INT1_FSM15</td><td>INT1_FSM14</td><td>INT1_FSM13</td><td>INT1_FSM12</td><td>INT1_FSM11</td><td>INT1_FSM10</td><td>INT1_FSM9</td></tr></table>


Table 195. FSM_INT1_B register description


<table><tr><td><eq>INT1\_FSM16^{(1)}</eq></td><td>Routing of FSM16 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM15^{(1)}</eq></td><td>Routing of FSM15 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM14^{(1)}</eq></td><td>Routing of FSM14 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM13^{(1)}</eq></td><td>Routing of FSM13 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM12^{(1)}</eq></td><td>Routing of FSM12 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM11^{(1)}</eq></td><td>Routing of FSM11 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM10^{(1)}</eq></td><td>Routing of FSM10 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT1\_FSM9^{(1)}</eq></td><td>Routing of FSM9 interrupt event on INT1. Default value: 0(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr></table>


1. This bit is effective if the INT1_EMB_FUNC bit of MD1_CFG (5Eh) is set to 1. 


# 11.10 EMB_FUNC_INT2 (0Eh)

INT2 pin control register (r/w). 

Each bit in this register enables a signal to be carried over INT2. The pin's output will supply the OR combination of the selected signals. 


Table 196. EMB_FUNC_INT2 register


<table><tr><td>INT2_FSM_LC</td><td><eq>0^{(1)}</eq></td><td>INT2_SIG_MOT</td><td>INT2_TILT</td><td>INT2_STEP_DETECTOR</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 197. EMB_FUNC_INT2 register description


<table><tr><td>INT2_FSM_LC(1)</td><td>Routing of FSM long counter timeout interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td>INT2_SIG_MOT(1)</td><td>Routing of significant motion event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td>INT2_TILT(1)</td><td>Routing of tilt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td>INT2_STEP_DETECTOR(1)</td><td>Routing of pedometer step recognition event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr></table>


1. This bit is effective if the INT2_EMB_FUNC bit of MD2_CFG (5Fh) is set to 1. 


# 11.11 FSM_INT2_A (0Fh)

INT2 pin control register (r/w). 

Each bit in this register enables a signal to be carried over INT2. The pin's output will supply the OR combination of the selected signals. 


Table 198. FSM_INT2_A register


<table><tr><td>INT2_FSM8</td><td>INT2_FSM7</td><td>INT2_FSM6</td><td>INT2_FSM5</td><td>INT2_FSM4</td><td>INT2_FSM3</td><td>INT2_FSM2</td><td>INT2_FSM1</td></tr></table>


Table 199. FSM_INT2_A register description


<table><tr><td><eq>INT2\_FSM8^{(1)}</eq></td><td>Routing of FSM8 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM7^{(1)}</eq></td><td>Routing of FSM7 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM6^{(1)}</eq></td><td>Routing of FSM6 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM5^{(1)}</eq></td><td>Routing of FSM5 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM4^{(1)}</eq></td><td>Routing of FSM4 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM3^{(1)}</eq></td><td>Routing of FSM3 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT2\_FSM2^{(1)}</eq></td><td>Routing of FSM2 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM1^{(1)}</eq></td><td>Routing of FSM1 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr></table>


1. This bit is effective if the INT2_EMB_FUNC bit of MD2_CFG (5Fh) is set to 1. 


# 11.12 FSM_INT2_B (10h)

INT2 pin control register (r/w). 

Each bit in this register enables a signal to be carried over INT2. The pin's output will supply the OR combination of the selected signals. 


Table 200. FSM_INT2_B register


<table><tr><td>INT2_FSM16</td><td>INT2_FSM15</td><td>INT2_FSM14</td><td>INT2_FSM13</td><td>INT2_FSM12</td><td>INT2_FSM11</td><td>INT2_FSM10</td><td>INT2_FSM9</td></tr></table>


Table 201. FSM_INT2_B register description


<table><tr><td><eq>INT2\_FSM16^{(1)}</eq></td><td>Routing of FSM16 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM15^{(1)}</eq></td><td>Routing of FSM15 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM14^{(1)}</eq></td><td>Routing of FSM14 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM13^{(1)}</eq></td><td>Routing of FSM13 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM12^{(1)}</eq></td><td>Routing of FSM12 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM11^{(1)}</eq></td><td>Routing of FSM11 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)(0: routing on INT1 disabled; 1: routing on INT1 enabled)</td></tr><tr><td><eq>INT2\_FSM10^{(1)}</eq></td><td>Routing of FSM10 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM9^{(1)}</eq></td><td>Routing of FSM9 interrupt event on INT2. Default value: 0(0: routing on INT2 disabled; 1: routing on INT2 enabled)</td></tr></table>


1. This bit is effective if the INT2_EMB_FUNC bit of MD2_CFG (5Fh) is set to 1. 


# 11.13 EMB_FUNC_STATUS (12h)

Embedded function status register (r) 


Table 202. EMB_FUNC_STATUS register


<table><tr><td>IS_FSM_LC</td><td>0</td><td>IS_SIGMOT</td><td>IS_TILT</td><td>IS_STEP_DET</td><td>0</td><td>0</td><td>0</td></tr></table>


Table 203. EMB_FUNC_STATUS register description


<table><tr><td>IS_FSM_LC</td><td>Interrupt status bit for FSM long counter timeout interrupt event.(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_SIGMOT</td><td>Interrupt status bit for significant motion detection(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_TILT</td><td>Interrupt status bit for tilt detection(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_STEP_DET</td><td>Interrupt status bit for step detection(1: interrupt detected; 0: no interrupt)</td></tr></table>

# 11.14 FSM_STATUS_A (13h)

Finite State Machine status register (r) 


Table 204. FSM_STATUS_A register


<table><tr><td>IS_FSM8</td><td>IS_FSM7</td><td>IS_FSM6</td><td>IS_FSM5</td><td>IS_FSM4</td><td>IS_FSM3</td><td>IS_FSM2</td><td>IS_FSM1</td></tr></table>


Table 205. FSM_STATUS_A register description


<table><tr><td>IS_FSM8</td><td>Interrupt status bit for FSM8 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM7</td><td>Interrupt status bit for FSM7 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM6</td><td>Interrupt status bit for FSM6 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM5</td><td>Interrupt status bit for FSM5 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM4</td><td>Interrupt status bit for FSM4 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM3</td><td>Interrupt status bit for FSM3 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM2</td><td>Interrupt status bit for FSM2 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM1</td><td>Interrupt status bit for FSM1 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr></table>

# 11.15 FSM_STATUS_B (14h)

Finite State Machine status register (r) 


Table 206. FSM_STATUS_B register


<table><tr><td>IS_FSM16</td><td>IS_FSM15</td><td>IS_FSM14</td><td>IS_FSM13</td><td>IS_FSM12</td><td>IS_FSM11</td><td>IS_FSM10</td><td>IS_FSM9</td></tr></table>


Table 207. FSM_STATUS_B register description


<table><tr><td>IS_FSM16</td><td>Interrupt status bit for FSM16 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM15</td><td>Interrupt status bit for FSM15 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM14</td><td>Interrupt status bit for FSM14 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM13</td><td>Interrupt status bit for FSM13 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM12</td><td>Interrupt status bit for FSM12 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM11</td><td>Interrupt status bit for FSM11 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM10</td><td>Interrupt status bit for FSM10 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM9</td><td>Interrupt status bit for FSM9 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr></table>

# 11.16 PAGE_RW (17h)

Enable read and write mode of advanced features dedicated page (r/w) 


Table 208. PAGE_RW register


<table><tr><td>EMB_FUNC_LIR</td><td>PAGE_WRITE</td><td>PAGE_READ</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 209. PAGE_RW register description


<table><tr><td>EMB_FUNC_LIR</td><td>Latched Interrupt mode for Embedded Functions. Default value: 0(0: Embedded Functions interrupt request not latched;1: Embedded Functions interrupt request latched)</td></tr><tr><td>PAGE_WRITE</td><td>Enable writes to the selected advanced features dedicated page.<eq>^{(1)}</eq>Default value: 0(1: enable; 0: disable)</td></tr><tr><td>PAGE_READ</td><td>Enable reads from the selected advanced features dedicated page.<eq>^{(1)}</eq>Default value: 0(1: enable; 0: disable)</td></tr></table>


1. Page selected by PAGE_SEL[3:0] in register PAGE_SEL (02h). 


# 11.17 EMB_FUNC_FIFO_CFG (44h)

Embedded functions batching configuration register (r/w) 


Table 210. EMB_FUNC_FIFO_CFG register


<table><tr><td><eq>0^{(1)}</eq></td><td>PEDO_FIFO_EN</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 211. EMB_FUNC_FIFO_CFG register description


<table><tr><td>PEDO_FIFO_EN</td><td>Enable FIFO batching of step counter values. Default value: 0</td></tr></table>

# 11.18 FSM_ENABLE_A (46h)

FSM enable register (r/w) 


Table 212. FSM_ENABLE_A register


<table><tr><td>FSM8_EN</td><td>FSM7_EN</td><td>FSM6_EN</td><td>FSM5_EN</td><td>FSM4_EN</td><td>FSM3_EN</td><td>FSM2_EN</td><td>FSM1_EN</td></tr></table>


Table 213. FSM_ENABLE_A register description


<table><tr><td>FSM8_EN</td><td>FSM8 enable. Default value: 0 (0: FSM8 disabled; 1: FSM8 enabled)</td></tr><tr><td>FSM7_EN</td><td>FSM7 enable. Default value: 0 (0: FSM7 disabled; 1: FSM7 enabled)</td></tr><tr><td>FSM6_EN</td><td>FSM6 enable. Default value: 0 (0: FSM6 disabled; 1: FSM6 enabled)</td></tr><tr><td>FSM5_EN</td><td>FSM5 enable. Default value: 0 (0: FSM5 disabled; 1: FSM5 enabled)</td></tr><tr><td>FSM4_EN</td><td>FSM4 enable. Default value: 0 (0: FSM4 disabled; 1: FSM4 enabled)</td></tr><tr><td>FSM3_EN</td><td>FSM3 enable. Default value: 0 (0: FSM3 disabled; 1: FSM3 enabled)</td></tr><tr><td>FSM2_EN</td><td>FSM2 enable. Default value: 0 (0: FSM2 disabled; 1: FSM2 enabled)</td></tr><tr><td>FSM1_EN</td><td>FSM1 enable. Default value: 0 (0: FSM1 disabled; 1: FSM1 enabled)</td></tr></table>

# 11.19 FSM_ENABLE_B (47h)

FSM enable register (r/w) 


Table 214. FSM_ENABLE_B register


<table><tr><td>FSM16_EN</td><td>FSM15_EN</td><td>FSM14_EN</td><td>FSM13_EN</td><td>FSM12_EN</td><td>FSM11_EN</td><td>FSM10_EN</td><td>FSM9_EN</td></tr></table>


Table 215. FSM_ENABLE_B register description


<table><tr><td>FSM16_EN</td><td>FSM16 enable. Default value: 0 (0: FSM16 disabled; 1: FSM16 enabled)</td></tr><tr><td>FSM15_EN</td><td>FSM15 enable. Default value: 0 (0: FSM15 disabled; 1: FSM15 enabled)</td></tr><tr><td>FSM14_EN</td><td>FSM14 enable. Default value: 0 (0: FSM14 disabled; 1: FSM14 enabled)</td></tr><tr><td>FSM13_EN</td><td>FSM13 enable. Default value: 0 (0: FSM13 disabled; 1: FSM13 enabled)</td></tr><tr><td>FSM12_EN</td><td>FSM12 enable. Default value: 0 (0: FSM12 disabled; 1: FSM12 enabled)</td></tr><tr><td>FSM11_EN</td><td>FSM11 enable. Default value: 0 (0: FSM11 disabled; 1: FSM11 enabled)</td></tr><tr><td>FSM10_EN</td><td>FSM10 enable. Default value: 0 (0: FSM10 disabled; 1: FSM10 enabled)</td></tr><tr><td>FSM9_EN</td><td>FSM9 enable. Default value: 0 (0: FSM9 disabled; 1: FSM9 enabled)</td></tr></table>

# 11.20 FSM_LONG_COUNTER_L (48h) and FSM_LONG_COUNTER_H (49h)

FSM long counter status register (r/w). 

Long counter value is an unsigned integer value (16-bit format); this value can be reset using the LC_CLEAR bit in FSM_LONG_COUNTER_CLEAR (4Ah) register. 


Table 216. FSM_LONG_COUNTER_L register


<table><tr><td>FSM_LC_7</td><td>FSM_LC_6</td><td>FSM_LC_5</td><td>FSM_LC_4</td><td>FSM_LC_3</td><td>FSM_LC_2</td><td>FSM_LC_1</td><td>FSM_LC_0</td></tr></table>


Table 217. FSM_LONG_COUNTER_L register description


<table><tr><td>FSM_LC_[7:0]</td><td>Long counter current value (LSbyte). Default value: 00000000</td></tr></table>


Table 218. FSM_LONG_COUNTER_H register


<table><tr><td>FSM_LC_15</td><td>FSM_LC_14</td><td>FSM_LC_13</td><td>FSM_LC_12</td><td>FSM_LC_11</td><td>FSM_LC_10</td><td>FSM_LC_9</td><td>FSM_LC_8</td></tr></table>


Table 219. FSM_LONG_COUNTER_H register description


<table><tr><td>FSM_LC_[15:8]</td><td>Long counter current value (MSbyte). Default value: 00000000</td></tr></table>

# 11.21 FSM_LONG_COUNTER_CLEAR (4Ah)

FSM long counter reset register (r/w) 


Table 220. FSM_LONG_COUNTER_CLEAR register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>FSM_LC_CLEARED</td><td>FSM_LC_CLEAR</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 221. FSM_LONG_COUNTER_CLEAR register description


<table><tr><td>FSM_LC_CLEARED</td><td>This read-only bit is automatically set to 1 when the long counter reset is done. Default value: 0</td></tr><tr><td>FSM_LC_CLEAR</td><td>Clear FSM long counter value. Default value: 0</td></tr></table>

# 11.22 FSM_OUTS1 (4Ch)

FSM1 output register (r) 


Table 222. FSM_OUTS1 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 223. FSM_OUTS1 register description


<table><tr><td>P_X</td><td>FSM1 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM1 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM1 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM1 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM1 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM1 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM1 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM1 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.23 FSM_OUTS2 (4Dh)

FSM2 output register (r) 


Table 224. FSM_OUTS2 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 225. FSM_OUTS2 register description


<table><tr><td>P_X</td><td>FSM2 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM2 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM2 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM2 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM2 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM2 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM2 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM2 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.24 FSM_OUTS3 (4Eh)

FSM3 output register (r) 


Table 226. FSM_OUTS3 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 227. FSM_OUTS3 register description


<table><tr><td>P_X</td><td>FSM3 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM3 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM3 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM3 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM3 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM3 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM3 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM3 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.25 FSM_OUTS4 (4Fh)

FSM4 output register (r) 


Table 228. FSM_OUTS4 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 229. FSM_OUTS4 register description


<table><tr><td>P_X</td><td>FSM4 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM4 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM4 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM4 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM4 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM4 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM4 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM4 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.26 FSM_OUTS5 (50h)

FSM5 output register (r) 


Table 230. FSM_OUTS5 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 231. FSM_OUTS5 register description


<table><tr><td>P_X</td><td>FSM5 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM5 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM5 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM5 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM5 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM5 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM5 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM5 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.27 FSM_OUTS6 (51h)

FSM6 output register (r) 


Table 232. FSM_OUTS6 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 233. FSM_OUTS6 register description


<table><tr><td>P_X</td><td>FSM6 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM6 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM6 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM6 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM6 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM6 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM6 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM6 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.28 FSM_OUTS7 (52h)

FSM7 output register (r) 


Table 234. FSM_OUTS7 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 235. FSM_OUTS7 register description


<table><tr><td>P_X</td><td>FSM7 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM7 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM7 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM7 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM7 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM7 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM7 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM7 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.29 FSM_OUTS8 (53h)

FSM8 output register (r) 


Table 236. FSM_OUTS8 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 237. FSM_OUTS8 register description


<table><tr><td>P_X</td><td>FSM8 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM8 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM8 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM8 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM8 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM8 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM8 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM8 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.30 FSM_OUTS9 (54h)

FSM9 output register (r) 


Table 238. FSM_OUTS9 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 239. FSM_OUTS9 register description


<table><tr><td>P_X</td><td>FSM9 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM9 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM9 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM9 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM9 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM9 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM9 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM9 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.31 FSM_OUTS10 (55h)

FSM10 output register (r) 


Table 240. FSM_OUTS10 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 241. FSM_OUTS10 register description


<table><tr><td>P_X</td><td>FSM10 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM10 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM10 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM10 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM10 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM10 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM10 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM10 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.32 FSM_OUTS11 (56h)

FSM11 output register (r) 


Table 242. FSM_OUTS11 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 243. FSM_OUTS11 register description


<table><tr><td>P_X</td><td>FSM11 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM11 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM11 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM11 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM11 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM11 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM11 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM11 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.33 FSM_OUTS12 (57h)

FSM12 output register (r) 


Table 244. FSM_OUTS12 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 245. FSM_OUTS12 register description


<table><tr><td>P_X</td><td>FSM12 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM12 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM12 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM12 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM12 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM12 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM12 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM12 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.34 FSM_OUTS13 (58h)

FSM13 output register (r) 


Table 246. FSM_OUTS13 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 247. FSM_OUTS13 register description


<table><tr><td>P_X</td><td>FSM13 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM13 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM13 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM13 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM13 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM13 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM13 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM13 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.35 FSM_OUTS14 (59h)

FSM14 output register (r) 


Table 248. FSM_OUTS14 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 249. FSM_OUTS14 register description


<table><tr><td>P_X</td><td>FSM14 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM14 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM14 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM14 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM14 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM14 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM14 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM14 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.36 FSM_OUTS15 (5Ah)

FSM15 output register (r) 


Table 250. FSM_OUTS15 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 251. FSM_OUTS15 register description


<table><tr><td>P_X</td><td>FSM15 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM15 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM15 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM15 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM15 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM15 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM15 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM15 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.37 FSM_OUTS16 (5Bh)

FSM16 output register (r) 


Table 252. FSM_OUTS16 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 253. FSM_OUTS16 register description


<table><tr><td>P_X</td><td>FSM16 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM16 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM16 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM16 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM16 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM16 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM16 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM16 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

# 11.38 EMB_FUNC_ODR_CFG_B (5Fh)

Finite State Machine output data rate configuration register (r/w) 


Table 254. EMB_FUNC_ODR_CFG_B register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td><td><eq>0^{(1)}</eq></td><td>FSM_ODR1</td><td>FSM_ODR0</td><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td><td><eq>1^{(2)}</eq></td></tr></table>

1. This bit must be set to '0' for the correct operation of the device. 

2. This bit must be set to '1' for the correct operation of the device 


Table 255. EMB_FUNC_ODR_CFG_B register description


<table><tr><td>FSM_ODR[1:0]</td><td>Finite State Machine ODR configuration:(00: 12.5 Hz;01: 26 Hz (default);10: 52 Hz;11: 104 Hz)</td></tr></table>

# 11.39 STEP_COUNTER_L (62h) and STEP_COUNTER_H (63h)

Step counter output register (r) 


Table 256. STEP_COUNTER_L register


<table><tr><td>STEP_7</td><td>STEP_6</td><td>STEP_5</td><td>STEP_4</td><td>STEP_3</td><td>STEP_2</td><td>STEP_1</td><td>STEP_0</td></tr></table>


Table 257. STEP_COUNTER_L register description


<table><tr><td>STEP_[7:0]</td><td>Step counter output (LSbyte)</td></tr></table>


Table 258. STEP_COUNTER_H register


<table><tr><td>STEP_15</td><td>STEP_14</td><td>STEP_13</td><td>STEP_12</td><td>STEP_11</td><td>STEP_10</td><td>STEP_9</td><td>STEP_8</td></tr></table>


Table 259. STEP_COUNTER_H register description


<table><tr><td>STEP_[15:8]</td><td>Step counter output (MSbyte)</td></tr></table>

# 11.40 EMB_FUNC_SRC (64h)

Embedded function source register (r/w) 


Table 260. EMB_FUNC_SRC register


<table><tr><td>PEDO_RST_STEP</td><td><eq>0^{(1)}</eq></td><td>STEP_DETECTED</td><td>STEP_COUNT_DELTA_IA</td><td>STEP_OVERFLOW</td><td>STEPCOUNTER_BIT_SET</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 261. EMB_FUNC_SRC register description


<table><tr><td>PEDO_RST_STEP</td><td>Reset pedometer step counter. Read/write bit.(0: disabled; 1: enabled)</td></tr><tr><td>STEP_DETECTED</td><td>Step detector event detection status. Read-only bit.(0: step detection event not detected; 1: step detection event detected)</td></tr><tr><td>STEP_COUNT_DELTA_IA</td><td>Pedometer step recognition on delta time status. Read-only bit.(0: no step recognized during delta time;1: at least one step recognized during delta time)</td></tr><tr><td>STEP_OVERFLOW</td><td>Step counter overflow status. Read-only bit.(0: step counter value <eq>&lt; 2^{16}</eq>; 1: step counter value reached <eq>2^{16}</eq>)</td></tr><tr><td>STEPCOUNTER_BIT_SET</td><td>This bit is equal to 1 when the step count is increased. Read-only bit.</td></tr></table>

# 11.41 EMB_FUNC_INIT_A (66h)

Embedded functions initialization register (r/w) 


Table 262. EMB_FUNC_INIT_A register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>SIG_MOT_INIT</td><td>TILT_INIT</td><td>STEP_DET_INIT</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 263. EMB_FUNC_INIT_A register description


<table><tr><td>SIG_MOT_INIT</td><td>Significant Motion Detection algorithm initialization request. Default value: 0</td></tr><tr><td>TILT_INIT</td><td>Tilt algorithm initialization request. Default value: 0</td></tr><tr><td>STEP_DET_INIT</td><td>Pedometer Step Counter/Detector algorithm initialization request. Default value: 0</td></tr></table>

# 11.42 EMB_FUNC_INIT_B (67h)

Embedded functions initialization register (r/w) 


Table 264. EMB_FUNC_INIT_B register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>FIFO_COMPR_INIT</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>FSM_INIT</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 265. EMB_FUNC_INIT_B register description


<table><tr><td>FIFO_COMPR_INIT</td><td>FIFO compression feature initialization request. Default value: 0</td></tr><tr><td>FSM_INIT</td><td>FSM initialization request. Default value: 0</td></tr></table>

# 12 Embedded advanced features pages

The table given below provides a list of the registers for the embedded advanced features page 0. These registers are accessible when PAGE_SEL[3:0] are set to 0000 in PAGE_SEL (02h). 


Table 266. Register address map - embedded advanced features page 0


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>MAG_SENSITIVITY_L</td><td>RW</td><td>BA</td><td>10111010</td><td>00100100</td><td></td></tr><tr><td>MAG_SENSITIVITY_H</td><td>RW</td><td>BB</td><td>10111011</td><td>00010110</td><td></td></tr><tr><td>MAG_OFFX_L</td><td>RW</td><td>C0</td><td>11000000</td><td>00000000</td><td></td></tr><tr><td>MAG_OFFX_H</td><td>RW</td><td>C1</td><td>11000001</td><td>00000000</td><td></td></tr><tr><td>MAG_OFFY_L</td><td>RW</td><td>C2</td><td>11000010</td><td>00000000</td><td></td></tr><tr><td>MAG_OFFY_H</td><td>RW</td><td>C3</td><td>11000011</td><td>00000000</td><td></td></tr><tr><td>MAG_OFFZ_L</td><td>RW</td><td>C4</td><td>11000100</td><td>00000000</td><td></td></tr><tr><td>MAG_OFFZ_H</td><td>RW</td><td>C5</td><td>11000101</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_XX_L</td><td>RW</td><td>C6</td><td>11000110</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_XX_H</td><td>RW</td><td>C7</td><td>11000111</td><td>00111100</td><td></td></tr><tr><td>MAG_SI_XY_L</td><td>RW</td><td>C8</td><td>11001000</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_XY_H</td><td>RW</td><td>C9</td><td>11001001</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_XZ_L</td><td>RW</td><td>CA</td><td>11001010</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_XZ_H</td><td>RW</td><td>CB</td><td>11001011</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_YY_L</td><td>RW</td><td>CC</td><td>11001100</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_YY_H</td><td>RW</td><td>CD</td><td>11001101</td><td>00111100</td><td></td></tr><tr><td>MAG_SI_YZ_L</td><td>RW</td><td>CE</td><td>11001110</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_YZ_H</td><td>RW</td><td>CF</td><td>11001111</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_ZZ_L</td><td>RW</td><td>D0</td><td>11010000</td><td>00000000</td><td></td></tr><tr><td>MAG_SI_ZZ_H</td><td>RW</td><td>D1</td><td>11010001</td><td>00111100</td><td></td></tr><tr><td>MAG_CFG_A</td><td>RW</td><td>D4</td><td>11010100</td><td>00000101</td><td></td></tr><tr><td>MAG_CFG_B</td><td>RW</td><td>D5</td><td>11010101</td><td>00000010</td><td></td></tr></table>

The following table provides a list of the registers for the embedded advanced features page 1. These registers are accessible when PAGE_SEL[3:0] are set to 0001 in PAGE_SEL (02h). 


Table 267. Register address map - embedded advanced features page 1


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>FSM_LC_TIMEOUT_L</td><td>RW</td><td>7A</td><td>01111010</td><td>00000000</td><td></td></tr><tr><td>FSM_LC_TIMEOUT_H</td><td>RW</td><td>7B</td><td>01111011</td><td>00000000</td><td></td></tr><tr><td>FSM_PROGRAMS</td><td>RW</td><td>7C</td><td>01111100</td><td>00000000</td><td></td></tr><tr><td>FSM_START_ADD_L</td><td>RW</td><td>7E</td><td>01111110</td><td>00000000</td><td></td></tr><tr><td>FSM_START_ADD_H</td><td>RW</td><td>7F</td><td>01111111</td><td>00000000</td><td></td></tr><tr><td>PEDO_CMD_REG</td><td>RW</td><td>83</td><td>10000011</td><td>00000000</td><td></td></tr><tr><td>PEDO_DEB_STEPS_CONF</td><td>RW</td><td>84</td><td>10000100</td><td>00001010</td><td></td></tr><tr><td>PEDO_SC_DELTAT_L</td><td>RW</td><td>D0</td><td>11010000</td><td>00000000</td><td></td></tr><tr><td>PEDO_SC_DELTAT_H</td><td>RW</td><td>D1</td><td>11010001</td><td>00000000</td><td></td></tr></table>

Registers marked as Reserved must not be changed. Writing to those registers may cause permanent damage to the device. 

The content of the registers that are loaded at boot should not be changed. They contain the factory calibration values. Their content is automatically restored when the device is powered up. 

# Write procedure example:

Example: write value 06h register at address 84h (PEDO_DEB_STEPS_CONF) in Page 1 

1. Write bit FUNC_CFG_EN = 1 // Enable access to embedded functions registers in FUNC_CFG_ACCESS (01h) 

2. Write bit PAGE_WRITE = 1 // Select write operation mode in PAGE_RW (17h) register 

3. Write 0001 in PAGE_SEL[3:0] field // Select page 1 of register PAGE_SEL (02h) 

4. Write 84h in PAGE_ADDR register (08h) // Set address 

5. Write 06h in PAGE_DATA register (09h) // Set value to be written 

6. Write bit PAGE_WRITE = 0 // Write operation disabled in PAGE_RW (17h) register 

7. Write bit FUNC_CFG_EN = 0 // Disable access to embedded functions registers in FUNC_CFG_ACCESS (01h) 

# Read procedure example:

Example: read value of register at address 84h (PEDO_DEB_STEPS_CONF) in Page 1 

1. Write bit FUNC_CFG_EN = 1 // Enable access to embedded functions registers in FUNC_CFG_ACCESS (01h) 

2. Write bit PAGE_READ = 1 // Select read operation mode in PAGE_RW (17h) register 

3. Write 0001 in PAGE_SEL[3:0] field // Select page 1 of register PAGE_SEL (02h) 

4. Write 84h in PAGE_ADDR register (08h) // Set address 

5. Read value of PAGE_DATA register (09h) // Get register value 

6. Write bit PAGE_READ = 0 in PAGE_RW (17h) register 

// Read operation disabled 

7. Write bit FUNC_CFG_EN = 0 in FUNC_CFG_ACCESS (01h) 

// Disable access to embedded functions registers 

Note: Steps 1 and 2 of both procedures are intended to be performed at the beginning of the procedure. Steps 6 and 7 of both procedures are intended to be performed at the end of the procedure. If the procedure involves multiple operations, only steps 3, 4 and 5 must be repeated for each operation. If, in particular, multiple operations involve consecutive registers, only step 5 can be performed. 

# 13 Embedded advanced features register description

# 13.1 Page 0 - Embedded advanced features registers

# 13.1.1 MAG_SENSITIVITY_L (BAh) and MAG_SENSITIVITY_H (BBh)

External magnetometer sensitivity value register for the Finite State Machine (r/w). 

This register corresponds to the LSB-to-gauss conversion value of the external magnetometer sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 

Default value of MAG_SENS[15:0] is 0x1624, corresponding to 0.0015 gauss/LSB. 


Table 268. MAG_SENSITIVITY_L register


<table><tr><td>MAG_SENS_7</td><td>MAG_SENS_6</td><td>MAG_SENS_5</td><td>MAG_SENS_4</td><td>MAG_SENS_3</td><td>MAG_SENS_2</td><td>MAG_SENS_1</td><td>MAG_SENS_0</td></tr></table>


Table 269. MAG_SENSITIVITY_L register description


<table><tr><td>MAG_SENS_[7:0]</td><td>External magnetometer sensitivity (LSbyte). Default value: 00100100</td></tr></table>


Table 270. MAG_SENSITIVITY_H register


<table><tr><td>MAG_SENS_15</td><td>MAG_SENS_14</td><td>MAG_SENS_13</td><td>MAG_SENS_12</td><td>MAG_SENS_11</td><td>MAG_SENS_10</td><td>MAG_SENS_9</td><td>MAG_SENS_8</td></tr></table>


Table 271. MAG_SENSITIVITY_H register description


<table><tr><td>MAG_SENS_[15:8]</td><td>External magnetometer sensitivity (MSbyte). Default value: 00010110</td></tr></table>

# 13.1.2 MAG_OFFX_L (C0h) and MAG_OFFX_H (C1h)

Offset for X-axis hard-iron compensation register (r/w). 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 272. MAG_OFFX_L register


<table><tr><td>MAG_OFFX_7</td><td>MAG_OFFX_6</td><td>MAG_OFFX_5</td><td>MAG_OFFX_4</td><td>MAG_OFFX_3</td><td>MAG_OFFX_2</td><td>MAG_OFFX_1</td><td>MAG_OFFX_0</td></tr></table>


Table 273. MAG_OFFX_L register description


<table><tr><td>MAG_OFFX_[7:0]</td><td>Offset for X-axis hard-iron compensation (LSbyte). Default value: 00000000</td></tr></table>


Table 274. MAG_OFFX_H register


<table><tr><td>MAG_OFFX_15</td><td>MAG_OFFX_14</td><td>MAG_OFFX_13</td><td>MAG_OFFX_12</td><td>MAG_OFFX_11</td><td>MAG_OFFX_10</td><td>MAG_OFFX_9</td><td>MAG_OFFX_8</td></tr></table>


Table 275. MAG_OFFX_H register description


<table><tr><td>MAG_OFFX_[15:8]</td><td>Offset for X-axis hard-iron compensation (MSbyte). Default value: 00000000</td></tr></table>

# 13.1.3 MAG_OFFY_L (C2h) and MAG_OFFY_H (C3h)

Offset for Y-axis hard-iron compensation register (r/w). 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 276. MAG_OFFY_L register


<table><tr><td>MAG_OFFY_7</td><td>MAG_OFFY_6</td><td>MAG_OFFY_5</td><td>MAG_OFFY_4</td><td>MAG_OFFY_3</td><td>MAG_OFFY_2</td><td>MAG_OFFY_1</td><td>MAG_OFFY_0</td></tr></table>


Table 277. MAG_OFFY_L register description


<table><tr><td>MAG_OFFY_[7:0]</td><td>Offset for Y-axis hard-iron compensation (LSbyte). Default value: 00000000</td></tr></table>


Table 278. MAG_OFFY_H register


<table><tr><td>MAG_OFFY_15</td><td>MAG_OFFY_14</td><td>MAG_OFFY_13</td><td>MAG_OFFY_12</td><td>MAG_OFFY_11</td><td>MAG_OFFY_10</td><td>MAG_OFFY_9</td><td>MAG_OFFY_8</td></tr></table>


Table 279. MAG_OFFY_H register description


<table><tr><td>MAG_OFFY_[15:8]</td><td>Offset for Y-axis hard-iron compensation (MSbyte). Default value: 00000000</td></tr></table>

# 13.1.4 MAG_OFFZ_L (C4h) and MAG_OFFZ_H (C5h)

Offset for Z-axis hard-iron compensation register (r/w). 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 280. MAG_OFFZ_L register


<table><tr><td>MAG_OFFZ_7</td><td>MAG_OFFZ_6</td><td>MAG_OFFZ_5</td><td>MAG_OFFZ_4</td><td>MAG_OFFZ_3</td><td>MAG_OFFZ_2</td><td>MAG_OFFZ_1</td><td>MAG_OFFZ_0</td></tr></table>


Table 281. MAG_OFFZ_L register description


<table><tr><td>MAG_OFFZ_[7:0]</td><td>Offset for Z-axis hard-iron compensation (LSbyte). Default value: 00000000</td></tr></table>


Table 282. MAG_OFFZ_H register


<table><tr><td>MAG_OFFZ_15</td><td>MAG_OFFZ_14</td><td>MAG_OFFZ_13</td><td>MAG_OFFZ_12</td><td>MAG_OFFZ_11</td><td>MAG_OFFZ_10</td><td>MAG_OFFZ_9</td><td>MAG_OFFZ_8</td></tr></table>


Table 283. MAG_OFFZ_H register description


<table><tr><td>MAG_OFFZ_[15:8]</td><td>Offset for Z-axis hard-iron compensation (MSbyte). Default value: 00000000</td></tr></table>

# 13.1.5 MAG_SI_XX_L (C6h) and MAG_SI_XX_H (C7h)

Soft-iron (3x3 symmetric) matrix correction register (r/w). 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 284. MAG_SI_XX_L register


<table><tr><td>MAG_SI_XX_7</td><td>MAG_SI_XX_6</td><td>MAG_SI_XX_5</td><td>MAG_SI_XX_4</td><td>MAG_SI_XX_3</td><td>MAG_SI_XX_2</td><td>MAG_SI_XX_1</td><td>MAG_SI_XX_0</td></tr></table>


Table 285. MAG_SI_XX_L register description


<table><tr><td>MAG_SI_XX_[7:0]</td><td>Soft-iron correction row1 col1 coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 286. MAG_SI_XX_H register


<table><tr><td>MAG_SI_XX_15</td><td>MAG_SI_XX_14</td><td>MAG_SI_XX_13</td><td>MAG_SI_XX_12</td><td>MAG_SI_XX_11</td><td>MAG_SI_XX_10</td><td>MAG_SI_XX_9</td><td>MAG_SI_XX_8</td></tr></table>


Table 287. MAG_SI_XX_H register description


<table><tr><td>MAG_SI_XX_[15:8]</td><td>Soft-iron correction row1 col1 coefficient (MSbyte). Default value: 00111100</td></tr></table>

# 13.1.6

# MAG_SI_XY_L (C8h) and MAG_SI_XY_H (C9h)

Soft-iron (3x3 symmetric) matrix correction register (r/w). 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 288. MAG_SI_XY_L register


<table><tr><td>MAG_SI_XY_7</td><td>MAG_SI_XY_6</td><td>MAG_SI_XY_5</td><td>MAG_SI_XY_4</td><td>MAG_SI_XY_3</td><td>MAG_SI_XY_2</td><td>MAG_SI_XY_1</td><td>MAG_SI_XY_0</td></tr></table>


Table 289. MAG_SI_XY_L register description


<table><tr><td>MAG_SI_XY_[7:0]</td><td>Soft-iron correction row1 col2 (and row2 col1) coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 290. MAG_SI_XY_H register


<table><tr><td>MAG_SI_XY_15</td><td>MAG_SI_XY_14</td><td>MAG_SI_XY_13</td><td>MAG_SI_XY_12</td><td>MAG_SI_XY_11</td><td>MAG_SI_XY_10</td><td>MAG_SI_XY_9</td><td>MAG_SI_XY_8</td></tr></table>


Table 291. MAG_SI_XY_H register description


<table><tr><td>MAG_SI_XY_[15:8]</td><td>Soft-iron correction row1 col2 (and row2 col1) coefficient (MSbyte). Default value: 00000000</td></tr></table>

# 13.1.7

# MAG_SI_XZ_L (CAh) and MAG_SI_XZ_H (CBh)

Soft-iron (3x3 symmetric) matrix correction register (r/w). 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 292. MAG_SI_XZ_L register


<table><tr><td>MAG_SI_XZ_7</td><td>MAG_SI_XZ_6</td><td>MAG_SI_XZ_5</td><td>MAG_SI_XZ_4</td><td>MAG_SI_XZ_3</td><td>MAG_SI_XZ_2</td><td>MAG_SI_XZ_1</td><td>MAG_SI_XZ_0</td></tr></table>


Table 293. MAG_SI_XZ_L register description


<table><tr><td>MAG_SI_XZ_[7:0]</td><td>Soft-iron correction row1 col3 (and row3 col1) coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 294. MAG_SI_XZ_H register


<table><tr><td>MAG_SI_XZ_15</td><td>MAG_SI_XZ_14</td><td>MAG_SI_XZ_13</td><td>MAG_SI_XZ_12</td><td>MAG_SI_XZ_11</td><td>MAG_SI_XZ_10</td><td>MAG_SI_XZ_9</td><td>MAG_SI_XZ_8</td></tr></table>


Table 295. MAG_SI_XZ_H register description


<table><tr><td>MAG_SI_XZ_[15:8]</td><td>Soft-iron correction row1 col3 (and row3 col1) coefficient (MSbyte). Default value: 00000000</td></tr></table>

# 13.1.8 MAG_SI_YY_L (CCh) and MAG_SI_YY_H (CDh)

Soft-iron (3x3 symmetric) matrix correction register (r/w). 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 296. MAG_SI_YY_L register


<table><tr><td>MAG_SI_YY_7</td><td>MAG_SI_YY_6</td><td>MAG_SI_YY_5</td><td>MAG_SI_YY_4</td><td>MAG_SI_YY_3</td><td>MAG_SI_YY_2</td><td>MAG_SI_YY_1</td><td>MAG_SI_YY_0</td></tr></table>


Table 297. MAG_SI_YY_L register description


<table><tr><td>MAG_SI_YY_[7:0]</td><td>Soft-iron correction row2 col2 coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 298. MAG_SI_YY_H register


<table><tr><td>MAG_SI_YY_15</td><td>MAG_SI_YY_14</td><td>MAG_SI_YY_13</td><td>MAG_SI_YY_12</td><td>MAG_SI_YY_11</td><td>MAG_SI_YY_10</td><td>MAG_SI_YY_9</td><td>MAG_SI_YY_8</td></tr></table>


Table 299. MAG_SI_YY_H register description


<table><tr><td>MAG_SI_YY_[15:8]</td><td>Soft-iron correction row2 col2 coefficient (MSbyte). Default value: 00111100</td></tr></table>

# 13.1.9 MAG_SI_YZ_L (CEh) and MAG_SI_YZ_H (CFh)

Soft-iron (3x3 symmetric) matrix correction register (r/w). 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 300. MAG_SI_YZ_L register


<table><tr><td>MAG_SI_YZ_7</td><td>MAG_SI_YZ_6</td><td>MAG_SI_YZ_5</td><td>MAG_SI_YZ_4</td><td>MAG_SI_YZ_3</td><td>MAG_SI_YZ_2</td><td>MAG_SI_YZ_1</td><td>MAG_SI_YZ_0</td></tr></table>


Table 301. MAG_SI_YZ_L register description


<table><tr><td>MAG_SI_YZ_[7:0]</td><td>Soft-iron correction row2 col3 (and row3 col2) coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 302. MAG_SI_YZ_H register


<table><tr><td>MAG_SI_YZ_15</td><td>MAG_SI_YZ_14</td><td>MAG_SI_YZ_13</td><td>MAG_SI_YZ_12</td><td>MAG_SI_YZ_11</td><td>MAG_SI_YZ_10</td><td>MAG_SI_YZ_9</td><td>MAG_SI_YZ_8</td></tr></table>


Table 303. MAG_SI_YZ_H register description


<table><tr><td>MAG_SI_YZ_[15:8]</td><td>Soft-iron correction row2 col3 (and row3 col2) coefficient (MSbyte). Default value: 00000000</td></tr></table>

# 13.1.10 MAG_SI_ZZ_L (D0h) and MAG_SI_ZZ_H (D1h)

Soft-iron (3x3 symmetric) matrix correction register (r/w). 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 304. MAG_SI_ZZ_L register


<table><tr><td>MAG_SI_ZZ_7</td><td>MAG_SI_ZZ_6</td><td>MAG_SI_ZZ_5</td><td>MAG_SI_ZZ_4</td><td>MAG_SI_ZZ_3</td><td>MAG_SI_ZZ_2</td><td>MAG_SI_ZZ_1</td><td>MAG_SI_ZZ_0</td></tr></table>


Table 305. MAG_SI_ZZ_L register description


<table><tr><td>MAG_SI_ZZ_[7:0]</td><td>Soft-iron correction row3 col3 coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 306. MAG_SI_ZZ_H register


<table><tr><td>MAG_SI_ZZ_15</td><td>MAG_SI_ZZ_14</td><td>MAG_SI_ZZ_13</td><td>MAG_SI_ZZ_12</td><td>MAG_SI_ZZ_11</td><td>MAG_SI_ZZ_10</td><td>MAG_SI_ZZ_9</td><td>MAG_SI_ZZ_8</td></tr></table>


Table 307. MAG_SI_ZZ_H register description


<table><tr><td>MAG_SI_ZZ_[15:8]</td><td>Soft-iron correction row3 col3 coefficient (MSbyte). Default value: 00111100</td></tr></table>

# 13.1.11 MAG_CFG_A (D4h)

External magnetometer coordinates (Z and Y axes) rotation register (r/w) 


Table 308. MAG_CFG_A register


<table><tr><td><eq>0^{(1)}</eq></td><td>MAG_Y_AXIS2</td><td>MAG_Y_AXIS1</td><td>MAG_Y_AXIS0</td><td><eq>0^{(1)}</eq></td><td>MAG_Z_AXIS2</td><td>MAG_Z_AXIS1</td><td>MAG_Z_AXIS0</td></tr></table>


1. This bit must be set to ‘0’ for the correct operation of the device. 



Table 309. MAG_CFG_A register description


<table><tr><td>MAG_Y_AXIS[2:0]</td><td>Magnetometer Y-axis coordinates rotation (to be aligned to accelerometer/gyroscope axes orientation)(000: Y = Y; (default)001: Y = -Y;010: Y = X;011: Y = -X;100: Y = -Z;101: Y = Z;Others: Y = Y)</td></tr><tr><td>MAG_Z_AXIS[2:0]</td><td>Magnetometer Z-axis coordinates rotation (to be aligned to accelerometer/gyroscope axes orientation)(000: Z = Y;001: Z = -Y;010: Z = X;011: Z = -X;100: Z = -Z;101: Z = Z; (default)Others: Z = Y)</td></tr></table>

# 13.1.12 MAG_CFG_B (D5h)

External magnetometer coordinates (X-axis) rotation register (r/w) 


Table 310. MAG_CFG_B register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>MAG_X_AXIS2</td><td>MAG_X_AXIS1</td><td>MAG_X_AXIS0</td></tr></table>


1. This bit must be set to ‘0’ for the correct operation of the device. 



Table 311. MAG_CFG_B register description


<table><tr><td>MAG_X_AXIS[2:0]</td><td>Magnetometer X-axis coordinates rotation (to be aligned to accelerometer/gyroscope axes orientation)(000: X = Y;001: X = -Y;010: X = X; (default)011: X = -X;100: X = -Z;101: X = Z;Others: X = Y)</td></tr></table>

# 13.2 Page 1 - Embedded advanced features registers

# 13.2.1 FSM_LC_TIMEOUT_L (7Ah) and FSM_LC_TIMEOUT_H (7Bh)

FSM long counter timeout register (r/w). 

The long counter timeout value is an unsigned integer value (16-bit format). When the long counter value reaches this value, the FSM generates an interrupt. 


Table 312. FSM_LC_TIMEOUT_L register


<table><tr><td>FSM_LC_TIMEOUT7</td><td>FSM_LC_TIMEOUT6</td><td>FSM_LC_TIMEOUT5</td><td>FSM_LC_TIMEOUT4</td><td>FSM_LC_TIMEOUT3</td><td>FSM_LC_TIMEOUT2</td><td>FSM_LC_TIMEOUT1</td><td>FSM_LC_TIMEOUT0</td></tr></table>


Table 313. FSM_LC_TIMEOUT_L register description


<table><tr><td>FSM_LC_TIMEOUT[7:0]</td><td>FSM long counter timeout value (LSbyte). Default value: 00000000</td></tr></table>


Table 314. FSM_LC_TIMEOUT_H register


<table><tr><td>FSM_LC_TIMEOUT15</td><td>FSM_LC_TIMEOUT14</td><td>FSM_LC_TIMEOUT13</td><td>FSM_LC_TIMEOUT12</td><td>FSM_LC_TIMEOUT11</td><td>FSM_LC_TIMEOUT10</td><td>FSM_LC_TIMEOUT9</td><td>FSM_LC_TIMEOUT8</td></tr></table>


Table 315. FSM_LC_TIMEOUT_H register description


<table><tr><td>FSM_LC_TIMEOUT[15:8]</td><td>FSM long counter timeout value (MSbyte). Default value: 00000000</td></tr></table>

# 13.2.2 FSM_PROGRAMS (7Ch)

FSM number of programs register (r/w) 


Table 316. FSM_PROGRAMS register


<table><tr><td>FSM_N_PROG7</td><td>FSM_N_PROG6</td><td>FSM_N_PROG5</td><td>FSM_N_PROG4</td><td>FSM_N_PROG3</td><td>FSM_N_PROG2</td><td>FSM_N_PROG1</td><td>FSM_N_PROG0</td></tr></table>


Table 317. FSM_PROGRAMS register description


<table><tr><td>FSM_N_PROG[7:0]</td><td>Number of FSM programs; must be less than or equal to 16. Default value: 00000000</td></tr></table>

# 13.2.3 FSM_START_ADD_L (7Eh) and FSM_START_ADD_H (7Fh)

FSM start address register (r/w). First available address is 0x033C. 


Table 318. FSM_START_ADD_L register


<table><tr><td>FSM_START7</td><td>FSM_START6</td><td>FSM_START5</td><td>FSM_START4</td><td>FSM_START3</td><td>FSM_START2</td><td>FSM_START1</td><td>FSM_START0</td></tr></table>


Table 319. FSM_START_ADD_L register description


<table><tr><td>FSM_START[7:0]</td><td>FSM start address value (LSbyte). Default value: 00000000</td></tr></table>


Table 320. FSM_START_ADD_H register


<table><tr><td>FSM_START15</td><td>FSM_START14</td><td>FSM_START13</td><td>FSM_START12</td><td>FSM_START11</td><td>FSM_START10</td><td>FSM_START9</td><td>FSM_START8</td></tr></table>


Table 321. FSM_START_ADD_H register description


<table><tr><td>FSM_START[15:8]</td><td>FSM start address value (MSbyte). Default value: 00000000</td></tr></table>

# 13.2.4 PEDO_CMD_REG (83h)

Pedometer configuration register (r/w) 


Table 322. PEDO_CMD_REG register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>CARRY_COUNT_EN</td><td>FP_REJECTION_EN</td><td><eq>0^{(1)}</eq></td><td>AD_DET_EN</td></tr></table>


1. This bit must be set to '0' for the correct operation of the device. 



Table 323. PEDO_CMD_REG register description


<table><tr><td>CARRY_COUNT_EN</td><td>Set when user wants to generate interrupt only on count overflow event.</td></tr><tr><td>FP_REJECTION_EN<eq>^{(1)}</eq></td><td>Enables the false-positive rejection feature.</td></tr><tr><td>ADV_DET_EN<eq>^{(2)}</eq></td><td>Enables the advanced detection feature.</td></tr></table>


1. This bit is effective if the PEDO_ADV_EN bit of EMB_FUNC_EN_B (05h) is set to 1 and the PEDO_FPR_ADF_DIS bit of ADV_PEDO (03h) is set to 0. 



2. This bit is effective if the FP_REJECTION_EN bit in PEDO_CMD_REG (83h) is set to 1, the PEDO_ADV_EN bit of EMB_FUNC_EN_B (05h) is set to 1 and the PEDO_FPR_ADF_DIS bit of ADV_PEDO (03h) is set to 0. 


# 13.2.5 PEDO_DEB_CONF (84h)

Pedometer debounce configuration register (r/w) 


Table 324. PEDO_DEB_STEPS_CONF register


<table><tr><td>DEB_STEP7</td><td>DEB_STEP6</td><td>DEB_STEP5</td><td>DEB_STEP4</td><td>DEB_STEP3</td><td>DEB_STEP2</td><td>DEB_STEP1</td><td>DEB_STEP0</td></tr></table>


Table 325. PEDO_DEB_STEPS_CONF register description


<table><tr><td>DEB_STEP[7:0]</td><td>Debounce threshold. Minimum number of steps to increment the step counter (debounce).Default value: 00001010</td></tr></table>

# 13.2.6

# PEDO_SC_DELTAT_L (D0h) and PEDO_SC_DELTAT_H (D1h)

Time period register for step detection on delta time (r/w) 


Table 326. PEDO_SC_DELTAT_L register


<table><tr><td>PD_SC_7</td><td>PD_SC_6</td><td>PD_SC_5</td><td>PD_SC_4</td><td>PD_SC_3</td><td>PD_SC_2</td><td>PD_SC_1</td><td>PD_SC_0</td></tr></table>


Table 327. PEDO_SC_DELTAT_H register


<table><tr><td>PD_SC_15</td><td>PD_SC_14</td><td>PD_SC_13</td><td>PD_SC_12</td><td>PD_SC_11</td><td>PD_SC_10</td><td>PD_SC_9</td><td>PD_SC_8</td></tr></table>


Table 328. PEDO_SC_DELTAT_H/L register description


<table><tr><td>PD_SC_[15:0]</td><td>Time period value (1LSB = 6.4 ms)</td></tr></table>

# 14 Sensor hub register mapping

The table given below provides a list of the registers for the sensor hub functions available in the device and the corresponding addresses. The sensor hub registers are accessible when bit SHUB_REG_ACCESS is set to '1' in FUNC_CFG_ACCESS (01h). 


Table 329. Registers address map


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>SENSOR_HUB_1</td><td>R</td><td>02</td><td>00000010</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_2</td><td>R</td><td>03</td><td>00000011</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_3</td><td>R</td><td>04</td><td>00000100</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_4</td><td>R</td><td>05</td><td>00000101</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_5</td><td>R</td><td>06</td><td>00000110</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_6</td><td>R</td><td>07</td><td>00000111</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_7</td><td>R</td><td>08</td><td>00001000</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_8</td><td>R</td><td>09</td><td>00001001</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_9</td><td>R</td><td>0A</td><td>00001010</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_10</td><td>R</td><td>0B</td><td>00001011</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_11</td><td>R</td><td>0C</td><td>00001100</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_12</td><td>R</td><td>0D</td><td>00001101</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_13</td><td>R</td><td>0E</td><td>00001110</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_14</td><td>R</td><td>0F</td><td>00001111</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_15</td><td>R</td><td>10</td><td>00010000</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_16</td><td>R</td><td>11</td><td>00010001</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_17</td><td>R</td><td>12</td><td>00010010</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_18</td><td>R</td><td>13</td><td>00010011</td><td>output</td><td></td></tr><tr><td>MASTER_CONFIG</td><td>RW</td><td>14</td><td>00010100</td><td>00000000</td><td></td></tr><tr><td>SLV0_ADD</td><td>RW</td><td>15</td><td>00010101</td><td>00000000</td><td></td></tr><tr><td>SLV0_SUBADD</td><td>RW</td><td>16</td><td>00010110</td><td>00000000</td><td></td></tr><tr><td>SLV0_CONFIG</td><td>RW</td><td>17</td><td>00010111</td><td>00000000</td><td></td></tr><tr><td>SLV1_ADD</td><td>RW</td><td>18</td><td>00011000</td><td>00000000</td><td></td></tr><tr><td>SLV1_SUBADD</td><td>RW</td><td>19</td><td>00011001</td><td>00000000</td><td></td></tr><tr><td>SLV1_CONFIG</td><td>RW</td><td>1A</td><td>00011010</td><td>00000000</td><td></td></tr><tr><td>SLV2_ADD</td><td>RW</td><td>1B</td><td>00011011</td><td>00000000</td><td></td></tr><tr><td>SLV2_SUBADD</td><td>RW</td><td>1C</td><td>00011100</td><td>00000000</td><td></td></tr><tr><td>SLV2_CONFIG</td><td>RW</td><td>1D</td><td>00011101</td><td>00000000</td><td></td></tr><tr><td>SLV3_ADD</td><td>RW</td><td>1E</td><td>00011110</td><td>00000000</td><td></td></tr><tr><td>SLV3_SUBADD</td><td>RW</td><td>1F</td><td>00011111</td><td>00000000</td><td></td></tr><tr><td>SLV3_CONFIG</td><td>RW</td><td>20</td><td>00100000</td><td>00000000</td><td></td></tr><tr><td>DATAWRITE_SLV0</td><td>RW</td><td>21</td><td>00100001</td><td>00000000</td><td></td></tr><tr><td>STATUS_MASTER</td><td>R</td><td>22</td><td>00100010</td><td>output</td><td></td></tr></table>

Registers marked as Reserved must not be changed. Writing to those registers may cause permanent damage to the device. 

The content of the registers that are loaded at boot should not be changed. They contain the factory calibration values. Their content is automatically restored when the device is powered up. 

# 15 Sensor hub register description

# 15.1 SENSOR_HUB_1 (02h)

Sensor hub output register (r) 

First byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 330. SENSOR_HUB_1 register


<table><tr><td>SensorHub1_7</td><td>SensorHub1_6</td><td>SensorHub1_5</td><td>SensorHub1_4</td><td>SensorHub1_3</td><td>SensorHub1_2</td><td>SensorHub1_1</td><td>SensorHub1_0</td></tr></table>


Table 331. SENSOR_HUB_1 register description


<table><tr><td>SensorHub1[7:0]</td><td>First byte associated to external sensors</td></tr></table>

# 15.2 SENSOR_HUB_2 (03h)

Sensor hub output register (r) 

Second byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from $\mathsf { x } = 0 \mathrm { t } 0 \mathsf { x } = 3 )$ . 


Table 332. SENSOR_HUB_2 register


<table><tr><td>SensorHub2_7</td><td>SensorHub2_6</td><td>SensorHub2_5</td><td>SensorHub2_4</td><td>SensorHub2_3</td><td>SensorHub2_2</td><td>SensorHub2_1</td><td>SensorHub2_0</td></tr></table>


Table 333. SENSOR_HUB_2 register description


<table><tr><td>SensorHub2[7:0]</td><td>Second byte associated to external sensors</td></tr></table>

# 15.3 SENSOR_HUB_3 (04h)

Sensor hub output register (r) 

Third byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from ${ \sf x } = 0$ to x = 3). 


Table 334. SENSOR_HUB_3 register


<table><tr><td>SensorHub3_7</td><td>SensorHub3_6</td><td>SensorHub3_5</td><td>SensorHub3_4</td><td>SensorHub3_3</td><td>SensorHub3_2</td><td>SensorHub3_1</td><td>SensorHub3_0</td></tr></table>


Table 335. SENSOR_HUB_3 register description


<table><tr><td>SensorHub3[7:0]</td><td>Third byte associated to external sensors</td></tr></table>

# 15.4 SENSOR_HUB_4 (05h)

Sensor hub output register (r) 

Fourth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 336. SENSOR_HUB_4 register


<table><tr><td>SensorHub4_7</td><td>SensorHub4_6</td><td>SensorHub4_5</td><td>SensorHub4_4</td><td>SensorHub4_3</td><td>SensorHub4_2</td><td>SensorHub4_1</td><td>SensorHub4_0</td></tr></table>


Table 337. SENSOR_HUB_4 register description


<table><tr><td>SensorHub4[7:0]</td><td>Fourth byte associated to external sensors</td></tr></table>

# 15.5 SENSOR_HUB_5 (06h)

Sensor hub output register (r) 

Fifth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 338. SENSOR_HUB_5 register


<table><tr><td>SensorHub5_7</td><td>SensorHub5_6</td><td>SensorHub5_5</td><td>SensorHub5_4</td><td>SensorHub5_3</td><td>SensorHub5_2</td><td>SensorHub5_1</td><td>SensorHub5_0</td></tr></table>


Table 339. SENSOR_HUB_5 register description


<table><tr><td>SensorHub5[7:0]</td><td>Fifth byte associated to external sensors</td></tr></table>

# 15.6 SENSOR_HUB_6 (07h)

Sensor hub output register (r) 

Sixth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 340. SENSOR_HUB_6 register


<table><tr><td>SensorHub6_7</td><td>SensorHub6_6</td><td>SensorHub6_5</td><td>SensorHub6_4</td><td>SensorHub6_3</td><td>SensorHub6_2</td><td>SensorHub6_1</td><td>SensorHub6_0</td></tr></table>


Table 341. SENSOR_HUB_6 register description


<table><tr><td>SensorHub6[7:0]</td><td>Sixth byte associated to external sensors</td></tr></table>

# 15.7 SENSOR_HUB_7 (08h)

Sensor hub output register (r) 

Seventh byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 342. SENSOR_HUB_7 register


<table><tr><td>SensorHub7_7</td><td>SensorHub7_6</td><td>SensorHub7_5</td><td>SensorHub7_4</td><td>SensorHub7_3</td><td>SensorHub7_2</td><td>SensorHub7_1</td><td>SensorHub7_0</td></tr></table>


Table 343. SENSOR_HUB_7 register description


<table><tr><td>SensorHub7[7:0]</td><td>Seventh byte associated to external sensors</td></tr></table>

# 15.8 SENSOR_HUB_8 (09h)

Sensor hub output register (r) 

Eighth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 344. SENSOR_HUB_8 register


<table><tr><td>SensorHub8_7</td><td>SensorHub8_6</td><td>SensorHub8_5</td><td>SensorHub8_4</td><td>SensorHub8_3</td><td>SensorHub8_2</td><td>SensorHub8_1</td><td>SensorHub8_0</td></tr></table>


Table 345. SENSOR_HUB_8 register description


<table><tr><td>SensorHub8[7:0]</td><td>Eighth byte associated to external sensors</td></tr></table>

# 15.9 SENSOR_HUB_9 (0Ah)

Sensor hub output register (r) 

Ninth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 346. SENSOR_HUB_9 register


<table><tr><td>SensorHub9_7</td><td>SensorHub9_6</td><td>SensorHub9_5</td><td>SensorHub9_4</td><td>SensorHub9_3</td><td>SensorHub9_2</td><td>SensorHub9_1</td><td>SensorHub9_0</td></tr></table>


Table 347. SENSOR_HUB_9 register description


<table><tr><td>SensorHub9[7:0]</td><td>Ninth byte associated to external sensors</td></tr></table>

# 15.10 SENSOR_HUB_10 (0Bh)

Sensor hub output register (r) 

Tenth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from $\mathsf { x } = 0 \mathrm { t } 0 \mathsf { x } = 3 )$ . 


Table 348. SENSOR_HUB_10 register


<table><tr><td>SensorHub10_7</td><td>SensorHub10_6</td><td>SensorHub10_5</td><td>SensorHub10_4</td><td>SensorHub10_3</td><td>SensorHub10_2</td><td>SensorHub10_1</td><td>SensorHub10_0</td></tr></table>


Table 349. SENSOR_HUB_10 register description


<table><tr><td>SensorHub10[7:0]</td><td>Tenth byte associated to external sensors</td></tr></table>

# 15.11 SENSOR_HUB_11 (0Ch)

Sensor hub output register (r) 

Eleventh byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 350. SENSOR_HUB_11 register


<table><tr><td>SensorHub11_7</td><td>SensorHub11_6</td><td>SensorHub11_5</td><td>SensorHub11_4</td><td>SensorHub11_3</td><td>SensorHub11_2</td><td>SensorHub11_1</td><td>SensorHub11_0</td></tr></table>


Table 351. SENSOR_HUB_11 register description


<table><tr><td>SensorHub11[7:0]</td><td>Eleventh byte associated to external sensors</td></tr></table>

# 15.12 SENSOR_HUB_12 (0Dh)

Sensor hub output register (r) 

Twelfth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from ${ \sf x } = 0$ to x = 3). 


Table 352. SENSOR_HUB_12 register


<table><tr><td>SensorHub12_7</td><td>SensorHub12_6</td><td>SensorHub12_5</td><td>SensorHub12_4</td><td>SensorHub12_3</td><td>SensorHub12_2</td><td>SensorHub12_1</td><td>SensorHub12_0</td></tr></table>


Table 353. SENSOR_HUB_12 register description


<table><tr><td>SensorHub12[7:0]</td><td>Twelfth byte associated to external sensors</td></tr></table>

# 15.13 SENSOR_HUB_13 (0Eh)

Sensor hub output register (r) 

Thirteenth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from ${ \sf x } = 0$ to $\mathsf { x } = 3 )$ . 


Table 354. SENSOR_HUB_13 register


<table><tr><td>SensorHub13_7</td><td>SensorHub13_6</td><td>SensorHub13_5</td><td>SensorHub13_4</td><td>SensorHub13_3</td><td>SensorHub13_2</td><td>SensorHub13_1</td><td>SensorHub13_0</td></tr></table>


Table 355. SENSOR_HUB_13 register description


<table><tr><td>SensorHub13[7:0]</td><td>Thirteenth byte associated to external sensors</td></tr></table>

# 15.14 SENSOR_HUB_14 (0Fh)

Sensor hub output register (r) 

Fourteenth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from ${ \sf x } = 0$ to $\mathsf { x } = 3 )$ . 


Table 356. SENSOR_HUB_14 register


<table><tr><td>SensorHub14_7</td><td>SensorHub14_6</td><td>SensorHub14_5</td><td>SensorHub14_4</td><td>SensorHub14_3</td><td>SensorHub14_2</td><td>SensorHub14_1</td><td>SensorHub14_0</td></tr></table>


Table 357. SENSOR_HUB_14 register description


<table><tr><td>SensorHub14[7:0]</td><td>Fourteenth byte associated to external sensors</td></tr></table>

# 15.15 SENSOR_HUB_15 (10h)

Sensor hub output register (r) 

Fifteenth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from ${ \sf x } = 0$ to x = 3). 


Table 358. SENSOR_HUB_15 register


<table><tr><td>SensorHub15_7</td><td>SensorHub15_6</td><td>SensorHub15_5</td><td>SensorHub15_4</td><td>SensorHub15_3</td><td>SensorHub15_2</td><td>SensorHub15_1</td><td>SensorHub15_0</td></tr></table>


Table 359. SENSOR_HUB_15 register description


<table><tr><td>SensorHub15[7:0]</td><td>Fifteenth byte associated to external sensors</td></tr></table>

# 15.16 SENSOR_HUB_16 (11h)

Sensor hub output register (r) 

Sixteenth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 360. SENSOR_HUB_16 register


<table><tr><td>SensorHub16_7</td><td>SensorHub16_6</td><td>SensorHub16_5</td><td>SensorHub16_4</td><td>SensorHub16_3</td><td>SensorHub16_2</td><td>SensorHub16_1</td><td>SensorHub16_0</td></tr></table>


Table 361. SENSOR_HUB_16 register description


<table><tr><td>SensorHub16[7:0]</td><td>Sixteenth byte associated to external sensors</td></tr></table>

# 15.17 SENSOR_HUB_17 (12h)

Sensor hub output register (r) 

Seventeenth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 362. SENSOR_HUB_17 register


<table><tr><td>SensorHub17_7</td><td>SensorHub17_6</td><td>SensorHub17_5</td><td>SensorHub17_4</td><td>SensorHub17_3</td><td>SensorHub17_2</td><td>SensorHub17_1</td><td>SensorHub17_0</td></tr></table>


Table 363. SENSOR_HUB_17 register description


<table><tr><td>SensorHub17[7:0]</td><td>Seventeenth byte associated to external sensors</td></tr></table>

# 15.18 SENSOR_HUB_18 (13h)

Sensor hub output register (r) 

Eighteenth byte associated to external sensors. The content of the register is consistent with the SLAVEx_CONFIG number of read operation configurations (for external sensors from ${ \sf x } = 0$ to x = 3). 


Table 364. SENSOR_HUB_18 register


<table><tr><td>SensorHub18_7</td><td>SensorHub18_6</td><td>SensorHub18_5</td><td>SensorHub18_4</td><td>SensorHub18_3</td><td>SensorHub18_2</td><td>SensorHub18_1</td><td>SensorHub18_0</td></tr></table>


Table 365. SENSOR_HUB_18 register description


<table><tr><td>SensorHub18[7:0]</td><td>Eighteenth byte associated to external sensors</td></tr></table>

# 15.19 MASTER_CONFIG (14h)

Master configuration register (r/w) 


Table 366. MASTER_CONFIG register


<table><tr><td>RST_MASTER_REGS</td><td>WRITE_ONCE</td><td>START_CONFIG</td><td>PASS_THROUGH_MODE</td><td>SHUB_PU_EN</td><td>MASTER_ON</td><td>AUX_SENS_ON1</td><td>AUX_SENS_ON0</td></tr></table>


Table 367. MASTER_CONFIG register description


<table><tr><td>RST_MASTER_REGS</td><td>Reset Master logic and output registers. Must be set to ‘1’ and then set it to ‘0’. Default value: 0</td></tr><tr><td>WRITE_ONCE</td><td>Slave 0 write operation is performed only at the first sensor hub cycle.Default value: 0(0: write operation for each sensor hub cycle;1: write operation only for the first sensor hub cycle)</td></tr><tr><td>START_CONFIG</td><td>Sensor hub trigger signal selection. Default value: 0(0: sensor hub trigger signal is the accelerometer/gyro data-ready;1: sensor hub trigger signal external from INT2 pin)</td></tr><tr><td>PASS_THROUGH_MODE</td><td>I2C interface pass-through. Default value: 0(0: pass-through disabled;1: pass-through enabled, main I2C line is short-circuited with the auxiliary line)</td></tr><tr><td>SHUB_PU_EN</td><td>Master I2C pull-up enable. Default value: 0(0: internal pull-up on auxiliary I2C line disabled;1: internal pull-up on auxiliary I2C line enabled)</td></tr><tr><td>MASTER_ON</td><td>Sensor hub I2C master enable. Default: 0(0: master I2C of sensor hub disabled; 1: master I2C of sensor hub enabled)</td></tr><tr><td>AUX_SENS_ON[1:0]</td><td>Number of external sensors to be read by the sensor hub.(00: one sensor (default);01: two sensors;10: three sensors;11: four sensors)</td></tr></table>

# 15.20 SLV0_ADD (15h)

I²C slave address of the first external sensor (Sensor 1) register (r/w) 


Table 368. SLV0_ADD register


<table><tr><td>slave0_add6</td><td>slave0_add5</td><td>slave0_add4</td><td>slave0_add3</td><td>slave0_add2</td><td>slave0_add1</td><td>slave0_add0</td><td>rw_0</td></tr></table>


Table 369. SLV0_ADD register description


<table><tr><td>slave0_add[6:0]</td><td>I2C slave address of Sensor1 that can be read by the sensor hub.Default value: 0000000</td></tr><tr><td>rw_0</td><td>Read/write operation on Sensor 1. Default value: 0(0: write operation; 1: read operation)</td></tr></table>

# 15.21 SLV0_SUBADD (16h)

Address of register on the first external sensor (Sensor 1) register (r/w) 


Table 370. SLV0_SUBADD register


<table><tr><td>slave0_reg7</td><td>slave0_reg6</td><td>slave0_reg5</td><td>slave0_reg4</td><td>slave0_reg3</td><td>slave0_reg2</td><td>slave0_reg1</td><td>slave0_reg0</td></tr></table>


Table 371. SLV0_SUBADD register description


<table><tr><td>slave0_reg[7:0]</td><td>Address of register on Sensor1 that has to be read/written according to the rw_0 bit value in SLV0_ADD (15h). Default value: 00000000</td></tr></table>

# 15.22 SLAVE0_CONFIG (17h)

First external sensor (Sensor1) configuration and sensor hub settings register (r/w) 


Table 372. SLAVE0_CONFIG register


<table><tr><td>SHUB_ODR_1</td><td>SHUB_ODR_0</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>BATCH_EXT_SENS_0_EN</td><td>Slave0_numop2</td><td>Slave0_numop1</td><td>Slave0_numop0</td></tr></table>


1. This bit must be set to ‘0’ for the correct operation of the device. 



Table 373. SLAVE0_CONFIG register description


<table><tr><td>SHUB_ODR_[1:0]</td><td>Rate at which the master communicates. Default value: 00(00: 104 Hz (or at the maximum ODR between the accelerometer and gyro if it is less than 104 Hz);01: 52 Hz (or at the maximum ODR between the accelerometer and gyro if it is less than 52 Hz);10: 26 Hz (or at the maximum ODR between the accelerometer and gyro if it is less than 26 Hz);11: 12.5 Hz (or at the maximum ODR between the accelerometer and gyro if it is less than 12.5 Hz)</td></tr><tr><td>BATCH_EXT_SENS_0_EN</td><td>Enable FIFO data batching of first slave. Default value: 0</td></tr><tr><td>Slave0_numop[2:0]</td><td>Number of read operations on Sensor 1. Default value: 000</td></tr></table>

# 15.23 SLV1_ADD (18h)

I²C slave address of the second external sensor (Sensor 2) register (r/w) 


Table 374. SLV1_ADD register


<table><tr><td>Slave1_add6</td><td>Slave1_add5</td><td>Slave1_add4</td><td>Slave1_add3</td><td>Slave1_add2</td><td>Slave1_add1</td><td>Slave1_add0</td><td>r_1</td></tr></table>


Table 375. SLV1_ADD register description


<table><tr><td>Slave1_add[6:0]</td><td>I2C slave address of Sensor 2 that can be read by the sensor hub.Default value: 0000000</td></tr><tr><td>r_1</td><td>Read operation on Sensor 2 enable. Default value: 0(0: read operation disabled; 1: read operation enabled)</td></tr></table>

# 15.24 SLV1_SUBADD (19h)

Address of register on the second external sensor (Sensor 2) register (r/w) 


Table 376. SLV1_SUBADD register


<table><tr><td>Slave1_reg7</td><td>Slave1_reg6</td><td>Slave1_reg5</td><td>Slave1_reg4</td><td>Slave1_reg3</td><td>Slave1_reg2</td><td>Slave1_reg1</td><td>Slave1_reg0</td></tr></table>


Table 377. SLV1_SUBADD register description


<table><tr><td>Slave1_reg[7:0]</td><td>Address of register on Sensor 2 that has to be read/written according to the r_1 bit value in SLV1_ADD (18h).</td></tr></table>

# 15.25 SLAVE1_CONFIG (1Ah)

Second external sensor (Sensor 2) configuration register (r/w) 


Table 378. SLAVE1_CONFIG register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>BATCH_EXT_SENS_1_EN</td><td>Slave1_numop2</td><td>Slave1_numop1</td><td>Slave1_numop0</td></tr></table>


1. This bit must be set to ‘0’ for the correct operation of the device. 



Table 379. SLAVE1_CONFIG register description


<table><tr><td>BATCH_EXT_SENS_1_EN</td><td>Enable FIFO data batching of second slave. Default value: 0</td></tr><tr><td>Slave1_numop[2:0]</td><td>Number of read operations on Sensor 2. Default value: 000</td></tr></table>

# 15.26 SLV2_ADD (1Bh)

I²C slave address of the third external sensor (Sensor 3) register (r/w) 


Table 380. SLV2_ADD register


<table><tr><td>Slave2_add6</td><td>Slave2_add5</td><td>Slave2_add4</td><td>Slave2_add3</td><td>Slave2_add2</td><td>Slave2_add1</td><td>Slave2_add0</td><td>r_2</td></tr></table>


Table 381. SLV2_ADD register description


<table><tr><td>Slave2_add[6:0]</td><td>I2C slave address of Sensor 3 that can be read by the sensor hub.</td></tr><tr><td>r_2</td><td>Read operation on Sensor 3 enable. Default value: 0(0: read operation disabled; 1: read operation enabled)</td></tr></table>

# 15.27 SLV2_SUBADD (1Ch)

Address of register on the third external sensor (Sensor 3) register (r/w) 


Table 382. SLV2_SUBADD register


<table><tr><td>Slave2_reg7</td><td>Slave2_reg6</td><td>Slave2_reg5</td><td>Slave2_reg4</td><td>Slave2_reg3</td><td>Slave2_reg2</td><td>Slave2_reg1</td><td>Slave2_reg0</td></tr></table>


Table 383. SLV2_SUBADD register description


<table><tr><td>Slave2_reg[7:0]</td><td>Address of register on Sensor 3 that has to be read/written according to the r_2 bit value in SLV2_ADD (1Bh).</td></tr></table>

# 15.28 SLAVE2_CONFIG (1Dh)

Third external sensor (Sensor 3) configuration register (r/w) 


Table 384. SLAVE2_CONFIG register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>BATCH_EXT_SENS_2_EN</td><td>Slave2_numop2</td><td>Slave2_numop1</td><td>Slave2_numop0</td></tr></table>

1. This bit must be set to ‘0’ for the correct operation of the device. 


Table 385. SLAVE2_CONFIG register description


<table><tr><td>BATCH_EXT_SENS_2_EN</td><td>Enable FIFO data batching of third slave. Default value: 0</td></tr><tr><td>Slave2_numop[2:0]</td><td>Number of read operations on Sensor 3. Default value: 000</td></tr></table>

# 15.29 SLV3_ADD (1Eh)

I²C slave address of the fourth external sensor (Sensor 4) register (r/w) 


Table 386. SLV3_ADD register


<table><tr><td>Slave3_add6</td><td>Slave3_add5</td><td>Slave3_add4</td><td>Slave3_add3</td><td>Slave3_add2</td><td>Slave3_add1</td><td>Slave3_add0</td><td>r_3</td></tr></table>


Table 387. SLV3_ADD register description


<table><tr><td>Slave3_add[6:0]</td><td>I2C slave address of Sensor 4 that can be read by the sensor hub.</td></tr><tr><td>r_3</td><td>Read operation on Sensor 4 enable. Default value: 0(0: read operation disabled; 1: read operation enabled)</td></tr></table>

# 15.30 SLV3_SUBADD (1Fh)

Address of register on the fourth external sensor (Sensor 4) register (r/w) 


Table 388. SLV3_SUBADD register


<table><tr><td>Slave3_reg7</td><td>Slave3_reg6</td><td>Slave3_reg5</td><td>Slave3_reg4</td><td>Slave3_reg3</td><td>Slave3_reg2</td><td>Slave3_reg1</td><td>Slave3_reg0</td></tr></table>


Table 389. SLV3_SUBADD register description


<table><tr><td>Slave3_reg[7:0]</td><td>Address of register on Sensor 4 that has to be read according to the r_3 bit value in SLV3_ADD (1Eh).</td></tr></table>

# 15.31 SLAVE3_CONFIG (20h)

Fourth external sensor (Sensor 4) configuration register (r/w) 


Table 390. SLAVE3_CONFIG register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>BATCH_EXT_SENS_3_EN</td><td>Slave3_numop2</td><td>Slave3_numop1</td><td>Slave3_numop0</td></tr></table>


1. This bit must be set to ‘0’ for the correct operation of the device. 



Table 391. SLAVE3_CONFIG register description


<table><tr><td>BATCH_EXT_SENS_3_EN</td><td>Enable FIFO data batching of fourth slave. Default value: 0</td></tr><tr><td>Slave3_numop[2:0]</td><td>Number of read operations on Sensor 4. Default value: 000</td></tr></table>

# 15.32 DATAWRITE_SLV0 (21h)

Data to be written into the slave device register (r/w) 


Table 392. DATAWRITE_SLV0 register


<table><tr><td>Slave0_dataw7</td><td>Slave0_dataw6</td><td>Slave0_dataw5</td><td>Slave0_dataw4</td><td>Slave0_dataw3</td><td>Slave0_dataw2</td><td>Slave0_dataw1</td><td>Slave0_dataw0</td></tr></table>


Table 393. DATAWRITE_SLV0 register description


<table><tr><td>Slave0_dataw[7:0]</td><td>Data to be written into the slave 0 device according to the rw_0 bit in register SLV0_ADD (15h).Default value: 00000000</td></tr></table>

# 15.33 STATUS_MASTER (22h)

Sensor hub source register (r) 


Table 394. STATUS_MASTER register


<table><tr><td>WR_ONCE_DONE</td><td>SLAVE3_NACK</td><td>SLAVE2_NACK</td><td>SLAVE1_NACK</td><td>SLAVE0_NACK</td><td>0</td><td>0</td><td>SENS_HUB_ENDOP</td></tr></table>


Table 395. STATUS_MASTER register description


<table><tr><td>WR_ONCE_DONE</td><td>When the bit WRITE_ONCE in MASTER_CONFIG (14h) is configured as 1, this bit is set to 1 when the write operation on slave 0 has been performed and completed. Default value: 0</td></tr><tr><td>SLAVE3_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 3 communication. Default value: 0</td></tr><tr><td>SLAVE2_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 2 communication. Default value: 0</td></tr><tr><td>SLAVE1_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 1 communication. Default value: 0</td></tr><tr><td>SLAVE0_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 0 communication. Default value: 0</td></tr><tr><td>SENS_HUB_ENDOP</td><td>Sensor hub communication status. Default value: 0(0: sensor hub communication not concluded;1: sensor hub communication concluded)</td></tr></table>

# 16 Soldering information

The LGA package is compliant with the ECOPACK, RoHS and "Green" standard. It is qualified for soldering heat resistance according to JEDEC J-STD-020. Land pattern and soldering recommendations are available at www.st.com/mems. 

# 17 Package information

In order to meet environmental requirements, ST offers these devices in different grades of ECOPACK packages, depending on their level of environmental compliance. ECOPACK specifications, grade definitions and product status are available at: www.st.com. ECOPACK is an ST trademark. 

# 17.1 LGA-14L package information


Figure 26. LGA-14L 2.5 x 3.0 x 0.86 mm package outline and mechanical data


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/0b0e7ebf5673a18535cc185d70c5266f0da1eed94544c3a2478ddc0eecc1c8cc.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/71bf7cf2e088d312f53006e6849951054d0cf4d55f5fdead5f6c516aaec265fc.jpg)



Dimensions are in millimeter unless otherwise specified General tolerance is +/-0.1mm unless otherwise specified



OUTER DIMENSIONS


<table><tr><td>ITEM</td><td>DIMENSION [mm]</td><td>TOLERANCE [mm]</td></tr><tr><td>Length [L]</td><td>2.50</td><td>±0.1</td></tr><tr><td>Width [W]</td><td>3.00</td><td>±0.1</td></tr><tr><td>Height [H]</td><td>0.86</td><td>MAX</td></tr></table>

DM00249496_1 

# 17.2 LGA-14 packing information


Figure 27. Carrier tape information for LGA-14 package


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/20ee2d6be78941a3783c0a1b4c563228159dbfccfd2ab72d9b4772966c2f2c27.jpg)


<table><tr><td>Ao</td><td>2.80</td><td>+/- 0.05</td></tr><tr><td>Bo</td><td>3.30</td><td>+/- 0.05</td></tr><tr><td>Ko</td><td>1.00</td><td>+/- 0.10</td></tr><tr><td>F</td><td>5.50</td><td>+/- 0.05</td></tr><tr><td>P1</td><td>8.00</td><td>+/- 0.10</td></tr><tr><td>W</td><td>12.00</td><td>+/- 0.30</td></tr></table>


Forming format:Pressform-17-8 Required length:170meter/22B3reel 



Cumulative toleranceof 10 sprocket holesis±0.20 



（) Measured trom centreline of sprocket hole to centreline ot pocket. 



(IV)Other material available. 



ALLDIMENSIONS INMILLIMETRES UNLESS OTHERWISESTATED 



Figure 28. LGA-14 package orientation in carrier tape


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/69803102e0819197a49bac4c061e53277c2518642b99f2affb528c45d0f5e07d.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/9025c8c743ea46e4958f9e720d400cc4f6943b78682db681e2bc60eaafdd5d98.jpg)



Figure 29. Reel information for carrier tape of LGA-14 package


![image](https://cdn-mineru.openxlab.org.cn/result/2026-05-24/d523aa31-0329-4898-bd0b-3cddb0c9e73e/df1f379874e0d9638e77d9285846733217b43ec99bcac6911a05be863933edbb.jpg)



Table 396. Reel dimensions for carrier tape of LGA-14 package


<table><tr><td colspan="2">Reel dimensions (mm)</td></tr><tr><td>A (max)</td><td>330</td></tr><tr><td>B (min)</td><td>1.5</td></tr><tr><td>C</td><td>13 ±0.25</td></tr><tr><td>D (min)</td><td>20.2</td></tr><tr><td>N (min)</td><td>60</td></tr><tr><td>G</td><td>12.4 +2/-0</td></tr><tr><td>T (max)</td><td>18.4</td></tr></table>

# Revision history


Table 397. Document revision history


<table><tr><td>Date</td><td>Version</td><td>Changes</td></tr><tr><td>25-Mar-2019</td><td>1</td><td>Initial release</td></tr><tr><td>18-Nov-2020</td><td>2</td><td>Updated linear acceleration self-test output change in Table 2. Mechanical characteristicsUpdated Table 6. I2C slave timing valuesUpdate Note below Figure 5 and Figure 6Updated Figure 19 and Figure 20Updated Table 50. Accelerometer ODR selectionUpdated description of bit 7 in TAP_THS_6D (59h)Updated description of bits in INT_DUR2 (5Ah)Updated bit 0 in I3C_BUS_AVB (62h)</td></tr></table>

# Contents

# 1 Overview . 3

# 2 Embedded low-power features

2.1 Tilt detection. 4 

2.2 Significant Motion Detection 4 

2.3 Finite State Machine . . 5 

# 3 Pin description .6

3.1 Pin connections . 

# 4 Module specifications 9

4.1 Mechanical characteristics . 9 

4.2 Electrical characteristics. 11 

4.3 Temperature sensor characteristics 11 

4.4 Communication interface characteristics 12 

4.4.1 SPI - serial peripheral interface . 12 

4.4.2 I²C - inter-IC control interface 13 

4.5 Absolute maximum ratings. 14 

4.6 Terminology . . 15 

4.6.1 Sensitivity . 15 

4.6.2 Zero-g and zero-rate level. 15 

# 5 Digital interfaces .16

5.1 I²C/SPI interface . 16 

5.1.1 I²C serial interface . 16 

5.1.2 SPI bus interface. 19 

5.2 MIPI I3CSM interface. . 23 

5.2.1 MIPI I3CSM slave interface . 23 

5.2.2 MIPI I3CSM CCC supported commands . 23 

5.3 I²C/I3C coexistence in LSM6DSR . . 25 

5.4 Master I²C interface . 26 

5.5 Auxiliary SPI interface. . 26 

# 6 Functionality .27

6.1 Operating modes. . 27 

6.2 Gyroscope power modes . 27 

6.3 Accelerometer power modes . 27 

6.4 Block diagram of filters . . 27 

6.4.1 Block diagrams of the accelerometer filters. . 28 

6.4.2 Block diagrams of the gyroscope filters. . 29 

6.5 OIS . 31 

6.6 FIFO . 32 

6.6.1 Bypass mode 33 

6.6.2 FIFO mode . 33 

6.6.3 Continuous mode . 33 

6.6.4 Continuous-to-FIFO mode. . 33 

6.6.5 Bypass-to-Continuous mode . . 33 

6.6.6 Bypass-to-FIFO mode. 34 

6.6.7 FIFO reading procedure 34 

# 7 Application hints .35

7.1 LSM6DSR electrical connections in Mode 1 35 

7.2 LSM6DSR electrical connections in Mode 2 36 

7.3 LSM6DSR electrical connections in Mode 3 and Mode 4 37 

# 8 Register mapping. .40

# 9 Register description . .43

9.1 FUNC_CFG_ACCESS (01h) . . 43 

9.2 PIN_CTRL (02h) . 43 

9.3 S4S_TPH_L (04h). 44 

9.4 S4S_TPH_H (05h) . 44 

9.5 S4S_RR (06h) . . 44 

9.6 FIFO_CTRL1 (07h) . . 45 

9.7 FIFO_CTRL2 (08h) . . 45 

9.8 FIFO_CTRL3 (09h) . . 46 

9.9 FIFO_CTRL4 (0Ah). 47 

9.10 COUNTER_BDR_REG1 (0Bh) . . 48 

9.11 COUNTER_BDR_REG2 (0Ch) . . 48 

9.12 INT1_CTRL (0Dh). . 49 

9.13 INT2_CTRL (0Eh) . . 50 

9.14 WHO_AM_I (0Fh) . . 50 

9.15 CTRL1_XL (10h) . . 51 

9.16 CTRL2_G (11h) . . 52 

9.17 CTRL3_C (12h) . . 53 

9.18 CTRL4_C (13h) . . 54 

9.19 CTRL5_C (14h) . . 55 

9.20 CTRL6_C (15h) . . 56 

9.21 CTRL7_G (16h). . 57 

9.22 CTRL8_XL (17h) . . 58 

9.23 CTRL9_XL (18h) . . 60 

9.24 CTRL10_C (19h). . 60 

9.25 ALL_INT_SRC (1A) . 61 

9.26 WAKE_UP_SRC (1Bh). . 62 

9.27 TAP_SRC (1Ch) . 63 

9.28 DRD_SRC (1Dh). . 64 

9.29 STATUS_REG (1Eh) / STATUS_SPIAux (1Eh). . 65 

9.30 OUT_TEMP_L (20h), OUT_TEMP_H (21h). . 66 

9.31 OUTX_L_G (22h) and OUTX_H_G (23h) . 66 

9.32 OUTY_L_G (24h) and OUTY_H_G (25h) . 67 

9.33 OUTZ_L_G (26h) and OUTZ_H_G (27h). . 67 

9.34 OUTX_L_A (28h) and OUTX_H_A (29h) . . 68 

9.35 OUTY_L_A (2Ah) and OUTY_H_A (2Bh) . 68 

9.36 OUTZ_L_A (2Ch) and OUTZ_H_A (2Dh) . 69 

9.37 EMB_FUNC_STATUS_MAINPAGE (35h) . 69 

9.38 FSM_STATUS_A_MAINPAGE (36h) . 70 

9.39 FSM_STATUS_B_MAINPAGE (37h) 70 

9.40 STATUS_MASTER_MAINPAGE (39h). 71 

9.41 FIFO_STATUS1 (3Ah) . 72 

9.42 FIFO_STATUS2 (3Bh) . 72 

9.43 TIMESTAMP0 (40h), TIMESTAMP1 (41h), TIMESTAMP2 (42h), and TIMESTAMP3 (43h) 73 

9.44 TAP_CFG0 (56h). . 74 

9.45 TAP_CFG1 (57h). . 75 

9.46 TAP_CFG2 (58h). . 75 

9.47 TAP_THS_6D (59h) . 76 

9.48 INT_DUR2 (5Ah). . 76 

9.49 WAKE_UP_THS (5Bh) . 77 

9.50 WAKE_UP_DUR (5Ch) 77 

9.51 FREE_FALL (5Dh) . 78 

9.52 MD1 _CFG (5Eh) . . 79 

9.53 MD2_CFG (5Fh) . 80 

9.54 S4S_ST_CMD_CODE (60h) . . 81 

9.55 S4S_DT_REG (61h) . . 81 

9.56 I3C_BUS_AVB (62h). . 81 

9.57 INTERNAL_FREQ_FINE (63h) . . 82 

9.58 INT_OIS (6Fh) . . 83 

9.59 CTRL1_OIS (70h) . . 84 

9.60 CTRL2_OIS (71h) . . 85 

9.61 CTRL3_OIS (72h) . . 86 

9.62 X_OFS_USR (73h) . . 87 

9.63 Y_OFS_USR (74h) . . 87 

9.64 Z_OFS_USR (75h) . . 87 

9.65 FIFO_DATA_OUT_TAG (78h) . . 88 

9.66 FIFO_DATA_OUT_X_L (79h) and FIFO_DATA_OUT_X_H (7Ah) . 89 

9.67 FIFO_DATA_OUT_Y_L (7Bh) and FIFO_DATA_OUT_Y_H (7Ch) . . 89 

9.68 FIFO_DATA_OUT_Z_L (7Dh) and FIFO_DATA_OUT_Z_H (7Eh) . . 89 

10 Embedded functions register mapping . .90 

11 Embedded functions register description .92 

11.1 PAGE_SEL (02h) . 92 

11.2 ADV_PEDO (03h) . . 92 

11.3 EMB_FUNC_EN_A (04h). . 93 

11.4 EMB_FUNC_EN_B (05h). . 93 

11.5 PAGE_ADDRESS (08h). . 94 

11.6 PAGE_VALUE (09h) . . 94 

11.7 EMB_FUNC_INT1 (0Ah) . 95 

11.8 FSM_INT1_A (0Bh) . 96 

11.9 FSM_INT1_B (0Ch) . 97 

11.10 EMB_FUNC_INT2 (0Eh) . 98 

11.11 FSM_INT2_A (0Fh). . 99 

11.12 FSM_INT2_B (10h). . 100 

11.13 EMB_FUNC_STATUS (12h) .101 

11.14 FSM_STATUS_A (13h). .101 

11.15 FSM_STATUS_B (14h). . . 102 

11.16 PAGE_RW (17h) . .103 

11.17 EMB_FUNC_FIFO_CFG (44h) .103 

11.18 FSM_ENABLE_A (46h) .104 

11.19 FSM_ENABLE_B (47h) .104 

11.20 FSM_LONG_COUNTER_L (48h) and FSM_LONG_COUNTER_H (49h). .105 

11.21 FSM_LONG_COUNTER_CLEAR (4Ah) .105 

11.22 FSM_OUTS1 (4Ch) . 106 

11.23 FSM_OUTS2 (4Dh) . 106 

11.24 FSM_OUTS3 (4Eh). .107 

11.25 FSM_OUTS4 (4Fh). .107 

11.26 FSM_OUTS5 (50h) . .108 

11.27 FSM_OUTS6 (51h) . .108 

11.28 FSM_OUTS7 (52h) . .109 

11.29 FSM_OUTS8 (53h) . .109 

11.30 FSM_OUTS9 (54h) . 110 

11.31 FSM_OUTS10 (55h). 110 

11.32 FSM_OUTS11 (56h) . 111 

11.33 FSM_OUTS12 (57h). 111 

11.34 FSM_OUTS13 (58h). 112 

11.35 FSM_OUTS14 (59h). 112 

11.36 FSM_OUTS15 (5Ah) . 113 

11.37 FSM_OUTS16 (5Bh) 113 

11.38 EMB_FUNC_ODR_CFG_B (5Fh). 114 

11.39 STEP_COUNTER_L (62h) and STEP_COUNTER_H (63h) . 115 

11.40 EMB_FUNC_SRC (64h). . 116 

11.41 EMB_FUNC_INIT_A (66h). 116 

11.42 EMB_FUNC_INIT_B (67h). 117 

12 Embedded advanced features pages . 118 

13 Embedded advanced features register description 121 

13.1 Page 0 - Embedded advanced features registers. .121 

13.1.1 MAG_SENSITIVITY_L (BAh) and MAG_SENSITIVITY_H (BBh) 121 

13.1.2 MAG_OFFX_L (C0h) and MAG_OFFX_H (C1h). . 122 

13.1.3 MAG_OFFY_L (C2h) and MAG_OFFY_H (C3h). 122 

13.1.4 MAG_OFFZ_L (C4h) and MAG_OFFZ_H (C5h) . 123 

13.1.5 MAG_SI_XX_L (C6h) and MAG_SI_XX_H (C7h) . 123 

13.1.6 MAG_SI_XY_L (C8h) and MAG_SI_XY_H (C9h) . 124 

13.1.7 MAG_SI_XZ_L (CAh) and MAG_SI_XZ_H (CBh) . 124 

13.1.8 MAG_SI_YY_L (CCh) and MAG_SI_YY_H (CDh) 125 

13.1.9 MAG_SI_YZ_L (CEh) and MAG_SI_YZ_H (CFh) . 125 

13.1.10 MAG_SI_ZZ_L (D0h) and MAG_SI_ZZ_H (D1h) 126 

13.1.11 MAG_CFG_A (D4h) 127 

13.1.12 MAG_CFG_B (D5h) 127 

13.2 Page 1 - Embedded advanced features registers . . 128 

13.2.1 FSM_LC_TIMEOUT_L (7Ah) and FSM_LC_TIMEOUT_H (7Bh). . 128 

13.2.2 FSM_PROGRAMS (7Ch) . 128 

13.2.3 FSM_START_ADD_L (7Eh) and FSM_START_ADD_H (7Fh) 129 

13.2.4 PEDO_CMD_REG (83h). 129 

13.2.5 PEDO_DEB_CONF (84h) . 130 

13.2.6 PEDO_SC_DELTAT_L (D0h) and PEDO_SC_DELTAT_H (D1h) 131 

# 14 Sensor hub register mapping 132

# 15 Sensor hub register description. 134

15.1 SENSOR_HUB_1 (02h) . 134 

15.2 SENSOR_HUB_2 (03h) . . 134 

15.3 SENSOR_HUB_3 (04h) . . 134 

15.4 SENSOR_HUB_4 (05h) . .135 

15.5 SENSOR_HUB_5 (06h) . . 135 

15.6 SENSOR_HUB_6 (07h) . . 135 

15.7 SENSOR_HUB_7 (08h) . .136 

15.8 SENSOR_HUB_8 (09h) . . 136 

15.9 SENSOR_HUB_9 (0Ah). . 136 

15.10 SENSOR_HUB_10 (0Bh). .137 

15.11 SENSOR_HUB_11 (0Ch). .137 

15.12 SENSOR_HUB_12 (0Dh). .137 

15.13 SENSOR_HUB_13 (0Eh). . 138 

15.14 SENSOR_HUB_14 (0Fh). .138 

15.15 SENSOR_HUB_15 (10h) . . 138 

15.16 SENSOR_HUB_16 (11h) . . 139 

15.17 SENSOR_HUB_17 (12h) . .139 

15.18 SENSOR_HUB_18 (13h) . . 139 

15.19 MASTER_CONFIG (14h). .140 

15.20 SLV0_ADD (15h). . 141 

15.21 SLV0_SUBADD (16h). .141 

15.22 SLAVE0_CONFIG (17h). . .141 

15.23 SLV1_ADD (18h). . 142 

15.24 SLV1_SUBADD (19h). .142 

15.25 SLAVE1_CONFIG (1Ah) .142 

15.26 SLV2_ADD (1Bh) .143 

15.27 SLV2_SUBADD (1Ch) .143 

15.28 SLAVE2_CONFIG (1Dh) . 143 

15.29 SLV3_ADD (1Eh) . 144 

15.30 SLV3_SUBADD (1Fh). 144 

15.31 SLAVE3_CONFIG (20h). . 144 

15.32 DATAWRITE_SLV0 (21h). . 145 

15.33 STATUS_MASTER (22h) . . 145 

16 Soldering information. . 146 

17 Package information. 147 

17.1 LGA-14L package information. .147 

17.2 LGA-14 packing information . 148 

Revision history . 150 

Contents 151 

List of tables 159 

List of figures. . 167 

# List of tables

Table 1. Pin description. . 8 

Table 2. Mechanical characteristics 9 

Table 3. Electrical characteristics . 11 

Table 4. Temperature sensor characteristics 11 

Table 5. SPI slave timing values (in mode 3) . 12 

Table 6. I²C slave timing values . 13 

Table 7. Absolute maximum ratings 14 

Table 8. Serial interface pin description . 16 

Table 9. I²C terminology 16 

Table 10. SAD+Read/Write patterns . 17 

Table 11. Transfer when master is writing one byte to slave. 17 

Table 12. Transfer when master is writing multiple bytes to slave . . 17 

Table 13. Transfer when master is receiving (reading) one byte of data from slave 17 

Table 14. Transfer when master is receiving (reading) multiple bytes of data from slave 17 

Table 15. MIPI I3CSM CCC commands . 23 

Table 16. Master I²C pin details 26 

Table 17. Auxiliary SPI pin details . 26 

Table 18. Gyroscope LPF2 bandwidth selection. 30 

Table 19. Internal pin status 38 

Table 20. Registers address map. 40 

Table 21. FUNC_CFG_ACCESS register 43 

Table 22. FUNC_CFG_ACCESS register description 43 

Table 23. PIN_CTRL register. 43 

Table 24. PIN_CTRL register description 43 

Table 25. S4S_TPH_L register 44 

Table 26. S4S_TPH_L register description 44 

Table 27. S4S_TPH_H register 44 

Table 28. S4S_TPH_H register description . 44 

Table 29. S4S_RR register 44 

Table 30. S4S_RR register description 44 

Table 31. FIFO_CTRL1 register . 45 

Table 32. FIFO_CTRL1 register description. 45 

Table 33. FIFO_CTRL2 register . 45 

Table 34. FIFO_CTRL2 register . 45 

Table 35. FIFO_CTRL3 register . 46 

Table 36. FIFO_CTRL3 register description. . 46 

Table 37. FIFO_CTRL4 register . 47 

Table 38. FIFO_CTRL4 register description. . 47 

Table 39. COUNTER_BDR_REG1 register . 48 

Table 40. COUNTER_BDR_REG1 register description . 48 

Table 41. COUNTER_BDR_REG2 register 48 

Table 42. COUNTER_BDR_REG2 register description . 48 

Table 43. INT1_CTRL register . 49 

Table 44. INT1_CTRL register description. 49 

Table 45. INT2_CTRL register . 50 

Table 46. INT2_CTRL register description. 50 

Table 47. WhoAmI register 50 

Table 48. CTRL1_XL register 51 

Table 49. CTRL1_XL register description 51 

Table 50. Accelerometer ODR selection 51 

Table 51. CTRL2_G register 52 

Table 52. CTRL2_G register description . 52 

Table 53. Gyroscope ODR configuration setting. 52 

Table 54. CTRL3_C register 53 

Table 55. CTRL3_C register description . 53 

Table 56. CTRL4_C register 54 

Table 57. CTRL4_C register description . 54 

Table 58. CTRL5_C register 55 

Table 59. CTRL5_C register description . 55 

Table 60. Angular rate sensor self-test mode selection . 55 

Table 61. Linear acceleration sensor self-test mode selection 55 

Table 62. CTRL6_C register 56 

Table 63. CTRL6_C register description . 56 

Table 64. Trigger mode selection . 56 

Table 65. Gyroscope LPF1 bandwidth selection. . 56 

Table 66. CTRL7_G register 57 

Table 67. CTRL8_XL register 58 

Table 68. Accelerometer bandwidth configurations . 58 

Table 69. CTRL9_XL register 60 

Table 70. CTRL9_XL register description 60 

Table 71. CTRL10_C register 60 

Table 72. CTRL10_C register description 60 

Table 73. ALL_INT_SRC register . 61 

Table 74. ALL_INT_SRC register description. 61 

Table 75. WAKE_UP_SRC register 62 

Table 76. WAKE_UP_SRC register description 62 

Table 77. TAP_SRC register 63 

Table 78. TAP_SRC register description . 63 

Table 79. D6D_SRC register . 64 

Table 80. D6D_SRC register description . 64 

Table 81. STATUS_REG register . 65 

Table 82. STATUS_REG register description . 65 

Table 83. STATUS_SPIAux register . 65 

Table 84. STATUS_SPIAux register description . 65 

Table 85. OUT_TEMP_L register . 66 

Table 86. OUT_TEMP_H register. . 66 

Table 87. OUT_TEMP register description. 66 

Table 88. OUTX_L_G register . 66 

Table 89. OUTX_H_G register. . 66 

Table 90. OUTX_H_G register description. . 66 

Table 91. OUTY_L_G register . 67 

Table 92. OUTY_H_G register. . 67 

Table 93. OUTY_H_G register description. 67 

Table 94. OUTZ_L_G register . 67 

Table 95. OUTZ_H_G register . 67 

Table 96. OUTZ_H_G register description. 67 

Table 97. OUTX_L_A register . 68 

Table 98. OUTX_H_A register . 68 

Table 99. OUTX_H_A register description . 68 

Table 100. OUTY_L_A register . 68 

Table 101. OUTY_H_A register . 68 

Table 102. OUTY_H_A register description . 68 

Table 103. OUTZ_L_A register 69 

Table 104. OUTZ_H_A register . 69 

Table 105. OUTZ_H_A register description . 69 

Table 106. EMB_FUNC_STATUS_MAINPAGE register 69 

Table 107. EMB_FUNC_STATUS_MAINPAGE register description 69 

Table 108. FSM_STATUS_A_MAINPAGE register . 70 

Table 109. FSM_STATUS_A_MAINPAGE register description . 70 

Table 110. FSM_STATUS_B_MAINPAGE register . 70 

Table 111. FSM_STATUS_B_MAINPAGE register description . 70 

Table 112. STATUS_MASTER_MAINPAGE register. . 71 

Table 113. STATUS_MASTER_MAINPAGE register description 71 

Table 114. FIFO_STATUS1 register . 72 

Table 115. FIFO_STATUS1 register description . . 72 

Table 116. FIFO_STATUS2 register . 72 

Table 117. FIFO_STATUS2 register description . . 72 

Table 118. TIMESTAMP3 register 73 

Table 119. TIMESTAMP2 register 73 

Table 120. TIMESTAMP1 register 73 

Table 121. TIMESTAMP0 register 73 

Table 122. TAP_CFG0 register . 74 

Table 123. TAP_CFG0 register description 74 

Table 124. TAP_CFG1 register . 75 

Table 125. TAP_CFG1 register description 75 

Table 126. TAP priority decoding . 75 

Table 127. TAP_CFG2 register . 75 

Table 128. TAP_CFG2 register description 75 

Table 129. TAP_THS_6D register 76 

Table 130. TAP_THS_6D register description . 76 

Table 131. INT_DUR2 register. . 76 

Table 132. INT_DUR2 register description 76 

Table 133. WAKE_UP_THS register. 77 

Table 134. WAKE_UP_THS register description 77 

Table 135. WAKE_UP_DUR register 77 

Table 136. WAKE_UP_DUR register description 77 

Table 137. FREE_FALL register 78 

Table 138. FREE_FALL register description 78 

Table 139. MD1_CFG register. . 79 

Table 140. MD1_CFG register description. 79 

Table 141. MD2_CFG register. . 80 

Table 142. MD2_CFG register description. 80 

Table 143. S4S_ST_CMD_CODE register 81 

Table 144. S4S_ST_CMD_CODE register description 81 

Table 145. S4S_DT_REG register . 81 

Table 146. S4S_DT_REG register description . 81 

Table 147. I3C_BUS_AVB register. 81 

Table 148. I3C_BUS_AVB register description. . 81 

Table 149. INTERNAL_FREQ_FINE register. 82 

Table 150. INTERNAL_FREQ_FINE register description. 82 

Table 151. INT_OIS register . 83 

Table 152. INT_OIS register description 83 

Table 153. CTRL1_OIS register. . 84 

Table 154. CTRL1_OIS register description. 84 

Table 155. DEN mode selection. . 84 

Table 156. CTRL2_OIS register. 85 

Table 157. CTRL2_OIS register description. 85 

Table 158. Gyroscope OIS chain digital LPF1 filter bandwidth selection 85 

Table 159. CTRL3_OIS register. 86 

Table 160. CTRL3_OIS register description. 86 

Table 161. Accelerometer OIS channel bandwidth and phase . 86 

Table 162. Self-test nominal output variation . 86 

Table 163. X_OFS_USR register . 87 

Table 164. X_OFS_USR register description. . 87 

Table 165. Y_OFS_USR register . 87 

Table 166. Z_OFS_USR register . 87 

Table 167. Z_OFS_USR register description . 87 

Table 168. FIFO_DATA_OUT_TAG register. . 88 

Table 169. FIFO_DATA_OUT_TAG register description 88 

Table 170. FIFO tag . 88 

Table 171. FIFO_DATA_OUT_X_H and FIFO_DATA_OUT_X_L registers . 89 

Table 172. FIFO_DATA_OUT_X_H and FIFO_DATA_OUT_X_L register description 89 

Table 173. FIFO_DATA_OUT_Y_H and FIFO_DATA_OUT_Y_L registers . 89 

Table 174. FIFO_DATA_OUT_Y_H and FIFO_DATA_OUT_Y_L register description 89 

Table 175. FIFO_DATA_OUT_Z_H and FIFO_DATA_OUT_Z_L registers . 89 

Table 176. FIFO_DATA_OUT_Z_H and FIFO_DATA_OUT_Z_L register description. . 89 

Table 177. Register address map - embedded functions . 90 

Table 178. PAGE_SEL register . 92 

Table 179. PAGE_SEL register description 92 

Table 180. EMB_FUNC_EN_A register. . 92 

Table 181. EMB_FUNC_EN_A register description 92 

Table 182. EMB_FUNC_EN_A register. . 93 

Table 183. EMB_FUNC_EN_A register description 93 

Table 184. EMB_FUNC_EN_B register. . 93 

Table 185. EMB_FUNC_EN_B register description 93 

Table 186. PAGE_ADDRESS register 94 

Table 187. PAGE_ADDRESS register description 94 

Table 188. PAGE_VALUE register . 94 

Table 189. PAGE_VALUE register description . 94 

Table 190. EMB_FUNC_INT1 register 95 

Table 191. EMB_FUNC_INT1 register description . 95 

Table 192. FSM_INT1_A register. . 96 

Table 193. FSM_INT1_A register description. . 96 

Table 194. FSM_INT1_B register. . 97 

Table 195. FSM_INT1_B register description. . 97 

Table 196. EMB_FUNC_INT2 register 98 

Table 197. EMB_FUNC_INT2 register description . 98 

Table 198. FSM_INT2_A register. . 99 

Table 199. FSM_INT2_A register description. . 99 

Table 200. FSM_INT2_B register. . 100 

Table 201. FSM_INT2_B register description. . 100 

Table 202. EMB_FUNC_STATUS register. 101 

Table 203. EMB_FUNC_STATUS register description. . 101 

Table 204. FSM_STATUS_A register . 101 

Table 205. FSM_STATUS_A register description . 101 

Table 206. FSM_STATUS_B register 102 

Table 207. FSM_STATUS_B register description . 102 

Table 208. PAGE_RW register 103 

Table 209. PAGE_RW register description 103 

Table 210. EMB_FUNC_FIFO_CFG register . 103 

Table 211. EMB_FUNC_FIFO_CFG register description. 103 

Table 212. FSM_ENABLE_A register . 104 

Table 213. FSM_ENABLE_A register description. 104 

Table 214. FSM_ENABLE_B register . 104 

Table 215. FSM_ENABLE_B register description. . 104 

Table 216. FSM_LONG_COUNTER_L register . 105 

Table 217. FSM_LONG_COUNTER_L register description . 105 

Table 218. FSM_LONG_COUNTER_H register . 105 

Table 219. FSM_LONG_COUNTER_H register description. 105 

Table 220. FSM_LONG_COUNTER_CLEAR register. . 105 

Table 221. FSM_LONG_COUNTER_CLEAR register description. . 105 

Table 222. FSM_OUTS1 register . . 106 

Table 223. FSM_OUTS1 register description. . 106 

Table 224. FSM_OUTS2 register . . 106 

Table 225. FSM_OUTS2 register description. . 106 

Table 226. FSM_OUTS3 register . 107 

Table 227. FSM_OUTS3 register description. . 107 

Table 228. FSM_OUTS4 register . . 107 

Table 229. FSM_OUTS4 register description. . 107 

Table 230. FSM_OUTS5 register . 108 

Table 231. FSM_OUTS5 register description. . 108 

Table 232. FSM_OUTS6 register . . 108 

Table 233. FSM_OUTS6 register description. . 108 

Table 234. FSM_OUTS7 register . . 109 

Table 235. FSM_OUTS7 register description. . 109 

Table 236. FSM_OUTS8 register . . 109 

Table 237. FSM_OUTS8 register description. . 109 

Table 238. FSM_OUTS9 register . . .110 

Table 239. FSM_OUTS9 register description. . .110 

Table 240. FSM_OUTS10 register . .110 

Table 241. FSM_OUTS10 register description . .110 

Table 242. FSM_OUTS11 register . .111 

Table 243. FSM_OUTS11 register description . .111 

Table 244. FSM_OUTS12 register . .111 

Table 245. FSM_OUTS12 register description . .111 

Table 246. FSM_OUTS13 register . .112 

Table 247. FSM_OUTS13 register description . .112 

Table 248. FSM_OUTS14 register . .112 

Table 249. FSM_OUTS14 register description . .112 

Table 250. FSM_OUTS15 register . .113 

Table 251. FSM_OUTS15 register description . .113 

Table 252. FSM_OUTS16 register . .113 

Table 253. FSM_OUTS16 register description . . .113 

Table 254. EMB_FUNC_ODR_CFG_B register . .114 

Table 255. EMB_FUNC_ODR_CFG_B register description . .114 

Table 256. STEP_COUNTER_L register. .115 

Table 257. STEP_COUNTER_L register description. . .115 

Table 258. STEP_COUNTER_H register .115 

Table 259. STEP_COUNTER_H register description .115 

Table 260. EMB_FUNC_SRC register .116 

Table 261. EMB_FUNC_SRC register description .116 

Table 262. EMB_FUNC_INIT_A register. .116 

Table 263. EMB_FUNC_INIT_A register description. . .116 

Table 264. EMB_FUNC_INIT_B register. 117 

Table 265. EMB_FUNC_INIT_B register description. . 

Table 266. Register address map - embedded advanced features page 0 . .118 

Table 267. Register address map - embedded advanced features page 1 .119 

Table 268. MAG_SENSITIVITY_L register 121 

Table 269. MAG_SENSITIVITY_L register description 121 

Table 270. MAG_SENSITIVITY_H register . 121 

Table 271. MAG_SENSITIVITY_H register description . 121 

Table 272. MAG_OFFX_L register . 122 

Table 273. MAG_OFFX_L register description. 122 

Table 274. MAG_OFFX_H register. . 122 

Table 275. MAG_OFFX_H register description 122 

Table 276. MAG_OFFY_L register . 122 

Table 277. MAG_OFFY_L register description. 122 

Table 278. MAG_OFFY_H register. 122 

Table 279. MAG_OFFY_H register description 122 

Table 280. MAG_OFFZ_L register . 123 

Table 281. MAG_OFFZ_L register description . 123 

Table 282. MAG_OFFZ_H register. 123 

Table 283. MAG_OFFZ_H register description 123 

Table 284. MAG_SI_XX_L register. 123 

Table 285. MAG_SI_XX_L register description 123 

Table 286. MAG_SI_XX_H register 123 

Table 287. MAG_SI_XX_H register description . 123 

Table 288. MAG_SI_XY_L register. 124 

Table 289. MAG_SI_XY_L register description 124 

Table 290. MAG_SI_XY_H register 124 

Table 291. MAG_SI_XY_H register description 124 

Table 292. MAG_SI_XZ_L register. 124 

Table 293. MAG_SI_XZ_L register description 124 

Table 294. MAG_SI_XZ_H register 124 

Table 295. MAG_SI_XZ_H register description 124 

Table 296. MAG_SI_YY_L register. 125 

Table 297. MAG_SI_YY_L register description 125 

Table 298. MAG_SI_YY_H register 125 

Table 299. MAG_SI_YY_H register description 125 

Table 300. MAG_SI_YZ_L register. 125 

Table 301. MAG_SI_YZ_L register description 125 

Table 302. MAG_SI_YZ_H register 125 

Table 303. MAG_SI_YZ_H register description 125 

Table 304. MAG_SI_ZZ_L register. 126 

Table 305. MAG_SI_ZZ_L register description. 126 

Table 306. MAG_SI_ZZ_H register 126 

Table 307. MAG_SI_ZZ_H register description 126 

Table 308. MAG_CFG_A register 127 

Table 309. MAG_CFG_A register description 127 

Table 310. MAG_CFG_B register 127 

Table 311. MAG_CFG_B register description 127 

Table 312. FSM_LC_TIMEOUT_L register 128 

Table 313. FSM_LC_TIMEOUT_L register description 128 

Table 314. FSM_LC_TIMEOUT_H register 128 

Table 315. FSM_LC_TIMEOUT_H register description . . 128 

Table 316. FSM_PROGRAMS register . 128 

Table 317. FSM_PROGRAMS register description. 128 

Table 318. FSM_START_ADD_L register 129 

Table 319. FSM_START_ADD_L register description . 129 

Table 320. FSM_START_ADD_H register. 129 

Table 321. FSM_START_ADD_H register description. . 129 

Table 322. PEDO_CMD_REG register . 129 

Table 323. PEDO_CMD_REG register description . 129 

Table 324. PEDO_DEB_STEPS_CONF register 130 

Table 325. PEDO_DEB_STEPS_CONF register description 130 

Table 326. PEDO_SC_DELTAT_L register 131 

Table 327. PEDO_SC_DELTAT_H register . 131 

Table 328. PEDO_SC_DELTAT_H/L register description. 131 

Table 329. Registers address map. 132 

Table 330. SENSOR_HUB_1 register. 134 

Table 331. SENSOR_HUB_1 register description 134 

Table 332. SENSOR_HUB_2 register. 134 

Table 333. SENSOR_HUB_2 register description 134 

Table 334. SENSOR_HUB_3 register. 134 

Table 335. SENSOR_HUB_3 register description 134 

Table 336. SENSOR_HUB_4 register. 135 

Table 337. SENSOR_HUB_4 register description 135 

Table 338. SENSOR_HUB_5 register. 135 

Table 339. SENSOR_HUB_5 register description 135 

Table 340. SENSOR_HUB_6 register. 135 

Table 341. SENSOR_HUB_6 register description 135 

Table 342. SENSOR_HUB_7 register. . 136 

Table 343. SENSOR_HUB_7 register description 136 

Table 344. SENSOR_HUB_8 register. 136 

Table 345. SENSOR_HUB_8 register description 136 

Table 346. SENSOR_HUB_9 register. 136 

Table 347. SENSOR_HUB_9 register description 136 

Table 348. SENSOR_HUB_10 register. 137 

Table 349. SENSOR_HUB_10 register description. 137 

Table 350. SENSOR_HUB_11 register . 137 

Table 351. SENSOR_HUB_11 register description. 137 

Table 352. SENSOR_HUB_12 register. 137 

Table 353. SENSOR_HUB_12 register description. 137 

Table 354. SENSOR_HUB_13 register. 138 

Table 355. SENSOR_HUB_13 register description. 138 

Table 356. SENSOR_HUB_14 register. 138 

Table 357. SENSOR_HUB_14 register description. 138 

Table 358. SENSOR_HUB_15 register. . 138 

Table 359. SENSOR_HUB_15 register description. 138 

Table 360. SENSOR_HUB_16 register. 139 

Table 361. SENSOR_HUB_16 register description. 139 

Table 362. SENSOR_HUB_17 register. 139 

Table 363. SENSOR_HUB_17 register description. 139 

Table 364. SENSOR_HUB_18 register. . 139 

Table 365. SENSOR_HUB_18 register description. 139 

Table 366. MASTER_CONFIG register. . 140 

Table 367. MASTER_CONFIG register description 140 

Table 368. SLV0_ADD register 141 

Table 369. SLV0_ADD register description . 141 

Table 370. SLV0_SUBADD register 141 

Table 371. SLV0_SUBADD register description . 141 

Table 372. SLAVE0_CONFIG register 141 

Table 373. SLAVE0_CONFIG register description 141 

Table 374. SLV1_ADD register 142 

Table 375. SLV1_ADD register description . 142 

Table 376. SLV1_SUBADD register . 142 

Table 377. SLV1_SUBADD register description . 142 

Table 378. SLAVE1_CONFIG register 142 

Table 379. SLAVE1_CONFIG register description 142 

Table 380. SLV2_ADD register 143 

Table 381. SLV2_ADD register description 143 

Table 382. SLV2_SUBADD register . 143 

Table 383. SLV2_SUBADD register description . 143 

Table 384. SLAVE2_CONFIG register 143 

Table 385. SLAVE2_CONFIG register description 143 

Table 386. SLV3_ADD register 144 

Table 387. SLV3_ADD register description . 144 

Table 388. SLV3_SUBADD register . 144 

Table 389. SLV3_SUBADD register description . 144 

Table 390. SLAVE3_CONFIG register 144 

Table 391. SLAVE3_CONFIG register description 144 

Table 392. DATAWRITE_SLV0 register. 145 

Table 393. DATAWRITE_SLV0 register description 145 

Table 394. STATUS_MASTER register . 145 

Table 395. STATUS_MASTER register description. 145 

Table 396. Reel dimensions for carrier tape of LGA-14 package 149 

Table 397. Document revision history . 150 

# List of figures

Figure 1. Generic state machine. 5 

Figure 2. State machine in the LSM6DSR 5 

Figure 3. Pin connections 6 

Figure 4. LSM6DSR connection modes. 

Figure 5. SPI slave timing diagram (in mode 3) 12 

Figure 6. I²C slave timing diagram 13 

Figure 7. Read and write protocol (in mode 3) 19 

Figure 8. SPI read protocol (in mode 3) . 20 

Figure 9. Multiple byte SPI read protocol (2-byte example) (in mode 3) . 20 

Figure 10. SPI write protocol (in mode 3). 21 

Figure 11. Multiple byte SPI write protocol (2-byte example) (in mode 3) . 21 

Figure 12. SPI read protocol in 3-wire mode (in mode 3) . 22 

Figure 13. I²C and I3C both active (INT1 pin not connected) 25 

Figure 14. Only I3C active (INT1 pin connected to Vdd_IO) . 25 

Figure 15. Block diagram of filters 27 

Figure 16. Accelerometer UI chain . 28 

Figure 17. Accelerometer composite filter 28 

Figure 18. Accelerometer chain with Mode 4 enabled . 29 

Figure 19. Gyroscope digital chain - Mode 1 (UI/EIS) and Mode 2 29 

Figure 20. Gyroscope digital chain - Mode 3 / Mode 4 (OIS/EIS) 30 

Figure 21. Auxiliary SPI full control (a) and enabling primary interface (b) 31 

Figure 22. LSM6DSR electrical connections in Mode 1 . 35 

Figure 23. LSM6DSR electrical connections in Mode 2 . 36 

Figure 24. LSM6DSR electrical connections in Mode 3 and Mode 4 (auxiliary 3/4-wire SPI) . 37 

Figure 25. Accelerometer block diagram 59 

Figure 26. LGA-14L 2.5 x 3.0 x 0.86 mm package outline and mechanical data 147 

Figure 27. Carrier tape information for LGA-14 package 148 

Figure 28. LGA-14 package orientation in carrier tape. 148 

Figure 29. Reel information for carrier tape of LGA-14 package . 149 

# IMPORTANT NOTICE – PLEASE READ CAREFULLY

STMicroelectronics NV and its subsidiaries (“ST”) reserve the right to make changes, corrections, enhancements, modifications, and improvements to ST products and/or to this document at any time without notice. Purchasers should obtain the latest relevant information on ST products before placing orders. ST products are sold pursuant to ST’s terms and conditions of sale in place at the time of order acknowledgement. 

Purchasers are solely responsible for the choice, selection, and use of ST products and ST assumes no liability for application assistance or the design of Purchasers’ products. 

No license, express or implied, to any intellectual property right is granted by ST herein. 

Resale of ST products with provisions different from the information set forth herein shall void any warranty granted by ST for such product. 

ST and the ST logo are trademarks of ST. For additional information about ST trademarks, please refer to www.st.com/trademarks. All other product or service names are the property of their respective owners. 

Information in this document supersedes and replaces information previously supplied in any prior versions of this document. 

© 2020 STMicroelectronics – All rights reserved 