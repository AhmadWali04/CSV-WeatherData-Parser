#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXCHAR 1000

/*
Note to the user, run the program via the main.exe file as errors may occur when running from code editor due to compiler issues
*/

size_t capacity = 2;
size_t count = 0;

typedef struct{ // Struct to store ClimateRecord data
    char date[15];
    int maxGust;
    float precip;
    float minTemp;
    float maxTemp;
    float meanTemp;
} ClimateRecord;

void findHighestPrecip(ClimateRecord *records); // Initialize functions
void findHighestSpeed(ClimateRecord *records); 
void findHighestFluc(ClimateRecord *records);
void printAverageMonthPrecip(ClimateRecord *records);
void printAverageMonthSpeed(ClimateRecord *records);
void printAverageMeanTemp(ClimateRecord *records);
void printMonthMinTemp(ClimateRecord *records);
void printMonthMaxTemp(ClimateRecord *records); 
void displayDataRange(ClimateRecord *records, char *start, char *end);

void findHighestPrecip(ClimateRecord *records) { // Function to find month with highest precipitation level
    char *ptr;
    char buffer[15];
    char currentMonth[8]; 
    char month[8];
    char highestMonth[8];
    float highestPrecip = records[0].precip;
    float newPrecip = highestPrecip;

    strcpy(buffer, records[0].date); // Code block to isolate a string in the form YYYY/MM, stores string in "currentMonth"
    ptr = strtok(buffer, "-");
    strcpy(currentMonth, ptr);
    strcat(currentMonth, "-");
    ptr = strtok(NULL, "-");
    strcat(currentMonth, ptr);
    strcpy(highestMonth, currentMonth);

    size_t i = 1;
    strcpy(buffer, records[i].date);
    while (i < count) {
        ptr = strtok(buffer, "-"); 
        strcpy(currentMonth, ptr);
        strcat(currentMonth, "-");
        strcpy(month, ptr);
        strcat(month, "-");
        ptr = strtok(NULL, "-");
        strcat(currentMonth, ptr);
        strcat(month, ptr);
        while ((strcmp(currentMonth, month) == 0) && i < count-1) {
            newPrecip += records[i].precip;
            i += 1;
            strcpy(buffer, records[i].date);
            ptr = strtok(buffer, "-");
            strcpy(month, ptr);
            strcat(month, "-");
            ptr = strtok(NULL, "-");
            strcat(month, ptr);
        }
        if (newPrecip > highestPrecip) {
            highestPrecip = newPrecip;
            strcpy(highestMonth, currentMonth);
        }
        newPrecip = records[i].precip;
        strcpy(buffer, records[i].date);
        i += 1;
    }
    printf("The highest total precipitation of a month was %.1f and occurred in the month of %s\n", highestPrecip, highestMonth);
}

void findHighestSpeed(ClimateRecord *records){ // Function to find the day with the highest max gust speed
    char *ptr;
    char buffer[15];
    char currentDate[15]; 
    int highestSpeed = records[0].maxGust;
    strcpy(currentDate, records[0].date);
    for (size_t i = 1; i < count; i++) {
        if (records[i].maxGust > highestSpeed) {
            highestSpeed = records[i].maxGust;
            strcpy(currentDate, records[i].date);
        }
    }
    ptr = strtok(currentDate, " ");
    strcpy(currentDate, ptr);
    printf("The highest max gust speed was %d and occurred on %s\n", highestSpeed, currentDate);
}

void findHighestFluc(ClimateRecord *records){ // Function to find the day with the highest temperature fluctuation
    char *ptr;
    char buffer[15];
    char currentDate[15]; 
    float highestFluc = records[0].maxTemp - records[0].minTemp;
    strcpy(currentDate, records[0].date);
    for (size_t i = 1; i < count; i++) {
        if ((records[i].maxTemp - records[i].minTemp) > highestFluc) {
            highestFluc = records[i].maxTemp - records[i].minTemp;
            strcpy(currentDate, records[i].date);
        }
    }
    ptr = strtok(currentDate, " ");
    strcpy(currentDate, ptr);
    printf("The largest temperature fluctuation was %.1f and occurred on %s\n", highestFluc, currentDate);
}

