# Design 1 DTCP Project Repository

## Overview

This repository presents the files associated with the design of a wireless neurostimulation platform powered through **Differential Tissue Coupled Powering (DTCP)**.  
The system transmits high-frequency (~20 – 25 MHz) differential signals through epidermal electrodes to power and communicate with implanted devices, while simultaneously recording **EMG (Electromyography)** activity for research.

The project integrates four key subsystems:

1. **RF Signal Generation** – AD9850 DDS digitally tunes the HF output frequency.  
2. **Power Amplification** – A Class-E PA delivers ≥ 1 W (≈ 30–35 dBm) efficiently.  
3. **Signal Acquisition** – ADS1299 AFE captures and amplifies EMG signals.  
4. **Control & Interface** – MSPM0C1104 microcontroller manages DDS control, AFE sampling, and power switching.

## Project Plan

### **First Prototype**

The first prototype aims to realize the most basic functionality: a 25 MHz differential output at 1 W.

| Task | Finish By | Leader | Supporters | Comments | Status |
|------|------------|---------|-------------|-----------|---------|
| Design the PA circuit | End of October 2025 | Luis Wong | Jeremiah Dados |  | [x] |
| Design the EMG circuit | End of October 2025 | Dmytro Stavskyi | Jeremiah Dados |  | [x] |
| Design the first prototype PCB in Altium | Mid-November 2025 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi |  | [ ] |
| Place the fabrication order | Mid-November 2025 | Jeremiah Dados | Han Wu |  | [ ] |
| Receive the board and assemble it | End of November 2025 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi |  | [ ] |
| Validate board outputs on lab equipment | Mid-December 2025 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi | Present functional prototype at end of semester | [ ] |
| Validate board functionality in animal experiments | End of January 2026 | Han Wu | Jeremiah Dados, Luis Wong, Dmytro Stavskyi | Work resumes 2nd week of January after winter break | [ ] |

---

### **Second Prototype**

The second prototype addresses issues found in the first design and focuses on improving compactness, flexibility, and performance.

| Task | Finish By | Leader | Supporters | Comments | Status |
|------|------------|---------|-------------|-----------|---------|
| Revisions to the circuit design | Mid-February 2026 | Luis Wong, Dmytro Stavskyi | Jeremiah Dados |  | [ ] |
| Design and order the PCB | End of February 2026 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi |  | [ ] |
| Place the fabrication order | End of February 2026 | Jeremiah Dados | Han Wu |  | [ ] |
| Receive the board and assemble it | Mid-March 2026 | Luis Wong, Dmytro Stavskyi | Jeremiah Dados |  | [ ] |
| Validate board outputs on lab equipment | End of March 2026 | Jeremiah Dados | Luis Wong, Dmytro Stavskyi |  | [ ] |
| Validate board functionality in animal experiments | End of April 2026 | Han Wu | Jeremiah Dados, Luis Wong, Dmytro Stavskyi |  | [ ] |

## Links

- [Time tracking log](https://docs.google.com/spreadsheets/d/18YieW_wAob6iDCQWRSr79hOXjbCugq7RjKLDexqUogo/edit?gid=0#gid=0)

- [Design draft](https://docs.google.com/document/d/1d00vnsQUVDlf2uW5-OWDDMQm1jWjiy-7jFtAZofUm3A/edit?tab=t.0)

- [Pre-alpha build](https://docs.google.com/document/d/1ijc-FFz9Bt2qVDn8euLwuQjNTMDzeiQRgQFuhg-fLZ0/edit?tab=t.0)
