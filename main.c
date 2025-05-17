#include <stdio.h>
#include <string.h>

#define MAX_ROOMMATES 10
#define MAX_EXPENSES 100

int main()
{
    int roommateCount;
    char roommateNames[MAX_ROOMMATES][20];
    float expenses[MAX_ROOMMATES][MAX_EXPENSES];
    int expenseCounts[MAX_ROOMMATES] = {0};
    float totals[MAX_ROOMMATES] = {0};

    printf("Enter number of roommates (max %d): ", MAX_ROOMMATES);
    scanf("%d", &roommateCount);

    if (roommateCount < 1 || roommateCount > MAX_ROOMMATES)
    {
        printf("Invalid number of roommates.\n");
        return 1;
    }

    for (int i = 0; i < roommateCount; i++)
    {
        printf("Enter name of roommate %d: ", i + 1);
        scanf("%s", roommateNames[i]);
    }

    int choice;
    do
    {
        printf("\n==== ROOMMATE EXPENSE TRACKER MENU ====\n");
        printf("1. Add Expense\n");
        printf("2. View All Expenses\n");
        printf("3. View Individual Roommate Expenses\n");
        printf("4. Edit Last Expense for a Roommate\n");
        printf("5. Clear All Expenses for a Roommate\n");
        printf("6. Show Summary and Settlement\n");
        printf("7. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int rIndex;
            printf("\nSelect roommate to add expense:\n");
            for (int i = 0; i < roommateCount; i++)
            {
                printf("%d. %s\n", i + 1, roommateNames[i]);
            }
            printf("Enter number: ");
            scanf("%d", &rIndex);

            if (rIndex < 1 || rIndex > roommateCount)
            {
                printf("Invalid selection.\n");
                continue;
            }

            rIndex--;

            if (expenseCounts[rIndex] >= MAX_EXPENSES)
            {
                printf("Expense limit reached for %s.\n", roommateNames[rIndex]);
                continue;
            }

            float amount;
            printf("Enter expense amount for %s: ", roommateNames[rIndex]);
            scanf("%f", &amount);

            expenses[rIndex][expenseCounts[rIndex]] = amount;
            expenseCounts[rIndex]++;
            totals[rIndex] += amount;

            printf("Expense added successfully!\n");
        }
        else if (choice == 2)
        {
            printf("\n===== All Expenses =====\n");
            for (int i = 0; i < roommateCount; i++)
            {
                printf("%s:\n", roommateNames[i]);
                if (expenseCounts[i] == 0)
                {
                    printf("  No expenses recorded.\n");
                }
                else
                {
                    for (int j = 0; j < expenseCounts[i]; j++)
                    {
                        printf("  Expense %d: %.2f\n", j + 1, expenses[i][j]);
                    }
                }
                printf("----------------------\n");
            }
        }
        else if (choice == 3)
        {
            int rIndex;
            printf("Enter roommate number to view expenses: ");
            for (int i = 0; i < roommateCount; i++)
            {
                printf("%d. %s\n", i + 1, roommateNames[i]);
            }
            scanf("%d", &rIndex);
            if (rIndex < 1 || rIndex > roommateCount)
            {
                printf("Invalid number.\n");
                continue;
            }
            rIndex--;

            printf("\nExpenses for %s:\n", roommateNames[rIndex]);
            if (expenseCounts[rIndex] == 0)
            {
                printf("No expenses found.\n");
            }
            else
            {
                for (int j = 0; j < expenseCounts[rIndex]; j++)
                {
                    printf("  Expense %d: %.2f\n", j + 1, expenses[rIndex][j]);
                }
            }
        }
        else if (choice == 4)
        {
            int rIndex;
            printf("Enter roommate number to edit last expense:\n");
            for (int i = 0; i < roommateCount; i++)
            {
                printf("%d. %s\n", i + 1, roommateNames[i]);
            }
            scanf("%d", &rIndex);
            if (rIndex < 1 || rIndex > roommateCount)
            {
                printf("Invalid number.\n");
                continue;
            }
            rIndex--;

            if (expenseCounts[rIndex] == 0)
            {
                printf("No expenses to edit for %s.\n", roommateNames[rIndex]);
            }
            else
            {
                float old = expenses[rIndex][expenseCounts[rIndex] - 1];
                printf("Last expense for %s is %.2f\n", roommateNames[rIndex], old);
                float newAmount;
                printf("Enter new amount: ");
                scanf("%f", &newAmount);
                expenses[rIndex][expenseCounts[rIndex] - 1] = newAmount;
                totals[rIndex] = totals[rIndex] - old + newAmount;
                printf("Last expense updated!\n");
            }
        }
        else if (choice == 5)
        {
            int rIndex;
            printf("Select roommate to clear all expenses:\n");
            for (int i = 0; i < roommateCount; i++)
            {
                printf("%d. %s\n", i + 1, roommateNames[i]);
            }
            scanf("%d", &rIndex);
            if (rIndex < 1 || rIndex > roommateCount)
            {
                printf("Invalid number.\n");
                continue;
            }
            rIndex--;

            expenseCounts[rIndex] = 0;
            totals[rIndex] = 0;
            printf("All expenses cleared for %s.\n", roommateNames[rIndex]);
        }
        else if (choice == 6)
        {
            float grandTotal = 0;
            for (int i = 0; i < roommateCount; i++)
            {
                grandTotal += totals[i];
            }

            float share = grandTotal / roommateCount;

            printf("\n===== EXPENSE SUMMARY =====\n");
            printf("Total group expense: %.2f\n", grandTotal);
            printf("Each roommate should pay: %.2f\n\n", share);

            for (int i = 0; i < roommateCount; i++)
            {
                printf("%s spent: %.2f\n", roommateNames[i], totals[i]);

                if (totals[i] > share)
                {
                    printf("-> %s should receive %.2f\n", roommateNames[i], totals[i] - share);
                }
                else if (totals[i] < share)
                {
                    printf("-> %s should pay %.2f\n", roommateNames[i], share - totals[i]);
                }
                else
                {
                    printf("-> %s is settled up.\n", roommateNames[i]);
                }
                printf("--------------------------\n");
            }
        }
        else if (choice == 7)
        {
            char confirm;
            printf("Are you sure you want to quit? (y/n): ");
            scanf(" %c", &confirm);
            if (confirm == 'y' || confirm == 'Y')
            {
                printf("Goodbye!\n");
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }

    } while (1);

    return 0;
}