# Water-spill-detector
Detect water leak under the washing machine in the basement

By using a moisture sensor taped to the floor behind the washing machine and connected to an ESP32, it detects if there is water on the floor or not.

If there is water, then a Webhook is sent to IFTTT and i recieve an email about the alert. 

On top of this code, you need to create another .h file called "arduino_secrets.h" and add in your SSID, WIFI password and secret device ID. 

#define SECRET_SSID "EXAMPLE123"
#define SECRET_OPTIONAL_PASS "Password1"
#define SECRET_DEVICE_KEY "Devicekeyhere"
