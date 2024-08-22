#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Student {
    int rollNumber;
    string name;
    int age;
    string course;
};

class StudentManagementSystem {
private:
    vector<Student> students;
    const string fileName = "students.txt";

    void loadStudentsFromFile() {
        ifstream file(fileName);
        if (!file.is_open()) return;

        Student student;
        while (file >> student.rollNumber) {
            file.ignore(); // Ignore newline
            getline(file, student.name);
            file >> student.age;
            file.ignore();
            getline(file, student.course);
            students.push_back(student);
        }
        file.close();
    }

    void saveStudentsToFile() const {
        ofstream file(fileName);
        if (!file.is_open()) return;

        for (const auto &student : students) {
            file << student.rollNumber << endl;
            file << student.name << endl;
            file << student.age << endl;
            file << student.course << endl;
        }
        file.close();
    }

    bool validateRollNumber(int rollNumber) const {
        for (const auto &student : students) {
            if (student.rollNumber == rollNumber) {
                cout << "Error: Roll Number already exists!\n";
                return false;
            }
        }
        return true;
    }

    bool validateAge(int age) const {
        if (age <= 0) {
            cout << "Error: Age must be positive!\n";
            return false;
        }
        return true;
    }

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    StudentManagementSystem() {
        loadStudentsFromFile();
    }

    ~StudentManagementSystem() {
        saveStudentsToFile();
    }

    void addStudent() {
        Student newStudent;
        do {
            cout << "Enter Roll Number: ";
            cin >> newStudent.rollNumber;
            clearInputBuffer();
        } while (!validateRollNumber(newStudent.rollNumber));

        cout << "Enter Name: ";
        getline(cin, newStudent.name);

        do {
            cout << "Enter Age: ";
            cin >> newStudent.age;
            clearInputBuffer();
        } while (!validateAge(newStudent.age));

        cout << "Enter Course: ";
        getline(cin, newStudent.course);

        students.push_back(newStudent);
        cout << "Student added successfully!" << endl;
    }

    void displayStudents() const {
        if (students.empty()) {
            cout << "No students to display!" << endl;
            return;
        }

        cout << "\nStudent Records:\n";
        for (const auto &student : students) {
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Age: " << student.age << endl;
            cout << "Course: " << student.course << endl;
            cout << "------------------------" << endl;
        }
    }

    void deleteStudent() {
        int rollNumber;
        cout << "Enter the Roll Number of the student to delete: ";
        cin >> rollNumber;
        clearInputBuffer();

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->rollNumber == rollNumber) {
                students.erase(it);
                cout << "Student record deleted successfully!" << endl;
                return;
            }
        }
        cout << "Student with Roll Number " << rollNumber << " not found!" << endl;
    }

    void updateStudent() {
        int rollNumber;
        cout << "Enter the Roll Number of the student to update: ";
        cin >> rollNumber;
        clearInputBuffer();

        for (auto &student : students) {
            if (student.rollNumber == rollNumber) {
                cout << "Enter New Name: ";
                getline(cin, student.name);
                do {
                    cout << "Enter New Age: ";
                    cin >> student.age;
                    clearInputBuffer();
                } while (!validateAge(student.age));
                cout << "Enter New Course: ";
                getline(cin, student.course);

                cout << "Student record updated successfully!" << endl;
                return;
            }
        }
        cout << "Student with Roll Number " << rollNumber << " not found!" << endl;
    }

    void searchStudent() const {
        int rollNumber;
        cout << "Enter the Roll Number of the student to search: ";
        cin >> rollNumber;
        //clearInputBuffer();

        for (const auto &student : students) {
            if (student.rollNumber == rollNumber) {
                cout << "Roll Number: " << student.rollNumber << endl;
                cout << "Name: " << student.name << endl;
                cout << "Age: " << student.age << endl;
                cout << "Course: " << student.course << endl;
                return;
            }
        }
        cout << "Student with Roll Number " << rollNumber << " not found!" << endl;
    }

    void menu() {
        int choice;
        do {
            cout << "\n--- Student Management System ---\n";
            cout << "1. Add Student\n";
            cout << "2. Display All Students\n";
            cout << "3. Delete Student\n";
            cout << "4. Update Student\n";
            cout << "5. Search Student\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            clearInputBuffer();

            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    displayStudents();
                    break;
                case 3:
                    deleteStudent();
                    break;
                case 4:
                    updateStudent();
                    break;
                case 5:
                    searchStudent();
                    break;
                case 6:
                    cout << "Exiting the system...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 6);
    }
};

int main() {
    StudentManagementSystem sms;
    sms.menu();
    return 0;
}