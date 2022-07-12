#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum SearchType
{
    ROUTE = 1,
    ORIGIN,
    DESTINATION,
    AIRLINE,
    QUIT,
} SearchType;

typedef struct RouteRecord_struct
{
    char origin[4];
    char destination[4];
    char airline[4];
    int passengers[7];
} RouteRecord;

int checkFileOpening(FILE *inputFile)
{
    int output = 0;

    if (inputFile == NULL)
    {
        printf("Error\n");
        output = -1;
    }
return output;
}

int getFileLength(FILE *inputFile)
{
    int output;
    char buffer[1000];
    while (!feof(inputFile) && output != -1)
        {
            fgets(buffer, 1000, inputFile);
    output++;
    }
    rewind(inputFile);
    return output;
}

RouteRecord *createRecords(FILE *inputFile)
{
    RouteRecord *flights;
    int fileLength = getFileLength(inputFile);
    fileLength -= checkCSVHeader(inputFile);
    flights = (RouteRecord *)malloc(sizeof(RouteRecord) * fileLength);
    return flights;
}
void stringUpper(char *lowered)
{
    int i;
    for (i = 0; i < strlen(lowered); i++)
        {
            lowered[i] = toupper(lowered[i]);
        }
}

int checkCSVHeader(FILE *inputFile)
{
    char buffer[1000];
    fgets(buffer, 1000, inputFile);
    char tester[5];
    sscanf(buffer, "%5[^,]", tester);
    stringUpper(tester);
    if (strcmp(tester, "MONTH") == 0)
        {
            rewind(inputFile);
    return 1;
    }
    rewind(inputFile);

return 0;
}

