#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <cstdlib>

using namespace std;

// Кольори для консолі
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

void setColor(Color textColor, Color bgColor = BLACK) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((bgColor << 4) | textColor));
}

void resetColor() {
    setColor(WHITE, BLACK);
}

void setUTF8() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}

void clearScreen() {
    system("cls");
}
void setWindowTitle() {
    SetConsoleTitle(TEXT("Вікторина 2024"));
}

struct Question {
    string text;
    vector<string> options;
    int correctAnswer;
};

vector<Question> loadQuestions() {
    return {
        {
            "Хто був одним із найвідоміших художників Голландії у 1600-ті роки?",
            {"Вольфганг", "Мемлінг", "Караваджо", "Рембрандт"},
            3
        },
        {
            "Що з перерахованого не є психічним розладом?",
            {"Біполярний розлад", "Депресія", "Анемія", "Шизофренія"},
            2
        },
        {
            "Що містить найбільше білка на 100 грам?",
            {"Краб", "Тунець", "Яйця", "Банан"},
            0
        },
        {
            "Найдорожча з коли-небудь проданих картин у світі?",
            {"Алжирські жінки (Пікассо)", "Рятівник світу (Леонардо да Вінчі)", "Крик (Едвард Мунк)", "Лежача оголена (Модільяні)"},
            1
        },
        {
            "Яка наука досліджує закономірності підготовки, вчинення та розкриття злочину?",
            {"Кримінальне право", "Криміналістика", "Кримінологія", "Прокурорський нагляд"},
            1
        },
        {
            "Для визначення чого використовують шкалу Апгар?",
            {"Стан новонароджених", "Кількість лейкоцитів у сечі", "Зір", "Рясне потовиділення"},
            0
        },
        {
            "Скільки кісток складає стопа людини?",
            {"35", "22", "18", "26"},
            3
        },
        {
            "Який кут нахилу осі обертання Землі?",
            {"8 градусів", "17 градусів", "23 градуси", "0 градусів"},
            2
        },
        {
            "Хто автор картини \"Не чекали\"?",
            {"Шишкін", "Рєпін", "Іванов", "Васнецов"},
            1
        },
        {
            "Який острів у Японії є найбільшим?",
            {"Кюсю", "Хонсю", "Хоккайдо", "Фудзі"},
            1
        }
    };
}

// Відображення заголовка
void showHeader() {
    setColor(BRIGHT_CYAN);
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║             ВІКТОРИНА 2024                 ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    resetColor();
    cout << endl;
}


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


void showQuestion(const Question& q, int questionNum, int total) {
    setColor(BRIGHT_WHITE);
    cout << "| Питання " << questionNum << " з " << total << ":" << endl;
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


void showCorrectAnswer(const Question& q) {
    setColor(BRIGHT_GREEN);
    cout << "✓ Правильна відповідь: " << (q.correctAnswer + 1) << ". " << q.options[q.correctAnswer] << endl;
    resetColor();
}


void showResult(int score, int total) {
    clearScreen();
    showHeader();

    double percentage = (double)score / total * 100;

    setColor(BRIGHT_YELLOW);
    cout << "╔════════════════════════════════════════════╗" << endl;
    cout << "║              | РЕЗУЛЬТАТ |               ║" << endl;
    cout << "╚════════════════════════════════════════════╝" << endl;
    resetColor();
    cout << endl;

    setColor(WHITE);
    cout << "Правильних відповідей: ";
    setColor(BRIGHT_GREEN);
    cout << score << " з " << total << endl;
    resetColor();

    setColor(WHITE);
    cout << "Відсоток правильних: ";
    setColor(BRIGHT_CYAN);
    cout << percentage << "%" << endl;
    resetColor();
    cout << endl;

    if (percentage == 100) {
        setColor(BRIGHT_GREEN);
        cout << " ІДЕАЛЬНО! Ви справжній ерудит! " << endl;
    } else if (percentage >= 80) {
        setColor(BRIGHT_CYAN);
        cout << " Чудовий результат! Так тримати! " << endl;
    } else if (percentage >= 60) {
        setColor(BRIGHT_YELLOW);
        cout << "Хороший результат! Є куди рости! " << endl;
    } else if (percentage >= 40) {
        setColor(BRIGHT_MAGENTA);
        cout << " Непогано, але варто повчитися! " << endl;
    } else {
        setColor(BRIGHT_RED);
        cout << " Не здавайтеся! Спробуйте ще раз! " << endl;
    }
    resetColor();

    cout << endl;
    setColor(BRIGHT_YELLOW);
    cout << "╚════════════════════════════════════════════╝" << endl;
    resetColor();
}

void waitForKey() {
    cout << endl;
    setColor(GRAY);
    cout << "Натисніть Enter, щоб продовжити...";
    resetColor();
    cin.ignore();
    cin.get();
}


void showMenu() {
    clearScreen();
    showHeader();

    setColor(BRIGHT_WHITE);
    cout << "| ГОЛОВНЕ МЕНЮ" << endl;
    resetColor();
    cout << endl;

    setColor(BRIGHT_CYAN);
    cout << "  1. Почати вікторину" << endl;
    cout << "  2. Про програму" << endl;
    cout << "  3. Вихід" << endl;
    resetColor();
    cout << endl;

    setColor(WHITE);
    cout << "Ваш вибір: ";
    resetColor();
}

void showAbout() {
    clearScreen();
    showHeader();

    setColor(BRIGHT_WHITE);
    cout << "| ПРО ПРОГРАМУ" << endl;
    resetColor();
    cout << endl;

    setColor(WHITE);
    cout << "Вікторина 2024" << endl;
    cout << "Версія: 1.0" << endl;
    cout << endl;
    cout << "Програма містить 10 питань на різні теми:" << endl;
    cout << "• Мистецтво і живопис" << endl;
    cout << "• Медицина і здоров'я" << endl;
    cout << "• Наука і природа" << endl;
    cout << "• Географія" << endl;
    cout << "• Криміналістика" << endl;
    cout << endl;
    cout << "Розроблено на C++" << endl;
    resetColor();
    cout << endl;

    waitForKey();
}

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
        cout << "Ваша відповідь: ";
        resetColor();

        int userAnswer;
        cin >> userAnswer;

        cout << endl;

        if (userAnswer >= 1 && userAnswer <= 4) {
            if (userAnswer - 1 == questions[i].correctAnswer) {
                setColor(BRIGHT_GREEN);
                cout << "| Правильно!" << endl;
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
            cout << "X Невірний ввід!" << endl;
            resetColor();
            cout << endl;
            showCorrectAnswer(questions[i]);
        }

        waitForKey();
    }

    showResult(score, totalQuestions);

    cout << endl;
    setColor(BRIGHT_CYAN);
    cout << "Хочете повернутися в головне меню? (y/n): ";
    resetColor();

    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y' || choice == 'т' || choice == 'Т') {
        return;
    }
}

int main() {

    setUTF8();
    setWindowTitle();

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
                cout << "Дякуємо за участь у вікторині! " << endl;
                resetColor();
                cout << endl;
                cout << "Натисніть Enter, щоб закрити вікно...";
                cin.ignore();
                cin.get();
                return 0;
            default:
                clearScreen();
                setColor(BRIGHT_RED);
                cout << "Невірний вибір! Спробуйте знову." << endl;
                resetColor();
                waitForKey();
        }
    }

    return 0;
}
