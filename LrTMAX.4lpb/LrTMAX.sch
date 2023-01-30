EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "LrE-6"
Date "2019-01-24"
Rev ""
Comp "Ruffles Inc,."
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LrE-6-rescue:STM32F072C8Tx-MCU_ST_STM32F0 U1
U 1 1 5C490C50
P 8500 3950
F 0 "U1" H 8450 4250 50  0000 C CNN
F 1 "STM32F072C8Tx" H 8550 4400 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 7900 2550 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00090510.pdf" H 8500 3950 50  0001 C CNN
	1    8500 3950
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0101
U 1 1 5C490E15
P 8300 5600
F 0 "#PWR0101" H 8300 5350 50  0001 C CNN
F 1 "GND" H 8305 5427 50  0000 C CNN
F 2 "" H 8300 5600 50  0001 C CNN
F 3 "" H 8300 5600 50  0001 C CNN
	1    8300 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 5450 8300 5550
Wire Wire Line
	8300 5550 8400 5550
Wire Wire Line
	8600 5550 8600 5450
Connection ~ 8300 5550
Wire Wire Line
	8300 5550 8300 5600
Wire Wire Line
	8400 5450 8400 5550
Connection ~ 8400 5550
Wire Wire Line
	8400 5550 8500 5550
Wire Wire Line
	8500 5450 8500 5550
Connection ~ 8500 5550
Wire Wire Line
	8500 5550 8600 5550
$Comp
L LrE-6-rescue:C-Device C40
U 1 1 5C490EFE
P 8000 1950
F 0 "C40" H 7700 2000 50  0000 L CNN
F 1 "100n" H 7700 1900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8038 1800 50  0001 C CNN
F 3 "~" H 8000 1950 50  0001 C CNN
	1    8000 1950
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C43
U 1 1 5C490F9B
P 9000 1600
F 0 "C43" V 8950 1400 50  0000 C CNN
F 1 "100n" V 8950 1750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9038 1450 50  0001 C CNN
F 3 "~" H 9000 1600 50  0001 C CNN
	1    9000 1600
	0    1    1    0   
$EndComp
$Comp
L LrE-6-rescue:C-Device C44
U 1 1 5C4911FC
P 9000 1900
F 0 "C44" V 8950 1700 50  0000 C CNN
F 1 "100n" V 8950 2050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9038 1750 50  0001 C CNN
F 3 "~" H 9000 1900 50  0001 C CNN
	1    9000 1900
	0    1    1    0   
$EndComp
$Comp
L LrE-6-rescue:C-Device C45
U 1 1 5C49129B
P 9000 2200
F 0 "C45" V 8950 2000 50  0000 C CNN
F 1 "100n" V 8950 2350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9038 2050 50  0001 C CNN
F 3 "~" H 9000 2200 50  0001 C CNN
	1    9000 2200
	0    1    1    0   
$EndComp
$Comp
L LrE-6-rescue:C-Device C42
U 1 1 5C49133B
P 9000 1400
F 0 "C42" V 8950 1200 50  0000 C CNN
F 1 "4.7u" V 8950 1550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9038 1250 50  0001 C CNN
F 3 "~" H 9000 1400 50  0001 C CNN
	1    9000 1400
	0    1    1    0   
$EndComp
$Comp
L LrE-6-rescue:C-Device C41
U 1 1 5C4913C6
P 9000 1200
F 0 "C41" V 8950 1000 50  0000 C CNN
F 1 "100n" V 8950 1350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9038 1050 50  0001 C CNN
F 3 "~" H 9000 1200 50  0001 C CNN
	1    9000 1200
	0    1    1    0   
$EndComp
$Comp
L LrE-6-rescue:+3V3-power #PWR0102
U 1 1 5C49143B
P 8300 950
F 0 "#PWR0102" H 8300 800 50  0001 C CNN
F 1 "+3V3" H 8315 1123 50  0000 C CNN
F 2 "" H 8300 950 50  0001 C CNN
F 3 "" H 8300 950 50  0001 C CNN
	1    8300 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 2450 8700 2400
Wire Wire Line
	8700 1050 8600 1050
Wire Wire Line
	8300 1050 8300 950 
Wire Wire Line
	8300 2450 8300 1700
Connection ~ 8300 1050
Wire Wire Line
	8400 2450 8400 1400
Connection ~ 8400 1050
Wire Wire Line
	8400 1050 8300 1050
Connection ~ 8500 1050
Wire Wire Line
	8500 1050 8400 1050
Connection ~ 8600 1050
Wire Wire Line
	8600 1050 8500 1050
$Comp
L LrE-6-rescue:GND-power #PWR0103
U 1 1 5C49307F
P 8000 2150
F 0 "#PWR0103" H 8000 1900 50  0001 C CNN
F 1 "GND" H 8005 1977 50  0000 C CNN
F 2 "" H 8000 2150 50  0001 C CNN
F 3 "" H 8000 2150 50  0001 C CNN
	1    8000 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 1200 8400 1200
Connection ~ 8400 1200
Wire Wire Line
	8400 1200 8400 1050
Wire Wire Line
	8850 1400 8400 1400
Connection ~ 8400 1400
Wire Wire Line
	8400 1400 8400 1200
Wire Wire Line
	8850 1600 8500 1600
Connection ~ 8500 1600
Wire Wire Line
	8500 1600 8500 1050
Wire Wire Line
	8000 1800 8000 1700
Wire Wire Line
	8000 1700 8300 1700
Connection ~ 8300 1700
Wire Wire Line
	8300 1700 8300 1050
Wire Wire Line
	8000 2150 8000 2100
Wire Wire Line
	8850 1900 8600 1900
Wire Wire Line
	8850 2200 8700 2200
Connection ~ 8700 2200
Wire Wire Line
	8700 2200 8700 1050
$Comp
L LrE-6-rescue:C-Device C46
U 1 1 5C494805
P 9000 2400
F 0 "C46" V 8950 2200 50  0000 C CNN
F 1 "4.7u" V 8950 2550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9038 2250 50  0001 C CNN
F 3 "~" H 9000 2400 50  0001 C CNN
	1    9000 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	8700 2400 8850 2400
Connection ~ 8700 2400
Wire Wire Line
	8700 2400 8700 2200
$Comp
L LrE-6-rescue:GND-power #PWR0104
U 1 1 5C494D8B
P 9300 2500
F 0 "#PWR0104" H 9300 2250 50  0001 C CNN
F 1 "GND" H 9305 2327 50  0000 C CNN
F 2 "" H 9300 2500 50  0001 C CNN
F 3 "" H 9300 2500 50  0001 C CNN
	1    9300 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2500 9300 2400
Wire Wire Line
	9300 1200 9150 1200
Wire Wire Line
	9150 1400 9300 1400
Connection ~ 9300 1400
Wire Wire Line
	9300 1400 9300 1200
Wire Wire Line
	9150 1600 9300 1600
Connection ~ 9300 1600
Wire Wire Line
	9300 1600 9300 1400
Wire Wire Line
	9150 1900 9300 1900
Wire Wire Line
	9150 2200 9300 2200
Connection ~ 9300 2200
Wire Wire Line
	9150 2400 9300 2400
Connection ~ 9300 2400
Wire Wire Line
	9300 2400 9300 2200
$Comp
L LrE-6-rescue:MountingHole-Mechanical H1
U 1 1 5C4990AB
P 12100 9750
F 0 "H1" H 12200 9796 50  0000 L CNN
F 1 "MountingHole" H 12200 9705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 12100 9750 50  0001 C CNN
F 3 "~" H 12100 9750 50  0001 C CNN
	1    12100 9750
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:MountingHole-Mechanical H2
U 1 1 5C4990F9
P 12950 9750
F 0 "H2" H 13050 9796 50  0000 L CNN
F 1 "MountingHole" H 13050 9705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 12950 9750 50  0001 C CNN
F 3 "~" H 12950 9750 50  0001 C CNN
	1    12950 9750
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:MountingHole-Mechanical H3
U 1 1 5C49919E
P 13750 9750
F 0 "H3" H 13850 9796 50  0000 L CNN
F 1 "MountingHole" H 13850 9705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 13750 9750 50  0001 C CNN
F 3 "~" H 13750 9750 50  0001 C CNN
	1    13750 9750
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:MountingHole-Mechanical H4
U 1 1 5C499229
P 14600 9750
F 0 "H4" H 14700 9796 50  0000 L CNN
F 1 "MountingHole" H 14700 9705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 14600 9750 50  0001 C CNN
F 3 "~" H 14600 9750 50  0001 C CNN
	1    14600 9750
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:Conn_01x06-Connector_Generic J2
U 1 1 5C49BFE9
P 13850 3650
F 0 "J2" H 13750 4200 50  0000 L CNN
F 1 "SM06B-SRSS-TB" H 13750 4100 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM06B-SRSS-TB_1x06-1MP_P1.00mm_Horizontal" H 13850 3650 50  0001 C CNN
F 3 "~" H 13850 3650 50  0001 C CNN
	1    13850 3650
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:LDK130-08_SOT23_SOT353-Regulator_Linear U4
U 1 1 5C49CE6A
P 14450 1000
F 0 "U4" H 14450 1342 50  0000 C CNN
F 1 "SPX3819M5-L3-3TR" H 14450 1251 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 14450 1325 50  0001 C CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/29/10/f7/87/2f/66/47/f4/DM00076097.pdf/files/DM00076097.pdf/jcr:content/translations/en.DM00076097.pdf" H 14450 1000 50  0001 C CNN
	1    14450 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1600 9300 1900
$Comp
L LrE-6-rescue:GND-power #PWR0105
U 1 1 5C4A0726
P 15050 1500
F 0 "#PWR0105" H 15050 1250 50  0001 C CNN
F 1 "GND" H 15055 1327 50  0000 C CNN
F 2 "" H 15050 1500 50  0001 C CNN
F 3 "" H 15050 1500 50  0001 C CNN
	1    15050 1500
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0106
U 1 1 5C4A25A6
P 14450 1500
F 0 "#PWR0106" H 14450 1250 50  0001 C CNN
F 1 "GND" H 14455 1327 50  0000 C CNN
F 2 "" H 14450 1500 50  0001 C CNN
F 3 "" H 14450 1500 50  0001 C CNN
	1    14450 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	14450 1500 14450 1300
$Comp
L LrE-6-rescue:C-Device C56
U 1 1 5C4A31C8
P 15650 1150
F 0 "C56" H 15765 1196 50  0000 L CNN
F 1 "1u" H 15765 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 15688 1000 50  0001 C CNN
F 3 "~" H 15650 1150 50  0001 C CNN
	1    15650 1150
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0108
U 1 1 5C4A32F6
P 15650 1500
F 0 "#PWR0108" H 15650 1250 50  0001 C CNN
F 1 "GND" H 15655 1327 50  0000 C CNN
F 2 "" H 15650 1500 50  0001 C CNN
F 3 "" H 15650 1500 50  0001 C CNN
	1    15650 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	15650 1000 15650 900 
Wire Wire Line
	15650 1500 15650 1300
Wire Wire Line
	14750 900  15650 900 
Connection ~ 15650 900 
Wire Wire Line
	14150 1000 13950 1000
Wire Wire Line
	13950 1000 13950 900 
Connection ~ 13950 900 
Wire Wire Line
	13950 900  14150 900 
Text Label 13400 900  0    50   ~ 0
VBUS
$Comp
L LrE-6-rescue:C-Device C54
U 1 1 5C4A6079
P 13950 1300
F 0 "C54" H 14065 1346 50  0000 L CNN
F 1 "1u" H 14065 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 13988 1150 50  0001 C CNN
F 3 "~" H 13950 1300 50  0001 C CNN
	1    13950 1300
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0109
U 1 1 5C4A60F8
P 13950 1500
F 0 "#PWR0109" H 13950 1250 50  0001 C CNN
F 1 "GND" H 13955 1327 50  0000 C CNN
F 2 "" H 13950 1500 50  0001 C CNN
F 3 "" H 13950 1500 50  0001 C CNN
	1    13950 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	13950 1500 13950 1450
Wire Wire Line
	13950 1150 13950 1000
Connection ~ 13950 1000
$Comp
L LrE-6-rescue:GND-power #PWR0110
U 1 1 5C4A8121
P 11700 2550
F 0 "#PWR0110" H 11700 2300 50  0001 C CNN
F 1 "GND" H 11705 2377 50  0000 C CNN
F 2 "" H 11700 2550 50  0001 C CNN
F 3 "" H 11700 2550 50  0001 C CNN
	1    11700 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	11700 2550 11700 2500
Text Label 12500 1600 0    50   ~ 0
USB_DP
Text Label 12500 1400 0    50   ~ 0
USB_DM
Wire Wire Line
	13650 3650 13550 3650