void printAverageMonthPrecip(ClimateRecord *records) {
    printf("Date\tAvg Precipitation\n");
    printf("-----------------\n");
    float precipitation = 0;
    int amount = 0;
    char *ptr;
    char buffer[15];
    char currentMonth[8]; 
    char month[8];
    strcpy(buffer, records[0].date); // Code block to isolate a string in the form YYYY/MM, stores string in "currentMonth"
    ptr = strtok(buffer, "-");
    strcpy(currentMonth, ptr);
    strcat(currentMonth, "-");
    ptr = strtok(NULL, "-");
    strcat(currentMonth, ptr);

    for (size_t i = 0; i < count; i++) {
        strcpy(buffer, records[i].date); 
        ptr = strtok(buffer, "-"); // Code block to set month string to the next date's month
        strcpy(month, ptr);
        strcat(month, "-");
        ptr = strtok(NULL, "-");
        strcat(month, ptr);
        if (strcmp(month, currentMonth) == 0) { // Retains currentMonth information of the previous date and compares with the new one to see if a new precipitation and amount should be created
            precipitation += records[i].precip; // Increment precipitation for this month
            amount += 1;
        }
        else {
            printf("%s\t%.2f\n", currentMonth, precipitation/amount); // Print precipitation and currentMonth information of the previous month entry
            precipitation = 0; // Reset precipitation and amount variables to prepare for next month's data.
            amount = 0;
        }
        strcpy(buffer, records[i].date); // Code block to reset current month to the previous date's month
        ptr = strtok(buffer, "-");
        strcpy(currentMonth, ptr);
        strcat(currentMonth, "-");
        ptr = strtok(NULL, "-");
        strcat(currentMonth, ptr);
    }
}

void printAverageMonthSpeed(ClimateRecord *records) {
    printf("Date\tAvg Max Gust Speed\n");
    printf("-----------------\n");
    float speed = 0;
    int amount = 0;
    char *ptr;
    char buffer[15];
    char currentMonth[8]; 
    char month[8];
    strcpy(buffer, records[0].date); // Code block to isolate a string in the form YYYY/MM, stores string in "currentMonth"
    ptr = strtok(buffer, "-");
    strcpy(currentMonth, ptr);
    strcat(currentMonth, "-");
    ptr = strtok(NULL, "-");
    strcat(currentMonth, ptr);

    for (size_t i = 0; i < count; i++) {
        strcpy(buffer, records[i].date); 
        ptr = strtok(buffer, "-"); // Code block to set month string to the next date's month
        strcpy(month, ptr);
        strcat(month, "-");
        ptr = strtok(NULL, "-");
        strcat(month, ptr);
        if (strcmp(month, currentMonth) == 0) { // Retains currentMonth information of the previous date and compares with the new one to see if a new speed and amount should be created
            speed += records[i].maxGust; // Increment speed for this month
            amount += 1;
        }
        else {
            printf("%s\t%.2f\n", currentMonth, speed/amount); // Print speed and currentMonth information of the previous month entry
            speed = 0; // Reset speed and amount variables to prepare for next month's data.
            amount = 0;
        }
        strcpy(buffer, records[i].date); // Code block to reset current month to the previous date's month
        ptr = strtok(buffer, "-");
        strcpy(currentMonth, ptr);
        strcat(currentMonth, "-");
        ptr = strtok(NULL, "-");
        strcat(currentMonth, ptr);
    }
}

void printAverageMeanTemp(ClimateRecord *records) {
    printf("Date\tAvg Mean Temp\n");
    printf("-----------------\n");
    float temp = 0;
    int amount = 0;
    char *ptr;
    char buffer[15];
    char currentMonth[8]; 
    char month[8];
    strcpy(buffer, records[0].date); // Code block to isolate a string in the form YYYY/MM, stores string in "currentMonth"
    ptr = strtok(buffer, "-");
    strcpy(currentMonth, ptr);
    strcat(currentMonth, "-");
    ptr = strtok(NULL, "-");
    strcat(currentMonth, ptr);

    for (size_t i = 0; i < count; i++) {
        strcpy(buffer, records[i].date); 
        ptr = strtok(buffer, "-"); // Code block to set month string to the next date's month
        strcpy(month, ptr);
        strcat(month, "-");
        ptr = strtok(NULL, "-");
        strcat(month, ptr);
        if (strcmp(month, currentMonth) == 0) { // Retains currentMonth information of the previous date and compares with the new one to see if a new mean temp and amount should be created
            temp += records[i].meanTemp; // Increment mean temp for this month
            amount += 1;
        }
        else {
            printf("%s\t%.1f\n", currentMonth, temp/amount); // Print mean temp and currentMonth information of the previous month entry
            temp = 0; // Reset mean temp and amount variables to prepare for next month's data.
            amount = 0;
        }
        strcpy(buffer, records[i].date); // Code block to reset current month to the previous date's month
        ptr = strtok(buffer, "-");
        strcpy(currentMonth, ptr);
        strcat(currentMonth, "-");
        ptr = strtok(NULL, "-");
        strcat(currentMonth, ptr);
    }
}

