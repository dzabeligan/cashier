#ifndef CASHIER_H
#define CASHIER_H

#include <stdbool.h>

#define NAME_LENGTH 25

typedef long ID;

typedef struct cashier
{
    ID id;
    bool suspended;
    char firstName[NAME_LENGTH];
    char lastName[NAME_LENGTH];
    struct cashier *previous;
    struct cashier *next;
} cashier;

// prototypes
void addCashier(void);
void removeCashier(void);
void suspendCashier(void);
void traverseCashier(void);
void editCashier(void);
void freeCashier(void);

#endif // CASHIER_H