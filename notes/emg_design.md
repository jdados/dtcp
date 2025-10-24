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
	- frequency range: 0 - 500 Hz
	- amplitude range: 0 - 10 mV
	- usual amplification is in the hundreds

- ADS1299 specs:
	- 7.5 electrical characteristics (explain everything: importance of input capacitance, etc.)
	- e.g., if amplitude of EMG is 1 mV, then we need minimum of 16 bit ADC
- SPI: 
	- can fully setup and control the device with SPI (commands include: WAKEUP, STANDBY, START, STOP)
- PGA:
	- gain of up to 24x
- filtering: 
	- external band-pass of 500 Hz and low-pass filters
- ADC: 
	- resolution: 24 bits (assuming reference of 4.5 V, (4.5 V / 2^24^) = 0.268 μV)
	- sampling (data) rate: from 250 SPS to 16 kSPS (~1000 SPS is good?)

- papers using ADS1299:
	- [Development of an 8 channel sEMG wireless device based on ADS1299 with Virtual Instrumentation](https://arxiv.org/abs/1808.03711)
	- [Analog front-ends comparison in the way of a portable, low-power and low-cost EMG controller based on pattern recognition](https://ieeexplore.ieee.org/abstract/document/7318805)
	- [Data acquisition system of 16-channel EEG based on ATSAM3X8E ARM Cortex-M3 32-bit microcontroller and ADS1299 ](https://pubs.aip.org/aip/acp/article/1862/1/030149/649943/Data-acquisition-system-of-16-channel-EEG-based-on)

# Pre-alpha build

- schematic (altium):

- electrodes:
	- how electrodes work (drawings)
	- refer to some paper

- every connection needs to be able to be debugged
- MCU needs to have a launchpad (for debugging; launchpad contains a debugger chip and the chip identical to one used in PCB)
