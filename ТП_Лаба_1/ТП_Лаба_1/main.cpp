#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

#include <iostream>
#include <limits>
#include <windows.h>
#include <locale>
#include <clocale>
#include "keeper.h"
#include "student.h"
#include "teacher.h"
#include "staff.h"

// ������� ��� ����������� ����� ����� � ���������
int safeInputInt() {
    int value;
    while (!(std::wcin >> value)) {
        std::wcout << L"������ �����! ������� ����� �����: ";
        std::wcin.clear();
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// ������� ��� ����������� ����� ����� � ��������� ������
double safeInputDouble() {
    double value;
    while (!(std::wcin >> value)) {
        std::wcout << L"������ �����! ������� �����: ";
        std::wcin.clear();
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// ������� ��� ����������� ����� ������
void safeInputString(wchar_t* buffer, int size, const wchar_t* prompt) {
    std::wcout << prompt;
    std::wcin.getline(buffer, size);
    // ���� ����� ��� ������ (������������ ������ ����� Enter)
    if (wcslen(buffer) == 0) {
        std::wcout << L"���� �� ����� ���� ������! ";
        safeInputString(buffer, size, prompt);
    }
}

void displayMenu() {
    std::wcout << L"\n=== ������� ���������� ����� ===" << std::endl;
    std::wcout << L"1. �������� ��������" << std::endl;
    std::wcout << L"2. �������� �������������" << std::endl;
    std::wcout << L"3. �������� ��������" << std::endl;
    std::wcout << L"4. �������� ���" << std::endl;
    std::wcout << L"5. ������������� ������" << std::endl;
    std::wcout << L"6. ������� ������" << std::endl;
    std::wcout << L"7. ��������� � ����" << std::endl;
    std::wcout << L"8. ��������� �� �����" << std::endl;
    std::wcout << L"0. �����" << std::endl;
    std::wcout << L"�����: ";
}

Base* createStudent() {
    wchar_t name[100], group[100], specialty[100];
    int course;
    double avg;

    // ������� ����� ����� ������� �����
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    safeInputString(name, 100, L"������� ��� ��������: ");
    safeInputString(group, 100, L"������� ������: ");
    safeInputString(specialty, 100, L"������� �������������: ");

    std::wcout << L"������� ����: ";
    course = safeInputInt();

    std::wcout << L"������� ������� ����: ";
    avg = safeInputDouble();

    return new Student(name, group, specialty, course, avg);
}

Base* createTeacher() {
    wchar_t name[100];

    // ������� ����� ����� ������� �����
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    safeInputString(name, 100, L"������� ��� �������������: ");

    Teacher* teacher = new Teacher();
    teacher->setFullName(name);

    int choice;
    do {
        std::wcout << L"\n���� �������� �������������:" << std::endl;
        std::wcout << L"1. �������� ������" << std::endl;
        std::wcout << L"2. �������� �������" << std::endl;
        std::wcout << L"0. ��������� ��������" << std::endl;
        std::wcout << L"�����: ";
        choice = safeInputInt();

        switch (choice) {
        case 1:
            teacher->addNewGroup();
            break;
        case 2:
            teacher->addNewSubject();
            break;
        case 0:
            break;
        default:
            std::wcout << L"�������� �����!" << std::endl;
        }
    } while (choice != 0);

    return teacher;
}

Base* createStaff() {
    wchar_t name[100], position[100], phone[100], responsibility[100];

    // ������� ����� ����� ������� �����
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    safeInputString(name, 100, L"������� ��� ����������: ");
    safeInputString(position, 100, L"������� ���������: ");
    safeInputString(phone, 100, L"������� �������: ");
    safeInputString(responsibility, 100, L"������� ������� ���������������: ");

    return new Staff(name, position, phone, responsibility);
}

int main() {
    // ��������� ������� ������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::setlocale(LC_ALL, "Russian");

    Keeper keeper;
    int choice;

    std::wcout << L"������� ���������� ����� ��������" << std::endl;

    do {
        try {
            displayMenu();
            choice = safeInputInt();

            switch (choice) {
            case 1: {
                Base* student = createStudent();
                keeper.add(student);
                break;
            }
            case 2: {
                Base* teacher = createTeacher();
                keeper.add(teacher);
                break;
            }
            case 3: {
                Base* staff = createStaff();
                keeper.add(staff);
                break;
            }
            case 4: {
                keeper.displayAll();
                break;
            }
            case 5: {
                if (keeper.getSize() == 0) {
                    std::wcout << L"��������� ����!" << std::endl;
                    break;
                }
                keeper.displayAll();
                int index;
                std::wcout << L"������� ����� ������� ��� �������������� (1-" << keeper.getSize() << L"): ";
                index = safeInputInt();
                if (index >= 1 && index <= keeper.getSize()) {
                    keeper.edit(index - 1);
                }
                else {
                    std::wcout << L"�������� �����!" << std::endl;
                }
                break;
            }
            case 6: {
                if (keeper.getSize() == 0) {
                    std::wcout << L"��������� ����!" << std::endl;
                    break;
                }
                keeper.displayAll();
                int index;
                std::wcout << L"������� ����� ������� ��� �������� (1-" << keeper.getSize() << L"): ";
                index = safeInputInt();
                if (index >= 1 && index <= keeper.getSize()) {
                    keeper.remove(index - 1);
                }
                else {
                    std::wcout << L"�������� �����!" << std::endl;
                }
                break;
            }
            case 7: {
                wchar_t filename[100];
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                safeInputString(filename, 100, L"������� ��� ����� ��� ����������: ");

                char narrowFilename[100];
                wcstombs(narrowFilename, filename, 100);
                keeper.saveToFile(narrowFilename);
                break;
            }
            case 8: {
                wchar_t filename[100];
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                safeInputString(filename, 100, L"������� ��� ����� ��� ��������: ");

                char narrowFilename[100];
                wcstombs(narrowFilename, filename, 100);
                keeper.loadFromFile(narrowFilename);
                break;
            }
            case 0: {
                std::wcout << L"���������� ���������..." << std::endl;
                break;
            }
            default: {
                std::wcout << L"�������� �����! ����������, ���������� �����." << std::endl;
                break;
            }
            }
        }
        catch (const std::exception& e) {
            std::wcout << L"������: " << e.what() << std::endl;
        }
    } while (choice != 0);

    return 0;
}