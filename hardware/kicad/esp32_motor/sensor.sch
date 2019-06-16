EESchema Schematic File Version 4
LIBS:esp32_motor-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
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
L Sensor_Motion:MPU-9250 U601
U 1 1 5D2E602C
P 6000 3290
F 0 "U601" H 5540 4030 50  0000 C CNN
F 1 "MPU-9250" H 6310 2540 50  0000 C CNN
F 2 "Sensor_Motion:InvenSense_QFN-24_3x3mm_P0.4mm" H 6000 2290 50  0001 C CNN
F 3 "https://store.invensense.com/datasheets/invensense/MPU9250REV1.0.pdf" H 6000 3140 50  0001 C CNN
	1    6000 3290
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0603
U 1 1 5D2E7685
P 6000 4240
F 0 "#PWR0603" H 6000 3990 50  0001 C CNN
F 1 "GND" H 6005 4067 50  0000 C CNN
F 2 "" H 6000 4240 50  0001 C CNN
F 3 "" H 6000 4240 50  0001 C CNN
	1    6000 4240
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4190 6000 4210
$Comp
L Device:C C602
U 1 1 5D2E8CD1
P 6790 2130
F 0 "C602" H 6905 2176 50  0000 L CNN
F 1 "0.1uF" H 6905 2085 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6828 1980 50  0001 C CNN
F 3 "~" H 6790 2130 50  0001 C CNN
	1    6790 2130
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0604
U 1 1 5D2E9C71
P 6790 2390
F 0 "#PWR0604" H 6790 2140 50  0001 C CNN
F 1 "GND" H 6795 2217 50  0000 C CNN
F 2 "" H 6790 2390 50  0001 C CNN
F 3 "" H 6790 2390 50  0001 C CNN
	1    6790 2390
	1    0    0    -1  
$EndComp
Wire Wire Line
	6790 2390 6790 2280
Wire Wire Line
	6100 2390 6100 1940
Wire Wire Line
	6100 1940 6790 1940
Wire Wire Line
	6790 1940 6790 1980
Text GLabel 7720 1940 2    50   Input ~ 0
3V3_OUT
Wire Wire Line
	7720 1940 7310 1940
Connection ~ 6790 1940
$Comp
L Device:C C601
U 1 1 5D2EAF97
P 5280 2200
F 0 "C601" H 5395 2246 50  0000 L CNN
F 1 "10nF" H 5395 2155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5318 2050 50  0001 C CNN
F 3 "~" H 5280 2200 50  0001 C CNN
	1    5280 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2390 5900 1950
Wire Wire Line
	5900 1950 5280 1950
Wire Wire Line
	5280 1950 5280 2050
$Comp
L power:GND #PWR0602
U 1 1 5D2EBD7A
P 5280 2420
F 0 "#PWR0602" H 5280 2170 50  0001 C CNN
F 1 "GND" H 5285 2247 50  0000 C CNN
F 2 "" H 5280 2420 50  0001 C CNN
F 3 "" H 5280 2420 50  0001 C CNN
	1    5280 2420
	1    0    0    -1  
$EndComp
Wire Wire Line
	5280 2350 5280 2420
Text GLabel 5070 1950 0    50   Input ~ 0
3V3_OUT
Wire Wire Line
	5070 1950 5280 1950
Connection ~ 5280 1950
$Comp
L power:GND #PWR0601
U 1 1 5D2ECC41
P 4800 3090
F 0 "#PWR0601" H 4800 2840 50  0001 C CNN
F 1 "GND" V 4805 2962 50  0000 R CNN
F 2 "" H 4800 3090 50  0001 C CNN
F 3 "" H 4800 3090 50  0001 C CNN
	1    4800 3090
	0    1    1    0   
$EndComp
$Comp
L Device:R R603
U 1 1 5D2EDBC6
P 4650 2730
F 0 "R603" H 4720 2776 50  0000 L CNN
F 1 "4.7K" H 4720 2685 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4580 2730 50  0001 C CNN
F 3 "~" H 4650 2730 50  0001 C CNN
	1    4650 2730
	1    0    0    -1  
$EndComp
$Comp
L Device:R R602
U 1 1 5D2EE1B4
P 4350 2730
F 0 "R602" H 4420 2776 50  0000 L CNN
F 1 "4.7K" H 4420 2685 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4280 2730 50  0001 C CNN
F 3 "~" H 4350 2730 50  0001 C CNN
	1    4350 2730
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2990 4650 2990
Wire Wire Line
	4650 2990 4650 2880
Wire Wire Line
	5300 3190 4350 3190
Wire Wire Line
	4350 3190 4350 2880
Text GLabel 3970 2500 0    50   Input ~ 0
3V3_OUT
Wire Wire Line
	4350 2500 4350 2580
Wire Wire Line
	4650 2580 4650 2500
Wire Wire Line
	4650 2500 4350 2500
