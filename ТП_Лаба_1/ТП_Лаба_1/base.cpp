#define _CRT_SECURE_NO_WARNINGS
#include "base.h"

void Base::copyString(wchar_t*& dest, const wchar_t* src) {
    if (dest) delete[] dest;
    if (src) {
        dest = new wchar_t[wcslen(src) + 1];
        wcscpy(dest, src);
    }
    else {
        dest = nullptr;
    }
}

Base::Base() : fullName(nullptr) {
    std::wcout << L"Базовый конструктор по умолчанию вызван" << std::endl;
}

Base::Base(const wchar_t* name) : fullName(nullptr) {
    copyString(fullName, name);
    std::wcout << L"Базовый параметризованный конструктор вызван для: " << (name ? name : L"Неизвестно") << std::endl;
}

Base::Base(const Base& other) : fullName(nullptr) {
    copyString(fullName, other.fullName);
    std::wcout << L"Базовый конструктор копирования вызван для: " << (other.fullName ? other.fullName : L"Неизвестно") << std::endl;
}

Base::~Base() {
    std::wcout << L"Базовый деструктор вызван для: " << (fullName ? fullName : L"Неизвестно") << std::endl;
    delete[] fullName;
}

const wchar_t* Base::getFullName() const {
    return fullName ? fullName : L"Неизвестно";
}

void Base::setFullName(const wchar_t* name) {
    if (!name || wcslen(name) == 0) {
        throw std::invalid_argument("ФИО не может быть пустым");
    }
    copyString(fullName, name);
}

Base& Base::operator=(const Base& other) {
    if (this != &other) {
        copyString(fullName, other.fullName);
    }
    return *this;
}