Wire Wire Line
	13650 3550 13100 3550
Wire Wire Line
	13100 3550 13100 2950
$Comp
L LrE-6-rescue:C-Device C49
U 1 1 5C4BD331
P 7800 8750
F 0 "C49" H 7850 8850 50  0000 L CNN
F 1 "1u" H 7900 8650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7838 8600 50  0001 C CNN
F 3 "~" H 7800 8750 50  0001 C CNN
	1    7800 8750
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:C-Device C50
U 1 1 5C4D2D25
P 7800 9200
F 0 "C50" H 7850 9300 50  0000 L CNN
F 1 "1u" H 7850 9100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7838 9050 50  0001 C CNN
F 3 "~" H 7800 9200 50  0001 C CNN
	1    7800 9200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8500 1600 8500 2450
Connection ~ 8600 1900
Wire Wire Line
	8600 1900 8600 1050
Connection ~ 9300 1900
Wire Wire Line
	8600 1900 8600 2450
Wire Wire Line
	9300 1900 9300 2200
$Comp
L LrE-6-rescue:+3V3-power #PWR0119
U 1 1 5C4EAC46
P 7600 6000
F 0 "#PWR0119" H 7600 5850 50  0001 C CNN
F 1 "+3V3" H 7615 6173 50  0000 C CNN
F 2 "" H 7600 6000 50  0001 C CNN
F 3 "" H 7600 6000 50  0001 C CNN
	1    7600 6000
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R40
U 1 1 5C4EACBD
P 7600 7100
F 0 "R40" V 7500 6900 50  0000 L CNN
F 1 "10K" V 7500 7100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7530 7100 50  0001 C CNN
F 3 "~" H 7600 7100 50  0001 C CNN
	1    7600 7100
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R41
U 1 1 5C4EAD6C
P 7850 7100
F 0 "R41" V 7750 6900 50  0000 L CNN
F 1 "10K" V 7750 7100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7780 7100 50  0001 C CNN
F 3 "~" H 7850 7100 50  0001 C CNN
	1    7850 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 6950 7850 6050
Text Label 6900 7800 0    50   ~ 0
SDA
Text Label 6900 7950 0    50   ~ 0
SCL
$Comp
L LrE-6-rescue:R-Device R45
U 1 1 5C509B04
P 9600 9250
F 0 "R45" V 9700 9350 50  0000 C CNN
F 1 "62" V 9700 9150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9530 9250 50  0001 C CNN
F 3 "~" H 9600 9250 50  0001 C CNN
	1    9600 9250
	1    0    0    -1  
$EndComp
Text Label 9200 3750 0    50   ~ 0
M0
Text Label 9200 3850 0    50   ~ 0
M1
Text Label 9200 3950 0    50   ~ 0
M2
Text Label 9200 4050 0    50   ~ 0
M3
Text Label 7300 4550 0    50   ~ 0
ENC1A
Text Label 7300 4650 0    50   ~ 0
ENC1B
Wire Wire Line
	9100 4150 9600 4150
Wire Wire Line
	9100 4250 9600 4250
Wire Wire Line
	9100 4050 9600 4050
Wire Wire Line
	9100 3950 9600 3950
Wire Wire Line
	9100 3850 9600 3850
Wire Wire Line
	9100 3750 9600 3750
Wire Wire Line
	7300 4050 7800 4050
Wire Wire Line
	7300 4150 7800 4150
Wire Wire Line
	7300 4250 7800 4250
Wire Wire Line
	7300 4350 7800 4350
Text Label 9200 4650 0    50   ~ 0
L0
Text Label 7300 4150 0    50   ~ 0
L1
Text Label 7300 4250 0    50   ~ 0
L2
Text Label 7300 5050 0    50   ~ 0
SCL
Wire Wire Line
	7800 2650 7300 2650
Text Label 7300 2650 0    50   ~ 0
NRST
Wire Wire Line
	7800 3050 7300 3050
Wire Wire Line
	7800 3150 7300 3150
Text Label 7300 4950 0    50   ~ 0
ENC5A
Text Label 7300 3350 0    50   ~ 0
ENC5B
Wire Wire Line
	7300 3450 7800 3450
Wire Wire Line
	7300 3550 7800 3550
Text Label 7300 3050 0    50   ~ 0
ENC4A
Text Label 7300 3150 0    50   ~ 0
ENC4B
Wire Wire Line
	9100 4850 9600 4850
Wire Wire Line
	9100 4950 9600 4950
Text Label 9200 4850 0    50   ~ 0
USB_DM
Text Label 9200 4950 0    50   ~ 0
USB_DP
Wire Wire Line
	9100 5050 9600 5050
Wire Wire Line
	9100 5150 9600 5150
Text Label 9200 5150 0    50   ~ 0
SWCLK
Text Label 9200 5050 0    50   ~ 0
SWDIO
Wire Wire Line
	7800 4450 7300 4450
Text Label 7300 5150 0    50   ~ 0
SDA
Wire Wire Line
	7800 3950 7300 3950
Text Label 9200 4750 0    50   ~ 0
L3
Wire Wire Line
	7800 4550 7300 4550
Wire Wire Line
	7800 4650 7300 4650
Wire Wire Line
	7800 4750 7300 4750
Wire Wire Line
	7800 4850 7300 4850
Text Label 7300 3450 0    50   ~ 0
ENC3A
Text Label 7300 3550 0    50   ~ 0
ENC3B
Text Label 7300 4750 0    50   ~ 0
ENC2A
Text Label 7300 4850 0    50   ~ 0
ENC2B
Wire Wire Line
	7800 4950 7300 4950
Wire Wire Line
	7800 5050 7300 5050
Text Label 9200 4150 0    50   ~ 0
ENC0A
Text Label 9200 4250 0    50   ~ 0
ENC0B
$Comp
L LrE-6-rescue:Rotary_Encoder_Switch-Device SW14
U 1 1 5C6AB5C2
P 5350 1450
F 0 "SW14" H 5350 1817 50  0000 C CNN
F 1 "EC11_SMD" H 5350 1726 50  0000 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC11E-Switch_Vertical_H20mm" H 5200 1610 50  0001 C CNN
F 3 "~" H 5350 1710 50  0001 C CNN
	1    5350 1450
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:Rotary_Encoder_Switch-Device SW15
U 1 1 5C6AB6D3
P 5500 3150
F 0 "SW15" H 5500 3517 50  0000 C CNN
F 1 "EC11_SMD" H 5500 3426 50  0000 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC11E-Switch_Vertical_H20mm" H 5350 3310 50  0001 C CNN
F 3 "~" H 5500 3410 50  0001 C CNN
	1    5500 3150
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:Rotary_Encoder_Switch-Device SW10
U 1 1 5C6AB791
P 2600 1450
F 0 "SW10" H 2600 1817 50  0000 C CNN
F 1 "EC11_SMD" H 2600 1726 50  0000 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC11E-Switch_Vertical_H20mm" H 2450 1610 50  0001 C CNN
F 3 "~" H 2600 1710 50  0001 C CNN
	1    2600 1450
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R19
U 1 1 5C6AC0FC
P 4550 1150
F 0 "R19" H 4620 1196 50  0000 L CNN
F 1 "10K" H 4620 1105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4480 1150 50  0001 C CNN
F 3 "~" H 4550 1150 50  0001 C CNN
	1    4550 1150
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R18
U 1 1 5C6AC218
P 4250 1150
F 0 "R18" H 4320 1196 50  0000 L CNN
F 1 "10K" H 4320 1105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4180 1150 50  0001 C CNN
F 3 "~" H 4250 1150 50  0001 C CNN
	1    4250 1150
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R21
U 1 1 5C6AC31F
P 4650 2850
F 0 "R21" H 4720 2896 50  0000 L CNN
F 1 "10K" H 4720 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4580 2850 50  0001 C CNN
F 3 "~" H 4650 2850 50  0001 C CNN
	1    4650 2850
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R20
U 1 1 5C6AC425
P 4350 2850
F 0 "R20" H 4420 2896 50  0000 L CNN
F 1 "10K" H 4420 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4280 2850 50  0001 C CNN
F 3 "~" H 4350 2850 50  0001 C CNN
	1    4350 2850
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R11
U 1 1 5C6AC516
P 1700 1100
F 0 "R11" H 1770 1146 50  0000 L CNN
F 1 "10K" H 1770 1055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1630 1100 50  0001 C CNN
F 3 "~" H 1700 1100 50  0001 C CNN
	1    1700 1100
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R10
U 1 1 5C6AC614
P 1400 1100
F 0 "R10" H 1470 1146 50  0000 L CNN
F 1 "10K" H 1470 1055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1330 1100 50  0001 C CNN
F 3 "~" H 1400 1100 50  0001 C CNN
	1    1400 1100
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:+3V3-power #PWR0126
U 1 1 5C724379
P 1400 850
F 0 "#PWR0126" H 1400 700 50  0001 C CNN
F 1 "+3V3" H 1415 1023 50  0000 C CNN
F 2 "" H 1400 850 50  0001 C CNN
F 3 "" H 1400 850 50  0001 C CNN
	1    1400 850 
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:+3V3-power #PWR0127
U 1 1 5C724780
P 4350 2600
F 0 "#PWR0127" H 4350 2450 50  0001 C CNN
F 1 "+3V3" H 4365 2773 50  0000 C CNN
F 2 "" H 4350 2600 50  0001 C CNN
F 3 "" H 4350 2600 50  0001 C CNN
	1    4350 2600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:+3V3-power #PWR0128
U 1 1 5C724CCA
P 4250 900
F 0 "#PWR0128" H 4250 750 50  0001 C CNN
F 1 "+3V3" H 4265 1073 50  0000 C CNN
F 2 "" H 4250 900 50  0001 C CNN
F 3 "" H 4250 900 50  0001 C CNN
	1    4250 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 900  4250 950 
Wire Wire Line
	4550 1000 4550 950 
Wire Wire Line
	4550 950  4250 950 
Connection ~ 4250 950 
Wire Wire Line
	4250 950  4250 1000
Wire Wire Line
	4350 2600 4350 2650
Wire Wire Line
	4650 2700 4650 2650
Wire Wire Line
	4650 2650 4350 2650
Connection ~ 4350 2650
Wire Wire Line
	4350 2650 4350 2700
Wire Wire Line
	1400 850  1400 900 
Wire Wire Line
	1700 950  1700 900 
Wire Wire Line
	1700 900  1400 900 
Connection ~ 1400 900 
Wire Wire Line
	1400 900  1400 950 
Wire Wire Line
	2300 1550 1900 1550
Wire Wire Line
	1400 1250 1400 1350
Wire Wire Line
	1700 1250 1700 1550
Wire Wire Line
	5200 3050 4450 3050
Wire Wire Line
	5200 3250 4800 3250
Wire Wire Line
	4350 3000 4350 3050
Connection ~ 4350 3050
Wire Wire Line
	4350 3050 3700 3050
Wire Wire Line
	4650 3000 4650 3250
Connection ~ 4650 3250
Wire Wire Line
	4650 3250 3700 3250
Wire Wire Line
	5050 1350 4350 1350
Wire Wire Line
	5050 1550 4700 1550
Wire Wire Line
	4250 1300 4250 1350
Wire Wire Line
	4550 1300 4550 1550
$Comp
L LrE-6-rescue:C-Device C18
U 1 1 5C92A85A
P 4350 1800
F 0 "C18" H 4465 1846 50  0000 L CNN
F 1 "22n" H 4400 1700 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4388 1650 50  0001 C CNN
F 3 "~" H 4350 1800 50  0001 C CNN
	1    4350 1800
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C19
U 1 1 5C92A94C
P 4700 1800
F 0 "C19" H 4815 1846 50  0000 L CNN
F 1 "22n" H 4750 1700 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4738 1650 50  0001 C CNN
F 3 "~" H 4700 1800 50  0001 C CNN
	1    4700 1800
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C20
U 1 1 5C92AA33
P 4450 3500
F 0 "C20" H 4565 3546 50  0000 L CNN
F 1 "22n" H 4500 3400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4488 3350 50  0001 C CNN
F 3 "~" H 4450 3500 50  0001 C CNN
	1    4450 3500
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C21
U 1 1 5C92ABB3
P 4800 3500
F 0 "C21" H 4915 3546 50  0000 L CNN
F 1 "22n" H 4850 3400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4838 3350 50  0001 C CNN
F 3 "~" H 4800 3500 50  0001 C CNN
	1    4800 3500
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C10
U 1 1 5C92ACD6
P 1550 1750
F 0 "C10" H 1665 1796 50  0000 L CNN
F 1 "22n" H 1600 1650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1588 1600 50  0001 C CNN
F 3 "~" H 1550 1750 50  0001 C CNN
	1    1550 1750
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C11
U 1 1 5C92ADE4
P 1900 1750
F 0 "C11" H 2015 1796 50  0000 L CNN
F 1 "22n" H 2000 1650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1938 1600 50  0001 C CNN
F 3 "~" H 1900 1750 50  0001 C CNN
	1    1900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3350 4450 3050
