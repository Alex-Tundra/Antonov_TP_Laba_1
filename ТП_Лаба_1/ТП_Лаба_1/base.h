#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <cstring>
#include <locale>
#include <clocale>

class Base {
protected:
    wchar_t* fullName;

    void copyString(wchar_t*& dest, const wchar_t* src);

public:
    Base();
    Base(const wchar_t* name);
    Base(const Base& other);
    virtual ~Base();

    virtual void display() const = 0;
    virtual void edit() = 0;
    virtual Base* clone() const = 0;
    virtual void saveToStream(std::ostream& os) const = 0;
    virtual void loadFromStream(std::istream& is) = 0;

    const wchar_t* getFullName() const;
    void setFullName(const wchar_t* name);

    Base& operator=(const Base& other);
};

#endif