#include <stdio.h>

#include "ezxml.h"
#include "cashier.h"
#include "utils.h"

cashier *firstCashier = NULL;

cashier *findCashier(const ID id)
{
    cashier *c;

    for (c = firstCashier; c != NULL && id != c->id; c = c->next)
        ;

    return c;
}

void addCashier(void)
{
    cashier *newCashier;

    newCashier = malloc(sizeof(cashier));
    if (newCashier == NULL)
    {
        printf("\nDatabase is full; can't add more cashiers.\n");
        return;
    }

    newCashier->next = firstCashier;
    if (firstCashier != NULL)
        firstCashier->previous = newCashier;
    firstCashier = newCashier;
    newCashier->previous = NULL;

    ID id;

    do
    {
        id = generateID();
    } while (findCashier(id) != NULL);

    newCashier->id = id;

    printf("Enter first name: ");
    scanf("%s", newCashier->firstName);

    printf("Enter last name: ");
    scanf("%s", newCashier->lastName);

    newCashier->suspended = false;

    skipLine();

    printCashier(newCashier);
}

void removeCashier(void)
{
    ID id;
    cashier *c;

    printf("Enter ID: ");
    scanf(" %ld", &id);

    skipLine();

    c = findCashier(id);
    if (c != NULL)
    {
        char affirm;
        printf("\nAre you sure you want to delete this transaction?\n y/n\n");
        affirm = getchar();

        skipLine();

        switch (affirm)
        {
        case 'y':
        case 'Y':
            if (c->previous != NULL)
                c->previous->next = c->next;

            if (c->next != NULL)
                c->next->previous = c->previous;

            free(c);
            printf("\nCashier deleted successfully.\n");
            break;

        default:
            break;
        }
    }
    else
        printf("\nCashier not found.\n");
}

void suspendCashier(void)
{
    ID id;
    cashier *c;

    printf("Enter ID: ");
    scanf(" %ld", &id);

    skipLine();

    c = findCashier(id);
    if (c != NULL)
    {
        printf("\nAre you sure you want to %s cashier?\ny/n\n\n", c->suspended ? "unsuspend" : "suspend");
        char affirm = getchar();

        skipLine();

        switch (affirm)
        {
        case 'y':
        case 'Y':
            c->suspended = !c->suspended;
            break;

        default:
            break;
        }

        printCashier(c);
    }
    else
        printf("\nCashier not found\n");
}

void editCashier(void)
{
    ID id;
    cashier *c;

    printf("Enter ID: ");
    scanf(" %ld", &id);

    skipLine();

    c = findCashier(id);
    if (c != NULL)
    {
        char command;
        printf("\nWhat would you like to update?\n");
        printf("1 - first name\n");
        printf("2 - last name\n");

        command = getchar();

        skipLine();

        switch (command)
        {
        case '1':
            scanf("%s", c->firstName);
            skipLine();
            break;

        case '2':
            scanf("%s", c->lastName);
            skipLine();
            break;

        default:
            printf("\ninvalid command\n");
            break;
        }

        printCashier(c);
    }
    else
        printf("\nCashier not found\n");
}

void traverseCashier(void)
{
    cashier *c;
    char move;

    c = firstCashier;

    if (c != NULL)
        printCashier(c);
    else
    {
        printf("There are no cashiers stored\n");
        return;
    }

    for (;;)
    {
        printf("\n\nb - to move back, f - to move forward, m - to go back to menu\n");
        printf("Enter an option: ");
        move = getchar();
        skipLine();

        switch (move)
        {
        case 'b':
        case 'B':
            if (c->previous != NULL)
                c = c->previous;
            else
                printf("\nThis is the first element in the list\n\n");
            break;

        case 'f':
        case 'F':
            if (c->next != NULL)
                c = c->next;
            else
                printf("\nThis is the last element in the list\n\n");
            break;

        case 'm':
        case 'M':
            return;

        default:
            printf("\nInvalid input\n");
            break;
        }

        printCashier(c);
    }
}

/**********************************************************
 * freeCashier: Frees memory allocated for cashiers       *   
 *********************************************************/
void freeCashier(void)
{
    while (firstCashier != NULL)
    {
        cashier *currentCashier = firstCashier;
        firstCashier = firstCashier->next;
        free(currentCashier);
    }
}