Connection ~ 4450 3050
Wire Wire Line
	4450 3050 4350 3050
Wire Wire Line
	4800 3350 4800 3250
Connection ~ 4800 3250
Wire Wire Line
	4800 3250 4650 3250
Wire Wire Line
	1550 1600 1550 1350
Connection ~ 1550 1350
Wire Wire Line
	1550 1350 1400 1350
$Comp
L LrE-6-rescue:GND-power #PWR0129
U 1 1 5C9CBA79
P 1550 2050
F 0 "#PWR0129" H 1550 1800 50  0001 C CNN
F 1 "GND" H 1555 1877 50  0000 C CNN
F 2 "" H 1550 2050 50  0001 C CNN
F 3 "" H 1550 2050 50  0001 C CNN
	1    1550 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1650 4350 1350
Connection ~ 4350 1350
Wire Wire Line
	4350 1350 4250 1350
Wire Wire Line
	4700 1650 4700 1550
Connection ~ 4700 1550
Wire Wire Line
	4700 1550 4550 1550
Wire Wire Line
	1550 2050 1550 2000
$Comp
L LrE-6-rescue:GND-power #PWR0133
U 1 1 5CB92FE6
P 4350 2050
F 0 "#PWR0133" H 4350 1800 50  0001 C CNN
F 1 "GND" H 4355 1877 50  0000 C CNN
F 2 "" H 4350 2050 50  0001 C CNN
F 3 "" H 4350 2050 50  0001 C CNN
	1    4350 2050
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0134
U 1 1 5CB930D1
P 4450 3750
F 0 "#PWR0134" H 4450 3500 50  0001 C CNN
F 1 "GND" H 4455 3577 50  0000 C CNN
F 2 "" H 4450 3750 50  0001 C CNN
F 3 "" H 4450 3750 50  0001 C CNN
	1    4450 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2050 4350 2000
Wire Wire Line
	4350 2000 4700 2000
Wire Wire Line
	5000 2000 5000 1450
Wire Wire Line
	5000 1450 5050 1450
Connection ~ 4350 2000
Wire Wire Line
	4350 2000 4350 1950
Wire Wire Line
	4700 1950 4700 2000
Connection ~ 4700 2000
Wire Wire Line
	4700 2000 5000 2000
Wire Wire Line
	4450 3650 4450 3700
Wire Wire Line
	4450 3700 4800 3700
Wire Wire Line
	5150 3700 5150 3150
Wire Wire Line
	5150 3150 5200 3150
Connection ~ 4450 3700
Wire Wire Line
	4450 3700 4450 3750
Wire Wire Line
	4800 3650 4800 3700
Connection ~ 4800 3700
Wire Wire Line
	4800 3700 5150 3700
Wire Wire Line
	2300 1450 2250 1450
Wire Wire Line
	2250 1450 2250 2000
Wire Wire Line
	2250 2000 1900 2000
Connection ~ 1550 2000
Wire Wire Line
	1550 2000 1550 1900
Wire Wire Line
	1900 1900 1900 2000
Connection ~ 1900 2000
Wire Wire Line
	1900 2000 1550 2000
Text Label 3700 3050 0    50   ~ 0
ENC5A
Text Label 3700 3250 0    50   ~ 0
ENC5B
Text Label 950  1350 0    50   ~ 0
ENC0A
Text Label 950  1550 0    50   ~ 0
ENC0B
$Comp
L LrE-6-rescue:SW_Push_45deg-Switch SW1
U 1 1 5CCE212B
P 12700 5000
F 0 "SW1" H 12700 5278 50  0000 C CNN
F 1 "Tact_SW_8mm" H 12850 5200 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 12700 5000 50  0001 C CNN
F 3 "" H 12700 5000 50  0001 C CNN
	1    12700 5000
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:SW_Push_45deg-Switch SW2
U 1 1 5CCE2246
P 12700 6050
F 0 "SW2" H 12700 6328 50  0000 C CNN
F 1 "Tact_SW_8mm" H 12850 6250 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 12700 6050 50  0001 C CNN
F 3 "" H 12700 6050 50  0001 C CNN
	1    12700 6050
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:SW_Push_45deg-Switch SW3
U 1 1 5CCE2412
P 12700 7050
F 0 "SW3" H 12700 7328 50  0000 C CNN
F 1 "Tact_SW_8mm" H 12850 7250 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 12700 7050 50  0001 C CNN
F 3 "" H 12700 7050 50  0001 C CNN
	1    12700 7050
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:SW_Push_45deg-Switch SW4
U 1 1 5CCE2530
P 12800 8300
F 0 "SW4" H 12800 8578 50  0000 C CNN
F 1 "Tact_SW_8mm" H 12900 8500 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 12800 8300 50  0001 C CNN
F 3 "" H 12800 8300 50  0001 C CNN
	1    12800 8300
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:SW_Push_45deg-Switch SW5
U 1 1 5CCE27CC
P 13850 5000
F 0 "SW5" H 13850 5278 50  0000 C CNN
F 1 "Tact_SW_8mm" H 13850 5187 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 13850 5000 50  0001 C CNN
F 3 "" H 13850 5000 50  0001 C CNN
	1    13850 5000
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:SW_Push_45deg-Switch SW6
U 1 1 5CCE28E5
P 13850 6050
F 0 "SW6" H 13850 6328 50  0000 C CNN
F 1 "Tact_SW_8mm" H 13850 6237 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 13850 6050 50  0001 C CNN
F 3 "" H 13850 6050 50  0001 C CNN
	1    13850 6050
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:SW_Push_45deg-Switch SW7
U 1 1 5CCE2A37
P 13950 7100
F 0 "SW7" H 13950 7378 50  0000 C CNN
F 1 "Tact_SW_8mm" H 13950 7287 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 13950 7100 50  0001 C CNN
F 3 "" H 13950 7100 50  0001 C CNN
	1    13950 7100
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:SW_Push_45deg-Switch SW8
U 1 1 5CCE2B60
P 13950 8250
F 0 "SW8" H 13950 8528 50  0000 C CNN
F 1 "Tact_SW_8mm" H 13950 8437 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H9.5mm" H 13950 8250 50  0001 C CNN
F 3 "" H 13950 8250 50  0001 C CNN
	1    13950 8250
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D4
U 1 1 5C4E1850
P 12900 8550
F 0 "D4" V 12946 8470 50  0000 R CNN
F 1 "1N4148W" V 12855 8470 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 12900 8375 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 12900 8550 50  0001 C CNN
	1    12900 8550
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D8
U 1 1 5C4E2E74
P 14050 8500
F 0 "D8" V 14096 8420 50  0000 R CNN
F 1 "1N4148W" V 14005 8420 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 14050 8325 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 14050 8500 50  0001 C CNN
	1    14050 8500
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:R-Device R4
U 1 1 5C4E6032
P 12250 8700
F 0 "R4" V 12043 8700 50  0000 C CNN
F 1 "1K" V 12134 8700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 12180 8700 50  0001 C CNN
F 3 "~" H 12250 8700 50  0001 C CNN
	1    12250 8700
	0    1    1    0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D3
U 1 1 5C4E8A83
P 12800 7300
F 0 "D3" V 12846 7220 50  0000 R CNN
F 1 "1N4148W" V 12755 7220 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 12800 7125 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 12800 7300 50  0001 C CNN
	1    12800 7300
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D7
U 1 1 5C4E949A
P 14050 7350
F 0 "D7" V 14096 7270 50  0000 R CNN
F 1 "1N4148W" V 14005 7270 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 14050 7175 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 14050 7350 50  0001 C CNN
	1    14050 7350
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:R-Device R3
U 1 1 5C4EAB19
P 12200 7500
F 0 "R3" V 11993 7500 50  0000 C CNN
F 1 "1K" V 12084 7500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 12130 7500 50  0001 C CNN
F 3 "~" H 12200 7500 50  0001 C CNN
	1    12200 7500
	0    1    1    0   
$EndComp
$Comp
L LrE-6-rescue:R-Device R2
U 1 1 5C4EBA08
P 12200 6450
F 0 "R2" V 12407 6450 50  0000 C CNN
F 1 "1K" V 12316 6450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 12130 6450 50  0001 C CNN
F 3 "~" H 12200 6450 50  0001 C CNN
	1    12200 6450
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D2
U 1 1 5C4EC382
P 12800 6300
F 0 "D2" V 12846 6220 50  0000 R CNN
F 1 "1N4148W" V 12755 6220 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 12800 6125 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 12800 6300 50  0001 C CNN
	1    12800 6300
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D6
U 1 1 5C4ED026
P 13950 6300
F 0 "D6" V 13996 6220 50  0000 R CNN
F 1 "1N4148W" V 13905 6220 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 13950 6125 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 13950 6300 50  0001 C CNN
	1    13950 6300
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0135
U 1 1 5C4EFC63
P 12100 8800
F 0 "#PWR0135" H 12100 8550 50  0001 C CNN
F 1 "GND" H 12105 8627 50  0000 C CNN
F 2 "" H 12100 8800 50  0001 C CNN
F 3 "" H 12100 8800 50  0001 C CNN
	1    12100 8800
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0136
U 1 1 5C4F0FEB
P 12050 7600
F 0 "#PWR0136" H 12050 7350 50  0001 C CNN
F 1 "GND" H 12055 7427 50  0000 C CNN
F 2 "" H 12050 7600 50  0001 C CNN
F 3 "" H 12050 7600 50  0001 C CNN
	1    12050 7600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0137
U 1 1 5C4F2322
P 12050 6550
F 0 "#PWR0137" H 12050 6300 50  0001 C CNN
F 1 "GND" H 12055 6377 50  0000 C CNN
F 2 "" H 12050 6550 50  0001 C CNN
F 3 "" H 12050 6550 50  0001 C CNN
	1    12050 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	12050 6550 12050 6450
Wire Wire Line
	12050 7600 12050 7500
Wire Wire Line
	12100 8800 12100 8700
Wire Wire Line
	14050 8700 14050 8650
Connection ~ 12900 8700
Wire Wire Line
	12900 8700 14050 8700
Wire Wire Line
	12350 7500 12800 7500
Wire Wire Line
	12800 7450 12800 7500
Connection ~ 12800 7500
Wire Wire Line
	12800 7500 14050 7500
Wire Wire Line
	12350 6450 12800 6450
Connection ~ 12800 6450
Wire Wire Line
	12800 6450 13950 6450
$Comp
L LrE-6-rescue:1N4148W-Diode D1
U 1 1 5C6AD044
P 12800 5250
F 0 "D1" V 12846 5170 50  0000 R CNN
F 1 "1N4148W" V 12755 5170 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 12800 5075 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 12800 5250 50  0001 C CNN
	1    12800 5250
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D5
U 1 1 5C6AE01B
P 13950 5250
F 0 "D5" V 13996 5170 50  0000 R CNN
F 1 "1N4148W" V 13905 5170 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 13950 5075 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 13950 5250 50  0001 C CNN
	1    13950 5250
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:R-Device R1
U 1 1 5C6B3D26
P 12250 5400
F 0 "R1" V 12043 5400 50  0000 C CNN
F 1 "1K" V 12134 5400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 12180 5400 50  0001 C CNN
F 3 "~" H 12250 5400 50  0001 C CNN
	1    12250 5400
	0    1    1    0   
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0138
U 1 1 5C7E5536
P 12100 5550
F 0 "#PWR0138" H 12100 5300 50  0001 C CNN
F 1 "GND" H 12105 5377 50  0000 C CNN
F 2 "" H 12100 5550 50  0001 C CNN
F 3 "" H 12100 5550 50  0001 C CNN
	1    12100 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	12100 5550 12100 5400
Wire Wire Line
	12600 6950 12500 6950
Wire Wire Line
	12500 6950 12500 5950
Wire Wire Line
	12700 8200 12500 8200
Wire Wire Line
	12500 8200 12500 6950
Connection ~ 12500 6950
Wire Wire Line
	12600 5950 12500 5950
Connection ~ 12500 5950
Wire Wire Line
	12500 5950 12500 4900
Wire Wire Line
	12600 4900 12500 4900
Connection ~ 12800 5400
Wire Wire Line
	12800 5400 13950 5400
Wire Wire Line
	12400 5400 12800 5400
