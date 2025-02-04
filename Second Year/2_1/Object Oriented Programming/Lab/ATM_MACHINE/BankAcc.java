package ATM_MACHINE;

import java.util.ArrayList;

public class BankAcc {
    private double balance;
    private ArrayList<String> tr_history;

    public BankAcc(double InitBal) {
        this.balance = InitBal;
        this.tr_history = new ArrayList<>();
        tr_history.add("Initial Balance: $" + InitBal);
    }

    public double getBalance() {
        return balance;
    }

    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            tr_history.add("Deposited: $" + amount);
            System.out.println("Successfully deposited $" + amount);
        } else {
            System.out.println("Invalid deposit amount.");
        }
    }

    public boolean withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            tr_history.add("Withdrawn: $" + amount);
            System.out.println("Successfully withdrawn $" + amount);
            return true;
        } else {
            System.out.println("Invalid withdrawal amount or insufficient balance.");
            return false;
        }
    }
    public void PrintStatement() {
        System.out.println("\nMini Statement:");
        for (String transaction : tr_history) {
            System.out.println(transaction);
        }
        System.out.println("Current Balance: $" + balance);
    }
}
