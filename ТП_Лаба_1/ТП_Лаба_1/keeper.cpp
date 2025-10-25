#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

#include "keeper.h"
#include "student.h"
#include "teacher.h"
#include "staff.h"
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <string>
#include <cwchar>

// Простая функция для замены std::max
int myMax(int a, int b) {
    return (a > b) ? a : b;
}

Keeper::Keeper() : size(0), capacity(10) {
    data = new Base * [capacity];
    std::wcout << L"Конструктор хранителя по умолчанию вызван" << std::endl;
}

Keeper::Keeper(int cap) : size(0), capacity((cap > 0) ? cap : 10) {
    data = new Base * [capacity];
    std::wcout << L"Параметризованный конструктор хранителя вызван с вместимостью: " << capacity << std::endl;
}

Keeper::Keeper(const Keeper& other) : size(other.size), capacity(other.capacity) {
    data = new Base * [capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i]->clone();
    }
    std::wcout << L"Конструктор копирования хранителя вызван" << std::endl;
}

Keeper::~Keeper() {
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
    delete[] data;
    std::wcout << L"Деструктор хранителя вызван" << std::endl;
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
    if (size < capacity) {
        data[size] = item;
        size++;
        std::wcout << L"Объект добавлен в хранитель успешно!" << std::endl;
    }
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Неверный индекс для удаления");
    }

    delete data[index];
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    std::wcout << L"Объект удален успешно!" << std::endl;
}

void Keeper::displayAll() const {
    if (size == 0) {
        std::wcout << L"Хранитель пуст!" << std::endl;
        return;
    }

    std::wcout << L"\n=== ВСЕ ОБЪЕКТЫ В ХРАНИТЕЛЕ ===" << std::endl;
    for (int i = 0; i < size; i++) {
        std::wcout << L"Объект " << (i + 1) << L":" << std::endl;
        data[i]->display();
        std::wcout << std::endl;
    }
}

void Keeper::edit(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Неверный индекс для редактирования");
    }
    data[index]->edit();
}

void Keeper::saveToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи");
    }

    file << size << std::endl;
    for (int i = 0; i < size; i++) {
        if (dynamic_cast<Student*>(data[i])) {
            file << "Student" << std::endl;
            Student* s = dynamic_cast<Student*>(data[i]);

            const wchar_t* wname = s->getFullName();
            const wchar_t* wgroup = s->getGroup();
            const wchar_t* wspecialty = s->getSpecialty();

            char buffer[100];
            wcstombs(buffer, wname, 100);
            file << buffer << std::endl;

            wcstombs(buffer, wgroup, 100);
            file << buffer << std::endl;

            wcstombs(buffer, wspecialty, 100);
            file << buffer << std::endl;

            file << s->getCourse() << std::endl;
            file << s->getAverageGrade() << std::endl;
        }
        else if (dynamic_cast<Staff*>(data[i])) {
            file << "Staff" << std::endl;
            Staff* st = dynamic_cast<Staff*>(data[i]);

            const wchar_t* wname = st->getFullName();
            const wchar_t* wposition = st->getPosition();
            const wchar_t* wphone = st->getPhone();
            const wchar_t* wresponsibility = st->getResponsibility();

            char buffer[100];
            wcstombs(buffer, wname, 100);
            file << buffer << std::endl;

            wcstombs(buffer, wposition, 100);
            file << buffer << std::endl;

            wcstombs(buffer, wphone, 100);
            file << buffer << std::endl;

            wcstombs(buffer, wresponsibility, 100);
            file << buffer << std::endl;
        }
    }
    file.close();
    std::wcout << L"Данные сохранены в файл" << std::endl;
}

void Keeper::loadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения");
    }

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

            wchar_t wname[100], wgroup[100], wspecialty[100];
            mbstowcs(wname, name.c_str(), 100);
            mbstowcs(wgroup, group.c_str(), 100);
            mbstowcs(wspecialty, specialty.c_str(), 100);

            add(new Student(wname, wgroup, wspecialty, course, avg));
        }
        else if (type == "Staff") {
            std::string name, position, phone, responsibility;

            std::getline(file, name);
            std::getline(file, position);
            std::getline(file, phone);
            std::getline(file, responsibility);

            wchar_t wname[100], wposition[100], wphone[100], wresponsibility[100];
            mbstowcs(wname, name.c_str(), 100);
            mbstowcs(wposition, position.c_str(), 100);
            mbstowcs(wphone, phone.c_str(), 100);
            mbstowcs(wresponsibility, responsibility.c_str(), 100);

            add(new Staff(wname, wposition, wphone, wresponsibility));
        }
    }
    file.close();
    std::wcout << L"Данные загружены из файла" << std::endl;
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

        for (int i = 0; i < size && i < capacity; i++) {
            data[i] = other.data[i]->clone();
        }
    }
    return *this;
}

Base* Keeper::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Неверный индекс");
    }
    return data[index];
}