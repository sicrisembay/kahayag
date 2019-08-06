EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
Title "ESP32 MOTOR BOARD"
Date "2019-08-06"
Rev "2"
Comp "ZPL HACK PROJECT"
Comment1 "Author: Sicris Rey Embay"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x06 J401
U 1 1 5D48BAD4
P 4530 1620
F 0 "J401" H 4610 1612 50  0000 L CNN
F 1 "MOTOR1" H 4610 1521 50  0000 L CNN
F 2 "Connector_JST:JST_PH_B6B-PH-K_1x06_P2.00mm_Vertical" H 4530 1620 50  0001 C CNN
F 3 "~" H 4530 1620 50  0001 C CNN
	1    4530 1620
	1    0    0    -1  
$EndComp
Text GLabel 4060 1820 0    50   Input ~ 0
MOT1A_OUT
Text GLabel 4060 1920 0    50   Input ~ 0
MOT1B_OUT
Text GLabel 1440 1180 0    50   Output ~ 0
MOT1_ENCA
Text GLabel 1480 2270 0    50   Output ~ 0
MOT1_ENCB
Text GLabel 1480 3320 0    50   Output ~ 0
MOT2_ENCA
Text GLabel 1480 4100 0    50   Output ~ 0
MOT2_ENCB
$Comp
L Connector_Generic:Conn_01x06 J403
U 1 1 5D4BF808
P 8920 1700
F 0 "J403" H 9000 1692 50  0000 L CNN
F 1 "MOTOR3" H 9000 1601 50  0000 L CNN
F 2 "Connector_JST:JST_PH_B6B-PH-K_1x06_P2.00mm_Vertical" H 8920 1700 50  0001 C CNN
F 3 "~" H 8920 1700 50  0001 C CNN
	1    8920 1700
	1    0    0    -1  
$EndComp
Text GLabel 8450 1900 0    50   Input ~ 0
MOT3A_OUT
Text GLabel 8450 2000 0    50   Input ~ 0
MOT3B_OUT
Text GLabel 5690 1200 0    50   Output ~ 0
MOT3_ENCA
Text GLabel 5670 2280 0    50   Output ~ 0
MOT3_ENCB
$Comp
L power:GND #PWR0407
U 1 1 5D4BF817
P 8540 1800
F 0 "#PWR0407" H 8540 1550 50  0001 C CNN
F 1 "GND" V 8545 1672 50  0000 R CNN
F 2 "" H 8540 1800 50  0001 C CNN
F 3 "" H 8540 1800 50  0001 C CNN
	1    8540 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	8720 1800 8540 1800
Wire Wire Line
	8720 1900 8450 1900
Wire Wire Line
	8720 2000 8450 2000
$Comp
L Connector_Generic:Conn_01x06 J404
U 1 1 5D4C5D7A
P 9110 4050
F 0 "J404" H 9190 4042 50  0000 L CNN
F 1 "MOTOR4" H 9190 3951 50  0000 L CNN
F 2 "Connector_JST:JST_PH_B6B-PH-K_1x06_P2.00mm_Vertical" H 9110 4050 50  0001 C CNN
F 3 "~" H 9110 4050 50  0001 C CNN
	1    9110 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0408
U 1 1 5D4C5DA1
P 8720 4150
F 0 "#PWR0408" H 8720 3900 50  0001 C CNN
F 1 "GND" V 8725 4022 50  0000 R CNN
F 2 "" H 8720 4150 50  0001 C CNN
F 3 "" H 8720 4150 50  0001 C CNN
	1    8720 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	8720 4150 8910 4150
Text GLabel 5700 3430 0    50   Output ~ 0
MOT4_ENCA
Text GLabel 5700 4160 0    50   Output ~ 0
MOT4_ENCB
Text GLabel 8580 4250 0    50   Input ~ 0
MOT4A_OUT
Text GLabel 8580 4350 0    50   Input ~ 0
MOT4B_OUT
Wire Wire Line
	8580 4250 8910 4250
