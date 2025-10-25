#ifndef STUDENT_H
#define STUDENT_H

#include "base.h"

class Student : public Base {
private:
    wchar_t* group;
    wchar_t* specialty;
    int course;
    double averageGrade;

public:
    Student();
    Student(const wchar_t* name, const wchar_t* grp, const wchar_t* spec, int crs, double avg);
    Student(const Student& other);
    ~Student();

    void display() const override;
    void edit() override;
    Base* clone() const override;

    const wchar_t* getGroup() const;
    const wchar_t* getSpecialty() const;
    int getCourse() const;
    double getAverageGrade() const;

    void setGroup(const wchar_t* grp);
    void setSpecialty(const wchar_t* spec);
    void setCourse(int crs);
    void setAverageGrade(double avg);

    Student& operator=(const Student& other);
};

#endif