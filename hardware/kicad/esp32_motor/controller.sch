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
P 5530 3780
F 0 "U3" H 5080 5140 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 6020 2420 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 5530 2280 50  0000 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 5230 3830 50  0001 C CNN
	1    5530 3780
	1    0    0    -1  
$EndComp
Text GLabel 6390 4680 2    50   Output ~ 0
MOT2_INA
Text GLabel 6390 4580 2    50   Output ~ 0
MOT2_INB
Text GLabel 6390 3580 2    50   Output ~ 0
MOT3_INA
Text GLabel 6390 3680 2    50   Output ~ 0
MOT3_INB
Text GLabel 6390 2780 2    50   Output ~ 0
MOT4_INB
Text GLabel 6390 2980 2    50   Output ~ 0
MOT4_INA
Text GLabel 6390 4780 2    50   Input ~ 0
MOT1_ENCA
Text GLabel 6390 4880 2    50   Input ~ 0
MOT1_ENCB
Text GLabel 4670 2880 0    50   Input ~ 0
MOT2_ENCA
Text GLabel 4670 2780 0    50   Input ~ 0
MOT2_ENCB
Text GLabel 6380 4080 2    50   Input ~ 0
MOT3_ENCA
Text GLabel 6380 4180 2    50   Input ~ 0
MOT3_ENCB
Text GLabel 6390 3080 2    50   Input ~ 0
MOT4_ENCA
Text GLabel 6370 3980 2    50   Input ~ 0
MOT4_ENCB
Text GLabel 6390 3380 2    50   Output ~ 0
MOT1_VREF
Text GLabel 6390 4480 2    50   Output ~ 0
MOT2_VREF
Text GLabel 6390 3880 2    50   Output ~ 0
MOT3_VREF
Text GLabel 6390 3780 2    50   Output ~ 0
MOT4_VREF
Text GLabel 3730 1810 0    50   Input ~ 0
3V3_OUT
Wire Wire Line
	3730 1810 3960 1810
Wire Wire Line
	5530 1810 5530 2380
$Comp
L power:GND #PWR0203
U 1 1 5D469F60
P 5530 5360
F 0 "#PWR0203" H 5530 5110 50  0001 C CNN
F 1 "GND" H 5535 5187 50  0000 C CNN
F 2 "" H 5530 5360 50  0001 C CNN
F 3 "" H 5530 5360 50  0001 C CNN
	1    5530 5360
	1    0    0    -1  
$EndComp
Wire Wire Line
	5530 5180 5530 5360
$Comp
L Device:C C202
U 1 1 5D46B321
P 4680 2050
F 0 "C202" H 4390 2090 50  0000 L CNN
F 1 "22uF" H 4390 2000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4718 1900 50  0001 C CNN
F 3 "~" H 4680 2050 50  0001 C CNN
	1    4680 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C203
U 1 1 5D46BCFF
P 5030 2050
F 0 "C203" H 5145 2096 50  0000 L CNN
F 1 "0.1uF" H 5145 2005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5068 1900 50  0001 C CNN
F 3 "~" H 5030 2050 50  0001 C CNN
	1    5030 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0202
U 1 1 5D46C393
P 4680 2320
F 0 "#PWR0202" H 4680 2070 50  0001 C CNN
F 1 "GND" H 4685 2147 50  0000 C CNN
F 2 "" H 4680 2320 50  0001 C CNN
F 3 "" H 4680 2320 50  0001 C CNN
	1    4680 2320
	1    0    0    -1  
$EndComp
Wire Wire Line
	4680 1900 4680 1810
Connection ~ 4680 1810
Wire Wire Line
	4680 1810 5030 1810
Wire Wire Line
	5030 1900 5030 1810
Connection ~ 5030 1810
Wire Wire Line
	5030 1810 5530 1810
Wire Wire Line
	4680 2200 4680 2270
Wire Wire Line
	5030 2200 5030 2270
Wire Wire Line
	5030 2270 4680 2270
Connection ~ 4680 2270
Wire Wire Line
	4680 2270 4680 2320
$Comp
L Device:R R201
U 1 1 5D46E73C
P 3960 2270
F 0 "R201" H 4030 2316 50  0000 L CNN
F 1 "10K" H 4030 2225 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3890 2270 50  0001 C CNN
F 3 "~" H 3960 2270 50  0001 C CNN
	1    3960 2270
	1    0    0    -1  
