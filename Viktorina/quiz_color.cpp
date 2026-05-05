#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <cstdlib>

using namespace std;

// Цвета для консоли
enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_MAGENTA = 13,
    BRIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

// Установка цвета текста
void setColor(Color textColor, Color bgColor = BLACK) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((bgColor << 4) | textColor));
}

// Сброс цвета
void resetColor() {
    setColor(WHITE, BLACK);
}

// Установка кодировки UTF-8
void setUTF8() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

// Очистка экрана
void clearScreen() {
    system("cls");
}

// Структура для хранения вопроса
struct Question {
    string text;
    vector<string> options;
    int correctAnswer;
};

// База вопросов
vector<Question> loadQuestions() {
    return {
        {
            "Хто був одним із найвідоміших художників Голландії у 1600-ті роки?",
            {"Вольфганг", "Мемлинг", "Караваджо", "Рембрандт"},
            3
        },
        {
            "Що з перерахованого не психічний розлад?",
            {"Биполярное расстройство", "Депрессия", "Анемия", "Шизофрения"},
            2
        },
        {
            "Що містить найбільше білка на 100 грам?",
            {"Краб", "Тунец", "Яйца", "Банан"},
            0
        },
        {
            "Найдорожча з колись проданих картин у світі?",
            {"Алжирские женщины (Пикассо)", "Спасатель мира (Леонардо да Винчи)", "Крик (Эдвард Мунк)", "Лежащая обнаженная (Модильяни)"},
            1
        },
        {
            "Яка наука досліджує закономірності приготування, вчинення та розкриття злочину?",
            {"Уголовное право", "Криминалистика", "Криминология", "Прокурорский надзор"},
            1
        },
        {
            "Для визначення чого використовують шкалу Апгар?",
            {"Состояние новорожденных", "Количество лейкоцитов в моче", "Зрение", "Обильность потоотделения"},
            0
        },
        {
            "Скільки кісток складається стопа людини?",
            {"35", "22", "18", "26"},
            3
        },
        {
            "Какой угол наклона оси вращения Земли?",
            {"8 градусов", "17 градусов", "23 градуса", "0 градусов"},
            2
        },
        {
            "Кто автор картины \"Не ждали\"?",
            {"Шишкин", "Репин", "Иванов", "Васнецов"},
            1
        },
        {
            "Какой остров в Японии является самым большим?",
            {"Кюсю", "Хонсю", "Хоккайдо", "Фуджи"},
            1
        }
    };
}

// Отображение заголовка
void showHeader() {
    setColor(BRIGHT_CYAN);
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║           🎯 ВИКТОРИНА 2024 🎯              ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    resetColor();
    cout << endl;
}

// Отображение прогресс-бара
void showProgressBar(int current, int total) {
    int width = 40;
    int filled = (int)((double)current / total * width);

    setColor(BRIGHT_YELLOW);
    cout << "[";
    for (int i = 0; i < width; i++) {
        if (i < filled) {
            setColor(BRIGHT_GREEN);
            cout << "█";
        } else {
            setColor(GRAY);
            cout << "░";
        }
    }
    setColor(BRIGHT_YELLOW);
    cout << "] " << current << "/" << total;
    resetColor();
    cout << endl << endl;
}

// Отображение вопроса
void showQuestion(const Question& q, int questionNum, int total) {
    setColor(BRIGHT_WHITE);
    cout << "📝 Вопрос " << questionNum << " из " << total << ":" << endl;
    resetColor();
    cout << endl;

    setColor(WHITE);
    cout << q.text << endl;
    resetColor();
    cout << endl;

    for (size_t i = 0; i < q.options.size(); i++) {
        setColor(BRIGHT_CYAN);
        cout << "  " << (i + 1) << ". ";
        resetColor();
        setColor(WHITE);
        cout << q.options[i] << endl;
        resetColor();
    }
    cout << endl;
}

// Отображение правильного ответа
void showCorrectAnswer(const Question& q) {
    setColor(BRIGHT_GREEN);
    cout << "✓ Правильный ответ: " << (q.correctAnswer + 1) << ". " << q.options[q.correctAnswer] << endl;
    resetColor();
}

