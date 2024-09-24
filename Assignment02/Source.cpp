#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Struct to hold student data
struct STUDENT_DATA {
    string firstName;
    string lastName;

#ifdef PRE_RELEASE
    string email;
#endif
};

// Overload the << operator for easy printing 
ostream& operator<<(ostream& os, const STUDENT_DATA& student) {
    os << student.firstName << ", " << student.lastName;
#ifdef PRE_RELEASE
    os << " - " << student.email;
#endif
    return os;
}

// Function to load student data from a file
void loadStudentData(vector<STUDENT_DATA>& students) {
    ifstream file("StudentData.txt");
    if (!file.is_open()) {
        cerr << "Unable to open StudentData.txt file" << std::endl;
        return;
    }

    string line;
    // Read each line from the file
    while (getline(file, line)) {
        size_t commaPos = line.find(','); // Find the position of the comma
        if (commaPos != string::npos) {
            STUDENT_DATA student;
            student.lastName = line.substr(0, commaPos);
            student.firstName = line.substr(commaPos + 1);

#ifdef PRE_RELEASE
            student.email = "No Email";
#endif

            students.push_back(student);
        }
    }
    file.close();
}

#ifdef PRE_RELEASE
// Function to load student emails from a separate file
void loadStudentEmails(vector<STUDENT_DATA>& students) {
    ifstream file("StudentData_Emails.txt");
    if (!file.is_open()) {
        cerr << "Unable to open StudentData_Emails.txt file" << std::endl;
        return;
    }

    string line;
    int index = 0;
    while (getline(file, line) && index < students.size()) {
        size_t commaPos = line.find_last_of(','); // Find the last comma
        if (commaPos != string::npos) {
            students[index].email = line.substr(commaPos + 1);
            index++;
        }
    }
    file.close();
}
#endif

int main() {
    vector<STUDENT_DATA> students; // Vector to store student data

#ifdef _DEBUG
    cout << "Running Debug Version" << endl;
    loadStudentData(students); // Load student data
    cout << "Student List (First Name, Last Name):" << endl;
    for (const auto& student : students) {
        cout << student.firstName << ", " << student.lastName << endl;
    }
#endif

#ifdef PRE_RELEASE
    cout << "Running Pre-Release Version" << endl;
    loadStudentData(students); // Load student data
    loadStudentEmails(students);
    cout << "Student List (First Name, Last Name, Email):" << endl;
    for (const auto& student : students) {
        cout << student << endl;
    }
#else
    cout << "Running Standard Version" << endl;
    loadStudentData(students);
#endif

    return 0;
}
