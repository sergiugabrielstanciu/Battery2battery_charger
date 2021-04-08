#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_Sensor.h>
#include <RFM69.h>
#include <RFM69_ATC.h>
#include <RFM69_OTA.h>
#include <Adafruit_SleepyDog.h>
#include <avr/power.h>

#define led_pin    6 // On Trinket or Gemma, suggest changing this to 1
#define led_number 1 // Popular NeoPixel ring size
#define DELAYVAL   500 // Time (in milliseconds) to pause between pixels

Adafruit_NeoPixel WS_led(led_number, led_pin, NEO_GRB + NEO_KHZ800);
Adafruit_INA219 ina219;


void setup() {
  WS_led.begin();

}

void loop() {
  
}