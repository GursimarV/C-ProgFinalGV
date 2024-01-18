#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

enum TransactionType { Withdrawal, Deposit };

class BankAccount {
public:
    BankAccount() : AccountTotal(0) {}
    ~BankAccount() {}

    std::string AccountID;
    double trans_amt;
    TransactionType trans_type;
    int AccountTotal;
};

TransactionType convertToTransactionType(const std::string& type) {
    if (type == "withdrawal") {
        return Withdrawal;
    } else {
        return Deposit;
    }
}

void processTransaction(BankAccount& newAccount, std::vector<std::string>& accountStrings, std::vector<BankAccount>& bankAccounts) {
    // Checks if string is in list already
    auto it = std::find(accountStrings.begin(), accountStrings.end(), newAccount.AccountID);
    if (it == accountStrings.end()) {
        accountStrings.push_back(newAccount.AccountID);
        newAccount.AccountTotal += newAccount.trans_amt;
        bankAccounts.push_back(newAccount);
    } else {
        for (auto& account : bankAccounts) {
            if (account.AccountID == newAccount.AccountID) {
                if (newAccount.trans_type == Withdrawal) {
                    account.AccountTotal -= newAccount.trans_amt;
                } else {
                    account.AccountTotal += newAccount.trans_amt;
                }
            }
        }
    }
}

void printAccountDetails(const std::vector<BankAccount>& bankAccounts) {
    int accountNumber = 1;
    for (const auto& account : bankAccounts) {
        std::cout << "Account #" << accountNumber << ": " << account.AccountID << " $" << account.AccountTotal << std::endl;
        accountNumber++;
    }
}

int main() {
    std::vector<std::string> accountStrings;
    std::vector<BankAccount> bankAccounts;

    // Opens text file
    std::ifstream file_;
    file_.open("output.txt");

    // Checks if the file is open
    if (!file_.is_open()) {
        std::cout << "Unable to open the file." << '\n';
        return 1;
    }

    BankAccount fooAcc;

    while (file_ >> fooAcc.AccountID >> fooAcc.trans_amt) {
        std::string transTypeStr;
        file_ >> transTypeStr;
        fooAcc.trans_type = convertToTransactionType(transTypeStr);

        processTransaction(fooAcc, accountStrings, bankAccounts);
    }

    printAccountDetails(bankAccounts);

    file_.close();

    return 0;
}