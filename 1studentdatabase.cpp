#include <iostream>
#include <string>
using namespace std;

struct Student
{
    int rollNo;
    string name;
    float sgpa;
};

void bubbleSortByRollNo(Student students[], int n)
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

void insertionSortByName(Student students[], int n)
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

void searchBySGPA(Student students[], int n, float sgpa)
{
    const float EPSILON = 0.0001f;
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if (abs(students[i].sgpa - sgpa) < EPSILON)
        {
            cout << "Roll No: " << students[i].rollNo << ", Name: " << students[i].name
                 << ", SGPA: " << students[i].sgpa << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No students found with SGPA " << sgpa << endl;
    }
}

void printStudents(Student students[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Roll No: " << students[i].rollNo << ", Name: " << students[i].name << ", SGPA: " << students[i].sgpa << endl;
    }
}

int main()
{
    const int n = 15;
    Student students[n] = {
        {101, "Alice", 8.5}, {102, "Bob", 7.9}, {103, "Charlie", 8.2}, {104, "David", 9.1}, {105, "Eve", 8.0}, {106, "Frank", 7.5}, {107, "Grace", 8.7}, {108, "Hannah", 7.8}, {109, "Ivy", 9.2}, {110, "Jack", 8.6}, {111, "Kate", 7.3}, {112, "Leo", 8.1}, {113, "Mia", 9.0}, {114, "Noah", 8.8}, {115, "Olivia", 8.4}};

    cout << "Original List:\n";
    printStudents(students, n);

    bubbleSortByRollNo(students, n);
    cout << "\nList Sorted by Roll No:\n";
    printStudents(students, n);

    insertionSortByName(students, n);
    cout << "\nList Sorted Alphabetically by Name:\n";
    printStudents(students, n);

    float searchSGPA;
    cout << "\nEnter SGPA to search: ";
    cin >> searchSGPA;
    cout << "\nStudents with SGPA " << searchSGPA << ":\n";
    searchBySGPA(students, n, searchSGPA);

    return 0;
}

/*BUBBLE SORT (by Roll Number)
1. Input: array of students, size n
2. For i = 0 to n-1
   3. For j = 0 to n-i-1
      4. If students[j].rollNo > students[j+1].rollNo
         5. Swap students[j] and students[j+1]

B. INSERTION SORT (by Name)
1. Input: array of students, size n
2. For i = 1 to n-1
   3. key = students[i]
   4. j = i-1
   5. While j >= 0 AND students[j].name > key.name
      6. students[j+1] = students[j]
      7. j = j-1
   8. students[j+1] = key

C. SEARCH (by SGPA)
1. Input: array of students, size n, target SGPA
2. For each student in array
   3. If student.sgpa matches target (within epsilon)
      4. Display student details */