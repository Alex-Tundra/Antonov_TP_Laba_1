#include "teacher.h"
#include <iostream>
#include <cstring>

Teacher::Teacher() : Base(), groups(nullptr), subjects(nullptr),
groupsCount(0), subjectsCount(0),
groupsCapacity(5), subjectsCapacity(5) {
    groups = new char* [groupsCapacity];
    subjects = new char* [subjectsCapacity];
    std::cout << "Teacher default constructor called" << std::endl;
}

Teacher::Teacher(const char* name, const char** grps, int grpCount, const char** subj, int subjCount)
    : Base(name), groups(nullptr), subjects(nullptr),
    groupsCount(0), subjectsCount(0),
    groupsCapacity(std::max(5, grpCount + 5)), subjectsCapacity(std::max(5, subjCount + 5)) {

    groups = new char* [groupsCapacity];
    subjects = new char* [subjectsCapacity];

    for (int i = 0; i < grpCount; i++) {
        addGroup(grps[i]);
    }

    for (int i = 0; i < subjCount; i++) {
        addSubject(subj[i]);
    }

    std::cout << "Teacher parameterized constructor called for: " << (name ? name : "Unknown") << std::endl;
}

Teacher::Teacher(const Teacher& other) : Base(other), groups(nullptr), subjects(nullptr),
groupsCount(0), subjectsCount(0),
groupsCapacity(other.groupsCapacity), subjectsCapacity(other.subjectsCapacity) {

    groups = new char* [groupsCapacity];
    subjects = new char* [subjectsCapacity];

    for (int i = 0; i < other.groupsCount; i++) {
        addGroup(other.groups[i]);
    }

    for (int i = 0; i < other.subjectsCount; i++) {
        addSubject(other.subjects[i]);
    }

    std::cout << "Teacher copy constructor called for: " << other.getFullName() << std::endl;
}

Teacher::~Teacher() {
    std::cout << "Teacher destructor called for: " << getFullName() << std::endl;
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
    char** newGroups = new char* [groupsCapacity];
    for (int i = 0; i < groupsCount; i++) {
        newGroups[i] = groups[i];
    }
    delete[] groups;
    groups = newGroups;
}

void Teacher::resizeSubjects() {
    subjectsCapacity *= 2;
    char** newSubjects = new char* [subjectsCapacity];
    for (int i = 0; i < subjectsCount; i++) {
        newSubjects[i] = subjects[i];
    }
    delete[] subjects;
    subjects = newSubjects;
}

void Teacher::addGroup(const char* group) {
    if (groupsCount >= groupsCapacity) {
        resizeGroups();
    }
    groups[groupsCount] = new char[strlen(group) + 1];
    strcpy(groups[groupsCount], group);
    groupsCount++;
}

void Teacher::addSubject(const char* subject) {
    if (subjectsCount >= subjectsCapacity) {
        resizeSubjects();
    }
    subjects[subjectsCount] = new char[strlen(subject) + 1];
    strcpy(subjects[subjectsCount], subject);
    subjectsCount++;
}

void Teacher::display() const {
    std::cout << "TEACHER: " << getFullName() << std::endl;
    displayGroups();
    displaySubjects();
}

void Teacher::edit() {
    std::cout << "Editing Teacher: " << getFullName() << std::endl;

    char buffer[100];
    std::cout << "Enter new full name: ";
    std::cin.ignore();
    std::cin.getline(buffer, 100);
    setFullName(buffer);

    int choice;
    do {
        std::cout << "\nTeacher Editing Menu:" << std::endl;
        std::cout << "1. Add group" << std::endl;
        std::cout << "2. Remove group" << std::endl;
        std::cout << "3. Add subject" << std::endl;
        std::cout << "4. Remove subject" << std::endl;
        std::cout << "5. Display groups" << std::endl;
        std::cout << "6. Display subjects" << std::endl;
        std::cout << "0. Finish editing" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: addNewGroup(); break;
        case 2: removeGroup(); break;
        case 3: addNewSubject(); break;
        case 4: removeSubject(); break;
        case 5: displayGroups(); break;
        case 6: displaySubjects(); break;
        case 0: break;
        default: std::cout << "Invalid choice!" << std::endl;
        }
    } while (choice != 0);
}

Base* Teacher::clone() const {
    return new Teacher(*this);
}

void Teacher::addNewGroup() {
    char buffer[100];
    std::cout << "Enter group name: ";
    std::cin.ignore();
    std::cin.getline(buffer, 100);
    addGroup(buffer);
    std::cout << "Group added successfully!" << std::endl;
}

void Teacher::addNewSubject() {
    char buffer[100];
    std::cout << "Enter subject name: ";
    std::cin.ignore();
    std::cin.getline(buffer, 100);
    addSubject(buffer);
    std::cout << "Subject added successfully!" << std::endl;
}

void Teacher::removeGroup() {
    if (groupsCount == 0) {
        std::cout << "No groups to remove!" << std::endl;
        return;
    }

    displayGroups();
    int index;
    std::cout << "Enter group number to remove (1-" << groupsCount << "): ";
    std::cin >> index;

    if (index < 1 || index > groupsCount) {
        std::cout << "Invalid group number!" << std::endl;
        return;
    }

    delete[] groups[index - 1];
    for (int i = index - 1; i < groupsCount - 1; i++) {
        groups[i] = groups[i + 1];
    }
    groupsCount--;
    std::cout << "Group removed successfully!" << std::endl;
}

void Teacher::removeSubject() {
    if (subjectsCount == 0) {
        std::cout << "No subjects to remove!" << std::endl;
        return;
    }

    displaySubjects();
    int index;
    std::cout << "Enter subject number to remove (1-" << subjectsCount << "): ";
    std::cin >> index;

    if (index < 1 || index > subjectsCount) {
        std::cout << "Invalid subject number!" << std::endl;
        return;
    }

    delete[] subjects[index - 1];
    for (int i = index - 1; i < subjectsCount - 1; i++) {
        subjects[i] = subjects[i + 1];
    }
    subjectsCount--;
    std::cout << "Subject removed successfully!" << std::endl;
}

void Teacher::displayGroups() const {
    std::cout << "  Groups (" << groupsCount << "): ";
    if (groupsCount == 0) {
        std::cout << "None" << std::endl;
    }
    else {
        for (int i = 0; i < groupsCount; i++) {
            std::cout << groups[i];
            if (i < groupsCount - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

void Teacher::displaySubjects() const {
    std::cout << "  Subjects (" << subjectsCount << "): ";
    if (subjectsCount == 0) {
        std::cout << "None" << std::endl;
    }
    else {
        for (int i = 0; i < subjectsCount; i++) {
            std::cout << subjects[i];
            if (i < subjectsCount - 1) std::cout << ", ";
        }
        std::cout << std::endl;
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

        groups = new char* [groupsCapacity];
        subjects = new char* [subjectsCapacity];

        for (int i = 0; i < other.groupsCount; i++) {
            addGroup(other.groups[i]);
        }

        for (int i = 0; i < other.subjectsCount; i++) {
            addSubject(other.subjects[i]);
        }
    }
    return *this;
}