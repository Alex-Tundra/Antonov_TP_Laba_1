#ifndef STAFF_H
#define STAFF_H

#include "base.h"

class Staff : public Base {
private:
    char* position;
    char* phone;
    char* responsibility;

public:
    Staff();
    Staff(const char* name, const char* pos, const char* ph, const char* resp);
    Staff(const Staff& other);
    ~Staff();

    void display() const override;
    void edit() override;
    Base* clone() const override;

    const char* getPosition() const;
    const char* getPhone() const;
    const char* getResponsibility() const;

    void setPosition(const char* pos);
    void setPhone(const char* ph);
    void setResponsibility(const char* resp);

    Staff& operator=(const Staff& other);
};

#endif