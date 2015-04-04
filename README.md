# Garden of Eden

Inspired by Guardian of Eden by ???
Arduino code for Intel Edison with Arduino breakboard.
Automatically controls pump to water plants with two soil moisture sensors. Sensors' readings are avereged. In case of one sensor outage, the control implemented to avoid overwatering.
Soil moisture metering as follows:
DRY < 450
450 <= MOIST < 700
FLOOF > 700
Average moisture  readings  sent to Intel Analitics where it builds graph of soil moisture over time.
