#include <iostream>
#include <vector>
#include <cstdlib>  
#include <ctime>    

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
    std::string mood;  

public:
    Teacher(const std::string& teacherName, const std::string& teacherMood)
        : name(teacherName), mood(teacherMood) {}

    void giveMark(Student& student) {
        int mark = 0;

        
        int randomValue = rand() % 2; 

        if (mood == "хорошее") {
            mark = (student.isHonorStudent()) ? 5 : 4;
        } else {
            mark = (randomValue == 0) ? 4 : (student.isHonorStudent() ? 5 : (rand() % 2 + 2));
        }

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
    SchoolSystem() {
        
        std::srand(std::time(0));
    }

    void addStudent(const std::string& studentName) {
        students.emplace_back(studentName);
    }

    void addTeacher(const std::string& teacherName, const std::string& teacherMood) {
        teachers.emplace_back(teacherName, teacherMood);
    }

    void giveMark(const std::string& teacherName, const std::string& studentName) {
        for (auto& teacher : teachers) {
            if (teacherName == teacher.getName()) {
                for (auto& student : students) {
                    if (studentName == student.getName()) {
                        teacher.giveMark(student);
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

    
    school.addTeacher("Чеканов", "хорошее");
    school.addTeacher("Осипова", "плохое");

    
    school.giveMark("Чеканов", "Саня");
    school.giveMark("Осипова", "Гриша");

   
    school.printStudentStatus();

    return 0;
}