Text Label 12500 4550 1    50   ~ 0
L0
Wire Wire Line
	13500 8150 13500 7000
Wire Wire Line
	13750 5950 13500 5950
Connection ~ 13500 5950
Wire Wire Line
	13500 5950 13500 4900
Wire Wire Line
	13850 7000 13500 7000
Connection ~ 13500 7000
Wire Wire Line
	13500 7000 13500 5950
Wire Wire Line
	13500 8150 13850 8150
Wire Wire Line
	13750 4900 13500 4900
Text Label 13500 4550 1    50   ~ 0
L1
$Comp
L LrE-6-rescue:1N4148W-Diode D14
U 1 1 5CACD41C
P 5650 1700
F 0 "D14" V 5696 1620 50  0000 R CNN
F 1 "1N4148W" V 5605 1620 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 5650 1525 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5650 1700 50  0001 C CNN
	1    5650 1700
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D15
U 1 1 5CACE3B1
P 5800 3400
F 0 "D15" V 5846 3320 50  0000 R CNN
F 1 "1N4148W" V 5755 3320 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 5800 3225 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5800 3400 50  0001 C CNN
	1    5800 3400
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D10
U 1 1 5CACF29F
P 2900 1700
F 0 "D10" V 2946 1620 50  0000 R CNN
F 1 "1N4148W" V 2855 1620 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 2900 1525 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2900 1700 50  0001 C CNN
	1    2900 1700
	0    -1   -1   0   
$EndComp
Text Label 14550 8700 0    50   ~ 0
M3
Text Label 14550 7500 0    50   ~ 0
M2
Text Label 14500 6450 0    50   ~ 0
M1
Text Label 14500 5400 0    50   ~ 0
M0
Wire Wire Line
	5650 1350 6150 1350
Wire Wire Line
	2900 1850 2900 2050
Wire Wire Line
	5800 3550 5800 3650
Wire Wire Line
	5650 1850 5650 2050
Wire Wire Line
	5650 2050 6200 2050
Text Label 6200 2050 0    50   ~ 0
M0
Text Label 6050 3650 0    50   ~ 0
M1
Text Label 3100 2050 0    50   ~ 0
M0
Text Label 6150 1350 0    50   ~ 0
L3
Text Label 6050 3050 0    50   ~ 0
L3
Text Label 3100 1350 0    50   ~ 0
L2
$Comp
L LrE-6-rescue:+3V3-power #PWR0139
U 1 1 5C5248C7
P 15700 2250
F 0 "#PWR0139" H 15700 2100 50  0001 C CNN
F 1 "+3V3" H 15715 2423 50  0000 C CNN
F 2 "" H 15700 2250 50  0001 C CNN
F 3 "" H 15700 2250 50  0001 C CNN
	1    15700 2250
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R48
U 1 1 5C5249AB
P 15400 2300
F 0 "R48" V 15193 2300 50  0000 C CNN
F 1 "1K" V 15284 2300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 15330 2300 50  0001 C CNN
F 3 "~" H 15400 2300 50  0001 C CNN
	1    15400 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	15550 2300 15700 2300
Wire Wire Line
	15700 2300 15700 2250
$Comp
L LrE-6-rescue:LED-Device D18
U 1 1 5C54E897
P 15000 2300
F 0 "D18" H 14991 2516 50  0000 C CNN
F 1 "LED0603_BL" H 14991 2425 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 15000 2300 50  0001 C CNN
F 3 "~" H 15000 2300 50  0001 C CNN
	1    15000 2300
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0140
U 1 1 5C54EA62
P 14700 2400
F 0 "#PWR0140" H 14700 2150 50  0001 C CNN
F 1 "GND" H 14705 2227 50  0000 C CNN
F 2 "" H 14700 2400 50  0001 C CNN
F 3 "" H 14700 2400 50  0001 C CNN
	1    14700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	14700 2400 14700 2300
Wire Wire Line
	14700 2300 14850 2300
Wire Wire Line
	15150 2300 15250 2300
$Comp
L LrE-6-rescue:GND-power #PWR0141
U 1 1 5C4E242E
P 6700 3300
F 0 "#PWR0141" H 6700 3050 50  0001 C CNN
F 1 "GND" H 6705 3127 50  0000 C CNN
F 2 "" H 6700 3300 50  0001 C CNN
F 3 "" H 6700 3300 50  0001 C CNN
	1    6700 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3000 6700 2850
Wire Wire Line
	6700 2850 7800 2850
Wire Wire Line
	12500 4900 12500 4550
Connection ~ 12500 4900
Wire Wire Line
	13500 4900 13500 4550
Connection ~ 13500 4900
Wire Wire Line
	1550 1350 2300 1350
Wire Wire Line
	1900 1600 1900 1550
Connection ~ 1900 1550
Wire Wire Line
	1900 1550 1700 1550
NoConn ~ 13650 3950
Connection ~ 11700 2500
Text Notes 13800 10450 0    197  ~ 0
LrTMAX type C
Wire Wire Line
	12400 8700 12900 8700
$Comp
L LrE-6-rescue:TestPoint-Connector TP1
U 1 1 5C9CF623
P 14700 2950
F 0 "TP1" H 14758 3068 50  0000 L CNN
F 1 "TestPoint" H 14758 2977 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.0mm_Drill0.5mm" H 14900 2950 50  0001 C CNN
F 3 "~" H 14900 2950 50  0001 C CNN
	1    14700 2950
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0144
U 1 1 5C9D2E04
P 14700 3100
F 0 "#PWR0144" H 14700 2850 50  0001 C CNN
F 1 "GND" H 14705 2927 50  0000 C CNN
F 2 "" H 14700 3100 50  0001 C CNN
F 3 "" H 14700 3100 50  0001 C CNN
	1    14700 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	14700 3100 14700 2950
$Comp
L LrE-6-rescue:GND-power #PWR0111
U 1 1 5C4AB9A8
P 13900 4200
F 0 "#PWR0111" H 13900 3950 50  0001 C CNN
F 1 "GND" H 13905 4027 50  0000 C CNN
F 2 "" H 13900 4200 50  0001 C CNN
F 3 "" H 13900 4200 50  0001 C CNN
	1    13900 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	15650 900  15650 850 
$Comp
L LrE-6-rescue:+3V3-power #PWR0107
U 1 1 5C4A315E
P 15650 850
F 0 "#PWR0107" H 15650 700 50  0001 C CNN
F 1 "+3V3" H 15665 1023 50  0000 C CNN
F 2 "" H 15650 850 50  0001 C CNN
F 3 "" H 15650 850 50  0001 C CNN
	1    15650 850 
	1    0    0    -1  
$EndComp
Text Label 12550 3450 0    50   ~ 0
NRST
Wire Wire Line
	13650 3850 13000 3850
Wire Wire Line
	13650 3750 13000 3750
Text Label 13000 3750 0    50   ~ 0
SWDIO
Text Label 13000 3850 0    50   ~ 0
SWCLK
$Comp
L LrE-6-rescue:+3V3-power #PWR0112
U 1 1 5C4ACA20
P 12250 2850
F 0 "#PWR0112" H 12250 2700 50  0001 C CNN
F 1 "+3V3" H 12265 3023 50  0000 C CNN
F 2 "" H 12250 2850 50  0001 C CNN
F 3 "" H 12250 2850 50  0001 C CNN
	1    12250 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	12250 2850 12250 2950
Wire Wire Line
	12250 2950 12250 3000
Connection ~ 12250 2950
Wire Wire Line
	13100 2950 12250 2950
Wire Wire Line
	12250 3450 12250 3300
Connection ~ 12250 3450
Wire Wire Line
	13650 3450 12250 3450
Wire Wire Line
	12250 3550 12250 3450
Wire Wire Line
	12250 3850 12250 3900
$Comp
L LrE-6-rescue:GND-power #PWR0113
U 1 1 5C4ACBA6
P 12250 3900
F 0 "#PWR0113" H 12250 3650 50  0001 C CNN
F 1 "GND" H 12255 3727 50  0000 C CNN
F 2 "" H 12250 3900 50  0001 C CNN
F 3 "" H 12250 3900 50  0001 C CNN
	1    12250 3900
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R47
U 1 1 5C4ACB2C
P 12250 3150
F 0 "R47" H 12320 3196 50  0000 L CNN
F 1 "10K" H 12320 3105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 12180 3150 50  0001 C CNN
F 3 "~" H 12250 3150 50  0001 C CNN
	1    12250 3150
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C53
U 1 1 5C4ACA82
P 12250 3700
F 0 "C53" H 12365 3746 50  0000 L CNN
F 1 "1u" H 12365 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 12288 3550 50  0001 C CNN
F 3 "~" H 12250 3700 50  0001 C CNN
	1    12250 3700
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0146
U 1 1 5E26F099
P 5300 1850
F 0 "#PWR0146" H 5300 1600 50  0001 C CNN
F 1 "GND" H 5305 1677 50  0000 C CNN
F 2 "" H 5300 1850 50  0001 C CNN
F 3 "" H 5300 1850 50  0001 C CNN
	1    5300 1850
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0147
U 1 1 5E35B268
P 5450 3550
F 0 "#PWR0147" H 5450 3300 50  0001 C CNN
F 1 "GND" H 5455 3377 50  0000 C CNN
F 2 "" H 5450 3550 50  0001 C CNN
F 3 "" H 5450 3550 50  0001 C CNN
	1    5450 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	13900 4100 13900 4150
Wire Wire Line
	13900 4150 13800 4150
Wire Wire Line
	13550 3650 13550 4150
Wire Wire Line
	13800 4100 13800 4150
Connection ~ 13800 4150
Wire Wire Line
	13800 4150 13550 4150
Wire Wire Line
	13900 4150 13900 4200
Connection ~ 13900 4150
Wire Wire Line
	5450 3450 5450 3500
Wire Wire Line
	5600 3450 5600 3500
Wire Wire Line
	5600 3500 5450 3500
Connection ~ 5450 3500
Wire Wire Line
	5450 3500 5450 3550
Wire Wire Line
	5300 1850 5300 1800
Wire Wire Line
	5300 1800 5450 1800
Wire Wire Line
	5450 1800 5450 1750
Connection ~ 5300 1800
Wire Wire Line
	5300 1800 5300 1750
$Comp
L LrE-6-rescue:GND-power #PWR0149
U 1 1 5E927946
P 2550 1850
F 0 "#PWR0149" H 2550 1600 50  0001 C CNN
F 1 "GND" H 2555 1677 50  0000 C CNN
F 2 "" H 2550 1850 50  0001 C CNN
F 3 "" H 2550 1850 50  0001 C CNN
	1    2550 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1750 2550 1800
Wire Wire Line
	2550 1800 2700 1800
Wire Wire Line
	2700 1800 2700 1750
Connection ~ 2550 1800
Wire Wire Line
	2550 1800 2550 1850
$Comp
L LrE-6:WS2812B-2020 D31
U 1 1 5CFA2C68
P 1600 10600
F 0 "D31" H 1300 10850 50  0000 L CNN
F 1 "WS2812B-2020" H 1100 10350 50  0000 L CNN
F 2 "LrE-6:LED_WS2812B-2020" H 1650 10300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/2686/SK6812MINI_REV.01-1-2.pdf" H 1700 10225 50  0001 L TNN
	1    1600 10600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6:WS2812B-2020 D32
U 1 1 5CFAA8BB
P 2700 10600
F 0 "D32" H 2400 10850 50  0000 L CNN
F 1 "WS2812B-2020" H 2200 10350 50  0000 L CNN
F 2 "LrE-6:LED_WS2812B-2020" H 2750 10300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/2686/SK6812MINI_REV.01-1-2.pdf" H 2800 10225 50  0001 L TNN
	1    2700 10600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6:WS2812B-2020 D33
U 1 1 5CFAB701
P 3850 10600
F 0 "D33" H 3550 10850 50  0000 L CNN
F 1 "WS2812B-2020" H 3350 10350 50  0000 L CNN
F 2 "LrE-6:LED_WS2812B-2020" H 3900 10300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/2686/SK6812MINI_REV.01-1-2.pdf" H 3950 10225 50  0001 L TNN
	1    3850 10600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6:WS2812B-2020 D34
U 1 1 5CFAC587
P 5000 10600
F 0 "D34" H 4650 10850 50  0000 L CNN
F 1 "WS2812B-2020" H 4500 10350 50  0000 L CNN
F 2 "LrE-6:LED_WS2812B-2020" H 5050 10300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/2686/SK6812MINI_REV.01-1-2.pdf" H 5100 10225 50  0001 L TNN
	1    5000 10600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6:WS2812B-2020 D35
