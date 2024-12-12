#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Student {
    string rollNumber;
    string name;
    string division;
    string address;

    void display() {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }
};

void addStudent() {
    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    ofstream file("students.txt", ios::app);
    file << student.rollNumber << "," << student.name << ","
         << student.division << "," << student.address << endl;
    file.close();
    cout << "Student added successfully.\n";
}

void displayStudent() {
    string rollNumber;
    cout << "Enter Roll Number to search: ";
    cin >> rollNumber;

    ifstream file("students.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string roll, name, division, address;
        getline(ss, roll, ',');
        getline(ss, name, ',');
        getline(ss, division, ',');
        getline(ss, address);

        if (roll == rollNumber) {
            Student student = {roll, name, division, address};
            student.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }
    file.close();
}

void deleteStudent() {
    string rollNumber;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNumber;

    ifstream file("students.txt");
    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string roll, name, division, address;
        getline(ss, roll, ',');
        getline(ss, name, ',');
        getline(ss, division, ',');
        getline(ss, address);

        if (roll != rollNumber) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Student deleted successfully.\n";
    } else {
        cout << "Student not found.\n";
        remove("temp.txt");
    }
}

int main() {
    int choice;
    do {
        cout << "\n1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudent(); break;
            case 3: deleteStudent(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
