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

// ���������� ������� ��� ����� �����
namespace {
    int myMax(int a, int b) {
        return (a > b) ? a : b;
    }
}

Keeper::Keeper() : size(0), capacity(10) {
    data = new Base * [capacity];
    std::wcout << L"����������� ��������� �� ��������� ������" << std::endl;
}

Keeper::Keeper(int cap) : size(0), capacity((cap > 0) ? cap : 10) {
    data = new Base * [capacity];
    std::wcout << L"����������������� ����������� ��������� ������ � ������������: " << capacity << std::endl;
}

Keeper::Keeper(const Keeper& other) : size(other.size), capacity(other.capacity) {
    data = new Base * [capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i]->clone();
    }
    std::wcout << L"����������� ����������� ��������� ������" << std::endl;
}

Keeper::~Keeper() {
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
    delete[] data;
    std::wcout << L"���������� ��������� ������" << std::endl;
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
        std::wcout << L"������ �������� � ��������� �������!" << std::endl;
    }
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("�������� ������ ��� ��������");
    }

    delete data[index];
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    std::wcout << L"������ ������ �������!" << std::endl;
}

void Keeper::displayAll() const {
    if (size == 0) {
        std::wcout << L"��������� ����!" << std::endl;
        return;
    }

    std::wcout << L"\n=== ��� ������� � ��������� ===" << std::endl;
    for (int i = 0; i < size; i++) {
        std::wcout << L"������ " << (i + 1) << L":" << std::endl;
        data[i]->display();
        std::wcout << std::endl;
    }
}

void Keeper::edit(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("�������� ������ ��� ��������������");
    }
    data[index]->edit();
}

void Keeper::saveToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� ��� ������");
    }

    // ��������� ���������� ��������
    file << size << std::endl;

    // ��������� ������ ������
    for (int i = 0; i < size; i++) {
        data[i]->saveToStream(file);
    }

    file.close();
    std::wcout << L"������ ������� ��������� � ����: " << filename << std::endl;
}

void Keeper::loadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� ��� ������");
    }

    // ������� ������� ������
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
    size = 0;

    // ������ ���������� ��������
    int fileSize;
    file >> fileSize;
    file.ignore(); // ���������� ������ ����� ������

    // ������ ������ ������
    for (int i = 0; i < fileSize; i++) {
        std::string type;
        std::getline(file, type);

        Base* obj = nullptr;

        if (type == "Student") {
            obj = new Student();
            obj->loadFromStream(file);
        }
        else if (type == "Teacher") {
            obj = new Teacher();
            obj->loadFromStream(file);
        }
        else if (type == "Staff") {
            obj = new Staff();
            obj->loadFromStream(file);
        }

        if (obj) {
            add(obj);
        }
    }

    file.close();
    std::wcout << L"������ ������� ��������� �� �����: " << filename << std::endl;
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
        throw std::out_of_range("�������� ������");
    }
    return data[index];
}