Connection ~ 4350 2500
Text GLabel 3960 2990 0    50   Input ~ 0
I2C_SDA
Text GLabel 3960 3190 0    50   Input ~ 0
I2C_SCL
Wire Wire Line
	3960 3190 4350 3190
Connection ~ 4350 3190
Wire Wire Line
	4650 2990 3960 2990
Connection ~ 4650 2990
$Comp
L Device:C C603
U 1 1 5D2F26D4
P 7010 3490
F 0 "C603" V 6758 3490 50  0000 C CNN
F 1 "0.1uF" V 6849 3490 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7048 3340 50  0001 C CNN
F 3 "~" H 7010 3490 50  0001 C CNN
	1    7010 3490
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0605
U 1 1 5D2F30AB
P 7250 3490
F 0 "#PWR0605" H 7250 3240 50  0001 C CNN
F 1 "GND" V 7255 3362 50  0000 R CNN
F 2 "" H 7250 3490 50  0001 C CNN
F 3 "" H 7250 3490 50  0001 C CNN
	1    7250 3490
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7250 3490 7160 3490
Wire Wire Line
	6860 3490 6700 3490
Text GLabel 7590 2990 2    50   Output ~ 0
MPU_9250_INT
Wire Wire Line
	6700 2990 7310 2990
$Comp
L Device:R R605
U 1 1 5D2F9666
P 7310 2650
F 0 "R605" H 7380 2696 50  0000 L CNN
F 1 "10K" H 7380 2605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7240 2650 50  0001 C CNN
F 3 "~" H 7310 2650 50  0001 C CNN
	1    7310 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7310 2500 7310 1940
Connection ~ 7310 1940
Wire Wire Line
	7310 1940 6790 1940
Wire Wire Line
	7310 2800 7310 2990
Connection ~ 7310 2990
Wire Wire Line
	7310 2990 7590 2990
Text GLabel 7340 3590 2    50   Input ~ 0
3V3_OUT
Wire Wire Line
	6700 3590 7340 3590
$Comp
L Device:R R604
U 1 1 5D2FCBFD
P 5190 3720
F 0 "R604" H 5260 3766 50  0000 L CNN
F 1 "10K" H 5260 3675 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5120 3720 50  0001 C CNN
F 3 "~" H 5190 3720 50  0001 C CNN
	1    5190 3720
	1    0    0    -1  
$EndComp
Wire Wire Line
	5190 3570 5190 3490
Wire Wire Line
	5190 3490 5300 3490
Wire Wire Line
	5190 3870 5190 4210
Wire Wire Line
	5190 4210 6000 4210
Connection ~ 6000 4210
Wire Wire Line
	6000 4210 6000 4240
Wire Wire Line
	6700 3690 6760 3690
Wire Wire Line
	6760 3690 6760 4210
Wire Wire Line
	6760 4210 6000 4210
$Comp
L Connector:TestPoint TP602
U 1 1 5D2FF32B
P 7180 3190
F 0 "TP602" V 7220 3400 50  0000 C CNN
F 1 "TP" V 7140 3420 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 7380 3190 50  0001 C CNN
F 3 "~" H 7380 3190 50  0001 C CNN
	1    7180 3190
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP603
U 1 1 5D2FF8C7
P 7180 3290
F 0 "TP603" V 7220 3500 50  0000 C CNN
F 1 "TP" V 7140 3520 50  0000 C CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 7380 3290 50  0001 C CNN
F 3 "~" H 7380 3290 50  0001 C CNN
	1    7180 3290
	0    1    1    0   
$EndComp
Wire Wire Line
	6700 3190 7180 3190
Wire Wire Line
	6700 3290 7180 3290
Wire Wire Line
	3970 2500 4080 2500
$Comp
L Device:R R601
U 1 1 5D302DD7
P 4080 2730
F 0 "R601" H 4150 2776 50  0000 L CNN
F 1 "10K" H 4150 2685 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4010 2730 50  0001 C CNN
F 3 "~" H 4080 2730 50  0001 C CNN
	1    4080 2730
	1    0    0    -1  
$EndComp
Wire Wire Line
	4080 2580 4080 2500
Connection ~ 4080 2500
Wire Wire Line
	4080 2500 4350 2500
Wire Wire Line
	4080 2880 4080 3290
Wire Wire Line
	4080 3290 5300 3290
$Comp
L Device:R R606
U 1 1 5D30634F
P 5090 3090
F 0 "R606" V 4883 3090 50  0000 C CNN
F 1 "10K" V 4974 3090 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5020 3090 50  0001 C CNN
F 3 "~" H 5090 3090 50  0001 C CNN
	1    5090 3090
	0    1    1    0   
$EndComp
Wire Wire Line
	5240 3090 5300 3090
Wire Wire Line
	4940 3090 4800 3090
$EndSCHEMATC
