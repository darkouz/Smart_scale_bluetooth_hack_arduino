/*
 Name:		Smart_scale_bluetooth_hack.ino
 Created:	3/25/2018 12:53:29 PM
 Author:	darkouz

 Allows you to grab and decode bluetooth data coming from a diki smart scale or (i guess) any smart scale compatible
 with the Alfit app.

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

#define WEIGHT 0
#define BODY_INFO 1

SoftwareSerial mySerial(10, 11); // RX, TX

float weight;
float IMG;
float BMI;
float fat;
float muscle;
float IMM;
float bones;
float water;
float age;
float protein;
int bufferIdx = 0;

byte buffer[12]; //

bool isWeigth = false;
bool isInfo = false;





/**
Print the weigth and body info on the serial port

@param Which info to print (weigth or body info)
@return void
*/

void printData(int dataType) {

	if (dataType == WEIGHT)
	{

		if (weight) {
			Serial.print("Weigth : ");
			Serial.print(weight);
			Serial.println(" Kg");
			Serial.println("--------------------------");
		}
	}

	if (dataType == BODY_INFO) {
		if (IMG) {
			Serial.print("IMG : ");
			Serial.print(IMG);
			Serial.println(" %");
			Serial.println("--------------------------");
		}

		if (BMI) {
			Serial.print("BMI : ");
			Serial.println(BMI);
			Serial.println("--------------------------");
		}

		if (fat) {
			Serial.print("fat : ");
			Serial.println(fat);
			Serial.println("--------------------------");

		}

		if (muscle) {
			Serial.print("muscle : ");
			Serial.print(muscle);
			Serial.println(" %");
			Serial.println("--------------------------");
		}

		if (IMM) {
			Serial.print("IMM : ");
			Serial.print(IMM);
			Serial.println(" Kcal");
			Serial.println("--------------------------");
		}

		if (bones) {
			Serial.print("bones : ");
			Serial.print(bones);
			Serial.println(" Kg");
			Serial.println("--------------------------");

		}

		if (water) {
			Serial.print("water : ");
			Serial.print(water);
			Serial.println(" %");
			Serial.println("--------------------------");
		}

		if (age) {
			Serial.print("age : ");
			Serial.print(age);
			Serial.println(" year");
			Serial.println("--------------------------");
		}

		if (protein) {
			Serial.print("protein : ");
			Serial.print(protein);
			Serial.println(" %");
			Serial.println("--------------------------");
		}
	}

}

/**
Handle data coming from the serial port

@param 
@return void
*/

void handleData() {

	// Start Weight Info
	if (buffer[3] == 0x06 && buffer[4] == 0xFE && buffer[5] == 0xCC)
	{
		isWeigth = true;
		//Serial.println("isWeight == true");
	}

	// Start Body health Info
	if (buffer[2] == 0xFD && buffer[3] == 0xCB && buffer[4] == 0xC8)
	{
		isInfo = true;
		//Serial.println("isInfo == true");
	}

	// End Body health Info
	if (buffer[3] == 0xFC && buffer[4] == 0xCB && buffer[5] == 0xC5)
	{
		isInfo = false;
		//Serial.println("isInfo == false");
		printData(BODY_INFO);
	}



	int size = 0;

	for (int j = 0; j < sizeof(buffer) - 1; j++) {

		// Get size of the serial word by checking non null byte
		if (buffer[j] != NULL) { size++; }

		// Handle Weight data
		if (buffer[j] == 0xCA && isWeigth == true) {

			// If size == 5 weight data is coded on 2 Bytes
			if (size == 5)
			{
				weight = (float)(buffer[j - 1] | buffer[j - 2] << 8) / 10;
			}
			// else coded on 1 Byte
			else
			{
				weight = (float)(buffer[j - 1]) / 10;
			}

			// End Weigth Info
			isWeigth = false;
			printData(WEIGHT);
		}
	}

	// Handle body data info
	if (isInfo) {

		// Filter the wanted data
		if (buffer[0] == 0xAC && buffer[1] == 0x02 && buffer[2] == 0xFE) {

			switch (buffer[3])
			{
			case 0x01:
				BMI = (float)(buffer[5] | buffer[4] << 8) / 10;
				break;
			case 0x02:
				IMG = (float)buffer[4] / 10;
				break;
			case 0x04:
				fat = (float)buffer[4];
				break;
			case 0x05:
				muscle = (float)(buffer[5] | buffer[4] << 8) / 10;
				break;
			case 0x06:
				IMM = (buffer[5] | buffer[4] << 8);
				break;
			case 0x07:
				bones = (float)buffer[4] / 10;
				break;
			case 0x08:
				water = (float)(buffer[5] | buffer[4] << 8) / 10;
				break;
			case 0x09:
				age = buffer[4];
				break;
			case 0x0A:
				protein = (float)buffer[4] / 10;
				break;
			default:
				break;
			}
		}
	}

	for (int k = 0; k < sizeof(buffer) - 1; k++) {
		buffer[k] = NULL;
	}

	bufferIdx = 0;
	size = 0;

}

void setup()
{

	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	// set the data rate for the SoftwareSerial port
	mySerial.begin(9600);
	while (!mySerial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	Serial.println();
	Serial.println(R"=====(
+----------------------------------------+
|   WELCOME TO YOUR SMART SCALE HACKER   |
| STEP ON YOUR SCALE AND ENJOY YOUR DATA |
|                   :D                   |
+----------------------------------------+
)=====");


}


void loop()
{


	while (mySerial.available()) {
		byte c = mySerial.read();

		if (c == 0xAC && buffer[0] != NULL) {
			handleData();
		}

		if (c != 0x00) {
			buffer[bufferIdx++] = c;
		}
	}


}
