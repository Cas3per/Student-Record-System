/*
* Project Title: Student Record System
 * Course: COS 201 - Computer Programming I
 *
 * Description:  This main.c file should be incredibly clean.
 * Its only job is to
 * 1. bootstrap the application,
 * 2. load the data,
 * 3. display the menu,
 * 4. route the user's choice,
 * 5. and clean up when done.
 */

#include <stdio.h>

#include <stdlib.h>

// This header file acts as our API contract.
#include "student.h"


int main() {
    greet_user();     // Initial Setup
    load_from_file(); // Load existing students records

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