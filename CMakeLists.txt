cmake_minimum_required(VERSION 3.20)

# Define the project name and the language (C)
project(StudentRecordSystem C)

# Set the C standard (C11 is a solid, modern default)
set(CMAKE_C_STANDARD 11)

# Tell the compiler where to look for header (.h) files
include_directories(include)

# Compile the executable from multiple source files
add_executable(StudentRecordSystem
        src/main.c
        src/student.c
        src/student.c
)