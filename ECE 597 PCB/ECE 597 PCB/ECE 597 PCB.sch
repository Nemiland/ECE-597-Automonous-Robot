EESchema Schematic File Version 4
LIBS:ECE 597 PCB-cache
EELAYER 29 0
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
L ECE~ESP~32~WiFi~Kit:LogicShifter U3
U 1 1 5D358CE4
P 1800 6900
F 0 "U3" H 1550 7025 50  0001 C CNN
F 1 "LogicShifter1" H 1550 6933 50  0000 C CNN
F 2 "ECE 597 PCB:LogicShifter" V 1500 6550 50  0001 C CNN
F 3 "" V 1500 6550 50  0001 C CNN
	1    1800 6900
	-1   0    0    1   
$EndComp
$Comp
L ECE~ESP~32~WiFi~Kit:LogicShifter U2
U 1 1 5D35A517
P 1800 6300
F 0 "U2" H 1550 6425 50  0001 C CNN
F 1 "LogicShifter2" H 1550 6333 50  0000 C CNN
F 2 "ECE 597 PCB:LogicShifter" V 1500 5950 50  0001 C CNN
F 3 "" V 1500 5950 50  0001 C CNN
	1    1800 6300
	-1   0    0    1   
$EndComp
$Comp
L ECE~ESP~32~WiFi~Kit:LogicShifter U1
U 1 1 5D35B3BA
P 1800 5700
F 0 "U1" H 1550 5825 50  0001 C CNN
F 1 "LogicShifter3" H 1550 5733 50  0000 C CNN
F 2 "ECE 597 PCB:LogicShifter" V 1500 5350 50  0001 C CNN
F 3 "" V 1500 5350 50  0001 C CNN
	1    1800 5700
	-1   0    0    1   
$EndComp
$Comp
L ECE~ESP~32~WiFi~Kit:MotorControllerPololu U5
U 1 1 5D3659D7
P 4400 2700
F 0 "U5" H 3919 2326 50  0000 L CNN
F 1 "MC1" H 3919 2235 50  0000 L CNN
F 2 "ECE 597 PCB:MotCon" H 2350 2600 50  0001 C CNN
F 3 "" H 2350 2600 50  0001 C CNN
	1    4400 2700
	1    0    0    -1  
$EndComp
$Comp
L ECE~ESP~32~WiFi~Kit:MotorControllerPololu U6
U 1 1 5D365CE6
P 6300 2700
F 0 "U6" H 5819 2326 50  0000 L CNN
F 1 "MC2" H 5819 2235 50  0000 L CNN
F 2 "ECE 597 PCB:MotCon" H 4250 2600 50  0001 C CNN
F 3 "" H 4250 2600 50  0001 C CNN
	1    6300 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 5350 4350 5350
Connection ~ 4350 5050
Wire Wire Line
	4400 3050 4400 4750
Wire Wire Line
	4400 4750 4350 4750
Wire Wire Line
	1800 5400 1450 5400
Wire Wire Line
	1450 5400 1450 6000
Wire Wire Line
	1450 6000 1800 6000
Wire Wire Line
	1450 6000 1450 6600
Wire Wire Line
	1450 6600 1800 6600
Connection ~ 1450 6000
Connection ~ 1450 6600
$Comp
L ECE~ESP~32~WiFi~Kit:WiFiKit32 U4
U 1 1 5D32D1D2
P 4250 4900
F 0 "U4" H 3750 4975 50  0000 C CNN
F 1 "WiFiKit32" H 3750 4884 50  0000 C CNN
F 2 "ECE 597 PCB:WiFiKit32" H 3750 3100 50  0001 C CNN
F 3 "" H 3750 3100 50  0001 C CNN
	1    4250 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 5050 2650 5300
Wire Wire Line
	1450 6600 1450 7000
Wire Wire Line
	4550 5150 4550 7000
Wire Wire Line
	4550 7000 1450 7000
Wire Wire Line
	1350 5300 1350 5900
Wire Wire Line
	1350 5900 1350 6500
Connection ~ 1350 5900
Wire Wire Line
	3250 5450 2750 5450
Wire Wire Line
	2750 5450 2750 5100
Wire Wire Line
	2750 5100 2300 5100
Wire Wire Line
	3250 5550 2700 5550
Wire Wire Line
	2700 5550 2700 5200
