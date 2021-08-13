EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L power:GND #PWR?
U 1 1 60D6C2FC
P 1800 1850
AR Path="/60D6C2FC" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60D6C2FC" Ref="#PWR025"  Part="1" 
F 0 "#PWR025" H 1800 1600 50  0001 C CNN
F 1 "GND" H 1805 1677 50  0000 C CNN
F 2 "" H 1800 1850 50  0001 C CNN
F 3 "" H 1800 1850 50  0001 C CNN
	1    1800 1850
	1    0    0    -1  
$EndComp
$Comp
L Interface_USB:FT231XS U?
U 1 1 60D6C304
P 9100 2300
AR Path="/60D6C304" Ref="U?"  Part="1" 
AR Path="/60D5E44C/60D6C304" Ref="U5"  Part="1" 
F 0 "U5" H 9100 3381 50  0000 C CNN
F 1 "FT231XS" H 9100 3290 50  0000 C CNN
F 2 "Package_SO:SSOP-20_3.9x8.7mm_P0.635mm" H 10100 1500 50  0001 C CNN
F 3 "https://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT231X.pdf" H 9100 2300 50  0001 C CNN
	1    9100 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2000 8150 2000
Wire Wire Line
	8400 2100 8150 2100
Wire Wire Line
	9800 1700 10200 1700
Wire Wire Line
	9800 1800 10200 1800
Wire Wire Line
	9000 1100 9000 1400
$Comp
L power:GND #PWR?
U 1 1 60D6C315
P 9100 3550
AR Path="/60D6C315" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60D6C315" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 9100 3300 50  0001 C CNN
F 1 "GND" H 9105 3377 50  0000 C CNN
F 2 "" H 9100 3550 50  0001 C CNN
F 3 "" H 9100 3550 50  0001 C CNN
	1    9100 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 3200 9000 3400
Wire Wire Line
	9200 3400 9200 3200
Wire Wire Line
	9000 3400 9100 3400
Wire Wire Line
	8400 2300 8300 2300
Wire Wire Line
	8300 2300 8300 1700
Connection ~ 8300 1700
Wire Wire Line
	9100 3550 9100 3400
Connection ~ 9100 3400
Wire Wire Line
	9100 3400 9200 3400
Text Label 7550 2000 0    50   ~ 0
USB_DM
Text Label 7550 2100 0    50   ~ 0
USB_DP
Wire Wire Line
	10050 2550 10050 2450
Wire Wire Line
	10050 2850 10050 2800
$Comp
L power:GND #PWR?
U 1 1 60D6C333
P 10050 2850
AR Path="/60D6C333" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60D6C333" Ref="#PWR045"  Part="1" 
F 0 "#PWR045" H 10050 2600 50  0001 C CNN
F 1 "GND" H 10055 2677 50  0000 C CNN
F 2 "" H 10050 2850 50  0001 C CNN
F 3 "" H 10050 2850 50  0001 C CNN
	1    10050 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60D6C339
P 10050 2650
AR Path="/60D6C339" Ref="C?"  Part="1" 
AR Path="/60D5E44C/60D6C339" Ref="C14"  Part="1" 
F 0 "C14" H 10142 2696 50  0000 L CNN
F 1 "10n" H 10142 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 10050 2650 50  0001 C CNN
F 3 "~" H 10050 2650 50  0001 C CNN
	1    10050 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 1200 5500 1300
$Comp
L power:+BATT #PWR?
U 1 1 60D6C34F
P 1800 1250
AR Path="/60D6C34F" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60D6C34F" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 1800 1100 50  0001 C CNN
F 1 "+BATT" H 1815 1423 50  0000 C CNN
F 2 "" H 1800 1250 50  0001 C CNN
F 3 "" H 1800 1250 50  0001 C CNN
	1    1800 1250
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 60D6C355
P 5500 1200
AR Path="/60D6C355" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60D6C355" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 5500 1050 50  0001 C CNN
F 1 "+BATT" H 5515 1373 50  0000 C CNN
F 2 "" H 5500 1200 50  0001 C CNN
F 3 "" H 5500 1200 50  0001 C CNN
	1    5500 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 1250 9200 1400
Wire Wire Line
	5750 2000 5750 2100
