# Veterinary Clinic Management System

This project is a veterinary clinic management system developed in C. It allows clinic staff to manage patient (pet) information, schedule appointments, and maintain a list of records in an organized manner.

## Features

- **Patient Management**: Add, edit, search, and remove pet (patient) records, including names and contact information.
- **Appointment Scheduling**: Schedule, view, and manage pet appointments. The system ensures no double-booking and handles appointment cancellations.
- **Data Import/Export**: Import patient and appointment data from text files to ensure seamless operation.
- **Modular Code Design**: The project is structured using separate modules for core functionalities, patient management, and appointment handling, ensuring maintainability and scalability.

## Project Structure

The system is divided into three milestones, each building upon the previous:

1. **Milestone 1**: Helper functions for core operations such as input validation and string handling.
2. **Milestone 2**: Patient management system with the ability to add, edit, search, and remove patient records.
3. **Milestone 3**: Appointment management functionality, including scheduling, viewing, and removing appointments, along with data import from text files.

### Files

- **core.h / core.c**: Contains core utility functions for input handling and other general operations.
- **clinic.h / clinic.c**: Contains functions related to patient and appointment management.
- **a1ms1.c, a1ms2.c, main.c**: Main files for each milestone, implementing testing and validation for the corresponding module.
- **patientData.txt / appointmentData.txt**: Sample text files used for importing patient and appointment data.

## How to Run

1. Clone the repository:

   git clone https://github.com/YourGitHubUsername/vet-clinic-appointment-system.git

2. Compile the project using the gcc compiler:

   gcc -Wall main.c core.c clinic.c -o vet_clinic

3. Run the executable:

   ./vet_clinic

4. Follow the on-screen instructions to manage patients and appointments.

## Usage
- **Add a Patient:** Input patient (pet) details including name and contact phone number.
- **Search for a Patient:** Search by patient number or phone number.
- **Schedule an Appointment:** Input the date, time, and patient details to schedule an appointment.
- **View Appointments:** View all appointments or appointments for a specific date.
- **Remove Appointments:** Cancel an appointment by specifying the patient and date.

## Technologies
- **Language:** C
- **Tools:** Xcode

## Acknowledgements
- Inspired by the desire to create a functional system for real-world clinic management applications.
