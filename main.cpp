#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Defining the constants
const int NUM_CLASSES_BIO = 3;
const int NUM_CLASSES_MATH = 5;
const int STUDENTS_PER_CLASS = 40;

// Defining the subjects
const std::string BIO_SUBJECTS[] = {"Biology", "Physics", "Chemistry"};
const std::string MATH_SUBJECTS[] = {"Combined Maths", "Physics", "Chemistry"};

// Structure to store information
struct Student {
    std::string name;
    std::string stream;
    int classNumber;
    int marks[3]; // Assuming we have 3 subjects
    int totalMarks;
    int rank;

    // Constructor 
    Student(std::string n, std::string s, int cn, int m1, int m2, int m3)
        : name(n), stream(s), classNumber(cn) {
        marks[0] = m1;
        marks[1] = m2;
        marks[2] = m3;
        totalMarks = m1 + m2 + m3;
        rank = 0; 
    }
};

// Function to calculate total marks and rank students
void calculateRank(std::vector<Student>& students) {
    // Calculate total marks and assign ranks
    for (auto& student : students) {
        student.totalMarks = student.marks[0] + student.marks[1] + student.marks[2];
    }

    // Sorting based on total marks 
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) { return a.totalMarks > b.totalMarks; });

    // Assign ranks
    for (size_t i = 0; i < students.size(); ++i) {
        students[i].rank = i + 1;
    }
}

// Function to display and write ranks 
void displayAndWriteRanks(const std::vector<Student>& students, const std::string& fileName) {
    // Display and write ranks
    std::ofstream outFile(fileName);

    if (outFile.is_open()) {
        std::cout << "School Rank\tClass Rank\tName\t\tStream\tClass\tTotal Marks\n";
        outFile << "School Rank\tClass Rank\tName\t\tStream\tClass\tTotal Marks\n";

        for (const auto& student : students) {
            std::cout << student.rank << "\t\t" << student.rank << "\t\t" << student.name << "\t\t"
                      << student.stream << "\t" << student.classNumber << "\t" << student.totalMarks << "\n";
            outFile << student.rank << "\t\t" << student.rank << "\t\t" << student.name << "\t\t"
                    << student.stream << "\t" << student.classNumber << "\t" << student.totalMarks << "\n";
        }

        outFile.close();
    } else {
        std::cerr << "Unable to open the output file.\n";
    }
}

int main() {
    std::vector<Student> students;

    // Adding data of students
    students.emplace_back("Student1", "Bio", 1, 90, 85, 88);
    students.emplace_back("Student2", "Bio", 3, 95, 92, 88);
    students.emplace_back("Student3", "Math", 5, 91, 84, 70);
    students.emplace_back("Student4", "Math", 8, 78, 86, 83);
    

    // Calculating and displaying ranks
    calculateRank(students);
    displayAndWriteRanks(students, "rank_output.txt");

    return 0;
}
