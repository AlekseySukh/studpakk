#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Parent;

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
    int marksCount;
    bool alwaysGive5;
    bool alwaysGive2;

public:
    Teacher(const std::string& teacherName, const std::string& teacherMood, bool always5, bool always2)
        : name(teacherName), mood(teacherMood), marksCount(0), alwaysGive5(always5), alwaysGive2(always2) {}

    void giveMark(Student& student) {
        int mark = 0;

        if (alwaysGive5) {
            mark = 5;
        } else if (alwaysGive2) {
            mark = 2;
        } else {
            int randomValue = rand() % 2;

            if (mood == "хорошее") {
                mark = (student.isHonorStudent()) ? 5 : 4;
            } else {
                mark = (randomValue == 0) ? 4 : (student.isHonorStudent() ? 5 : (rand() % 2 + 2));
            }
        }

        student.addMark(mark);

        marksCount++;
        if (marksCount % 5 == 0) {
            mood = (rand() % 2 == 0) ? "хорошее" : "плохое";
            std::cout << "Преподаватель " << name << " сменил настроение на " << mood << std::endl;
        }

        std::cout << "Преподаватель " << name << " выставил оценку " << mark
                  << " студенту " << student.getName() << std::endl;
    }

    const std::string& getName() const {
        return name;
    }
};

class Parent {
private:
    std::string name;
    std::string mood;
    Student* child;

public:
    Parent(const std::string& parentName, const std::string& parentMood, Student* parentChild)
        : name(parentName), mood(parentMood), child(parentChild) {}

    void tellAboutChild() const {
        if (child != nullptr) {
            std::cout << "Родитель " << name << " рассказывает о своем ребенке " << child->getName() << ": ";
            if (mood == "хорошее") {
                std::cout << "Мой ребенок хорош!";
            } else {
                std::cout << "Мой ребенок даун...";
            }
            std::cout << std::endl;
        } else {
            std::cerr << "Ошибка: У родителя нет ребенка." << std::endl;
        }
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
    std::vector<Parent> parents;

public:
    SchoolSystem() {
        std::srand(std::time(0));
    }

    void addStudent(const std::string& studentName) {
        students.emplace_back(studentName);
    }

    void addTeacher(const std::string& teacherName, const std::string& teacherMood, bool alwaysGive5, bool alwaysGive2) {
        teachers.emplace_back(teacherName, teacherMood, alwaysGive5, alwaysGive2);
    }

    void addParent(const std::string& parentName, const std::string& parentMood, Student* parentChild) {
        parents.emplace_back(parentName, parentMood, parentChild);
    }

    void addChildToParent(const std::string& parentName, const std::string& childName) {
        Student* child = findStudent(childName);
        if (child != nullptr) {
            Parent* parent = findParent(parentName);
            if (parent != nullptr) {
                parent->tellAboutChild();
            }
        }
    }

    Student* findStudent(const std::string& studentName) {
        for (auto& student : students) {
            if (student.getName() == studentName) {
                return &student;
            }
        }
        return nullptr;
    }

    Parent* findParent(const std::string& parentName) {
        for (auto& parent : parents) {
            if (parent.getName() == parentName) {
                return &parent;
            }
        }
        return nullptr;
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

    school.addTeacher("Осипова", "плохое", false, false);
    school.addTeacher("Чеканов", "хорошее", false, true);
    school.addTeacher("Иваненко", "плохое", true, false);
    school.addTeacher("Ефремов", "хорошее", false, false);
    school.addTeacher("Крестникова", "плохое", false, false);

    std::vector<Student> studentsForAlgebra = {Student("Гриша"), Student("Саня")};
    school.addLesson("Алгебра", Teacher("Чеканов", "хорошее", false, true), studentsForAlgebra);

    std::vector<Student> studentsForMathAnalysis = {Student("Саня"), Student("Гриша")};
    school.addLesson("Матанализ", Teacher("Осипова", "плохое", false, false), studentsForMathAnalysis);

    std::vector<Student> studentsForOVP = {Student("Гриша"), Student("Саня")};
    school.addLesson("ОВП", Teacher("Иваненко", "плохое", true, false), studentsForOVP);

    std::vector<Student> studentsForMatLogics = {Student("Гриша"), Student("Саня")};
    school.addLesson("Матлогика", Teacher("Ефремов", "хорошее", false, false), studentsForMatLogics);

    std::vector<Student> studentsForAlgorithms = {Student("Саня"), Student("Гриша")};
    school.addLesson("Алгоритмы", Teacher("Крестникова", "плохое", false, false), studentsForAlgorithms);

    school.conductAllLessons();
    school.printStudentStatus();

    school.addParent("Родитель1", "хорошее", school.findStudent("Саня"));
    school.addParent("Родитель2", "плохое", school.findStudent("Гриша"));

    school.addChildToParent("Родитель1", "Саня");
    school.addChildToParent("Родитель2", "Саня"); // Это вызовет ошибку, так как у Родителя2 нет Сани в качестве ребенка

    return 0;
}