Wire Wire Line
	2700 5200 2300 5200
Wire Wire Line
	3250 5650 2650 5650
Wire Wire Line
	2650 5650 2650 5500
Wire Wire Line
	2650 5500 2300 5500
Wire Wire Line
	3250 5750 2600 5750
Wire Wire Line
	2600 5750 2600 5600
Wire Wire Line
	2600 5600 2300 5600
Wire Wire Line
	2300 5700 2550 5700
Wire Wire Line
	2550 5700 2550 5850
Wire Wire Line
	2550 5850 3250 5850
Wire Wire Line
	2300 5800 2500 5800
Wire Wire Line
	2500 5800 2500 5950
Wire Wire Line
	2500 5950 3250 5950
Wire Wire Line
	2900 5400 2300 5400
Wire Wire Line
	2900 5400 2900 6000
Wire Wire Line
	2900 6000 2300 6000
Connection ~ 2900 5400
Wire Wire Line
	2900 6000 2900 6600
Wire Wire Line
	2900 6600 2300 6600
Connection ~ 2900 6000
Wire Wire Line
	3250 6050 2850 6050
Wire Wire Line
	2850 6050 2850 6100
Wire Wire Line
	2850 6100 2300 6100
Wire Wire Line
	3250 6150 2850 6150
Wire Wire Line
	2850 6150 2850 6200
Wire Wire Line
	2850 6200 2300 6200
Wire Wire Line
	3250 6250 2850 6250
Wire Wire Line
	2850 6250 2850 6300
Wire Wire Line
	2850 6300 2300 6300
Wire Wire Line
	3250 6350 2850 6350
Wire Wire Line
	2850 6350 2850 6400
Wire Wire Line
	2850 6400 2300 6400
Wire Wire Line
	3250 6450 2850 6450
Wire Wire Line
	2850 6450 2850 6700
Wire Wire Line
	2850 6700 2300 6700
Wire Wire Line
	3250 6550 2950 6550
Wire Wire Line
	2950 6550 2950 6800
Wire Wire Line
	2950 6800 2300 6800
Wire Wire Line
	900  3650 2900 3650
Wire Wire Line
	2900 3650 2900 3050
Wire Wire Line
	1800 6100 950  6100
Wire Wire Line
	950  6100 950  3700
Wire Wire Line
	950  3700 3200 3700
Wire Wire Line
	3200 3700 3200 3050
Wire Wire Line
	1800 5100 1050 5100
Wire Wire Line
	1050 5100 1050 3800
Wire Wire Line
	1050 3800 5100 3800
Wire Wire Line
	5100 3800 5100 3050
Wire Wire Line
	1800 5600 1000 5600
Wire Wire Line
	1000 5600 1000 3750
Wire Wire Line
	1000 3750 4800 3750
Wire Wire Line
	4800 3750 4800 3050
Wire Wire Line
	1800 6800 1100 6800
Wire Wire Line
	1100 6800 1100 3950
Wire Wire Line
	1100 3950 2700 3950
Wire Wire Line
	2700 3950 2700 3050
Wire Wire Line
	1800 6700 1150 6700
Wire Wire Line
	1150 6700 1150 4000
Wire Wire Line
	1150 4000 2800 4000
Wire Wire Line
	2800 4000 2800 3050
Wire Wire Line
	1800 6300 1250 6300
Wire Wire Line
	1250 6300 1250 4100
Wire Wire Line
	1250 4100 3000 4100
Wire Wire Line
	3000 4100 3000 3050
Wire Wire Line
	1800 6200 1300 6200
Wire Wire Line
	1300 6200 1300 4150
Wire Wire Line
	3100 4150 3100 3050
Wire Wire Line
	1300 4150 3100 4150
Wire Wire Line
	1800 5800 1500 5800
Wire Wire Line
	1500 5800 1500 4350
Wire Wire Line
	1500 4350 4600 4350
Wire Wire Line
	4600 4350 4600 3050
Wire Wire Line
	1800 5700 1550 5700
Wire Wire Line
	1550 5700 1550 4400
Wire Wire Line
	1550 4400 4700 4400
Wire Wire Line
	4700 4400 4700 3050
Wire Wire Line
	1800 5500 1650 5500
Wire Wire Line
	1650 5500 1650 4500
