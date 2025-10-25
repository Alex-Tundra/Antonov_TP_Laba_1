#ifndef STAFF_H
#define STAFF_H

#include "base.h"

class Staff : public Base {
private:
    wchar_t* position;
    wchar_t* phone;
    wchar_t* responsibility;

public:
    Staff();
    Staff(const wchar_t* name, const wchar_t* pos, const wchar_t* ph, const wchar_t* resp);
    Staff(const Staff& other);
    ~Staff();

    void display() const override;
    void edit() override;
    Base* clone() const override;

    const wchar_t* getPosition() const;
    const wchar_t* getPhone() const;
    const wchar_t* getResponsibility() const;

    void setPosition(const wchar_t* pos);
    void setPhone(const wchar_t* ph);
    void setResponsibility(const wchar_t* resp);

    Staff& operator=(const Staff& other);
};

#endif