#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <time.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");
    
    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);
    
    displayFormattedPhone(patient->phone.number);
    
    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// main menu
void menuMain(struct ClinicData* data)
{
    int selection;
    
    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
            case 0:
                printf("Are you sure you want to exit? (y|n): ");
                selection = !(inputCharOption("yn") == 'y');
                putchar('\n');
                if (!selection)
                {
                    printf("Exiting system... Goodbye.\n\n");
                }
                break;
            case 1:
                menuPatient(data->patients, data->maxPatient);
                break;
            case 2:
                menuAppointment(data);
                break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;
    
    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
            case 1:
                displayAllPatients(patient, max, FMT_TABLE);
                suspend();
                break;
            case 2:
                searchPatientData(patient, max);
                break;
            case 3:
                addPatient(patient, max);
                suspend();
                break;
            case 4:
                editPatient(patient, max);
                break;
            case 5:
                removePatient(patient, max);
                suspend();
                break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;
    
    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        
        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }
        
    } while (selection);
}

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;
    
    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
            case 1:
                viewAllAppointments(data);  // ToDo: You will need to create this function!
                suspend();
                break;
            case 2:
                viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
                suspend();
                break;
            case 3:
                addAppointment(data->appointments, data->maxAppointments,
                               data->patients, data->maxPatient);  // ToDo: You will need to create this function!
                suspend();
                break;
            case 4:
                removeAppointment(data->appointments, data->maxAppointments,
                                  data->patients, data->maxPatient);  // ToDo: You will need to create this function!
                suspend();
                break;
        }
    } while (selection);
}


// Display's all patient data in the FMT_FORM | FMT_TABLE format

void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0, count=0 ;
    
    if (fmt == FMT_TABLE) //check what is the 'format' tabular or form.
    {
        displayPatientTableHeader();
    }
    for (i=0; i < max; i++)
    {
        if (patient[i].patientNumber != 0) // Check the patients numbers that are not 0 or (NULL)
        {
            displayPatientData(&patient[i], fmt); // Display the patient that is found by index.
            count++; // incerease counter to check how many result we have
        }
        else {
        }
    }
    if (count == 0)
    {
        printf("*** No records found ***\n"); // if there is nothing to display, show this message.
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number

void searchPatientData(const struct Patient patient[], int max)
{
    int choice=0;
    
    do
    {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n" // Make sure this is .
               "0) Previous menu\n"
               "..........................\n" // Make sure this is .
               "Selection: ");
        
        choice = inputInt(); // Get the choice of search option.
        printf("\n"); // New Line
        switch (choice)
        {
            case 1:
                searchPatientByPatientNumber(patient, max); // Search Patient by Patient Number
                suspend(); // Suspend and ask for ENTER
                break;
            case 2:
                searchPatientByPhoneNumber(patient, max); // Search Patient by Phone Number
                suspend(); // Suspend and ask for ENTER
                break;
        }
    }while(choice != 0);
}

// Add a new patient record to the patient array

void addPatient(struct Patient patient[], int max)
{
    int availableIndex,  nextNumber;
    
    availableIndex = findPatientIndexByPatientNum(0, patient, max);
    
    if (availableIndex == -1) // if there is no space to add patient.
    {
        printf("ERROR: Patient listing is FULL!\n\n"); // display error message
    }
    else
    {
        nextNumber = nextPatientNumber(patient, max); // store next patient number
        patient[availableIndex].patientNumber = nextNumber; // store the next patient's number to its array
        inputPatient(&patient[availableIndex]); // ask for the patient's infromation
        printf("*** New patient record added ***\n\n"); // Display successful message
    }
}


// Edit a patient record from the patient array

void editPatient(struct Patient patient[], int max)
{
    int choice, exist;
    printf("Enter the patient number: "); // prompt the user for the patient number
    choice = inputInt(); // Get the patient number
    exist = findPatientIndexByPatientNum(choice, patient, max); // make sure the patient number exists
    if (exist != -1) // if exists
    {
        printf("\n");
        menuPatientEdit(&patient[exist]); // show the patient edit menu
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n"); // if doesn't exist, show this error
    }
}


// Remove a patient record from the patient array