Wire Wire Line
	8580 4350 8910 4350
$Comp
L Device:C C402
U 1 1 5D4E9B42
P 5950 6820
F 0 "C402" H 5580 6940 50  0000 L CNN
F 1 "0.1uF" H 5590 6830 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5988 6670 50  0001 C CNN
F 3 "~" H 5950 6820 50  0001 C CNN
	1    5950 6820
	1    0    0    -1  
$EndComp
Wire Wire Line
	4060 4020 4390 4020
Wire Wire Line
	4060 3920 4390 3920
Text GLabel 4060 4020 0    50   Input ~ 0
MOT2B_OUT
Text GLabel 4060 3920 0    50   Input ~ 0
MOT2A_OUT
Wire Wire Line
	4200 3820 4390 3820
$Comp
L power:GND #PWR0404
U 1 1 5D4BC675
P 4200 3820
F 0 "#PWR0404" H 4200 3570 50  0001 C CNN
F 1 "GND" V 4205 3692 50  0000 R CNN
F 2 "" H 4200 3820 50  0001 C CNN
F 3 "" H 4200 3820 50  0001 C CNN
	1    4200 3820
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J402
U 1 1 5D48DA8C
P 4590 3720
F 0 "J402" H 4670 3712 50  0000 L CNN
F 1 "MOTOR2" H 4670 3621 50  0000 L CNN
F 2 "Connector_JST:JST_PH_B6B-PH-K_1x06_P2.00mm_Vertical" H 4590 3720 50  0001 C CNN
F 3 "~" H 4590 3720 50  0001 C CNN
	1    4590 3720
	1    0    0    -1  
$EndComp
$Comp
L Device:C C401
U 1 1 5D175F4E
P 3300 6800
F 0 "C401" H 3010 6930 50  0000 L CNN
F 1 "0.1uF" H 2970 6810 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3338 6650 50  0001 C CNN
F 3 "~" H 3300 6800 50  0001 C CNN
	1    3300 6800
	1    0    0    -1  
