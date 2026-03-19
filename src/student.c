#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/student.h"

// Here we define the global variables declared as extern in the header
Student *students = NULL;
int student_count = 0;
int capacity = 0;

// --- Security & Utility Functions ---

void secure_read_string(char *buffer, int length) {
    if (fgets(buffer, length, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            // Clear the input buffer if the string was too long
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

// --- Core Application Logic ---

void greet_user() {
    char admin_name[MAX_NAME_LENGTH];
    printf("=========================================\n");
    printf("       STUDENT RECORD SYSTEM v1.0        \n");
    printf("=========================================\n");
    printf("System Initialization...\n");
    printf("Please enter your name to continue: ");
    secure_read_string(admin_name, sizeof(admin_name));

    // Fallback if user just hits enter
    if (strlen(admin_name) == 0) {
        strcpy(admin_name, "Admin");
    }

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
    // Dynamic array resizing logic
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
            // Shift all subsequent elements left by one
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
               students[i].name,
               students[i].roll_number,
               students[i].marks,
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

// Static comparators keep these functions hidden from other files
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

// --- Data Persistence ---

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
        // Strip newline
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