void printMonthMinTemp(ClimateRecord *records) {
    printf("Date\tMin Temp\n");
    printf("-----------------\n");
    float temp = 0;
    char *ptr;
    char buffer[15];
    char currentMonth[8]; 
    char month[8];
    strcpy(buffer, records[0].date); // Code block to isolate a string in the form YYYY/MM, stores string in "currentMonth"
    ptr = strtok(buffer, "-");
    strcpy(currentMonth, ptr);
    strcat(currentMonth, "-");
    ptr = strtok(NULL, "-");
    strcat(currentMonth, ptr);

    for (size_t i = 0; i < count; i++) {
        strcpy(buffer, records[i].date); 
        ptr = strtok(buffer, "-"); // Code block to set month string to the next date's month
        strcpy(month, ptr);
        strcat(month, "-");
        ptr = strtok(NULL, "-");
        strcat(month, ptr);
        if (strcmp(month, currentMonth) == 0) { // Retains currentMonth information of the previous date and compares with the new one to see if a new minimum temperature should be examined.
            if (temp > records[i].minTemp) {
                temp = records[i].minTemp;
            }
        }
        else {
            printf("%s\t%.1f\n", currentMonth, temp); // Print minimum temperature and currentMonth information of the previous month entry
            temp = records[i].minTemp; // Reset minimum temperature and amount variables to prepare for next month's data.
        }
        strcpy(buffer, records[i].date); // Code block to reset current month to the previous date's month
        ptr = strtok(buffer, "-");
        strcpy(currentMonth, ptr);
        strcat(currentMonth, "-");
        ptr = strtok(NULL, "-");
        strcat(currentMonth, ptr);
    }
}

void printMonthMaxTemp(ClimateRecord *records) {
    printf("Date\tMax Temp\n");
    printf("-----------------\n");
    float temp = 0;
    char *ptr;
    char buffer[15];
    char currentMonth[8]; 
    char month[8];
    strcpy(buffer, records[0].date); // Code block to isolate a string in the form YYYY/MM, stores string in "currentMonth"
    ptr = strtok(buffer, "-");
    strcpy(currentMonth, ptr);
    strcat(currentMonth, "-");
    ptr = strtok(NULL, "-");
    strcat(currentMonth, ptr);

    for (size_t i = 0; i < count; i++) {
        strcpy(buffer, records[i].date); 
        ptr = strtok(buffer, "-"); // Code block to set month string to the next date's month
        strcpy(month, ptr);
        strcat(month, "-");
        ptr = strtok(NULL, "-");
        strcat(month, ptr);
        if (strcmp(month, currentMonth) == 0) { // Retains currentMonth information of the previous date and compares with the new one to see if a new maximum temperature should be examined.
            if (temp < records[i].maxTemp) {
                temp = records[i].maxTemp;
            }
        }
        else {
            printf("%s\t%.1f\n", currentMonth, temp); // Print maximum temperature and currentMonth information of the previous month entry
            temp = records[i].maxTemp; // Reset maximum temperature and amount variables to prepare for next month's data.
        }
        strcpy(buffer, records[i].date); // Code block to reset current month to the previous date's month
        ptr = strtok(buffer, "-");
        strcpy(currentMonth, ptr);
        strcat(currentMonth, "-");
        ptr = strtok(NULL, "-");
        strcat(currentMonth, ptr);
    }
}