$EndComp
Text GLabel 2050 6160 0    50   Input ~ 0
3V3_OUT
$Comp
L power:GND #PWR0401
U 1 1 5D1765FE
P 2390 7360
F 0 "#PWR0401" H 2390 7110 50  0001 C CNN
F 1 "GND" H 2395 7187 50  0000 C CNN
F 2 "" H 2390 7360 50  0001 C CNN
F 3 "" H 2390 7360 50  0001 C CNN
	1    2390 7360
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U401
U 1 1 5D4BA1B0
P 2250 1180
F 0 "U401" H 2250 863 50  0000 C CNN
F 1 "74HC14" H 2250 954 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2250 1180 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2250 1180 50  0001 C CNN
	1    2250 1180
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U401
U 2 1 5D4BCF2F
P 2260 2270
F 0 "U401" H 2260 1953 50  0000 C CNN
F 1 "74HC14" H 2260 2044 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2260 2270 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2260 2270 50  0001 C CNN
	2    2260 2270
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U401
U 3 1 5D4BE781
P 2260 4970
F 0 "U401" H 2260 4653 50  0000 C CNN
F 1 "74HC14" H 2260 4744 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2260 4970 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2260 4970 50  0001 C CNN
	3    2260 4970
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U401
U 4 1 5D4BF8AC
P 2260 5570
F 0 "U401" H 2260 5253 50  0000 C CNN
F 1 "74HC14" H 2260 5344 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2260 5570 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2260 5570 50  0001 C CNN
	4    2260 5570
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U401
U 5 1 5D4C1249
P 2270 4100
F 0 "U401" H 2270 3783 50  0000 C CNN
F 1 "74HC14" H 2270 3874 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2270 4100 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2270 4100 50  0001 C CNN
	5    2270 4100
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U401
U 6 1 5D4C219D
P 2270 3320
F 0 "U401" H 2270 3003 50  0000 C CNN
F 1 "74HC14" H 2270 3094 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2270 3320 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2270 3320 50  0001 C CNN
	6    2270 3320
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U401
U 7 1 5D4C31B3
P 2390 6780
F 0 "U401" H 2620 6826 50  0000 L CNN
F 1 "74HC14" H 2620 6735 50  0000 L CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 2390 6780 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2390 6780 50  0001 C CNN
	7    2390 6780
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U402
U 1 1 5D4C44B5
P 6600 1200
F 0 "U402" H 6600 883 50  0000 C CNN
F 1 "74HC14" H 6600 974 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 6600 1200 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 6600 1200 50  0001 C CNN
	1    6600 1200
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U402
U 2 1 5D4C5FD0
P 6620 2280
F 0 "U402" H 6620 1963 50  0000 C CNN
F 1 "74HC14" H 6620 2054 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 6620 2280 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 6620 2280 50  0001 C CNN
	2    6620 2280
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U402
U 3 1 5D4C7481
P 6590 4960
F 0 "U402" H 6590 4643 50  0000 C CNN
F 1 "74HC14" H 6590 4734 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 6590 4960 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 6590 4960 50  0001 C CNN
	3    6590 4960
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U402
U 4 1 5D4C89DB
P 6590 5540
F 0 "U402" H 6590 5223 50  0000 C CNN
F 1 "74HC14" H 6590 5314 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 6590 5540 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 6590 5540 50  0001 C CNN
	4    6590 5540
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U402
U 5 1 5D4C9DC0
P 6590 4160
F 0 "U402" H 6590 3843 50  0000 C CNN
F 1 "74HC14" H 6590 3934 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 6590 4160 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 6590 4160 50  0001 C CNN
	5    6590 4160
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U402
U 6 1 5D4CAF78
P 6600 3430
F 0 "U402" H 6600 3113 50  0000 C CNN
F 1 "74HC14" H 6600 3204 50  0000 C CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 6600 3430 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 6600 3430 50  0001 C CNN
	6    6600 3430
	-1   0    0    1   
$EndComp
$Comp
L 74xx:74HC14 U402
U 7 1 5D4CD1E8
P 4920 6780
F 0 "U402" H 5150 6826 50  0000 L CNN
F 1 "74HC14" H 5150 6735 50  0000 L CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 4920 6780 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 4920 6780 50  0001 C CNN
	7    4920 6780
	1    0    0    -1  
$EndComp
Wire Wire Line
	4330 1920 4060 1920
Wire Wire Line
	4330 1820 4060 1820
Wire Wire Line
	4330 1720 4150 1720
$Comp
L power:GND #PWR0403
U 1 1 5D494038
P 4150 1720
F 0 "#PWR0403" H 4150 1470 50  0001 C CNN
F 1 "GND" V 4155 1592 50  0000 R CNN
F 2 "" H 4150 1720 50  0001 C CNN
F 3 "" H 4150 1720 50  0001 C CNN
	1    4150 1720
	0    1    1    0   
$EndComp
$Comp
L Device:R R401
U 1 1 5D520749
P 1680 1180
F 0 "R401" V 1473 1180 50  0000 C CNN
F 1 "100" V 1564 1180 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1610 1180 50  0001 C CNN
F 3 "~" H 1680 1180 50  0001 C CNN
	1    1680 1180
	0    1    1    0   
$EndComp
$Comp
L Device:R R404
U 1 1 5D520C63
P 1720 2270
F 0 "R404" V 1513 2270 50  0000 C CNN
F 1 "100" V 1604 2270 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1650 2270 50  0001 C CNN
F 3 "~" H 1720 2270 50  0001 C CNN
	1    1720 2270
	0    1    1    0   
