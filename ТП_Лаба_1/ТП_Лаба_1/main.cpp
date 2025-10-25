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

// Функция для безопасного ввода числа с проверкой
int safeInputInt() {
    int value;
    while (!(std::wcin >> value)) {
        std::wcout << L"Ошибка ввода! Введите целое число: ";
        std::wcin.clear();
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Функция для безопасного ввода числа с плавающей точкой
double safeInputDouble() {
    double value;
    while (!(std::wcin >> value)) {
        std::wcout << L"Ошибка ввода! Введите число: ";
        std::wcin.clear();
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Функция для безопасного ввода строки
void safeInputString(wchar_t* buffer, int size, const wchar_t* prompt) {
    std::wcout << prompt;
    std::wcin.getline(buffer, size);
    // Если буфер был пустым (пользователь просто нажал Enter)
    if (wcslen(buffer) == 0) {
        std::wcout << L"Поле не может быть пустым! ";
        safeInputString(buffer, size, prompt);
    }
}

void displayMenu() {
    std::wcout << L"\n=== СИСТЕМА УПРАВЛЕНИЯ ВУЗОМ ===" << std::endl;
    std::wcout << L"1. Добавить студента" << std::endl;
    std::wcout << L"2. Добавить преподавателя" << std::endl;
    std::wcout << L"3. Добавить персонал" << std::endl;
    std::wcout << L"4. Показать все" << std::endl;
    std::wcout << L"5. Редактировать объект" << std::endl;
    std::wcout << L"6. Удалить объект" << std::endl;
    std::wcout << L"7. Сохранить в файл" << std::endl;
    std::wcout << L"8. Загрузить из файла" << std::endl;
    std::wcout << L"0. Выход" << std::endl;
    std::wcout << L"Выбор: ";
}

Base* createStudent() {
    wchar_t name[100], group[100], specialty[100];
    int course;
    double avg;

    // Очищаем буфер перед началом ввода
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    safeInputString(name, 100, L"Введите ФИО студента: ");
    safeInputString(group, 100, L"Введите группу: ");
    safeInputString(specialty, 100, L"Введите специальность: ");

    std::wcout << L"Введите курс: ";
    course = safeInputInt();

    std::wcout << L"Введите средний балл: ";
    avg = safeInputDouble();

    return new Student(name, group, specialty, course, avg);
}

Base* createTeacher() {
    wchar_t name[100];

    // Очищаем буфер перед началом ввода
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    safeInputString(name, 100, L"Введите ФИО преподавателя: ");

    Teacher* teacher = new Teacher();
    teacher->setFullName(name);

    int choice;
    do {
        std::wcout << L"\nМеню создания преподавателя:" << std::endl;
        std::wcout << L"1. Добавить группу" << std::endl;
        std::wcout << L"2. Добавить предмет" << std::endl;
        std::wcout << L"0. Завершить создание" << std::endl;
        std::wcout << L"Выбор: ";
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
            std::wcout << L"Неверный выбор!" << std::endl;
        }
    } while (choice != 0);

    return teacher;
}

Base* createStaff() {
    wchar_t name[100], position[100], phone[100], responsibility[100];

    // Очищаем буфер перед началом ввода
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    safeInputString(name, 100, L"Введите ФИО сотрудника: ");
    safeInputString(position, 100, L"Введите должность: ");
    safeInputString(phone, 100, L"Введите телефон: ");
    safeInputString(responsibility, 100, L"Введите область ответственности: ");

    return new Staff(name, position, phone, responsibility);
}

int main() {
    // Установка русской локали
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::setlocale(LC_ALL, "Russian");

    Keeper keeper;
    int choice;

    std::wcout << L"Система управления ВУЗом запущена" << std::endl;

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
                    std::wcout << L"Хранитель пуст!" << std::endl;
                    break;
                }
                keeper.displayAll();
                int index;
                std::wcout << L"Введите номер объекта для редактирования (1-" << keeper.getSize() << L"): ";
                index = safeInputInt();
                if (index >= 1 && index <= keeper.getSize()) {
                    keeper.edit(index - 1);
                }
                else {
                    std::wcout << L"Неверный номер!" << std::endl;
                }
                break;
            }
            case 6: {
                if (keeper.getSize() == 0) {
                    std::wcout << L"Хранитель пуст!" << std::endl;
                    break;
                }
                keeper.displayAll();
                int index;
                std::wcout << L"Введите номер объекта для удаления (1-" << keeper.getSize() << L"): ";
                index = safeInputInt();
                if (index >= 1 && index <= keeper.getSize()) {
                    keeper.remove(index - 1);
                }
                else {
                    std::wcout << L"Неверный номер!" << std::endl;
                }
                break;
            }
            case 7: {
                wchar_t filename[100];
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                safeInputString(filename, 100, L"Введите имя файла для сохранения: ");

                char narrowFilename[100];
                wcstombs(narrowFilename, filename, 100);
                keeper.saveToFile(narrowFilename);
                break;
            }
            case 8: {
                wchar_t filename[100];
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                safeInputString(filename, 100, L"Введите имя файла для загрузки: ");

                char narrowFilename[100];
                wcstombs(narrowFilename, filename, 100);
                keeper.loadFromFile(narrowFilename);
                break;
            }
            case 0: {
                std::wcout << L"Завершение программы..." << std::endl;
                break;
            }
            default: {
                std::wcout << L"Неверный выбор! Пожалуйста, попробуйте снова." << std::endl;
                break;
            }
            }
        }
        catch (const std::exception& e) {
            std::wcout << L"Ошибка: " << e.what() << std::endl;
        }
    } while (choice != 0);

    return 0;
}