void displayDataRange(ClimateRecord *records, char *start, char *end) {
    printf("Date\t\tMax Gust Speed\tPrecipitation\t\tMin Temp\tMax Temp\tMean Temp\n");
    printf("------------------------------------------------------------------------------------------------\n");
    int begin = 0;
    size_t i = 0;
    char *ptr;
    char buffer[15];
    char currentDate[15]; 
    while ((begin == 0) && i < count) {
        strcpy(buffer, records[i].date); // Code block to isolate a string in the form YYYY/MM/DD, stores string in "currentDate"
        ptr = strtok(buffer, " ");
        strcpy(currentDate, ptr);
        if (strcmp(currentDate, start) >= 0) {
            begin = 1;
            printf("%s\t\t%d\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", records[i].date, records[i].maxGust, records[i].precip, records[i].minTemp, records[i].maxTemp, records[i].meanTemp);
        }
        i += 1;
    }
    strcpy(buffer, records[i].date);
    ptr = strtok(buffer, " ");
    strcpy(currentDate, ptr);
    if (strcmp(currentDate, end) >= 0) {
        begin = 0;
    }
    while ((begin == 1) && i < count) {
        printf("%s\t\t%d\t\t%.1f\t\t%.1f\t\t%.1f\t\t%.1f\n", records[i].date, records[i].maxGust, records[i].precip, records[i].minTemp, records[i].maxTemp, records[i].meanTemp);
        strcpy(buffer, records[i].date);
        ptr = strtok(buffer, " ");
        strcpy(currentDate, ptr);
        if (strcmp(currentDate, end) >= 0) {
            begin = 0;
        }
        i += 1;
    }
}