// Отображение результата
void showResult(int score, int total) {
    clearScreen();
    showHeader();

    double percentage = (double)score / total * 100;

    setColor(BRIGHT_YELLOW);
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║              📊 РЕЗУЛЬТАТ 📊               ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    resetColor();
    cout << endl;

    setColor(WHITE);
    cout << "Правильных ответов: ";
    setColor(BRIGHT_GREEN);
    cout << score << " из " << total << endl;
    resetColor();

    setColor(WHITE);
    cout << "Процент правильных: ";
    setColor(BRIGHT_CYAN);
    cout << percentage << "%" << endl;
    resetColor();
    cout << endl;

    // Оценка
    if (percentage == 100) {
        setColor(BRIGHT_GREEN);
        cout << "🏆 ИДЕАЛЬНО! Вы настоящий эрудит! 🏆" << endl;
    } else if (percentage >= 80) {
        setColor(BRIGHT_CYAN);
        cout << "🌟 Отличный результат! Так держать! 🌟" << endl;
    } else if (percentage >= 60) {
        setColor(BRIGHT_YELLOW);
        cout << "👍 Хороший результат! Есть куда расти! 👍" << endl;
    } else if (percentage >= 40) {
        setColor(BRIGHT_MAGENTA);
        cout << "📚 Неплохо, но стоит поучиться! 📚" << endl;
    } else {
        setColor(BRIGHT_RED);
        cout << "💪 Не сдавайтесь! Попробуйте еще раз! 💪" << endl;
    }
    resetColor();

    cout << endl;
    setColor(BRIGHT_YELLOW);
    cout << "╚════════════════════════════════════════════╝" << endl;
    resetColor();
}

// Ожидание нажатия клавиши
void waitForKey() {
    cout << endl;
    setColor(GRAY);
    cout << "Нажмите Enter, чтобы продолжить...";
    resetColor();
    cin.ignore();
    cin.get();
}

// Главное меню
void showMenu() {
    clearScreen();
    showHeader();

    setColor(BRIGHT_WHITE);
    cout << "🎮 ГЛАВНОЕ МЕНЮ" << endl;
    resetColor();
    cout << endl;

    setColor(BRIGHT_CYAN);
    cout << "  1. Начать викторину" << endl;
    cout << "  2. О программе" << endl;
    cout << "  3. Выход" << endl;
    resetColor();
    cout << endl;

    setColor(WHITE);
    cout << "Ваш выбор: ";
    resetColor();
}

// Информация о программе
void showAbout() {
    clearScreen();
    showHeader();

    setColor(BRIGHT_WHITE);
    cout << "📖 О ПРОГРАММЕ" << endl;
    resetColor();
    cout << endl;

    setColor(WHITE);
    cout << "Викторина 2024" << endl;
    cout << "Версия: 1.0" << endl;
    cout << endl;
    cout << "Программа содержит 10 вопросов на различные темы:" << endl;
    cout << "• Искусство и живопись" << endl;
    cout << "• Медицина и здоровье" << endl;
    cout << "• Наука и природа" << endl;
    cout << "• География" << endl;
    cout << "• Криминалистика" << endl;
    cout << endl;
    cout << "Разработано на C++" << endl;
    resetColor();
    cout << endl;

    waitForKey();
}

// Запуск викторины
void runQuiz() {
    vector<Question> questions = loadQuestions();
    int score = 0;
    int totalQuestions = questions.size();

    for (size_t i = 0; i < questions.size(); i++) {
        clearScreen();
        showHeader();
        showProgressBar(i + 1, totalQuestions);
        showQuestion(questions[i], i + 1, totalQuestions);

        setColor(BRIGHT_CYAN);
        cout << "Ваш ответ: ";
        resetColor();

        int userAnswer;
        cin >> userAnswer;

        cout << endl;

        if (userAnswer >= 1 && userAnswer <= 4) {
            if (userAnswer - 1 == questions[i].correctAnswer) {
                setColor(BRIGHT_GREEN);
                cout << "✓ Правильно!" << endl;
                resetColor();
                score++;
            } else {
                setColor(BRIGHT_RED);
                cout << "✗ Неправильно!" << endl;
                resetColor();
                cout << endl;
                showCorrectAnswer(questions[i]);
            }
        } else {
            setColor(BRIGHT_RED);
            cout << "✗ Неверный ввод!" << endl;
            resetColor();
            cout << endl;
            showCorrectAnswer(questions[i]);
        }

        waitForKey();
    }

    showResult(score, totalQuestions);

    cout << endl;
    setColor(BRIGHT_CYAN);
    cout << "Хотите вернуться в главное меню? (y/n): ";
    resetColor();

    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y' || choice == 'н' || choice == 'Н') {
        return;
    }
}

int main() {
    setUTF8();

    while (true) {
        showMenu();

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                runQuiz();
                break;
            case 2:
                showAbout();
                break;
            case 3:
                clearScreen();
                setColor(BRIGHT_GREEN);
                cout << "Спасибо за участие в викторине! 👋" << endl;
                resetColor();
                return 0;
            default:
                clearScreen();
                setColor(BRIGHT_RED);
                cout << "Неверный выбор! Попробуйте снова." << endl;
                resetColor();
                waitForKey();
        }
    }

    return 0;
}
