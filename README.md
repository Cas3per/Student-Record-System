# Student Record System 🎓

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)

A robust, production-grade Command Line Interface (CLI) application written in C to manage student information. Built as a Lab Project for for COS 201 - Computer Programming I at Miva Open University. 

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
* **Dynamic Data Management:** Add, modify, and remove student records using dynamic memory allocation (`malloc`/`realloc`), ensuring efficient memory use without fixed array limits.
* **Persistent Storage:** Save and load student records seamlessly from a local text file database (`students.txt`)[cite: 33, 34].
* **Robust Input Validation:** Custom input handling prevents buffer overflows and infinite loops caused by standard `scanf` vulnerabilities.
* **Analytics & Sorting:** Calculate system-wide average marks and sort records in ascending or descending order using standard C algorithms (`qsort`).
* **Search Functionality:** Quickly retrieve individual student data by querying their unique Roll Number.
* **Automated Grading:** Automatically determines "Pass" or "Fail" status based on a configurable threshold (e.g., marks >= 40.0).

---

## 🗂 Project Structure
The codebase follows a modular structure to enforce the Separation of Concerns:

```text
StudentRecordSystem/
[cite_start]├── CMakeLists.txt       # CMake build configuration 
├── include/
│   └── student.h        # API contract: Structs, constants, and function prototypes
├── src/
│   ├── main.c           # Entry point: User interface, menu loop, and routing
│   └── student.c        # Business logic: Memory, file I/O, and data manipulation
└── data/
    └── students.txt     # Persistent storage for records (Auto-generated)