U 1 1 5CFAD843
P 6150 10600
F 0 "D35" H 5850 10850 50  0000 L CNN
F 1 "WS2812B-2020" H 5650 10350 50  0000 L CNN
F 2 "LrE-6:LED_WS2812B-2020" H 6200 10300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/2686/SK6812MINI_REV.01-1-2.pdf" H 6250 10225 50  0001 L TNN
	1    6150 10600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6:WS2812B-2020 D36
U 1 1 5CFAE065
P 7300 10600
F 0 "D36" H 6950 10850 50  0000 L CNN
F 1 "WS2812B-2020" H 6800 10350 50  0000 L CNN
F 2 "LrE-6:LED_WS2812B-2020" H 7350 10300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/2686/SK6812MINI_REV.01-1-2.pdf" H 7400 10225 50  0001 L TNN
	1    7300 10600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0122
U 1 1 5CFAF29C
P 1600 11000
F 0 "#PWR0122" H 1600 10750 50  0001 C CNN
F 1 "GND" H 1605 10827 50  0000 C CNN
F 2 "" H 1600 11000 50  0001 C CNN
F 3 "" H 1600 11000 50  0001 C CNN
	1    1600 11000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 11000 1600 10950
Wire Wire Line
	1600 10950 2000 10950
Wire Wire Line
	7300 10950 7300 10900
Connection ~ 1600 10950
Wire Wire Line
	1600 10950 1600 10900
Wire Wire Line
	6150 10900 6150 10950
Connection ~ 6150 10950
Wire Wire Line
	6150 10950 6550 10950
Wire Wire Line
	5000 10900 5000 10950
Connection ~ 5000 10950
Wire Wire Line
	5000 10950 5350 10950
Wire Wire Line
	3850 10900 3850 10950
Connection ~ 3850 10950
Wire Wire Line
	2700 10900 2700 10950
Connection ~ 2700 10950
Wire Wire Line
	2700 10950 3050 10950
Wire Wire Line
	7300 10300 7300 10150
Wire Wire Line
	7300 10150 6550 10150
Wire Wire Line
	6150 10300 6150 10150
Connection ~ 6150 10150
Wire Wire Line
	6150 10150 5350 10150
Wire Wire Line
	5000 10300 5000 10150
Connection ~ 5000 10150
Wire Wire Line
	5000 10150 4200 10150
Wire Wire Line
	3850 10300 3850 10150
Connection ~ 3850 10150
Wire Wire Line
	3850 10150 3050 10150
Wire Wire Line
	2700 10300 2700 10150
Connection ~ 2700 10150
Wire Wire Line
	2700 10150 2000 10150
Wire Wire Line
	1600 10300 1600 10150
Connection ~ 1600 10150
Text Label 800  10150 0    50   ~ 0
VBUS
Wire Wire Line
	1900 10600 2400 10600
Wire Wire Line
	3000 10600 3550 10600
Wire Wire Line
	4150 10600 4700 10600
Wire Wire Line
	5300 10600 5850 10600
Wire Wire Line
	6450 10600 7000 10600
NoConn ~ 6300 10700
$Comp
L LrE-6-rescue:C-Device C31
U 1 1 5D7055E7
P 2000 10300
F 0 "C31" H 2115 10346 50  0000 L CNN
F 1 "0.1u" H 2115 10255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2038 10150 50  0001 C CNN
F 3 "~" H 2000 10300 50  0001 C CNN
	1    2000 10300
	1    0    0    -1  
$EndComp
Connection ~ 2000 10150
Wire Wire Line
	2000 10150 1600 10150
$Comp
L LrE-6-rescue:C-Device C32
U 1 1 5D706229
P 3050 10300
F 0 "C32" H 3165 10346 50  0000 L CNN
F 1 "0.1u" H 3165 10255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3088 10150 50  0001 C CNN
F 3 "~" H 3050 10300 50  0001 C CNN
	1    3050 10300
	1    0    0    -1  
$EndComp
Connection ~ 3050 10150
Wire Wire Line
	3050 10150 2700 10150
$Comp
L LrE-6-rescue:C-Device C33
U 1 1 5D706B4B
P 4200 10300
F 0 "C33" H 4315 10346 50  0000 L CNN
F 1 "0.1u" H 4315 10255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4238 10150 50  0001 C CNN
F 3 "~" H 4200 10300 50  0001 C CNN
	1    4200 10300
	1    0    0    -1  
$EndComp
Connection ~ 4200 10150
Wire Wire Line
	4200 10150 3850 10150
Connection ~ 5350 10150
Wire Wire Line
	5350 10150 5000 10150
$Comp
L LrE-6-rescue:C-Device C35
U 1 1 5D7076C0
P 6550 10300
F 0 "C35" H 6665 10346 50  0000 L CNN
F 1 "0.1u" H 6665 10255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6588 10150 50  0001 C CNN
F 3 "~" H 6550 10300 50  0001 C CNN
	1    6550 10300
	1    0    0    -1  
$EndComp
Connection ~ 6550 10150
Wire Wire Line
	6550 10150 6150 10150
$Comp
L LrE-6-rescue:C-Device C36
U 1 1 5D708E26
P 7750 10300
F 0 "C36" H 7865 10346 50  0000 L CNN
F 1 "0.1u" H 7865 10255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7788 10150 50  0001 C CNN
F 3 "~" H 7750 10300 50  0001 C CNN
	1    7750 10300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 10150 7750 10150
Connection ~ 7300 10150
Wire Wire Line
	7300 10950 7750 10950
Wire Wire Line
	7750 10950 7750 10450
Connection ~ 7300 10950
Wire Wire Line
	2000 10450 2000 10950
Connection ~ 2000 10950
Wire Wire Line
	2000 10950 2700 10950
Wire Wire Line
	3050 10450 3050 10950
Connection ~ 3050 10950
Wire Wire Line
	3050 10950 3850 10950
Wire Wire Line
	4200 10450 4200 10950
Wire Wire Line
	3850 10950 4200 10950
Connection ~ 4200 10950
Wire Wire Line
	4200 10950 5000 10950
Wire Wire Line
	5350 10450 5350 10950
Connection ~ 5350 10950
Wire Wire Line
	5350 10950 6150 10950
$Comp
L LrE-6-rescue:C-Device C34
U 1 1 5D707270
P 5350 10300
F 0 "C34" H 5465 10346 50  0000 L CNN
F 1 "0.1u" H 5465 10255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5388 10150 50  0001 C CNN
F 3 "~" H 5350 10300 50  0001 C CNN
	1    5350 10300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 10450 6550 10950
Connection ~ 6550 10950
Wire Wire Line
	6550 10950 7300 10950
Text Label 800  10600 0    50   ~ 0
LED_DOUT
Text Label 2050 10600 0    50   ~ 0
LED1OUT
Text Label 3200 10600 0    50   ~ 0
LED2OUT
Text Label 4300 10600 0    50   ~ 0
LED3OUT
Text Label 5450 10600 0    50   ~ 0
LED4OUT
Text Label 6650 10600 0    50   ~ 0
LED5OUT
Text Label 10850 4100 0    50   ~ 0
LED_DOUT
Wire Wire Line
	15050 1300 15050 1500
Wire Wire Line
	14750 1000 15050 1000
$Comp
L LrE-6-rescue:C-Device C55
U 1 1 5C4910AD
P 15050 1150
F 0 "C55" H 15250 1250 50  0000 C CNN
F 1 "100n" H 15250 1150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 15088 1000 50  0001 C CNN
F 3 "~" H 15050 1150 50  0001 C CNN
	1    15050 1150
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:2N7002-Transistor_FET Q1
U 1 1 5D0213C1
P 10200 4350
F 0 "Q1" H 10406 4396 50  0000 L CNN
F 1 "2N7002" H 10406 4305 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10400 4275 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 10200 4350 50  0001 L CNN
	1    10200 4350
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0121
U 1 1 5D0228D6
P 10300 4550
F 0 "#PWR0121" H 10300 4300 50  0001 C CNN
F 1 "GND" H 10305 4377 50  0000 C CNN
F 2 "" H 10300 4550 50  0001 C CNN
F 3 "" H 10300 4550 50  0001 C CNN
	1    10300 4550
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R46
U 1 1 5D024220
P 10300 3700
F 0 "R46" H 10370 3746 50  0000 L CNN
F 1 "1.2K" H 10370 3655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10230 3700 50  0001 C CNN
F 3 "~" H 10300 3700 50  0001 C CNN
	1    10300 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 4150 10300 4100
Wire Wire Line
	10300 3350 10300 3550
Wire Wire Line
	10300 4100 10850 4100
Connection ~ 10300 4100
Wire Wire Line
	10300 4100 10300 3850
Text Label 9200 4350 0    50   ~ 0
LED_DON
Text Label 10000 3350 0    50   ~ 0
VBUS
$Comp
L LrE-6-rescue:C-Device C30
U 1 1 5D54B231
P 10850 3550
F 0 "C30" H 11000 3600 50  0000 L CNN
F 1 "100n" H 11000 3500 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10888 3400 50  0001 C CNN
F 3 "~" H 10850 3550 50  0001 C CNN
	1    10850 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	800  10600 1300 10600
Wire Wire Line
	9100 4350 10000 4350
Wire Wire Line
	7600 7250 7600 7950
Connection ~ 7600 7950
Wire Wire Line
	7850 7250 7850 7800
Wire Wire Line
	7600 7950 8300 7950
Wire Wire Line
	7950 8750 8300 8750
Wire Wire Line
	7950 9200 8300 9200
Wire Wire Line
	7650 8750 7400 8750
Wire Wire Line
	7650 9200 7400 9200
Wire Wire Line
	8300 8250 6900 8250
Wire Wire Line
	8300 9350 7400 9350
Wire Wire Line
	7400 9200 7400 9350
Wire Wire Line
	8300 8900 7400 8900
Wire Wire Line
	7400 8750 7400 8900
Wire Wire Line
	7850 7800 8300 7800
Connection ~ 7850 7800
$Comp
L LrE-6-rescue:C-Device C52
U 1 1 5E946B99
P 10200 9500
F 0 "C52" H 10000 9350 50  0000 L CNN
F 1 "4.7u" H 9950 9600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10238 9350 50  0001 C CNN
F 3 "~" H 10200 9500 50  0001 C CNN
	1    10200 9500
	-1   0    0    1   
$EndComp
$Comp
L LrE-6-rescue:C-Device C51
U 1 1 5E947AA4
P 9900 9500
F 0 "C51" H 9700 9350 50  0000 L CNN
F 1 "4.7u" H 9700 9600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9938 9350 50  0001 C CNN
F 3 "~" H 9900 9500 50  0001 C CNN
	1    9900 9500
	-1   0    0    1   
$EndComp
Text Label 6900 8250 0    50   ~ 0
NRST
$Comp
L LrE-6-rescue:C-Device C48
U 1 1 5EE6A509
P 9300 7100
F 0 "C48" H 9050 7000 50  0000 L CNN
F 1 "1u" H 9100 7200 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9338 6950 50  0001 C CNN
F 3 "~" H 9300 7100 50  0001 C CNN
	1    9300 7100
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0114
U 1 1 5C4B6C52
P 8900 9650
F 0 "#PWR0114" H 8900 9400 50  0001 C CNN
F 1 "GND" H 8905 9477 50  0000 C CNN
F 2 "" H 8900 9650 50  0001 C CNN
F 3 "" H 8900 9650 50  0001 C CNN
	1    8900 9650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 9550 8900 9650
$Comp
L LrE-6-rescue:GND-power #PWR0115
U 1 1 5E367F16
P 8150 7100
F 0 "#PWR0115" H 8150 6850 50  0001 C CNN
F 1 "GND" H 8155 6927 50  0000 C CNN
F 2 "" H 8150 7100 50  0001 C CNN
F 3 "" H 8150 7100 50  0001 C CNN
	1    8150 7100
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0116
U 1 1 5E3C3094
P 9600 9650
F 0 "#PWR0116" H 9600 9400 50  0001 C CNN
F 1 "GND" H 9605 9477 50  0000 C CNN
F 2 "" H 9600 9650 50  0001 C CNN
F 3 "" H 9600 9650 50  0001 C CNN
	1    9600 9650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 8900 9600 8900
Wire Wire Line
	9600 9650 9600 9400
Wire Wire Line
	10200 7800 10200 9350
Wire Wire Line
	9900 8350 9900 9350
