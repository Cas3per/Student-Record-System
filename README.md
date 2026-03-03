
```markdown
# Student Record System 🎓

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)

[cite_start]A robust, production-grade Command Line Interface (CLI) application written in C programming language to manage student information[cite: 8]. [cite_start]Built as a Lab Project for COS 201 - Computer Programming I [cite: 1] [cite_start]at Department of Computing, MIVA Open University, Abuja, Nigeria.[cite: 3, 4]. 

This project adheres to Software Development Life Cycle (SDLC) principles, featuring a modular architecture that separates business logic, data persistence, and the user interface.

## 📋 Table of Contents
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Installation & Setup](#-installation--setup)
- [Usage Instructions](#-usage-instructions)
- [Software Requirements Specification (SRS)](#-software-requirements-specification-srs)
- [Author](#-author)

---

## ✨ Features
* [cite_start]**Dynamic Data Management:** Add, modify, and remove student records using dynamic memory allocation (`malloc`/`realloc`), ensuring efficient memory use without fixed array limits[cite: 28, 31].
* [cite_start]**Persistent Storage:** Save and load student records seamlessly from a local text file database (`students.txt`)[cite: 33, 34].
* **Robust Input Validation:** Custom input handling prevents buffer overflows and infinite loops caused by standard `scanf` vulnerabilities.
* [cite_start]**Analytics & Sorting:** Calculate system-wide average marks [cite: 46] [cite_start]and sort records in ascending or descending order using standard C algorithms (`qsort`)[cite: 48, 49].
* [cite_start]**Search Functionality:** Quickly retrieve individual student data by querying their unique Roll Number[cite: 43, 44].
* [cite_start]**Automated Grading:** Automatically determines "Pass" or "Fail" status based on a configurable threshold (marks above 40 are considered passing)[cite: 17].

---

## 🗂 Project Structure

The codebase follows a modular structure to enforce the Separation of Concerns. Click the dropdowns below to view the source code for each file.

```text
StudentRecordSystem/
├── CMakeLists.txt       # CMake build configuration
├── include/
│   └── student.h        # API contract: Structs, constants, and function prototypes
├── src/
│   ├── main.c           # Entry point: User interface, menu loop, and routing
│   └── student.c        # Business logic: Memory, file I/O, and data manipulation
└── data/
    └── students.txt     # Persistent storage for records (Auto-generated)

```

<details>
<summary><b>📄 CMakeLists.txt</b> (Click to expand)</summary>

```cmake
cmake_minimum_required(VERSION 3.20)
project(StudentRecordSystem C)

set(CMAKE_C_STANDARD 11)

# Tell the compiler where to look for header (.h) files
include_directories(include)

# Compile the executable from multiple source files
add_executable(StudentRecordSystem 
    src/main.c 
    src/student.c
)

```

</details>

<details>
<summary><b>📄 include/student.h</b> (Click to expand)</summary>

```c
#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 50
#define FILE_PATH "../data/students.txt"
#define PASS_THRESHOLD 40.0

// Data Storage Structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    int roll_number;
    float marks;
} Student;

// Global State Management
extern Student *students;
extern int student_count;
extern int capacity;

// Core Function Prototypes
void greet_user();
void display_menu();
void add_student();
void modify_student();
void remove_student();
void display_students();
void search_student();
void calculate_average();
void sort_students();

// File & Memory Management
void save_to_file();
void load_from_file();
void cleanup_memory();

// Security & Utility Enhancements
void secure_read_string(char *buffer, int length);
float secure_read_float();
int secure_read_int();

#endif // STUDENT_H

