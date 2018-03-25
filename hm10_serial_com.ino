/*
Name:		Smart_scale_bluetooth_hack.ino
Created:	3/25/2018 12:53:29 PM
Author:	darkouz

Allows you to communicate with HM-10 Bluetooth Le module via serial.

Hardware :
-Arduino Uno
-Hm-10 BluetoothLE module

Wiring :

+-------------+-----------+
| ARDUINO PIN | HM-10 PIN |
+-------------+-----------+
|     3.3V    |    VCC    |
+-------------+-----------+
|    Ground   |   Ground  |
+-------------+-----------+
|      10     |     TX    |
+-------------+-----------+
|      11     |     RX    |
+-------------+-----------+
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX




void setup()
{


	Serial.begin(9600);
	while (!Serial) {
		; 
	}
	
	mySerial.begin(9600);
	while (!mySerial) {
		;
	}

}




void loop()
{

	while (mySerial.available()) {
		byte c = mySerial.read();
		Serial.write(c);
		}

	
	while (Serial.available()) {
		byte b = Serial.read();
		mySerial.write(b);
	}

}
