#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

const int MAX_NAME_LENGTH = 20;

enum Specialty {
    MATH_ECONOMICS,
    PHYSICS_CS,
    COMPUTER_SCIENCE
};

struct Student {
    int studentNumber;
    char lastName[MAX_NAME_LENGTH];
    int course;
    Specialty specialty;
    double physics;
    double math;
    double it;
};

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary);
    char ch;
    string s;
    do {
        cin.ignore();  // Clear the keyboard buffer
        cout << "Enter line: ";
        getline(cin, s);
        for (unsigned i = 0; i < s.length(); i++) {
            fout.write(&s[i], sizeof(s[i]));
        }
        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << endl;
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary);
    char c;
    while (fin.read(&c, sizeof(c))) {
        cout << c;
    }
    cout << endl;
}

const char* specialtiesToString(Specialty specialty) {
    switch (specialty) {
    case MATH_ECONOMICS:
        return "Mathematics and economics";
    case PHYSICS_CS:
        return "Physics and computer science";
    case COMPUTER_SCIENCE:
        return "Computer science";
    default:
        return "Unknown Specialty";
    }
}

void inputStudents(Student* students, int numberOfStudents) {
    const Specialty specialties[] = { MATH_ECONOMICS, PHYSICS_CS, COMPUTER_SCIENCE };
    const char* lastNames[] = { "Vovk", "Mazurok", "Ushakov", "Kojushko", "Zarubich", "Simonenko", "Barchuk", "Osadchyi", "Kalyna" };

    for (int i = 0; i < numberOfStudents; ++i) {
        strncpy(students[i].lastName, lastNames[i % (sizeof(lastNames) / sizeof(lastNames[0]))], MAX_NAME_LENGTH - 1);
        students[i].lastName[MAX_NAME_LENGTH - 1] = '\0';

        students[i].specialty = specialties[i % (sizeof(specialties) / sizeof(specialties[0]))];
        students[i].course = rand() % 5 + 1;
        students[i].physics = rand() % 3 + 3;
        students[i].math = rand() % 3 + 3;
        students[i].it = rand() % 3 + 3;
        students[i].studentNumber = i + 1;
    }
}

void displayTable(const Student* students, int numberOfStudents) {
    int countWithoutThrees = 0;
    int countBelowFour = 0;
    // Display the table header
    cout << "--------------------------------------------------------------------------" << endl;
    cout << "| No |  Surname   |Course|            Speciality          |  P |  M | I  |" << endl;
    cout << "--------------------------------------------------------------------------" << endl;

    // Display the data for each student
    for (int i = 0; i < numberOfStudents; ++i) {
        cout << "| " << setw(2) << students[i].studentNumber << " | " << setw(10) << students[i].lastName << " | "
            << setw(4) << students[i].course << " | " << setw(30) << specialtiesToString(students[i].specialty) << " | "
            << setw(2) << students[i].physics << " | " << setw(2) << students[i].math << " | "
            << setw(2) << students[i].it << " |" << endl;
        // Обчислення
        if (students[i].physics >= 4 && students[i].math >= 4 && students[i].it >= 4) {
            countWithoutThrees++;
        }

        double averageGrade = (students[i].physics + students[i].math + students[i].it) / 3.0;
        if (averageGrade < 4.0) {
            countBelowFour++;
        }
    }

    std::cout << "--------------------------------------------------------------------------" << std::endl;

    // Виведення результатів обчислень
    std::cout << "1. Number of students without threes: " << countWithoutThrees << std::endl;
    std::cout << "2. Percentage of students with an average grade below 4: " << std::fixed << std::setprecision(2)
        << (static_cast<double>(countBelowFour) / numberOfStudents) * 100 << "%" << std::endl;
}

void WriteTableToFile(char* fname, const Student* students, int numberOfStudents) {
    int countWithoutThrees = 0;
    int countBelowFour = 0;
    ofstream fout(fname, ios::binary);
    if (!fout) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    fout << "--------------------------------------------------------------------------" << endl;
    fout << "| No |  Surname   |Course|            Speciality          |  P |  M | I  |" << endl;
    fout << "--------------------------------------------------------------------------" << endl;

    for (int i = 0; i < numberOfStudents; ++i) {
        fout << "| " << setw(2) << students[i].studentNumber << " | " << setw(10) << students[i].lastName << " | "
            << setw(4) << students[i].course << " | " << setw(30) << specialtiesToString(students[i].specialty) << " | "
            << setw(2) << students[i].physics << " | " << setw(2) << students[i].math << " | "
            << setw(2) << students[i].it << " |" << endl;

        if (students[i].physics >= 4 && students[i].math >= 4 && students[i].it >= 4) {
            countWithoutThrees++;
        }

        double averageGrade = (students[i].physics + students[i].math + students[i].it) / 3.0;
        if (averageGrade < 4.0) {
            countBelowFour++;
        }
    }

    fout << "--------------------------------------------------------------------------" << endl;
    fout << "1. Number of students without threes: " << countWithoutThrees << endl;
    fout << "2. Percentage of students with an average grade below 4: " << fixed << setprecision(2)
        << (static_cast<double>(countBelowFour) / numberOfStudents) * 100 << "%" << endl;

    fout.close();
}

int main() {
    char fname[100];
    cout << "Enter file name: ";
    cin >> fname;

    int numberOfStudents;
    cout << "Enter the number of students: ";
    cin >> numberOfStudents;

    srand(static_cast<unsigned>(time(0)));

    Student* students = new Student[numberOfStudents];
    inputStudents(students, numberOfStudents);

    // Display the table
    displayTable(students, numberOfStudents);

    // Write the table to the file
    WriteTableToFile(fname, students, numberOfStudents);

    delete[] students;

    return 0;
}