```

</details>

<details>
<summary><b>📄 src/main.c</b> (Click to expand)</summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main() {
    greet_user();     // Initial Setup
    load_from_file(); // Load existing records

    int choice;
    do {
        display_menu();
        printf("\nEnter your choice: ");
        choice = secure_read_int(); // Secured input handling

        switch (choice) {
            case 1: add_student(); break;
            case 2: modify_student(); break;
            case 3: remove_student(); break;
            case 4: display_students(); break;
            case 5: search_student(); break;
            case 6: calculate_average(); break;
            case 7: sort_students(); break;
            case 8: save_to_file(); break;
            case 9: 
                save_to_file();
                printf("Saving and shutting down gracefully...\n");
                break;
            default: 
                printf("Invalid choice. Please select 1-9.\n");
        }
    } while (choice != 9); // Loop until exit

    cleanup_memory(); // Prevent memory leaks
    return 0;
}

```

</details>

<details>
<summary><b>📄 src/student.c</b> (Click to expand)</summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/student.h"

Student *students = NULL;
int student_count = 0;
int capacity = 0;

void secure_read_string(char *buffer, int length) {
    if (fgets(buffer, length, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
}

int secure_read_int() {
    char buffer[50];
    secure_read_string(buffer, sizeof(buffer));
    return atoi(buffer);
}

float secure_read_float() {
    char buffer[50];
    secure_read_string(buffer, sizeof(buffer));
    return atof(buffer);
}

void greet_user() {
    char admin_name[MAX_NAME_LENGTH];
    printf("=========================================\n");
    printf("       STUDENT RECORD SYSTEM v1.0        \n");
    printf("=========================================\n");
    printf("System Initialization...\n");
    printf("Please enter your name to authenticate: ");
    secure_read_string(admin_name, sizeof(admin_name));
    
    if (strlen(admin_name) == 0) strcpy(admin_name, "Admin");
    printf("\nWelcome, %s. System ready.\n", admin_name);
}

void display_menu() {
    printf("\n--- Main Menu ---\n");
    printf("1. Add Student Record\n");
    printf("2. Modify Existing Record\n");
    printf("3. Remove Student Record\n");
    printf("4. Display All Records\n");
    printf("5. Search Student by Roll Number\n");
    printf("6. Calculate System-wide Average Marks\n");
    printf("7. Sort Records by Marks\n");
    printf("8. Manually Save to Database (File)\n");
    printf("9. Save & Exit\n");
}

void add_student() {
    if (student_count >= capacity) {
        capacity = (capacity == 0) ? 2 : capacity * 2;
        Student *temp = realloc(students, capacity * sizeof(Student));
        if (!temp) {
            printf("[ERROR] Memory allocation failed. Cannot add student.\n");
            return;
        }
        students = temp;
    }

    Student new_student;
    printf("Enter Student Full Name: ");
    secure_read_string(new_student.name, MAX_NAME_LENGTH);
    printf("Enter Roll Number (Integer): ");
    new_student.roll_number = secure_read_int();
    printf("Enter Final Marks: ");
    new_student.marks = secure_read_float();

    students[student_count++] = new_student;
    printf("\n[SUCCESS] Record added. Status: %s\n", 
           (new_student.marks >= PASS_THRESHOLD) ? "PASSED" : "FAILED");
}

void modify_student() {
    printf("Enter Roll Number of student to modify: ");
    int roll = secure_read_int();

    for (int i = 0; i < student_count; i++) {
        if (students[i].roll_number == roll) {
            printf("Found record for: %s\n", students[i].name);
            printf("Enter new Marks: ");
            students[i].marks = secure_read_float();
            printf("[SUCCESS] Record updated. New Status: %s\n", 
                   (students[i].marks >= PASS_THRESHOLD) ? "PASSED" : "FAILED");
            return;
        }
    }
    printf("[NOT FOUND] No student matches Roll Number %d.\n", roll);
}

void remove_student() {
    printf("Enter Roll Number of student to remove: ");
    int roll = secure_read_int();

    for (int i = 0; i < student_count; i++) {
        if (students[i].roll_number == roll) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("[SUCCESS] Student record removed.\n");
            return;
        }
    }
    printf("[NOT FOUND] No student matches Roll Number %d.\n", roll);
}

void display_students() {
    if (student_count == 0) {
        printf("\n[INFO] The database is currently empty.\n");
        return;
    }
    
    printf("\n%-25s %-15s %-10s %-10s\n", "Student Name", "Roll Number", "Marks", "Status");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < student_count; i++) {
        printf("%-25s %-15d %-10.2f %-10s\n", 
               students[i].name, students[i].roll_number, students[i].marks,
               (students[i].marks >= PASS_THRESHOLD) ? "PASS" : "FAIL");
    }
    printf("----------------------------------------------------------------\n");
    printf("Total Records: %d\n", student_count);
}

