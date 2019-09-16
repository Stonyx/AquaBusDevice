#include <EEPROM.h>
#include <SoftwareSerial.h>

// AquaBus Device
//
// This software is provided "as is" without express or implied warranty.

// Debug related definitions
#define DEBUG
#ifdef DEBUG
  #define DEBUG_SERIAL_BEGIN() DebugSerial.begin(57600)
  #define DEBUG_LOG(string) DebugSerial.print(string)
  #define DEBUG_LOG_LN(string) DebugSerial.println(string)
#else
  #define DEBUG_SERIAL_BEGIN()
  #define DEBUG_LOG(string)
  #define DEBUG_LOG_LN(string)
#endif
#define DEBUGV_LOG_FREE_RAM() DEBUG_LOG(F("Free RAM: ")); DEBUG_LOG_LN(FreeRam())

#define MAX3059_AQUABUS_ADAPTER

// Include header files
#include <AquaBusDev.h>
#include <AquaBusLib.h>
#include <EB8.h>
//#include <PM2.h>
//#include <PM1.h>
//#include <PM3.h>
//#include <VDM.h>

// Declare global variables
SoftwareSerial DebugSerial(8, 9); // 8 is RX, 9  is TX
AquaBusLib gAquaBusLib(2);
EB8 gEB8_1(0x1234);
EB8 gEB8_2(0x1234);
//PM2 gPM2(0x1234);
//PM1 gPM1(0x1234);
//PM3 gPM3(0x1234);
//VDM gVDM(0x1234);

int incomingByte = 0;   // for incoming serial data

// Setup code
void setup()
{
  // Initialize the serial communication for debugging
  DEBUG_SERIAL_BEGIN();
  DEBUG_LOG_LN(F("Starting Aqua Bus Device sketch ..."));

  #ifdef MAX3059_AQUABUS_ADAPTER
  //ON MAX3059 based boards, drive RS pin LOW and TERM pin High to match Apex cofiguration
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
  #endif

  //EB8 setup
//EB8_1 measures current on analog pin A0
//EB8_2 measures current on analog pin A1
gEB8_1.SetCurSensor(ACS712_20A, A1);
gEB8_2.SetCurSensor(ACS712_20A, A0);

//EB8_1 uses pins 22-29 for outlets
//EB8_1 uses pins 30-37 for outlets
byte eb1Outlets[8] = {22,23,24,25,26,27,28,29};
byte eb2Outlets[8] = {30,31,32,33,34,35,36,37};
gEB8_1.SetOutletPins(eb1Outlets);
gEB8_2.SetOutletPins(eb2Outlets);

gEB8_1.Init();
gEB8_2.Init();

eeprom_update_byte(0,0);
eeprom_update_word(1,0);
eeprom_update_byte(3,0);
eeprom_update_word(4,0);
for (int i = 0; i < 8; i++)
{
  pinMode(eb1Outlets[i], OUTPUT);
  digitalWrite(eb1Outlets[i], HIGH);
  pinMode(eb2Outlets[i], OUTPUT);
  digitalWrite(eb2Outlets[i], HIGH);
}

//AB Address Init
//eeprom_update_byte(0,0);

//PM1 Init
//  eeprom_update_byte(3, 0);
//  eeprom_update_word(4, 0xFFF2);
//  eeprom_update_word(6, 0xFFF9);
//  eeprom_update_word(8, 0xFFF0);
//  eeprom_update_word(10, 0x0238);
//  eeprom_update_word(12, 0x1000);
//  eeprom_update_word(14, 0x0B55);
//  eeprom_update_word(16, 0x0E60);
//  eeprom_update_word(18, 0x1086);

//PM2 Init
//  eeprom_update_byte(3, (CONDUCTIVITY_PROBE_RANGE_SALINITY << 1));
//  eeprom_update_word(4, 0xFFF2);
//  eeprom_update_word(6, 0xFFF9);
//  eeprom_update_word(8, 0xFFF0);
//  eeprom_update_word(10, 0x0238);
//  eeprom_update_word(12, 0x1000);
//  eeprom_update_word(14, 0x0B55);
//  eeprom_update_word(16, 0x0E60);
//  eeprom_update_word(18, 0x1086);

//PM3 Init
//  eeprom_update_byte(3, (DO_PROBE_RANGE_TYPE_SAT << 1));
//  eeprom_update_word(4, 0xFFF2);
//  eeprom_update_word(6, 0xFFF9);
//  eeprom_update_word(8, 0xFFF0);
//  eeprom_update_word(10, 0x0238);
//  eeprom_update_word(12, 0x1000);
//  eeprom_update_word(14, 0x0B55);
//  eeprom_update_word(16, 0x0E60);
//  eeprom_update_word(18, 0x1086);
  
  // Initialize the AquaBus library
  gAquaBusLib.setup();
}

// Main cod
void loop()
{
  // Call the AquaBus library loop function
  gAquaBusLib.loop();
}
