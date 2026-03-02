
/*
 *This header file acts as our API contract.
 * It defines the data structures and what functions are available,
 * without exposing the internal implementation.
 */

#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 50
#define FILE_PATH "../data/students.txt"
#define PASS_THRESHOLD 40.0

// Data Storage Structure [cite: 14, 15]
typedef struct {
    char name[MAX_NAME_LENGTH];
    int roll_number;
    float marks;
} Student;

// Global State Management (extern tells the compiler these exist in a .c file)
extern Student *students;
extern int student_count;
extern int capacity;

// Core Function Prototypes [cite: 29]
void greet_user();
void display_menu();
void add_student();
void modify_student();
void remove_student();
void display_students();
void search_student();
void calculate_average();
void sort_students();

// File & Memory Management [cite: 30, 32]
void save_to_file();
void load_from_file();
void cleanup_memory();

// Security & Utility Enhancements
void secure_read_string(char *buffer, int length);
float secure_read_float();
int secure_read_int();

#endif // STUDENT_H