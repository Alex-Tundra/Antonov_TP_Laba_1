#define _CRT_SECURE_NO_WARNINGS
#include "teacher.h"
#include <iostream>
#include <cwchar>

// Добавляем inline функцию вместо std::max
template<typename T>
inline T my_max(T a, T b) {
    return (a > b) ? a : b;
}

Teacher::Teacher() : Base(), groups(nullptr), subjects(nullptr),
groupsCount(0), subjectsCount(0),
groupsCapacity(5), subjectsCapacity(5) {
    groups = new wchar_t* [groupsCapacity];
    subjects = new wchar_t* [subjectsCapacity];
    std::wcout << L"Конструктор преподавателя по умолчанию вызван" << std::endl;
}

Teacher::Teacher(const wchar_t* name, const wchar_t** grps, int grpCount, const wchar_t** subj, int subjCount)
    : Base(name), groups(nullptr), subjects(nullptr),
    groupsCount(0), subjectsCount(0),
    groupsCapacity(my_max(5, grpCount + 5)), subjectsCapacity(my_max(5, subjCount + 5)) {

    groups = new wchar_t* [groupsCapacity];
    subjects = new wchar_t* [subjectsCapacity];

    for (int i = 0; i < grpCount; i++) {
        addGroup(grps[i]);
    }

    for (int i = 0; i < subjCount; i++) {
        addSubject(subj[i]);
    }

    std::wcout << L"Параметризованный конструктор преподавателя вызван для: " << (name ? name : L"Неизвестно") << std::endl;
}

Teacher::Teacher(const Teacher& other) : Base(other), groups(nullptr), subjects(nullptr),
groupsCount(0), subjectsCount(0),
groupsCapacity(other.groupsCapacity), subjectsCapacity(other.subjectsCapacity) {

    groups = new wchar_t* [groupsCapacity];
    subjects = new wchar_t* [subjectsCapacity];

    for (int i = 0; i < other.groupsCount; i++) {
        addGroup(other.groups[i]);
    }

    for (int i = 0; i < other.subjectsCount; i++) {
        addSubject(other.subjects[i]);
    }

    std::wcout << L"Конструктор копирования преподавателя вызван для: " << other.getFullName() << std::endl;
}

Teacher::~Teacher() {
    std::wcout << L"Деструктор преподавателя вызван для: " << getFullName() << std::endl;
    for (int i = 0; i < groupsCount; i++) {
        delete[] groups[i];
    }
    for (int i = 0; i < subjectsCount; i++) {
        delete[] subjects[i];
    }
    delete[] groups;
    delete[] subjects;
}

void Teacher::resizeGroups() {
    groupsCapacity *= 2;
    wchar_t** newGroups = new wchar_t* [groupsCapacity];
    for (int i = 0; i < groupsCount; i++) {
        newGroups[i] = groups[i];
    }
    delete[] groups;
    groups = newGroups;
}

void Teacher::resizeSubjects() {
    subjectsCapacity *= 2;
    wchar_t** newSubjects = new wchar_t* [subjectsCapacity];
    for (int i = 0; i < subjectsCount; i++) {
        newSubjects[i] = subjects[i];
    }
    delete[] subjects;
    subjects = newSubjects;
}

void Teacher::addGroup(const wchar_t* group) {
    if (groupsCount >= groupsCapacity) {
        resizeGroups();
    }
    groups[groupsCount] = new wchar_t[wcslen(group) + 1];
    wcscpy(groups[groupsCount], group);
    groupsCount++;
}

void Teacher::addSubject(const wchar_t* subject) {
    if (subjectsCount >= subjectsCapacity) {
        resizeSubjects();
    }
    subjects[subjectsCount] = new wchar_t[wcslen(subject) + 1];
    wcscpy(subjects[subjectsCount], subject);
    subjectsCount++;
}

void Teacher::display() const {
    std::wcout << L"ПРЕПОДАВАТЕЛЬ: " << getFullName() << std::endl;
    displayGroups();
    displaySubjects();
}

