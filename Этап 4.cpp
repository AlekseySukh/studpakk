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

class Lesson {
private:
    std::string subject;
    Teacher teacher;
    std::vector<Student> students;

public:
    Lesson(const std::string& lessonSubject, const Teacher& lessonTeacher, const std::vector<Student>& lessonStudents)
        : subject(lessonSubject), teacher(lessonTeacher), students(lessonStudents) {}

    void conductLesson() {
        std::cout << "Занятие по " << subject << " начато. Преподаватель: " << teacher.getName() << std::endl;
        
        for (auto& student : students) {
            teacher.giveMark(student);
        }

        std::cout << "Занятие по " << subject << " завершено." << std::endl;
    }
};

class SchoolSystem {
private:
    std::vector<Student> students;
    std::vector<Teacher> teachers;
    std::vector<Lesson> lessons;

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

    void addLesson(const std::string& lessonSubject, const Teacher& lessonTeacher, const std::vector<Student>& lessonStudents) {
        lessons.emplace_back(lessonSubject, lessonTeacher, lessonStudents);
    }

    void conductAllLessons() {
        for (auto& lesson : lessons) {
            lesson.conductLesson();
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

    // Добавляем преподавателей с настроением
    school.addTeacher("Осипова", "плохое");
    school.addTeacher("Чеканов", "хорошее");

    
    std::vector<Student> studentsForAlgebra = {Student("Гриша"), Student("Саня")};
    school.addLesson("Алгебра", Teacher("Чеканов", "хорошее"), studentsForAlgebra);

    std::vector<Student> studentsForMathAnalysis = {Student("Саня"), Student("Гриша")};
    school.addLesson("Матанализ", Teacher("Осипова", "плохое"), studentsForMathAnalysis);

    
    school.conductAllLessons();

    
    school.printStudentStatus();

    return 0;
}
