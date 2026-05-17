import random
import numpy as np
import matplotlib.pyplot as plt
total_points = 10000
inside_square = 0

inside_x = []
inside_y = []
outside_x = []
outside_y = []

for i in range(total_points):
    x = random.uniform(-1, 1)
    y = random.uniform(-1, 1)
    if abs(x) + abs(y) <= 1:
        inside_square += 1
        inside_x.append(x)
        inside_y.append(y)
    else:
        outside_x.append(x)
        outside_y.append(y)
estimated_ratio = inside_square / total_points
actual_ratio = 2 / 4
print("Total Points =", total_points)
print("Points Inside Rotated Square =", inside_square)
print("Estimated Ratio =", estimated_ratio)
print("Actual Ratio =", actual_ratio)
inner_sq_x = [1, 0, -1, 0, 1]
inner_sq_y = [0, 1, 0, -1, 0]
plt.plot(inner_sq_x, inner_sq_y, label="Rotated Inner Square", color="red")

outer_sq_x = [-1, 1, 1, -1, -1]
outer_sq_y = [-1, -1, 1, 1, -1]
plt.plot(outer_sq_x, outer_sq_y, label="Outer Square", color="black")
plt.scatter(inside_x, inside_y, s=5, label="Inside Rotated Square", color="green")
plt.scatter(outside_x, outside_y, s=5, label="Outside Rotated Square", color="blue")
plt.axis("equal")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.title("Monte Carlo Simulation: Rotated Inner Square")
plt.grid(True)
plt.legend()
plt.show()
