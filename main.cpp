#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

// Defining constants
const int NUM_CLASSES_BIO = 3;
const int NUM_CLASSES_MATH = 5;
const int STUDENTS_PER_CLASS = 40;

// Defining subjects
const std::string BIO_SUBJECTS[] = {"Biology", "Physics", "Chemistry"};
const std::string MATH_SUBJECTS[] = {"Combined Maths", "Physics", "Chemistry"};

// Structure to store information
struct Student {
    std::string name;
    std::string stream;
    int classNumber;
    int marks[3]; //  Assuming we have 3 subjects
    int totalMarks;
    double zScoreTotalMarks;
    int rankTotalMarks;
    double zScore;
    int rank;

    // Constructor 
    Student(std::string n, std::string s, int cn, int m1, int m2, int m3)
        : name(n), stream(s), classNumber(cn) {
        marks[0] = m1;
        marks[1] = m2;
        marks[2] = m3;
        totalMarks = m1 + m2 + m3;
        rank = 0;
        zScore = 0.0;
        zScoreTotalMarks = 0.0;
    }
};

// Function to calculate z-scores
void calculateZScores(std::vector<Student>& students) {
    // Calculate mean and standard deviation 
    double meanTotalMarks = 0.0;
    double meanSquaresTotalMarks = 0.0;
    for (const auto& student : students) {
        meanTotalMarks += student.totalMarks;
        meanSquaresTotalMarks += std::pow(student.totalMarks, 2);
    }
    meanTotalMarks /= students.size();
    double stdDevTotalMarks = std::sqrt(meanSquaresTotalMarks / students.size() - std::pow(meanTotalMarks, 2));

    // Calculate z-scores for total marks
    for (auto& student : students) {
        student.zScoreTotalMarks = (student.totalMarks - meanTotalMarks) / stdDevTotalMarks;
    }

    // Calculate mean and standard deviation for z-scores
    double meanZScore = 0.0;
    double meanSquaresZScore = 0.0;
    for (const auto& student : students) {
        meanZScore += student.zScoreTotalMarks;
        meanSquaresZScore += std::pow(student.zScoreTotalMarks, 2);
    }
    meanZScore /= students.size();
    double stdDevZScore = std::sqrt(meanSquaresZScore / students.size() - std::pow(meanZScore, 2));

    // Calculate z-scores
    for (auto& student : students) {
        student.zScore = (student.zScoreTotalMarks - meanZScore) / stdDevZScore;
    }
}

// Function to calculate total marks and rank students
void calculateRanks(std::vector<Student>& students) {
    
    for (auto& student : students) {
        student.totalMarks = student.marks[0] + student.marks[1] + student.marks[2];
    }

    // Sorting students based on total marks
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) { return a.totalMarks > b.totalMarks; });

    // Assigning ranks for total marks
    for (size_t i = 0; i < students.size(); ++i) {
        students[i].rankTotalMarks = i + 1;
    }

    // Calculating z-scores and ranks
    calculateZScores(students);

    // Sorting students based on z-scores
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) { return a.zScore > b.zScore; });

    // Assigning ranks based on z-scores
    for (size_t i = 0; i < students.size(); ++i) {
        students[i].rank = i + 1;
    }
}

// Function to display and write ranks to a file
void displayAndWriteRanks(const std::vector<Student>& students, const std::string& fileName) {
    // Displaying ranks 
    std::ofstream outFile(fileName);

    if (outFile.is_open()) {
        std::cout << "Total Marks Rank\tZ-Score Rank\tName\t\tStream\tClass\tTotal Marks\tZ-Score\n";
        outFile << "Total Marks Rank\tZ-Score Rank\tName\t\tStream\tClass\tTotal Marks\tZ-Score\n";

        for (const auto& student : students) {
            std::cout << student.rankTotalMarks << "\t\t" << student.rank << "\t\t" << student.name << "\t\t"
                      << student.stream << "\t" << student.classNumber << "\t" << student.totalMarks << "\t\t"
                      << student.zScore << "\n";
            outFile << student.rankTotalMarks << "\t\t" << student.rank << "\t\t" << student.name << "\t\t"
                    << student.stream << "\t" << student.classNumber << "\t" << student.totalMarks << "\t\t"
                    << student.zScore << "\n";
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
    calculateRanks(students);
    displayAndWriteRanks(students, "rank_output.txt");

    return 0;
}