$Comp
L LrE-6-rescue:GND-power #PWR0117
U 1 1 5E4AEB5A
P 9650 7150
F 0 "#PWR0117" H 9650 6900 50  0001 C CNN
F 1 "GND" H 9655 6977 50  0000 C CNN
F 2 "" H 9650 7150 50  0001 C CNN
F 3 "" H 9650 7150 50  0001 C CNN
	1    9650 7150
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0118
U 1 1 5E4AEDFA
P 10200 9650
F 0 "#PWR0118" H 10200 9400 50  0001 C CNN
F 1 "GND" H 10205 9477 50  0000 C CNN
F 2 "" H 10200 9650 50  0001 C CNN
F 3 "" H 10200 9650 50  0001 C CNN
	1    10200 9650
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0120
U 1 1 5E4AF14D
P 9900 9650
F 0 "#PWR0120" H 9900 9400 50  0001 C CNN
F 1 "GND" H 9905 9477 50  0000 C CNN
F 2 "" H 9900 9650 50  0001 C CNN
F 3 "" H 9900 9650 50  0001 C CNN
	1    9900 9650
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C47
U 1 1 5C4B998D
P 8450 6950
F 0 "C47" H 8200 6900 50  0000 L CNN
F 1 "1u" H 8250 7050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8488 6800 50  0001 C CNN
F 3 "~" H 8450 6950 50  0001 C CNN
	1    8450 6950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9600 9100 9600 8900
Wire Wire Line
	9500 8350 9900 8350
Wire Wire Line
	9500 7800 10200 7800
Wire Wire Line
	9050 6050 9050 7100
Wire Wire Line
	9450 7100 9650 7100
Wire Wire Line
	9650 7100 9650 7150
Wire Wire Line
	8300 6950 8150 6950
Wire Wire Line
	8150 6950 8150 7100
Wire Wire Line
	8600 6950 8800 6950
Wire Wire Line
	8800 6950 8800 7350
Connection ~ 9050 7100
Wire Wire Line
	9050 7100 9050 7350
Wire Wire Line
	9050 7100 9150 7100
$Comp
L LrE-6:OLED-0.91 U3
U 1 1 5E1BA71E
P 8900 8450
F 0 "U3" H 8900 8500 50  0000 C CNN
F 1 "SSD1306_OLED_0.91" H 8900 8400 50  0000 C CNN
F 2 "LrE-6:OLED-9.1" H 8900 8450 50  0001 C CNN
F 3 "" H 8900 8450 50  0001 C CNN
	1    8900 8450
	1    0    0    -1  
$EndComp
NoConn ~ 9500 8700
Wire Wire Line
	6900 7800 7850 7800
Wire Wire Line
	6900 7950 7600 7950
Wire Wire Line
	7600 6950 7600 6050
$Comp
L LrE-6-rescue:R-Device R44
U 1 1 5EEE6BD3
P 8800 6400
F 0 "R44" H 8550 6500 50  0000 L CNN
F 1 "100" H 8550 6400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8730 6400 50  0001 C CNN
F 3 "~" H 8800 6400 50  0001 C CNN
	1    8800 6400
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R42
U 1 1 5EEE73A1
P 8450 6700
F 0 "R42" V 8243 6700 50  0000 C CNN
F 1 "1K" V 8334 6700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8380 6700 50  0001 C CNN
F 3 "~" H 8450 6700 50  0001 C CNN
	1    8450 6700
	0    1    1    0   
$EndComp
Wire Wire Line
	8800 6550 8800 6700
Connection ~ 8800 6950
Wire Wire Line
	8600 6700 8800 6700
Connection ~ 8800 6700
Wire Wire Line
	8800 6700 8800 6950
Wire Wire Line
	8300 6700 8150 6700
Wire Wire Line
	8150 6700 8150 6950
Connection ~ 8150 6950
Wire Wire Line
	7600 6050 7850 6050
Connection ~ 7600 6050
Wire Wire Line
	7600 6050 7600 6000
Connection ~ 7850 6050
Wire Wire Line
	7850 6050 8800 6050
Wire Wire Line
	8800 6250 8800 6050
Connection ~ 8800 6050
Wire Wire Line
	8800 6050 9050 6050
NoConn ~ 9100 5250
NoConn ~ 9100 4450
NoConn ~ 9100 4550
Wire Wire Line
	9100 4650 9600 4650
Wire Wire Line
	9100 4750 9600 4750
Text Label 7300 3950 0    50   ~ 0
ENC6A
Text Label 7300 4050 0    50   ~ 0
ENC6B
NoConn ~ 7800 3750
NoConn ~ 7800 3850
Wire Wire Line
	7800 5150 7300 5150
Wire Wire Line
	7800 3350 7300 3350
Text Label 7300 4350 0    50   ~ 0
ENC7A
Text Label 7300 4450 0    50   ~ 0
ENC7B
NoConn ~ 7800 5250
$Comp
L LrE-6-rescue:Rotary_Encoder_Switch-Device SW17
U 1 1 60A92800
P 5500 6600
F 0 "SW17" H 5500 6967 50  0000 C CNN
F 1 "EC11_SMD" H 5500 6876 50  0000 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC11E-Switch_Vertical_H20mm" H 5350 6760 50  0001 C CNN
F 3 "~" H 5500 6860 50  0001 C CNN
	1    5500 6600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R25
U 1 1 60A92812
P 4600 6250
F 0 "R25" H 4670 6296 50  0000 L CNN
F 1 "10K" H 4670 6205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4530 6250 50  0001 C CNN
F 3 "~" H 4600 6250 50  0001 C CNN
	1    4600 6250
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R24
U 1 1 60A92818
P 4300 6250
F 0 "R24" H 4370 6296 50  0000 L CNN
F 1 "10K" H 4370 6205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4230 6250 50  0001 C CNN
F 3 "~" H 4300 6250 50  0001 C CNN
	1    4300 6250
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:+3V3-power #PWR0143
U 1 1 60A9282C
P 4300 6000
F 0 "#PWR0143" H 4300 5850 50  0001 C CNN
F 1 "+3V3" H 4315 6173 50  0000 C CNN
F 2 "" H 4300 6000 50  0001 C CNN
F 3 "" H 4300 6000 50  0001 C CNN
	1    4300 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 6000 4300 6050
Wire Wire Line
	4600 6100 4600 6050
Wire Wire Line
	4600 6050 4300 6050
Connection ~ 4300 6050
Wire Wire Line
	4300 6050 4300 6100
Wire Wire Line
	5200 6700 4800 6700
Wire Wire Line
	4300 6400 4300 6500
Connection ~ 4300 6500
Wire Wire Line
	4600 6400 4600 6700
Connection ~ 4600 6700
Wire Wire Line
	3650 6500 4300 6500
Wire Wire Line
	3650 6700 4600 6700
$Comp
L LrE-6-rescue:C-Device C24
U 1 1 60A92843
P 4450 6900
F 0 "C24" H 4565 6946 50  0000 L CNN
F 1 "22n" H 4500 6800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4488 6750 50  0001 C CNN
F 3 "~" H 4450 6900 50  0001 C CNN
	1    4450 6900
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C25
U 1 1 60A92849
P 4800 6900
F 0 "C25" H 4915 6946 50  0000 L CNN
F 1 "22n" H 4900 6800 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4838 6750 50  0001 C CNN
F 3 "~" H 4800 6900 50  0001 C CNN
	1    4800 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 6750 4450 6500
Connection ~ 4450 6500
Wire Wire Line
	4450 6500 4300 6500
$Comp
L LrE-6-rescue:GND-power #PWR0151
U 1 1 60A92864
P 4450 7200
F 0 "#PWR0151" H 4450 6950 50  0001 C CNN
F 1 "GND" H 4455 7027 50  0000 C CNN
F 2 "" H 4450 7200 50  0001 C CNN
F 3 "" H 4450 7200 50  0001 C CNN
	1    4450 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 7200 4450 7150
Wire Wire Line
	5200 6600 5150 6600
Wire Wire Line
	5150 6600 5150 7150
Wire Wire Line
	5150 7150 4800 7150
Connection ~ 4450 7150
Wire Wire Line
	4450 7150 4450 7050
Wire Wire Line
	4800 7050 4800 7150
Connection ~ 4800 7150
Wire Wire Line
	4800 7150 4450 7150
Text Label 3650 6500 0    50   ~ 0
ENC7A
Text Label 3650 6700 0    50   ~ 0
ENC7B
$Comp
L LrE-6-rescue:1N4148W-Diode D17
U 1 1 60A9288C
P 5800 6850
F 0 "D17" V 5846 6770 50  0000 R CNN
F 1 "1N4148W" V 5755 6770 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 5800 6675 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5800 6850 50  0001 C CNN
	1    5800 6850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 7000 5800 7200
Text Label 6050 7200 0    50   ~ 0
M3
Text Label 6050 6500 0    50   ~ 0
L3
Wire Wire Line
	4450 6500 5200 6500
Wire Wire Line
	4800 6750 4800 6700
Connection ~ 4800 6700
Wire Wire Line
	4800 6700 4600 6700
$Comp
L LrE-6-rescue:GND-power #PWR0153
U 1 1 60A928A0
P 5450 7000
F 0 "#PWR0153" H 5450 6750 50  0001 C CNN
F 1 "GND" H 5455 6827 50  0000 C CNN
F 2 "" H 5450 7000 50  0001 C CNN
F 3 "" H 5450 7000 50  0001 C CNN
	1    5450 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 6900 5450 6950
Wire Wire Line
	5450 6950 5600 6950
Wire Wire Line
	5600 6950 5600 6900
Connection ~ 5450 6950
Wire Wire Line
	5450 6950 5450 7000
Wire Wire Line
	13950 5400 14500 5400
Connection ~ 13950 5400
Wire Wire Line
	13950 6450 14500 6450
Connection ~ 13950 6450
Wire Wire Line
	14050 7500 14550 7500
Connection ~ 14050 7500
Wire Wire Line
	14050 8700 14550 8700
Connection ~ 14050 8700
$Comp
L LrE-6:WS2812B-2020 D37
U 1 1 60809BD1
P 8550 10600
F 0 "D37" H 8250 10850 50  0000 L CNN
F 1 "WS2812B-2020" H 8050 10350 50  0000 L CNN
F 2 "LrE-6:LED_WS2812B-2020" H 8600 10300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/2686/SK6812MINI_REV.01-1-2.pdf" H 8650 10225 50  0001 L TNN
	1    8550 10600
	1    0    0    -1  
$EndComp
$Comp
L LrE-6:WS2812B-2020 D38
U 1 1 60809BD7
P 9700 10600
F 0 "D38" H 9350 10850 50  0000 L CNN
F 1 "WS2812B-2020" H 9200 10350 50  0000 L CNN
F 2 "LrE-6:LED_WS2812B-2020" H 9750 10300 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/2686/SK6812MINI_REV.01-1-2.pdf" H 9800 10225 50  0001 L TNN
	1    9700 10600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 10950 9700 10900
Wire Wire Line
	8550 10900 8550 10950
Wire Wire Line
	8550 10950 8950 10950
Wire Wire Line
	9700 10300 9700 10150
Wire Wire Line
	9700 10150 8950 10150
Wire Wire Line
	8550 10300 8550 10150
Wire Wire Line
	8850 10600 9400 10600
$Comp
L LrE-6-rescue:C-Device C37
U 1 1 60809BE9
P 8950 10300
F 0 "C37" H 9065 10346 50  0000 L CNN
F 1 "0.1u" H 9065 10255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8988 10150 50  0001 C CNN
F 3 "~" H 8950 10300 50  0001 C CNN
	1    8950 10300
	1    0    0    -1  
$EndComp
Connection ~ 8950 10150
Wire Wire Line
	8950 10150 8550 10150
$Comp
L LrE-6-rescue:C-Device C38
U 1 1 60809BF1
P 10150 10300
F 0 "C38" H 10265 10346 50  0000 L CNN
F 1 "0.1u" H 10265 10255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10188 10150 50  0001 C CNN
F 3 "~" H 10150 10300 50  0001 C CNN
	1    10150 10300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 10150 10150 10150
Connection ~ 9700 10150
Wire Wire Line
	9700 10950 10150 10950
Wire Wire Line
	10150 10950 10150 10450
Connection ~ 9700 10950
Wire Wire Line
	8950 10450 8950 10950
Connection ~ 8950 10950
Wire Wire Line
	8950 10950 9700 10950
Text Label 9050 10600 0    50   ~ 0
LED7OUT
Text Label 7850 10600 0    50   ~ 0
LED6OUT
Wire Wire Line
	7600 10600 8250 10600
Wire Wire Line
	7750 10950 8550 10950
Connection ~ 7750 10950
Connection ~ 8550 10950
Wire Wire Line
	7750 10150 8550 10150
Connection ~ 7750 10150
Connection ~ 8550 10150
NoConn ~ 10000 10600
Connection ~ 4550 1550
Connection ~ 4250 1350
Wire Wire Line
	2550 6900 2550 6950
