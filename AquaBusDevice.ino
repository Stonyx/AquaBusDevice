// AquaBus Device
//
// This software is provided "as is" without express or implied warranty.

// Debug related definitions
// #define DEBUG
#ifdef DEBUG
  #define DEBUG_SERIAL_BEGIN() Serial.begin(9600)
  #define DEBUG_LOG(string) Serial.print(string)
  #define DEBUG_LOG_LN(string) Serial.println(string)
#else
  #define DEBUG_SERIAL_BEGIN()
  #define DEBUG_LOG(string)
  #define DEBUG_LOG_LN(string)
#endif
#define DEBUG_LOG_FREE_RAM() DEBUG_LOG(F("Free RAM: ")); DEBUG_LOG_LN(FreeRam())

// Include header files
#include <AquaBusLib.h>

// Declare global variables
AquaBusLib gAquaBusLib(1);
EB8 gEB8;

// Setup code
void setup()
{
  // Initialize the serial communication for debugging
  DEBUG_SERIAL_BEGIN();
  DEBUG_LOG_LN(F("Starting Aqua Bus Device sketch ..."));

  // Add the devices to the AquaBus
  gAquaBusLib.addDevice(0, gEB8);

  // Initialize the AquaBus devices
  gAquaBusLib.initializeDevices();
}

// Main code
void loop()
{
  // Call the AquaBus library loop function
  gAquaBusLib.loop();
}
