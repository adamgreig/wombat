EESchema Schematic File Version 2  date Sat 08 Oct 2011 20:26:03 BST
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
Sheet 1 5
Title "Wombat Root Schematic"
Date "8 oct 2011"
Rev "1"
Comp "C.U. Spaceflight"
Comment1 "Drawn by Adam Greig & Jon Sowman"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 5000 3500 0    60   ~ 0
TXDAT
Text Label 5000 3400 0    60   ~ 0
MXOUT
Text Label 5000 3300 0    60   ~ 0
CLK
Text Label 5000 3200 0    60   ~ 0
DATA
Text Label 5000 3100 0    60   ~ 0
LE
Text Label 5900 4650 0    60   ~ 0
TXDAT
Text Label 5900 4500 0    60   ~ 0
MXOUT
Text Label 5900 4400 0    60   ~ 0
CLK
Text Label 5900 4200 0    60   ~ 0
LE
Text Label 5900 4300 0    60   ~ 0
DATA
Wire Wire Line
	6200 4650 5850 4650
Wire Wire Line
	6200 4400 5850 4400
Wire Wire Line
	6200 4200 5850 4200
Wire Wire Line
	5150 3400 4950 3400
Wire Wire Line
	5150 3200 4950 3200
Wire Bus Line
	5250 3200 5250 5200
Wire Bus Line
	5250 5200 6300 5200
Wire Wire Line
	4950 3000 6650 3000
Wire Wire Line
	4950 3650 5850 3650
Wire Wire Line
	5850 3650 5850 3150
Wire Wire Line
	5850 3150 6650 3150
Wire Wire Line
	5850 4900 6050 4900
Wire Wire Line
	5850 3950 6650 3950
Wire Wire Line
	6650 3700 5900 3700
Wire Wire Line
	5900 3700 5900 2650
Wire Wire Line
	5900 2650 4050 2650
Wire Wire Line
	4050 2650 4050 3500
Wire Wire Line
	4050 3500 4250 3500
Wire Wire Line
	6650 3600 6000 3600
Wire Wire Line
	6000 3600 6000 2750
Wire Wire Line
	6000 2750 4150 2750
Wire Wire Line
	4150 2750 4150 3300
Wire Wire Line
	4150 3300 4250 3300
Wire Wire Line
	6500 3350 6650 3350
Wire Wire Line
	3950 4700 4050 4700
Wire Wire Line
	5050 4700 4550 4700
Wire Wire Line
	6050 4900 6050 4950
Wire Wire Line
	3950 4850 3950 4800
Wire Wire Line
	3950 4800 4050 4800
Wire Wire Line
	4250 4150 4150 4150
Wire Wire Line
	4150 4150 4150 4200
Wire Wire Line
	6650 4300 6550 4300
Wire Wire Line
	6550 4300 6550 4350
Wire Wire Line
	4250 4050 4150 4050
Wire Wire Line
	6450 4200 6650 4200
Wire Wire Line
	6550 4100 6650 4100
Wire Wire Line
	6100 3500 6650 3500
Wire Wire Line
	4250 3400 4100 3400
Wire Wire Line
	4100 3400 4100 2700
Wire Wire Line
	4100 2700 5950 2700
Wire Wire Line
	6650 3800 5950 3800
Wire Wire Line
	5950 3800 5950 2700
Wire Wire Line
	5850 4800 6100 4800
Wire Wire Line
	4000 2600 6100 2600
Wire Wire Line
	4000 2600 4000 3900
Wire Wire Line
	4000 3900 4250 3900
Connection ~ 6100 3350
Wire Wire Line
	6650 3250 5800 3250
Wire Wire Line
	5800 3250 5800 3750
Wire Wire Line
	5800 3750 4950 3750
Wire Wire Line
	5850 4100 6100 4100
Wire Wire Line
	6100 4100 6100 2600
Connection ~ 6100 3500
Wire Bus Line
	6300 5200 6300 4300
Wire Wire Line
	5150 3100 4950 3100
Wire Wire Line
	5150 3300 4950 3300
Wire Wire Line
	5150 3500 4950 3500
Wire Wire Line
	6200 4300 5850 4300
Wire Wire Line
	6200 4500 5850 4500
Entry Wire Line
	5150 3500 5250 3600
Entry Wire Line
	5150 3400 5250 3500
Entry Wire Line
	5150 3300 5250 3400
Entry Wire Line
	5150 3200 5250 3300
Entry Wire Line
	5150 3100 5250 3200
Entry Wire Line
	6200 4650 6300 4750
Entry Wire Line
	6200 4500 6300 4600
Entry Wire Line
	6200 4400 6300 4500
Entry Wire Line
	6200 4300 6300 4400
Entry Wire Line
	6200 4200 6300 4300
$Comp
L C C1
U 1 1 4E90A126
P 6300 3350
F 0 "C1" H 6350 3450 50  0000 L CNN
F 1 "100n" H 6350 3250 50  0000 L CNN
F 2 "SM0603" H 6400 3500 60  0001 C CNN
	1    6300 3350
	0    1    1    0   
