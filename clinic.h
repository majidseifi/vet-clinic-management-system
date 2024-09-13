#ifndef CLINIC_H
#define CLINIC_H

#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10

#define TIME_INTERVAL 30
#define HOUR_OPENING 10
#define MIN_OPENING 00
#define HOUR_CLOSING 14
#define MIN_CLOSING 00

//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type: Phone
struct Phone
{
    char description[PHONE_DESC_LEN + 1]; // Phone Type Description: "CELL", "HOME", "WORK", "TBD"
    char number[PHONE_LEN + 1]; // Length of the phone number
};

// Data type: Patient
struct Patient
{
    int patientNumber; // Unique Patient Number
    char name[NAME_LEN]; // Patient's (pet) name
    struct Phone phone; // Patient's Contact Information
    
};

// Data type: Time
struct Time
{
    int hour;
    int min;
};

// Data type: Date
struct Date
{
    int day;
    int month;
    int year;
};

// Data type: Appointment
struct Appointment
{
    int patientNumber;
    struct Date date;
    struct Time time;
};

// ClinicData type: Provided to student
struct ClinicData
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void);

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt);

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField);


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct ClinicData* data);

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient);

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data);

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data);

// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* data);

// Add an appointment record to the appointment array
int addAppointment(struct Appointment* Appointment, int maxAppointments, struct Patient* patient, int maxPatient);

// Remove an appointment record from the appointment array
int removeAppointment(struct Appointment* Appointment, int maxAppointments, struct Patient* patient, int maxPatient);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max);

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max);

// Sort the array of Patients
void SortPatients(struct Patient* patients, int max);

// Sort the array of Appointments
void SortAppoints(struct Appointment appoints[], int max);

// Get Date Function from user
struct Date GetDate (void);

// Get Time Function from user
struct Time GetTime (void);

// Validate Patient Number
int getPatientNumber (const struct Patient* patient, int max);

// Find Next Available Array Index for Appointment
int nextAppointIndex(const struct Appointment* appoint, int max);

// Find the appointment array index by patient number (returns -1 if not found)
int findAppointIndex(int patientNumber,const struct Date date, const struct Appointment appoint[], int max);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient);

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone);

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max);

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max);


#endif // !CLINIC_H
