//#pragma GCC diagnostic error "-Wconversion"

/*
   HABalloon by KD2NDR, Miami Florida October 25 2018
   Improvements by YO3ICT, Bucharest Romania, April-May 2019 
   Improvements By SA6BSS, Sweden, fall 2020
   You may use and modify the following code to suit
   your needs so long as it remains open source
   and it is for non-commercial use only.
*/
#include <Sodaq_wdt.h>
#include <si5351.h>
#include <JTEncode.h>
#include <TimeLib.h>
#include <TinyGPS++.h>
#include <avr/power.h>
#include "debug.h"
#include "config.h"


#ifdef DEBUG_MODE
# include <SendOnlySoftwareSerial.h>
SendOnlySoftwareSerial debugPort(PIN_SOFTSERIAL_TX);
unsigned long l_millis = 0;

// just for debuging purposes
int board_voltage_mv = 0;
int board_temperature = 0;
char vcc_str[6];

#endif

// Enumerations
enum mode {MODE_WSPR};
TinyGPSPlus gps;
Si5351 si5351;
JTEncode jtencode;

// Global variables
unsigned long freq;
char call[] = CONFIG_CALLSIGN; // WSPR Standard callsign
char call_telemetry[7]; // WSPR telemetry callsign
char loc_telemetry[5]; // WSPR telemetry locator
uint8_t dbm_telemetry; // WSPR telemetry dbm
char loc4[5]; // 4 digit gridsquare locator
byte Hour, Minute, Second; // Used for timing
long lat, lon, oldlat, oldlon; // Used for location
uint8_t tx_buffer[255]; // WSPR Tx buffer
uint8_t symbol_count; // JTencode
uint16_t tone_delay, tone_spacing; // JTencode
int alt_meters = 0;
bool telemetry_set = false;
int Sats = 0;
int gps_speed = 0;
volatile bool proceed = false;
bool flip = false;

#include "TelemFunctions.h" // Various telemetry functions
#include "Timing.h" // Scheduling

ISR(TIMER1_COMPA_vect)
{ proceed = true; }

void tx_on();
void tx_off();


void setup()
{
  //clock_prescale_set(clock_div_2);
  //clock_prescale_set(clock_div_4);
  //clock_prescale_set(clock_div_8);

  sodaq_wdt_enable(WDT_PERIOD_8X);
  pinMode(3, OUTPUT); digitalWrite(3, HIGH); //gps pin 5 on
  
  pinMode(2, OUTPUT);  // Si5351 off
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  pinMode(A0, OUTPUT); // GPS VCC on
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH); 

#ifdef DEBUG_MODE
  sodaq_wdt_reset();
  debugPort.begin(DEBUG_BAUDRATE);
  debugPort.println(F("Boot"));
  debugPort.print(F("OSCCAL="));
  debugPort.println(OSCCAL);
  debugPort.print(F("WSPR_CTC="));
  debugPort.println(WSPR_CTC);
  debugPort.print(F("CALLSIGN: '"));
  debugPort.print(call);
  debugPort.println(F("'"));
  debugI2CScanner();

#ifdef USE_TEST_TIMING
  debugPort.println(F("Using test timing"));
#endif
#ifdef IGNORE_GPS_FIX
  debugPort.println(F("Ignoring GPS fix and mocking clock"));
  setTime(00, 01, 45, 11, 3, 2021); // (hr,min,sec,day,month,yr
  #endif
#endif

  Serial.begin(9600);
  delay(1000);
  Serial.write("$PCAS04,1*18\r\n"); //Sets navsystem of the ATGM to GPS only
  delay(1000);

  noInterrupts(); // Set up Timer1 for interrupts every symbol period.
  TCCR1A = 0;
  TCNT1  = 0;
  TCCR1B = (1 << CS12) |
           (1 << CS10) |
           (1 << WGM12);
  TIMSK1 = (1 << OCIE1A);
  OCR1A = WSPR_CTC;
  interrupts();
  sodaq_wdt_reset();

  }


void loop() {
	sodaq_wdt_reset();
	while (Serial.available() > 0)
		if (gps.encode(Serial.read())) // GPS related functions need to be in here to work with tinyGPS Plus library
			if (timeStatus() == timeNotSet) // Only sets time if already not done previously
					{
				setGPStime();
			} // Sets system time to GPS UTC time for sync
#ifdef IGNORE_GPS_FIX
	TXtiming(); // Process timing
#else
	if (gps.location.isValid()){
		TXtiming(); // Process timing
	}
#endif

#ifdef DEBUG_MODE
	// Print info to debug port every second
	char buffer[90];

	if ((millis() - l_millis) >= 1000){
		flip = !flip;

		if (second() % 10 == 0) {
			debugReadBoardSensors();
			memset(vcc_str, 0, sizeof(vcc_str));
			dtostrf((board_voltage_mv / 1000.0), 4, 2, vcc_str);
		}
		sprintf(buffer, " %s / %02d:%02d:%02d gps.l.valid=%d speed: %d temp: %d, VCC: %s\r\n",
				loc4, hour(), minute(), second(),gps.location.isValid(), int(gps.speed.kmph()), board_temperature,
				vcc_str);
		debugPort.write(buffer);
		l_millis = millis();

//		if (flip) tx_on();
//		else tx_off();

	}
#endif
}

//void loop(){
//	sodaq_wdt_reset();
////	tx_on();
////	delay(250);
////	tx_off();
////	delay(250);
//			TXtiming(); // Process timing
//
//}


void tx_on() // Turn on the high-side switch, activating the transmitter
{
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  delay(2); // buvo 2

  si5351.init(SI5351_CRYSTAL_LOAD_0PF, 27000000, 0); // TCXO 27MHz
  si5351.set_clock_pwr(SI5351_CLK1, 0);  // Turn off the CLK1 clock
  si5351.output_enable(SI5351_CLK1, 0);  // Turn off the CLK1 output
  si5351.set_clock_pwr(SI5351_CLK2, 0);  // Turn off the CLK2 clock
  si5351.output_enable(SI5351_CLK2, 0);  // Turn off the CLK2 output
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_8MA); // Set for max power if desired. Check datasheet.
  si5351.set_freq((WSPR_FREQ * 100),SI5351_CLK0);

}

void tx_off() // Turn off the high-side switch
{
  si5351.output_enable(SI5351_CLK0, 0);  // Disable the clock initially

  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

}