$Comp
L Device:R_Small R?
U 1 1 60D6C36C
P 4900 1400
AR Path="/60D6C36C" Ref="R?"  Part="1" 
AR Path="/60D5E44C/60D6C36C" Ref="R9"  Part="1" 
F 0 "R9" H 4959 1446 50  0000 L CNN
F 1 "1k" H 4959 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4900 1400 50  0001 C CNN
F 3 "~" H 4900 1400 50  0001 C CNN
	1    4900 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60D6C372
P 4900 1750
AR Path="/60D6C372" Ref="R?"  Part="1" 
AR Path="/60D5E44C/60D6C372" Ref="R10"  Part="1" 
F 0 "R10" H 4959 1796 50  0000 L CNN
F 1 "10k" H 4959 1705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4900 1750 50  0001 C CNN
F 3 "~" H 4900 1750 50  0001 C CNN
	1    4900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1500 4900 1600
$Comp
L power:GND #PWR?
U 1 1 60D6C379
P 4900 1850
AR Path="/60D6C379" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60D6C379" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 4900 1600 50  0001 C CNN
F 1 "GND" H 4905 1677 50  0000 C CNN
F 2 "" H 4900 1850 50  0001 C CNN
F 3 "" H 4900 1850 50  0001 C CNN
	1    4900 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 1600 4900 1600
Connection ~ 4900 1600
Wire Wire Line
	4900 1600 4900 1650
$Comp
L Device:CP1_Small C?
U 1 1 60D6C383
P 4850 2650
AR Path="/60D6C383" Ref="C?"  Part="1" 
AR Path="/60D5E44C/60D6C383" Ref="C9"  Part="1" 
F 0 "C9" H 4941 2696 50  0000 L CNN
F 1 "22uF" H 4941 2605 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 4850 2650 50  0001 C CNN
F 3 "~" H 4850 2650 50  0001 C CNN
	1    4850 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D6C38A
P 4850 2800
AR Path="/60D6C38A" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60D6C38A" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 4850 2550 50  0001 C CNN
F 1 "GND" H 4855 2627 50  0000 C CNN
F 2 "" H 4850 2800 50  0001 C CNN
F 3 "" H 4850 2800 50  0001 C CNN
	1    4850 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2100 5750 2100
NoConn ~ 9800 1900
NoConn ~ 9800 2000
NoConn ~ 9800 2100
NoConn ~ 9800 2200
NoConn ~ 9800 2300
NoConn ~ 9800 2400
NoConn ~ 9800 2600
NoConn ~ 9800 2700
NoConn ~ 9800 2800
NoConn ~ 9800 2900
Wire Wire Line
	8300 1700 8300 1250
Wire Wire Line
	8300 1700 8400 1700
Wire Wire Line
	8300 1250 8700 1250
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 60DA4681
P 5950 1300
F 0 "JP1" H 5950 1505 50  0000 C CNN
F 1 "Vbat_bridge" H 5950 1414 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5950 1300 50  0001 C CNN
F 3 "~" H 5950 1300 50  0001 C CNN
	1    5950 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 1300 5500 1300
Connection ~ 5500 1300
Wire Wire Line
	5500 1300 5500 1400
Wire Wire Line
	6450 1300 6450 1200
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 60DC049F
P 1150 1500
F 0 "J2" H 1258 1681 50  0000 C CNN
F 1 "Power" H 1258 1590 50  0000 C CNN
F 2 "Battery:BatteryHolder_Keystone_1060_1x2032" H 1150 1500 50  0001 C CNN
F 3 "~" H 1150 1500 50  0001 C CNN
	1    1150 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1350 1650 1350
Wire Wire Line
	1500 1350 1500 1500
Wire Wire Line
	1500 1500 1350 1500
Wire Wire Line
	1800 1350 1800 1250
Wire Wire Line
	1350 1600 1500 1600
Wire Wire Line
	1500 1600 1500 1800
Wire Wire Line
	1500 1800 1800 1800
Wire Wire Line
	1800 1800 1800 1850
Wire Notes Line
	850  800  2500 800 
Wire Notes Line
	2500 800  2500 2300
Wire Notes Line
	2500 2300 850  2300
Wire Notes Line
	850  2300 850  800 
Text Notes 1750 2250 0    50   ~ 10
Battery Connector
Text Notes 3500 1150 0    50   ~ 10
Power muxer
Wire Notes Line
	7450 800  10750 800 
Wire Notes Line
	10750 800  10750 4000
Wire Notes Line
	10750 4000 7450 4000
Wire Notes Line
	7450 4000 7450 800 
