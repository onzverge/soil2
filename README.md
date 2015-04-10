# Garden of Eden

Inspired by Guardian of Eden by ???
Arduino code for Intel Edison with Arduino breakboard.
The sytem automatically controls reley (connected to 12V submerged pump) to water plants. Soil's moisture controled by two sensors. Sensors' readings are avereged. In case of one sensor outage, the control implemented to avoid overwatering.
Moisture and temperature readings displayed on LCD with LCD changing baklight color depending on soil conditions (DRY-red,MOIST-green,FLOOD-blue)
Average moisture readings and outdoor temperature readings  sent to Intel Analitics, where it builds the graph.
TO DO: implement IOTkit dashboard e-mail alerts
TO DO: syetem solar power
TO DO: implement Sun tracking for solar panel( Oleg, you have wishful mind, don't overdo it)

Bill of materials:
1. Intel Edison with Arduino breakout board 1 ea  https://www.sparkfun.com/products/13097
2. Soil moisture sensor - 2e http://www.seeedstudio.com/depot/Grove-Moisture-Sensor-p-955.html
3. Relay - 1 ea http://www.seeedstudio.com/wiki/Grove_-_Relay
4. LCD RGB Backlight - 1 ea http://www.seeedstudio.com/wiki/Grove_-_LCD_RGB_Backlight
5. 12V Mini DC Pump submersible - aliexpress or ebay
