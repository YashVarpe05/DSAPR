#include <iostream>
#include <string>
using namespace std;

struct Student {
    int rollNo;
    string name;
    float sgpa;
};

void bubbleSort(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void insertionSort(Student students[], int n) {
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
            found = true;
            cout << "Roll No: " << students[i].rollNo << ", Name: " << students[i].name << ", SGPA: " << students[i].sgpa << endl;
        }
    }
    if (!found) {
        cout << "No student found with SGPA: " << sgpa << endl;
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    Student students[15] = {
        {101, "Alice", 8.5}, {102, "Bob", 7.2}, {103, "Charlie", 9.1},
        {104, "David", 6.8}, {105, "Eve", 7.5}, {106, "Frank", 8.0},
        {107, "Grace", 8.3}, {108, "Hannah", 9.0}, {109, "Ivy", 7.8},
        {110, "Jack", 6.5}, {111, "Kara", 8.4}, {112, "Leo", 7.0},
        {113, "Mia", 8.2}, {114, "Noah", 9.2}, {115, "Oscar", 7.9}
    };

    int n = 15;

    cout << "Original List:\n";
    for (int i = 0; i < n; i++) {
        cout << students[i].rollNo << " " << students[i].name << " " << students[i].sgpa << endl;
    }

    bubbleSort(students, n);
    cout << "\nSorted by Roll No:\n";
    for (int i = 0; i < n; i++) {
        cout << students[i].rollNo << " " << students[i].name << " " << students[i].sgpa << endl;
    }

    insertionSort(students, n);
    cout << "\nSorted by Name:\n";
    for (int i = 0; i < n; i++) {
        cout << students[i].rollNo << " " << students[i].name << " " << students[i].sgpa << endl;
    }

    float searchSgpa;
    cout << "\nEnter SGPA to search: ";
    cin >> searchSgpa;
    searchBySGPA(students, n, searchSgpa);

    // Example for Heap Sort
    int arr[] = {15, 10, 20, 5, 30, 25};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    cout << "\nOriginal Array:\n";
    for (int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";
    cout << endl;

    heapSort(arr, arrSize);

    cout << "\nSorted Array using Heap Sort:\n";
    for (int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
