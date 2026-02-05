#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HISTORY 10


char name[30];
char family[30];
int accountID = 0;
int balance = 0;
int pin = 1234;
int isActive = 0;

int history[MAX_HISTORY];
int historyCount = 0;


void showMenu() {
    printf("\n===== ATM MENU =====\n");
    printf("1. Create Account\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Check Balance\n");
    printf("5. Change PIN\n");
    printf("6. Exit\n");
    printf("Choose: ");
}


void addHistory(int amount) {
    if (historyCount < MAX_HISTORY) {
        history[historyCount++] = amount;
    } else {
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY - 1] = amount;
    }
}


void createAccount() {
    if (isActive) {
        printf("Account already exists!\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", name);

    printf("Enter family: ");
    scanf("%s", family);

    printf("Enter initial balance: ");
    scanf("%d", &balance);

    if (balance < 0) {
        printf("Invalid balance! Set to 0.\n");
        balance = 0;
    }

    accountID = rand() % 9000 + 1000; 
    isActive = 1;
    historyCount = 0;

    printf("Account created successfully.\n");
    printf("Account ID: %d\n", accountID);
}


void deposit() {
    if (!isActive) {
        printf("No active account!\n");
        return;
    }

    int amount;
    printf("Enter deposit amount: ");
    scanf("%d", &amount);

    if (amount > 0) {
        balance += amount;
        addHistory(amount);
        printf("Deposit successful.\n");
    } else {
        printf("Invalid amount!\n");
    }
}


void withdrawMoney() {
    if (!isActive) {
        printf("No active account!\n");
        return;
    }

    int amount;
    printf("Enter withdraw amount: ");
    scanf("%d", &amount);

    if (amount > 0 && amount <= balance) {
        balance -= amount;
        addHistory(-amount);
        printf("Withdraw successful.\n");
    } else {
        printf("Invalid amount!\n");
    }
}


void checkBalance() {
    if (!isActive) {
        printf("No account exists!\n");
        return;
    }

    int id;
    printf("Enter Account ID: ");
    scanf("%d", &id);

    if (id != accountID) {
        printf("Wrong Account ID!\n");
        return;
    }

    printf("\nAccount Owner: %s %s\n", name, family);
    printf("Balance: %d\n", balance);
    printf("Last Transactions:\n");

    for (int i = historyCount - 1; i >= 0; i--) {
        printf("%d\n", history[i]);
    }
}


void changePIN() {
    int oldPin;
    printf("Enter current PIN: ");
    scanf("%d", &oldPin);

    if (oldPin == pin) {
        printf("Enter new PIN: ");
        scanf("%d", &pin);
        printf("PIN changed successfully.\n");
    } else {
        printf("Wrong PIN!\n");
    }
}


int main() {
    srand(time(NULL));

    int attempts = 0;
    int inputPin;

    while (attempts < 3) {
        printf("Enter PIN: ");
        scanf("%d", &inputPin);

        if (inputPin == pin)
            break;

        attempts++;
        printf("Wrong PIN!\n");
    }

    if (attempts == 3) {
        printf("Too many wrong attempts. Program terminated.\n");
        return 0;
    }

    int choice;

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: changePIN(); break;
            case 6: printf("Safe exit.\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}