# Battery2battery_charger
 
Current version in development. 

Trying to implement a module that charges a leisure battery in a car when the engine is turned on. This module will detect the voltage to determine the engine state and will try to charge the leisure battery at a current of ~30A. It features a simple buck converter based on a BTN8962 power switch to regulate the output voltage, a INA219 current sensor IC to determine the leisure battery charging current, an 128x64 OLED to display different settings that can be selected using a rotary encoder, and multiple DS18B20 temperature sensors to detect the engine alternator temperature and leisure battery temperature.
PCB board link: https://oshwlab.com/sergiugabrielstanciu/battery-battery_charger