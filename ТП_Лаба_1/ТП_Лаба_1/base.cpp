#include "base.h"

void Base::copyString(char*& dest, const char* src) {
    if (dest) delete[] dest;
    if (src) {
        dest = new char[strlen(src) + 1];
        strcpy(dest, src);
    }
    else {
        dest = nullptr;
    }
}

Base::Base() : fullName(nullptr) {
    std::cout << "Base default constructor called" << std::endl;
}

Base::Base(const char* name) : fullName(nullptr) {
    copyString(fullName, name);
    std::cout << "Base parameterized constructor called for: " << (name ? name : "Unknown") << std::endl;
}

Base::Base(const Base& other) : fullName(nullptr) {
    copyString(fullName, other.fullName);
    std::cout << "Base copy constructor called for: " << (other.fullName ? other.fullName : "Unknown") << std::endl;
}

Base::~Base() {
    std::cout << "Base destructor called for: " << (fullName ? fullName : "Unknown") << std::endl;
    delete[] fullName;
}

const char* Base::getFullName() const {
    return fullName ? fullName : "Unknown";
}

void Base::setFullName(const char* name) {
    if (!name || strlen(name) == 0) {
        throw std::invalid_argument("Full name cannot be empty");
    }
    copyString(fullName, name);
}

Base& Base::operator=(const Base& other) {
    if (this != &other) {
        copyString(fullName, other.fullName);
    }
    return *this;
}