void search_student() {
    printf("Enter Roll Number to search: ");
    int roll = secure_read_int();

    for (int i = 0; i < student_count; i++) {
        if (students[i].roll_number == roll) {
            printf("\n--- Record Found ---\n");
            printf("Name:        %s\n", students[i].name);
            printf("Roll Number: %d\n", students[i].roll_number);
            printf("Marks:       %.2f\n", students[i].marks);
            printf("Status:      %s\n", (students[i].marks >= PASS_THRESHOLD) ? "PASSED" : "FAILED");
            return;
        }
    }
    printf("[NOT FOUND] No student matches Roll Number %d.\n", roll);
}

void calculate_average() {
    if (student_count == 0) {
        printf("\n[INFO] No records available to calculate average.\n");
        return;
    }
    float total = 0;
    for (int i = 0; i < student_count; i++) {
        total += students[i].marks;
    }
    printf("\nSystem-wide Average Marks: %.2f (across %d students)\n", total / student_count, student_count);
}

static int compare_asc(const void *a, const void *b) {
    float diff = ((Student*)a)->marks - ((Student*)b)->marks;
    return (diff > 0) - (diff < 0);
}

static int compare_desc(const void *a, const void *b) {
    float diff = ((Student*)b)->marks - ((Student*)a)->marks;
    return (diff > 0) - (diff < 0);
}

void sort_students() {
    if (student_count < 2) {
        printf("\n[INFO] Not enough records to perform sorting.\n");
        return;
    }
    
    printf("Sort Order: [1] Ascending or [2] Descending? ");
    int order = secure_read_int();

    if (order == 1) {
        qsort(students, student_count, sizeof(Student), compare_asc);
        printf("[SUCCESS] Records sorted in Ascending order.\n");
    } else if (order == 2) {
        qsort(students, student_count, sizeof(Student), compare_desc);
        printf("[SUCCESS] Records sorted in Descending order.\n");
    } else {
        printf("[ERROR] Invalid selection. Sorting cancelled.\n");
        return;
    }
    display_students();
}

void save_to_file() {
    FILE *file = fopen(FILE_PATH, "w");
    if (!file) {
        printf("[ERROR] Could not open file %s for writing. Ensure directory exists.\n", FILE_PATH);
        return;
    }
    
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%s,%d,%.2f\n", students[i].name, students[i].roll_number, students[i].marks);
    }
    
    fclose(file);
    printf("[SUCCESS] Database saved to %s.\n", FILE_PATH);
}

void load_from_file() {
    FILE *file = fopen(FILE_PATH, "r");
    if (!file) {
        printf("[INFO] No existing database found at %s. Starting fresh.\n", FILE_PATH);
        return; 
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        if (student_count >= capacity) {
            capacity = (capacity == 0) ? 2 : capacity * 2;
            Student *temp = realloc(students, capacity * sizeof(Student));
            if (temp) students = temp;
        }
        
        char *token = strtok(line, ",");
        if (token) {
            strncpy(students[student_count].name, token, MAX_NAME_LENGTH - 1);
            students[student_count].name[MAX_NAME_LENGTH - 1] = '\0';
        }
        
        token = strtok(NULL, ",");
        if (token) students[student_count].roll_number = atoi(token);
        
        token = strtok(NULL, ",");
        if (token) students[student_count].marks = atof(token);
        
        student_count++;
    }
    fclose(file);
    printf("[SUCCESS] Loaded %d records from disk.\n", student_count);
}

void cleanup_memory() {
    if (students != NULL) {
        free(students);
        students = NULL;
        capacity = 0;
        student_count = 0;
    }
}

