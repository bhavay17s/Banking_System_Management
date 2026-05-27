#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS  200
#define NAME_LEN      50
#define FILE_NAME     "accounts.dat"

typedef struct {
    int    accountNumber;
    char   holderName[NAME_LEN];
    double balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int     totalAccounts = 0;

void loadRecords() {
    FILE* fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        totalAccounts = 0;
        return;
    }
    totalAccounts = 0;
    while (totalAccounts < MAX_ACCOUNTS &&
           fread(&accounts[totalAccounts], sizeof(Account), 1, fp) == 1) {
        totalAccounts++;
    }
    fclose(fp);
}

void saveRecords() {
    FILE* fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("  [!] Error: Could not open file for writing.\n");
        return;
    }
    fwrite(accounts, sizeof(Account), totalAccounts, fp);
    fclose(fp);
}

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getIntInput(const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value > 0) {
            clearInput();
            return value;
        }
        printf("  [!] Invalid input. Please enter a positive integer.\n");
        clearInput();
    }
}

double getAmountInput(const char* prompt) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1 && value > 0.0) {
            clearInput();
            return value;
        }
        printf("  [!] Amount must be greater than 0.\n");
        clearInput();
    }
}

void getStringInput(const char* prompt, char* buffer, int maxLen) {
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, maxLen, stdin) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n')
                buffer[len - 1] = '\0';
            if (strlen(buffer) > 0)
                return;
        }
        printf("  [!] Input cannot be empty.\n");
    }
}

int findAccount(int accNum) {
    for (int i = 0; i < totalAccounts; i++)
        if (accounts[i].accountNumber == accNum)
            return i;
    return -1;
}

void printDivider() {
    printf("  %s\n", "---------------------------------------------------");
}

void printTableHeader() {
    printDivider();
    printf("  %-12s %-25s %-15s\n", "Acc. No.", "Holder Name", "Balance (Rs.)");
    printDivider();
}

void printAccount(const Account* acc) {
    printf("  %-12d %-25s %-15.2f\n",
           acc->accountNumber,
           acc->holderName,
           acc->balance);
}

void createAccount() {
    printf("\n--- Create New Account ---\n");
    if (totalAccounts >= MAX_ACCOUNTS) {
        printf("  [!] Maximum account limit reached.\n");
        return;
    }
    int accNum = getIntInput("  Enter Account Number : ");
    if (findAccount(accNum) != -1) {
        printf("  [!] Account number %d already exists.\n", accNum);
        return;
    }
    char name[NAME_LEN];
    getStringInput("  Enter Account Holder Name : ", name, NAME_LEN);
    double initialDeposit = getAmountInput("  Enter Initial Deposit Amount (Rs.) : ");
    accounts[totalAccounts].accountNumber = accNum;
    strncpy(accounts[totalAccounts].holderName, name, NAME_LEN - 1);
    accounts[totalAccounts].holderName[NAME_LEN - 1] = '\0';
    accounts[totalAccounts].balance = initialDeposit;
    totalAccounts++;
    saveRecords();
    printf("  [+] Account created successfully. Account Number: %d\n", accNum);
}

void depositMoney() {
    printf("\n--- Deposit Money ---\n");
    int accNum = getIntInput("  Enter Account Number : ");
    int idx    = findAccount(accNum);
    if (idx == -1) {
        printf("  [!] Account number %d not found.\n", accNum);
        return;
    }
    printf("  Account Holder : %s\n", accounts[idx].holderName);
    printf("  Current Balance: Rs. %.2f\n", accounts[idx].balance);
    double amount = getAmountInput("  Enter Deposit Amount (Rs.) : ");
    accounts[idx].balance += amount;
    saveRecords();
    printf("  [+] Rs. %.2f deposited successfully.\n", amount);
    printf("  New Balance: Rs. %.2f\n", accounts[idx].balance);
}

void withdrawMoney() {
    printf("\n--- Withdraw Money ---\n");
    int accNum = getIntInput("  Enter Account Number : ");
    int idx    = findAccount(accNum);
    if (idx == -1) {
        printf("  [!] Account number %d not found.\n", accNum);
        return;
    }
    printf("  Account Holder : %s\n", accounts[idx].holderName);
    printf("  Current Balance: Rs. %.2f\n", accounts[idx].balance);
    double amount = getAmountInput("  Enter Withdrawal Amount (Rs.) : ");
    if (amount > accounts[idx].balance) {
        printf("  [!] Insufficient funds. Available Balance: Rs. %.2f\n",
               accounts[idx].balance);
        return;
    }
    accounts[idx].balance -= amount;
    saveRecords();
    printf("  [+] Rs. %.2f withdrawn successfully.\n", amount);
    printf("  Remaining Balance: Rs. %.2f\n", accounts[idx].balance);
}

void checkBalance() {
    printf("\n--- Check Balance ---\n");
    int accNum = getIntInput("  Enter Account Number : ");
    int idx    = findAccount(accNum);
    if (idx == -1) {
        printf("  [!] Account number %d not found.\n", accNum);
        return;
    }
    printTableHeader();
    printAccount(&accounts[idx]);
    printDivider();
}

void viewAllAccounts() {
    if (totalAccounts == 0) {
        printf("\n  [!] No accounts found.\n");
        return;
    }
    printf("\n--- All Accounts (%d) ---\n", totalAccounts);
    printTableHeader();
    for (int i = 0; i < totalAccounts; i++)
        printAccount(&accounts[i]);
    printDivider();
}

void deleteAccount() {
    printf("\n--- Delete Account ---\n");
    int accNum = getIntInput("  Enter Account Number to delete : ");
    int idx    = findAccount(accNum);
    if (idx == -1) {
        printf("  [!] Account number %d not found.\n", accNum);
        return;
    }
    printf("  Account to delete:\n");
    printTableHeader();
    printAccount(&accounts[idx]);
    printDivider();
    printf("  Are you sure you want to delete this account? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    clearInput();
    if (confirm == 'y' || confirm == 'Y') {
        for (int i = idx; i < totalAccounts - 1; i++)
            accounts[i] = accounts[i + 1];
        totalAccounts--;
        saveRecords();
        printf("  [+] Account deleted successfully.\n");
    } else {
        printf("  [-] Deletion cancelled.\n");
    }
}

void printMenu() {
    printf("\n");
    printf("  ==========================================\n");
    printf("        BANKING MANAGEMENT SYSTEM          \n");
    printf("  ==========================================\n");
    printf("   1. Create New Account                   \n");
    printf("   2. Deposit Money                        \n");
    printf("   3. Withdraw Money                       \n");
    printf("   4. Check Balance                        \n");
    printf("   5. View All Accounts                    \n");
    printf("   6. Delete Account                       \n");
    printf("   7. Exit                                 \n");
    printf("  ==========================================\n");
    printf("  Enter your choice: ");
}

int main() {
    loadRecords();
    int choice;
    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            clearInput();
            choice = 0;
        } else {
            clearInput();
        }
        switch (choice) {
            case 1: createAccount();   break;
            case 2: depositMoney();    break;
            case 3: withdrawMoney();   break;
            case 4: checkBalance();    break;
            case 5: viewAllAccounts(); break;
            case 6: deleteAccount();   break;
            case 7: printf("\n  Goodbye!\n\n"); break;
            default: printf("\n  [!] Invalid choice. Please enter 1-7.\n");
        }
    } while (choice != 7);
    return 0;
}