Connection ~ 2550 6900
Wire Wire Line
	2700 6900 2550 6900
Wire Wire Line
	2700 6850 2700 6900
Wire Wire Line
	2550 6850 2550 6900
$Comp
L LrE-6-rescue:GND-power #PWR0150
U 1 1 5E9A409D
P 2550 6950
F 0 "#PWR0150" H 2550 6700 50  0001 C CNN
F 1 "GND" H 2555 6777 50  0000 C CNN
F 2 "" H 2550 6950 50  0001 C CNN
F 3 "" H 2550 6950 50  0001 C CNN
	1    2550 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5150 2450 5200
Connection ~ 2450 5150
Wire Wire Line
	2450 5150 2600 5150
Wire Wire Line
	2600 5100 2600 5150
Wire Wire Line
	2450 5100 2450 5150
Wire Wire Line
	2550 3500 2550 3550
Connection ~ 2550 3500
Wire Wire Line
	2700 3500 2700 3450
Wire Wire Line
	2550 3500 2700 3500
Wire Wire Line
	2550 3450 2550 3500
$Comp
L LrE-6-rescue:GND-power #PWR0148
U 1 1 5E3D5025
P 2450 5200
F 0 "#PWR0148" H 2450 4950 50  0001 C CNN
F 1 "GND" H 2455 5027 50  0000 C CNN
F 2 "" H 2450 5200 50  0001 C CNN
F 3 "" H 2450 5200 50  0001 C CNN
	1    2450 5200
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0145
U 1 1 5E26EB21
P 2550 3550
F 0 "#PWR0145" H 2550 3300 50  0001 C CNN
F 1 "GND" H 2555 3377 50  0000 C CNN
F 2 "" H 2550 3550 50  0001 C CNN
F 3 "" H 2550 3550 50  0001 C CNN
	1    2550 3550
	1    0    0    -1  
$EndComp
Text Label 3200 7100 0    50   ~ 0
M3
Wire Wire Line
	2900 7100 3250 7100
Wire Wire Line
	2900 6950 2900 7100
Text Label 3150 6450 0    50   ~ 0
L2
Text Label 3050 5400 0    50   ~ 0
M2
Text Label 3150 3750 0    50   ~ 0
M1
Text Label 3050 4700 0    50   ~ 0
L2
Text Label 3200 3050 0    50   ~ 0
L2
Wire Wire Line
	2900 6450 3150 6450
Wire Wire Line
	2900 3050 3200 3050
Wire Wire Line
	2800 4700 3050 4700
Wire Wire Line
	2800 5400 3050 5400
Wire Wire Line
	2800 5200 2800 5400
Wire Wire Line
	2900 3750 3150 3750
Wire Wire Line
	2900 3550 2900 3750
$Comp
L LrE-6-rescue:1N4148W-Diode D13
U 1 1 5CACBDAF
P 2900 6800
F 0 "D13" V 2946 6720 50  0000 R CNN
F 1 "1N4148W" V 2855 6720 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 2900 6625 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2900 6800 50  0001 C CNN
	1    2900 6800
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D11
U 1 1 5CACAD5F
P 2900 3400
F 0 "D11" V 2946 3320 50  0000 R CNN
F 1 "1N4148W" V 2855 3320 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 2900 3225 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2900 3400 50  0001 C CNN
	1    2900 3400
	0    -1   -1   0   
$EndComp
$Comp
L LrE-6-rescue:1N4148W-Diode D12
U 1 1 5CAC9D35
P 2800 5050
F 0 "D12" V 2846 4970 50  0000 R CNN
F 1 "1N4148W" V 2755 4970 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 2800 4875 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2800 5050 50  0001 C CNN
	1    2800 5050
	0    -1   -1   0   
$EndComp
Text Label 3550 1550 0    50   ~ 0
ENC4B
Text Label 3550 1350 0    50   ~ 0
ENC4A
Text Label 900  6650 0    50   ~ 0
ENC3B
Text Label 900  6450 0    50   ~ 0
ENC3A
Text Label 900  4900 0    50   ~ 0
ENC2B
Text Label 900  4700 0    50   ~ 0
ENC2A
Text Label 950  3250 0    50   ~ 0
ENC1B
Text Label 950  3050 0    50   ~ 0
ENC1A
Wire Wire Line
	1900 3650 2200 3650
Connection ~ 1900 3650
Wire Wire Line
	1900 3600 1900 3650
Wire Wire Line
	1550 3650 1550 3700
Connection ~ 1550 3650
Wire Wire Line
	2200 3150 2300 3150
Wire Wire Line
	2200 3650 2200 3150
Wire Wire Line
	1550 3650 1900 3650
Wire Wire Line
	1550 3600 1550 3650
$Comp
L LrE-6-rescue:GND-power #PWR0132
U 1 1 5CB17BB7
P 1550 3700
F 0 "#PWR0132" H 1550 3450 50  0001 C CNN
F 1 "GND" H 1555 3527 50  0000 C CNN
F 2 "" H 1550 3700 50  0001 C CNN
F 3 "" H 1550 3700 50  0001 C CNN
	1    1550 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 5300 1500 5300
Connection ~ 1850 5300
Wire Wire Line
	1850 5250 1850 5300
Wire Wire Line
	1500 5300 1500 5250
Connection ~ 1500 5300
Wire Wire Line
	2150 5300 1850 5300
Wire Wire Line
	2150 4800 2150 5300
Wire Wire Line
	2200 4800 2150 4800
Connection ~ 1950 7050
Wire Wire Line
	2250 7050 1950 7050
Wire Wire Line
	2250 6550 2250 7050
Wire Wire Line
	2300 6550 2250 6550
Wire Wire Line
	1600 7050 1600 7100
Connection ~ 1600 7050
Wire Wire Line
	1950 7050 1950 7000
Wire Wire Line
	1600 7050 1950 7050
Wire Wire Line
	1600 7000 1600 7050
Wire Wire Line
	1500 5350 1500 5300
$Comp
L LrE-6-rescue:GND-power #PWR0131
U 1 1 5C9CBCA0
P 1500 5350
F 0 "#PWR0131" H 1500 5100 50  0001 C CNN
F 1 "GND" H 1505 5177 50  0000 C CNN
F 2 "" H 1500 5350 50  0001 C CNN
F 3 "" H 1500 5350 50  0001 C CNN
	1    1500 5350
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:GND-power #PWR0130
U 1 1 5C9CBBAE
P 1600 7100
F 0 "#PWR0130" H 1600 6850 50  0001 C CNN
F 1 "GND" H 1605 6927 50  0000 C CNN
F 2 "" H 1600 7100 50  0001 C CNN
F 3 "" H 1600 7100 50  0001 C CNN
	1    1600 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 6650 1800 6650
Connection ~ 1950 6650
Wire Wire Line
	1950 6700 1950 6650
Wire Wire Line
	1600 6450 1450 6450
Connection ~ 1600 6450
Wire Wire Line
	1600 6700 1600 6450
$Comp
L LrE-6-rescue:C-Device C17
U 1 1 5C92B0B3
P 1950 6850
F 0 "C17" H 2065 6896 50  0000 L CNN
F 1 "22n" H 2000 6750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1988 6700 50  0001 C CNN
F 3 "~" H 1950 6850 50  0001 C CNN
	1    1950 6850
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C16
U 1 1 5C92AEF7
P 1600 6850
F 0 "C16" H 1715 6896 50  0000 L CNN
F 1 "22n" H 1700 6750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1638 6700 50  0001 C CNN
F 3 "~" H 1600 6850 50  0001 C CNN
	1    1600 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4900 1700 4900
Connection ~ 1850 4900
Wire Wire Line
	1850 4950 1850 4900
Wire Wire Line
	1500 4700 1400 4700
Connection ~ 1500 4700
Wire Wire Line
	1500 4950 1500 4700
Wire Wire Line
	1900 3250 1700 3250
Connection ~ 1900 3250
Wire Wire Line
	1900 3300 1900 3250
Wire Wire Line
	1550 3050 1400 3050
Connection ~ 1550 3050
Wire Wire Line
	1550 3300 1550 3050
$Comp
L LrE-6-rescue:C-Device C15
U 1 1 5C8CF86C
P 1850 5100
F 0 "C15" H 1965 5146 50  0000 L CNN
F 1 "22n" H 1900 5000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1888 4950 50  0001 C CNN
F 3 "~" H 1850 5100 50  0001 C CNN
	1    1850 5100
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C14
U 1 1 5C8CF744
P 1500 5100
F 0 "C14" H 1615 5146 50  0000 L CNN
F 1 "22n" H 1550 5000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1538 4950 50  0001 C CNN
F 3 "~" H 1500 5100 50  0001 C CNN
	1    1500 5100
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C13
U 1 1 5C8CF611
P 1900 3450
F 0 "C13" H 2015 3496 50  0000 L CNN
F 1 "22n" H 1950 3350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1938 3300 50  0001 C CNN
F 3 "~" H 1900 3450 50  0001 C CNN
	1    1900 3450
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C12
U 1 1 5C8CF4FD
P 1550 3450
F 0 "C12" H 1665 3496 50  0000 L CNN
F 1 "22n" H 1600 3350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1588 3300 50  0001 C CNN
F 3 "~" H 1550 3450 50  0001 C CNN
	1    1550 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2650 1400 2700
Connection ~ 1400 2650
Wire Wire Line
	1700 2650 1400 2650
Wire Wire Line
	1700 2700 1700 2650
Wire Wire Line
	1400 2600 1400 2650
Wire Wire Line
	1450 6000 1450 6050
Connection ~ 1450 6000
Wire Wire Line
	1800 6000 1450 6000
Wire Wire Line
	1800 6050 1800 6000
Wire Wire Line
	1450 5950 1450 6000
Wire Wire Line
	1400 4300 1400 4350
Connection ~ 1400 4300
Wire Wire Line
	1700 4300 1700 4350
Wire Wire Line
	1400 4300 1700 4300
Wire Wire Line
	1400 4250 1400 4300
Wire Wire Line
	4550 1550 3550 1550
Wire Wire Line
	4250 1350 3550 1350
$Comp
L LrE-6-rescue:+3V3-power #PWR0125
U 1 1 5C723D83
P 1450 5950
F 0 "#PWR0125" H 1450 5800 50  0001 C CNN
F 1 "+3V3" H 1465 6123 50  0000 C CNN
F 2 "" H 1450 5950 50  0001 C CNN
F 3 "" H 1450 5950 50  0001 C CNN
	1    1450 5950
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:+3V3-power #PWR0124
U 1 1 5C723C85
P 1400 4250
F 0 "#PWR0124" H 1400 4100 50  0001 C CNN
F 1 "+3V3" H 1415 4423 50  0000 C CNN
F 2 "" H 1400 4250 50  0001 C CNN
F 3 "" H 1400 4250 50  0001 C CNN
	1    1400 4250
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:+3V3-power #PWR0123
U 1 1 5C723BBE
P 1400 2600
F 0 "#PWR0123" H 1400 2450 50  0001 C CNN
F 1 "+3V3" H 1415 2773 50  0000 C CNN
F 2 "" H 1400 2600 50  0001 C CNN
F 3 "" H 1400 2600 50  0001 C CNN
	1    1400 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 3250 950  3250
Connection ~ 1700 3250
Wire Wire Line
	1700 3000 1700 3250
Wire Wire Line
	1400 3050 950  3050
Connection ~ 1400 3050
Wire Wire Line
	1400 3000 1400 3050
Wire Wire Line
	1700 4900 900  4900
Connection ~ 1700 4900
Wire Wire Line
	1700 4650 1700 4900
Wire Wire Line
	1400 4700 900  4700
Connection ~ 1400 4700
Wire Wire Line
	1400 4650 1400 4700
Wire Wire Line
	1800 6650 900  6650
Connection ~ 1800 6650
Wire Wire Line
	1800 6350 1800 6650
Wire Wire Line
	1450 6450 900  6450
Connection ~ 1450 6450
Wire Wire Line
	1450 6350 1450 6450
Wire Wire Line
	2300 6650 1950 6650
Wire Wire Line
	2300 6450 1600 6450
Wire Wire Line
	2200 4900 1850 4900
Wire Wire Line
	2200 4700 1500 4700
Wire Wire Line
	2300 3250 1900 3250
Wire Wire Line
	2300 3050 1550 3050
