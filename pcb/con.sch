EESchema Schematic File Version 2  date Sun 19 Feb 2012 01:14:43 GMT
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
Sheet 5 5
Title "Wombat Connectors Schematic"
Date "19 feb 2012"
Rev "1"
Comp "C.U. Spaceflight"
Comment1 "Drawn by Adam Greig & Jon Sowman"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3500 3550 3550 3550
Wire Wire Line
	8850 3350 8800 3350
Wire Wire Line
	7950 3650 8000 3650
Connection ~ 7100 3950
Wire Wire Line
	7100 3950 7100 4050
Wire Wire Line
	7100 4050 8000 4050
Wire Wire Line
	8000 4050 8000 3950
Wire Wire Line
	8000 3950 7950 3950
Connection ~ 7100 3450
Wire Wire Line
	7100 3450 7100 3250
Wire Wire Line
	7100 3250 8000 3250
Wire Wire Line
	7150 3550 6750 3550
Wire Wire Line
	8000 3250 8000 3450
Wire Wire Line
	8000 3450 7950 3450
Wire Wire Line
	7150 3950 6850 3950
Wire Wire Line
	5900 3700 5950 3700
Wire Wire Line
	5050 3800 5100 3800
Wire Wire Line
	5050 3600 5100 3600
Connection ~ 3450 3850
Wire Wire Line
	3550 3750 3450 3750
Wire Wire Line
	3450 3950 3550 3950
Wire Wire Line
	3450 3850 3550 3850
Connection ~ 3450 3950
Wire Wire Line
	3550 3650 3450 3650
Wire Wire Line
	3450 3650 3450 4000
Connection ~ 3450 3750
Wire Wire Line
	5050 3700 5100 3700
Wire Wire Line
	5900 3600 5900 3550
Wire Wire Line
	5900 3800 5900 3850
Wire Wire Line
	7150 3850 6850 3850
Wire Wire Line
	6850 3850 6850 4000
Connection ~ 6850 3950
Wire Wire Line
	7150 3650 7100 3650
Wire Wire Line
	7950 3550 8050 3550
Wire Wire Line
	8050 3550 8050 3200
Wire Wire Line
	7050 3450 7150 3450
Wire Wire Line
	8050 3200 6800 3200
Wire Wire Line
	6800 3200 6800 3550
Connection ~ 6800 3550
Wire Wire Line
	7950 3850 8050 3850
Wire Wire Line
	8050 3850 8050 4100
Wire Wire Line
	8050 4100 6750 4100
Wire Wire Line
	6750 4100 6750 3750
Wire Wire Line
	6750 3750 7150 3750
Connection ~ 6850 3750
Wire Wire Line
	7950 3750 8000 3750
Wire Wire Line
	8850 3500 8800 3500
Wire Wire Line
	8800 3500 8800 3550
Text HLabel 8850 3500 2    60   Input ~ 0
GND
Text HLabel 8850 3350 2    60   Input ~ 0
Vdd
$Comp
L GND #PWR50
U 1 1 4E909F05
P 8800 3550
F 0 "#PWR50" H 8800 3550 30  0001 C CNN
F 1 "GND" H 8800 3480 30  0001 C CNN
	1    8800 3550
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR49
U 1 1 4E909F03
P 8800 3350
F 0 "#PWR49" H 8800 3450 30  0001 C CNN
F 1 "VDD" H 8800 3460 30  0000 C CNN
	1    8800 3350
	1    0    0    -1  
$EndComp
Text HLabel 8000 3650 2    60   Output ~ 0
DATA
Text HLabel 8000 3750 2    60   Output ~ 0
5V
$Comp
L GND #PWR48
U 1 1 4E909DE1
P 6850 4000
F 0 "#PWR48" H 6850 4000 30  0001 C CNN
F 1 "GND" H 6850 3930 30  0001 C CNN
	1    6850 4000
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR47
U 1 1 4E909DDC
P 6850 3750
F 0 "#PWR47" H 6850 3850 30  0001 C CNN
F 1 "VDD" H 6850 3860 30  0000 C CNN
	1    6850 3750
	1    0    0    -1  
$EndComp
Text HLabel 7100 3650 0    60   Output ~ 0
TX
Text HLabel 6750 3550 0    60   Input ~ 0
RX
Text HLabel 7050 3450 0    60   Output ~ 0
DTR
$Comp
L GND #PWR46
U 1 1 4E909D5A
P 5900 3850
F 0 "#PWR46" H 5900 3850 30  0001 C CNN
F 1 "GND" H 5900 3780 30  0001 C CNN
	1    5900 3850
	1    0    0    -1  
$EndComp
Text HLabel 5050 3800 0    60   Output ~ 0
RST
Text HLabel 5950 3700 2    60   Input ~ 0
MOSI
Text HLabel 5050 3700 0    60   Input ~ 0
SCK
$Comp
L VDD #PWR45
U 1 1 4E909D31
P 5900 3550
F 0 "#PWR45" H 5900 3650 30  0001 C CNN
F 1 "VDD" H 5900 3660 30  0000 C CNN
	1    5900 3550
	1    0    0    -1  
$EndComp
Text HLabel 5050 3600 0    60   Output ~ 0
MISO
Text HLabel 3500 3550 0    60   Input ~ 0
RF_OUT
$Comp
L GND #PWR44
U 1 1 4E909CD9
P 3450 4000
F 0 "#PWR44" H 3450 4000 30  0001 C CNN
F 1 "GND" H 3450 3930 30  0001 C CNN
	1    3450 4000
	1    0    0    -1  
$EndComp
$Comp
L CONN_3X2 P2
U 1 1 4E909CBE
P 5500 3750
F 0 "P2" H 5500 4000 50  0000 C CNN
F 1 "CONN_3X2" V 5500 3800 40  0000 C CNN
	1    5500 3750
	1    0    0    -1  
$EndComp
$Comp
L CONN_6X2 P3
U 1 1 4E909CB6
P 7550 3700
F 0 "P3" H 7550 4050 60  0000 C CNN
F 1 "CONN_6X2" V 7550 3700 60  0000 C CNN
	1    7550 3700
	1    0    0    -1  
$EndComp
$Comp
L CONN_5 P1
U 1 1 4E909CB0
P 3950 3750
F 0 "P1" V 3900 3750 50  0000 C CNN
F 1 "CONN_5" V 4000 3750 50  0000 C CNN
	1    3950 3750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