$EndComp
Wire Wire Line
	3960 2120 3960 1810
Connection ~ 3960 1810
Wire Wire Line
	3960 1810 4680 1810
$Comp
L Device:C C201
U 1 1 5D46FA58
P 3960 2840
F 0 "C201" H 3640 2880 50  0000 L CNN
F 1 "0.1uF" H 3640 2790 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3998 2690 50  0001 C CNN
F 3 "~" H 3960 2840 50  0001 C CNN
	1    3960 2840
	1    0    0    -1  
$EndComp
Wire Wire Line
	3960 2420 3960 2580
Wire Wire Line
	4930 2580 3960 2580
Connection ~ 3960 2580
Wire Wire Line
	3960 2580 3960 2690
$Comp
L power:GND #PWR0201
U 1 1 5D47164E
P 3960 3300
F 0 "#PWR0201" H 3960 3050 50  0001 C CNN
F 1 "GND" H 3965 3127 50  0000 C CNN
F 2 "" H 3960 3300 50  0001 C CNN
F 3 "" H 3960 3300 50  0001 C CNN
	1    3960 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3960 2990 3960 3210
$Comp
L Jumper:Jumper_2_Open JP201
U 1 1 5D4785F9
P 3290 2890
F 0 "JP201" V 3190 2600 50  0000 L CNN
F 1 "RESET" V 3300 2600 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3290 2890 50  0001 C CNN
F 3 "~" H 3290 2890 50  0001 C CNN
	1    3290 2890
	0    1    1    0   
$EndComp
Wire Wire Line
	3290 3090 3290 3210
Wire Wire Line
	3290 3210 3960 3210
Connection ~ 3960 3210
Wire Wire Line
	3960 3210 3960 3300
Wire Wire Line
	3290 2690 3290 2580
Wire Wire Line
	3290 2580 3960 2580
$Comp
L Jumper:Jumper_2_Open JP202
U 1 1 5D47D6DC
P 6630 2250
F 0 "JP202" V 6676 2162 50  0000 R CNN
F 1 "MODE" V 6585 2162 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6630 2250 50  0001 C CNN
F 3 "~" H 6630 2250 50  0001 C CNN
	1    6630 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6130 2580 6630 2580
Wire Wire Line
	6630 2580 6630 2450
$Comp
L power:GND #PWR0204
U 1 1 5D480A65
P 6340 2060
F 0 "#PWR0204" H 6340 1810 50  0001 C CNN
F 1 "GND" H 6345 1887 50  0000 C CNN
F 2 "" H 6340 2060 50  0001 C CNN
F 3 "" H 6340 2060 50  0001 C CNN
	1    6340 2060
	1    0    0    -1  
$EndComp
Wire Wire Line
	6340 2060 6340 1970
Wire Wire Line
	6340 1970 6630 1970
Wire Wire Line
	6630 1970 6630 2050
$Comp
L power:GND #PWR0205
U 1 1 5D483E5D
P 7430 2960
F 0 "#PWR0205" H 7430 2710 50  0001 C CNN
F 1 "GND" H 7435 2787 50  0000 C CNN
F 2 "" H 7430 2960 50  0001 C CNN
F 3 "" H 7430 2960 50  0001 C CNN
	1    7430 2960
	1    0    0    -1  
$EndComp
Wire Wire Line
	7430 2960 7430 2880
Wire Wire Line
	7430 2880 7540 2880
Wire Wire Line
	6130 2880 7330 2880
Wire Wire Line
	7330 2880 7330 2780
Wire Wire Line
	7330 2780 7540 2780
Wire Wire Line
	6130 2680 7540 2680
$Comp
L Connector_Generic:Conn_01x03 J201
U 1 1 5D49013C
P 7740 2780
F 0 "J201" H 7820 2822 50  0000 L CNN
F 1 "Program" H 7820 2731 50  0000 L CNN
F 2 "Connector_JST:JST_PH_B3B-PH-K_1x03_P2.00mm_Vertical" H 7740 2780 50  0001 C CNN
F 3 "~" H 7740 2780 50  0001 C CNN
	1    7740 2780
	1    0    0    -1  
