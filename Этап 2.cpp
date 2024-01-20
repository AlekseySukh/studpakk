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

class Teacher {
private:
    std::string name;

public:
    Teacher(const std::string& teacherName) : name(teacherName) {}

    void giveMark(Student& student, int mark) {
        student.addMark(mark);
        std::cout << "Преподаватель " << name << " выставил оценку " << mark
                  << " студенту " << student.getName() << std::endl;
    }

    const std::string& getName() const {
        return name;
    }
};

class SchoolSystem {
private:
    std::vector<Student> students;
    std::vector<Teacher> teachers;

public:
    void addStudent(const std::string& studentName) {
        students.emplace_back(studentName);
    }

    void addTeacher(const std::string& teacherName) {
        teachers.emplace_back(teacherName);
    }

    void giveMark(const std::string& teacherName, const std::string& studentName, int mark) {
        for (auto& teacher : teachers) {
            if (teacherName == teacher.getName()) {
                for (auto& student : students) {
                    if (studentName == student.getName()) {
                        teacher.giveMark(student, mark);
                        break;
                    }
                }
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

   
    school.addTeacher("Чеканов");
    school.addTeacher("Осипова");

    
    school.giveMark("Чеканов", "Саня", 95);
    school.giveMark("Осипова", "Гриша", 85);

    
    school.printStudentStatus();

    return 0;
}
