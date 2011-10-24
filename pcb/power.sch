EESchema Schematic File Version 2  date Sun 09 Oct 2011 15:55:55 BST
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
LIBS:wombat-cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 2 5
Title "Wombat Power Supply Schematic"
Date "8 oct 2011"
Rev "1"
Comp "C.U. Spaceflight"
Comment1 "Drawn by Adam Greig & Jon Sowman"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 5350 3600
Wire Wire Line
	5350 3600 5350 3750
Wire Wire Line
	5350 3750 5400 3750
Wire Wire Line
	7200 3900 7200 3850
Wire Wire Line
	7200 3850 7250 3850
Wire Wire Line
	7250 3550 7200 3550
Wire Wire Line
	6500 3550 6500 3600
Connection ~ 5800 4050
Wire Wire Line
	6500 3600 6200 3600
Wire Wire Line
	5400 3600 5050 3600
Wire Wire Line
	6500 4000 6500 4050
Wire Wire Line
	6500 4050 5050 4050
Wire Wire Line
	5050 4050 5050 4000
Wire Wire Line
	5800 4100 5800 4000
Wire Wire Line
	5050 3600 5050 3550
Wire Wire Line
	7250 3700 7200 3700
$Comp
L GND #PWR56
U 1 1 4E9093BB
P 7200 3900
F 0 "#PWR56" H 7200 3900 30  0001 C CNN
F 1 "GND" H 7200 3830 30  0001 C CNN
	1    7200 3900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR54
U 1 1 4E9093AF
P 7200 3550
F 0 "#PWR54" H 7200 3640 20  0001 C CNN
F 1 "+5V" H 7200 3640 30  0000 C CNN
	1    7200 3550
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR55
U 1 1 4E9093AB
P 7200 3700
F 0 "#PWR55" H 7200 3800 30  0001 C CNN
F 1 "VDD" H 7200 3810 30  0000 C CNN
	1    7200 3700
	1    0    0    -1  
$EndComp
Text HLabel 7250 3850 2    60   Output ~ 0
GND
Text HLabel 7250 3700 2    60   Output ~ 0
3v3
Text HLabel 7250 3550 2    60   Input ~ 0
5V
$Comp
L +5V #PWR51
U 1 1 4E90933E
P 5050 3550
F 0 "#PWR51" H 5050 3640 20  0001 C CNN
F 1 "+5V" H 5050 3640 30  0000 C CNN
	1    5050 3550
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR53
U 1 1 4E90931F
P 6500 3550
F 0 "#PWR53" H 6500 3650 30  0001 C CNN
F 1 "VDD" H 6500 3660 30  0000 C CNN
	1    6500 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR52
U 1 1 4E90930F
P 5800 4100
F 0 "#PWR52" H 5800 4100 30  0001 C CNN
F 1 "GND" H 5800 4030 30  0001 C CNN
	1    5800 4100
	1    0    0    -1  
$EndComp
$Comp
L C C22
U 1 1 4E9092E8
P 5050 3800
F 0 "C22" H 5100 3900 50  0000 L CNN
F 1 "1µ" H 5100 3700 50  0000 L CNN
	1    5050 3800
	1    0    0    -1  
$EndComp
$Comp
L CP1 C23
U 1 1 4E9092E1
P 6500 3800
F 0 "C23" H 6550 3900 50  0000 L CNN
F 1 "4µ7" H 6550 3700 50  0000 L CNN
	1    6500 3800
	1    0    0    -1  
$EndComp
$Comp
L TPS76333DBVT IC3
U 1 1 4E9092AA
P 5800 3650
F 0 "IC3" H 5900 3400 60  0000 C CNN
F 1 "TPS76333DBVT" H 5800 3850 60  0000 C CNN
F 2 "SOT23-5" H 5800 3650 60  0001 C CNN
F 4 "8461376" H 5800 3650 60  0001 C CNN "Farnell Order Code"
	1    5800 3650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
