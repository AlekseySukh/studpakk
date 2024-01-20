#include <iostream>
#include <vector>

class Student {
private:
    std::string name;
    int marks;

public:
    Student(const std::string& studentName) : name(studentName), marks(0) {}

    void addMark(int mark) {
        marks += mark;
    }

    bool isHonorStudent() const {
        
        return marks >= 90;
    }

    const std::string& getName() const {
        return name;
    }
};

class SchoolSystem {
private:
    std::vector<Student> students;

public:
    void addStudent(const std::string& studentName) {
        students.emplace_back(studentName);
    }

    void giveMark(const std::string& studentName, int mark) {
        for (auto& student : students) {
            if (student.getName() == studentName) {
                student.addMark(mark);
                break;
            }
        }
    }

    void printStudentStatus() const {
        for (const auto& student : students) {
            std::cout << "Студент: " << student.getName() << ", Отличник: "
                      << (student.isHonorStudent() ? "Да" : "Нет") << std::endl;
        }
    }
};

int main() {
    SchoolSystem school;

    
    school.addStudent("Саня");
    school.addStudent("Гриша");

    
    school.giveMark("Саня", 95);
    school.giveMark("Гриша", 85);

    
    school.printStudentStatus();

    return 0;
}
