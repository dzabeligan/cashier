#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cashier.h"
#include "utils.h"
#include "ezxml.h"

#define ID_LENGTH 12

/**********************************************************
 * skipLine: skips to end of line                         *
 *********************************************************/
void skipLine(void)
{
    while (getchar() != '\n')
      ;
}

/**********************************************************
 * printCommand: Prints the available commands to console*
 *********************************************************/
void printCommand(void)
{
  printf(
      "\n a - add cashier,"
      "\n r - remove cashier,"
      "\n s - suspend cashier,"
      "\n e - edit cashier"
      "\n t - traverse cashiers"
      "\n x - terminate program\n");
}

/**********************************************************
 * generate_id: Generates random 12-digit long integers. *
 *********************************************************/
ID generateID(void)
{
    srand(time(NULL));

    // generate 12 digit long numbers
    return ((ID)rand() * time(NULL) % 100) % 1000000000000;
}

/**********************************************************
 * generate_id: Generates random 12-digit long integers. *
 *********************************************************/
void printCashier(const cashier *c)
{
    ezxml_t cashier = ezxml_new("cashier");
    ezxml_t id = ezxml_add_child(cashier, "id", 0);
    ezxml_t firstName = ezxml_add_child(cashier, "firstName", 0);
    ezxml_t lastName = ezxml_add_child(cashier, "lastName", 0);
    
    char idAsString[ID_LENGTH];
    sprintf(idAsString, "%ld", c->id);

    ezxml_set_txt(id, idAsString);
    ezxml_set_txt(firstName, c->firstName);
    ezxml_set_txt(lastName, c->lastName);

    ezxml_set_attr(cashier, "suspended", c->suspended ? "true" : "false");

    printf("%s", ezxml_toxml(cashier));

    ezxml_free(cashier);
}