EESchema Schematic File Version 4
LIBS:e-paper-296x128-bricklet-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "ePaper 296x128 Bricklet"
Date "2018-09-28"
Rev "1.0"
Comp "Tinkerforge GmbH"
Comment1 "Licensed under CERN OHL v.1.1"
Comment2 "Copyright (©) 2018, T.Schneidermann <tim@tinkerforge.com>"
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 550  7700 0    40   ~ 0
Copyright Tinkerforge GmbH 2018.\nThis documentation describes Open Hardware and is licensed under the\nCERN OHL v. 1.1.\nYou may redistribute and modify this documentation under the terms of the\nCERN OHL v.1.1. (http://ohwr.org/cernohl). This documentation is distributed\nWITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF\nMERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A\nPARTICULAR PURPOSE. Please see the CERN OHL v.1.1 for applicable\nconditions\n
$Comp
L tinkerforge:DRILL U4
U 1 1 4C6050A5
P 10650 6150
F 0 "U4" H 10700 6200 60  0001 C CNN
F 1 "DRILL" H 10650 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10650 6150 60  0001 C CNN
F 3 "" H 10650 6150 60  0001 C CNN
	1    10650 6150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U5
U 1 1 4C6050A2
P 10650 6350
F 0 "U5" H 10700 6400 60  0001 C CNN
F 1 "DRILL" H 10650 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 10650 6350 60  0001 C CNN
F 3 "" H 10650 6350 60  0001 C CNN
	1    10650 6350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U7
U 1 1 4C60509F
P 11000 6350
F 0 "U7" H 11050 6400 60  0001 C CNN
F 1 "DRILL" H 11000 6350 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 11000 6350 60  0001 C CNN
F 3 "" H 11000 6350 60  0001 C CNN
	1    11000 6350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DRILL U6
U 1 1 4C605099
P 11000 6150
F 0 "U6" H 11050 6200 60  0001 C CNN
F 1 "DRILL" H 11000 6150 60  0000 C CNN
F 2 "kicad-libraries:DRILL_NP" H 11000 6150 60  0001 C CNN
F 3 "" H 11000 6150 60  0001 C CNN
	1    11000 6150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:CON-SENSOR2 P1
U 1 1 4C5FCF27
P 800 1550
F 0 "P1" H 950 1950 60  0000 C CNN
F 1 "CON-SENSOR" V 950 1550 60  0000 C CNN
F 2 "kicad-libraries:CON-SENSOR2" H 800 1550 60  0001 C CNN
F 3 "" H 800 1550 60  0001 C CNN
	1    800  1550
	-1   0    0    -1  
$EndComp
$Comp
L tinkerforge:C C3
U 1 1 54F76B96
P 1450 1050
F 0 "C3" V 1550 1200 50  0000 L CNN
F 1 "10uF" V 1300 1050 50  0000 L CNN
F 2 "kicad-libraries:C0805" H 1450 1050 60  0001 C CNN
F 3 "" H 1450 1050 60  0001 C CNN
	1    1450 1050
	-1   0    0    1   
$EndComp
$Comp
L tinkerforge:C C4
U 1 1 54F77AA5
P 1800 1050
F 0 "C4" V 1900 1200 50  0000 L CNN
F 1 "1uF" V 1650 1050 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 1800 1050 60  0001 C CNN
F 3 "" H 1800 1050 60  0001 C CNN
	1    1800 1050
	-1   0    0    1   
$EndComp
$Comp
L tinkerforge:GND #PWR07
U 1 1 54F77AEA
P 1800 1400
F 0 "#PWR07" H 1800 1400 30  0001 C CNN
F 1 "GND" H 1800 1330 30  0001 C CNN
F 2 "" H 1800 1400 60  0001 C CNN
F 3 "" H 1800 1400 60  0001 C CNN
	1    1800 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1350 1450 1350
Wire Wire Line
	1800 1250 1800 1350
Connection ~ 1800 1350
Wire Wire Line
	1450 1250 1450 1350
Connection ~ 1450 1350
Wire Wire Line
	1150 1450 1250 1450
Wire Wire Line
	1250 1450 1250 800 
Wire Wire Line
	1250 800  1450 800 
Wire Wire Line
	1800 750  1800 800 
Wire Wire Line
	1450 800  1450 850 
Connection ~ 1450 800 
Connection ~ 1800 800 
$Comp
L tinkerforge:GND #PWR09
U 1 1 5A5EA870
P 1300 2350
F 0 "#PWR09" H 1300 2350 30  0001 C CNN
F 1 "GND" H 1300 2280 30  0001 C CNN
F 2 "" H 1300 2350 60  0001 C CNN
F 3 "" H 1300 2350 60  0001 C CNN
	1    1300 2350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C1
U 1 1 5A5EB0DF
P 1300 2100
F 0 "C1" V 1400 2250 50  0000 L CNN
F 1 "220pF" V 1150 2100 50  0000 L CNN
F 2 "kicad-libraries:C0402F" H 1300 2100 60  0001 C CNN
F 3 "" H 1300 2100 60  0001 C CNN
	1    1300 2100
	-1   0    0    1   
$EndComp
$Comp
L tinkerforge:GND #PWR010
U 1 1 5A5EB32B
P 800 2350
F 0 "#PWR010" H 800 2350 30  0001 C CNN
F 1 "GND" H 800 2280 30  0001 C CNN
F 2 "" H 800 2350 60  0001 C CNN
F 3 "" H 800 2350 60  0001 C CNN
	1    800  2350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:R_PACK4 RP1
U 1 1 5A5EB5CC
P 1650 1900
F 0 "RP1" H 1650 2350 50  0000 C CNN
F 1 "82" H 1650 1850 50  0000 C CNN
F 2 "kicad-libraries:4X0402" H 1650 1900 50  0001 C CNN
F 3 "" H 1650 1900 50  0000 C CNN
	1    1650 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1550 1450 1550
Wire Wire Line
	1450 1650 1150 1650
Wire Wire Line
	1150 1750 1450 1750
Wire Wire Line
	1450 1850 1300 1850
Wire Wire Line
	1300 1900 1300 1850
Connection ~ 1300 1850
Wire Wire Line
	1300 2300 1300 2350
Wire Wire Line
	800  2350 800  2000
Wire Wire Line
	1850 1550 2150 1550
Wire Wire Line
	2150 1650 1850 1650
Wire Wire Line
	1850 1750 2150 1750
Wire Wire Line
	1850 1850 2150 1850
Text GLabel 2150 1550 2    47   Output ~ 0
S-CS
Text GLabel 2150 1650 2    47   Output ~ 0
S-CLK
Text GLabel 2150 1750 2    47   Output ~ 0
S-MOSI
Text GLabel 2150 1850 2    47   Input ~ 0
S-MISO
$Comp
L tinkerforge:XMC1XXX48 U1
U 4 1 5A5EEDF8
P 5050 6400
F 0 "U1" H 4900 7050 60  0000 C CNN
F 1 "XMC1404" H 5050 5450 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 5200 6650 60  0001 C CNN
F 3 "" H 5200 6650 60  0000 C CNN
	4    5050 6400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:XMC1XXX48 U1
U 2 1 5A5EEE8C
P 4900 3050
F 0 "U1" H 4750 4000 60  0000 C CNN
F 1 "XMC1404" H 4900 2100 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 5050 3300 60  0001 C CNN
F 3 "" H 5050 3300 60  0000 C CNN
	2    4900 3050
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:XMC1XXX48 U1
U 1 1 5A5EEEE9
P 2000 5900
F 0 "U1" H 1850 6850 60  0000 C CNN
F 1 "XMC1404" H 2000 4950 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 2150 6150 60  0001 C CNN
F 3 "" H 2150 6150 60  0000 C CNN
	1    2000 5900
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:XMC1XXX48 U1
U 3 1 5A5EEFFE
P 5050 4850
F 0 "U1" H 4900 5350 60  0000 C CNN
F 1 "XMC1404" H 5050 4350 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 5200 5100 60  0001 C CNN
F 3 "" H 5200 5100 60  0000 C CNN
	3    5050 4850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:XMC1XXX48 U1
U 5 1 5A5EF05B
P 5050 1250
F 0 "U1" H 4900 1700 60  0000 C CNN
F 1 "XMC1404" H 5050 700 60  0000 C CNN
F 2 "kicad-libraries:QFN48-EP2" H 5200 1500 60  0001 C CNN
F 3 "" H 5200 1500 60  0000 C CNN
	5    5050 1250
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C14
U 1 1 5A5F0752
P 1450 6450
F 0 "C14" V 1550 6600 50  0000 L CNN
F 1 "220nF" V 1300 6350 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 1450 6450 60  0001 C CNN
F 3 "" H 1450 6450 60  0001 C CNN
	1    1450 6450
	-1   0    0    1   
$EndComp
$Comp
L tinkerforge:C C12
U 1 1 5A5F09B8
P 1100 6450
F 0 "C12" V 1200 6600 50  0000 L CNN
F 1 "100nF" V 950 6350 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 1100 6450 60  0001 C CNN
F 3 "" H 1100 6450 60  0001 C CNN
	1    1100 6450
	-1   0    0    1   
$EndComp
$Comp
L tinkerforge:C C13
U 1 1 5A5F0D03
P 1450 5500
F 0 "C13" V 1550 5650 50  0000 L CNN
F 1 "100nF" V 1300 5400 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 1450 5500 60  0001 C CNN
F 3 "" H 1450 5500 60  0001 C CNN
	1    1450 5500
	-1   0    0    1   
$EndComp
$Comp
L tinkerforge:C C6
U 1 1 5A5F0D85
P 1100 5500
F 0 "C6" V 1200 5650 50  0000 L CNN
F 1 "100nF" V 950 5400 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 1100 5500 60  0001 C CNN
F 3 "" H 1100 5500 60  0001 C CNN
	1    1100 5500
	-1   0    0    1   
$EndComp
$Comp
L tinkerforge:GND #PWR012
U 1 1 5A5F144D
P 1100 5800
F 0 "#PWR012" H 1100 5800 30  0001 C CNN
F 1 "GND" H 1100 5730 30  0001 C CNN
F 2 "" H 1100 5800 60  0001 C CNN
F 3 "" H 1100 5800 60  0001 C CNN
	1    1100 5800
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR013
U 1 1 5A5F1B15
P 1100 6750
F 0 "#PWR013" H 1100 6750 30  0001 C CNN
F 1 "GND" H 1100 6680 30  0001 C CNN
F 2 "" H 1100 6750 60  0001 C CNN
F 3 "" H 1100 6750 60  0001 C CNN
	1    1100 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 6700 1450 6700
Wire Wire Line
	1100 6650 1100 6700
Connection ~ 1100 6700
Wire Wire Line
	1450 6650 1450 6700
Connection ~ 1450 6700
Wire Wire Line
	1650 6200 1450 6200
Wire Wire Line
	1100 6050 1100 6100
Wire Wire Line
	1450 6250 1450 6200
Connection ~ 1450 6200
Wire Wire Line
	1650 6100 1100 6100
Connection ~ 1100 6200
Connection ~ 1100 6100
Wire Wire Line
	1650 5750 1450 5750
Wire Wire Line
	1100 5700 1100 5750
Wire Wire Line
	1450 5850 1650 5850
Wire Wire Line
	1450 5700 1450 5750
Connection ~ 1450 5750
Connection ~ 1100 5750
Wire Wire Line
	1100 5300 1100 5250
Wire Wire Line
	1650 5250 1450 5250
Connection ~ 1100 5250
Wire Wire Line
	1450 5300 1450 5250
Connection ~ 1450 5250
Wire Wire Line
	1650 5150 1100 5150
Connection ~ 1100 5150
Text GLabel 4350 4650 0    47   Input ~ 0
S-CS
Text GLabel 4350 4850 0    47   Input ~ 0
S-CLK
Text GLabel 4350 4750 0    47   Input ~ 0
S-MOSI
Text GLabel 4350 5150 0    47   Output ~ 0
S-MISO
Wire Wire Line
	4350 4650 4700 4650
Wire Wire Line
	4350 4750 4700 4750
Wire Wire Line
	4700 4850 4350 4850
Wire Wire Line
	4350 5150 4700 5150
Text Notes 3650 4550 0    39   ~ 0
SPI Slave\nP1.1 : USIC0_CH1-DX2E : SEL\nP1.2 : USIC0_CH1-DX0B : MOSI\nP1.3 : USIC0_CH1-DX1A : CLK\nP1.6 : USIC0_CH1-DOUT0 : MISO
NoConn ~ 4700 6800
NoConn ~ 4700 6700
NoConn ~ 4700 6600
NoConn ~ 4700 6500
NoConn ~ 4700 6400
NoConn ~ 4700 6300
NoConn ~ 4700 6200
NoConn ~ 4700 6100
NoConn ~ 4700 6000
NoConn ~ 4700 5050
NoConn ~ 4700 4950
NoConn ~ 4700 4550
$Comp
L tinkerforge:C C5
U 1 1 5A5FBCBA
P 1100 4050
F 0 "C5" V 1250 4000 50  0000 L CNN
F 1 "10pF" V 950 3950 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 1100 4050 60  0001 C CNN
F 3 "" H 1100 4050 60  0001 C CNN
	1    1100 4050
	0    -1   -1   0   
$EndComp
$Comp
L tinkerforge:C C2
U 1 1 5A5FBF73
P 1100 3450
F 0 "C2" V 1250 3400 50  0000 L CNN
F 1 "10pF" V 950 3350 50  0000 L CNN
F 2 "kicad-libraries:C0603F" H 1100 3450 60  0001 C CNN
F 3 "" H 1100 3450 60  0001 C CNN
	1    1100 3450
	0    -1   -1   0   
$EndComp
$Comp
L tinkerforge:CRYSTAL_3225 X1
U 1 1 5A5FC0A9
P 1450 3750
F 0 "X1" V 1450 3750 60  0000 C CNN
F 1 "16MHz" V 1800 3750 60  0000 C CNN
F 2 "kicad-libraries:CRYSTAL_3225" H 1450 3750 60  0001 C CNN
F 3 "" H 1450 3750 60  0000 C CNN
	1    1450 3750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1650 3800 2200 3800
Wire Wire Line
	1650 4050 1650 3800
Wire Wire Line
	2200 3700 1650 3700
Wire Wire Line
	1650 3700 1650 3450
$Comp
L tinkerforge:GND #PWR015
U 1 1 5A5FD017
P 1750 4200
F 0 "#PWR015" H 1750 4200 30  0001 C CNN
F 1 "GND" H 1750 4130 30  0001 C CNN
F 2 "" H 1750 4200 60  0001 C CNN
F 3 "" H 1750 4200 60  0001 C CNN
	1    1750 4200
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR016
U 1 1 5A5FD6B6
P 850 4200
F 0 "#PWR016" H 850 4200 30  0001 C CNN
F 1 "GND" H 850 4130 30  0001 C CNN
F 2 "" H 850 4200 60  0001 C CNN
F 3 "" H 850 4200 60  0001 C CNN
	1    850  4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3900 1750 4200
Wire Wire Line
	850  3450 850  4050
Wire Wire Line
	850  4050 900  4050
Wire Wire Line
	850  3450 900  3450
Connection ~ 850  4050
Text Notes 1050 3200 0    39   ~ 0
TSX-3225 16.0000MF18X-AC0\nno C - 1,00017\n3pF - 1,00008\n4.7pF - 1,00005\n9pF - 1,00001\n10pF - 1,00000MHz
$Comp
L tinkerforge:CONN_01X02 P4
U 1 1 5A5FEC07
P 4250 1600
F 0 "P4" H 4250 1750 50  0000 C CNN
F 1 "BOOT" V 4350 1600 50  0000 C CNN
F 2 "kicad-libraries:SolderJumper" H 4250 1600 50  0001 C CNN
F 3 "" H 4250 1600 50  0000 C CNN
	1    4250 1600
	-1   0    0    1   
$EndComp
$Comp
L tinkerforge:GND #PWR017
U 1 1 5A5FEF1C
P 4500 1700
F 0 "#PWR017" H 4500 1700 30  0001 C CNN
F 1 "GND" H 4500 1630 30  0001 C CNN
F 2 "" H 4500 1700 60  0001 C CNN
F 3 "" H 4500 1700 60  0001 C CNN
	1    4500 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 1550 4450 1550
Wire Wire Line
	4450 1650 4500 1650
Wire Wire Line
	4500 1650 4500 1700
$Comp
L tinkerforge:R R2
U 1 1 5A5FF8FD
P 3900 1450
F 0 "R2" V 3980 1450 50  0000 C CNN
F 1 "1k" V 3900 1450 50  0000 C CNN
F 2 "kicad-libraries:R0603F" H 3900 1450 60  0001 C CNN
F 3 "" H 3900 1450 60  0000 C CNN
	1    3900 1450
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:LED D1
U 1 1 5A5FFD2F
P 3400 1450
F 0 "D1" H 3400 1550 50  0000 C CNN
F 1 "blue" H 3400 1350 50  0000 C CNN
F 2 "kicad-libraries:D0603F" H 3400 1450 50  0001 C CNN
F 3 "" H 3400 1450 50  0000 C CNN
	1    3400 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 1350 3100 1450
Wire Wire Line
	3100 1450 3200 1450
Wire Wire Line
	3600 1450 3650 1450
Wire Wire Line
	4150 1450 4700 1450
NoConn ~ 4700 1650
NoConn ~ 4700 1350
NoConn ~ 4700 950 
NoConn ~ 4550 3800
NoConn ~ 4550 3700
NoConn ~ 4550 3600
NoConn ~ 4550 3500
NoConn ~ 4550 3200
NoConn ~ 4550 3100
$Comp
L tinkerforge:CONN_01X01 P5
U 1 1 5A620021
P 4350 5900
F 0 "P5" H 4350 6050 50  0000 C CNN
F 1 "BOOT" V 4450 5900 50  0000 C CNN
F 2 "kicad-libraries:DEBUG_PAD" H 4350 5900 50  0001 C CNN
F 3 "" H 4350 5900 50  0000 C CNN
	1    4350 5900
	-1   0    0    1   
$EndComp
Wire Wire Line
	4700 5900 4550 5900
Wire Wire Line
	1800 1350 1800 1400
Wire Wire Line
	1450 1350 1800 1350
Wire Wire Line
	1450 800  1800 800 
Wire Wire Line
	1800 800  1800 850 
Wire Wire Line
	1300 1850 1150 1850
Wire Wire Line
	1100 6700 1100 6750
Wire Wire Line
	1450 6700 1100 6700
Wire Wire Line
	1450 6200 1100 6200
Wire Wire Line
	1100 6200 1100 6250
Wire Wire Line
	1100 6100 1100 6200
Wire Wire Line
	1450 5750 1100 5750
Wire Wire Line
	1450 5750 1450 5850
Wire Wire Line
	1100 5750 1100 5800
Wire Wire Line
	1100 5250 1100 5150
Wire Wire Line
	1450 5250 1100 5250
Wire Wire Line
	1100 5150 1100 5100
Wire Wire Line
	850  4050 850  4200
Wire Wire Line
	1300 4050 1450 4050
Wire Wire Line
	1300 3450 1450 3450
$Comp
L tinkerforge:+5V #PWR?
U 1 1 5BAFE29A
P 1150 800
F 0 "#PWR?" H 1150 650 50  0001 C CNN
F 1 "+5V" H 1165 973 50  0000 C CNN
F 2 "" H 1150 800 50  0000 C CNN
F 3 "" H 1150 800 50  0000 C CNN
	1    1150 800 
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR?
U 1 1 5BAFE3F3
P 1800 750
F 0 "#PWR?" H 1800 600 50  0001 C CNN
F 1 "3V3" H 1815 923 50  0000 C CNN
F 2 "" H 1800 750 50  0000 C CNN
F 3 "" H 1800 750 50  0000 C CNN
	1    1800 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1250 1150 800 
$Comp
L tinkerforge:3V3 #PWR?
U 1 1 5BB014B7
P 3100 1350
F 0 "#PWR?" H 3100 1200 50  0001 C CNN
F 1 "3V3" H 3115 1523 50  0000 C CNN
F 2 "" H 3100 1350 50  0000 C CNN
F 3 "" H 3100 1350 50  0000 C CNN
	1    3100 1350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR?
U 1 1 5BB01693
P 1100 5100
F 0 "#PWR?" H 1100 4950 50  0001 C CNN
F 1 "3V3" H 1115 5273 50  0000 C CNN
F 2 "" H 1100 5100 50  0000 C CNN
F 3 "" H 1100 5100 50  0000 C CNN
	1    1100 5100
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:3V3 #PWR?
U 1 1 5BB01788
P 1100 6050
F 0 "#PWR?" H 1100 5900 50  0001 C CNN
F 1 "3V3" H 1000 6100 50  0000 C CNN
F 2 "" H 1100 6050 50  0000 C CNN
F 3 "" H 1100 6050 50  0000 C CNN
	1    1100 6050
	1    0    0    -1  
$EndComp
Connection ~ 1450 3450
Wire Wire Line
	1450 3450 1650 3450
Connection ~ 1450 4050
Wire Wire Line
	1450 4050 1650 4050
NoConn ~ 4550 3300
NoConn ~ 4550 3400
NoConn ~ 10150 750 
NoConn ~ 10150 1050
Wire Wire Line
	10150 2150 10000 2150
Wire Wire Line
	10000 2150 10000 2250
Wire Wire Line
	10000 2250 10150 2250
Wire Wire Line
	10000 2250 9050 2250
Wire Wire Line
	8300 2250 8300 2150
Connection ~ 10000 2250
$Comp
L tinkerforge:3V3 #PWR?
U 1 1 5BB011E6
P 8300 2150
F 0 "#PWR?" H 8300 2000 50  0001 C CNN
F 1 "3V3" H 8315 2323 50  0000 C CNN
F 2 "" H 8300 2150 50  0000 C CNN
F 3 "" H 8300 2150 50  0000 C CNN
	1    8300 2150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C?
U 1 1 5BB0125F
P 8650 2450
F 0 "C?" H 8780 2496 50  0000 L CNN
F 1 "4,7uF" H 8780 2405 50  0000 L CNN
F 2 "" H 8650 2450 60  0000 C CNN
F 3 "" H 8650 2450 60  0000 C CNN
	1    8650 2450
	1    0    0    -1  
$EndComp
Connection ~ 8650 2250
Wire Wire Line
	8650 2250 8300 2250
Wire Wire Line
	10150 2350 9050 2350
Wire Wire Line
	9050 2350 9050 2650
Wire Wire Line
	9050 2650 8650 2650
Wire Wire Line
	8650 2650 8300 2650
Connection ~ 8650 2650
$Comp
L tinkerforge:GND #PWR?
U 1 1 5BB0504D
P 8300 2650
F 0 "#PWR?" H 8300 2400 50  0001 C CNN
F 1 "GND" H 8305 2477 50  0000 C CNN
F 2 "" H 8300 2650 50  0000 C CNN
F 3 "" H 8300 2650 50  0000 C CNN
	1    8300 2650
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR?
U 1 1 5BB0510E
P 8300 1150
F 0 "#PWR?" H 8300 900 50  0001 C CNN
F 1 "GND" H 8305 977 50  0000 C CNN
F 2 "" H 8300 1150 50  0000 C CNN
F 3 "" H 8300 1150 50  0000 C CNN
	1    8300 1150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C?
U 1 1 5BB0518A
P 9100 1150
F 0 "C?" V 8833 1150 50  0000 C CNN
F 1 "1uF" V 8924 1150 50  0000 C CNN
F 2 "" H 9100 1150 60  0000 C CNN
F 3 "" H 9100 1150 60  0000 C CNN
	1    9100 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	8300 1150 8900 1150
Wire Wire Line
	9300 1150 10150 1150
Wire Wire Line
	10150 1450 8300 1450
$Comp
L tinkerforge:GND #PWR?
U 1 1 5BB0B30B
P 8300 1450
F 0 "#PWR?" H 8300 1200 50  0001 C CNN
F 1 "GND" H 8305 1277 50  0000 C CNN
F 2 "" H 8300 1450 50  0000 C CNN
F 3 "" H 8300 1450 50  0000 C CNN
	1    8300 1450
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR?
U 1 1 5BB0B375
P 8300 3700
F 0 "#PWR?" H 8300 3450 50  0001 C CNN
F 1 "GND" H 8305 3527 50  0000 C CNN
F 2 "" H 8300 3700 50  0000 C CNN
F 3 "" H 8300 3700 50  0000 C CNN
	1    8300 3700
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:Con24HT U?
U 1 1 5BB01CCB
P 10650 1850
F 0 "U?" H 10600 3100 50  0000 L CNN
F 1 "Con24HT" V 10800 1650 50  0000 L CNN
F 2 "" H 10650 1850 50  0001 C CNN
F 3 "" H 10650 1850 50  0001 C CNN
	1    10650 1850
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C?
U 1 1 5BB14469
P 8900 3350
F 0 "C?" H 8800 3450 50  0000 L CNN
F 1 "1uF" H 8750 3250 50  0000 L CNN
F 2 "" H 8900 3350 60  0000 C CNN
F 3 "" H 8900 3350 60  0000 C CNN
	1    8900 3350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C?
U 1 1 5BB0B3F4
P 8600 3350
F 0 "C?" H 8700 3250 50  0000 R CNN
F 1 "1uF" H 8750 3450 50  0000 R CNN
F 2 "" V 8783 3350 60  0000 C CNN
F 3 "" H 8600 3350 60  0000 C CNN
	1    8600 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	8300 3700 8300 3550
Wire Wire Line
	8300 3550 8600 3550
Wire Wire Line
	8900 3550 8600 3550
Connection ~ 8600 3550
Wire Wire Line
	8600 3150 8600 2750
Wire Wire Line
	8600 2750 9150 2750
Wire Wire Line
	9150 2750 9150 2450
Wire Wire Line
	9150 2450 10150 2450
Wire Wire Line
	10150 2650 9250 2650
Wire Wire Line
	9250 2650 9250 2900
Wire Wire Line
	9250 2900 8900 2900
Wire Wire Line
	8900 2900 8900 3150
Wire Wire Line
	10150 2850 9350 2850
Wire Wire Line
	9350 2850 9350 3000
Wire Wire Line
	9350 3000 9200 3000
Wire Wire Line
	9200 3000 9200 3150
$Comp
L tinkerforge:C C?
U 1 1 5BB2B344
P 9200 3350
F 0 "C?" H 9100 3450 50  0000 L CNN
F 1 "1uF" H 9050 3250 50  0000 L CNN
F 2 "" H 9200 3350 60  0000 C CNN
F 3 "" H 9200 3350 60  0000 C CNN
	1    9200 3350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C?
U 1 1 5BB2B576
P 9500 3350
F 0 "C?" H 9550 3450 50  0000 L CNN
F 1 "0,47uF" H 9550 3250 50  0000 L CNN
F 2 "" H 9500 3350 60  0000 C CNN
F 3 "" H 9500 3350 60  0000 C CNN
	1    9500 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 3050 9500 3050
Wire Wire Line
	9500 3050 9500 3150
Wire Wire Line
	9500 3550 9200 3550
Wire Wire Line
	8900 3550 9200 3550
Connection ~ 8900 3550
Connection ~ 9200 3550
Text GLabel 8800 2100 0    39   Input ~ 0
VCI
Wire Wire Line
	8800 2100 9050 2100
Wire Wire Line
	9050 2100 9050 2250
Connection ~ 9050 2250
Wire Wire Line
	9050 2250 8650 2250
Text GLabel 9750 850  0    39   Output ~ 0
GDR
Text GLabel 9750 950  0    39   Output ~ 0
RESE
Wire Wire Line
	9750 850  10150 850 
Wire Wire Line
	10150 950  9750 950 
Text GLabel 9750 1250 0    39   Output ~ 0
TSCL
Text GLabel 9750 1350 0    39   Output ~ 0
TSDA
Wire Wire Line
	9750 1250 10150 1250
Wire Wire Line
	10150 1350 9750 1350
Text GLabel 9750 1550 0    39   Output ~ 0
BUSY
Text GLabel 9750 1650 0    39   Input ~ 0
RES#
Text GLabel 9750 1750 0    39   Input ~ 0
DC#
Text GLabel 9750 1850 0    39   Input ~ 0
CS#
Text GLabel 9750 1950 0    39   BiDi ~ 0
SCL
Text GLabel 9750 2050 0    39   BiDi ~ 0
SDA
Wire Wire Line
	9750 1550 10150 1550
Wire Wire Line
	10150 1650 9750 1650
Wire Wire Line
	9750 1750 10150 1750
Wire Wire Line
	10150 1850 9750 1850
Wire Wire Line
	9750 1950 10150 1950
Wire Wire Line
	10150 2050 9750 2050
Text GLabel 9750 2750 0    39   Output ~ 0
VGH
Text GLabel 9750 2950 0    39   Output ~ 0
VGL
Wire Wire Line
	9750 2750 10150 2750
Wire Wire Line
	10150 2950 9750 2950
$Comp
L tinkerforge:C C?
U 1 1 5BB5F1CA
P 7350 4350
F 0 "C?" V 7083 4350 50  0000 C CNN
F 1 "1uF" V 7174 4350 50  0000 C CNN
F 2 "" H 7350 4350 60  0000 C CNN
F 3 "" H 7350 4350 60  0000 C CNN
	1    7350 4350
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:C C?
U 1 1 5BB5F2C9
P 7850 4550
F 0 "C?" H 7980 4596 50  0000 L CNN
F 1 "1uF" H 7980 4505 50  0000 L CNN
F 2 "" H 7850 4550 60  0000 C CNN
F 3 "" H 7850 4550 60  0000 C CNN
	1    7850 4550
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR?
U 1 1 5BB5F383
P 9550 4400
F 0 "#PWR?" H 9550 4150 50  0001 C CNN
F 1 "GND" H 9555 4227 50  0000 C CNN
F 2 "" H 9550 4400 50  0000 C CNN
F 3 "" H 9550 4400 50  0000 C CNN
	1    9550 4400
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DIODESCH D?
U 1 1 5BB5F437
P 8250 4750
F 0 "D?" H 8250 4943 40  0000 C CNN
F 1 "MBR0530" H 8250 4867 40  0000 C CNN
F 2 "" H 8250 4750 60  0000 C CNN
F 3 "" H 8250 4750 60  0000 C CNN
	1    8250 4750
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DIODESCH D?
U 1 1 5BB5F516
P 9050 4750
F 0 "D?" H 9050 4943 40  0000 C CNN
F 1 "MBR0530" H 9050 4867 40  0000 C CNN
F 2 "" H 9050 4750 60  0000 C CNN
F 3 "" H 9050 4750 60  0000 C CNN
	1    9050 4750
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:DIODESCH D?
U 1 1 5BB5F5D0
P 8250 5150
F 0 "D?" H 8250 5343 40  0000 C CNN
F 1 "MBR0530" H 8250 5267 40  0000 C CNN
F 2 "" H 8250 5150 60  0000 C CNN
F 3 "" H 8250 5150 60  0000 C CNN
	1    8250 5150
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C?
U 1 1 5BB5F7A1
P 8650 4950
F 0 "C?" H 8780 4996 50  0000 L CNN
F 1 "1uF" H 8780 4905 50  0000 L CNN
F 2 "" H 8650 4950 60  0000 C CNN
F 3 "" H 8650 4950 60  0000 C CNN
	1    8650 4950
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:INDUCTOR L?
U 1 1 5BB5FBC2
P 9350 5150
F 0 "L?" H 9350 5397 60  0000 C CNN
F 1 "47uH" H 9350 5291 60  0000 C CNN
F 2 "" H 9350 5150 60  0001 C CNN
F 3 "" H 9350 5150 60  0001 C CNN
	1    9350 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4350 7850 4350
Wire Wire Line
	9550 4350 9550 4400
Wire Wire Line
	9550 4350 9250 4350
Connection ~ 7850 4350
Wire Wire Line
	7850 4750 8050 4750
Wire Wire Line
	8450 4750 8650 4750
Connection ~ 8650 4750
Wire Wire Line
	8650 4750 8850 4750
Wire Wire Line
	9250 4750 9250 4350
Connection ~ 9250 4350
Wire Wire Line
	9250 4350 7850 4350
Wire Wire Line
	8650 5150 8450 5150
Wire Wire Line
	8650 5150 9050 5150
Connection ~ 8650 5150
Wire Wire Line
	8050 5150 7150 5150
Wire Wire Line
	7150 5150 7150 4350
Text GLabel 6950 5150 0    39   Input ~ 0
VGH
Wire Wire Line
	7150 5150 6950 5150
Connection ~ 7150 5150
Wire Wire Line
	7600 4750 7850 4750
Connection ~ 7850 4750
Text GLabel 7600 4750 0    39   Input ~ 0
VGL
Text GLabel 9250 5850 2    39   Input ~ 0
RESE
Wire Wire Line
	9250 5850 8650 5850
$Comp
L tinkerforge:R R?
U 1 1 5BB9269D
P 7700 5850
F 0 "R?" V 7492 5850 50  0000 C CNN
F 1 "2,2" V 7583 5850 50  0000 C CNN
F 2 "" H 7700 5850 60  0000 C CNN
F 3 "" H 7700 5850 60  0000 C CNN
	1    7700 5850
	0    1    1    0   
$EndComp
$Comp
L tinkerforge:GND #PWR?
U 1 1 5BB928E6
P 7150 5950
F 0 "#PWR?" H 7150 5700 50  0001 C CNN
F 1 "GND" H 7155 5777 50  0000 C CNN
F 2 "" H 7150 5950 50  0000 C CNN
F 3 "" H 7150 5950 50  0000 C CNN
	1    7150 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 5850 7150 5850
Wire Wire Line
	7150 5850 7150 5950
Text GLabel 6950 5500 0    39   Input ~ 0
GDR
$Comp
L tinkerforge:MOSFET_N_CH Q?
U 1 1 5BB98117
P 8550 5500
F 0 "Q?" H 8741 5546 50  0000 L CNN
F 1 "Sil304BDL" H 8741 5455 50  0000 L CNN
F 2 "" H 8750 5600 50  0000 C CNN
F 3 "" H 8550 5500 50  0000 C CNN
	1    8550 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 5150 8650 5300
Wire Wire Line
	8650 5700 8650 5850
Connection ~ 8650 5850
Wire Wire Line
	8650 5850 7950 5850
Wire Wire Line
	8350 5500 6950 5500
$Comp
L tinkerforge:3V3 #PWR?
U 1 1 5BBA77BF
P 10700 4350
F 0 "#PWR?" H 10700 4200 50  0001 C CNN
F 1 "3V3" H 10715 4523 50  0000 C CNN
F 2 "" H 10700 4350 50  0000 C CNN
F 3 "" H 10700 4350 50  0000 C CNN
	1    10700 4350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C?
U 1 1 5BBA7865
P 10300 5350
F 0 "C?" H 10430 5396 50  0000 L CNN
F 1 "1uF" H 10430 5305 50  0000 L CNN
F 2 "" H 10300 5350 60  0000 C CNN
F 3 "" H 10300 5350 60  0000 C CNN
	1    10300 5350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:C C?
U 1 1 5BBA799B
P 10700 5350
F 0 "C?" H 10830 5396 50  0000 L CNN
F 1 "10uF" H 10830 5305 50  0000 L CNN
F 2 "" H 10700 5350 60  0000 C CNN
F 3 "" H 10700 5350 60  0000 C CNN
	1    10700 5350
	1    0    0    -1  
$EndComp
$Comp
L tinkerforge:GND #PWR?
U 1 1 5BBA7A6A
P 9950 5950
F 0 "#PWR?" H 9950 5700 50  0001 C CNN
F 1 "GND" H 9955 5777 50  0000 C CNN
F 2 "" H 9950 5950 50  0000 C CNN
F 3 "" H 9950 5950 50  0000 C CNN
	1    9950 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 5150 9900 5150
Wire Wire Line
	10700 5150 10300 5150
Connection ~ 10300 5150
Wire Wire Line
	10700 5150 10700 4350
Connection ~ 10700 5150
Wire Wire Line
	9950 5950 9950 5550
Wire Wire Line
	9950 5550 10300 5550
Wire Wire Line
	10700 5550 10300 5550
Connection ~ 10300 5550
Wire Wire Line
	9900 5150 9900 4950
Wire Wire Line
	9900 4950 10150 4950
Connection ~ 9900 5150
Wire Wire Line
	9900 5150 10300 5150
Text GLabel 10150 4950 2    39   Output ~ 0
VCI
Text GLabel 3800 2600 0    39   BiDi ~ 0
SDA
Text GLabel 3800 2500 0    39   BiDi ~ 0
SCL
Wire Wire Line
	4550 2500 3800 2500
Wire Wire Line
	3800 2600 4550 2600
Wire Wire Line
	3800 2400 4550 2400
Wire Wire Line
	4550 2300 3800 2300
Text GLabel 3800 2400 0    39   Input ~ 0
TSCL
Text GLabel 3800 2300 0    39   Input ~ 0
TSDA
Text GLabel 3800 2700 0    39   Input ~ 0
BUSY
Text GLabel 3800 2800 0    39   Output ~ 0
RES#
Text GLabel 3800 2900 0    39   Output ~ 0
DC#
Text GLabel 3800 3000 0    39   Output ~ 0
CS#
Wire Wire Line
	3800 2700 4550 2700
Wire Wire Line
	4550 2800 3800 2800
Wire Wire Line
	3800 2900 4550 2900
Wire Wire Line
	4550 3000 3800 3000
NoConn ~ 10150 2550
$EndSCHEMATC