Text Notes 7600 3950 0    50   ~ 10
USB <> UART
Text Notes 5750 1050 0    20   ~ 0
Populate this solder bridge to always\nconnect battery to +3V3 power net.\n(This is to be used only for testing)
$Comp
L Connector:USB_B_Micro J3
U 1 1 60C8255D
P 1600 4000
F 0 "J3" H 1657 4467 50  0000 C CNN
F 1 "USB_B_Micro" H 1657 4376 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex-105017-0001" H 1750 3950 50  0001 C CNN
F 3 "~" H 1750 3950 50  0001 C CNN
	1    1600 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 3650 2250 3800
$Comp
L power:GND #PWR?
U 1 1 60C86ACE
P 1600 4500
AR Path="/60C86ACE" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60C86ACE" Ref="#PWR023"  Part="1" 
F 0 "#PWR023" H 1600 4250 50  0001 C CNN
F 1 "GND" H 1605 4327 50  0000 C CNN
F 2 "" H 1600 4500 50  0001 C CNN
F 3 "" H 1600 4500 50  0001 C CNN
	1    1600 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 4500 1600 4400
Text Label 2250 4100 2    50   ~ 0
USB_DM
Text Label 2250 4000 2    50   ~ 0
USB_DP
Wire Wire Line
	1900 4000 2250 4000
Wire Wire Line
	1900 4100 2250 4100
$Comp
L Device:R_Small R?
U 1 1 60C8F24E
P 8050 2000
AR Path="/60C8F24E" Ref="R?"  Part="1" 
AR Path="/60D5E44C/60C8F24E" Ref="R12"  Part="1" 
F 0 "R12" H 8109 2046 50  0000 L CNN
F 1 "27" H 8109 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8050 2000 50  0001 C CNN
F 3 "~" H 8050 2000 50  0001 C CNN
	1    8050 2000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60C92F81
P 8050 2100
AR Path="/60C92F81" Ref="R?"  Part="1" 
AR Path="/60D5E44C/60C92F81" Ref="R13"  Part="1" 
F 0 "R13" H 8109 2146 50  0000 L CNN
F 1 "27" H 8109 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8050 2100 50  0001 C CNN
F 3 "~" H 8050 2100 50  0001 C CNN
	1    8050 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 2000 7750 2000
Wire Wire Line
	7950 2100 7900 2100
Wire Wire Line
	7650 2750 7650 2650
$Comp
L power:GND #PWR?
U 1 1 60C970EF
P 7650 2750
AR Path="/60C970EF" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60C970EF" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 7650 2500 50  0001 C CNN
F 1 "GND" H 7655 2577 50  0000 C CNN
F 2 "" H 7650 2750 50  0001 C CNN
F 3 "" H 7650 2750 50  0001 C CNN
	1    7650 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60C970F5
P 7650 2550
AR Path="/60C970F5" Ref="C?"  Part="1" 
AR Path="/60D5E44C/60C970F5" Ref="C11"  Part="1" 
F 0 "C11" H 7742 2596 50  0000 L CNN
F 1 "47p" H 7742 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7650 2550 50  0001 C CNN
F 3 "~" H 7650 2550 50  0001 C CNN
	1    7650 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 2750 7900 2650
$Comp
L power:GND #PWR?
U 1 1 60C98669
P 7900 2750
AR Path="/60C98669" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60C98669" Ref="#PWR040"  Part="1" 
F 0 "#PWR040" H 7900 2500 50  0001 C CNN
F 1 "GND" H 7905 2577 50  0000 C CNN
F 2 "" H 7900 2750 50  0001 C CNN
F 3 "" H 7900 2750 50  0001 C CNN
	1    7900 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60C9866F
P 7900 2550
AR Path="/60C9866F" Ref="C?"  Part="1" 
AR Path="/60D5E44C/60C9866F" Ref="C12"  Part="1" 
F 0 "C12" H 7992 2596 50  0000 L CNN
F 1 "47p" H 7992 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7900 2550 50  0001 C CNN
F 3 "~" H 7900 2550 50  0001 C CNN
	1    7900 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2200 7750 2200
Wire Wire Line
	7750 2200 7750 2000
Wire Wire Line
	7650 2200 7650 2450
Connection ~ 7750 2000
Wire Wire Line
	7750 2000 7550 2000
Wire Wire Line
	7900 2100 7900 2450
Connection ~ 7900 2100
Wire Wire Line
	7900 2100 7550 2100