$EndComp
Text GLabel 6390 3480 2    50   Output ~ 0
I2C_SCL
Text GLabel 6390 3280 2    50   BiDi ~ 0
I2C_SDA
Text GLabel 6390 3180 2    50   Input ~ 0
MPU_9250_INT
Wire Wire Line
	6130 3180 6390 3180
Wire Wire Line
	6130 4080 6380 4080
Wire Wire Line
	6130 4180 6380 4180
Wire Wire Line
	6130 3980 6370 3980
Wire Wire Line
	6130 2980 6390 2980
Wire Wire Line
	6130 3280 6390 3280
$Comp
L Device:R R202
U 1 1 5D220639
P 7140 2580
F 0 "R202" V 6933 2580 50  0000 C CNN
F 1 "10K" V 7024 2580 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7070 2580 50  0001 C CNN
F 3 "~" H 7140 2580 50  0001 C CNN
	1    7140 2580
	0    1    1    0   
$EndComp
Wire Wire Line
	6990 2580 6630 2580
Connection ~ 6630 2580
$Comp
L Device:LED D201
U 1 1 5D222400
P 8660 2130
F 0 "D201" V 8699 2012 50  0000 R CNN
F 1 "LED" V 8608 2012 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 8660 2130 50  0001 C CNN
F 3 "~" H 8660 2130 50  0001 C CNN
	1    8660 2130
	0    -1   -1   0   
$EndComp
Text GLabel 8410 1460 0    50   Input ~ 0
3V3_OUT
Wire Wire Line
	6390 3480 6130 3480
Wire Wire Line
	6390 2780 6130 2780
Wire Wire Line
	6130 3580 6390 3580
Wire Wire Line
	6390 3680 6130 3680
Wire Wire Line
	6390 3080 6130 3080
Wire Wire Line
	6390 3880 6130 3880
Wire Wire Line
	6390 3780 6130 3780
Wire Wire Line
	4670 2780 4930 2780
Wire Wire Line
	4670 2880 4930 2880
Wire Wire Line
	6390 4680 6130 4680
Wire Wire Line
	6390 4580 6130 4580
Text GLabel 6390 4280 2    50   Output ~ 0
MOT1_INB
Text GLabel 6390 4380 2    50   Output ~ 0
MOT1_INA
Wire Wire Line
	6390 4280 6130 4280
Wire Wire Line
	6390 4380 6130 4380
Wire Wire Line
	6390 4480 6130 4480
Wire Wire Line
	6390 3380 6130 3380
$Comp
L Transistor_BJT:MMBT3904 Q201
U 1 1 5D2F39E0
P 8560 2580
F 0 "Q201" H 8751 2626 50  0000 L CNN
F 1 "MMBT2222" H 8751 2535 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8760 2505 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 8560 2580 50  0001 L CNN
	1    8560 2580
	1    0    0    -1  
$EndComp
Wire Wire Line
	7290 2580 8360 2580
$Comp
L Device:R R203
U 1 1 5D2F8444
P 8660 1750
F 0 "R203" V 8453 1750 50  0000 C CNN
F 1 "220R" V 8544 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8590 1750 50  0001 C CNN
F 3 "~" H 8660 1750 50  0001 C CNN
	1    8660 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8410 1460 8660 1460
Wire Wire Line
	8660 1460 8660 1600
Wire Wire Line
	8660 1900 8660 1980
Wire Wire Line
	8660 2280 8660 2380
$Comp
L power:GND #PWR0206
U 1 1 5D2FD2F7
P 8660 2870
F 0 "#PWR0206" H 8660 2620 50  0001 C CNN
F 1 "GND" H 8665 2697 50  0000 C CNN
F 2 "" H 8660 2870 50  0001 C CNN
F 3 "" H 8660 2870 50  0001 C CNN
	1    8660 2870
	1    0    0    -1  
$EndComp
Wire Wire Line
	8660 2780 8660 2870
NoConn ~ 4930 3780
NoConn ~ 4930 3880
NoConn ~ 4930 3980
NoConn ~ 4930 4080
NoConn ~ 4930 4180
NoConn ~ 4930 4280
Wire Wire Line
	6390 4780 6130 4780
Wire Wire Line
	6130 4880 6390 4880
$EndSCHEMATC
