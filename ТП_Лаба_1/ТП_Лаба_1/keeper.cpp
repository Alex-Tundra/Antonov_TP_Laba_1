#include "keeper.h"
#include "student.h"
#include "teacher.h"
#include "staff.h"
#include <fstream>
#include <iostream>
#include <typeinfo>

Keeper::Keeper() : size(0), capacity(10) {
    data = new Base * [capacity];
    std::cout << "Keeper default constructor called" << std::endl;
}

Keeper::Keeper(int cap) : size(0), capacity(cap > 0 ? cap : 10) {
    data = new Base * [capacity];
    std::cout << "Keeper parameterized constructor called with capacity: " << capacity << std::endl;
}

Keeper::Keeper(const Keeper& other) : size(other.size), capacity(other.capacity) {
    data = new Base * [capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i]->clone();
    }
    std::cout << "Keeper copy constructor called" << std::endl;
}

Keeper::~Keeper() {
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
    delete[] data;
    std::cout << "Keeper destructor called" << std::endl;
}

void Keeper::resize() {
    capacity *= 2;
    Base** newData = new Base * [capacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void Keeper::add(Base* item) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = item;
    std::cout << "Item added to keeper successfully!" << std::endl;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index for removal");
    }

    delete data[index];
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    std::cout << "Item removed successfully!" << std::endl;
}

void Keeper::displayAll() const {
    if (size == 0) {
        std::cout << "Keeper is empty!" << std::endl;
        return;
    }

    std::cout << "\n=== ALL ITEMS IN KEEPER ===" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Item " << (i + 1) << ":" << std::endl;
        data[i]->display();
        std::cout << std::endl;
    }
}

void Keeper::edit(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index for editing");
    }
    data[index]->edit();
}

void Keeper::saveToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing");
    }

    file << size << std::endl;
    for (int i = 0; i < size; i++) {
        if (dynamic_cast<Student*>(data[i])) {
            file << "Student" << std::endl;
            Student* s = dynamic_cast<Student*>(data[i]);
            file << s->getFullName() << std::endl;
            file << s->getGroup() << std::endl;
            file << s->getSpecialty() << std::endl;
            file << s->getCourse() << std::endl;
            file << s->getAverageGrade() << std::endl;
        }
        else if (dynamic_cast<Teacher*>(data[i])) {
            file << "Teacher" << std::endl;
            Teacher* t = dynamic_cast<Teacher*>(data[i]);
            file << t->getFullName() << std::endl;
            // Groups and subjects would need more complex serialization
        }
        else if (dynamic_cast<Staff*>(data[i])) {
            file << "Staff" << std::endl;
            Staff* st = dynamic_cast<Staff*>(data[i]);
            file << st->getFullName() << std::endl;
            file << st->getPosition() << std::endl;
            file << st->getPhone() << std::endl;
            file << st->getResponsibility() << std::endl;
        }
    }
    file.close();
    std::cout << "Data saved to file: " << filename << std::endl;
}

void Keeper::loadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for reading");
    }

    // Clear current data
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
    size = 0;

    int fileSize;
    file >> fileSize;
    file.ignore();

    for (int i = 0; i < fileSize; i++) {
        std::string type;
        std::getline(file, type);

        if (type == "Student") {
            std::string name, group, specialty;
            int course;
            double avg;

            std::getline(file, name);
            std::getline(file, group);
            std::getline(file, specialty);
            file >> course;
            file >> avg;
            file.ignore();

            add(new Student(name.c_str(), group.c_str(), specialty.c_str(), course, avg));
        }
        else if (type == "Staff") {
            std::string name, position, phone, responsibility;

            std::getline(file, name);
            std::getline(file, position);
            std::getline(file, phone);
            std::getline(file, responsibility);

            add(new Staff(name.c_str(), position.c_str(), phone.c_str(), responsibility.c_str()));
        }
        // Teacher loading would be more complex due to dynamic arrays
    }
    file.close();
    std::cout << "Data loaded from file: " << filename << std::endl;
}

int Keeper::getSize() const {
    return size;
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        for (int i = 0; i < size; i++) {
            delete data[i];
        }
        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new Base * [capacity];

        for (int i = 0; i < size; i++) {
            data[i] = other.data[i]->clone();
        }
    }
    return *this;
}

Base* Keeper::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Invalid index");
    }
    return data[index];
}