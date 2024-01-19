#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>

//Enum to represent the two different transaction types
enum TransactionType { Withdrawal, Deposit };

//The class to represent the bank account and its details
class BankAccount{
public:
    BankAccount() : AccountTotal(0) {}
    ~BankAccount() {}

    std::string AccountID;
    double trans_amt;
    TransactionType trans_type;
    int AccountTotal;
};

//Converts the string of details to the two different transaction types
TransactionType convertToTransactionType(const std::string& type)
{
    if (type == "withdrawal")
    {
        return Withdrawal;
    }
    else
    {
        return Deposit;
    }
}

// Function to process a transaction and update account details
void processTransaction(BankAccount& newAccount, std::vector<std::string>& accountStrings, std::vector<BankAccount>& bankAccounts)
{
    // Checks if string is in list of accounts
    auto it = std::find(accountStrings.begin(), accountStrings.end(), newAccount.AccountID);
    //If the account isn't in the list, add it up and update the balance
    if (it == accountStrings.end())
    {
        accountStrings.push_back(newAccount.AccountID);
        newAccount.AccountTotal += newAccount.trans_amt;
        bankAccounts.push_back(newAccount);
    }
    //If the account is in the list, find the account and update the balance
    else
    {
        for (auto& account : bankAccounts)
        {
            if (account.AccountID == newAccount.AccountID)
            {
                if (newAccount.trans_type == Withdrawal)
                {
                    account.AccountTotal -= newAccount.trans_amt;
                }
                else
                {
                    account.AccountTotal += newAccount.trans_amt;
                }
            }
        }
    }
}

//This is the function to print out the account details
void printAccountDetails(const std::vector<BankAccount>& bankAccounts)
{
    int accountNumber = 1;
    for (const auto& account : bankAccounts)
    {
        //Print out the Account #, ID, and the total # of $
        std::cout << "Account #" << accountNumber << ": " << account.AccountID << " $" << std::fixed << std::setprecision(2) << account.AccountTotal << std::endl;
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
    if (!file_.is_open())
    {
        std::cout << "Unable to open the file." << '\n';
        return 1;
    }

    BankAccount fooAcc;

    //Read the account details and the transactions in the file and processes
    while (file_ >> fooAcc.AccountID >> fooAcc.trans_amt)
    {
        std::string transTypeStr;
        file_ >> transTypeStr;
        fooAcc.trans_type = convertToTransactionType(transTypeStr);

        processTransaction(fooAcc, accountStrings, bankAccounts);
    }

    //Print out all 10 account details
    printAccountDetails(bankAccounts);

    file_.close();

    return 0;
}