void removePatient(struct Patient patient[], int max)
{
    int choice, exist, flag = 1;
    char character, lastChar;
    printf("Enter the patient number: "); // prompt the user for the patient number
    choice = inputInt();  // Get the patient number
    exist = findPatientIndexByPatientNum(choice, patient, max); // make sure the patient number exists
    if (exist != -1)  // if exists
    {
        printf("\n");
        displayPatientData(&patient[exist], FMT_FORM); // Display the patient data
        printf("\nAre you sure you want to remove this patient record? (y/n): "); // prompt confirmation
        do
        {
            scanf("%c%c", &character, &lastChar);
            
            if ((character == 'n' || character == 'N') && (lastChar == '\n')) {
                printf("Operation aborted.\n\n");
                flag = 0;
//                clearInputBuffer();
            }
            else if ((character == 'y' || character == 'Y') && (lastChar == '\n')) {
                patient[exist].name[0] = '\0'; // set name to NULL
                patient[exist].patientNumber = 0; // set patient number to NULL
                patient[exist].phone.description[0] = '\0'; // set phone description to NULL
                patient[exist].phone.number[0] = '\0'; // set phone number to NULL
                printf("Patient record has been removed!\n\n"); // show success message
                flag = 0;
            }
            else {
                clearInputBuffer();
                printf("ERROR: Character must be one of [yn]: ");
            }
        }while (flag == 1);
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n"); // show patient not found message
    }
}


// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i = 0, j = 0;
    displayScheduleTableHeader(&data->appointments->date, 1);
    SortAppoints(data->appointments, data->maxAppointments);
    for (i=0; i < data->maxAppointments; i++)
    {
            for (j = 0; j < data->maxPatient; j++)
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                }
            }
            
        }
    printf("\n");
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* data)
{
    int i=0, patientIndex;
    struct Date date;
    
    SortAppoints(data->appointments, data->maxAppointments);

    date = GetDate();
    printf("\n");
    displayScheduleTableHeader(&date, 0);
    for (i=0; i < data->maxAppointments; i++)
    {
        if (date.year == data->appointments[i].date.year && date.month == data->appointments[i].date.month && date.day == data->appointments[i].date.day )
        {
            do
            {
                patientIndex =  findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
                if (patientIndex == -1) {
                    printf("\nERROR: Patient record not found!\n\n");
                }
            }while (patientIndex == -1);
            displayScheduleData(&data->patients[patientIndex], &data->appointments[i], 0);
        }
    }
    printf("\n");
}
// Add an appointment record to the appointment array
int addAppointment(struct Appointment* Appointment, int maxAppointments, struct Patient* patient, int maxPatient)
{
    int i = 0, patientId, validation = 0, arrayIndex;
    struct Date date;
    struct Time time;
    patientId = getPatientNumber(patient, maxPatient);
    if (patientId != -1)
    {
        do {
            date = GetDate();
            time = GetTime();
            validation = 0;
            for (i = 0; i < maxAppointments; i++)
            {
                if (Appointment[i].date.year == date.year)
                {
                    if (Appointment[i].date.month == date.month)
                    {
                        if (Appointment[i].date.day == date.day)
                        {
                            if (Appointment[i].time.hour == time.hour)
                            {
                                if (Appointment[i].time.min == time.min)
                                {
                                    printf("\nERROR: Appointment timeslot is not available!\n\n");
                                    validation = 1;
                                }
                            }
                        }
                    }
                }
            }
            if (validation == 0) {
                arrayIndex = nextAppointIndex(Appointment, maxAppointments);
                Appointment[arrayIndex].date.year = date.year;
                Appointment[arrayIndex].date.month = date.month;
                Appointment[arrayIndex].date.day = date.day;
                Appointment[arrayIndex].time.hour = time.hour;
                Appointment[arrayIndex].time.min = time.min;
                Appointment[arrayIndex].patientNumber = patientId;
                printf("\n*** Appointment scheduled! ***\n\n");
            }
        } while (validation != 0);
    }
    return 0;
}



// Remove an appointment record from the appointment array
int removeAppointment(struct Appointment* Appointment, int maxAppointments, struct Patient* patient, int maxPatient)
{
    int patientId, patientIndex, appointIndex, flag = 1;
    char character, lastChar;
    struct Date date;
    
    patientId = getPatientNumber(patient, maxPatient);
    patientIndex = findPatientIndexByPatientNum(patientId, patient, maxPatient);

    if (patientId != -1)
    {
        date = GetDate();
        printf("\n");
        displayPatientData(&patient[patientIndex], FMT_FORM); // Display the patient data
        printf("Are you sure you want to remove this appointment (y,n): ");
        do
        {
            scanf("%c%c", &character, &lastChar);
            
            if ((character == 'n' || character == 'N') && (lastChar == '\n')) {
                printf("Operation aborted.\n\n");
                flag = 0;
            }
            else if ((character == 'y' || character == 'Y') && (lastChar == '\n')) {
                
                appointIndex = findAppointIndex(patientId, date, Appointment, maxAppointments);
                Appointment[appointIndex].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
                flag = 0;
            }
            else {
                printf("ERROR: Character must be one of [yn]: ");
            }
        }while (flag == 1);
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    return 0;
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)

void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int choice, count = 0, result;
    
    printf("Search by patient number: "); // Prompt the question for patient number
    choice = inputInt(); // Ask for search type
    
    result = findPatientIndexByPatientNum(choice, patient, max);
    
    if (result != -1) //if the patient number is found in the list of patients
    {
        printf("\n"); // New Line
        displayPatientData(&patient[result], FMT_FORM); // Display patient data
        count++; // incerease counter to check how many result we have
    }
    else
    {
        printf("\n*** No records found ***\n"); // if no result is found, display this message.
    }
    printf("\n"); // New Line
}

