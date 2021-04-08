#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <RFM69.h>
#include <RFM69_ATC.h>
#include <RFM69_OTA.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SleepyDog.h>
#include <avr/power.h>
#include <OneWire.h>
#include <Encoder.h>


#define ENCODER_USE_INTERRUPTS


#define LED_PIN        8 
#define LED_NUMBERS    1 
#define DELAYVAL       500 
#define BTN_SWITCH_INH 7
#define BTN_SWITCH_IN  6
#define DALLAS_1_PIN   PC1
#define DALLAS_2_PIN   2
#define SW_SENSE       A2
#define VBAT_SENSE     A3
#define RF_IRQ         PD1
#define ENTER          PC0
#define ENC_P          3
#define ENC_N          4
#define BUZZER         5

#define SCREEN_WIDTH   128 
#define SCREEN_HEIGHT  64 
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D

#define NODEID       789
#define NETWORKID    100
#define GATEWAYID    1   //as a rule of thumb the gateway ID should always be 1
#define FREQUENCY    RF69_433MHZ
#define ENCRYPTKEY   "sampleEncryptKey" //exactly the same 16 characters/bytes on all nodes!
#define ENABLE_ATC   //comment out this line to disable AUTO TRANSMISSION CONTROL
#define ATC_RSSI     -90

#ifdef ENABLE_ATC
  RFM69_ATC radio;
#else
  RFM69 radio;
#endif

Adafruit_SSD1306  display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_NeoPixel WS_led(LED_NUMBERS, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_INA219   ina219;
OneWire           ds_sensor_1(DALLAS_1_PIN);
OneWire           ds_sensor_2(DALLAS_2_PIN);
Encoder           encoder_butt(ENC_P, ENC_N);


long encoder_position = -999;
long newPosition = encoder_butt.read();
bool enter_is_pressed = false;

int radio_init()
{
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.encrypt(ENCRYPTKEY);
    
  #ifdef ENABLE_ATC
    radio.enableAutoPower(ATC_RSSI);
  #endif
  return true;
}

void pciSetup(byte pin)
{
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

ISR (PCINT0_vect) // handle pin change interrupt for D8 to D13 here
{    
  if(!digitalRead(ENTER))
  {
    enter_is_pressed = true;
  }
} 

void setup() {
  WS_led.begin();
  radio_init();
  ina219.begin();
  pinMode(DALLAS_1_PIN, INPUT_PULLUP);
  pinMode(DALLAS_2_PIN, INPUT_PULLUP);
  pinMode(ENTER, INPUT_PULLUP);
  pciSetup(ENTER);
  
  tone(BUZZER, 1000, 100);
}

void loop() {
  
}