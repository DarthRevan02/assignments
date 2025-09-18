import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os

# Available algorithms
available_algorithms = {
    1: ('Heap Sort', 'C:\\Users\\Aadi Jain\\Desktop\\Assignments for DAA\\Csv files\\ANALYSIS_Heap.csv'),
    2: ('Shell Sort', 'C:\\Users\\Aadi Jain\\Desktop\\Assignments for DAA\\Csv files\\ANALYSIS_Shell.csv'),
    3: ('Quick Sort (Recursive)', 'C:\\Users\\Aadi Jain\\Desktop\\Assignments for DAA\\Csv files\\ANALYSIS_QuickRecursive.csv'),
    4: ('Quick Sort (Iterative)', 'C:\\Users\\Aadi Jain\\Desktop\\Assignments for DAA\\Csv files\\ANALYSIS_QuickIterative.csv'),
    5: ('Bubble Sort', 'C:\\Users\\Aadi Jain\\Desktop\\Assignments for DAA\\Csv files\\ANALYSIS_Bubble.csv'),
    6: ('Insert Sort', 'C:\\Users\\Aadi Jain\\Desktop\\Assignments for DAA\\Csv files\\ANALYSIS_Insert.csv'),
    7: ('Select Sort', 'C:\\Users\\Aadi Jain\\Desktop\\Assignments for DAA\\Csv files\\ANALYSIS_Select.csv')
}

print("=== Sorting Algorithm Performance Analyzer ===")
print("\nAvailable Sorting Algorithms:")
print("-" * 45)
for num, (name, _) in available_algorithms.items():
    print(f"{num}. {name}")

print("\nChoose algorithms to compare:")
print("- Enter numbers separated by spaces (e.g., '1 2 3' for Heap, Shell, Quick Recursive)")
print("- Enter 'all' to compare all algorithms")
print("- Enter 'fast' to compare only efficient algorithms (Heap, Shell, Quick)")
print("- Enter 'slow' to compare slower algorithms (Bubble, Insert, Select)")

user_input = input("\nYour choice: ").strip().lower()

# Process user input
selected_algorithms = {}

if user_input == 'all':
    selected_algorithms = {name: path for name, path in available_algorithms.values()}
elif user_input == 'fast':
    selected_algorithms = {
        'Heap Sort': available_algorithms[1][1],
        'Shell Sort': available_algorithms[2][1],
        'Quick Sort (Recursive)': available_algorithms[3][1],
        'Quick Sort (Iterative)': available_algorithms[4][1]
    }
elif user_input == 'slow':
    selected_algorithms = {
        'Bubble Sort': available_algorithms[5][1],
        'Insert Sort': available_algorithms[6][1],
        'Select Sort': available_algorithms[7][1]
    }
else:
    try:
        numbers = [int(x.strip()) for x in user_input.split()]
        for num in numbers:
            if num in available_algorithms:
                name, path = available_algorithms[num]
                selected_algorithms[name] = path
            else:
                print(f"Warning: Invalid choice {num} ignored.")
    except ValueError:
        print("Invalid input format. Using default: Heap, Shell, Quick Recursive")
        selected_algorithms = {
            'Heap Sort': available_algorithms[1][1],
            'Shell Sort': available_algorithms[2][1],
            'Quick Sort (Recursive)': available_algorithms[3][1]
        }

if not selected_algorithms:
    print("No valid algorithms selected. Exiting.")
    exit()

# Professional color scheme (will be assigned dynamically)
color_palette = ['#E74C3C', '#3498DB', '#2ECC71', '#9B59B6', '#F39C12', '#E67E22', '#1ABC9C']
line_style_palette = ['-', '--', '-.', ':', '-', '--', '-.']
marker_palette = ['o', 's', '^', 'v', 'D', 'p', 'h']

# Assign colors, styles, and markers to selected algorithms
colors = {}
line_styles = {}
markers = {}

for i, name in enumerate(selected_algorithms.keys()):
    colors[name] = color_palette[i % len(color_palette)]
    line_styles[name] = line_style_palette[i % len(line_style_palette)]
    markers[name] = marker_palette[i % len(marker_palette)]

# Create the figure with high quality
plt.figure(figsize=(12, 8))
plt.style.use('seaborn-v0_8-whitegrid')  # Professional style

print(f"\n=== Generating graph for: {', '.join(selected_algorithms.keys())} ===")
print("-" * 60)

