import matplotlib.pyplot as plt
import numpy as np

np.random.seed(42)

s_vals = [20, 40, 60]
S_vals = [40, 60, 80, 100]
policy_grid = [(x, y) for x in s_vals for y in S_vals if x < y]

setup_cost = 32
item_cost = 3
hold_cost = 1
backlog_cost = 5
months = 120
start_inv = 60
freq_per_month = 6
sim_days = months * 30
step_demand = 30 // freq_per_month

total_demands = freq_per_month * months
rng_demands = np.random.randint(5, 15, size=total_demands)


def visualize_sim(lower, upper, arr, cst):
    x_axis = range(1, sim_days + 1)
    plt.figure(figsize=(12, 6))
    plt.plot(x_axis, arr, color="navy", linewidth=1, label="Stock")
    plt.axhline(lower, color="darkorange", linestyle="-.", label=f"s = {lower}")
    plt.axhline(upper, color="forestgreen", linestyle="-.", label=f"S = {upper}")
    plt.axhline(0, color="crimson", linestyle="-", linewidth=1, label="Out of Stock")
    plt.xlabel("Days")
    plt.ylabel("Stock Units")
    plt.title(f"Optimal Policy ({lower}, {upper}) | Total Expense: {cst:.2f}")
    plt.legend()
    plt.tight_layout()
    plt.show()


def run_simulation(lower_s, upper_S):
    stock = start_inv
    idx = 0
    history = []
    order_expenses = 0.0

    arrival_day = -1
    incoming_qty = 0
    random_days = np.sort(np.random.randint(1, 31, size=6))
    for day in range(1, sim_days + 1):
        if day == arrival_day:
            stock += incoming_qty
            arrival_day = -1
            incoming_qty = 0

        if (day % 30) in random_days:
            stock -= rng_demands[idx]
            idx += 1

        if day % 30 == 0:
            random_days = np.sort(np.random.randint(1, 31, size=6))
            if stock < lower_s:
                incoming_qty = upper_S - stock
                delay = int(np.random.uniform(15, 30))
                arrival_day = day + delay
                order_expenses += setup_cost + item_cost * incoming_qty

        history.append(stock)

    data = np.array(history)
    h_cost = np.sum(data[data > 0]) * (hold_cost / 30.0)
    b_cost = np.sum(-data[data < 0]) * (backlog_cost / 30.0)

    final_expense = h_cost + b_cost + order_expenses

    return {
        "cost": final_expense,
        "s": lower_s,
        "S": upper_S,
        "h_cost": h_cost,
        "b_cost": b_cost,
        "order_cost": order_expenses,
        "history": history,
    }


simulation_results = []

for s_val, S_val in policy_grid:
    res = run_simulation(s_val, S_val)
    simulation_results.append(res)
    print(
        f"s={res['s']}, S={res['S']} -> Expense: {res['cost']:.2f} (Hold: {res['h_cost']:.2f}, Short: {res['b_cost']:.2f}, Order: {res['order_cost']:.2f})"
    )

simulation_results.sort(key=lambda item: item["cost"])

optimal = simulation_results[0]

print(
    f"\nOptimal Policy: s={optimal['s']}, S={optimal['S']} with Expense={optimal['cost']:.2f}"
)

visualize_sim(optimal["s"], optimal["S"], optimal["history"], optimal["cost"])
