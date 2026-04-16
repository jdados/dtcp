# CpE Design: DTCP Project Repository

## Overview

![Prototype 2 3D render](./notes/system%20design/PCB_AltiumModel2.png)

This repository presents the files associated with the design of a wireless neurostimulation platform powered through **Differential Tissue Coupled Powering (DTCP)**.  
The system transmits high-frequency (~20 – 25 MHz) differential signals through needle electrodes to power and communicate with implanted devices, while simultaneously recording **EMG (Electromyography)** activity for research.

![Prototype 2 System Architecture](./notes/system%20design/System_Architecture.png)

The project integrates four key subsystems:

1. **RF Signal Generation** – AD9850 DDS digitally tunes the HF output frequency.  
2. **Power Amplification** – 2 PAs in series deliver ≥ 1 W (≈ 30–35 dBm). Adjustable power through the help of a potentiometer and LED is included to make tuning power in surgery easier. It will light up when EMG signal is detected. 
3. **Signal Acquisition** – ADS1299 AFE captures and amplifies EMG signals.  
4. **Control & Interface** – MSPM0C1104 microcontroller manages DDS control, AFE sampling, and power switching.

## Project Plan

### **First Prototype**

The first prototype aims to realize the most basic functionality: a 25 MHz differential output at 1 W.

| Task | Finish By | Leader | Supporters | Comments | Status |
|------|------------|---------|-------------|-----------|---------|
| Design the PA circuit | End of October 2025 | Luis Wong | Jeremiah Dados |  | ✔️ |
| Design the EMG circuit | End of October 2025 | Dmytro Stavskyi | Jeremiah Dados |  | ✔️ |
| Design the first prototype PCB in Altium | Mid-November 2025 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi |  | ✔️ |
| Place the fabrication order | Mid-November 2025 | Jeremiah Dados | Han Wu |  | ✔️ |
| Receive the board and assemble it | End of November 2025 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi |  | ✔️ |
| Validate board outputs on lab equipment | Mid-December 2025 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi | Present functional prototype at end of semester | ✔️ |
| Validate board functionality in animal experiments | End of January 2026 | Han Wu | Jeremiah Dados, Luis Wong, Dmytro Stavskyi | Work resumes 2nd week of January after winter break | 🟡 |

---

### **Second Prototype**

The second prototype addresses issues found in the first design and focuses on improving compactness, flexibility, and performance.

| Task | Finish By | Leader | Supporters | Comments | Status |
|------|------------|---------|-------------|-----------|---------|
| Revisions to the circuit design | Mid-February 2026 | Luis Wong, Dmytro Stavskyi | Jeremiah Dados |  | ✔️ |
| Design and order the PCB | End of February 2026 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi |  | ✔️ |
| Place the fabrication order | End of February 2026 | Jeremiah Dados | Han Wu |  | ✔️ |
| Receive the board and assemble it | Mid-March 2026 | Luis Wong, Dmytro Stavskyi | Jeremiah Dados |  | ✔️ |
| Validate board outputs on lab equipment | End of March 2026 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi |  | ✔️ |
| Validate board functionality in animal experiments | End of April 2026 | Han Wu | Jeremiah Dados, Luis Wong, Dmytro Stavskyi |  | 🟡 |

## Bugs

### Firmware

- `printf` is apparently too large to fit into the MCU, and debugging is harder without console printing
  - look for smaller alternative, UART cannot be used as it is utilized for EMG plotting through SerialPlot.
- Not yet sure if it causes or will cause problems, but the serial clock starts at high and remains high until the first transaction, even though it should be low when not transmitting or receiving data (and hence should start with low)
  - It has not seemed to though.
- Fluctuating offset, possibly due to noise from main, makes EMG detection algorithm non-trivial.

### Hardware

#### EMG Circuit

- Class A PA is part of the second prototype and maxes out at 31 dBm meeting our target, but when we connect the SMA connector while also recording EMG we seem to face some interference or noise. Perhaps it's due to improper grounding?
- New PCB seems to have introduce more noise causing the EMG + Stimulation signal to be less clean.
  - Something might be shorted.

#### Class E PA

- Due to low Q of inductors the power efficiency we see in simulations is ~30% instead of the >50% we wish for and expect.
- Impedance matching network of Class-E PA might be unoptimized introducing unwanted reactance at output.
- Initial testing shows an extremely weak output signal at -45 dBm.
- Fixing drain inductance yields a power output of 7.26 dBm which is short of the 30dBm target.
- Simulations of the current setup on the physical board show the gain is below what we expected since the gate charge is too high requiring the power at input to be 0.704 W when we are aiming for a 1W output.
  - The current transistor is insufficient for our purposes as it's gate charge is too high to be efficient for amplification to 1W.
- We have elected to drop this design.

## Links

Some files may require UF sign-in:

- [Time Tracking Log](https://docs.google.com/spreadsheets/d/18YieW_wAob6iDCQWRSr79hOXjbCugq7RjKLDexqUogo/edit?gid=0#gid=0)

- [Design Draft](https://docs.google.com/document/d/1d00vnsQUVDlf2uW5-OWDDMQm1jWjiy-7jFtAZofUm3A/edit?tab=t.0)

- [Pre-Alpha Build](https://docs.google.com/document/d/1ijc-FFz9Bt2qVDn8euLwuQjNTMDzeiQRgQFuhg-fLZ0/edit?tab=t.0)

- [Design Prototype](https://docs.google.com/document/d/1iM8SsOxejECSPiFp-hwhw81iVYtYDDtyBoNlvvrWGng/edit?usp=sharing)
