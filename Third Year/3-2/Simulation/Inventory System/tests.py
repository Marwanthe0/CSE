import random
import statistics

import numpy as np

SIMULATION_DAYS = 3600
LEAD_TIME_DAYS = 15
STARTING_STOCK = 60
MIN_DAILY_DEMAND = 0
MAX_DAILY_DEMAND = 15
HOLDING_COST_PER_UNIT = 1.0
BACKLOG_COST_PER_UNIT = 5.0
ORDERING_COST_PER_ORDER = 50.0
REPLICATIONS_PER_COMBO = 8
S_CANDIDATES = list(range(100, 400, 50))
BIG_S_CANDIDATES = list(range(200, 600, 50))


def simulate_one_run(reorder_point, order_up_to_level, random_seed):
    rng = random.Random(random_seed)
    inventory_level = STARTING_STOCK
    pending_orders = []
    total_holding_cost = 0.0
    total_backlog_cost = 0.0
    total_ordering_cost = 0.0
    orders_placed_count = 0
    daily_log = []

    for current_day in range(1, SIMULATION_DAYS + 1):
        order_arrived_today = False
        remaining_pending = []
        for arrival_day, quantity in pending_orders:
            if arrival_day == current_day:
                inventory_level += quantity
                order_arrived_today = True
            else:
                remaining_pending.append([arrival_day, quantity])
        pending_orders = remaining_pending

        todays_demand = rng.randint(MIN_DAILY_DEMAND, MAX_DAILY_DEMAND)
        inventory_level -= todays_demand

        stock_on_order = sum(q for _, q in pending_orders)
        inventory_position = inventory_level + stock_on_order

        order_placed_today = False
        order_quantity_today = 0

        if current_day % 30 == 0:
            if inventory_position < reorder_point:
                order_quantity_today = order_up_to_level - inventory_position
                pending_orders.append(
                    [current_day + LEAD_TIME_DAYS, order_quantity_today]
                )
                order_placed_today = True
                orders_placed_count += 1
                total_ordering_cost += ORDERING_COST_PER_ORDER

        positive_units = max(inventory_level, 0)
        backlog_units = max(-inventory_level, 0)
        holding_cost_today = positive_units * HOLDING_COST_PER_UNIT
        backlog_cost_today = backlog_units * BACKLOG_COST_PER_UNIT

        total_holding_cost += holding_cost_today
        total_backlog_cost += backlog_cost_today

        daily_log.append(
            {
                "day": current_day,
                "demand": todays_demand,
                "inventory_level": inventory_level,
                "order_placed": order_placed_today,
                "order_quantity": order_quantity_today,
                "order_arrived": order_arrived_today,
            }
        )

    total_cost = total_holding_cost + total_backlog_cost + total_ordering_cost

    summary = {
        "reorder_point": reorder_point,
        "order_up_to_level": order_up_to_level,
        "total_holding_cost": total_holding_cost,
        "total_backlog_cost": total_backlog_cost,
        "total_ordering_cost": total_ordering_cost,
        "total_cost": total_cost,
        "average_daily_cost": total_cost / SIMULATION_DAYS,
        "orders_placed_count": orders_placed_count,
    }

    return daily_log, summary


def evaluate_parameter_combo(reorder_point, order_up_to_level):
    daily_costs = []
    for replication_index in range(REPLICATIONS_PER_COMBO):
        seed = hash((reorder_point, order_up_to_level, replication_index)) % (2**32)
        _, summary = simulate_one_run(reorder_point, order_up_to_level, seed)
        daily_costs.append(summary["average_daily_cost"])

    return statistics.mean(daily_costs)


def search_best_parameters():
    results_grid = {}
    best_params = None
    best_cost = float("inf")

    for s in S_CANDIDATES:
        for S in BIG_S_CANDIDATES:
            if S <= s:
                continue

            average_cost = evaluate_parameter_combo(s, S)
            results_grid[(s, S)] = average_cost

            if average_cost < best_cost:
                best_cost = average_cost
                best_params = (s, S)

    return best_params, best_cost, results_grid


def print_search_results(results_grid, best_params, best_cost):
    print(f"{'s':>5} {'S':>5} {'Avg Cost/Day':>14}")
    print("-" * 26)

    for (s, S), cost in sorted(results_grid.items(), key=lambda item: item[1]):
        marker = "  <-- BEST" if (s, S) == best_params else ""
        print(f"{s:>5} {S:>5} {cost:>14.2f}{marker}")

    print("\n" + "=" * 50)
    print(f"BEST PARAMETERS FOUND: s = {best_params[0]}, S = {best_params[1]}")
    print(f"LOWEST AVERAGE DAILY COST: {best_cost:.2f}")
    print("=" * 50)