$Comp
L power:VBUS #PWR026
U 1 1 60C9C23F
P 2250 3650
F 0 "#PWR026" H 2250 3500 50  0001 C CNN
F 1 "VBUS" H 2265 3823 50  0000 C CNN
F 2 "" H 2250 3650 50  0001 C CNN
F 3 "" H 2250 3650 50  0001 C CNN
	1    2250 3650
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR031
U 1 1 60C9D289
P 4900 1200
F 0 "#PWR031" H 4900 1050 50  0001 C CNN
F 1 "VBUS" H 4915 1373 50  0000 C CNN
F 2 "" H 4900 1200 50  0001 C CNN
F 3 "" H 4900 1200 50  0001 C CNN
	1    4900 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1200 4900 1300
$Comp
L power:VBUS #PWR042
U 1 1 60CA0544
P 9000 1100
F 0 "#PWR042" H 9000 950 50  0001 C CNN
F 1 "VBUS" H 9015 1273 50  0000 C CNN
F 2 "" H 9000 1100 50  0001 C CNN
F 3 "" H 9000 1100 50  0001 C CNN
	1    9000 1100
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-3.3 U4
U 1 1 60C9635E
P 4400 2450
F 0 "U4" H 4400 2692 50  0000 C CNN
F 1 "AMS1117-3.3" H 4400 2601 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4400 2650 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 4500 2200 50  0001 C CNN
	1    4400 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2450 3800 2450
Wire Wire Line
	4700 2450 4850 2450
$Comp
L Device:CP1_Small C?
U 1 1 60C9E935
P 3800 2650
AR Path="/60C9E935" Ref="C?"  Part="1" 
AR Path="/60D5E44C/60C9E935" Ref="C8"  Part="1" 
F 0 "C8" H 3891 2696 50  0000 L CNN
F 1 "10uF" H 3891 2605 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 3800 2650 50  0001 C CNN
F 3 "~" H 3800 2650 50  0001 C CNN
	1    3800 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2550 3800 2450
Connection ~ 3800 2450
Wire Wire Line
	3800 2450 3550 2450
$Comp
L power:GND #PWR?
U 1 1 60CA048B
P 3800 2800
AR Path="/60CA048B" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60CA048B" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 3800 2550 50  0001 C CNN
F 1 "GND" H 3805 2627 50  0000 C CNN
F 2 "" H 3800 2800 50  0001 C CNN
F 3 "" H 3800 2800 50  0001 C CNN
	1    3800 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2750 3800 2800
$Comp
L power:VBUS #PWR027
U 1 1 60CA1E12
P 3550 2450
F 0 "#PWR027" H 3550 2300 50  0001 C CNN
F 1 "VBUS" H 3565 2623 50  0000 C CNN
F 2 "" H 3550 2450 50  0001 C CNN
F 3 "" H 3550 2450 50  0001 C CNN
	1    3550 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2450 5500 2100
$Comp
L Device:D_Schottky D3
U 1 1 60CC2A39
P 5200 2450
F 0 "D3" H 5200 2233 50  0000 C CNN
F 1 "D_Schottky" H 5200 2324 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 5200 2450 50  0001 C CNN
F 3 "~" H 5200 2450 50  0001 C CNN
	1    5200 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	5350 2450 5500 2450
Wire Wire Line
	4400 2750 4400 2800
$Comp
L power:GND #PWR?
U 1 1 60C99C69
P 4400 2800
AR Path="/60C99C69" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60C99C69" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 4400 2550 50  0001 C CNN
F 1 "GND" H 4405 2627 50  0000 C CNN
F 2 "" H 4400 2800 50  0001 C CNN
F 3 "" H 4400 2800 50  0001 C CNN
	1    4400 2800
	1    0    0    -1  
$EndComp
Wire Notes Line
	3300 800  3300 3100
Wire Notes Line
	3300 3100 6650 3100
Wire Notes Line
	6650 3100 6650 800 
Wire Notes Line
	6650 800  3300 800 
$Comp
L Device:R_Small R?
U 1 1 60CB4B9B
P 5500 2650
AR Path="/60CB4B9B" Ref="R?"  Part="1" 
AR Path="/60D5E44C/60CB4B9B" Ref="R11"  Part="1" 
F 0 "R11" H 5559 2696 50  0000 L CNN
F 1 "10k" H 5559 2605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5500 2650 50  0001 C CNN
F 3 "~" H 5500 2650 50  0001 C CNN
	1    5500 2650
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60CB57D4
P 5500 2850
AR Path="/60CB57D4" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60CB57D4" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 5500 2600 50  0001 C CNN
F 1 "GND" H 5505 2677 50  0000 C CNN
F 2 "" H 5500 2850 50  0001 C CNN
F 3 "" H 5500 2850 50  0001 C CNN
	1    5500 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2750 5500 2850
