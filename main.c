#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "routeRecords.h"


int main( int argc, char *argv[])
{
    char inputName[20];
    strcpy(inputName, argv[1]);

    FILE *inputFile;
    printf("Opening data.csv... \n");
    inputFile = fopen(inputName, "data.csv");
    checkFileOpening(inputFile);

    RouteRecord *flights;
    flights = createRecords(inputFile);

    int flightsLength;
    flightsLength = fillRecords(flights, inputFile);


    int i;
    char key1[5];
    char key2[5];
    SearchType searchKind = 0;

    while (searchKind != 5)
    {
    searchKind = getMenuOption(key1, key2);
    stringUpper(key1);
    stringUpper(key2);
    searchRecords(flights, flightsLength, key1, key2, searchKind);
    }

    return 0;
}
