 int bus_number;
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define USERNAME "admin"
#define PASSWORD "@282018"

struct pass {
    char first_name[20];
    char last_name[20];
    long long roll_no;
    char clas[10];
    char vill[20];
    float per;
    int bus_number;
};

struct BusSchedule {
    char source[20];
    char destination[20];
    int charge;
    int no_seats;
    int bus_number;
    char bus_name[30];
    int time;
};

bool busNumbersBooked[7] = {false};
bool seatNumbersBooked[50] = {false};

void bookticket();
void viewrecord();
void delete_record();
void busSchedules();
void addBusSchedules();
void deleteBusSchedules();
void searchBusSchedules();
void clearScreen();

int main() {
    int choice = 0;
    char username[20];
    char password[20];

    printf("Welcome to the Bus Ticket Reservation System\n");

    // Implement a simple login system
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        // Login successful
        printf("Login successful\n");
    } else {
        // Invalid login
        printf("Invalid username or password. Exiting...\n");
        return 1;
    }

    while (choice != 8) {
        clearScreen();
        printf("\t\t=================================================\n");
        printf("\t\t|                                               |\n");
        printf("\t\t|        -----------------------------          |\n");
        printf("\t\t|          BUS TICKET RESERVATION SYSTEM          |\n");
        printf("\t\t|        -----------------------------          |\n");
        printf("\t\t|                                               |\n");
        printf("\t\t|                                               |\n");
        printf("\t\t|                                               |\n");
        printf("\t\t|              BROUGHT TO YOU BY                |\n");
        printf("\t\t|            //   Dennis Kariuki                |\n");
        printf("\t\t|                                               |\n");
        printf("\t\t=================================================\n\n\n");

        printf("\t\t\t\t======BUS RESERVATION SYSTEM====\n");
        printf("\n\n\n\t\t\t1. Book a ticket\n");
        printf("\t\t\t2. View ticket\n");
        printf("\t\t\t3. Delete record\n");
        printf("\t\t\t4. View bus schedules\n");
        printf("\t\t\t5. Search bus schedules\n");
        printf("\t\t\t6. Add bus schedules\n");
        printf("\t\t\t7. Delete bus schedules\n");
        printf("\t\t\t8. Exit\n");
        printf("---------------------------------------------------\n");
        printf("\t\t\t\t ::::");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearScreen();
                bookticket();
                clearScreen();
                break;
            case 2:
                clearScreen();
                viewrecord();
                printf("\t\t\tPress any key to exit\n");
                getchar();
                clearScreen();
                break;
            case 3:
                clearScreen();
                delete_record();
                printf("\t\t\tPress any key to exit\n");
                getchar();
                clearScreen();
                break;
            case 4:
                clearScreen();
                busSchedules();
                printf("\t\t\tPress any key to exit\n");
                getchar();
                clearScreen();
                break;
            case 5:
                clearScreen();
                searchBusSchedules();
                printf("\t\t\tPress any key to exit\n");
                getchar();
                clearScreen();
                break;
            case 6:
                clearScreen();
                addBusSchedules();
                printf("\t\t\tPress any key to exit\n");
                getchar();
                clearScreen();
                break;

            case 7:
                clearScreen();
                deleteBusSchedules();
                printf("\t\t\tPress any key to exit\n");
                getchar();
                clearScreen();
                break;

            case 8:
                clearScreen();
                printf("\n\t\t\tThank you for using this software\n");
                exit(0);
            default:
                clearScreen();
                getchar();
                printf("\t\t\tEnter a valid number\n\n");
                printf("\t\t\tPress any key to continue......\n\n");
                getchar();
                clearScreen();
                break;
        }
    }

    return 0;
}

