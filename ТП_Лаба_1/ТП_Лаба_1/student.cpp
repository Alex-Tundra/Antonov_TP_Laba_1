#define _CRT_SECURE_NO_WARNINGS
#include "student.h"
#include <iostream>
#include <limits>
#include <sstream>

Student::Student() : Base(), group(nullptr), specialty(nullptr), course(1), averageGrade(0.0) {
    std::wcout << L"����������� �������� �� ��������� ������" << std::endl;
}

Student::Student(const wchar_t* name, const wchar_t* grp, const wchar_t* spec, int crs, double avg)
    : Base(name), group(nullptr), specialty(nullptr), course(crs), averageGrade(avg) {
    copyString(group, grp);
    copyString(specialty, spec);
    std::wcout << L"����������������� ����������� �������� ������ ���: " << (name ? name : L"����������") << std::endl;
}

Student::Student(const Student& other) : Base(other), group(nullptr), specialty(nullptr),
course(other.course), averageGrade(other.averageGrade) {
    copyString(group, other.group);
    copyString(specialty, other.specialty);
    std::wcout << L"����������� ����������� �������� ������ ���: " << other.getFullName() << std::endl;
}

Student::~Student() {
    std::wcout << L"���������� �������� ������ ���: " << getFullName() << std::endl;
    delete[] group;
    delete[] specialty;
}

void Student::display() const {
    std::wcout << L"�������: " << getFullName() << std::endl;
    std::wcout << L"  ������: " << (group ? group : L"�� �������") << std::endl;
    std::wcout << L"  �������������: " << (specialty ? specialty : L"�� �������") << std::endl;
    std::wcout << L"  ����: " << course << std::endl;
    std::wcout << L"  ������� ����: " << averageGrade << std::endl;
}

void Student::edit() {
    std::wcout << L"�������������� ��������: " << getFullName() << std::endl;

    wchar_t buffer[100];
    int tempInt;
    double tempDouble;

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::wcout << L"������� ����� ���: ";
    std::wcin.getline(buffer, 100);
    setFullName(buffer);

    std::wcout << L"������� ������: ";
    std::wcin.getline(buffer, 100);
    setGroup(buffer);

    std::wcout << L"������� �������������: ";
    std::wcin.getline(buffer, 100);
    setSpecialty(buffer);

    std::wcout << L"������� ����: ";
    std::wcin >> tempInt;
    setCourse(tempInt);

    std::wcout << L"������� ������� ����: ";
    std::wcin >> tempDouble;
    setAverageGrade(tempDouble);

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::wcout << L"������ �������� ��������� �������!" << std::endl;
}

Base* Student::clone() const {
    return new Student(*this);
}

void Student::saveToStream(std::ostream& os) const {
    // ��������� ��� �������
    os << "Student" << std::endl;

    // ��������� ������ � UTF-8
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
    // ������ ������ �� ������
    std::string name, group, specialty;
    int crs;
    double avg;

    std::getline(is, name);
    std::getline(is, group);
    std::getline(is, specialty);
    is >> crs;
    is >> avg;
    is.ignore(); // ���������� ������ ����� ������

    // ������������ � wchar_t
    wchar_t wname[256], wgroup[256], wspecialty[256];
    mbstowcs(wname, name.c_str(), 256);
    mbstowcs(wgroup, group.c_str(), 256);
    mbstowcs(wspecialty, specialty.c_str(), 256);

    // ������������� ��������
    setFullName(wname);
    setGroup(wgroup);
    setSpecialty(wspecialty);
    setCourse(crs);
    setAverageGrade(avg);
}

const wchar_t* Student::getGroup() const { return group ? group : L"�� �������"; }
const wchar_t* Student::getSpecialty() const { return specialty ? specialty : L"�� �������"; }
int Student::getCourse() const { return course; }
double Student::getAverageGrade() const { return averageGrade; }

void Student::setGroup(const wchar_t* grp) {
    if (!grp || wcslen(grp) == 0) {
        throw std::invalid_argument("������ �� ����� ���� ������");
    }
    copyString(group, grp);
}

void Student::setSpecialty(const wchar_t* spec) {
    if (!spec || wcslen(spec) == 0) {
        throw std::invalid_argument("������������� �� ����� ���� ������");
    }
    copyString(specialty, spec);
}

void Student::setCourse(int crs) {
    if (crs < 1 || crs > 6) {
        throw std::invalid_argument("���� ������ ���� �� 1 �� 6");
    }
    course = crs;
}

void Student::setAverageGrade(double avg) {
    if (avg < 0.0 || avg > 10.0) {
        throw std::invalid_argument("������� ���� ������ ���� �� 0.0 �� 10.0");
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