int fillRecords(RouteRecord *flights, FILE *inputFile)
{
    int month;
    char origin[4];
    char destination[4];
    char airline[4];
    char flightType[20];
    int passengers;

    char buffer[1000];
    int flightsLength = 0;
    int flightIndex;
    int passengersIndex;

    int fileLength = getFileLength(inputFile);
    int i = checkCSVHeader(inputFile);

    if (i == 1)
        {
            fgets(buffer, 1000, inputFile);
        }

        while (i < fileLength && !feof(inputFile))
            {
                fgets(buffer, 1000, inputFile);
        sscanf(buffer, "%d,%3[^,],%3[^,],%3[^,],%20[^,],%d", &month, origin, destination, airline, flightType, &passengers);
        if (strlen(airline) != 3)
            {
                flightIndex = findAirlineRoute(flights, flightsLength, origin, destination, airline);
        if (flightIndex == -1
            {
                strcpy((*(flights + flightsLength)).origin, origin);
                strcpy((*(flights + flightsLength)).destination, destination);
                strcpy((*(flights + flightsLength)).airline, airline);
                for (passengersIndex = 0; passengersIndex < 6; passengersIndex++)
                    {
                        (*(flights + flightsLength)).passengers[passengersIndex] = 0;
        }
        (*(flights + flightsLength)).passengers[month - 1] = passengers;
        flightsLength++;
        }
        else
            {
                (*(flights + flightIndex)).passengers[month - 1] = passengers;
            }
        }
    i++;
    }

    printf("Unique routes operated by airlines: %d\n", flightsLength);

    return flightsLength;
}

int findAirlineRoute(RouteRecord *flights, int flightsLength, char *origin, char *destination, char *airline)
{
    int test = -1;
    int i = 0;
    while (i < flightsLength && test == -1)
        {
            RouteRecord compare = (*(flights + i));
    if (strcmp(compare.origin, origin) == 0)
        {
            if (strcmp(compare.destination, destination) == 0)
            {
                if (strcmp(compare.airline, airline) == 0)
                {
                    test = i;
                    }
                }
            }
        i++;
    }
    return test;
}

void printMenu()
{
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");
}

SearchType getMenuOption(char *key1, char *key2)
{
        printMenu();
        int searchKind;
        int checker;
        char buf[100];

    do
    {
        checker = scanf("%d", &searchKind);
        while (checker == 0)
            {
            printf("Invalid choice\n");
            printf("Please enter an INTEGER: ");
            fgets(buf, 100, stdin);
            checker = scanf("%d", &searchKind);
            }

            switch (searchKind)
            {
            case ROUTE:
                printf("Enter origin: ");
                scanf("%s", key1);
                printf("Enter destination: ");
                scanf("%s", key2);
                break;

            case ORIGIN:
                printf("Enter origin: ");
                scanf("%s", key1);
                break;

            case DESTINATION:
                printf("Enter destination: ");
                scanf("%s", key1);
                break;

            case AIRLINE:
                printf("Enter airline: ");
                scanf("%s", key1);
                break;

            case QUIT:
                break;

            default:
                printf("Invalid choice\n");
                printf("Please select an option from 1 to 5: ");
                break;
            }
    } while (searchKind != ROUTE && searchKind != ORIGIN && searchKind != DESTINATION && searchKind != AIRLINE && searchKind != QUIT);
return searchKind;
}

void searchRecords(RouteRecord *flights, int flightsLength, char *key1, char *key2, SearchType searchKind)
{
    int i;
    int j;
    int matches = 0;
    RouteRecord *compare;

    int totalPassengers[6] = {0, 0, 0, 0, 0, 0};
    printf("\n");
    switch (searchKind)
    {
            case ROUTE:
                printf("Searching by route...\n");
                for (i = 0; i < flightsLength; i++)
                {
                    if (strcmp(flights[i].origin, key1) == 0 && strcmp(flights[i].destination, key2) == 0)
                    {
                        matches++;
                        printf("%s (%s-%s) ", flights[i].airline, flights[i].origin, flights[i].destination);
                        for (j = 0; j < 6; j++)
                        {
                            (totalPassengers[j]) += flights[i].passengers[j];
                        }
                        if (i == 10)
                        {
                            printf("\n");
                        }
                    }
                }
                break;

            case ORIGIN:
                printf("Searching by origin...\n");
                for (i = 0; i < flightsLength; i++)
                    {
                        if (strcmp(flights[i].origin, key1) == 0)
                            {
                                matches++;
                                printf("%s (%s-%s) ", flights[i].airline, flights[i].origin, flights[i].destination);

                                for (j = 0; j < 6; j++)
                                {
                                        (totalPassengers[j]) += flights[i].passengers[j];
                                }
                                if (i == 10)
                                {
                                    printf("\n");
                                }
                            }
                        }
                        break;

            case DESTINATION:
                printf("Searching by destination...\n");
                for (i = 0; i < flightsLength; i++)
                    {
                        if (strcmp(flights[i].destination, key1) == 0)
                        {
                            matches++;
                            printf("%s (%s-%s)", flights[i].airline, flights[i].origin, flights[i].destination);
                            for (j = 0; j < 6; j++)
                                {
                                    totalPassengers[j] += flights[i].passengers[j];
                            }
                            if (i == 10)
                                {
                                    printf("\n");
                                }
                            }
                        }
                        break;

            case AIRLINE:
                printf("Searching by airline...\n");
                for (i = 0; i < flightsLength; i++)
                    {
                        if (strcmp(flights[i].airline, key1) == 0)
                        {
                            printf("%s (%s-%s)", flights[i].airline, flights[i].origin, flights[i].destination);
                            for (j = 0; j < 6; j++)
                            {
                                    totalPassengers[j] += flights[i].passengers[j];
                            }
                            if (i == 10)
                            {
                                printf("\n");
                            }
                        }
                    }
                    break;

    default:
    break;
    }
    printf("\n%d matches were found.\n", matches);
    printf("\n");
    printf("Statistics\n");

    int totaltotal = totalPassengers[0] + totalPassengers[1] + totalPassengers[2] + totalPassengers[3] + totalPassengers[4] + totalPassengers[5];
    printf("Total Passengers: %d\n", totaltotal);
    for (i = 0; i < 6; i++)
        {
            printf("Total Passengers in Month %d: %d\n", i + 1,totalPassengers[i]);
        }
    printf("\n");
    printf("Average Passengers per Month: %d\n", totaltotal / 6);
    printf("\n");
}
