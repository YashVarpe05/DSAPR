#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Student
{
    string rollNumber;
    string name;
    string division;
    string address;

    void display()
    {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }
};

void addStudent()
{
    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore(); // Clear input buffer
    cout << "Enter Name: ";
    getline(cin, student.name);
    cout << "Enter Division: ";
    getline(cin, student.division);
    cout << "Enter Address: ";
    getline(cin, student.address);

    ofstream file("students.txt", ios::app);
    if (file.is_open())
    {
        file << student.rollNumber << "," << student.name << ","
             << student.division << "," << student.address << endl;
        file.close();
        cout << "Student added successfully.\n";
    }
    else
    {
        cout << "Error opening file.\n";
    }
}

void displayStudent()
{
    string rollNumber;
    cout << "Enter Roll Number to search: ";
    cin >> rollNumber;

    ifstream file("students.txt");
    if (!file.is_open())
    {
        cout << "Error opening file.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string roll, name, division, address;
        getline(ss, roll, ',');
        getline(ss, name, ',');
        getline(ss, division, ',');
        getline(ss, address);

        if (roll == rollNumber)
        {
            Student student = {roll, name, division, address};
            student.display();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Student not found.\n";
    }

    file.close();
}

void deleteStudent()
{
    string rollNumber;
    cout << "Enter Roll Number to delete: ";
    cin >> rollNumber;

    ifstream file("students.txt");
    if (!file.is_open())
    {
        cout << "Error opening file.\n";
        return;
    }

    ofstream tempFile("temp.txt");
    string line;
    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string roll, name, division, address;
        getline(ss, roll, ',');
        getline(ss, name, ',');
        getline(ss, division, ',');
        getline(ss, address);

        if (roll != rollNumber)
        {
            tempFile << line << endl;
        }
        else
        {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    if (found)
    {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "Student deleted successfully.\n";
    }
    else
    {
        cout << "Student not found.\n";
        remove("temp.txt");
    }
}

int main()
{
    int choice;
    do
    {
        cout << "\n1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudent();
            break;
        case 3:
            deleteStudent();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}

/*
 START

    // Display Menu Options
    WHILE choice != 4:
        Display menu options:
            1. Add Student
            2. Display Student
            3. Delete Student
            4. Exit

        Get user choice

        IF choice == 1:
            Call addStudent()
        ELSE IF choice == 2:
            Call displayStudent()
        ELSE IF choice == 3:
            Call deleteStudent()
        ELSE IF choice == 4:
            EXIT program
        ELSE:
            Print "Invalid choice"

    END WHILE

END

// Function to Add Student
FUNCTION addStudent():
    Prompt user for student details (rollNumber, name, division, address)
    Open file "students.txt" in append mode
    Write student details to the file
    Close file
    Print "Student added successfully"

// Function to Display Student
FUNCTION displayStudent():
    Prompt user for rollNumber to search
    Open file "students.txt"
    FOR each line in file:
        Split line into (roll, name, division, address)
        IF roll == user input:
            Print student details
            EXIT loop
    IF student not found:
        Print "Student not found"
    Close file

// Function to Delete Student
FUNCTION deleteStudent():
    Prompt user for rollNumber to delete
    Open file "students.txt" for reading
    Open temporary file "temp.txt"
    FOR each line in file:
        Split line into (roll, name, division, address)
        IF roll != user input:
            Write line to temp file
        ELSE:
            Skip line (student to delete)
    Close both files
    IF student found:
        Delete "students.txt"
        Rename "temp.txt" to "students.txt"
        Print "Student deleted successfully"
    ELSE:
        Delete "temp.txt"
        Print "Student not found"
*/