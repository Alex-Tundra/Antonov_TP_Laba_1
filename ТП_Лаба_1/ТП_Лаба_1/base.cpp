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
    std::wcout << L"������� ����������� �� ��������� ������" << std::endl;
}

Base::Base(const wchar_t* name) : fullName(nullptr) {
    copyString(fullName, name);
    std::wcout << L"������� ����������������� ����������� ������ ���: " << (name ? name : L"����������") << std::endl;
}

Base::Base(const Base& other) : fullName(nullptr) {
    copyString(fullName, other.fullName);
    std::wcout << L"������� ����������� ����������� ������ ���: " << (other.fullName ? other.fullName : L"����������") << std::endl;
}

Base::~Base() {
    std::wcout << L"������� ���������� ������ ���: " << (fullName ? fullName : L"����������") << std::endl;
    delete[] fullName;
}

const wchar_t* Base::getFullName() const {
    return fullName ? fullName : L"����������";
}

void Base::setFullName(const wchar_t* name) {
    if (!name || wcslen(name) == 0) {
        throw std::invalid_argument("��� �� ����� ���� ������");
    }
    copyString(fullName, name);
}

Base& Base::operator=(const Base& other) {
    if (this != &other) {
        copyString(fullName, other.fullName);
    }
    return *this;
}