void bookticket() {
    char another;
    FILE *fp, *passengerFile;
    struct pass info;
    struct BusSchedule busInfo;

    getchar();

    do {
        printf("\n\n\n\n\t\t\t===== Book a ticket====\n\n\n");
        fp = fopen("pass_info.txt", "a");
        passengerFile = fopen("booking_details.txt", "a");  // New file to store booking details

        if (fp == NULL || passengerFile == NULL) {
            printf("Error opening the file for writing\n");
            exit(1);
        }

        printf("\n\t\t\tEnter first name: ");
        scanf("%s", info.first_name);
        printf("\n\t\t\tEnter last name: ");
        scanf("%s", info.last_name);
        printf("\n\t\t\tEnter address: ");
        scanf("%s", info.vill);

        do {
            printf("\n\n\t\tEnter your phone number: +254 ");
            scanf("%lld", &info.roll_no);
            if (info.roll_no < 100000000 || info.roll_no > 999999999 || (info.roll_no / 100000000) != 7) {
                printf("Invalid phone number\n");
            }
        } while (info.roll_no < 100000000 || info.roll_no > 999999999 || (info.roll_no / 100000000) != 7);

        char source[20], destination[20];
        int foundSource = 0, foundDestination = 0;

        do {
            printf("\n\t\t\tEnter source: ");
            scanf("%s", source);

            // Check if the entered source is available in bus schedules
            FILE *busFP = fopen("bus_info.txt", "rb");

            while (fread(&busInfo, sizeof(struct BusSchedule), 1, busFP)) {
                if (strcmp(source, busInfo.source) == 0) {
                    foundSource = 1;
                    break;
                }
            }

            fclose(busFP);

            if (!foundSource) {
                printf("Source not available in bus schedules. Please enter a valid source.\n");
            }
        } while (!foundSource);

        do {
            printf("\n\t\t\tEnter destination: ");
            scanf("%s", destination);

            // Check if the entered destination is available in bus schedules
            FILE *busFP = fopen("bus_info.txt", "rb");

            while (fread(&busInfo, sizeof(struct BusSchedule), 1, busFP)) {
                if (strcmp(destination, busInfo.destination) == 0) {
                    foundDestination = 1;
                    break;
                }
            }

            fclose(busFP);

            if (!foundDestination) {
                printf("Destination not available in bus schedules. Please enter a valid destination.\n");
            }
        } while (!foundDestination);

        // Display bus information
        FILE *busFP = fopen("bus_info.txt", "rb");

        while (fread(&busInfo, sizeof(struct BusSchedule), 1, busFP)) {
            if (strcmp(source, busInfo.source) == 0 && strcmp(destination, busInfo.destination) == 0) {
                printf("\n\t\t\tBus number: %d", busInfo.bus_number);
                printf("\n\t\t\tCharges: %d", busInfo.charge);
                printf("\n\t\t\tTime: %d", busInfo.time);

                // Save booking details to the new file
                fprintf(passengerFile, "Passenger name: %s %s\n", info.first_name, info.last_name);
                fprintf(passengerFile, "Phone number: +254 %lld\n", info.roll_no);
                fprintf(passengerFile, "Bus number: %d\n", busInfo.bus_number);
                fprintf(passengerFile, "Source: %s\n", source);
                fprintf(passengerFile, "Destination: %s\n", destination);
                fprintf(passengerFile, "Charges: %d\n", busInfo.charge);
                fprintf(passengerFile, "Time: %d\n", busInfo.time);
                printf("\n\n");
                break;
            }
        }

        fclose(busFP);

        do {
            printf("\n\t\t\tEnter seat number (1-50): ");
            scanf("%f", &info.per);
            if (info.per < 1 || info.per > 50) {
                printf("Seat number must be between 1 and 50\n");
            }
        } while (info.per < 1 || info.per > 50);

        printf("\n\t\t\t-----------------------------------------");

        printf("\t\t\tRecord stored successfully");
        fwrite(&info, sizeof(struct pass), 1, fp);
        fclose(fp);
        fclose(passengerFile);
        printf("\n\t\t\tDo you want to book another ticket? (y/n) : ");
        scanf(" %c", &another);
    } while (another == 'y' || another == 'Y');
}