$EndComp
$Comp
L Device:R R402
U 1 1 5D521447
P 1700 3320
F 0 "R402" V 1493 3320 50  0000 C CNN
F 1 "100" V 1584 3320 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1630 3320 50  0001 C CNN
F 3 "~" H 1700 3320 50  0001 C CNN
	1    1700 3320
	0    1    1    0   
$EndComp
$Comp
L Device:R R403
U 1 1 5D521CE7
P 1700 4100
F 0 "R403" V 1493 4100 50  0000 C CNN
F 1 "100" V 1584 4100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1630 4100 50  0001 C CNN
F 3 "~" H 1700 4100 50  0001 C CNN
	1    1700 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	1440 1180 1530 1180
Wire Wire Line
	1480 2270 1570 2270
Wire Wire Line
	1480 3320 1550 3320
Wire Wire Line
	1480 4100 1550 4100
Wire Wire Line
	1870 2270 1960 2270
Wire Wire Line
	1850 3320 1970 3320
Wire Wire Line
	1850 4100 1970 4100
Wire Wire Line
	1950 1180 1830 1180
$Comp
L Device:R R407
U 1 1 5D5442D8
P 3020 970
F 0 "R407" H 3090 1016 50  0000 L CNN
F 1 "DNP" H 3090 925 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2950 970 50  0001 C CNN
F 3 "~" H 3020 970 50  0001 C CNN
	1    3020 970 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R409
U 1 1 5D544B64
P 3360 970
F 0 "R409" H 3430 1016 50  0000 L CNN
F 1 "DNP" H 3430 925 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3290 970 50  0001 C CNN
F 3 "~" H 3360 970 50  0001 C CNN
	1    3360 970 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1180 3020 1180
Wire Wire Line
	3020 1180 3020 1120
Wire Wire Line
	2560 2270 3360 2270
Wire Wire Line
	3360 2270 3360 1520
Wire Wire Line
	4330 1420 3020 1420
Wire Wire Line
	3020 1420 3020 1180
Connection ~ 3020 1180
Wire Wire Line
	4330 1520 3360 1520
Connection ~ 3360 1520
Wire Wire Line
	3360 1520 3360 1120
Text GLabel 2440 630  0    50   Input ~ 0
ENC_V+
Wire Wire Line
	2440 630  2760 630 
Wire Wire Line
	3360 630  3360 820 
Wire Wire Line
	3020 820  3020 630 
Connection ~ 3020 630 
Wire Wire Line
	3020 630  3360 630 
$Comp
L Device:R R405
U 1 1 5D56E31E
P 2760 1390
F 0 "R405" H 2690 1344 50  0000 R CNN
F 1 "0" H 2690 1435 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2690 1390 50  0001 C CNN
F 3 "~" H 2760 1390 50  0001 C CNN
	1    2760 1390
	-1   0    0    1   
$EndComp
Wire Wire Line
	2760 1240 2760 630 
Connection ~ 2760 630 
Wire Wire Line
	2760 630  3020 630 
Wire Wire Line
	2760 1540 2760 1620
Wire Wire Line
	2760 1620 4330 1620
Text GLabel 2430 2760 0    50   Input ~ 0
ENC_V+
$Comp
L Device:R R408
U 1 1 5D57A9CC
P 3130 3010
F 0 "R408" H 3200 3056 50  0000 L CNN
F 1 "DNP" H 3200 2965 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3060 3010 50  0001 C CNN
F 3 "~" H 3130 3010 50  0001 C CNN
	1    3130 3010
	1    0    0    -1  
$EndComp
$Comp
L Device:R R410
U 1 1 5D57AFE9
P 3450 3010
F 0 "R410" H 3520 3056 50  0000 L CNN
F 1 "DNP" H 3520 2965 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3380 3010 50  0001 C CNN
F 3 "~" H 3450 3010 50  0001 C CNN
	1    3450 3010
	1    0    0    -1  
