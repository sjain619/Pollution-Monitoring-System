#include "SoftwareSerial.h"
SoftwareSerial esp(10, 11); // TX,RX
String ssid = "My ASUS";
String password = "1234567899";
String server = "localhost";
String uri = "/xampp/write_data.php", data;
int pinSignalGasAnalog = A0; //A0 analog
int gasSensorValue = 0;
int pinSignalSoundDigital = 4;
int soundSensorValue = 0;
float waterSensorValue = 7.40;
String arduinoId = "A06", location = "LH04";
void setup()
{
  esp.begin(115200);
  Serial.begin(115200);
  pinMode(pinSignalGasAnalog, INPUT);
  pinMode (pinSignalSoundDigital, INPUT);
  reset();
  connectWifi();
}
void loop()
{
  Serial.println("loop");
  collect_data();
  data = "arduinoid=" + arduinoId + "&kitlocation=" + location + "&gassensor=" + gasSensorValue + "&soundsensor=" + soundSensorValue + "&watersensor=" + waterSensorValue ;// data sent must be under this form //name1=value1&name2=value2.
  Serial.println(data);
  httppost();
  delay(10000);
}
void collect_data()
{
  gasSensorValue = analogRead(pinSignalGasAnalog);       // read analog input pin 0
  Serial.println("Gas Sensor");
  Serial.println(gasSensorValue, DEC);  // prints the value read
  Serial.println();
  soundSensorValue = analogRead(pinSignalSoundDigital);
  Serial.println("Sound Sensor");
  Serial.println(soundSensorValue, DEC);
  Serial.println();
}
void reset()
{
  esp.println("AT+RST");
  delay(1000);
  if (esp.find((char*)"OK"))
  {
    Serial.println("Module Reset");
  }
}
void connectWifi()
{
  String cmd = "AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";
  esp.println(cmd);
  delay(4000);
  if (esp.find((char*)"OK"))
  {
    Serial.println("Connected!");
  }
  else
  {
    connectWifi();
    Serial.println("Cannot connect to wifi");
  }
}
void httppost()
{
  esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",3306");//start a TCP connection.
  if ( esp.find((char*)"OK")) 
  {
    Serial.println("TCP connection ready");
  }
  delay(1000);
  String postRequest =
    "POST " + uri + " HTTP/1.0\r\n" +
    "Host: " + server + "\r\n" +
    "Accept: *" + "/" + "*\r\n" +
    "Content-Length: " + data.length() + "\r\n" +
    "Content-Type: application/x-www-form-urlencoded\r\n" +
    "\r\n" + data;
  String sendCmd = "AT+CIPSEND=";//determine the number of characters to be sent.
  esp.print(sendCmd);
  esp.println(postRequest.length() );
  delay(500);
  if (esp.find((char*)">"))
  {
    Serial.println("Sending..");
    esp.print(postRequest);
    if (esp.find((char*)"SEND OK"))
    {
      Serial.println("Packet sent");
      while (esp.available())
      {
        String tmpResp = esp.readString();
        Serial.println(tmpResp);
      }
      esp.println("AT+CIPCLOSE");   // close the connection
    }
  }
}
