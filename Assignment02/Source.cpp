#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct STUDENT_DATA {
    string firstName;
    string lastName;
};

void loadStudentData(vector<STUDENT_DATA>& students) {
    ifstream file("StudentData.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file" << std::endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            STUDENT_DATA student;
            student.firstName = line.substr(0, commaPos);  // Get first name
            student.lastName = line.substr(commaPos + 1);  // Get last name
            students.push_back(student);  // Add student to the vector
        }
    }
    file.close();
}


int main() {
    std::vector<STUDENT_DATA> students;  

    loadStudentData(students);  

#ifdef _DEBUG
    
    std::cout << "Student List:" << std::endl;
    for (const auto& student : students) {
        std::cout << "First Name: " << student.firstName << ", Last Name: " << student.lastName << std::endl;
    }
#endif

    return 1;  
}