```

</details>

---

## 🚀 Installation & Setup

### Prerequisites

* A C compiler (GCC, Clang, or MSVC)
* CMake (version 3.20 or higher)
* An IDE like JetBrains CLion, VS Code, or a standard terminal environment.



### Build Instructions

1. **Clone the repository:**
```bash
git clone [https://github.com/yourusername/StudentRecordSystem.git](https://github.com/yourusername/StudentRecordSystem.git)
cd StudentRecordSystem

```


2. **Create the necessary data directory:**
Ensure the `data` directory exists in the project root before running the application, as the program will write to `data/students.txt`.
```bash
mkdir data

```


3. **Build using CMake:**
```bash
mkdir build
cd build
cmake ..
make

```


4. **Run the Executable:**
```bash
./StudentRecordSystem

```



---

## 💻 Usage Instructions

Upon launching the application, you will be prompted to enter your name for authentication. The system will greet you and load any existing records from the database.

Navigate the system using the numeric keypad corresponding to the main menu options:

1. 
**Add Student:** Prompts for Name, Roll Number, and Marks.


2. 
**Modify Student:** Edit marks for an existing Roll Number.


3. 
**Remove Student:** Deletes a record from the dynamic array.


4. 
**Display All Students:** Prints a formatted table of all active records.


5. 
**Search Student:** Locates a specific student by Roll Number.


6. 
**Calculate Average:** Computes the mean marks across the system.


7. 
**Sort Students:** Orders the table by marks in ascending or descending order.


8. 
**Save to File:** Manually forces a database write.


9. 
**Exit:** Saves data and safely frees all allocated memory before shutting down.



---

## 📄 Software Requirements Specification (SRS)

### 1. Introduction

**1.1 Purpose:** The purpose of this document is to define the requirements for the Student Record System. This CLI application allows educational administrators to manage student information effectively and reliably.

**1.2 Scope:**
The system is designed for local, single-user operation. It handles temporary data processing in RAM via dynamic allocation and provides data persistence through flat-file storage (.txt).

### 2. Functional Requirements

* 
**FR-1 (Initial Setup):** The system shall prompt the user for their name upon execution and display a personalized greeting.


* 
**FR-2 (Data Storage):** The system shall store student name, roll number, and marks using appropriate C data types grouped in a `struct`.


* 
**FR-3 (Input and Output):** The system shall accept marks input and calculate Pass/Fail status based on a passing threshold (marks above 40).


* 
**FR-4 (Student Records Management):** The system shall implement an interactive loop allowing users to add, modify, and remove multiple records until they explicitly choose to exit.


* 
**FR-5 (File Operations):** The system shall provide functions to save current memory state to a text file and load existing text file data into memory on startup.


* 
**FR-6 (Search Functionality):** Users shall be able to query the system using a roll number to return specific student data.


* 
**FR-7 (Calculations and Sorting):** The system shall calculate the mathematical average of all stored marks and allow list sorting by marks.



### 3. Non-Functional Requirements

* 
**NFR-1 (Memory Management):** The system must use `malloc` and `realloc` for dynamic memory allocation for student records, and it must explicitly `free()` memory when no longer needed.


* **NFR-2 (Robustness):** The application must not crash upon receiving unexpected string inputs where integers or floats are expected.

### 4. System Architecture

The system utilizes a modular, procedural architecture separated into three logical layers:

1. **Presentation Layer:** Standard I/O (Terminal) handled primarily in `main.c`.
2. **Logic Layer:** Data manipulation, sorting algorithms, and memory operations handled in `student.c`.
3. **Data Layer:** Flat file storage (`students.txt`) acting as the persistent database.

---

## 👨‍💻 Team
**Phil Casper** *Software Engineering (student)*, Department of Computing,  Miva Open University, Abuja.

**Samuel Chukwu** *Software Engineering (student)*, Department of Computing,  Miva Open University, Abuja.

**Chidozie Bright** *Software Engineering (student)*, Department of Computing,  Miva Open University, Abuja.

*Copyright 2026 MIVA Open University All Rights Reserved*

```
