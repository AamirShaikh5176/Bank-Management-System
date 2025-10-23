#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "bank_records.txt"

typedef struct {
    int acc_no;
    char name[50];
    float balance;
} Account;

// Function declarations
void create_account();
void display_account();
void deposit();
void withdraw();
void transfer();
void update_account();
void delete_account();
void display_all();
float parse_amount(char str[]);

int main() {
    int choice;

    while (1) {
        printf("\n======= Bharati BANK MANAGEMENT SYSTEM =======\n");
        printf("1. Create New Account\n");
        printf("2. Display Account Details\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Transfer Money\n");
        printf("6. Update Account Info\n");
        printf("7. Delete Account\n");
        printf("8. Display All Accounts\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        getchar(); // remove newline after number input

        switch (choice) {
            case 1: create_account(); break;
            case 2: display_account(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: transfer(); break;
            case 6: update_account(); break;
            case 7: delete_account(); break;
            case 8: display_all(); break;
            case 9: printf("Thank you for using the system!\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }

        printf("\nPress Enter to continue...");
        getchar(); // wait for enter
        system("cls"); // clear screen (Windows)
    }
    return 0;
}

// Remove commas from string and convert to float
float parse_amount(char str[]) {
    char clean[30];
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ',')
            clean[j++] = str[i];
    }
    clean[j] = '\0';
    return atof(clean);
}

// Create account
void create_account() {
    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    Account acc = {0};
    char balance_input[30];

    printf("Enter Account Number: ");
    scanf("%d", &acc.acc_no);
    getchar();

    printf("Enter Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0';

    printf("Enter Initial Balance: ");
    fgets(balance_input, sizeof(balance_input), stdin);
    balance_input[strcspn(balance_input, "\n")] = '\0';
    acc.balance = parse_amount(balance_input);

    fprintf(fp, "%d \"%s\" %.2f\n", acc.acc_no, acc.name, acc.balance);
    fclose(fp);

    printf("\nAccount created successfully!\n");
}

// Display specific account
void display_account() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    int acc_no, found = 0;
    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &acc_no);

    while (fscanf(fp, "%d \"%[^\"]\" %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        if (acc.acc_no == acc_no) {
            printf("\nAccount No: %d\nName: %s\nBalance: %.2f\n",
                   acc.acc_no, acc.name, acc.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Account not found!\n");
}

// Deposit money
void deposit() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    int acc_no;
    char amount_input[30];
    float amount;
    int found = 0;
    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    getchar();
    printf("Enter Amount to Deposit: ");
    fgets(amount_input, sizeof(amount_input), stdin);
    amount_input[strcspn(amount_input, "\n")] = '\0';
    amount = parse_amount(amount_input);

    while (fscanf(fp, "%d \"%[^\"]\" %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        if (acc.acc_no == acc_no) {
            acc.balance += amount;
            found = 1;
        }
        fprintf(temp, "%d \"%s\" %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Deposit successful!\n");
    else
        printf("Account not found!\n");
}

// Withdraw money
void withdraw() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    int acc_no;
    char amount_input[30];
    float amount;
    int found = 0;
    Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    getchar();
    printf("Enter Amount to Withdraw: ");
    fgets(amount_input, sizeof(amount_input), stdin);
    amount_input[strcspn(amount_input, "\n")] = '\0';
    amount = parse_amount(amount_input);

    while (fscanf(fp, "%d \"%[^\"]\" %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        if (acc.acc_no == acc_no) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
                printf("Withdrawal successful! New Balance: %.2f\n", acc.balance);
            } else {
                printf("Insufficient balance!\n");
            }
            found = 1;
        }
        fprintf(temp, "%d \"%s\" %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (!found)
        printf("Account not found!\n");
}

// Transfer money
void transfer() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    int from_acc, to_acc;
    char amount_input[30];
    float amount;
    int found_from = 0, found_to = 0;
    Account acc;

    printf("Enter Source Account Number: ");
    scanf("%d", &from_acc);
    getchar();
    printf("Enter Destination Account Number: ");
    scanf("%d", &to_acc);
    getchar();
    printf("Enter Amount to Transfer: ");
    fgets(amount_input, sizeof(amount_input), stdin);
    amount_input[strcspn(amount_input, "\n")] = '\0';
    amount = parse_amount(amount_input);

    while (fscanf(fp, "%d \"%[^\"]\" %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        if (acc.acc_no == from_acc) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
                found_from = 1;
            } else {
                printf("Insufficient balance in source account!\n");
            }
        } else if (acc.acc_no == to_acc) {
            acc.balance += amount;
            found_to = 1;
        }
        fprintf(temp, "%d \"%s\" %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found_from && found_to)
        printf("Transfer Successful!\n");
    else
        printf("One or both accounts not found!\n");
}

// Update account
void update_account() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    int acc_no, found = 0;
    Account acc;
    char new_name[50];

    printf("Enter Account Number to Update: ");
    scanf("%d", &acc_no);
    getchar();
    printf("Enter New Name: ");
    fgets(new_name, sizeof(new_name), stdin);
    new_name[strcspn(new_name, "\n")] = '\0';

    while (fscanf(fp, "%d \"%[^\"]\" %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        if (acc.acc_no == acc_no) {
            strcpy(acc.name, new_name);
            found = 1;
        }
        fprintf(temp, "%d \"%s\" %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Account updated successfully!\n");
    else
        printf("Account not found!\n");
}

// Delete account
void delete_account() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    int acc_no, found = 0;
    Account acc;

    printf("Enter Account Number to Delete: ");
    scanf("%d", &acc_no);

    while (fscanf(fp, "%d \"%[^\"]\" %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        if (acc.acc_no != acc_no) {
            fprintf(temp, "%d \"%s\" %.2f\n", acc.acc_no, acc.name, acc.balance);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Account deleted successfully!\n");
    else
        printf("Account not found!\n");
}

// Display all accounts
void display_all() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    Account acc;
    printf("\n%-10s %-20s %-10s\n", "Acc No", "Name", "Balance");
    printf("--------------------------------------------------\n");

    while (fscanf(fp, "%d \"%[^\"]\" %f", &acc.acc_no, acc.name, &acc.balance) == 3) {
        printf("%-10d %-20s %-10.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
}
