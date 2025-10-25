#ifndef STUDENT_H
#define STUDENT_H

#include "base.h"

class Student : public Base {
private:
    char* group;
    char* specialty;
    int course;
    double averageGrade;

public:
    Student();
    Student(const char* name, const char* grp, const char* spec, int crs, double avg);
    Student(const Student& other);
    ~Student();

    void display() const override;
    void edit() override;
    Base* clone() const override;

    const char* getGroup() const;
    const char* getSpecialty() const;
    int getCourse() const;
    double getAverageGrade() const;

    void setGroup(const char* grp);
    void setSpecialty(const char* spec);
    void setCourse(int crs);
    void setAverageGrade(double avg);

    Student& operator=(const Student& other);
};

#endif