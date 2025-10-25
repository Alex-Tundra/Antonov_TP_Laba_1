#include <iostream>
#include <limits>
#include "keeper.h"
#include "student.h"
#include "teacher.h"
#include "staff.h"

void displayMenu() {
    std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ ВУЗОМ ===" << std::endl;
    std::cout << "1. Добавить студента" << std::endl;
    std::cout << "2. Добавить преподавателя" << std::endl;
    std::cout << "3. Добавить персонал" << std::endl;
    std::cout << "4. Показать все" << std::endl;
    std::cout << "5. Редактировать объект" << std::endl;
    std::cout << "6. Удалить объект" << std::endl;
    std::cout << "7. Сохранить в файл" << std::endl;
    std::cout << "8. Загрузить из файла" << std::endl;
    std::cout << "0. Выход" << std::endl;
    std::cout << "Выбор: ";
}

Base* createStudent() {
    char name[100], group[100], specialty[100];
    int course;
    double avg;

    std::cout << "Введите ФИО студента: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    std::cout << "Введите группу: ";
    std::cin.getline(group, 100);

    std::cout << "Введите специальность: ";
    std::cin.getline(specialty, 100);

    std::cout << "Введите курс: ";
    std::cin >> course;

    std::cout << "Введите средний балл: ";
    std::cin >> avg;

    return new Student(name, group, specialty, course, avg);
}

Base* createTeacher() {
    char name[100];

    std::cout << "Введите ФИО преподавателя: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    Teacher* teacher = new Teacher();
    teacher->setFullName(name);

    int choice;
    do {
        std::cout << "\nМеню создания преподавателя:" << std::endl;
        std::cout << "1. Добавить группу" << std::endl;
        std::cout << "2. Добавить предмет" << std::endl;
        std::cout << "0. Завершить создание" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: teacher->addNewGroup(); break;
        case 2: teacher->addNewSubject(); break;
        case 0: break;
        default: std::cout << "Неверный выбор!" << std::endl;
        }
    } while (choice != 0);

    return teacher;
}

Base* createStaff() {
    char name[100], position[100], phone[100], responsibility[100];

    std::cout << "Введите ФИО сотрудника: ";
    std::cin.ignore();
    std::cin.getline(name, 100);

    std::cout << "Введите должность: ";
    std::cin.getline(position, 100);

    std::cout << "Введите телефон: ";
    std::cin.getline(phone, 100);

    std::cout << "Введите область ответственности: ";
    std::cin.getline(responsibility, 100);

    return new Staff(name, position, phone, responsibility);
}

int main() {
    Keeper keeper;
    int choice;

    std::cout << "Система управления ВУЗом запущена" << std::endl;

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
                    std::cout << "Хранитель пуст!" << std::endl;
                    break;
                }
                keeper.displayAll();
                int index;
                std::cout << "Введите номер объекта для редактирования (1-" << keeper.getSize() << "): ";
                std::cin >> index;
                keeper.edit(index - 1);
                break;
            }
            case 6: {
                if (keeper.getSize() == 0) {
                    std::cout << "Хранитель пуст!" << std::endl;
                    break;
                }
                keeper.displayAll();
                int index;
                std::cout << "Введите номер объекта для удаления (1-" << keeper.getSize() << "): ";
                std::cin >> index;
                keeper.remove(index - 1);
                break;
            }
            case 7: {
                char filename[100];
                std::cout << "Введите имя файла для сохранения: ";
                std::cin.ignore();
                std::cin.getline(filename, 100);
                keeper.saveToFile(filename);
                break;
            }
            case 8: {
                char filename[100];
                std::cout << "Введите имя файла для загрузки: ";
                std::cin.ignore();
                std::cin.getline(filename, 100);
                keeper.loadFromFile(filename);
                break;
            }
            case 0: {
                std::cout << "Завершение программы..." << std::endl;
                break;
            }
            default: {
                std::cout << "Неверный выбор! Пожалуйста, попробуйте снова." << std::endl;
                break;
            }
            }
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice != 0);

    return 0;
}