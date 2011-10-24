EESchema Schematic File Version 2  date Mon 24 Oct 2011 19:44:07 BST
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:wombat
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 4 4
Title ""
Date "24 oct 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 4900 4100
Wire Wire Line
	4900 4350 4900 4000
Wire Wire Line
	4900 4000 5000 4000
Connection ~ 4900 4300
Wire Wire Line
	4900 4200 5000 4200
Wire Wire Line
	3900 4500 3900 4550
Wire Wire Line
	5000 3800 4900 3800
Wire Wire Line
	6550 4800 6550 4750
Wire Wire Line
	6550 4750 6600 4750
Wire Wire Line
	6300 4650 6600 4650
Wire Wire Line
	6600 4550 6600 4500
Wire Wire Line
	6600 4500 6500 4500
Wire Wire Line
	6500 4500 6500 4550
Wire Wire Line
	5000 3900 3900 3900
Wire Wire Line
	4900 4300 5000 4300
Wire Wire Line
	4900 4100 5000 4100
Connection ~ 4900 4200
Wire Wire Line
	5000 3500 5000 3600
$Comp
L GND #PWR?
U 1 1 4EA5B100
P 4900 4350
F 0 "#PWR?" H 4900 4350 30  0001 C CNN
F 1 "GND" H 4900 4280 30  0001 C CNN
	1    4900 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4EA5B09F
P 3900 4550
F 0 "#PWR?" H 3900 4550 30  0001 C CNN
F 1 "GND" H 3900 4480 30  0001 C CNN
	1    3900 4550
	1    0    0    -1  
$EndComp
$Comp
L BATTERY BT?
U 1 1 4EA5B095
P 3900 4200
F 0 "BT?" H 3900 4400 50  0000 C CNN
F 1 "BATTERY" H 3900 4010 50  0000 C CNN
	1    3900 4200
	0    -1   -1   0   
$EndComp
$Comp
L VDD #PWR?
U 1 1 4EA5B068
P 4900 3800
F 0 "#PWR?" H 4900 3900 30  0001 C CNN
F 1 "VDD" H 4900 3910 30  0000 C CNN
	1    4900 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4EA5AFF5
P 6500 4550
F 0 "#PWR?" H 6500 4550 30  0001 C CNN
F 1 "GND" H 6500 4480 30  0001 C CNN
	1    6500 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4EA5AF45
P 6550 4800
F 0 "#PWR?" H 6550 4800 30  0001 C CNN
F 1 "GND" H 6550 4730 30  0001 C CNN
	1    6550 4800
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K?
U 1 1 4EA5AEC2
P 6950 4650
F 0 "K?" V 6900 4650 50  0000 C CNN
F 1 "CONN_3" V 7000 4650 40  0000 C CNN
	1    6950 4650
	1    0    0    -1  
$EndComp
$Comp
L NEO6Q U?
U 1 1 4EA5AE9F
P 5650 3950
F 0 "U?" H 6000 4750 60  0000 C CNN
F 1 "NEO6Q" H 5350 4750 60  0000 C CNN
	1    5650 3950
	1    0    0    -1  
$EndComp
$EndSCHEMATC