Wire Wire Line
	5500 2550 5500 2450
Connection ~ 5500 2450
$Comp
L Device:D_Schottky D4
U 1 1 60CC256F
P 5500 1950
F 0 "D4" V 5500 2100 50  0000 C CNN
F 1 "D_Schottky" V 5400 2150 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 5500 1950 50  0001 C CNN
F 3 "~" H 5500 1950 50  0001 C CNN
	1    5500 1950
	0    -1   -1   0   
$EndComp
Connection ~ 5500 2100
Wire Wire Line
	4850 2750 4850 2800
Wire Wire Line
	4850 2550 4850 2450
Connection ~ 4850 2450
Wire Wire Line
	4850 2450 5050 2450
$Comp
L Device:CP1_Small C?
U 1 1 60CCEFE5
P 5750 2300
AR Path="/60CCEFE5" Ref="C?"  Part="1" 
AR Path="/60D5E44C/60CCEFE5" Ref="C10"  Part="1" 
F 0 "C10" H 5841 2346 50  0000 L CNN
F 1 "10uF" H 5841 2255 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 5750 2300 50  0001 C CNN
F 3 "~" H 5750 2300 50  0001 C CNN
	1    5750 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60CCFAE6
P 5750 2450
AR Path="/60CCFAE6" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60CCFAE6" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 5750 2200 50  0001 C CNN
F 1 "GND" H 5755 2277 50  0000 C CNN
F 2 "" H 5750 2450 50  0001 C CNN
F 3 "" H 5750 2450 50  0001 C CNN
	1    5750 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2400 5750 2450
Wire Wire Line
	5750 2200 5750 2100
Connection ~ 5750 2100
$Comp
L power:VDC #PWR036
U 1 1 60CD933F
P 5750 2000
F 0 "#PWR036" H 5750 1900 50  0001 C CNN
F 1 "VDC" H 5765 2173 50  0000 C CNN
F 2 "" H 5750 2000 50  0001 C CNN
F 3 "" H 5750 2000 50  0001 C CNN
	1    5750 2000
	1    0    0    -1  
$EndComp
$Comp
L power:VDC #PWR038
U 1 1 60CD9ED7
P 6450 1200
F 0 "#PWR038" H 6450 1100 50  0001 C CNN
F 1 "VDC" H 6465 1373 50  0000 C CNN
F 2 "" H 6450 1200 50  0001 C CNN
F 3 "" H 6450 1200 50  0001 C CNN
	1    6450 1200
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR044
U 1 1 60CDBC77
P 10050 2450
F 0 "#PWR044" H 10050 2300 50  0001 C CNN
F 1 "VBUS" H 10065 2623 50  0000 C CNN
F 2 "" H 10050 2450 50  0001 C CNN
F 3 "" H 10050 2450 50  0001 C CNN
	1    10050 2450
	1    0    0    -1  
$EndComp
Wire Notes Line
	1000 3150 2500 3150
Wire Notes Line
	2500 3150 2500 5000
Wire Notes Line
	2500 5000 1000 5000
Wire Notes Line
	1000 5000 1000 3150
Text Notes 1750 4900 0    50   ~ 10
USB Connector
Wire Wire Line
	7950 1450 7950 1350
$Comp
L power:GND #PWR?
U 1 1 60CC30AF
P 7950 1450
AR Path="/60CC30AF" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60CC30AF" Ref="#PWR041"  Part="1" 
F 0 "#PWR041" H 7950 1200 50  0001 C CNN
F 1 "GND" H 7955 1277 50  0000 C CNN
F 2 "" H 7950 1450 50  0001 C CNN
F 3 "" H 7950 1450 50  0001 C CNN
	1    7950 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60CC30B5
P 7950 1250
AR Path="/60CC30B5" Ref="C?"  Part="1" 
AR Path="/60D5E44C/60CC30B5" Ref="C13"  Part="1" 
F 0 "C13" H 8042 1296 50  0000 L CNN
F 1 "100n" H 8042 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 7950 1250 50  0001 C CNN
F 3 "~" H 7950 1250 50  0001 C CNN
	1    7950 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 1000 8700 1000
