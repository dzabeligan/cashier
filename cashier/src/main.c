/* cashier management app
*  uses libexpat or ezxml library
*   
*   1. Add Cashier.
*   2. Remove cashier.
*   3. Suspend cashier.//add another field to suspend
*   4. Traverse cashier.
*   5. Edit Cashier.
*/
#include <stdio.h>

#include "ezxml.h"
#include "cashier.h"
#include "utils.h"

int main(void)
{
    printf("Hello, Welcome to the Cashier Database Management System!\n");
    printCommand();

    char command;

    for (;;)
    {
        printf("\nPress key 'm' to see command menu.\n");
        printf("Enter an option: ");

        command = getchar();

        skipLine();

        switch (command)
        {
        case 'a':
        case 'A':
            addCashier();
            break;

        case 'r':
        case 'R':
            removeCashier();
            break;

        case 's':
        case 'S':
            suspendCashier();
            break;

        case 't':
        case 'T':
            traverseCashier();
            break;

        case 'e':
        case 'E':
            editCashier();
            break;

        case 'm':
        case 'M':
            printCommand();
            break;

        case 'x':
        case 'X':
            freeCashier();
            return 0;

        default:
            printCommand();
            printf("\nIncorrect option entered, please try again!\n");
        }
    }
}
