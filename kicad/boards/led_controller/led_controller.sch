EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Transistor_FET:BUZ11 Q1
U 1 1 5EAC184C
P 1850 3100
F 0 "Q1" H 1800 3450 50  0000 L CNN
F 1 "BUZ11" H 1800 3350 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 2100 3025 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BU/BUZ11.pdf" H 1850 3100 50  0001 L CNN
	1    1850 3100
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BUZ11 Q2
U 1 1 5EAC18B0
P 2450 3100
F 0 "Q2" H 2400 3450 50  0000 L CNN
F 1 "BUZ11" H 2400 3350 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 2700 3025 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BU/BUZ11.pdf" H 2450 3100 50  0001 L CNN
	1    2450 3100
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BUZ11 Q3
U 1 1 5EAC18F7
P 3050 3100
F 0 "Q3" H 3000 3450 50  0000 L CNN
F 1 "BUZ11" H 3000 3350 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 3300 3025 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BU/BUZ11.pdf" H 3050 3100 50  0001 L CNN
	1    3050 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR07
U 1 1 5EAC1B8E
P 1950 3400
F 0 "#PWR07" H 1950 3150 50  0001 C CNN
F 1 "GNDD" H 1954 3245 50  0000 C CNN
F 2 "" H 1950 3400 50  0001 C CNN
F 3 "" H 1950 3400 50  0001 C CNN
	1    1950 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR08
U 1 1 5EAC1BBC
P 2550 3400
F 0 "#PWR08" H 2550 3150 50  0001 C CNN
F 1 "GNDD" H 2554 3245 50  0000 C CNN
F 2 "" H 2550 3400 50  0001 C CNN
F 3 "" H 2550 3400 50  0001 C CNN
	1    2550 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR011
U 1 1 5EAC1BEA
P 3150 3400
F 0 "#PWR011" H 3150 3150 50  0001 C CNN
F 1 "GNDD" H 3154 3245 50  0000 C CNN
F 2 "" H 3150 3400 50  0001 C CNN
F 3 "" H 3150 3400 50  0001 C CNN
	1    3150 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 3300 1950 3400
Wire Wire Line
	2550 3300 2550 3400
Wire Wire Line
	1650 3100 1600 3100
Wire Wire Line
	3150 3300 3150 3400
$Comp
L Device:R R1
U 1 1 5EAC2EA9
P 1600 3250
F 0 "R1" H 1670 3296 50  0000 L CNN
F 1 "10k" H 1670 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 1530 3250 50  0001 C CNN
F 3 "~" H 1600 3250 50  0001 C CNN
	1    1600 3250
	1    0    0    -1  
$EndComp
Connection ~ 1600 3100
Wire Wire Line
	1600 3100 1500 3100
$Comp
L Device:R R2
U 1 1 5EAC2F47
P 2200 3250
F 0 "R2" H 2270 3296 50  0000 L CNN
F 1 "10k" H 2270 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2130 3250 50  0001 C CNN
F 3 "~" H 2200 3250 50  0001 C CNN
	1    2200 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5EAC2F9C
P 2800 3250
F 0 "R3" H 2870 3296 50  0000 L CNN
F 1 "10k" H 2870 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 2730 3250 50  0001 C CNN
F 3 "~" H 2800 3250 50  0001 C CNN
	1    2800 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 3100 2200 3100
Wire Wire Line
	2200 3100 2100 3100
Connection ~ 2200 3100
Wire Wire Line
	2850 3100 2800 3100
Wire Wire Line
	2800 3100 2700 3100
Connection ~ 2800 3100
Wire Wire Line
	1600 3400 1950 3400
Connection ~ 1950 3400
Wire Wire Line
	2200 3400 2550 3400
Connection ~ 2550 3400
Wire Wire Line
	2800 3400 3150 3400