Wire Wire Line
	8700 1000 8700 1250
Wire Wire Line
	7950 1000 7950 1150
Connection ~ 8700 1250
Wire Wire Line
	8700 1250 9200 1250
$Comp
L Device:CP1_Small C?
U 1 1 60CC9B9E
P 10400 2650
AR Path="/60CC9B9E" Ref="C?"  Part="1" 
AR Path="/60D5E44C/60CC9B9E" Ref="C15"  Part="1" 
F 0 "C15" H 10491 2696 50  0000 L CNN
F 1 "4.7uF" H 10491 2605 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_4x5.7" H 10400 2650 50  0001 C CNN
F 3 "~" H 10400 2650 50  0001 C CNN
	1    10400 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 2450 10400 2450
Wire Wire Line
	10400 2450 10400 2550
Connection ~ 10050 2450
Wire Wire Line
	10400 2750 10400 2800
Wire Wire Line
	10400 2800 10050 2800
Connection ~ 10050 2800
Wire Wire Line
	10050 2800 10050 2750
Text HLabel 10200 1700 2    50   Input ~ 0
FTDI_TX
Text HLabel 10200 1800 2    50   Input ~ 0
FTDI_RX
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 60E2BEB6
P 1450 1100
F 0 "#FLG0102" H 1450 1175 50  0001 C CNN
F 1 "PWR_FLAG" H 1450 1273 50  0000 C CNN
F 2 "" H 1450 1100 50  0001 C CNN
F 3 "~" H 1450 1100 50  0001 C CNN
	1    1450 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1100 1450 1250
Wire Wire Line
	1450 1250 1650 1250
Wire Wire Line
	1650 1250 1650 1350
Connection ~ 1650 1350
Wire Wire Line
	1650 1350 1500 1350
Wire Wire Line
	1900 3800 2250 3800
NoConn ~ 1900 4200
$Comp
L Device:C_Small C?
U 1 1 60E38EEA
P 1250 4550
AR Path="/60E38EEA" Ref="C?"  Part="1" 
AR Path="/60D5E44C/60E38EEA" Ref="C16"  Part="1" 
F 0 "C16" H 1342 4596 50  0000 L CNN
F 1 "100n" H 1342 4505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 1250 4550 50  0001 C CNN
F 3 "~" H 1250 4550 50  0001 C CNN
	1    1250 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4400 1500 4450
Wire Wire Line
	1500 4450 1250 4450
$Comp
L power:GND #PWR?
U 1 1 60E3C0D0
P 1250 4700
AR Path="/60E3C0D0" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60E3C0D0" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 1250 4450 50  0001 C CNN
F 1 "GND" H 1255 4527 50  0000 C CNN
F 2 "" H 1250 4700 50  0001 C CNN
F 3 "" H 1250 4700 50  0001 C CNN
	1    1250 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 4650 1250 4700
$Comp
L power:VDC #PWR?
U 1 1 60CDD520
P 6500 2900
AR Path="/60E10242/60CDD520" Ref="#PWR?"  Part="1" 
AR Path="/60CDD520" Ref="#PWR?"  Part="1" 
AR Path="/60D5E44C/60CDD520" Ref="#PWR046"  Part="1" 
F 0 "#PWR046" H 6500 2800 50  0001 C CNN
F 1 "VDC" H 6515 3073 50  0000 C CNN
F 2 "" H 6500 2900 50  0001 C CNN
F 3 "" H 6500 2900 50  0001 C CNN
	1    6500 2900
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 60CDD526
P 6200 2900
F 0 "#FLG01" H 6200 2975 50  0001 C CNN
F 1 "PWR_FLAG" H 6200 3073 50  0000 C CNN
F 2 "" H 6200 2900 50  0001 C CNN
F 3 "~" H 6200 2900 50  0001 C CNN
	1    6200 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2900 6200 3000
Wire Wire Line
	6200 3000 6500 3000
Wire Wire Line
	6500 3000 6500 2900
$Comp
L Device:Q_PMOS_GSD Q1
U 1 1 60D8512E
P 5400 1600
F 0 "Q1" H 5605 1554 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 5605 1645 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5600 1700 50  0001 C CNN
F 3 "~" H 5400 1600 50  0001 C CNN
	1    5400 1600
	1    0    0    1   
$EndComp
Wire Wire Line
	6100 1300 6450 1300
$EndSCHEMATC