$EndComp
$Sheet
S 5350 3850 500  1150
U 4E908D0A
F0 "Radio" 60
F1 "radio.sch" 60
F2 "RF_OUT" O R 5850 3950 60 
F3 "CE" I R 5850 4100 60 
F4 "LE" I R 5850 4200 60 
F5 "DATA" I R 5850 4300 60 
F6 "CLK" I R 5850 4400 60 
F7 "MUX_OUT" O R 5850 4500 60 
F8 "TX_DATA" I R 5850 4650 60 
F9 "GND" I R 5850 4900 60 
F10 "Vdd" I R 5850 4800 60 
$EndSheet
$Comp
L +5V #PWR9
U 1 1 4E90A0B5
P 6550 4100
F 0 "#PWR9" H 6550 4190 20  0001 C CNN
F 1 "+5V" H 6550 4190 30  0000 C CNN
	1    6550 4100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR1
U 1 1 4E90A039
P 3950 4700
F 0 "#PWR1" H 3950 4790 20  0001 C CNN
F 1 "+5V" H 3950 4790 30  0000 C CNN
	1    3950 4700
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR3
U 1 1 4E90A02D
P 4150 4050
F 0 "#PWR3" H 4150 4150 30  0001 C CNN
F 1 "VDD" H 4150 4160 30  0000 C CNN
	1    4150 4050
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR7
U 1 1 4E90A02B
P 6100 4800
F 0 "#PWR7" H 6100 4900 30  0001 C CNN
F 1 "VDD" H 6100 4910 30  0000 C CNN
	1    6100 4800
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR8
U 1 1 4E90A028
P 6450 4200
F 0 "#PWR8" H 6450 4300 30  0001 C CNN
F 1 "VDD" H 6450 4310 30  0000 C CNN
	1    6450 4200
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR5
U 1 1 4E90A01C
P 5050 4700
F 0 "#PWR5" H 5050 4800 30  0001 C CNN
F 1 "VDD" H 5050 4810 30  0000 C CNN
	1    5050 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 4E90A00F
P 4150 4200
F 0 "#PWR4" H 4150 4200 30  0001 C CNN
F 1 "GND" H 4150 4130 30  0001 C CNN
	1    4150 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 4E90A00B
P 6050 4950
F 0 "#PWR6" H 6050 4950 30  0001 C CNN
F 1 "GND" H 6050 4880 30  0001 C CNN
	1    6050 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 4E90A009
P 6550 4350
F 0 "#PWR10" H 6550 4350 30  0001 C CNN
F 1 "GND" H 6550 4280 30  0001 C CNN
	1    6550 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 4E90A005
P 3950 4850
F 0 "#PWR2" H 3950 4850 30  0001 C CNN
F 1 "GND" H 3950 4780 30  0001 C CNN
	1    3950 4850
	1    0    0    -1  
$EndComp
$Sheet
S 4050 4600 500  300 
U 4E908D93
F0 "Power Supply" 60
F1 "power.sch" 60
F2 "GND" O L 4050 4800 60 
F3 "3v3" O R 4550 4700 60 
F4 "5V" I L 4050 4700 60 
$EndSheet
$Sheet
S 6650 2900 500  1500
U 4E908D84
F0 "Connectors" 60
F1 "con.sch" 60
F2 "DATA" O L 6650 3000 60 
F3 "5V" O L 6650 4100 60 
F4 "TX" O L 6650 3150 60 
F5 "RX" I L 6650 3250 60 
F6 "DTR" O L 6650 3350 60 
F7 "RST" O L 6650 3500 60 
F8 "MOSI" I L 6650 3600 60 
F9 "SCK" I L 6650 3700 60 
F10 "MISO" O L 6650 3800 60 
F11 "RF_OUT" I L 6650 3950 60 
F12 "GND" I L 6650 4300 60 
F13 "Vdd" I L 6650 4200 60 
$EndSheet
$Sheet
S 4250 2900 700  1350
U 4E908D76
F0 "Microcontroller" 60
F1 "micro.sch" 60
F2 "GND" I L 4250 4150 60 
F3 "Vdd" I L 4250 4050 60 
F4 "PB5" B L 4250 3500 60 
F5 "PB4" B L 4250 3400 60 
F6 "PB3" B L 4250 3300 60 
F7 "PB2" B L 4250 3200 60 
F8 "PB1" B L 4250 3100 60 
F9 "PB0" B L 4250 3000 60 
F10 "PD5" B R 4950 4150 60 
F11 "PD4" B R 4950 4050 60 
F12 "PD3" B R 4950 3950 60 
F13 "PD2" B R 4950 3850 60 
F14 "PD1" B R 4950 3750 60 
F15 "PD0" B R 4950 3650 60 
F16 "ADC7" B L 4250 3750 60 
F17 "ADC6" B L 4250 3650 60 
F18 "PC5" B R 4950 3500 60 
F19 "PC4" B R 4950 3400 60 
F20 "PC3" B R 4950 3300 60 
F21 "PC2" B R 4950 3200 60 
F22 "PC1" B R 4950 3100 60 
F23 "PC0" B R 4950 3000 60 
F24 "RESET" I L 4250 3900 60 
$EndSheet
$EndSCHEMATC
