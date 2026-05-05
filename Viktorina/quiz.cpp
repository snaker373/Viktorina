#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <cstdlib>

using namespace std;

// Структура для хранения вопроса
struct Question {
    string text;
    vector<string> options;
    int correctAnswer; // индекс правильного ответа (0-3)
};

// Функция для установки кодировки UTF-8
void setUTF8() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Функция для очистки экрана
void clearScreen() {
    system("cls");
}

// Функция для отображения заголовка
void showHeader() {
    cout << "========================================" << endl;
    cout << "           ВИКТОРИНА 2024              " << endl;
    cout << "========================================" << endl;
    cout << endl;
}

// Функция для отображения результата
void showResult(int score, int total) {
    clearScreen();
    showHeader();

    double percentage = (double)score / total * 100;

    cout << "========================================" << endl;
    cout << "           РЕЗУЛЬТАТ                    " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Правильных ответов: " << score << " из " << total << endl;
    cout << "Процент правильных: " << percentage << "%" << endl;
    cout << endl;

    if (percentage == 100) {
        cout << "🏆 ИДЕАЛЬНО! Вы настоящий эрудит! 🏆" << endl;
    } else if (percentage >= 80) {
        cout << "🌟 Отличный результат! Так держать! 🌟" << endl;
    } else if (percentage >= 60) {
        cout << "👍 Хороший результат! Есть куда расти! 👍" << endl;
    } else if (percentage >= 40) {
        cout << "📚 Неплохо, но стоит почитать больше! 📚" << endl;
    } else {
        cout << "💪 Не сдавайтесь! Попробуйте еще раз! 💪" << endl;
    }

    cout << endl;
    cout << "========================================" << endl;
}

// Функция для ожидания нажатия клавиши
void waitForKey() {
    cout << endl << "Нажмите Enter, чтобы продолжить...";
    cin.ignore();
    cin.get();
}

int main() {
    setUTF8();

    // База вопросов
    vector<Question> questions = {
        {
            "Хто був одним із найвідоміших художників Голландії у 1600-ті роки?",
            {"Вольфганг", "Мемлинг", "Караваджо", "Рембрандт"},
            3 // Рембрандт
        },
        {
            "Що з перерахованого не психічний розлад?",
            {"Биполярное расстройство", "Депрессия", "Анемия", "Шизофрения"},
            2 // Анемия
        },
        {
            "Що містить найбільше білка на 100 грам?",
            {"Краб", "Тунец", "Яйца", "Банан"},
            0 // Краб
        },
        {
            "Найдорожча з колись проданих картин у світі?",
            {"Алжирские женщины (Пикассо)", "Спасатель мира (Леонардо да Винчи)", "Крик (Эдвард Мунк)", "Лежащая обнаженная (Модильяни)"},
            1 // Спасатель мира
        },
        {
            "Яка наука досліджує закономірності приготування, вчинення та розкриття злочину?",
            {"Уголовное право", "Криминалистика", "Криминология", "Прокурорский надзор"},
            1 // Криминалистика
        },
        {
            "Для визначення чого використовують шкалу Апгар?",
            {"Состояние новорожденных", "Количество лейкоцитов в моче", "Зрение", "Обильность потоотделения"},
            0 // Состояние новорожденных
        },
        {
            "Скільки кісток складається стопа людини?",
            {"35", "22", "18", "26"},
            3 // 26
        },
        {
            "Какой угол наклона оси вращения Земли?",
            {"8 градусов", "17 градусов", "23 градуса", "0 градусов"},
            2 // 23 градуса
        },
        {
            "Кто автор картины \"Не ждали\"?",
            {"Шишкин", "Репин", "Иванов", "Васнецов"},
            1 // Репин
        },
        {
            "Какой остров в Японии является самым большим?",
            {"Кюсю", "Хонсю", "Хоккайдо", "Фуджи"},
            1 // Хонсю
        }
    };

    int score = 0;
    int totalQuestions = questions.size();

    // Приветствие
    clearScreen();
    showHeader();
    cout << "Добро пожаловать в викторину!" << endl;
    cout << "Вам будет предложено " << totalQuestions << " вопросов." << endl;
    cout << "Выберите правильный ответ (1-4)." << endl;
    cout << endl;
    waitForKey();

    // Проход по вопросам
    for (size_t i = 0; i < questions.size(); i++) {
        clearScreen();
        showHeader();

        cout << "Вопрос " << (i + 1) << " из " << totalQuestions << ":" << endl;
        cout << endl;
        cout << questions[i].text << endl;
        cout << endl;

        // Вывод вариантов ответов
        for (size_t j = 0; j < questions[i].options.size(); j++) {
            cout << (j + 1) << ". " << questions[i].options[j] << endl;
        }
        cout << endl;

        // Получение ответа пользователя
        int userAnswer;
        cout << "Ваш ответ: ";
        cin >> userAnswer;

        // Проверка ответа
        if (userAnswer >= 1 && userAnswer <= 4) {
            if (userAnswer - 1 == questions[i].correctAnswer) {
                cout << endl;
                cout << "✓ Правильно!" << endl;
                score++;
            } else {
                cout << endl;
                cout << "✗ Неправильно!" << endl;
                cout << "Правильный ответ: " << (questions[i].correctAnswer + 1) << ". " << questions[i].options[questions[i].correctAnswer] << endl;
            }
        } else {
            cout << endl;
            cout << "✗ Неверный ввод!" << endl;
            cout << "Правильный ответ: " << (questions[i].correctAnswer + 1) << ". " << questions[i].options[questions[i].correctAnswer] << endl;
        }

        waitForKey();
    }

    // Показ результата
    showResult(score, totalQuestions);

    // Возможность повторить
    cout << endl << "Хотите попробовать еще раз? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y' || choice == 'н' || choice == 'Н') {
        main(); // Рекурсивный запуск для повторения
    }

    return 0;
}
