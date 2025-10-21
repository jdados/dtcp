# General

- ports (connections):
	- ground
	- vdd
	- channel
	- SPI

- components:
	- amplifiers (?)
	- filters (?)

- chip: ADS1299
	- not a microcontroller (external programming using SPI)
	- SPI interface
	- provides amplification
	- can provide low-pass filtering
- use the MCU of the design, MSPM0C1104, to program the ADS1299

- EMG signal characteristics:
	- how its done usually, frequency, amplitude
	- frequency range: 0 - 500 Hz
	- amplitude range: 0 - 10 mV

- ADS1299 specs:
	- 7.5 electrical characteristics (explain everything: importance of input capacitance, etc.)
	- e.g., if amplitude of EMG is 1 mV, then we need minimum of 16 bit ADC
	- SPI characterstics

- papers using ADS1299:

# Pre-alpha build

- schematic (altium):
	- not enough pins for the MCU (research another MCU of other type; Cortex M0+)

- electrodes:
	- how electrodes work (drawings)
	- refer to some paper

- every connection needs to be able to be debugged
- MCU needs to have a launchpad (for debugging; launchpad contains a debugger chip and the chip identical to one used in PCB)
