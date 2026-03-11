import csv
import pandas as pd

# Read the CSV file (replace 'data.csv' with your file path)
df = pd.read_csv('data.csv')

# Calculate column averages
column_averages = df.mean()

# Display the results
print("Average for each column:")
print(column_averages)
