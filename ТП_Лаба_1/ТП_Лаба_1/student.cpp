#define _CRT_SECURE_NO_WARNINGS
#include "student.h"
#include <iostream>
#include <limits>
#include <sstream>

Student::Student() : Base(), group(nullptr), specialty(nullptr), course(1), averageGrade(0.0) {
    std::wcout << L"Конструктор студента по умолчанию вызван" << std::endl;
}

Student::Student(const wchar_t* name, const wchar_t* grp, const wchar_t* spec, int crs, double avg)
    : Base(name), group(nullptr), specialty(nullptr), course(crs), averageGrade(avg) {
    copyString(group, grp);
    copyString(specialty, spec);
    std::wcout << L"Параметризованный конструктор студента вызван для: " << (name ? name : L"Неизвестно") << std::endl;
}

Student::Student(const Student& other) : Base(other), group(nullptr), specialty(nullptr),
course(other.course), averageGrade(other.averageGrade) {
    copyString(group, other.group);
    copyString(specialty, other.specialty);
    std::wcout << L"Конструктор копирования студента вызван для: " << other.getFullName() << std::endl;
}

Student::~Student() {
    std::wcout << L"Деструктор студента вызван для: " << getFullName() << std::endl;
    delete[] group;
    delete[] specialty;
}

void Student::display() const {
    std::wcout << L"СТУДЕНТ: " << getFullName() << std::endl;
    std::wcout << L"  Группа: " << (group ? group : L"Не указана") << std::endl;
    std::wcout << L"  Специальность: " << (specialty ? specialty : L"Не указана") << std::endl;
    std::wcout << L"  Курс: " << course << std::endl;
    std::wcout << L"  Средний балл: " << averageGrade << std::endl;
}

void Student::edit() {
    std::wcout << L"Редактирование студента: " << getFullName() << std::endl;

    wchar_t buffer[100];
    int tempInt;
    double tempDouble;

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::wcout << L"Введите новое ФИО: ";
    std::wcin.getline(buffer, 100);
    setFullName(buffer);

    std::wcout << L"Введите группу: ";
    std::wcin.getline(buffer, 100);
    setGroup(buffer);

    std::wcout << L"Введите специальность: ";
    std::wcin.getline(buffer, 100);
    setSpecialty(buffer);

    std::wcout << L"Введите курс: ";
    std::wcin >> tempInt;
    setCourse(tempInt);

    std::wcout << L"Введите средний балл: ";
    std::wcin >> tempDouble;
    setAverageGrade(tempDouble);

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::wcout << L"Данные студента обновлены успешно!" << std::endl;
}

Base* Student::clone() const {
    return new Student(*this);
}

void Student::saveToStream(std::ostream& os) const {
    // Сохраняем тип объекта
    os << "Student" << std::endl;

    // Сохраняем данные в UTF-8
    const wchar_t* wname = getFullName();
    const wchar_t* wgroup = getGroup();
    const wchar_t* wspecialty = getSpecialty();

    char buffer[256];

    wcstombs(buffer, wname, 256);
    os << buffer << std::endl;

    wcstombs(buffer, wgroup, 256);
    os << buffer << std::endl;

    wcstombs(buffer, wspecialty, 256);
    os << buffer << std::endl;

    os << course << std::endl;
    os << averageGrade << std::endl;
}

void Student::loadFromStream(std::istream& is) {
    // Читаем данные из потока
    std::string name, group, specialty;
    int crs;
    double avg;

    std::getline(is, name);
    std::getline(is, group);
    std::getline(is, specialty);
    is >> crs;
    is >> avg;
    is.ignore(); // Игнорируем символ новой строки

    // Конвертируем в wchar_t
    wchar_t wname[256], wgroup[256], wspecialty[256];
    mbstowcs(wname, name.c_str(), 256);
    mbstowcs(wgroup, group.c_str(), 256);
    mbstowcs(wspecialty, specialty.c_str(), 256);

    // Устанавливаем значения
    setFullName(wname);
    setGroup(wgroup);
    setSpecialty(wspecialty);
    setCourse(crs);
    setAverageGrade(avg);
}

const wchar_t* Student::getGroup() const { return group ? group : L"Не указана"; }
const wchar_t* Student::getSpecialty() const { return specialty ? specialty : L"Не указана"; }
int Student::getCourse() const { return course; }
double Student::getAverageGrade() const { return averageGrade; }

void Student::setGroup(const wchar_t* grp) {
    if (!grp || wcslen(grp) == 0) {
        throw std::invalid_argument("Группа не может быть пустой");
    }
    copyString(group, grp);
}

void Student::setSpecialty(const wchar_t* spec) {
    if (!spec || wcslen(spec) == 0) {
        throw std::invalid_argument("Специальность не может быть пустой");
    }
    copyString(specialty, spec);
}

void Student::setCourse(int crs) {
    if (crs < 1 || crs > 6) {
        throw std::invalid_argument("Курс должен быть от 1 до 6");
    }
    course = crs;
}

void Student::setAverageGrade(double avg) {
    if (avg < 0.0 || avg > 10.0) {
        throw std::invalid_argument("Средний балл должен быть от 0.0 до 10.0");
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