$EndComp
Wire Wire Line
	2430 2760 2830 2760
Wire Wire Line
	3450 2760 3450 2860
Wire Wire Line
	3130 2860 3130 2760
Connection ~ 3130 2760
Wire Wire Line
	3130 2760 3450 2760
Wire Wire Line
	3130 3160 3130 3320
Wire Wire Line
	3130 3520 4390 3520
Wire Wire Line
	3450 3160 3450 3620
Wire Wire Line
	3450 3620 4390 3620
Wire Wire Line
	2570 3320 3130 3320
Connection ~ 3130 3320
Wire Wire Line
	3130 3320 3130 3520
Wire Wire Line
	2570 4100 3450 4100
Wire Wire Line
	3450 4100 3450 3620
Connection ~ 3450 3620
$Comp
L Device:R R406
U 1 1 5D5A22D1
P 2830 3010
F 0 "R406" H 2760 2964 50  0000 R CNN
F 1 "0" H 2760 3055 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2760 3010 50  0001 C CNN
F 3 "~" H 2830 3010 50  0001 C CNN
	1    2830 3010
	-1   0    0    1   
$EndComp
Wire Wire Line
	2830 2860 2830 2760
Connection ~ 2830 2760
Wire Wire Line
	2830 2760 3130 2760
Wire Wire Line
	2830 3160 2830 3720
Wire Wire Line
	2830 3720 4390 3720
NoConn ~ 1960 4970
NoConn ~ 1960 5570
$Comp
L power:GND #PWR0402
U 1 1 5D5C0F8E
P 2710 5690
F 0 "#PWR0402" H 2710 5440 50  0001 C CNN
F 1 "GND" H 2715 5517 50  0000 C CNN
F 2 "" H 2710 5690 50  0001 C CNN
F 3 "" H 2710 5690 50  0001 C CNN
	1    2710 5690
	1    0    0    -1  
$EndComp
Wire Wire Line
	2560 4970 2710 4970
Wire Wire Line
	2710 4970 2710 5570
Wire Wire Line
	2560 5570 2710 5570
Connection ~ 2710 5570
Wire Wire Line
	2710 5570 2710 5690
$Comp
L Device:R R414
U 1 1 5D5DC1B2
P 6010 1200
F 0 "R414" V 5803 1200 50  0000 C CNN
F 1 "100" V 5894 1200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5940 1200 50  0001 C CNN
F 3 "~" H 6010 1200 50  0001 C CNN
	1    6010 1200
	0    1    1    0   
$EndComp
$Comp
L Device:R R412
U 1 1 5D5DC99D
P 5990 2280
F 0 "R412" V 5783 2280 50  0000 C CNN
F 1 "100" V 5874 2280 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5920 2280 50  0001 C CNN
F 3 "~" H 5990 2280 50  0001 C CNN
	1    5990 2280
	0    1    1    0   
$EndComp
$Comp
L Device:R R413
U 1 1 5D5DCE18
P 6000 3430
F 0 "R413" V 5793 3430 50  0000 C CNN
F 1 "100" V 5884 3430 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5930 3430 50  0001 C CNN
F 3 "~" H 6000 3430 50  0001 C CNN
	1    6000 3430
	0    1    1    0   
$EndComp
$Comp
L Device:R R411
U 1 1 5D5DD4B3
P 5980 4160
F 0 "R411" V 5773 4160 50  0000 C CNN
F 1 "100" V 5864 4160 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5910 4160 50  0001 C CNN
F 3 "~" H 5980 4160 50  0001 C CNN
	1    5980 4160
	0    1    1    0   
$EndComp
Wire Wire Line
	5690 1200 5860 1200
Wire Wire Line
	5670 2280 5840 2280
Wire Wire Line
	5700 3430 5850 3430
Wire Wire Line
	5700 4160 5830 4160
Wire Wire Line
	6160 1200 6300 1200
