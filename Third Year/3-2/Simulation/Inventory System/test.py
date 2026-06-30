import random
import statistics

SIMULATION_DAYS = 120
REORDER_POINT = 20
ORDER_UP_TO_LEVEL = 80
LEAD_TIME_DAYS = 3
STARTING_STOCK = 50

MIN_DAILY_DEMAND = 0
MAX_DAILY_DEMAND = 15

HOLDING_COST_PER_UNIT = 1.0
BACKLOG_COST_PER_UNIT = 5.0
ORDERING_COST_PER_ORDER = 50.0

random.seed(42)


def generate_daily_demand():
    return random.randint(MIN_DAILY_DEMAND, MAX_DAILY_DEMAND)


def run_inventory_simulation():
    inventory_level = STARTING_STOCK
    pending_orders = []

    total_holding_cost = 0.0
    total_backlog_cost = 0.0
    total_ordering_cost = 0.0
    orders_placed_count = 0

    daily_log = []

    for current_day in range(1, SIMULATION_DAYS + 1):
        remaining_pending = []
        for arrival_day, quantity in pending_orders:
            if arrival_day == current_day:
                inventory_level += quantity
            else:
                remaining_pending.append([arrival_day, quantity])
        pending_orders = remaining_pending

        todays_demand = generate_daily_demand()
        inventory_level -= todays_demand

        stock_on_order = sum(quantity for _, quantity in pending_orders)
        inventory_position = inventory_level + stock_on_order

        order_placed_today = False
        order_quantity_today = 0

        if inventory_position < REORDER_POINT:
            order_quantity_today = ORDER_UP_TO_LEVEL - inventory_position
            pending_orders.append([current_day + LEAD_TIME_DAYS, order_quantity_today])
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
                "holding_cost": holding_cost_today,
                "backlog_cost": backlog_cost_today,
            }
        )

    total_cost = total_holding_cost + total_backlog_cost + total_ordering_cost

    summary = {
        "total_holding_cost": total_holding_cost,
        "total_backlog_cost": total_backlog_cost,
        "total_ordering_cost": total_ordering_cost,
        "total_cost": total_cost,
        "average_daily_cost": total_cost / SIMULATION_DAYS,
        "orders_placed_count": orders_placed_count,
        "average_inventory_level": statistics.mean(
            d["inventory_level"] for d in daily_log
        ),
    }

    return daily_log, summary


def print_report(daily_log, summary):
    header = f"{'Day':>4} {'Demand':>7} {'InvLevel':>9} {'Order?':>7} {'OrderQty':>9}"
    print(header)
    print("-" * len(header))

    for d in daily_log:
        order_flag = "YES" if d["order_placed"] else ""
        order_qty = d["order_quantity"] if d["order_placed"] else ""
        print(
            f"{d['day']:>4} {d['demand']:>7} {d['inventory_level']:>9} "
            f"{order_flag:>7} {order_qty:>9}"
        )

    print("\n" + "=" * 50)
    print("SIMULATION SUMMARY")
    print("=" * 50)
    print(f"Orders placed            : {summary['orders_placed_count']}")
    print(f"Average inventory level  : {summary['average_inventory_level']:.2f} units")
    print(f"Total holding cost       : {summary['total_holding_cost']:.2f}")
    print(f"Total backlog cost       : {summary['total_backlog_cost']:.2f}")
    print(f"Total ordering cost      : {summary['total_ordering_cost']:.2f}")
    print(f"TOTAL COST               : {summary['total_cost']:.2f}")
    print(f"Average cost per day     : {summary['average_daily_cost']:.2f}")


def save_inventory_chart(daily_log, filename="inventory_level_chart.png", summary=None):
    import matplotlib

    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    import numpy as np

    days = np.array([d["day"] for d in daily_log])
    levels = np.array([d["inventory_level"] for d in daily_log])

    fig, ax = plt.subplots(figsize=(13, 5))

    ax.plot(
        days, levels, color="slategray", linewidth=1.2, label="Inventory level I(t)"
    )

    ax.fill_between(
        days,
        levels,
        0,
        where=(levels >= 0),
        interpolate=True,
        color="mediumturquoise",
        alpha=0.4,
        label="I+(t) - Holding Cost Region",
    )

    ax.fill_between(
        days,
        levels,
        0,
        where=(levels <= 0),
        interpolate=True,
        color="lightcoral",
        alpha=0.5,
        label="I-(t) - Backlog Cost Region",
    )

    ax.axhline(
        y=REORDER_POINT,
        color="darkorange",
        linestyle="--",
        linewidth=1.5,
        label=f"Reorder Point s = {REORDER_POINT}",
    )
    ax.axhline(
        y=ORDER_UP_TO_LEVEL,
        color="darkgreen",
        linestyle="--",
        linewidth=1.5,
        label=f"Order-Up-To S = {ORDER_UP_TO_LEVEL}",
    )
    ax.axhline(y=0, color="black", linewidth=0.8)

    if summary is not None:
        title = (
            f"Average Cost/Day = {summary['average_daily_cost']:.2f}  "
            f"[Ordering: {summary['total_ordering_cost'] / SIMULATION_DAYS:.2f} | "
            f"Holding: {summary['total_holding_cost'] / SIMULATION_DAYS:.2f} | "
            f"Backlog: {summary['total_backlog_cost'] / SIMULATION_DAYS:.2f}]"
        )
        ax.set_title(title)
    else:
        ax.set_title("Inventory Level Over Time - (s, S) Policy with Backorders")

    ax.set_xlabel("Day")
    ax.set_ylabel("Inventory level (units)")
    ax.legend(loc="upper right", fontsize=8)
    plt.tight_layout()
    plt.savefig(filename, dpi=150)
    plt.close()


if __name__ == "__main__":
    daily_log, summary = run_inventory_simulation()
    print_report(daily_log, summary)
    save_inventory_chart(daily_log, "inventory_level_chart.png", summary)
    print("\nChart saved as inventory_level_chart.png")
