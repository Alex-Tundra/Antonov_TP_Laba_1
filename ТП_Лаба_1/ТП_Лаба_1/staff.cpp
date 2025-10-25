#include "staff.h"
#include <iostream>
#include <cstring>

Staff::Staff() : Base(), position(nullptr), phone(nullptr), responsibility(nullptr) {
    std::cout << "Staff default constructor called" << std::endl;
}

Staff::Staff(const char* name, const char* pos, const char* ph, const char* resp)
    : Base(name), position(nullptr), phone(nullptr), responsibility(nullptr) {
    copyString(position, pos);
    copyString(phone, ph);
    copyString(responsibility, resp);
    std::cout << "Staff parameterized constructor called for: " << (name ? name : "Unknown") << std::endl;
}

Staff::Staff(const Staff& other) : Base(other), position(nullptr), phone(nullptr), responsibility(nullptr) {
    copyString(position, other.position);
    copyString(phone, other.phone);
    copyString(responsibility, other.responsibility);
    std::cout << "Staff copy constructor called for: " << other.getFullName() << std::endl;
}

Staff::~Staff() {
    std::cout << "Staff destructor called for: " << getFullName() << std::endl;
    delete[] position;
    delete[] phone;
    delete[] responsibility;
}

void Staff::display() const {
    std::cout << "STAFF: " << getFullName() << std::endl;
    std::cout << "  Position: " << (position ? position : "N/A") << std::endl;
    std::cout << "  Phone: " << (phone ? phone : "N/A") << std::endl;
    std::cout << "  Responsibility: " << (responsibility ? responsibility : "N/A") << std::endl;
}

void Staff::edit() {
    std::cout << "Editing Staff: " << getFullName() << std::endl;

    char buffer[100];

    std::cout << "Enter new full name: ";
    std::cin.ignore();
    std::cin.getline(buffer, 100);
    setFullName(buffer);

    std::cout << "Enter position: ";
    std::cin.getline(buffer, 100);
    setPosition(buffer);

    std::cout << "Enter phone: ";
    std::cin.getline(buffer, 100);
    setPhone(buffer);

    std::cout << "Enter responsibility area: ";
    std::cin.getline(buffer, 100);
    setResponsibility(buffer);
}

Base* Staff::clone() const {
    return new Staff(*this);
}

const char* Staff::getPosition() const { return position ? position : "N/A"; }
const char* Staff::getPhone() const { return phone ? phone : "N/A"; }
const char* Staff::getResponsibility() const { return responsibility ? responsibility : "N/A"; }

void Staff::setPosition(const char* pos) {
    if (!pos || strlen(pos) == 0) {
        throw std::invalid_argument("Position cannot be empty");
    }
    copyString(position, pos);
}

void Staff::setPhone(const char* ph) {
    if (!ph || strlen(ph) == 0) {
        throw std::invalid_argument("Phone cannot be empty");
    }
    copyString(phone, ph);
}

void Staff::setResponsibility(const char* resp) {
    if (!resp || strlen(resp) == 0) {
        throw std::invalid_argument("Responsibility cannot be empty");
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