Wire Wire Line
	6140 2280 6320 2280
Wire Wire Line
	6150 3430 6300 3430
Wire Wire Line
	6130 4160 6290 4160
Text GLabel 10010 5300 2    50   Output ~ 0
ENC_V+
$Comp
L Device:R R421
U 1 1 5D6068EA
P 9600 5300
F 0 "R421" V 9393 5300 50  0000 C CNN
F 1 "0" V 9484 5300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9530 5300 50  0001 C CNN
F 3 "~" H 9600 5300 50  0001 C CNN
	1    9600 5300
	0    1    1    0   
$EndComp
$Comp
L Device:R R422
U 1 1 5D606EF1
P 9600 5620
F 0 "R422" V 9393 5620 50  0000 C CNN
F 1 "DNP" V 9484 5620 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9530 5620 50  0001 C CNN
F 3 "~" H 9600 5620 50  0001 C CNN
	1    9600 5620
	0    1    1    0   
$EndComp
Text GLabel 9250 5300 0    50   Input ~ 0
3V3_OUT
Wire Wire Line
	9450 5300 9250 5300
Wire Wire Line
	9750 5300 9900 5300
Text GLabel 9250 5620 0    50   Input ~ 0
5VDC
Wire Wire Line
	9250 5620 9450 5620
Wire Wire Line
	9750 5620 9900 5620
Wire Wire Line
	9900 5620 9900 5300
Connection ~ 9900 5300
Wire Wire Line
	9900 5300 10010 5300
Text GLabel 6800 680  0    50   Input ~ 0
ENC_V+
$Comp
L Device:R R420
U 1 1 5D616FC3
P 7800 970
F 0 "R420" H 7870 1016 50  0000 L CNN
F 1 "DNP" H 7870 925 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7730 970 50  0001 C CNN
F 3 "~" H 7800 970 50  0001 C CNN
	1    7800 970 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R418
U 1 1 5D617600
P 7530 980
F 0 "R418" H 7600 1026 50  0000 L CNN
F 1 "DNP" H 7600 935 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7460 980 50  0001 C CNN
F 3 "~" H 7530 980 50  0001 C CNN
	1    7530 980 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R416
U 1 1 5D6179B5
P 7250 980
F 0 "R416" H 7320 1026 50  0000 L CNN
F 1 "0" H 7320 935 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7180 980 50  0001 C CNN
F 3 "~" H 7250 980 50  0001 C CNN
	1    7250 980 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 680  7250 680 
Wire Wire Line
	7800 680  7800 820 
Wire Wire Line
	7530 830  7530 680 
Connection ~ 7530 680 
Wire Wire Line
	7530 680  7800 680 
Wire Wire Line
	7250 830  7250 680 
Connection ~ 7250 680 
Wire Wire Line
	7250 680  7530 680 
Wire Wire Line
	6900 1200 7530 1200
Wire Wire Line
	7530 1200 7530 1130
Wire Wire Line
	6920 2280 7800 2280
Wire Wire Line
	7800 2280 7800 1600
Wire Wire Line
	8720 1600 7800 1600
Connection ~ 7800 1600
Wire Wire Line
	7800 1600 7800 1120
Wire Wire Line
	8720 1500 7530 1500
Wire Wire Line
	7530 1500 7530 1200
Connection ~ 7530 1200
Wire Wire Line
	7250 1130 7250 1700
Wire Wire Line
	7250 1700 8720 1700
Text GLabel 6860 2780 0    50   Input ~ 0
ENC_V+
$Comp
L Device:R R419
U 1 1 5D63A774
P 7790 3050
F 0 "R419" H 7860 3096 50  0000 L CNN
F 1 "DNP" H 7860 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7720 3050 50  0001 C CNN
F 3 "~" H 7790 3050 50  0001 C CNN
	1    7790 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R417
