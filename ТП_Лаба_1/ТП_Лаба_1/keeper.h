#ifndef KEEPER_H
#define KEEPER_H

#include "base.h"

class Keeper {
private:
    Base** data;
    int size;
    int capacity;

    void resize();

public:
    Keeper();
    Keeper(int cap);
    Keeper(const Keeper& other);
    ~Keeper();

    void add(Base* item);
    void remove(int index);
    void displayAll() const;
    void edit(int index);
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);

    int getSize() const;

    Keeper& operator=(const Keeper& other);
    Base* operator[](int index);
};

#endif