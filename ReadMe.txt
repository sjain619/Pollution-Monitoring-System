*************************************************************** Requirements *******************************************************************************

Hardware Components Required : Arduino UNO, Esp8266 WiFi Module, MQ-135 Gas Sensor, CZN-15E Sound Sensor, pH sensor, Breadboard, Jumperwires
Softwares Required : Arduino IDE, XAMPP  

1. Configure the required hardware components step by step, First connect WiFi module with Arduino and test AT commands
2. Connect Sensors one after the other
3. Download the required library files in Arduino IDE (EspSoftwareSerial)
4. Compile and Upload the Arduino Code
5. Open Serial Monitor and set baud rate to 115200
6. Store the php files in htdocs/xampp folder and configure the Database
7. The code will be executed and sensor data will be transmitted to the Database and values will be displayed (use the url to insert data into database)
url example : http://localhost/xampp/write_data.php?arduinoid=A007&kitlocation=LH04&gassensor=153&soundsensor=286&watersensor=7.40