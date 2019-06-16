EESchema Schematic File Version 4
LIBS:esp32_motor-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
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
P 4300 2900
F 0 "U3" H 3850 4260 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 4790 1540 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 4300 1400 50  0000 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 4000 2950 50  0001 C CNN
	1    4300 2900
	1    0    0    -1  
$EndComp
Text GLabel 5160 3800 2    50   Output ~ 0
MOT2_INA
Text GLabel 5160 3700 2    50   Output ~ 0
MOT2_INB
Text GLabel 5160 2700 2    50   Output ~ 0
MOT3_INA
Text GLabel 5160 2800 2    50   Output ~ 0
MOT3_INB
Text GLabel 5160 1900 2    50   Output ~ 0
MOT4_INB
Text GLabel 5160 2100 2    50   Output ~ 0
MOT4_INA
Text GLabel 5160 4000 2    50   Input ~ 0
MOT1_ENCA
Text GLabel 5160 3900 2    50   Input ~ 0
MOT1_ENCB
Text GLabel 3440 2000 0    50   Input ~ 0
MOT2_ENCA
Text GLabel 3440 1900 0    50   Input ~ 0
MOT2_ENCB
Text GLabel 5150 3200 2    50   Input ~ 0
MOT3_ENCA
Text GLabel 5150 3300 2    50   Input ~ 0
MOT3_ENCB
Text GLabel 5160 2200 2    50   Input ~ 0
MOT4_ENCA
Text GLabel 5140 3100 2    50   Input ~ 0
MOT4_ENCB
Text GLabel 5160 2500 2    50   Output ~ 0
MOT1_VREF
Text GLabel 5160 3600 2    50   Output ~ 0
MOT2_VREF
Text GLabel 5160 3000 2    50   Output ~ 0
MOT3_VREF
Text GLabel 5160 2900 2    50   Output ~ 0
MOT4_VREF
Text GLabel 2500 930  0    50   Input ~ 0
3V3_OUT
Wire Wire Line
	2500 930  2730 930 
Wire Wire Line
	4300 930  4300 1500
$Comp
L power:GND #PWR0203
U 1 1 5D469F60
P 4300 4480
F 0 "#PWR0203" H 4300 4230 50  0001 C CNN
F 1 "GND" H 4305 4307 50  0000 C CNN
F 2 "" H 4300 4480 50  0001 C CNN
F 3 "" H 4300 4480 50  0001 C CNN
	1    4300 4480
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 4300 4300 4480
$Comp
L Device:C C202
U 1 1 5D46B321
P 3450 1170
F 0 "C202" H 3160 1210 50  0000 L CNN
F 1 "22uF" H 3160 1120 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3488 1020 50  0001 C CNN
F 3 "~" H 3450 1170 50  0001 C CNN
	1    3450 1170
	1    0    0    -1  
$EndComp
$Comp
L Device:C C203
U 1 1 5D46BCFF
P 3800 1170
F 0 "C203" H 3915 1216 50  0000 L CNN
F 1 "0.1uF" H 3915 1125 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3838 1020 50  0001 C CNN
F 3 "~" H 3800 1170 50  0001 C CNN
	1    3800 1170
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0202
U 1 1 5D46C393
P 3450 1440
F 0 "#PWR0202" H 3450 1190 50  0001 C CNN
F 1 "GND" H 3455 1267 50  0000 C CNN
F 2 "" H 3450 1440 50  0001 C CNN
F 3 "" H 3450 1440 50  0001 C CNN
	1    3450 1440
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 1020 3450 930 
Connection ~ 3450 930 
Wire Wire Line
	3450 930  3800 930 
Wire Wire Line
	3800 1020 3800 930 
Connection ~ 3800 930 
Wire Wire Line
	3800 930  4300 930 
Wire Wire Line
	3450 1320 3450 1390
Wire Wire Line
	3800 1320 3800 1390
Wire Wire Line
	3800 1390 3450 1390
Connection ~ 3450 1390
Wire Wire Line
	3450 1390 3450 1440
$Comp
L Device:R R201
U 1 1 5D46E73C
P 2730 1390
F 0 "R201" H 2800 1436 50  0000 L CNN
F 1 "10K" H 2800 1345 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2660 1390 50  0001 C CNN
F 3 "~" H 2730 1390 50  0001 C CNN
	1    2730 1390
	1    0    0    -1  
$EndComp
Wire Wire Line
	2730 1240 2730 930 
Connection ~ 2730 930 
Wire Wire Line
	2730 930  3450 930 
$Comp
L Device:C C201
U 1 1 5D46FA58
P 2730 1960
F 0 "C201" H 2410 2000 50  0000 L CNN
F 1 "0.1uF" H 2410 1910 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2768 1810 50  0001 C CNN
F 3 "~" H 2730 1960 50  0001 C CNN
	1    2730 1960
	1    0    0    -1  
$EndComp
Wire Wire Line
	2730 1540 2730 1700
Wire Wire Line
	3700 1700 2730 1700
Connection ~ 2730 1700
Wire Wire Line
	2730 1700 2730 1810
$Comp
L power:GND #PWR0201
U 1 1 5D47164E
P 2730 2420
F 0 "#PWR0201" H 2730 2170 50  0001 C CNN
F 1 "GND" H 2735 2247 50  0000 C CNN
F 2 "" H 2730 2420 50  0001 C CNN
F 3 "" H 2730 2420 50  0001 C CNN
	1    2730 2420
	1    0    0    -1  
$EndComp
Wire Wire Line
	2730 2110 2730 2330
