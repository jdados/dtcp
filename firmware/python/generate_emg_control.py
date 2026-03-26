import numpy as np
import csv
from datetime import datetime
import matplotlib.pyplot as plt

sampling_rate = 100e3  # 100 kHz sampling rate
duration = 1.0  # 1 second total duration
num_samples = int(sampling_rate * duration)
time = np.arange(num_samples) / sampling_rate
voltage = np.zeros_like(time)

# Initial spike only (no EMG)
spike_start = 1e-3  # 1 ms
spike_duration = 0.5e-3  # 0.5 ms
spike_end = spike_start + spike_duration
spike_mask = (time >= spike_start) & (time < spike_end)
voltage[spike_mask] = 2.0

# write csv
output_filename = "emg_control_waveform.csv"
with open(output_filename, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['Time (s)', 'Voltage (V)'])
    for t, v in zip(time, voltage):
        writer.writerow([f'{t:.9e}', f'{v:.9e}'])

# plot waveform
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))

# full waveform plot
ax1.plot(time * 1e3, voltage, 'b-', linewidth=1)
ax1.set_xlabel('Time (ms)')
ax1.set_ylabel('Voltage (V)')
ax1.set_title('Control Waveform - Initial Spike Only')
ax1.grid(True, alpha=0.3)
ax1.axhline(y=0, color='k', linestyle='-', linewidth=0.5)

# zoomed in on spike
spike_zoom_start = spike_start * 1e3 - 0.5
spike_zoom_end = spike_end * 1e3 + 0.5
zoom_mask = (time * 1e3 >= spike_zoom_start) & (time * 1e3 <= spike_zoom_end)
ax2.plot(time[zoom_mask] * 1e3, voltage[zoom_mask], 'r-', linewidth=1.5)
ax2.set_xlabel('Time (ms)')
ax2.set_ylabel('Voltage (V)')
ax2.set_title('Initial Spike (Zoomed)')
ax2.grid(True, alpha=0.3)
ax2.axhline(y=0, color='k', linestyle='-', linewidth=0.5)

plt.tight_layout()
plt.show()