void viewrecord() {
    FILE *fp;
    fp = fopen("booking_details.txt", "r");

    printf("\t\t\t========= Booking Details ===\n\n\n\n");

    if (fp == NULL) {
        printf("\t\t\tNo booking details found\n");
        return;
    } else {
        printf("\t\t\tBooking Details\n");
        printf("\t\t\t-----------------------\n\n");
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }

    fclose(fp);

    char choice;
    printf("\n\n\t\t\tDo you want to delete a record? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        delete_record();
    }

    getchar();
}




void delete_record() {
    FILE *fp, *tempFile;
    struct pass info;
    long long roll_no;
    int found = 0;

    printf("\t\t\t========== Delete booking details =====\n\n\n");

    fp = fopen("booking_details.txt", "r");
    tempFile = fopen("temp_booking_details.txt", "w");

    if (fp == NULL || tempFile == NULL) {
        printf("\t\t\tCan't open file\n");
        return;
    }

    printf("\t\t\tEnter phone number to delete: +254 ");
    scanf("%lld", &roll_no);

    // Remove spaces from the entered phone number
    long long storedRollNo; 
 
while (fread(&info, sizeof(struct pass), 1, fp)) {
    if (info.roll_no == roll_no) {  // Compare directly without atoll
        found = 1;
        printf("\n\t\t\tPassenger found:\n");
        printf("\n\t\t\tPassenger name: %s %s", info.first_name, info.last_name);
        printf("\n\t\t\tPhone number: +254 %lld", info.roll_no);
        printf("\n\t\t\tBus number: %d", info.bus_number);
        printf("\n\t\t\tAddress: %s", info.vill);
        printf("\n\t\t\tSeat number: %.2f", info.per);
        printf("\n\t\t\t-----------------------------------------");
        printf("\n\t\t\tDo you want to delete this record? (y/n): ");
        char confirm;
        scanf(" %c", &confirm);
        if (confirm == 'y' || confirm == 'Y') {
            printf("\t\t\tBooking details deleted successfully\n");
        } else {
            fprintf(tempFile, "Passenger name: %s %s\n", info.first_name, info.last_name);
            fprintf(tempFile, "Phone number: +254%lld\n", info.roll_no);  // Use %lld
            fprintf(tempFile, "Bus number: %d\n", info.bus_number);
            fprintf(tempFile, "Address: %s\n", info.vill);
            fprintf(tempFile, "Seat number: %.2f\n", info.per);
        }
    } else {
        fprintf(tempFile, "Passenger name: %s %s\n", info.first_name, info.last_name);
        fprintf(tempFile, "Phone number: +254%lld\n", info.roll_no);  // Use %lld
        fprintf(tempFile, "Bus number: %d\n", info.bus_number);
        fprintf(tempFile, "Address: %s\n", info.vill);
        fprintf(tempFile, "Seat number: %.2f\n", info.per);
    }
}

    fclose(fp);
    fclose(tempFile);

    if (found) {
        remove("booking_details.txt");
        rename("temp_booking_details.txt", "booking_details.txt");
    } else {
        remove("temp_booking_details.txt");
        printf("\t\t\tBooking details not found for the specified phone number.\n");
    }

    getchar();
}



void busSchedules() {
    FILE *fp;
    struct BusSchedule info;

    fp = fopen("bus_info.txt", "rb");

    printf("\t\t\t========= BUS SCHEDULES AND TIMETABLE ===\n\n\n\n");

    if (fp == NULL) {
        printf("\t\t\tCan't open bus schedules\n");
        return;
    } else {
        printf("\t\t\tSchedules\n");
        printf("\n BUS.No\t Bus Name\tSource\t\tDestination\tCharges\t\tTime\tNo of Seats\n");
        printf("\n --------------------------------------------------------------------------------------------");
    }

    while (fread(&info, sizeof(struct BusSchedule), 1, fp)) {
        printf("\n%d\t%s\t\t%s\t\t%s\t\t  %d\t         %d\t     %d\n",
               info.bus_number, info.bus_name, info.source, info.destination, info.charge, info.time, info.no_seats);
    }

    fclose(fp);
    getchar();
}

