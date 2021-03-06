// Garden of Eden
#include <IoTkit.h>    // include IoTkit.h to use the Intel IoT Kit
#include <Ethernet.h>  // must be included to use IoTkit
#include <aJSON.h>
#include <stdio.h>
#include <math.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
#include <Wire.h>

float temperature;
int a;
int temp;
int B = 3975;                //B value of the thermistor
float resistance;
int HumidityPin1 = A1; //The pin number of the humidity sensor1
int HumidityPin2 = A2; //The pin number of the humidity sensor2
const int relayPin =  6; //THe pin number of power relay
IoTkit iotkit; //Intel analytics's enable

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2); //LCD begin
  pinMode(relayPin, OUTPUT); // initialize the relay pin as an output
  iotkit.begin(); //Intel analytics's enable
}

void loop() {


  int humidityValue1; //store the analog value from humidity sensor1
  int humidityValue2; //store the analog value from humidity sensor2
  int AverageHumidity; //store average for humidity sensor1 and sensor2

  // temperature sensor calculation from grove example
  int del = 1000;
  a = analogRead(0); //read the temperature sensor
  resistance = (float)(1023 - a) * 10000 / a; //get the resistance of the sensor;
  temperature = 1 / (log(resistance / 10000) / B + 1 / 298.15) - 273.15; //convert to temperature via datasheet ;
  temp = temperature;



  delay(1000);
  Serial.print("Current temperature is ");
  Serial.println(temp);

  humidityValue1 = analogRead(HumidityPin1); //read the humidity sensor1
  humidityValue2 = analogRead(HumidityPin2); //read the humidity sensor2

  // Control in case one sensor is down. Not used in latest release.
  //if (humidityValue1 + humidityValue2 == humidityValue1) {
  //    AverageHumidity = humidityValue1;
  //	}
  //else if (humidityValue1 + humidityValue2 == humidityValue2) {
  //	AverageHumidity = humidityValue2;
  //	}
  //else {
  //AverageHumidity=(humidityValue1 + humidityValue2)/2;
  //}

  Serial.print("H1:");
  Serial.println(humidityValue1);
  Serial.print("H2:");
  Serial.println(humidityValue2);
  Serial.print("AV:");
  Serial.println(AverageHumidity);
  iotkit.send("garden", AverageHumidity);
  iotkit.send("temp", temperature);
  delay(1000);

  //LCD shows the humidity of the soil
  lcd.clear();
  lcd.setCursor(0, 0); // set the cursor to column 6, line 0
  lcd.print("H1:") + lcd.print(humidityValue1) + lcd.print(" ");
  //lcd.print("AV:")+lcd.print(AverageHumidity)+lcd.print(" ");
  lcd.print("H2:") + lcd.print(humidityValue2);

  //LCD shows the temperature C
  lcd.setCursor(0, 1); // set the cursor to column 0, line 0
  lcd.print("T:");
  lcd.print(temp) + lcd.print("C");

  //Main loop
  //if (AverageHumidity<630) {- CLEAN UP
  if (humidityValue1 > 600 || humidityValue2 > 600) {
    lcd.print("   DRY");
    lcd.setRGB(200, 0, 0); // Red background
    digitalWrite(relayPin, HIGH); // turn relay on (water pump is on)
    Serial.print("Pump is working");
    delay(20000); //pump is working for 20 sec, loop delayed
    Serial.print("Pump was working for 20 sec");
  }
  // You need to experiment with soil humidity sensor readings. In my case DRY more than 600; MOIST 400-600; FLOOD less then 400.
  // else if (AverageHumidity>=630 && AverageHumidity<800){ - CLEAN UP
  else if (humidityValue1 > 400 && humidityValue1 <= 600 || humidityValue2 > 400 && humidityValue2 <= 600) { // Use 2 sensor reading
    lcd.print(" MOIST");
    lcd.setRGB(0, 254, 0); //Green background
    digitalWrite(relayPin, LOW); // turn relay off:
    Serial.print("Pump stopped");
  }

  else {
    lcd.print(" FLOOD");
    lcd.setRGB(0, 0, 250); //Blue background
    digitalWrite(relayPin, LOW); // turn relay off:
  }

  delay(500);

}
