
ss_res = np.sum((y - y_fit) ** 2)
ss_tot = np.sum((y - np.mean(y)) ** 2)
r2 = 1 - (ss_res / ss_tot)

print(f"Quadratic fit coefficients:")
print(f"a = {a:.6e}")
print(f"b = {b:.6e}")
print(f"c = {c:.6e}")
print(f"R^2 = {r2:.6f}")

# Display the equation and R^2 on the plot
eqn = f"y = {a:.2e}x² + {b:.2e}x + {c:.2e}\n$R^2$ = {r2:.4f}"
plt.text(0.05, 0.95, eqn, transform=plt.gca().transAxes, fontsize=10, verticalalignment='top', bbox=dict(facecolor='white', alpha=0.7))

plt.xlabel('Size of Array')
plt.ylabel('Time (seconds)')
plt.title('Selection Sort: Array Size vs Time with Quadratic Fit')
plt.xscale('linear')
plt.legend()
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.tight_layout()
plt.show()
