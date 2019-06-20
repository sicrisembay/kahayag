EESchema Schematic File Version 4
LIBS:esp32_motor-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
Title "ESP32 MOTOR BOARD"
Date "2019-06-20"
Rev "1"
Comp "ZPL HACK PROJECT"
Comment1 "Author: Sicris Rey Embay"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Mechanical:MountingHole_Pad H701
U 1 1 5D219567
P 2100 1800
F 0 "H701" V 2337 1803 50  0000 C CNN
F 1 "MountingHole_Pad" V 2246 1803 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 2100 1800 50  0001 C CNN
F 3 "~" H 2100 1800 50  0001 C CNN
	1    2100 1800
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H702
U 1 1 5D219E68
P 2120 2320
F 0 "H702" V 2357 2323 50  0000 C CNN
F 1 "MountingHole_Pad" V 2266 2323 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 2120 2320 50  0001 C CNN
F 3 "~" H 2120 2320 50  0001 C CNN
	1    2120 2320
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H703
U 1 1 5D21A564
P 2130 2770
F 0 "H703" V 2367 2773 50  0000 C CNN
F 1 "MountingHole_Pad" V 2276 2773 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 2130 2770 50  0001 C CNN
F 3 "~" H 2130 2770 50  0001 C CNN
	1    2130 2770
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H704
U 1 1 5D21A8ED
P 2140 3220
F 0 "H704" V 2377 3223 50  0000 C CNN
F 1 "MountingHole_Pad" V 2286 3223 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 2140 3220 50  0001 C CNN
F 3 "~" H 2140 3220 50  0001 C CNN
	1    2140 3220
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5D21AD6E
P 2470 1800
F 0 "#PWR0116" H 2470 1550 50  0001 C CNN
F 1 "GND" V 2475 1672 50  0000 R CNN
F 2 "" H 2470 1800 50  0001 C CNN
F 3 "" H 2470 1800 50  0001 C CNN
	1    2470 1800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2470 1800 2200 1800
$Comp
L power:GND #PWR0117
U 1 1 5D21B63C
P 2480 2320
F 0 "#PWR0117" H 2480 2070 50  0001 C CNN
F 1 "GND" V 2485 2192 50  0000 R CNN
F 2 "" H 2480 2320 50  0001 C CNN
F 3 "" H 2480 2320 50  0001 C CNN
	1    2480 2320
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2480 2320 2220 2320
$Comp
L power:GND #PWR0118
U 1 1 5D21BDED
P 2510 2770
F 0 "#PWR0118" H 2510 2520 50  0001 C CNN
F 1 "GND" V 2515 2642 50  0000 R CNN
F 2 "" H 2510 2770 50  0001 C CNN
F 3 "" H 2510 2770 50  0001 C CNN
	1    2510 2770
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2510 2770 2230 2770
$Comp
L power:GND #PWR0119
U 1 1 5D21C231
P 2510 3220
F 0 "#PWR0119" H 2510 2970 50  0001 C CNN
F 1 "GND" V 2515 3092 50  0000 R CNN
F 2 "" H 2510 3220 50  0001 C CNN
F 3 "" H 2510 3220 50  0001 C CNN
	1    2510 3220
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2510 3220 2240 3220
$EndSCHEMATC