$Comp
L LrE-6-rescue:R-Device R16
U 1 1 5C6ABE01
P 1450 6200
F 0 "R16" H 1520 6246 50  0000 L CNN
F 1 "10K" H 1520 6155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1380 6200 50  0001 C CNN
F 3 "~" H 1450 6200 50  0001 C CNN
	1    1450 6200
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R17
U 1 1 5C6ABCC1
P 1800 6200
F 0 "R17" H 1870 6246 50  0000 L CNN
F 1 "10K" H 1870 6155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1730 6200 50  0001 C CNN
F 3 "~" H 1800 6200 50  0001 C CNN
	1    1800 6200
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R14
U 1 1 5C6ABBD0
P 1400 4500
F 0 "R14" H 1470 4546 50  0000 L CNN
F 1 "10K" H 1470 4455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1330 4500 50  0001 C CNN
F 3 "~" H 1400 4500 50  0001 C CNN
	1    1400 4500
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R15
U 1 1 5C6ABADC
P 1700 4500
F 0 "R15" H 1770 4546 50  0000 L CNN
F 1 "10K" H 1770 4455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1630 4500 50  0001 C CNN
F 3 "~" H 1700 4500 50  0001 C CNN
	1    1700 4500
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R12
U 1 1 5C6AB990
P 1400 2850
F 0 "R12" H 1470 2896 50  0000 L CNN
F 1 "10K" H 1470 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1330 2850 50  0001 C CNN
F 3 "~" H 1400 2850 50  0001 C CNN
	1    1400 2850
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R13
U 1 1 5C6AB881
P 1700 2850
F 0 "R13" H 1770 2896 50  0000 L CNN
F 1 "10K" H 1770 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1630 2850 50  0001 C CNN
F 3 "~" H 1700 2850 50  0001 C CNN
	1    1700 2850
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:Rotary_Encoder_Switch-Device SW13
U 1 1 5C6AB18A
P 2600 6550
F 0 "SW13" H 2600 6917 50  0000 C CNN
F 1 "EC11_SMD" H 2600 6826 50  0000 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC11E-Switch_Vertical_H20mm" H 2450 6710 50  0001 C CNN
F 3 "~" H 2600 6810 50  0001 C CNN
	1    2600 6550
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:Rotary_Encoder_Switch-Device SW12
U 1 1 5C6AB096
P 2500 4800
F 0 "SW12" H 2500 5167 50  0000 C CNN
F 1 "EC11_SMD" H 2500 5076 50  0000 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC11E-Switch_Vertical_H20mm" H 2350 4960 50  0001 C CNN
F 3 "~" H 2500 5060 50  0001 C CNN
	1    2500 4800
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:Rotary_Encoder_Switch-Device SW11
U 1 1 5C6AAF87
P 2600 3150
F 0 "SW11" H 2600 3517 50  0000 C CNN
F 1 "EC11_SMD" H 2600 3426 50  0000 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC11E-Switch_Vertical_H20mm" H 2450 3310 50  0001 C CNN
F 3 "~" H 2600 3410 50  0001 C CNN
	1    2600 3150
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:Rotary_Encoder_Switch-Device SW16
U 1 1 60A927FA
P 5450 4900
F 0 "SW16" H 5450 5267 50  0000 C CNN
F 1 "EC11_SMD" H 5450 5176 50  0000 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC11E-Switch_Vertical_H20mm" H 5300 5060 50  0001 C CNN
F 3 "~" H 5450 5160 50  0001 C CNN
	1    5450 4900
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R23
U 1 1 60A92806
P 4650 4550
F 0 "R23" H 4720 4596 50  0000 L CNN
F 1 "10K" H 4720 4505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4580 4550 50  0001 C CNN
F 3 "~" H 4650 4550 50  0001 C CNN
	1    4650 4550
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R22
U 1 1 60A9280C
P 4300 4550
F 0 "R22" H 4370 4596 50  0000 L CNN
F 1 "10K" H 4370 4505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4230 4550 50  0001 C CNN
F 3 "~" H 4300 4550 50  0001 C CNN
	1    4300 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4800 4450 4800
Wire Wire Line
	5150 5000 4800 5000
Wire Wire Line
	4300 4700 4300 4800
Connection ~ 4300 4800
Wire Wire Line
	4300 4800 3750 4800
Wire Wire Line
	4650 4700 4650 5000
Connection ~ 4650 5000
Wire Wire Line
	4650 5000 3750 5000
$Comp
L LrE-6-rescue:+3V3-power #PWR0142
U 1 1 60A92826
P 4300 4300
F 0 "#PWR0142" H 4300 4150 50  0001 C CNN
F 1 "+3V3" H 4315 4473 50  0000 C CNN
F 2 "" H 4300 4300 50  0001 C CNN
F 3 "" H 4300 4300 50  0001 C CNN
	1    4300 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 4300 4300 4350
Wire Wire Line
	4650 4400 4650 4350
Wire Wire Line
	4650 4350 4300 4350
Connection ~ 4300 4350
Wire Wire Line
	4300 4350 4300 4400
$Comp
L LrE-6-rescue:C-Device C22
U 1 1 60A9284F
P 4450 5200
F 0 "C22" H 4565 5246 50  0000 L CNN
F 1 "22n" H 4550 5100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4488 5050 50  0001 C CNN
F 3 "~" H 4450 5200 50  0001 C CNN
	1    4450 5200
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:C-Device C23
U 1 1 60A92855
P 4800 5200
F 0 "C23" H 4915 5246 50  0000 L CNN
F 1 "22n" H 4850 5100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4838 5050 50  0001 C CNN
F 3 "~" H 4800 5200 50  0001 C CNN
	1    4800 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 5050 4450 4800
Connection ~ 4450 4800
Wire Wire Line
	4450 4800 4300 4800
Wire Wire Line
	4800 5050 4800 5000
Connection ~ 4800 5000
Wire Wire Line
	4800 5000 4650 5000
$Comp
L LrE-6-rescue:GND-power #PWR0152
U 1 1 60A9286A
P 4450 5450
F 0 "#PWR0152" H 4450 5200 50  0001 C CNN
F 1 "GND" H 4455 5277 50  0000 C CNN
F 2 "" H 4450 5450 50  0001 C CNN
F 3 "" H 4450 5450 50  0001 C CNN
	1    4450 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 5350 4450 5400
Wire Wire Line
	4450 5400 4800 5400
Wire Wire Line
	4800 5400 4800 5350
Connection ~ 4450 5400
Wire Wire Line
	4450 5400 4450 5450
Wire Wire Line
	5150 4900 5100 4900
Wire Wire Line
	5100 4900 5100 5400
Wire Wire Line
	5100 5400 4800 5400
Connection ~ 4800 5400
Text Label 3750 4800 0    50   ~ 0
ENC6A
Text Label 3750 5000 0    50   ~ 0
ENC6B
$Comp
L LrE-6-rescue:1N4148W-Diode D16
U 1 1 60A92886
P 5750 5150
F 0 "D16" V 5796 5070 50  0000 R CNN
F 1 "1N4148W" V 5705 5070 50  0000 R CNN
F 2 "LrE-6:D_SOD-123" H 5750 4975 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5750 5150 50  0001 C CNN
	1    5750 5150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5750 4800 6000 4800
Text Label 6000 4800 0    50   ~ 0
L3
Wire Wire Line
	5750 5300 5750 5450
Wire Wire Line
	5750 5450 6100 5450
Text Label 6100 5450 0    50   ~ 0
M2
$Comp
L LrE-6-rescue:GND-power #PWR0154
U 1 1 60A928AB
P 5400 5300
F 0 "#PWR0154" H 5400 5050 50  0001 C CNN
F 1 "GND" H 5405 5127 50  0000 C CNN
F 2 "" H 5400 5300 50  0001 C CNN
F 3 "" H 5400 5300 50  0001 C CNN
	1    5400 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 5200 5400 5250
Wire Wire Line
	5550 5200 5550 5250
Wire Wire Line
	5550 5250 5400 5250
Connection ~ 5400 5250
Wire Wire Line
	5400 5250 5400 5300
Wire Wire Line
	2900 1350 3100 1350
Wire Wire Line
	2900 2050 3100 2050
Wire Wire Line
	1400 1350 950  1350
Connection ~ 1400 1350
Wire Wire Line
	1700 1550 950  1550
Connection ~ 1700 1550
Wire Wire Line
	5800 6500 6050 6500
Wire Wire Line
	5800 7200 6050 7200
Wire Wire Line
	5800 3050 6050 3050
Wire Wire Line
	5800 3650 6050 3650
Wire Wire Line
	800  10150 1600 10150
$Comp
L LrE-6-rescue:GND-power #PWR01
U 1 1 60DE7033
P 10850 3700
F 0 "#PWR01" H 10850 3450 50  0001 C CNN
F 1 "GND" H 10855 3527 50  0000 C CNN
F 2 "" H 10850 3700 50  0001 C CNN
F 3 "" H 10850 3700 50  0001 C CNN
	1    10850 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 3350 10850 3350
Wire Wire Line
	10850 3350 10850 3400
Connection ~ 10300 3350
Wire Wire Line
	10000 3350 10300 3350
$Comp
L LrE-6:USB_C_Receptacle_USB2.0 J1
U 1 1 615E347D
P 11700 1500
F 0 "J1" H 11807 2367 50  0000 C CNN
F 1 "USB_C_Receptacle_USB2.0" H 11807 2276 50  0000 C CNN
F 2 "Connector_USB:USB_C_Receptacle_HRO_TYPE-C-31-M-12" H 11850 1500 50  0001 C CNN
F 3 "https://www.usb.org/sites/default/files/documents/usb_type-c.zip" H 11850 1500 50  0001 C CNN
	1    11700 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	11400 2500 11400 2400
Wire Wire Line
	11700 2400 11700 2500
Wire Wire Line
	11400 2500 11700 2500
Wire Wire Line
	12300 900  13950 900 
Wire Wire Line
	12300 1400 12400 1400
Wire Wire Line
	12300 1600 12400 1600
Wire Wire Line
	12300 1700 12400 1700
Wire Wire Line
	12400 1700 12400 1600
Wire Wire Line
	12300 1500 12400 1500
Wire Wire Line
	12400 1500 12400 1400
Wire Wire Line
	12400 1400 12900 1400
Connection ~ 12400 1400
Wire Wire Line
	12400 1600 12900 1600
Connection ~ 12400 1600
$Comp
L LrE-6-rescue:R-Device R5
U 1 1 61D441AE
P 13150 1350
F 0 "R5" H 13220 1396 50  0000 L CNN
F 1 "5.1K" H 13220 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 13080 1350 50  0001 C CNN
F 3 "" H 13150 1350 50  0001 C CNN
	1    13150 1350
	1    0    0    -1  
$EndComp
$Comp
L LrE-6-rescue:R-Device R6
U 1 1 61D90C84
P 13450 1350
F 0 "R6" H 13520 1396 50  0000 L CNN
F 1 "5.1K" H 13520 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 13380 1350 50  0001 C CNN
F 3 "" H 13450 1350 50  0001 C CNN
	1    13450 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	13150 1200 12300 1200
Wire Wire Line
	13450 1200 13450 1100
Wire Wire Line
	13450 1100 12300 1100
Wire Wire Line
	13450 1600 13450 1550
Wire Wire Line
	13150 1500 13150 1550
Wire Wire Line
	13150 1550 13450 1550
Connection ~ 13450 1550
Wire Wire Line
	13450 1550 13450 1500
$Comp
L LrE-6-rescue:GND-power #PWR02
U 1 1 61F167BF
P 13450 1600
F 0 "#PWR02" H 13450 1350 50  0001 C CNN
F 1 "GND" H 13455 1427 50  0000 C CNN
F 2 "" H 13450 1600 50  0001 C CNN
F 3 "" H 13450 1600 50  0001 C CNN
	1    13450 1600
	1    0    0    -1  
$EndComp
NoConn ~ 12300 2000
NoConn ~ 12300 2100
$Comp
L Device:R R8
U 1 1 63D44D4B
P 6700 3150
F 0 "R8" H 6770 3196 50  0000 L CNN
F 1 "0" H 6770 3105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6630 3150 50  0001 C CNN
F 3 "~" H 6700 3150 50  0001 C CNN
	1    6700 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 63DDF5C7
P 6700 2650
F 0 "R7" H 6770 2696 50  0000 L CNN
F 1 "10K" H 6770 2605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6630 2650 50  0001 C CNN
F 3 "~" H 6700 2650 50  0001 C CNN
	1    6700 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2800 6700 2850
Connection ~ 6700 2850
$Comp
L LrE-6-rescue:+3V3-power #PWR03
U 1 1 63E32B48
P 6700 2500
F 0 "#PWR03" H 6700 2350 50  0001 C CNN
F 1 "+3V3" H 6715 2673 50  0000 C CNN
F 2 "" H 6700 2500 50  0001 C CNN
F 3 "" H 6700 2500 50  0001 C CNN
	1    6700 2500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
