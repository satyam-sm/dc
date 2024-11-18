#include <iostream>
#include <algorithm> // for std::max

class LamportsClock {
    int clock;

public:
    LamportsClock() : clock(0) {}

    void internalEvent() {
        clock++;
    }

    int sendMessage() {
        clock++;
        return clock;
    }

    void receiveMessage(int receivedTimestamp) {
        clock = std::max(clock, receivedTimestamp) + 1;
    }

    int getClock() const {
        return clock;
    }
};

class Branch {
    std::string name;
    int balance;
    LamportsClock lamportsClock;

public:
    Branch(const std::string& branchName, int initialBalance)
        : name(branchName), balance(initialBalance) {}

    int deposit(int amount) {
        lamportsClock.internalEvent();
        balance += amount;
        std::cout << name << " deposits $" << amount
                  << ", clock = " << lamportsClock.getClock()
                  << ", balance = $" << balance << "\n";
        return lamportsClock.getClock();
    }

    int withdraw(int amount) {
        lamportsClock.internalEvent();
        if (amount > balance) {
            std::cout << name << " cannot withdraw $" << amount
                      << " due to insufficient funds.\n";
        } else {
            balance -= amount;
            std::cout << name << " withdraws $" << amount
                      << ", clock = " << lamportsClock.getClock()
                      << ", balance = $" << balance << "\n";
        }
        return lamportsClock.getClock();
    }

    void receiveTransaction(int incomingClock, int amount, const std::string& transactionType) {
        lamportsClock.receiveMessage(incomingClock);
        if (transactionType == "deposit") {
            balance += amount;
            std::cout << name << " received a deposit of $" << amount
                      << " with clock " << incomingClock
                      << ". Updated clock = " << lamportsClock.getClock()
                      << ", balance = $" << balance << "\n";
        } else if (transactionType == "withdraw" && amount <= balance) {
            balance -= amount;
            std::cout << name << " received a withdrawal of $" << amount
                      << " with clock " << incomingClock
                      << ". Updated clock = " << lamportsClock.getClock()
                      << ", balance = $" << balance << "\n";
        } else {
            std::cout << name << " could not process withdrawal of $" << amount
                      << " due to insufficient funds. Clock = "
                      << lamportsClock.getClock() << "\n";
        }
    }

    void getBalance() const {
        std::cout << name << " balance = $" << balance
                  << ", clock = " << lamportsClock.getClock() << "\n";
    }
};

int main() {
    Branch branchA("Branch A", 1000);
    Branch branchB("Branch B", 1000);

    // Branch A deposits $200
    int clockA = branchA.deposit(200);

    // Branch B receives this deposit transaction
    branchB.receiveTransaction(clockA, 200, "deposit");

    // Branch B withdraws $150
    int clockB = branchB.withdraw(150);

    // Branch A receives this withdrawal transaction
    branchA.receiveTransaction(clockB, 150, "withdraw");

    // Branch A attempts another transaction - withdraws $500
    clockA = branchA.withdraw(500);

    // Branch B receives this transaction
    branchB.receiveTransaction(clockA, 500, "withdraw");

    // Display final balances
    branchA.getBalance();
    branchB.getBalance();

    return 0;
}