def plot_search_heatmap(
    results_grid, best_params, filename="parameter_search_heatmap.png"
):
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    s_values = sorted(set(s for s, _ in results_grid))
    S_values = sorted(set(S for _, S in results_grid))

    cost_matrix = np.full((len(S_values), len(s_values)), np.nan)
    for (s, S), cost in results_grid.items():
        row = S_values.index(S)
        col = s_values.index(s)
        cost_matrix[row, col] = cost

    fig, ax = plt.subplots(figsize=(8, 6))
    image = ax.imshow(cost_matrix, cmap="viridis_r", aspect="auto", origin="lower")

    ax.set_xticks(range(len(s_values)))
    ax.set_xticklabels(s_values)
    ax.set_yticks(range(len(S_values)))
    ax.set_yticklabels(S_values)
    ax.set_xlabel("Reorder point s")
    ax.set_ylabel("Order-up-to level S")
    ax.set_title("Average Daily Cost Across (s, S) Combinations")

    best_col = s_values.index(best_params[0])
    best_row = S_values.index(best_params[1])
    ax.scatter(
        [best_col],
        [best_row],
        marker="*",
        s=300,
        color="red",
        edgecolors="white",
        linewidths=1,
        label="Best combination",
    )
    ax.legend(loc="upper right")

    fig.colorbar(image, ax=ax, label="Average daily cost")
    plt.tight_layout()
    plt.savefig(filename, dpi=150)
    plt.close()


def plot_best_policy_chart(daily_log, summary, filename="best_policy_chart.png"):
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    import numpy as np

    days = np.array([d["day"] for d in daily_log])
    levels = np.array([d["inventory_level"] for d in daily_log])

    fig, ax = plt.subplots(figsize=(15, 6))

    ax.plot(
        days,
        levels,
        color="slategray",
        linewidth=1.0,
        zorder=2,
        label="Inventory level I(t)",
    )
    ax.fill_between(
        days,
        levels,
        0,
        where=(levels >= 0),
        interpolate=True,
        color="mediumturquoise",
        alpha=0.4,
        zorder=1,
        label="I+(t) - Holding Cost",
    )
    ax.fill_between(
        days,
        levels,
        0,
        where=(levels <= 0),
        interpolate=True,
        color="lightcoral",
        alpha=0.5,
        zorder=1,
        label="I-(t) - Backlog Cost",
    )

    for month_day in range(30, SIMULATION_DAYS + 1, 30):
        ax.axvline(
            x=month_day, color="gray", linestyle=":", linewidth=0.5, alpha=0.6, zorder=0
        )
    ax.plot(
        [],
        [],
        color="gray",
        linestyle=":",
        linewidth=0.5,
        label="Monthly Check (30 days)",
    )

    arrived_days = [d["day"] for d in daily_log if d["order_arrived"]]
    arrived_levels = [d["inventory_level"] for d in daily_log if d["order_arrived"]]
    if arrived_days:
        ax.scatter(
            arrived_days,
            arrived_levels,
            color="lime",
            marker="^",
            s=50,
            edgecolors="black",
            linewidths=0.5,
            zorder=4,
            label="Restock Arrived (+15 days)",
        )

    placed_days = [d["day"] for d in daily_log if d["order_placed"]]
    placed_levels = [d["inventory_level"] for d in daily_log if d["order_placed"]]
    if placed_days:
        ax.scatter(
            placed_days,
            placed_levels,
            color="red",
            marker="v",
            s=50,
            edgecolors="black",
            linewidths=0.5,
            zorder=4,
            label="Order Placed",
        )

    ax.axhline(
        y=summary["reorder_point"],
        color="darkorange",
        linestyle="--",
        linewidth=2.0,
        zorder=5,
        label=f"Reorder Point s = {summary['reorder_point']}",
    )
    ax.axhline(
        y=summary["order_up_to_level"],
        color="darkgreen",
        linestyle="--",
        linewidth=2.0,
        zorder=5,
        label=f"Order-Up-To S = {summary['order_up_to_level']}",
    )
    ax.axhline(y=0, color="black", linewidth=1.0, zorder=3)

    title = (
        f"BEST POLICY  s={summary['reorder_point']}, S={summary['order_up_to_level']}  |  "
        f"Avg Cost/Day = {summary['average_daily_cost']:.2f}  "
        f"[Ordering: {summary['total_ordering_cost'] / SIMULATION_DAYS:.2f} | "
        f"Holding: {summary['total_holding_cost'] / SIMULATION_DAYS:.2f} | "
        f"Backlog: {summary['total_backlog_cost'] / SIMULATION_DAYS:.2f}]"
    )
    ax.set_title(title, fontsize=11)

    ax.set_xlabel("Day")
    ax.set_ylabel("Inventory level (units)")
    ax.legend(loc="upper right", fontsize=8, ncol=2)
    plt.tight_layout()
    plt.savefig(filename, dpi=200)
    plt.close()


if __name__ == "__main__":
    print("Searching for the best (s, S) combination...\n")
    best_params, best_cost, results_grid = search_best_parameters()
    print_search_results(results_grid, best_params, best_cost)

    plot_search_heatmap(results_grid, best_params, "parameter_search_heatmap.png")
    print("\nHeatmap saved as parameter_search_heatmap.png")

    best_s, best_S = best_params
    daily_log, summary = simulate_one_run(best_s, best_S, random_seed=2024)
    plot_best_policy_chart(daily_log, summary, "best_policy_chart.png")
    print("Best policy chart saved as best_policy_chart.png")
