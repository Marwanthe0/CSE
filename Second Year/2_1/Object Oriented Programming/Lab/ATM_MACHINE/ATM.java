package ATM_MACHINE;

import java.util.HashMap;
import java.util.Scanner;

public class ATM {
    private HashMap<Integer, BankAcc> accounts;
    private Scanner scanner;
    public ATM() {
        accounts = new HashMap<>();
        scanner = new Scanner(System.in);
        accounts.put(1234, new BankAcc(1000));
        accounts.put(5678, new BankAcc(500));
    }
    private int authenticateUser() {
        System.out.print("Enter PIN: ");
        int pin = scanner.nextInt();
        if (accounts.containsKey(pin)) {
            return pin;
        } else {
            System.out.println("Invalid PIN. Try again.");
            return -1;
        }
    }
    public void start() {
        System.out.println("Welcome to ATM!");
        int userPin;
        do {
            userPin = authenticateUser();
        } while (userPin == -1);
        BankAcc userAccount = accounts.get(userPin);
        while (true) {
            System.out.println("\n1. Check Balance");
            System.out.println("2. Deposit Money");
            System.out.println("3. Withdraw Money");
            System.out.println("4. Mini Statement");
            System.out.println("5. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            switch (choice) {
                case 1:
                    System.out.println("Current Balance: $" + userAccount.getBalance());
                    break;
                case 2:
                    System.out.print("Enter deposit amount: ");
                    double depositAmount = scanner.nextDouble();
                    userAccount.deposit(depositAmount);
                    break;
                case 3:
                    System.out.print("Enter withdrawal amount: ");
                    double withdrawAmount = scanner.nextDouble();
                    userAccount.withdraw(withdrawAmount);
                    break;
                case 4:
                    userAccount.PrintStatement();
                    break;
                case 5:
                    System.out.println("Thank you for using the ATM. Goodbye!");
                    return;
                default:
                    System.out.println("Invalid option. Try again.");
            }
        }
    }
}