Connection ~ 3150 3400
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5EAEBD35
P 900 1100
F 0 "J1" H 1006 1278 50  0000 C CNN
F 1 "Conn_01x02_Male" H 1006 1187 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 900 1100 50  0001 C CNN
F 3 "~" H 900 1100 50  0001 C CNN
	1    900  1100
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR03
U 1 1 5EAEBE46
P 1450 1100
F 0 "#PWR03" H 1450 950 50  0001 C CNN
F 1 "+12V" H 1465 1273 50  0000 C CNN
F 2 "" H 1450 1100 50  0001 C CNN
F 3 "" H 1450 1100 50  0001 C CNN
	1    1450 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR04
U 1 1 5EAEBEC9
P 1450 1200
F 0 "#PWR04" H 1450 950 50  0001 C CNN
F 1 "GNDD" H 1454 1045 50  0000 C CNN
F 2 "" H 1450 1200 50  0001 C CNN
F 3 "" H 1450 1200 50  0001 C CNN
	1    1450 1200
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR010
U 1 1 5EAEBF59
P 2300 2050
F 0 "#PWR010" H 2300 1900 50  0001 C CNN
F 1 "+12V" H 2315 2223 50  0000 C CNN
F 2 "" H 2300 2050 50  0001 C CNN
F 3 "" H 2300 2050 50  0001 C CNN
	1    2300 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 2050 2300 2600
Wire Wire Line
	1100 1100 1450 1100
Wire Wire Line
	1100 1200 1450 1200
Wire Wire Line
	2450 2500 2450 2600
Wire Wire Line
	2300 2600 2450 2600
Wire Wire Line
	2750 2500 2750 2700
Wire Wire Line
	2750 2700 3150 2700
Wire Wire Line
	3150 2700 3150 2900
Wire Wire Line
	2650 2500 2650 2700
Wire Wire Line
	2650 2700 2550 2700
Wire Wire Line
	2550 2700 2550 2900
Wire Wire Line
	2550 2500 2550 2650
Wire Wire Line
	2550 2650 1950 2650
Wire Wire Line
	1950 2650 1950 2900
$Comp
L misc:XL6009_Boost U1
U 1 1 5F3C9419
P 2400 1100
F 0 "U1" H 2400 1375 50  0000 C CNN
F 1 "XL6009_Boost" H 2400 1284 50  0000 C CNN
F 2 "misc:XL6009_Boost" H 2400 1300 50  0001 C CNN
F 3 "" H 2400 1300 50  0001 C CNN
	1    2400 1100
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR01
U 1 1 5F3C95D7
P 1950 1050
F 0 "#PWR01" H 1950 900 50  0001 C CNN
F 1 "+12V" H 1965 1223 50  0000 C CNN
F 2 "" H 1950 1050 50  0001 C CNN
F 3 "" H 1950 1050 50  0001 C CNN
	1    1950 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR02
U 1 1 5F3C95DD
P 1950 1250
F 0 "#PWR02" H 1950 1000 50  0001 C CNN
F 1 "GNDD" H 1954 1095 50  0000 C CNN
F 2 "" H 1950 1250 50  0001 C CNN
F 3 "" H 1950 1250 50  0001 C CNN
	1    1950 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR05
U 1 1 5F3D3C5B
P 2850 1250
F 0 "#PWR05" H 2850 1000 50  0001 C CNN
F 1 "GNDD" H 2854 1095 50  0000 C CNN
F 2 "" H 2850 1250 50  0001 C CNN
F 3 "" H 2850 1250 50  0001 C CNN
	1    2850 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1050 2050 1050
Wire Wire Line
	1950 1250 2050 1250
Wire Wire Line
	2750 1250 2850 1250
$Comp
L ESP8266:ESP-12E U2
U 1 1 62AA04FB
P 5750 3700
F 0 "U2" H 5750 4465 50  0000 C CNN
F 1 "ESP-12E" H 5750 4374 50  0000 C CNN
F 2 "ESP8266:ESP-12E_SMD" H 5750 3700 50  0001 C CNN
F 3 "http://l0l.org.uk/2014/12/esp8266-modules-hardware-guide-gotta-catch-em-all/" H 5750 3700 50  0001 C CNN
	1    5750 3700
	1    0    0    -1  
