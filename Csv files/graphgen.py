import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Read the CSV file
# Replace 'your_file.csv' with the actual filename
csv_file = 'C:\\Users\\Aadi Jain\\Desktop\\Assignments for DAA\\Csv files\\ANALYSIS_Bubble.csv'  # Change this to your actual CSV filename

print("Loading required packages...")
print("If you get import errors, install packages with:")
print("pip install matplotlib pandas numpy")
print("-" * 50)
df = pd.read_csv(csv_file)

# Create the line graph
plt.figure(figsize=(12, 8))

# Plot execution time vs array size
plt.plot(df['SizeOfArray'], df['AvgTime'], 
        marker='o', linewidth=2, markersize=6, 
        color='blue', label='Average Execution Time')

# Add error bars for standard deviation
plt.errorbar(df['SizeOfArray'], df['AvgTime'], 
            yerr=df['SDtime'], fmt='o', 
            color='blue', alpha=0.5, capsize=3)

# Customize the graph
plt.xlabel('Array Size', fontsize=12, fontweight='bold')
plt.ylabel('Execution Time (seconds)', fontsize=12, fontweight='bold')
plt.title('Sorting Algorithm Performance: Execution Time vs Array Size', 
        fontsize=14, fontweight='bold')

# Set logarithmic scale for better visualization (optional)
plt.xscale('log')
plt.yscale('log')

# Add grid for better readability
plt.grid(True, alpha=0.3)

# Add legend
plt.legend(fontsize=10)

# Improve layout
plt.tight_layout()

# Display the graph
plt.show()

# Optional: Save the graph
# plt.savefig('sorting_performance.png', dpi=300, bbox_inches='tight')

print("Graph generated successfully!")
print(f"Data points: {len(df)} array sizes")
print(f"Array size range: {df['SizeOfArray'].min()} to {df['SizeOfArray'].max()}")
print(f"Time range: {df['AvgTime'].min():.2e} to {df['AvgTime'].max():.2e} seconds")