int main() {
    ClimateRecord *records;
    records = malloc(sizeof(ClimateRecord) * capacity); // Initially allocate enough memory for 2 Climate Records

    char row[MAXCHAR];
    char *ptr;
    char buffer[MAXCHAR];
    FILE *fp;
    int isValid = 1;
    char start[15];
    char end[15];
    clock_t startClock, endClock;
    double cpu_time_used;

    fp = fopen("climate-daily.csv", "r");
    fgets(row, MAXCHAR, fp);
    while(fgets(row, MAXCHAR, fp)) {
        isValid = 1;
        strcpy(buffer, row);
        ptr = strtok(buffer, ",");
        for (int i = 0; i < 5; i++) { // Search for invalid entry in the row
            if (!(ptr = strtok(NULL, ","))) { // If invalid entry is found set isValid to 0 which will prevent that entry from being stored in the list
                isValid = 0;
            }
        }
        if (isValid == 1) { 
            ptr = strtok(row, ","); // Code block for storing the row data into a struct which goes into the dynamic list records.
            strcpy(records[count].date, ptr);
            ptr = strtok(NULL, ",");
            records[count].maxGust = atoi(ptr);
            ptr = strtok(NULL, ",");
            records[count].precip = atof(ptr);
            ptr = strtok(NULL, ",");
            records[count].minTemp = atof(ptr);
            ptr = strtok(NULL, ",");
            records[count].maxTemp = atof(ptr);
            ptr = strtok(NULL, ",");
            records[count].meanTemp = atof(ptr);
            count += 1;
            if (count >= capacity-1) { // When the amount of ClimateRecords in records list is close to the capacity, double the capacity and reallocate more memory for the list.
                capacity = capacity*2;
                records = realloc(records, sizeof(ClimateRecord) * capacity);
            }
        }
    }
    findHighestPrecip(records); // Initial function calls to satisfy conditions of task 3
    findHighestSpeed(records);
    findHighestFluc(records);
    int choice;

    printf("\n      1. Average Month Max Gust Speed\n"); // Creating GUI for task 4
    printf("      2. Average Month Precipitation\n");
    printf("      3. Month Minimum Temperature\n");
    printf("      4. Month Maximum Temperature\n");
    printf("      5. Average Month Mean Temperature\n");
    printf("      6. All Weather Records Between A Chosen Start and End Date\n");
    printf("      0. End Program\n");
    printf("\nPlease enter a number to select the type of report generated: ");
    scanf("%d", &choice);
    printf("\n");
    while (choice != 0) { // While loop for task 4
        switch(choice) { // Switch case to continue until 0 is chosen
            case 1:
                startClock = clock();
                printAverageMonthSpeed(records); // Functions for task 4
                endClock = clock();
                cpu_time_used = ((double) (endClock - startClock)) / CLOCKS_PER_SEC;
                printf("Execution time: %f seconds\n", cpu_time_used);
                break;
            case 2:
                startClock = clock();
                printAverageMonthPrecip(records);
                endClock = clock();
                cpu_time_used = ((double) (endClock - startClock)) / CLOCKS_PER_SEC;
                printf("Execution time: %f seconds\n", cpu_time_used);
                break;
            case 3:
                startClock = clock();
                printMonthMinTemp(records);
                endClock = clock();
                cpu_time_used = ((double) (endClock - startClock)) / CLOCKS_PER_SEC;
                printf("Execution time: %f seconds\n", cpu_time_used);
                break;
            case 4:
                startClock = clock();
                printMonthMaxTemp(records);
                endClock = clock();
                cpu_time_used = ((double) (endClock - startClock)) / CLOCKS_PER_SEC;
                printf("Execution time: %f seconds\n", cpu_time_used);
                break;
            case 5:
                startClock = clock();
                printAverageMeanTemp(records);
                endClock = clock();
                cpu_time_used = ((double) (endClock - startClock)) / CLOCKS_PER_SEC;
                printf("Execution time: %f seconds\n", cpu_time_used);
                break;
            case 6:
                isValid = 1; // Validity checks to ensure valid start and end date
                printf("Please enter the start date in the form YYYY-MM-DD: ");
                scanf("%s", &start);
                printf("Please enter the end date in the form YYYY-MM-DD: ");
                scanf("%s", &end);
                if (strcmp(start, end) > 0) { // Check if start is later than end date
                    isValid = 0;
                    printf("Invalid inputs, start date cannot be later than end date\n");
                }
                strcpy(buffer, records[0].date);
                ptr = strtok(buffer, " ");
                if (strcmp(ptr, start) > 0) { // Check if start date is outside of range
                    isValid = 0;
                    printf("Invalid start date, outside of range\n");
                }
                strcpy(buffer, records[count-1].date);
                ptr = strtok(buffer, " ");
                if (strcmp(end, ptr) > 0) { // Check if end date is outside of range
                    isValid = 0;
                    printf("Invalid end date, outside of range\n");
                }
                while (isValid == 0) {
                    isValid = 1;
                    printf("Please enter the start date in the form YYYY-MM-DD: ");
                    scanf("%s", &start);
                    printf("Please enter the end date in the form YYYY-MM-DD: ");
                    scanf("%s", &end);
                    if (strcmp(start, end) > 0) {
                        isValid = 0;
                        printf("Invalid inputs, start date cannot be later than end date\n");
                    }
                    strcpy(buffer, records[0].date);
                    ptr = strtok(buffer, " ");
                    if (strcmp(ptr, start) > 0) {
                        isValid = 0;
                        printf("Invalid start date, outside of range\n");
                    }
                    strcpy(buffer, records[count-1].date);
                    ptr = strtok(buffer, " ");
                    if (strcmp(end, ptr) > 0) {
                        isValid = 0;
                        printf("Invalid end date, outside of range\n");
                    }
                }
                startClock = clock();
                displayDataRange(records, start, end);
                endClock = clock();
                cpu_time_used = ((double) (endClock - startClock)) / CLOCKS_PER_SEC;
                printf("Execution time: %f seconds\n", cpu_time_used);
                break;
            default:
                printf("That is not a valid choice\n");
        }
        printf("\n      1. Average Month Max Gust Speed\n");
        printf("      2. Average Month Precipitation\n");
        printf("      3. Month Minimum Temperature\n");
        printf("      4. Month Maximum Temperature\n");
        printf("      5. Average Month Mean Temperature\n");
        printf("      6. All Weather Records Between A Chosen Start and End Date\n");
        printf("      0. End Program\n");
        printf("\nPlease enter a number to select the type of report generated: ");
        scanf("%d", &choice);
    }
    for (size_t i = 0; i < count; i++) { // Freeing each allocated date memory
        free(records[i].date);
    }
    free(records); // Freeing allocated list memory
    return 0;
}