$EndComp
NoConn ~ 5500 4600
NoConn ~ 5600 4600
NoConn ~ 5700 4600
NoConn ~ 5800 4600
NoConn ~ 5900 4600
NoConn ~ 6000 4600
$Comp
L Device:R R4
U 1 1 62AF1367
P 4550 3400
F 0 "R4" V 4450 3400 50  0000 C CNN
F 1 "10k" V 4550 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4480 3400 50  0001 C CNN
F 3 "~" H 4550 3400 50  0001 C CNN
	1    4550 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 62AF2469
P 4550 3600
F 0 "R5" V 4650 3600 50  0000 C CNN
F 1 "10k" V 4550 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4480 3600 50  0001 C CNN
F 3 "~" H 4550 3600 50  0001 C CNN
	1    4550 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 4100 4750 4100
Connection ~ 4750 4100
Wire Wire Line
	4750 4100 4400 4100
Wire Wire Line
	4400 3600 4400 3400
$Comp
L power:+3.3V #PWR0101
U 1 1 62AFFC7E
P 4400 3250
F 0 "#PWR0101" H 4400 3100 50  0001 C CNN
F 1 "+3.3V" H 4415 3423 50  0000 C CNN
F 2 "" H 4400 3250 50  0001 C CNN
F 3 "" H 4400 3250 50  0001 C CNN
	1    4400 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 3250 4400 3400
Connection ~ 4400 3400
Wire Wire Line
	4700 3400 4850 3400
Wire Wire Line
	4700 3600 4850 3600
$Comp
L Device:R R6
U 1 1 62B03F28
P 6950 3800
F 0 "R6" V 6850 3800 50  0000 C CNN
F 1 "10K" V 6950 3800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6880 3800 50  0001 C CNN
F 3 "~" H 6950 3800 50  0001 C CNN
	1    6950 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 62B05FCA
P 6950 4000
F 0 "R7" V 6850 4000 50  0000 C CNN
F 1 "10K" V 6950 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6880 4000 50  0001 C CNN
F 3 "~" H 6950 4000 50  0001 C CNN
	1    6950 4000
	0    1    1    0   
$EndComp
$Comp
L power:GNDD #PWR0102
U 1 1 62B0B487
P 7100 4100
F 0 "#PWR0102" H 7100 3850 50  0001 C CNN
F 1 "GNDD" H 7104 3945 50  0000 C CNN
F 2 "" H 7100 4100 50  0001 C CNN
F 3 "" H 7100 4100 50  0001 C CNN
	1    7100 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0103
U 1 1 62B0D430
P 4750 4400
F 0 "#PWR0103" H 4750 4150 50  0001 C CNN
F 1 "GNDD" H 4754 4245 50  0000 C CNN
F 2 "" H 4750 4400 50  0001 C CNN
F 3 "" H 4750 4400 50  0001 C CNN
	1    4750 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0104
U 1 1 62B0DCCA
P 4400 4400
F 0 "#PWR0104" H 4400 4150 50  0001 C CNN
F 1 "GNDD" H 4404 4245 50  0000 C CNN
F 2 "" H 4400 4400 50  0001 C CNN
F 3 "" H 4400 4400 50  0001 C CNN
	1    4400 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4100 7100 4100
Wire Wire Line
	7100 4100 7100 4000
Connection ~ 7100 4100
Wire Wire Line
	6800 4000 6650 4000
Wire Wire Line
	6650 3800 6800 3800
$Comp
L power:+3.3V #PWR0105
U 1 1 62B1B236
P 7100 3650
F 0 "#PWR0105" H 7100 3500 50  0001 C CNN
F 1 "+3.3V" H 7115 3823 50  0000 C CNN
F 2 "" H 7100 3650 50  0001 C CNN
F 3 "" H 7100 3650 50  0001 C CNN
	1    7100 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3650 7100 3800
