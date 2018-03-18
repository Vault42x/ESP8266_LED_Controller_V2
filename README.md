# ESP8266_LED_Controller_V2
My LED Controller project based off a NodeMCU ESP8266

For the most part, this is working.  I'm not a fan of running the ESP8266 off 12V though as the AMS1117 voltage
regulator is getting REALLY hot.  I have since added a secondary voltage regulator that takes the 12V that powers
the device and knocks it down to 5V for the ESP8266.  It's running great at 5V and the temperature seems to be
MUCH lower.  

I'll get the schematic updated to reflect this as soon as I'm done testing to make sure the thermals are good.
