# Changes required in V2

## PCBA

### Shall be able to go into the lowest power mode.

The version 1 PCBA does not make use of the wake up pins. Therefore, it is not possible to go to the lowest
power mode. That impacts the battery lifetime.

### Shall be able to detect low battery voltage
### Shall be able to log battery voltage

Need to route the ADC lines to power line

### Shall be able to easily measure current

Need to have some test points and zero ohm resistors

### Shall be able to wake-up/detect when the device gets connected to USB

Need to use the FTDI chip to generate some indication

### Re-evaluate the power circuitry to check whether it can be simplified

Can we use two diodes to feed current

### Don't use SMD LEDs

Use a LED that can retain brightness over the full range.

## Mechanical

### Shall implement the product enclosure with LEDs



# Product limitations