Wire Wire Line
	1650 4500 4900 4500
Wire Wire Line
	4900 4500 4900 3050
Wire Wire Line
	1800 5200 1700 5200
Wire Wire Line
	1700 5200 1700 4550
Wire Wire Line
	1700 4550 5000 4550
Wire Wire Line
	5000 4550 5000 3050
Wire Wire Line
	3500 3600 5400 3600
Wire Wire Line
	5400 3600 5400 5150
Wire Wire Line
	5400 5150 4550 5150
Connection ~ 5400 3600
Connection ~ 4550 5150
Wire Wire Line
	1350 6500 1800 6500
Connection ~ 1800 6500
Wire Wire Line
	1800 6500 2300 6500
Wire Wire Line
	1800 6400 900  6400
Wire Wire Line
	900  6400 900  3650
Wire Wire Line
	1350 5900 1800 5900
Connection ~ 1800 5900
Wire Wire Line
	1800 5900 2300 5900
Wire Wire Line
	1350 5300 1800 5300
Connection ~ 1800 5300
Wire Wire Line
	1800 5300 2300 5300
Connection ~ 2300 5300
Wire Wire Line
	2300 5300 2650 5300
Wire Wire Line
	2650 5050 3250 5050
Connection ~ 3250 5050
Wire Wire Line
	3250 5050 4250 5050
Wire Wire Line
	2900 5250 3250 5250
Connection ~ 3250 5250
Wire Wire Line
	3250 5250 4250 5250
Wire Wire Line
	4250 5150 4550 5150
Connection ~ 4250 5150
Wire Wire Line
	4250 5050 4350 5050
Connection ~ 4250 5050
Wire Wire Line
	3250 5150 4250 5150
Wire Wire Line
	5400 2950 5400 3050
Connection ~ 5400 3050
Wire Wire Line
	5400 3050 5400 3600
Wire Wire Line
	3500 2950 3500 3050
Connection ~ 3500 3050
Wire Wire Line
	3500 3050 3500 3600
Wire Wire Line
	2500 3050 2500 4800
Wire Wire Line
	4350 4750 4350 4800
Wire Wire Line
	2500 4800 4350 4800
Connection ~ 4350 4800
Wire Wire Line
	4350 4800 4350 5050
Wire Wire Line
	2900 5250 2900 5400
Wire Wire Line
	4350 5050 4350 5350
Connection ~ 4250 5250
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5D39E018
P 7150 5300
F 0 "J1" H 7230 5342 50  0000 L CNN
F 1 "Conn_01x03" H 7230 5251 50  0000 L CNN
F 2 "Connector_JST:JST_PH_B3B-PH-K_1x03_P2.00mm_Vertical" H 7150 5300 50  0001 C CNN
F 3 "~" H 7150 5300 50  0001 C CNN
	1    7150 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 5200 6950 4800
Wire Wire Line
	4250 5450 6950 5450
Wire Wire Line
	6950 5450 6950 5400
Wire Wire Line
	4250 5550 5800 5550
Wire Wire Line
	5800 5550 5800 5300
Wire Wire Line
	5800 5300 6950 5300
Wire Wire Line
	6950 4800 6350 4800
Wire Wire Line
	6350 4800 4350 4800
Connection ~ 6350 4800
Wire Wire Line
	6350 3750 6350 4800
$Comp
L ECE~ESP~32~WiFi~Kit:Waveshare10dof U7
U 1 1 5D3CB291
P 7000 3150
F 0 "U7" H 6572 3424 50  0000 R CNN
F 1 "Waveshare10dof" H 6572 3515 50  0000 R CNN
F 2 "ECE 597 PCB:Waveshare10dof" H 7000 3150 50  0001 C CNN
F 3 "" H 7000 3150 50  0001 C CNN
	1    7000 3150
	-1   0    0    1   
$EndComp
Wire Wire Line
	6900 3750 6900 3450
Wire Wire Line
	6350 3750 6900 3750
Wire Wire Line
	6800 5250 6800 3450
Wire Wire Line
	4250 5250 6800 5250
Wire Wire Line
	7000 6750 7000 3450
Wire Wire Line
	4250 6750 7000 6750
Wire Wire Line
	7100 6650 7100 3450
Wire Wire Line
	4250 6650 7100 6650
$EndSCHEMATC