$Comp
L Device:C C2
U 1 1 62AF9F52
P 4750 4250
F 0 "C2" H 4600 4350 50  0000 L CNN
F 1 "100nF" H 4800 4150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4788 4100 50  0001 C CNN
F 3 "~" H 4750 4250 50  0001 C CNN
	1    4750 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 62AFB79B
P 4400 4250
F 0 "C1" H 4250 4350 50  0000 L CNN
F 1 "10uF" H 4450 4150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4438 4100 50  0001 C CNN
F 3 "~" H 4400 4250 50  0001 C CNN
	1    4400 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0106
U 1 1 62B448C9
P 2850 1050
F 0 "#PWR0106" H 2850 900 50  0001 C CNN
F 1 "+3.3V" H 2865 1223 50  0000 C CNN
F 2 "" H 2850 1050 50  0001 C CNN
F 3 "" H 2850 1050 50  0001 C CNN
	1    2850 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 1050 2850 1050
NoConn ~ 4850 3700
NoConn ~ 4850 3500
Wire Wire Line
	2100 3900 2100 3100
$Comp
L power:+3.3V #PWR0107
U 1 1 62BB9AF4
P 4200 4100
F 0 "#PWR0107" H 4200 3950 50  0001 C CNN
F 1 "+3.3V" V 4215 4228 50  0000 L CNN
F 2 "" H 4200 4100 50  0001 C CNN
F 3 "" H 4200 4100 50  0001 C CNN
	1    4200 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4400 4100 4200 4100
Connection ~ 4400 4100
Wire Wire Line
	1500 3100 1500 3800
Wire Wire Line
	2700 3100 2700 4000
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 62AAA45D
P 2650 2300
F 0 "J2" V 2712 2012 50  0000 R CNN
F 1 "Conn_01x05_Male" V 2803 2012 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 2650 2300 50  0001 C CNN
F 3 "~" H 2650 2300 50  0001 C CNN
	1    2650 2300
	0    -1   1    0   
$EndComp
$Comp
L Transistor_FET:BUZ11 Q4
U 1 1 62ADBDC3
P 3650 3100
F 0 "Q4" H 3600 3450 50  0000 L CNN
F 1 "BUZ11" H 3600 3350 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 3900 3025 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BU/BUZ11.pdf" H 3650 3100 50  0001 L CNN
	1    3650 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0108
U 1 1 62ADBDC9
P 3750 3400
F 0 "#PWR0108" H 3750 3150 50  0001 C CNN
F 1 "GNDD" H 3754 3245 50  0000 C CNN
F 2 "" H 3750 3400 50  0001 C CNN
F 3 "" H 3750 3400 50  0001 C CNN
	1    3750 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3300 3750 3400
$Comp
L Device:R R8
U 1 1 62ADBDD0
P 3400 3250
F 0 "R8" H 3470 3296 50  0000 L CNN
F 1 "10k" H 3470 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3330 3250 50  0001 C CNN
F 3 "~" H 3400 3250 50  0001 C CNN
	1    3400 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3100 3400 3100
Wire Wire Line
	3400 3100 3300 3100
Connection ~ 3400 3100
Wire Wire Line
	3400 3400 3750 3400
Connection ~ 3750 3400
Wire Wire Line
	3750 2650 2850 2650
Wire Wire Line
	2850 2650 2850 2500
Wire Wire Line
	3750 2650 3750 2900
Wire Wire Line
	1500 3800 4850 3800
Wire Wire Line
	2100 3900 4850 3900
Wire Wire Line
	2700 4000 4850 4000
Text Notes 2400 2300 0    55   ~ 0
+ G R B W
Wire Wire Line
	3300 3100 3300 3700
Wire Wire Line
	3300 3700 4050 3700
Wire Wire Line
	4050 3700 4050 2800
Wire Wire Line
	4050 2800 7300 2800
Wire Wire Line
	7300 2800 7300 3900
Wire Wire Line
	7300 3900 6650 3900
$EndSCHEMATC
