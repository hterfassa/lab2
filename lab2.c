#include <stdio.h>
#include <stdlib.h>

// structure for parts
struct Part {
    int partNumber;
    char partName[50];
    float partSize;
    char sizeMetric[10];
    float partCost;
};

// add record function
struct Part* addRecord(struct Part* database, int* numRecords) {
    (*numRecords)++;
    database = (struct Part*)realloc(database, (*numRecords) * sizeof(struct Part));

    if (database == NULL) {
        printf("error: memory failed\n");
        exit(1);
    }

    // get input
    printf("\nEnter Part Number: ");
    scanf("%d", &database[*numRecords - 1].partNumber);

    printf("Enter Part Name: ");
    scanf(" %[^\n]", database[*numRecords - 1].partName); 

    printf("Enter Part Size: ");
    scanf("%f", &database[*numRecords - 1].partSize);

    printf("Enter Size Metric: ");
    scanf("%s", database[*numRecords - 1].sizeMetric);

    printf("Enter Part Cost: ");
    scanf("%f", &database[*numRecords - 1].partCost);

    printf("record added\n");
    return database;
}

// delete last record
struct Part* deleteRecord(struct Part* database, int* numRecords) {
    if (*numRecords == 0) {
        printf("\nnothing to delete\n");
        return database;
    }

    (*numRecords)--;

    if (*numRecords == 0) {
        free(database);
        printf("\nall records deleted\n");
        return NULL;
    }

    database = (struct Part*)realloc(database, (*numRecords) * sizeof(struct Part));

    if (database == NULL && *numRecords > 0) {
        printf("error: memory failed\n");
        exit(1);
    }

    printf("\nlast record deleted\n");
    return database;
}

// print records
void printRecords(struct Part* database, int numRecords) {
    if (numRecords == 0) {
        printf("\nnothing to show\n");
        return;
    }

    printf("\n--- records ---\n");
    for (int i = 0; i < numRecords; i++) {
        printf("record %d:\n", i + 1);
        printf(" part number: %d\n", database[i].partNumber);
        printf(" part name: %s\n", database[i].partName);
        printf(" part size: %.2f %s\n", database[i].partSize, database[i].sizeMetric);
        printf(" part cost: $%.2f\n", database[i].partCost);
        printf("--------------\n");
    }
}

int main() {
    struct Part* database = NULL;
    int numRecords = 0;
    int choice;

    while (1) {
        printf("\nmenu:\n");
        printf("1 - add record\n");
        printf("2 - delete last record\n");
        printf("3 - print records\n");
        printf("4 - exit\n");
        printf("choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                database = addRecord(database, &numRecords);
                break;
            case 2:
                database = deleteRecord(database, &numRecords);
                break;
            case 3:
                printRecords(database, numRecords);
                break;
            case 4:
                free(database);
                printf("\nexit\n");
                return 0;
            default:
                printf("\ninvalid\n");
        }
    }
}
