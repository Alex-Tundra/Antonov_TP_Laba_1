#include "student.h"
#include <iostream>
#include <limits>

Student::Student() : Base(), group(nullptr), specialty(nullptr), course(1), averageGrade(0.0) {
    std::cout << "Student default constructor called" << std::endl;
}

Student::Student(const char* name, const char* grp, const char* spec, int crs, double avg)
    : Base(name), group(nullptr), specialty(nullptr), course(crs), averageGrade(avg) {
    copyString(group, grp);
    copyString(specialty, spec);
    std::cout << "Student parameterized constructor called for: " << (name ? name : "Unknown") << std::endl;
}

Student::Student(const Student& other) : Base(other), group(nullptr), specialty(nullptr),
course(other.course), averageGrade(other.averageGrade) {
    copyString(group, other.group);
    copyString(specialty, other.specialty);
    std::cout << "Student copy constructor called for: " << other.getFullName() << std::endl;
}

Student::~Student() {
    std::cout << "Student destructor called for: " << getFullName() << std::endl;
    delete[] group;
    delete[] specialty;
}

void Student::display() const {
    std::cout << "STUDENT: " << getFullName() << std::endl;
    std::cout << "  Group: " << (group ? group : "N/A") << std::endl;
    std::cout << "  Specialty: " << (specialty ? specialty : "N/A") << std::endl;
    std::cout << "  Course: " << course << std::endl;
    std::cout << "  Average Grade: " << averageGrade << std::endl;
}

void Student::edit() {
    std::cout << "Editing Student: " << getFullName() << std::endl;

    char buffer[100];
    int tempInt;
    double tempDouble;

    std::cout << "Enter new full name: ";
    std::cin.ignore();
    std::cin.getline(buffer, 100);
    setFullName(buffer);

    std::cout << "Enter group: ";
    std::cin.getline(buffer, 100);
    setGroup(buffer);

    std::cout << "Enter specialty: ";
    std::cin.getline(buffer, 100);
    setSpecialty(buffer);

    std::cout << "Enter course: ";
    std::cin >> tempInt;
    setCourse(tempInt);

    std::cout << "Enter average grade: ";
    std::cin >> tempDouble;
    setAverageGrade(tempDouble);
}

Base* Student::clone() const {
    return new Student(*this);
}

const char* Student::getGroup() const { return group ? group : "N/A"; }
const char* Student::getSpecialty() const { return specialty ? specialty : "N/A"; }
int Student::getCourse() const { return course; }
double Student::getAverageGrade() const { return averageGrade; }

void Student::setGroup(const char* grp) {
    if (!grp || strlen(grp) == 0) {
        throw std::invalid_argument("Group cannot be empty");
    }
    copyString(group, grp);
}

void Student::setSpecialty(const char* spec) {
    if (!spec || strlen(spec) == 0) {
        throw std::invalid_argument("Specialty cannot be empty");
    }
    copyString(specialty, spec);
}

void Student::setCourse(int crs) {
    if (crs < 1 || crs > 6) {
        throw std::invalid_argument("Course must be between 1 and 6");
    }
    course = crs;
}

void Student::setAverageGrade(double avg) {
    if (avg < 0.0 || avg > 10.0) {
        throw std::invalid_argument("Average grade must be between 0.0 and 10.0");
    }
    averageGrade = avg;
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Base::operator=(other);
        copyString(group, other.group);
        copyString(specialty, other.specialty);
        course = other.course;
        averageGrade = other.averageGrade;
    }
    return *this;
}