void addBusSchedules() {
    char option;
    FILE *fp;
    struct BusSchedule info;

    fp = fopen("bus_info.txt", "ab");

    if (fp == NULL) {
        printf("Error opening the file for writing\n");
        exit(1);
    }

    do {
      
            printf("\n\t\t\tEnter bus number : ");
            scanf("%d", &info.bus_number);

          
        printf("\n\t\t\tEnter bus name: ");
        scanf("%s", info.bus_name);
        printf("\n\t\tEnter the source of the bus::");
        scanf("%s", info.source);
        printf("\n\t\tEnter destination of the bus:");
        scanf("%s", info.destination);
        printf("\n\t\tEnter the charges ::");
        scanf("%d", &info.charge);
        printf("\n\t\tEnter time of departure:");
        scanf("%d", &info.time);

        do {
            printf("\n\t\t\tEnter seat number (1-50): ");
            scanf("%d", &info.no_seats);

            if (info.no_seats < 1 || info.no_seats > 50) {
                printf("Seat number must be between 1 and 50\n");
            }
        } while (info.no_seats < 1 || info.no_seats > 50);

        printf("\n\t\t\t-----------------------------------------");
        printf("\t\t\tRecord stored successfully");
        fwrite(&info, sizeof(struct BusSchedule), 1, fp);

        printf("\n\t\t\tDo you want to add another bus? (y/n) : ");
        scanf(" %c", &option);
    } while (option == 'y' || option == 'Y');

    fclose(fp);
}

void deleteBusSchedules() {
    FILE *fp;
    FILE *tempFile;
    struct BusSchedule info;
    int busNumberToDelete;

    printf("\t\t\tEnter the bus number to delete: ");
    scanf("%d", &busNumberToDelete);

    fp = fopen("bus_info.txt", "rb");
    tempFile = fopen("temp_bus_info.txt", "wb");

    if (fp == NULL || tempFile == NULL) {
        printf("Error opening files\n");
        return;
    }

    int found = 0;

    while (fread(&info, sizeof(struct BusSchedule), 1, fp)) {
        if (info.bus_number == busNumberToDelete) {
            found = 1;
        } else {
            fwrite(&info, sizeof(struct BusSchedule), 1, tempFile);
        }
    }

    fclose(fp);
    fclose(tempFile);

    if (found) {
        remove("bus_info.txt");
        rename("temp_bus_info.txt", "bus_info.txt");
        printf("\t\t\tBus schedule with bus number %d has been deleted.\n", busNumberToDelete);
    } else {
        remove("temp_bus_info.txt");
        printf("\t\t\tBus schedule with bus number %d not found.\n", busNumberToDelete);
    }
}

void searchBusSchedules() {
    FILE *fp;
    struct BusSchedule info;
    char searchSource[20];
    char searchDestination[20];

    printf("\t\t\tEnter the source: ");
    scanf("%s", searchSource);
    printf("\t\t\tEnter the destination: ");
    scanf("%s", searchDestination);

    fp = fopen("bus_info.txt", "rb");

    if (fp == NULL) {
        printf("Can't open bus schedules\n");
        return;
    }

    printf("\t\t\t========= SEARCHING BUS SCHEDULES ===\n\n");
    printf("\t\t\tSource: %s, Destination: %s\n", searchSource, searchDestination);
    printf("\n BUS.No\tName\t\t\tSource\t\tDestination\tCharges\tTime\tNo of Seats\n");

    int found = 0;

    while (fread(&info, sizeof(struct BusSchedule), 1, fp)) {
        if (strcmp(info.source, searchSource) == 0 && strcmp(info.destination, searchDestination) == 0) {
            printf("%d\t%s\t\t  %s\t     %s\t\t   %d\t  %d \t      %d\n",
                   info.bus_number, info.bus_name, info.source, info.destination, info.charge, info.time, info.no_seats);
            found = 1;
        }
    }
  if (!found) {
        printf("\t\t\tNo bus schedules found for the specified source and destination.\n");
    }
    fclose(fp);
  getchar();

 }



void clearScreen() {
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Unix-like systems
    #endif
}