// Search and display patient records by phone number (tabular)

void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, count = 0;
    
    char choice[PHONE_LEN+1];
    
    printf("Search by phone number: ");// Prompt the question for patient phone number
    
    inputCString(choice, PHONE_LEN, PHONE_LEN); // Ask for search type
    
    printf("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, choice) == 0) //if the patient phone number is found in the list of patients.
        {
            displayPatientData(&patient[i], FMT_TABLE); // display the data in tabular format.
            count++; // incerease counter to check how many result we have.
        }
    }
    if (count == 0)
    {
        printf("\n*** No records found ***\n"); // if no result is found, display this message.
    }
    printf("\n");
}


// Get the next highest patient number

int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, result = 0;
    
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > result) // store the highest patient number in the array.
        {
            result = patient[i].patientNumber; // update the highest patient number.
        }
    }
    
    return result + 1; // return the next number
}


// Find the patient array index by patient number (returns -1 if not found)

int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i, result = -1;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber) //if the patient number is found in the list of patients
        {
            result = i ;
        }
    }
    return result;
}




// Sort the array of Patients
void SortPatients(struct Patient* patients, int max)
{
    int i, j;
    for (i = 0; i < max - 1; i++)
    {
        for (j = 0; j < max - 1 - i; j++)
        {
            if (patients[j].patientNumber > patients[j + 1].patientNumber)
            {
                struct Patient temp;
                temp = patients[j];
                patients[j] = patients[j+1];
                patients[j+1] = temp;
            }
        }
    }
}

