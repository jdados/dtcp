import numpy as np
import csv
from datetime import datetime
import matplotlib.pyplot as plt

sampling_rate = 10e3  # 10 kHz sampling rate
duration = 10e-3  # 10 ms total duration
num_samples = int(sampling_rate * duration)
time = np.arange(num_samples) / sampling_rate
voltage = np.zeros_like(time)

spike_start = 1e-3  # 1 ms
spike_duration = 0.5e-3  # 0.5 ms
spike_end = spike_start + spike_duration
spike_mask = (time >= spike_start) & (time < spike_end)
voltage[spike_mask] = 2.0

emg_start = 2.5e-3
emg_start_idx = int(emg_start * sampling_rate)
emg_duration = 10e-3
emg_samples = int(emg_duration * sampling_rate)

# create EMG waveform
emg_time = np.arange(emg_samples) / sampling_rate
dip_time = 1e-3
spike_time = 4e-3
dip = -2e-3 * np.exp(-((emg_time - dip_time)**2) / (0.5e-3)**2)
spike = 2e-3 * np.exp(-((emg_time - spike_time)**2) / (0.8e-3)**2)

emg = dip + spike

if emg_start_idx + emg_samples <= len(voltage):
    voltage[emg_start_idx:emg_start_idx + emg_samples] += emg
else:
    available_samples = len(voltage) - emg_start_idx
    voltage[emg_start_idx:] += emg[:available_samples]

# write csv
output_filename = "emg_artifact_waveform.csv"
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
ax1.grid(True, alpha=0.3)
ax1.axhline(y=0, color='k', linestyle='-', linewidth=0.5)

# zoomed in
emg_zoom_start = emg_start * 1e3 - 1  # 1 ms before EMG
emg_zoom_end = emg_start * 1e3 + 8    # 8 ms after EMG start
zoom_mask = (time * 1e3 >= emg_zoom_start) & (time * 1e3 <= emg_zoom_end)
ax2.plot(time[zoom_mask] * 1e3, voltage[zoom_mask] * 1e3, 'r-', linewidth=1.5)
ax2.set_xlabel('Time (ms)')
ax2.set_ylabel('Voltage (mV)')
ax2.set_title('EMG Response (Zoomed)')
ax2.grid(True, alpha=0.3)
ax2.axhline(y=0, color='k', linestyle='-', linewidth=0.5)

plt.tight_layout()
plt.show()