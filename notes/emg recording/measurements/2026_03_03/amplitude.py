import pandas as pd
import numpy as np

def calculate_amplitude_from_csv(file_path, column_name):
    """
    Reads a CSV file, extracts data from a specified column, and calculates the amplitude.

    Amplitude is defined as (Max Value - Min Value) / 2.
    
    Args:
        file_path (str): The path to the CSV file.
        column_name (str): The name of the column containing the data (e.g., 'Amplitude').

    Returns:
        float: The calculated amplitude.
    """
    try:
        # Read the CSV file into a pandas DataFrame
        df = pd.read_csv(file_path)
        
        # Ensure the column exists
        if column_name not in df.columns:
            print(f"Error: Column '{column_name}' not found in the CSV file.")
            return None

        # Extract the data as a numpy array, converting to numeric and handling potential errors
        data = pd.to_numeric(df[column_name], errors='coerce').dropna().values
        
        if len(data) == 0:
            print(f"Error: No numeric data found in column '{column_name}'.")
            return None

        # Calculate the amplitude
        max_value = np.max(data)
        min_value = np.min(data)
        amplitude = (max_value - min_value) / 2.0

        return amplitude

    except FileNotFoundError:
        print(f"Error: The file '{file_path}' was not found.")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

# --- Example Usage ---
# Assume you have a CSV file named 'sensor_data.csv' with a column named 'Signal_Value'

# 1. Create a dummy CSV file for testing (optional)
# data = {'Time': range(10), 'Signal_Value': np.sin(np.linspace(0, 2*np.pi, 10)) * 50 + 100}
# df_dummy = pd.DataFrame(data)
# df_dummy.to_csv('sensor_data.csv', index=False)

# 2. Call the function with your file path and column name
file_name = 'setup_3/Setup 3, 2.5Vpp 100 Hz sine signal.csv'
column_to_analyze = 'Voltage (mV)'
result_amplitude = calculate_amplitude_from_csv(file_name, column_to_analyze)

if result_amplitude is not None:
    print(f"The calculated amplitude of the signal is: {result_amplitude}")