# Plot each selected algorithm
for name, filename in selected_algorithms.items():
    if os.path.exists(filename):
        df = pd.read_csv(filename)
        
        # Plot the main line with logarithmic data
        plt.loglog(df['SizeOfArray'], df['AvgTime'], 
                color=colors[name], 
                linestyle=line_styles[name],
                marker=markers[name], 
                linewidth=2.5, 
                markersize=6, 
                label=name,
                alpha=0.9,
                markerfacecolor='white',
                markeredgewidth=2,
                markeredgecolor=colors[name])
        
        # Add error bars (optional - comment out if too cluttered)
        plt.errorbar(df['SizeOfArray'], df['AvgTime'], 
                    yerr=df['SDtime'], 
                    color=colors[name], 
                    alpha=0.3, 
                    capsize=3,
                    fmt='none')
        
        print(f"✓ {name}: {len(df)} data points loaded")
        print(f"  Time range: {df['AvgTime'].min():.2e} to {df['AvgTime'].max():.2e} seconds")
    else:
        print(f"✗ File not found: {filename}")

print("-" * 50)

# Customize the graph
plt.xlabel('Array Size (logarithmic scale)', fontsize=14, fontweight='bold')
plt.ylabel('Average Execution Time (seconds, logarithmic scale)', fontsize=14, fontweight='bold')
plt.title(f'Performance Comparison: {", ".join(selected_algorithms.keys())}\nExecution Time vs Array Size (Log-Log Scale)', 
        fontsize=16, fontweight='bold', pad=20)

# Customize grid
plt.grid(True, which='major', alpha=0.6, linestyle='-', linewidth=0.8)
plt.grid(True, which='minor', alpha=0.3, linestyle=':', linewidth=0.5)

# Add legend with better positioning and algorithm names
plt.legend(fontsize=12, loc='upper left', frameon=True, 
        fancybox=True, shadow=True, framealpha=0.9,
        title='Sorting Algorithms', title_fontsize=13)

# Add algorithm names directly on the graph lines (annotations)
for name, filename in selected_algorithms.items():
    if os.path.exists(filename):
        df = pd.read_csv(filename)
        # Find a good position to place the algorithm name (around middle of the data)
        mid_index = len(df) // 2
        if mid_index < len(df):
            x_pos = df['SizeOfArray'].iloc[mid_index]
            y_pos = df['AvgTime'].iloc[mid_index]
            
            # Add text annotation with algorithm name
            plt.annotate(name, 
                        xy=(x_pos, y_pos), 
                        xytext=(10, 10), 
                        textcoords='offset points',
                        fontsize=10, 
                        fontweight='bold',
                        color=colors[name],
                        bbox=dict(boxstyle='round,pad=0.3', 
                                facecolor='white', 
                                edgecolor=colors[name], 
                                alpha=0.8),
                        arrowprops=dict(arrowstyle='->', 
                                    color=colors[name], 
                                    alpha=0.7))

# Set axis limits for better visibility (optional)
# plt.xlim(1, 300000)
# plt.ylim(1e-8, 1)

# Add logarithmic scale confirmation and algorithm count
plt.text(0.02, 0.98, f'LOG-LOG SCALE\n✓ X-axis: Logarithmic\n✓ Y-axis: Logarithmic\n\n📊 Algorithms: {len(selected_algorithms)}', 
        transform=plt.gca().transAxes, 
        fontsize=10, verticalalignment='top', 
        bbox=dict(boxstyle='round', facecolor='lightblue', alpha=0.7),
        fontweight='bold')

# Improve layout
plt.tight_layout()

# Display the graph
plt.show()

# Optional: Save the graph in high quality
# plt.savefig('heap_shell_quick_comparison.png', dpi=300, bbox_inches='tight', 
#             facecolor='white', edgecolor='none')

print("\n🔍 LOGARITHMIC GRAPH FEATURES:")
print("✓ X-axis (Array Size): Logarithmic scale")
print("✓ Y-axis (Execution Time): Logarithmic scale") 
print("✓ Both major and minor grid lines for precision")
print("✓ Algorithm names displayed in legend AND on graph lines")
print("✓ Color-coded annotations with arrows pointing to each line")
print("✓ Log-log plot shows algorithmic complexity trends")
print("\n📊 WHAT TO LOOK FOR:")
print("• Straight lines = consistent time complexity")
print("• Steeper slopes = higher time complexity") 
print("• Quick Sort should show lowest values (best performance)")
print("• Shell Sort should be middle performance")
print("• Heap Sort should show consistent O(n log n) behavior")
print("-" * 60)