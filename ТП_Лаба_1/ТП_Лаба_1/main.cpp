#include <iostream>
#include <limits>
#include "keeper.h"
#include "student.h"
#include "teacher.h"
#include "staff.h"

void displayMenu() {
    std::cout << "\n=== ������� ���������� ����� ===" << std::endl;
    std::cout << "1. �������� ��������" << std::endl;
    std::cout << "2. �������� �������������" << std::endl;
    std::cout << "3. �������� ��������" << std::endl;
    std::cout << "4. �������� ���" << std::endl;
    std::cout << "5. ������������� ������" << std::endl;
    std::cout << "6. ������� ������" << std::endl;
    std::cout << "7. ��������� � ����" << std::endl;
    std::cout << "8. ��������� �� �����" << std::endl;
    std::cout << "0. �����" << std::endl;
    std::cout << "�����: ";
}

Base* createStudent() {
    char name[100], group[100], specialty[100];
    int course;
    double avg;

    std::cout << "������� ��� ��������: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    std::cout << "������� ������: ";
    std::cin.getline(group, 100);

    std::cout << "������� �������������: ";
    std::cin.getline(specialty, 100);

    std::cout << "������� ����: ";
    std::cin >> course;

    std::cout << "������� ������� ����: ";
    std::cin >> avg;

    return new Student(name, group, specialty, course, avg);
}

Base* createTeacher() {
    char name[100];

    std::cout << "������� ��� �������������: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    Teacher* teacher = new Teacher();
    teacher->setFullName(name);

    int choice;
    do {
        std::cout << "\n���� �������� �������������:" << std::endl;
        std::cout << "1. �������� ������" << std::endl;
        std::cout << "2. �������� �������" << std::endl;
        std::cout << "0. ��������� ��������" << std::endl;
        std::cout << "�����: ";
        std::cin >> choice;

        switch (choice) {
        case 1: teacher->addNewGroup(); break;
        case 2: teacher->addNewSubject(); break;
        case 0: break;
        default: std::cout << "�������� �����!" << std::endl;
        }
    } while (choice != 0);

    return teacher;
}

Base* createStaff() {
    char name[100], position[100], phone[100], responsibility[100];

    std::cout << "������� ��� ����������: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    std::cout << "������� ���������: ";
    std::cin.getline(position, 100);

    std::cout << "������� �������: ";
    std::cin.getline(phone, 100);

    std::cout << "������� ������� ���������������: ";
    std::cin.getline(responsibility, 100);

    return new Staff(name, position, phone, responsibility);
}

int main() {
    Keeper keeper;
    int choice;

    std::cout << "������� ���������� ����� ��������" << std::endl;

    do {
        try {
            displayMenu();
            std::cin >> choice;

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
                    std::cout << "��������� ����!" << std::endl;
                    break;
                }
                keeper.displayAll();
                int index;
                std::cout << "������� ����� ������� ��� �������������� (1-" << keeper.getSize() << "): ";
                std::cin >> index;
                keeper.edit(index - 1);
                break;
            }
            case 6: {
                if (keeper.getSize() == 0) {
                    std::cout << "��������� ����!" << std::endl;
                    break;
                }
                keeper.displayAll();
                int index;
                std::cout << "������� ����� ������� ��� �������� (1-" << keeper.getSize() << "): ";
                std::cin >> index;
                keeper.remove(index - 1);
                break;
            }
            case 7: {
                char filename[100];
                std::cout << "������� ��� ����� ��� ����������: ";
                std::cin.ignore();
                std::cin.getline(filename, 100);
                keeper.saveToFile(filename);
                break;
            }
            case 8: {
                char filename[100];
                std::cout << "������� ��� ����� ��� ��������: ";
                std::cin.ignore();
                std::cin.getline(filename, 100);
                keeper.loadFromFile(filename);
                break;
            }
            case 0: {
                std::cout << "���������� ���������..." << std::endl;
                break;
            }
            default: {
                std::cout << "�������� �����! ����������, ���������� �����." << std::endl;
                break;
            }
            }
        }
        catch (const std::exception& e) {
            std::cout << "������: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);

    return 0;
}