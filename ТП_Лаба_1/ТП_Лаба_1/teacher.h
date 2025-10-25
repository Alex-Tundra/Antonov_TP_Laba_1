#ifndef TEACHER_H
#define TEACHER_H

#include "base.h"

class Teacher : public Base {
private:
    char** groups;
    char** subjects;
    int groupsCount;
    int subjectsCount;
    int groupsCapacity;
    int subjectsCapacity;

    void addGroup(const char* group);
    void addSubject(const char* subject);
    void resizeGroups();
    void resizeSubjects();

public:
    Teacher();
    Teacher(const char* name, const char** grps, int grpCount, const char** subj, int subjCount);
    Teacher(const Teacher& other);
    ~Teacher();

    void display() const override;
    void edit() override;
    Base* clone() const override;

    void addNewGroup();
    void addNewSubject();
    void removeGroup();
    void removeSubject();
    void displayGroups() const;
    void displaySubjects() const;

    Teacher& operator=(const Teacher& other);
};

#endif