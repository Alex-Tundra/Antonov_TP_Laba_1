#ifndef TEACHER_H
#define TEACHER_H

#include "base.h"

class Teacher : public Base {
private:
    wchar_t** groups;
    wchar_t** subjects;
    int groupsCount;
    int subjectsCount;
    int groupsCapacity;
    int subjectsCapacity;

    void addGroup(const wchar_t* group);
    void addSubject(const wchar_t* subject);
    void resizeGroups();
    void resizeSubjects();
    void clearGroups();
    void clearSubjects();

public:
    Teacher();
    Teacher(const wchar_t* name, const wchar_t** grps, int grpCount, const wchar_t** subj, int subjCount);
    Teacher(const Teacher& other);
    ~Teacher();

    void display() const override;
    void edit() override;
    Base* clone() const override;
    void saveToStream(std::ostream& os) const override;
    void loadFromStream(std::istream& is) override;

    void addNewGroup();
    void addNewSubject();
    void removeGroup();
    void removeSubject();
    void displayGroups() const;
    void displaySubjects() const;

    Teacher& operator=(const Teacher& other);
};

#endif