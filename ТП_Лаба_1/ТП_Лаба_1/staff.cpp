#define _CRT_SECURE_NO_WARNINGS
#include "staff.h"
#include <iostream>
#include <cwchar>

Staff::Staff() : Base(), position(nullptr), phone(nullptr), responsibility(nullptr) {
    std::wcout << L"Конструктор персонала по умолчанию вызван" << std::endl;
}

Staff::Staff(const wchar_t* name, const wchar_t* pos, const wchar_t* ph, const wchar_t* resp)
    : Base(name), position(nullptr), phone(nullptr), responsibility(nullptr) {
    copyString(position, pos);
    copyString(phone, ph);
    copyString(responsibility, resp);
    std::wcout << L"Параметризованный конструктор персонала вызван для: " << (name ? name : L"Неизвестно") << std::endl;
}

Staff::Staff(const Staff& other) : Base(other), position(nullptr), phone(nullptr), responsibility(nullptr) {
    copyString(position, other.position);
    copyString(phone, other.phone);
    copyString(responsibility, other.responsibility);
    std::wcout << L"Конструктор копирования персонала вызван для: " << other.getFullName() << std::endl;
}

Staff::~Staff() {
    std::wcout << L"Деструктор персонала вызван для: " << getFullName() << std::endl;
    delete[] position;
    delete[] phone;
    delete[] responsibility;
}

void Staff::display() const {
    std::wcout << L"АДМИНИСТРАТИВНЫЙ ПЕРСОНАЛ: " << getFullName() << std::endl;
    std::wcout << L"  Должность: " << (position ? position : L"Не указана") << std::endl;
    std::wcout << L"  Телефон: " << (phone ? phone : L"Не указан") << std::endl;
    std::wcout << L"  Область ответственности: " << (responsibility ? responsibility : L"Не указана") << std::endl;
}

void Staff::edit() {
    std::wcout << L"Редактирование персонала: " << getFullName() << std::endl;

    wchar_t buffer[100];

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::wcout << L"Введите новое ФИО: ";
    std::wcin.getline(buffer, 100);
    setFullName(buffer);

    std::wcout << L"Введите должность: ";
    std::wcin.getline(buffer, 100);
    setPosition(buffer);

    std::wcout << L"Введите телефон: ";
    std::wcin.getline(buffer, 100);
    setPhone(buffer);

    std::wcout << L"Введите область ответственности: ";
    std::wcin.getline(buffer, 100);
    setResponsibility(buffer);

    std::wcout << L"Данные персонала обновлены успешно!" << std::endl;
}

Base* Staff::clone() const {
    return new Staff(*this);
}

const wchar_t* Staff::getPosition() const { return position ? position : L"Не указана"; }
const wchar_t* Staff::getPhone() const { return phone ? phone : L"Не указан"; }
const wchar_t* Staff::getResponsibility() const { return responsibility ? responsibility : L"Не указана"; }

void Staff::setPosition(const wchar_t* pos) {
    if (!pos || wcslen(pos) == 0) {
        throw std::invalid_argument("Должность не может быть пустой");
    }
    copyString(position, pos);
}

void Staff::setPhone(const wchar_t* ph) {
    if (!ph || wcslen(ph) == 0) {
        throw std::invalid_argument("Телефон не может быть пустым");
    }
    copyString(phone, ph);
}

void Staff::setResponsibility(const wchar_t* resp) {
    if (!resp || wcslen(resp) == 0) {
        throw std::invalid_argument("Область ответственности не может быть пустой");
    }
    copyString(responsibility, resp);
}

Staff& Staff::operator=(const Staff& other) {
    if (this != &other) {
        Base::operator=(other);
        copyString(position, other.position);
        copyString(phone, other.phone);
        copyString(responsibility, other.responsibility);
    }
    return *this;
}