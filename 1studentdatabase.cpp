#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float sgpa;
};

void bubbleSortByRollNo(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void insertionSortByName(Student students[], int n) {
    for (int i = 1; i < n; i++) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].name > key.name) {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
}

void searchBySGPA(Student students[], int n, float sgpa) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (students[i].sgpa == sgpa) {
            cout << "Roll No: " << students[i].rollNo << ", Name: " << students[i].name << ", SGPA: " << students[i].sgpa << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No students found with SGPA " << sgpa << endl;
    }
}

void printStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Roll No: " << students[i].rollNo << ", Name: " << students[i].name << ", SGPA: " << students[i].sgpa << endl;
    }
}

int main() {
    const int n = 15;
    Student students[n] = {
        {101, "Alice", 8.5}, {102, "Bob", 7.9}, {103, "Charlie", 8.2},
        {104, "David", 9.1}, {105, "Eve", 8.0}, {106, "Frank", 7.5},
        {107, "Grace", 8.7}, {108, "Hannah", 7.8}, {109, "Ivy", 9.2},
        {110, "Jack", 8.6}, {111, "Kate", 7.3}, {112, "Leo", 8.1},
        {113, "Mia", 9.0}, {114, "Noah", 8.8}, {115, "Olivia", 8.4}
    };

    cout << "Original List:\n";
    printStudents(students, n);

    // Task a: Sort by Roll No
    bubbleSortByRollNo(students, n);
    cout << "\nList Sorted by Roll No:\n";
    printStudents(students, n);

    // Task b: Sort by Name
    insertionSortByName(students, n);
    cout << "\nList Sorted Alphabetically by Name:\n";
    printStudents(students, n);

    // Task c: Search by SGPA
    float searchSGPA;
    cout << "\nEnter SGPA to search: ";
    cin >> searchSGPA;
    cout << "\nStudents with SGPA " << searchSGPA << ":\n";
    searchBySGPA(students, n, searchSGPA);

    return 0;
}
