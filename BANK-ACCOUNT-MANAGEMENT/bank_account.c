#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int acc_no;
    char name[50];
    float balance;
};

void createAccount() {
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &acc.acc_no);
    printf("Enter name: ");
    getchar();  // consume newline
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0'; // remove newline
    printf("Enter initial balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
    printf("Account created successfully!\n");
}

void depositMoney() {
    struct Account acc;
    int acc_no, found = 0;
    float amount;

    FILE *fp = fopen("accounts.dat", "rb+");
    if (!fp) {
        printf("No accounts file found!\n");
        return;
    }

    printf("Enter account number to deposit into: ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.acc_no == acc_no) {
            acc.balance += amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            found = 1;
            printf("Deposit successful! New balance: %.2f\n", acc.balance);
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(fp);
}

void withdrawMoney() {
    struct Account acc;
    int acc_no, found = 0;
    float amount;

    FILE *fp = fopen("accounts.dat", "rb+");
    if (!fp) {
        printf("No accounts file found!\n");
        return;
    }

    printf("Enter account number to withdraw from: ");
    scanf("%d", &acc_no);
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.acc_no == acc_no) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                found = 1;
                printf("Withdrawal successful! New balance: %.2f\n", acc.balance);
            } else {
                printf("Insufficient funds!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(fp);
}

void checkBalance() {
    struct Account acc;
    int acc_no, found = 0;

    FILE *fp = fopen("accounts.dat", "rb");
    if (!fp) {
        printf("No accounts file found!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &acc_no);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.acc_no == acc_no) {
            printf("Account Number: %d\n", acc.acc_no);
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(fp);
}

void displayAllAccounts() {
    struct Account acc;
    FILE *fp = fopen("accounts.dat", "rb");
    if (!fp) {
        printf("No accounts to display!\n");
        return;
    }

    printf("\n--- All Accounts ---\n");
    while (fread(&acc, sizeof(acc), 1, fp)) {
        printf("Acc No: %d | Name: %s | Balance: %.2f\n",
               acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Bank Account Management ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: displayAllAccounts(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

 return 0;
}
