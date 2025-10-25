#define _CRT_SECURE_NO_WARNINGS
#include "staff.h"
#include <iostream>
#include <cwchar>

Staff::Staff() : Base(), position(nullptr), phone(nullptr), responsibility(nullptr) {
    std::wcout << L"����������� ��������� �� ��������� ������" << std::endl;
}

Staff::Staff(const wchar_t* name, const wchar_t* pos, const wchar_t* ph, const wchar_t* resp)
    : Base(name), position(nullptr), phone(nullptr), responsibility(nullptr) {
    copyString(position, pos);
    copyString(phone, ph);
    copyString(responsibility, resp);
    std::wcout << L"����������������� ����������� ��������� ������ ���: " << (name ? name : L"����������") << std::endl;
}

Staff::Staff(const Staff& other) : Base(other), position(nullptr), phone(nullptr), responsibility(nullptr) {
    copyString(position, other.position);
    copyString(phone, other.phone);
    copyString(responsibility, other.responsibility);
    std::wcout << L"����������� ����������� ��������� ������ ���: " << other.getFullName() << std::endl;
}

Staff::~Staff() {
    std::wcout << L"���������� ��������� ������ ���: " << getFullName() << std::endl;
    delete[] position;
    delete[] phone;
    delete[] responsibility;
}

void Staff::display() const {
    std::wcout << L"���������������� ��������: " << getFullName() << std::endl;
    std::wcout << L"  ���������: " << (position ? position : L"�� �������") << std::endl;
    std::wcout << L"  �������: " << (phone ? phone : L"�� ������") << std::endl;
    std::wcout << L"  ������� ���������������: " << (responsibility ? responsibility : L"�� �������") << std::endl;
}

void Staff::edit() {
    std::wcout << L"�������������� ���������: " << getFullName() << std::endl;

    wchar_t buffer[100];

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::wcout << L"������� ����� ���: ";
    std::wcin.getline(buffer, 100);
    setFullName(buffer);

    std::wcout << L"������� ���������: ";
    std::wcin.getline(buffer, 100);
    setPosition(buffer);

    std::wcout << L"������� �������: ";
    std::wcin.getline(buffer, 100);
    setPhone(buffer);

    std::wcout << L"������� ������� ���������������: ";
    std::wcin.getline(buffer, 100);
    setResponsibility(buffer);

    std::wcout << L"������ ��������� ��������� �������!" << std::endl;
}

Base* Staff::clone() const {
    return new Staff(*this);
}

const wchar_t* Staff::getPosition() const { return position ? position : L"�� �������"; }
const wchar_t* Staff::getPhone() const { return phone ? phone : L"�� ������"; }
const wchar_t* Staff::getResponsibility() const { return responsibility ? responsibility : L"�� �������"; }

void Staff::setPosition(const wchar_t* pos) {
    if (!pos || wcslen(pos) == 0) {
        throw std::invalid_argument("��������� �� ����� ���� ������");
    }
    copyString(position, pos);
}

void Staff::setPhone(const wchar_t* ph) {
    if (!ph || wcslen(ph) == 0) {
        throw std::invalid_argument("������� �� ����� ���� ������");
    }
    copyString(phone, ph);
}

void Staff::setResponsibility(const wchar_t* resp) {
    if (!resp || wcslen(resp) == 0) {
        throw std::invalid_argument("������� ��������������� �� ����� ���� ������");
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