# PIC10C-Project-1
This is a project for my PIC10C course at UCLA.

The goal is to create my own implementation of a templatized vector class with all the same features as the vector class in the standard template library vector class. The specifics of the project are available in the pic10b_vector.pdf in this repository.

The grades for this assignment do not come from the functioning of the project, but a demonstration of a familiarity with various git commands and features as to be seen in my commit history. The actual assignment is available in the assignment.html file in this repository.

## Features currently implemented
1. Templatization of both member and non-member functions
2. Implemented comparison operators
3. Vector aritmetic

## Features to be implemented
1. Template specialization for string types
2. Verifying robustness of the code

## Special git features tried:
I added a .gitignore file to prevent git from picking up on my executable file and the visual studio code json files.

## Note:
Additional commits exist on the Partial-Template-Specialization branch

## Unit testing
Unit testing is done with the three driver .cpp files for int, double, and string types

## Compatibility
The code was written in Visual Studio Code and compiled using g++ 6.3.0 MinGW on Windows 10. It is using only the -g flag.
