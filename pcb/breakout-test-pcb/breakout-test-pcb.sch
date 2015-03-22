EESchema Schematic File Version 2
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
LIBS:LED_ARGB
LIBS:TCS3472
LIBS:breakout-test-pcb-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "22 mar 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED_ARGB LED1
U 1 1 550EBDBF
P 2250 1300
F 0 "LED1" H 2250 1200 50  0000 C CNN
F 1 "LED_ARGB" H 2250 1400 50  0000 C CNN
F 2 "MODULE" H 2250 1300 50  0001 C CNN
F 3 "DOCUMENTATION" H 2250 1300 50  0001 C CNN
	1    2250 1300
	1    0    0    -1  
$EndComp
$Comp
L TCS3472 IC1
U 1 1 550EC0EF
P 2250 2250
F 0 "IC1" H 2250 2150 50  0000 C CNN
F 1 "TCS3472" H 2250 2350 50  0000 C CNN
F 2 "MODULE" H 2250 2250 50  0001 C CNN
F 3 "DOCUMENTATION" H 2250 2250 50  0001 C CNN
	1    2250 2250
	1    0    0    -1  
$EndComp
$Comp
L CONN_10 P1
U 1 1 550EED33
P 4300 1850
F 0 "P1" V 4250 1850 60  0000 C CNN
F 1 "CONN_10" V 4350 1850 60  0000 C CNN
F 2 "" H 4300 1850 60  0000 C CNN
F 3 "" H 4300 1850 60  0000 C CNN
	1    4300 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1250 1500 850 
Wire Wire Line
	1500 850  3800 850 
Wire Wire Line
	3800 850  3800 1400
Wire Wire Line
	3800 1400 3950 1400
Wire Wire Line
	3000 1250 3000 1050
Wire Wire Line
	3000 1050 3700 1050
Wire Wire Line
	3700 1050 3700 1500
Wire Wire Line
	3700 1500 3950 1500
Wire Wire Line
	1500 1350 1500 1650
Wire Wire Line
	1500 1650 3700 1650
Wire Wire Line
	3700 1650 3700 1600
Wire Wire Line
	3700 1600 3950 1600
Wire Wire Line
	3000 1350 3600 1350
Wire Wire Line
	3600 1350 3600 1700
Wire Wire Line
	3600 1700 3950 1700
Wire Wire Line
	1500 2150 1500 1800
Wire Wire Line
	1500 1800 3950 1800
Wire Wire Line
	3000 2150 3000 1900
Wire Wire Line
	3000 1900 3950 1900
Wire Wire Line
	1500 2250 1200 2250
Wire Wire Line
	1200 2250 1200 2750
Wire Wire Line
	1200 2750 3500 2750
Wire Wire Line
	3500 2750 3500 2000
Wire Wire Line
	3500 2000 3950 2000
Wire Wire Line
	3000 2250 3600 2250
Wire Wire Line
	3600 2250 3600 2100
Wire Wire Line
	3600 2100 3950 2100
Wire Wire Line
	1500 2350 1500 2650
Wire Wire Line
	1500 2650 3700 2650
Wire Wire Line
	3700 2650 3700 2200
Wire Wire Line
	3700 2200 3950 2200
Wire Wire Line
	3000 2350 3900 2350
Wire Wire Line
	3900 2350 3900 2300
Wire Wire Line
	3900 2300 3950 2300
$EndSCHEMATC
