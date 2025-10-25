#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <cstring>

class Base {
protected:
    char* fullName;

    void copyString(char*& dest, const char* src);

public:
    Base();
    Base(const char* name);
    Base(const Base& other);
    virtual ~Base();

    virtual void display() const = 0;
    virtual void edit() = 0;
    virtual Base* clone() const = 0;

    const char* getFullName() const;
    void setFullName(const char* name);

    Base& operator=(const Base& other);
};

#endif