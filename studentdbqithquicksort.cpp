#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Student
{
    int rollNo;
    string name;
    float sgpa;
};

void bubbleSort(Student students[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (students[j].rollNo > students[j + 1].rollNo)
            {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void insertionSort(Student students[], int n)
{
    for (int i = 1; i < n; i++)
    {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].name > key.name)
        {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
}

int partition(Student students[], int low, int high)
{
    float pivot = students[high].sgpa;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (students[j].sgpa > pivot)
        { // Descending order
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

void quickSort(Student students[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}

void searchBySGPA(Student students[], int n, float sgpa)
{
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if (students[i].sgpa == sgpa)
        {
            found = true;
            cout << "Roll No: " << students[i].rollNo << ", Name: " << students[i].name << ", SGPA: " << students[i].sgpa << endl;
        }
    }
    if (!found)
    {
        cout << "No student found with SGPA: " << sgpa << endl;
    }
}

void binarySearchByName(Student students[], int n, string key)
{
    int low = 0, high = n - 1;
    bool found = false;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (students[mid].name.find(key) != string::npos)
        {
            found = true;
            cout << "Roll No: " << students[mid].rollNo << ", Name: " << students[mid].name << ", SGPA: " << students[mid].sgpa << endl;
            break;
        }
        else if (students[mid].name < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    if (!found)
    {
        cout << "No student found with name containing: " << key << endl;
    }
}

int main()
{
    Student students[15] = {
        {101, "Alice", 8.5}, {102, "Bob", 7.2}, {103, "Charlie", 9.1}, {104, "David", 6.8}, {105, "Eve", 7.5}, {106, "Frank", 8.0}, {107, "Grace", 8.3}, {108, "Hannah", 9.0}, {109, "Ivy", 7.8}, {110, "Jack", 6.5}, {111, "Kara", 8.4}, {112, "Leo", 7.0}, {113, "Mia", 8.2}, {114, "Noah", 9.2}, {115, "Oscar", 7.9}};

    int n = 15;

    cout << "Original List:\n";
    for (int i = 0; i < n; i++)
    {
        cout << students[i].rollNo << " " << students[i].name << " " << students[i].sgpa << endl;
    }

    bubbleSort(students, n);
    cout << "\nSorted by Roll No:\n";
    for (int i = 0; i < n; i++)
    {
        cout << students[i].rollNo << " " << students[i].name << " " << students[i].sgpa << endl;
    }

    insertionSort(students, n);
    cout << "\nSorted by Name:\n";
    for (int i = 0; i < n; i++)
    {
        cout << students[i].rollNo << " " << students[i].name << " " << students[i].sgpa << endl;
    }

    quickSort(students, 0, n - 1);
    cout << "\nTop 10 Toppers:\n";
    for (int i = 0; i < 10; i++)
    {
        cout << students[i].rollNo << " " << students[i].name << " " << students[i].sgpa << endl;
    }

    float searchSgpa;
    cout << "\nEnter SGPA to search: ";
    cin >> searchSgpa;
    searchBySGPA(students, n, searchSgpa);

    string searchName;
    cout << "\nEnter name to search: ";
    cin >> searchName;
    binarySearchByName(students, n, searchName);

    return 0;
}

/*
STRUCT Student:
    INTEGER rollNo
    STRING name
    FLOAT sgpa

FUNCTION bubbleSort(students[], n):
    FOR i = 0 to n-1:
        FOR j = 0 to n-i-1:
            IF students[j].rollNo > students[j+1].rollNo:
                SWAP students[j] and students[j+1]

FUNCTION insertionSort(students[], n):
    FOR i = 1 to n:
        SET key = students[i]
        SET j = i - 1
        WHILE j >= 0 AND students[j].name > key.name:
            students[j + 1] = students[j]
            j--
        students[j + 1] = key

FUNCTION partition(students[], low, high):
    SET pivot = students[high].sgpa
    SET i = low - 1
    FOR j = low to high-1:
        IF students[j].sgpa > pivot:
            i++
            SWAP students[i] and students[j]
    SWAP students[i + 1] and students[high]
    RETURN i + 1

FUNCTION quickSort(students[], low, high):
    IF low < high:
        SET pi = partition(students, low, high)
        CALL quickSort(students, low, pi - 1)
        CALL quickSort(students, pi + 1, high)

FUNCTION searchBySGPA(students[], n, sgpa):
    SET found = false
    FOR i = 0 to n-1:
        IF students[i].sgpa == sgpa:
            PRINT student details
            found = true
    IF not found, PRINT "No student found with SGPA"

FUNCTION binarySearchByName(students[], n, key):
    SET low = 0, high = n-1
    SET found = false
    WHILE low <= high:
        SET mid = (low + high) / 2
        IF students[mid].name contains key:
            PRINT student details
            found = true
            BREAK
        ELSE IF students[mid].name < key:
            low = mid + 1
        ELSE:
            high = mid - 1
    IF not found, PRINT "No student found with name containing key"

MAIN:
    SET students[15] with data
    PRINT original list of students

    CALL bubbleSort(students, n)
    PRINT sorted list by Roll No

    CALL insertionSort(students, n)
    PRINT sorted list by Name

    CALL quickSort(students, 0, n-1)
    PRINT Top 10 students based on SGPA

    READ searchSgpa
    CALL searchBySGPA(students, n, searchSgpa)

    READ searchName
    CALL binarySearchByName(students, n, searchName)

*/