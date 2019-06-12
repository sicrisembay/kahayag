EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP32-WROOM-32D U3
U 1 1 5D1E5494
P 5710 3300
F 0 "U3" H 5710 4881 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 5710 4790 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 5710 1800 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 5410 3350 50  0001 C CNN
	1    5710 3300
	1    0    0    -1  
$EndComp
Text HLabel 6700 4300 2    50   Input ~ 0
MOT1_INA
Text HLabel 6700 4400 2    50   Input ~ 0
MOT1_INB
Text HLabel 6700 4100 2    50   Input ~ 0
MOT2_INA
Text HLabel 6700 4200 2    50   Input ~ 0
MOT2_INB
Text HLabel 6700 3900 2    50   Input ~ 0
MOT3_INA
Text HLabel 6700 4000 2    50   Input ~ 0
MOT3_INB
Text HLabel 6700 3700 2    50   Input ~ 0
MOT4_INA
Text HLabel 6700 3800 2    50   Input ~ 0
MOT4_INB
Wire Wire Line
	6700 3700 6310 3700
Wire Wire Line
	6700 3800 6310 3800
Wire Wire Line
	6700 3900 6310 3900
Wire Wire Line
	6700 4000 6310 4000
Wire Wire Line
	6700 4100 6310 4100
Wire Wire Line
	6700 4200 6310 4200
Wire Wire Line
	6700 4300 6310 4300
Wire Wire Line
	6700 4400 6310 4400
Text HLabel 6700 3600 2    50   Input ~ 0
ENC1B
Text HLabel 6700 3500 2    50   Input ~ 0
ENC1A
Text HLabel 6700 3400 2    50   Input ~ 0
ENC2B
Text HLabel 6700 3300 2    50   Input ~ 0
ENC2A
Text HLabel 6700 3200 2    50   Input ~ 0
ENC3B
Text HLabel 6700 3100 2    50   Input ~ 0
ENC3A
Text HLabel 6700 3000 2    50   Input ~ 0
ENC4B
Text HLabel 6700 2900 2    50   Input ~ 0
ENC4A
Text HLabel 6700 2800 2    50   Input ~ 0
REF1
Text HLabel 6700 2700 2    50   Input ~ 0
REF2
Text HLabel 6700 2600 2    50   Input ~ 0
REF3
Text HLabel 6700 2500 2    50   Input ~ 0
REF4
Wire Wire Line
	6310 2500 6700 2500
Wire Wire Line
	6310 2600 6700 2600
Wire Wire Line
	6310 2700 6700 2700
Wire Wire Line
	6310 2800 6700 2800
Wire Wire Line
	6310 2900 6700 2900
Wire Wire Line
	6310 3000 6700 3000
Wire Wire Line
	6310 3100 6700 3100
Wire Wire Line
	6310 3200 6700 3200
Wire Wire Line
	6310 3300 6700 3300
Wire Wire Line
	6310 3400 6700 3400
Wire Wire Line
	6310 3500 6700 3500
Wire Wire Line
	6310 3600 6700 3600
$EndSCHEMATC