U 1 1 5D63AFB0
P 7500 3060
F 0 "R417" H 7570 3106 50  0000 L CNN
F 1 "DNP" H 7570 3015 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7430 3060 50  0001 C CNN
F 3 "~" H 7500 3060 50  0001 C CNN
	1    7500 3060
	1    0    0    -1  
$EndComp
$Comp
L Device:R R415
U 1 1 5D63B438
P 7210 3060
F 0 "R415" H 7280 3106 50  0000 L CNN
F 1 "0" H 7280 3015 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7140 3060 50  0001 C CNN
F 3 "~" H 7210 3060 50  0001 C CNN
	1    7210 3060
	1    0    0    -1  
$EndComp
Wire Wire Line
	6860 2780 7210 2780
Wire Wire Line
	7790 2780 7790 2900
Wire Wire Line
	7500 2910 7500 2780
Connection ~ 7500 2780
Wire Wire Line
	7500 2780 7790 2780
Wire Wire Line
	7210 2910 7210 2780
Connection ~ 7210 2780
Wire Wire Line
	7210 2780 7500 2780
Wire Wire Line
	6900 3430 7500 3430
Wire Wire Line
	7500 3430 7500 3210
Wire Wire Line
	6890 4160 7790 4160
Wire Wire Line
	7790 4160 7790 3950
Wire Wire Line
	8910 3850 7500 3850
Wire Wire Line
	7500 3850 7500 3430
Connection ~ 7500 3430
Wire Wire Line
	8910 3950 7790 3950
Connection ~ 7790 3950
Wire Wire Line
	7790 3950 7790 3200
Wire Wire Line
	7210 3210 7210 4050
Wire Wire Line
	7210 4050 8910 4050
Wire Wire Line
	2050 6160 2390 6160
Wire Wire Line
	2390 6160 2390 6280
Wire Wire Line
	2390 7360 2390 7320
Wire Wire Line
	3300 6650 3300 6160
Wire Wire Line
	3300 6160 2390 6160
Connection ~ 2390 6160
Wire Wire Line
	3300 6950 3300 7320
Wire Wire Line
	3300 7320 2390 7320
Connection ~ 2390 7320
Wire Wire Line
	2390 7320 2390 7280
$Comp
L power:GND #PWR0406
U 1 1 5D695321
P 7110 5670
F 0 "#PWR0406" H 7110 5420 50  0001 C CNN
F 1 "GND" H 7115 5497 50  0000 C CNN
F 2 "" H 7110 5670 50  0001 C CNN
F 3 "" H 7110 5670 50  0001 C CNN
	1    7110 5670
	1    0    0    -1  
$EndComp
Wire Wire Line
	6890 4960 7110 4960
Wire Wire Line
	7110 4960 7110 5540
Wire Wire Line
	6890 5540 7110 5540
Connection ~ 7110 5540
Wire Wire Line
	7110 5540 7110 5670
NoConn ~ 6290 4960
NoConn ~ 6290 5540
Text GLabel 4270 6150 0    50   Input ~ 0
3V3_OUT
Wire Wire Line
	4270 6150 4920 6150
Wire Wire Line
	4920 6150 4920 6280
$Comp
L power:GND #PWR0405
U 1 1 5D6AC832
P 4920 7400
F 0 "#PWR0405" H 4920 7150 50  0001 C CNN
F 1 "GND" H 4925 7227 50  0000 C CNN
F 2 "" H 4920 7400 50  0001 C CNN
F 3 "" H 4920 7400 50  0001 C CNN
	1    4920 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4920 7400 4920 7340
Wire Wire Line
	4920 6150 5950 6150
Wire Wire Line
	5950 6150 5950 6670
Connection ~ 4920 6150
Wire Wire Line
	5950 6970 5950 7340
Wire Wire Line
	5950 7340 4920 7340
Connection ~ 4920 7340
Wire Wire Line
	4920 7340 4920 7280
$EndSCHEMATC
