/*************************************************************
* By Tobias 180323
*
* Module Number 0
*
* Blynk Auth Tokens
*	Module 1: 7c23865250e34c8e84435532625c6510
*	Module 2: ec2e6bb785ae426b9d37c48eabd444b7
*	Module 3: 9a52bd2c6a0049b0b4d05bd4b646d38c
*	Module 4: 2d3eb9cff364493d86d4331adf30e39f
*	Module 5: 611eb127e3044fceb723ea9b86e2fcd7
*	Module 6: 6f4a783447da47c4ada4caf38633014e
*
* Connections:
*	ESP8266 -> BME 280
*		3.3V --> Vin
*		GND  --> GND
*		D1   --> SCL
*		D2   --> SDA 
*	TP4056	->
*		In+  --> Solarpanel +
*		In-  --> Solarpanel -
*		Out+ --> ESP8266 5V+
*		Out- --> ESP8266 5V-
*		B+   --> Battery +
*		B-   --> Battery -
*
**************************************************************/

//*****************Test module********************************/
//const char* module = "000102030405060708090a0b0c0d0e0f";	

//*****************Module1************************************/
const char* module = "7c23865250e34c8e84435532625c6510";

//*****************Module2************************************/
//const char* module = "ec2e6bb785ae426b9d37c48eabd444b7";

//*****************Module3************************************/
//const char* module = "9a52bd2c6a0049b0b4d05bd4b646d38c";

//*****************Module4************************************/
//const char* module = "2d3eb9cff364493d86d4331adf30e39f";

//*****************Module5************************************/
//const char* module = "611eb127e3044fceb723ea9b86e2fcd7";

//*****************Module6************************************/
//const char* module = "6f4a783447da47c4ada4caf38633014e";





/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * Note: This requires ESP8266 support package:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************/


 
#include <BMP280.h>
#include <Wire.h>

BMP280 bmp280;
#define P0 1013.25

// Wifi and Blynk settings
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 
char* ssid = "W-Less2";
char* pass = "surfa200";
 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
const char* auth = module;


// Measurement interval (seconds)
const int interval = 300; //5 mins

 
void setup()
{
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  if(!bmp280.begin())
  {
	Serial.println("BMP init faile!");
  }
  else Serial.println("BMP init success!");
  
  bmp280.setOversampling(4);
  
}

void loop()
{
  Blynk.run();		//Start blyn service and WiFi
  
  //Start mesusrement
  double T,P;
  char result = bmp280.startMeasurment();
 
  if(result!=0)
  {
    delay(result);
    result = bmp280.getTemperatureAndPressure(T,P);
    
      if(result!=0)
      {
        double A = bmp280.altitude(P,P0);
        
        Serial.print("T = \t");Serial.print(T,2); Serial.print(" degC\t");
		Blynk.virtualWrite(0, T); // virtual pin 0
        Serial.print("P = \t");Serial.print(P,2); Serial.print(" mBar\t");
		Blynk.virtualWrite(1, P); // virtual pin 1
        Serial.print("A = \t");Serial.print(A,2); Serial.println(" m");
		Blynk.virtualWrite(2, A); //virtual pin 2
       
      }
      else 
	  {
        Serial.println("Error.");
      }
  }
  else 
  {
    Serial.println("Error.");
  }
  
  ESP.deepSleep(interval * 1000000); // // deepSleep time is defined in microseconds.
}