void Teacher::edit() {
    std::wcout << L"Редактирование преподавателя: " << getFullName() << std::endl;

    wchar_t buffer[100];

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::wcout << L"Введите новое ФИО: ";
    std::wcin.getline(buffer, 100);
    setFullName(buffer);

    int choice;
    do {
        std::wcout << L"\nМеню редактирования преподавателя:" << std::endl;
        std::wcout << L"1. Добавить группу" << std::endl;
        std::wcout << L"2. Удалить группу" << std::endl;
        std::wcout << L"3. Добавить предмет" << std::endl;
        std::wcout << L"4. Удалить предмет" << std::endl;
        std::wcout << L"5. Показать группы" << std::endl;
        std::wcout << L"6. Показать предметы" << std::endl;
        std::wcout << L"0. Завершить редактирование" << std::endl;
        std::wcout << L"Выбор: ";
        std::wcin >> choice;
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            addNewGroup();
            break;
        case 2:
            removeGroup();
            break;
        case 3:
            addNewSubject();
            break;
        case 4:
            removeSubject();
            break;
        case 5:
            displayGroups();
            break;
        case 6:
            displaySubjects();
            break;
        case 0:
            break;
        default:
            std::wcout << L"Неверный выбор!" << std::endl;
        }
    } while (choice != 0);
}

Base* Teacher::clone() const {
    return new Teacher(*this);
}

void Teacher::addNewGroup() {
    wchar_t buffer[100];
    std::wcout << L"Введите название группы: ";
    std::wcin.getline(buffer, 100);
    addGroup(buffer);
    std::wcout << L"Группа добавлена успешно!" << std::endl;
}

void Teacher::addNewSubject() {
    wchar_t buffer[100];
    std::wcout << L"Введите название предмета: ";
    std::wcin.getline(buffer, 100);
    addSubject(buffer);
    std::wcout << L"Предмет добавлен успешно!" << std::endl;
}

void Teacher::removeGroup() {
    if (groupsCount == 0) {
        std::wcout << L"Нет групп для удаления!" << std::endl;
        return;
    }

    displayGroups();
    int index;
    std::wcout << L"Введите номер группы для удаления (1-" << groupsCount << L"): ";
    std::wcin >> index;
    std::wcin.ignore();

    if (index < 1 || index > groupsCount) {
        std::wcout << L"Неверный номер группы!" << std::endl;
        return;
    }

    delete[] groups[index - 1];
    for (int i = index - 1; i < groupsCount - 1; i++) {
        groups[i] = groups[i + 1];
    }
    groupsCount--;
    std::wcout << L"Группа удалена успешно!" << std::endl;
}

void Teacher::removeSubject() {
    if (subjectsCount == 0) {
        std::wcout << L"Нет предметов для удаления!" << std::endl;
        return;
    }

    displaySubjects();
    int index;
    std::wcout << L"Введите номер предмета для удаления (1-" << subjectsCount << L"): ";
    std::wcin >> index;
    std::wcin.ignore();

    if (index < 1 || index > subjectsCount) {
        std::wcout << L"Неверный номер предмета!" << std::endl;
        return;
    }

    delete[] subjects[index - 1];
    for (int i = index - 1; i < subjectsCount - 1; i++) {
        subjects[i] = subjects[i + 1];
    }
    subjectsCount--;
    std::wcout << L"Предмет удален успешно!" << std::endl;
}

void Teacher::displayGroups() const {
    std::wcout << L"  Группы (" << groupsCount << L"): ";
    if (groupsCount == 0) {
        std::wcout << L"Нет групп" << std::endl;
    }
    else {
        for (int i = 0; i < groupsCount; i++) {
            std::wcout << groups[i];
            if (i < groupsCount - 1) std::wcout << L", ";
        }
        std::wcout << std::endl;
    }
}

void Teacher::displaySubjects() const {
    std::wcout << L"  Предметы (" << subjectsCount << L"): ";
    if (subjectsCount == 0) {
        std::wcout << L"Нет предметов" << std::endl;
    }
    else {
        for (int i = 0; i < subjectsCount; i++) {
            std::wcout << subjects[i];
            if (i < subjectsCount - 1) std::wcout << L", ";
        }
        std::wcout << std::endl;
    }
}

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        Base::operator=(other);

        for (int i = 0; i < groupsCount; i++) {
            delete[] groups[i];
        }
        for (int i = 0; i < subjectsCount; i++) {
            delete[] subjects[i];
        }
        delete[] groups;
        delete[] subjects;

        groupsCount = 0;
        subjectsCount = 0;
        groupsCapacity = other.groupsCapacity;
        subjectsCapacity = other.subjectsCapacity;

        groups = new wchar_t* [groupsCapacity];
        subjects = new wchar_t* [subjectsCapacity];

        for (int i = 0; i < other.groupsCount; i++) {
            addGroup(other.groups[i]);
        }

        for (int i = 0; i < other.subjectsCount; i++) {
            addSubject(other.subjects[i]);
        }
    }
    return *this;
}