// Sort the array of Appointments
void SortAppoints(struct Appointment appoints[], int max)
{
    int i, j;
    struct Appointment temp;
    for (i = 0; i < max - 1; i++)
    {
        for (j = 0; j < max - 1 - i; j++)
        {
            if (appoints[j].patientNumber != 0 && appoints[j + 1].patientNumber != 0){
                if (appoints[j].date.year > appoints[j + 1].date.year)
                {
                    temp = appoints[j];
                    appoints[j] = appoints[j + 1];
                    appoints[j + 1] = temp;
                }
                else if (appoints[j].date.year == appoints[j + 1].date.year)
                {
                    if (appoints[j].date.month > appoints[j + 1].date.month)
                    {
                        temp = appoints[j];
                        appoints[j] = appoints[j + 1];
                        appoints[j + 1] = temp;
                    }
                    else if (appoints[j].date.month == appoints[j + 1].date.month)
                    {
                        if (appoints[j].date.day > appoints[j + 1].date.day)
                        {
                            temp = appoints[j];
                            appoints[j] = appoints[j + 1];
                            appoints[j + 1] = temp;
                        }
                        else if (appoints[j].date.day == appoints[j + 1].date.day)
                        {
                            if (appoints[j].time.hour > appoints[j + 1].time.hour)
                            {
                                temp = appoints[j];
                                appoints[j] = appoints[j + 1];
                                appoints[j + 1] = temp;
                            }
                            else if (appoints[j].time.hour == appoints[j + 1].time.hour)
                            {
                                if (appoints[j].time.min > appoints[j + 1].time.min)
                                {
                                    temp = appoints[j];
                                    appoints[j] = appoints[j + 1];
                                    appoints[j + 1] = temp;
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Get Date Function from user
struct Date GetDate (void)
{
    struct Date date;
    int day;
    
    printf("Year        : ");
    date.year = inputInt();
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);
    switch (date.month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            day = 31;
            break;
        case 2:
            if (date.year % 4 == 0)
            {
                day = 29;
            }
            else
            {
                day = 28;
            }
            break;
        default:
            day = 30;
            break;
    }
    printf("Day (1-%d)  : ", day);
    date.day = inputIntRange(1, day);
    
    return date;
};

// Get Time Function from user
struct Time GetTime (void)
{
    struct Time time;
        do {
            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

        if ((time.min % TIME_INTERVAL != 0) || (time.hour < HOUR_OPENING) || (time.hour > HOUR_CLOSING) || (time.hour == HOUR_CLOSING && time.min != MIN_CLOSING))
        {
            printf("ERROR: Time must be between %02d:%02d and %02d:%02d in %d minute intervals.\n\n", HOUR_OPENING, MIN_OPENING, HOUR_CLOSING, MIN_CLOSING, TIME_INTERVAL);
        }
    } while ((time.min % TIME_INTERVAL != 0) || (time.hour < HOUR_OPENING) || (time.hour > HOUR_CLOSING) || (time.hour == HOUR_CLOSING && time.min != MIN_CLOSING));
    return time;
};
//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record

void inputPatient(struct Patient* patient)
{
    
    char tempName[NAME_LEN];
    printf("Patient Data Input\n"
           "------------------\n");
    printf("Number: %05d\n", patient->patientNumber); // show the patient's number
    printf("Name  : ");
    inputCString(tempName, 1, NAME_LEN); // ask for the Name of the patient
    printf("\n");
    strcpy(patient->name, tempName); // copy the name of the patient to the patient name array
    inputPhoneData(&patient->phone); // ask for the contact information
}

// Validate Patient Number
int getPatientNumber (const struct Patient* patient, int max)
{
    int i = 0, result = -1, patientId;
    printf("Patient Number: ");
    patientId = inputInt();
    for (i = 0; i < max; i++) {
        if (patientId == patient[i].patientNumber)
        {
            result = patientId;
        }
    }
    if (result == 0) {
        printf("ERROR: Patient record not found!\n\n");
    }
    
    return result;
}

// Find Next Available Array Index for Appointment
int nextAppointIndex(const struct Appointment* appoint, int max)
{
    int i, result = -1;
    
    for (i = 0; i < max && result == -1; i++) {
        if (appoint[i].patientNumber == 0)
        {
            result = i;
        }
    }
    
    return result;
}


// Find the appointment array index by patient number (returns -1 if not found)
int findAppointIndex(int patientNumber,const struct Date date, const struct Appointment appoint[], int max)
{
    int i, result = -1;
    
    for (i = 0; i < max; i++) {
        if (appoint[i].patientNumber == patientNumber && appoint[i].date.year == date.year && appoint[i].date.month == date.month && appoint[i].date.day == date.day)
        {
            result = i;
        }
    }
    
    return result;
}

// Get user input for phone contact information

void inputPhoneData(struct Phone* phone)
{
    char phoneNumber[PHONE_LEN+1];
    int choice;
    printf("Phone Information\n"
           "-----------------\n"
           "How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");
    choice = inputIntRange(1, 4); // ask for the type of the patient's number
    switch (choice) {
        case 1: // if it's Cell
            strcpy(phone->description, "CELL"); // set 'CELL' to the description of the phone.
            printf("\nContact: CELL\nNumber : ");
            inputCString(phoneNumber, PHONE_LEN, PHONE_LEN); // ask for the phone number
            strcpy(phone->number, phoneNumber); // set phone number to the number of the phone array.
            break;
        case 2: // if it's Home
            strcpy(phone->description, "HOME"); // set 'HOME' to the description of the phone.
            printf("\nContact: HOME\nNumber : ");
            inputCString(phoneNumber, PHONE_LEN, PHONE_LEN); // ask for the phone number
            strcpy(phone->number, phoneNumber); // set phone number to the number of the phone array.
            break;
        case 3: // if it's Work
            strcpy(phone->description, "WORK"); // set 'WORK' to the description of the phone.
            printf("\nContact: WORK\nNumber : ");
            inputCString(phoneNumber, PHONE_LEN, PHONE_LEN); // ask for the phone number
            strcpy(phone->number, phoneNumber); // set phone number to the number of the phone array.
            break;
            
        case 4: // if it's TBD
            strcpy(phone->description, "TBD"); // set 'TBD' to the description of the phone.
            break;
    }
    printf("\n");
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;
    FILE* fp = NULL;
    
    fp = fopen(datafile, "r");
    
    if (fp != NULL)
    {
        
        while (i < max && fscanf(fp, "%d|%[^|]|%[^|]|%10[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF) //untill there is patient to scan
        {
            patients[i].name[NAME_LEN - 1] = '\0';
            patients[i].phone.description[PHONE_DESC_LEN] = '\0';
            patients[i].phone.number[PHONE_LEN] = '\0';
            i++;
        }
    }
    else
    {
        printf("File Not Found!");
        i = -1;
    }
    fclose(fp);
    SortPatients(patients, max);
    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;
    FILE* fp = NULL;
    
    fp = fopen(datafile, "r");
    
    if (fp != NULL)
    {
            while (fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) != EOF && i < max) //untill there is patient to scan
            {
                i++;
            }
    }
    else
    {
        printf("File Not Found!");
        i = -1;
    }
    if (fp) fclose(fp);
    return i;
}