$Comp
L Jumper:Jumper_2_Open JP201
U 1 1 5D4785F9
P 2060 2010
F 0 "JP201" V 1960 1720 50  0000 L CNN
F 1 "RESET" V 2070 1720 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2060 2010 50  0001 C CNN
F 3 "~" H 2060 2010 50  0001 C CNN
	1    2060 2010
	0    1    1    0   
$EndComp
Wire Wire Line
	2060 2210 2060 2330
Wire Wire Line
	2060 2330 2730 2330
Connection ~ 2730 2330
Wire Wire Line
	2730 2330 2730 2420
Wire Wire Line
	2060 1810 2060 1700
Wire Wire Line
	2060 1700 2730 1700
$Comp
L Jumper:Jumper_2_Open JP202
U 1 1 5D47D6DC
P 5400 1370
F 0 "JP202" V 5446 1282 50  0000 R CNN
F 1 "MODE" V 5355 1282 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5400 1370 50  0001 C CNN
F 3 "~" H 5400 1370 50  0001 C CNN
	1    5400 1370
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4900 1700 5400 1700
Wire Wire Line
	5400 1700 5400 1570
$Comp
L power:GND #PWR0204
U 1 1 5D480A65
P 5110 1180
F 0 "#PWR0204" H 5110 930 50  0001 C CNN
F 1 "GND" H 5115 1007 50  0000 C CNN
F 2 "" H 5110 1180 50  0001 C CNN
F 3 "" H 5110 1180 50  0001 C CNN
	1    5110 1180
	1    0    0    -1  
$EndComp
Wire Wire Line
	5110 1180 5110 1090
Wire Wire Line
	5110 1090 5400 1090
Wire Wire Line
	5400 1090 5400 1170
$Comp
L power:GND #PWR0205
U 1 1 5D483E5D
P 6200 2080
F 0 "#PWR0205" H 6200 1830 50  0001 C CNN
F 1 "GND" H 6205 1907 50  0000 C CNN
F 2 "" H 6200 2080 50  0001 C CNN
F 3 "" H 6200 2080 50  0001 C CNN
	1    6200 2080
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2080 6200 2000
Wire Wire Line
	6200 2000 6310 2000
Wire Wire Line
	4900 2000 6100 2000
Wire Wire Line
	6100 2000 6100 1900
Wire Wire Line
	6100 1900 6310 1900
Wire Wire Line
	4900 1800 6310 1800
$Comp
L Connector_Generic:Conn_01x03 J201
U 1 1 5D49013C
P 6510 1900
F 0 "J201" H 6590 1942 50  0000 L CNN
F 1 "Program" H 6590 1851 50  0000 L CNN
F 2 "Connector_JST:JST_EH_B3B-EH-A_1x03_P2.50mm_Vertical" H 6510 1900 50  0001 C CNN
F 3 "~" H 6510 1900 50  0001 C CNN
	1    6510 1900
	1    0    0    -1  
$EndComp
Text GLabel 5160 2600 2    50   Output ~ 0
I2C_SCL
Text GLabel 5160 2400 2    50   BiDi ~ 0
I2C_SDA
Text GLabel 5160 2300 2    50   Input ~ 0
MPU_9250_INT
Wire Wire Line
	4900 2300 5160 2300
Wire Wire Line
	4900 3200 5150 3200
Wire Wire Line
	4900 3300 5150 3300
Wire Wire Line
	4900 3100 5140 3100
Wire Wire Line
	4900 2100 5160 2100
Wire Wire Line
	4900 2400 5160 2400
$Comp
L Device:R R202
U 1 1 5D220639
P 5910 1700
F 0 "R202" V 5703 1700 50  0000 C CNN
F 1 "R" V 5794 1700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5840 1700 50  0001 C CNN
F 3 "~" H 5910 1700 50  0001 C CNN
	1    5910 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	5760 1700 5400 1700
Connection ~ 5400 1700
$Comp
L Device:LED D201
U 1 1 5D222400
P 6170 1420
F 0 "D201" V 6209 1302 50  0000 R CNN
F 1 "LED" V 6118 1302 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 6170 1420 50  0001 C CNN
F 3 "~" H 6170 1420 50  0001 C CNN
	1    6170 1420
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6170 1570 6170 1700
Wire Wire Line
	6170 1700 6060 1700
Text GLabel 6080 1100 0    50   Input ~ 0
3V3_OUT
Wire Wire Line
	6080 1100 6170 1100
Wire Wire Line
	6170 1100 6170 1270
Wire Wire Line
	5160 2600 4900 2600
Wire Wire Line
	5160 1900 4900 1900
Wire Wire Line
	4900 2700 5160 2700
Wire Wire Line
	5160 2800 4900 2800
Wire Wire Line
	5160 2200 4900 2200
Wire Wire Line
	5160 3000 4900 3000
Wire Wire Line
	5160 2900 4900 2900
Wire Wire Line
	3440 1900 3700 1900
Wire Wire Line
	5160 4000 4900 4000
Wire Wire Line
	3440 2000 3700 2000
Wire Wire Line
	5160 3900 4900 3900
Wire Wire Line
	5160 3800 4900 3800
Wire Wire Line
	5160 3700 4900 3700
Text GLabel 5160 3400 2    50   Output ~ 0
MOT1_INB
Text GLabel 5160 3500 2    50   Output ~ 0
MOT1_INA
Wire Wire Line
	5160 3400 4900 3400
Wire Wire Line
	5160 3500 4900 3500
Wire Wire Line
	5160 3600 4900 3600
Wire Wire Line
	5160 2500 4900 2500
$EndSCHEMATC
