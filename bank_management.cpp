#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolder;
    double balance;
    string username;
    string password;
    int authAttempts;

public:
    // Constructor
    Account(int accNum, string holder, double initialBalance, string user, string pass)
        : accountNumber(accNum), accountHolder(holder), balance(initialBalance), username(user), password(pass), authAttempts(0) {}

    // Getters
    int getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    string getUsername() const {
        return username;
    }

    int getAuthAttempts() const {
        return authAttempts;
    }

    void incrementAuthAttempts() {
        authAttempts++;
    }

    void resetAuthAttempts() {
        authAttempts = 0;
    }

    // Methods
    bool authenticate(const string &user, const string &pass) {
        if (username == user && password == pass) {
            resetAuthAttempts();
            return true;
        } else {
            incrementAuthAttempts();
            return false;
        }
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: " << balance << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds." << endl;
            return false;
        } else {
            balance -= amount;
            cout << "Withdrawal successful. New balance: " << balance << endl;
            return true;
        }
    }

    bool transfer(Account &toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            cout << "Transfer successful." << endl;
            return true;
        } else {
            cout << "Transfer failed." << endl;
            return false;
        }
    }

    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: " << balance << endl;
    }
};

class Bank {
private:
    vector<Account> accounts;
    set<int> accountNumbers;

    int generateUniqueAccountNumber() {
        int accNum;
        do {
            accNum = rand() % 9000 + 1000; // Generates a random number between 1000 and 9999
        } while (accountNumbers.find(accNum) != accountNumbers.end());
        accountNumbers.insert(accNum);
        return accNum;
    }

public:
    Bank() {
        srand(time(0)); // Seed the random number generator
    }

    // Create a new account
    void createAccount(string holder, double initialBalance, string user, string pass) {
        int accNum = generateUniqueAccountNumber();
        Account newAccount(accNum, holder, initialBalance, user, pass);
        accounts.push_back(newAccount);
        cout << "Account created successfully. Account Number: " << accNum << endl;
    }

    // Find account by account number
    Account* findAccount(int accNum) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accNum) {
                return &account;
            }
        }
        cout << "Account not found." << endl;
        return nullptr;
    }

    // Authenticate user
    Account* authenticateUser(const string &user, const string &pass) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->authenticate(user, pass)) {
                return &(*it);
            } else if (it->getAuthAttempts() >= 3) {
                cout << "Account locked due to too many failed attempts. Deleting account..." << endl;
                accountNumbers.erase(it->getAccountNumber());
                accounts.erase(it);
                return nullptr;
            }
        }
        cout << "Authentication failed." << endl;
        return nullptr;
    }

    // Delete account by account number
    void deleteAccount(int accNum) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->getAccountNumber() == accNum) {
                accountNumbers.erase(it->getAccountNumber());
                accounts.erase(it);
                cout << "Account deleted successfully." << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }

    // Display all accounts
    void displayAllAccounts() const {
        for (const auto &account : accounts) {
            account.display();
            cout << "-------------------------" << endl;
        }
    }
};

void showMenu() {
    cout << "1. Create Account" << endl;
    cout << "2. Deposit" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Transfer" << endl;
    cout << "5. Display Account Details" << endl;
    cout << "6. Display All Accounts" << endl;
    cout << "7. Delete Account" << endl;
    cout << "8. Exit" << endl;
}

int main() {
    Bank bank;
    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string holder, user, pass;
                double initialBalance;
                cout << "Enter account holder name: ";
                cin.ignore();
                getline(cin, holder);
                cout << "Enter initial balance: ";
                cin >> initialBalance;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                bank.createAccount(holder, initialBalance, user, pass);
                break;
            }
            case 2: {
                string user, pass;
                double amount;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                Account* account = bank.authenticateUser(user, pass);
                if (account) {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                }
                break;
            }
            case 3: {
                string user, pass;
                double amount;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                Account* account = bank.authenticateUser(user, pass);
                if (account) {
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    account->withdraw(amount);
                }
                break;
            }
            case 4: {
                string user, pass;
                int toAccNum;
                double amount;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                Account* fromAccount = bank.authenticateUser(user, pass);
                if (fromAccount) {
                    cout << "Enter destination account number: ";
                    cin >> toAccNum;
                    Account* toAccount = bank.findAccount(toAccNum);
                    if (toAccount) {
                        cout << "Enter amount to transfer: ";
                        cin >> amount;
                        fromAccount->transfer(*toAccount, amount);
                    }
                }
                break;
            }
            case 5: {
                string user, pass;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                Account* account = bank.authenticateUser(user, pass);
                if (account) {
                    account->display();
                }
                break;
            }
            case 6: {
                bank.displayAllAccounts();
                break;
            }
            case 7: {
                int accNum;
                cout << "Enter account number to delete: ";
                cin >> accNum;
                bank.deleteAccount(accNum);
                break;
            }
            case 8: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != 8);

    return 0;
}
