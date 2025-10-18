#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

int Random_Computer(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

struct St_Final_Result_is_Pass
{
    int NumberOfQuestions = 0;
    string QuestionsLEvel = "";
    string optype = "";
    int NumberOfRightAnswers = 0;
    int NumberofWrongAnswers = 0;
};

enum En_level { Easy = 1, Med = 2, Hart = 3, mix = 4 };
enum En_op { collection = 1, stated = 2, to_hit = 3, portion = 4, mix_op = 5 };

En_level QuestionsLEvel_user()
{
    int number_user;
    do
    {
        cout << "Enter Questions level: [1] Easy - [2] Med - [3] Hard - [4] Mix ? : ";
        cin >> number_user;
    } while (number_user < 1 || number_user > 4);
    return (En_level)number_user;
}

En_op oprethion()
{
    int op;
    do
    {
        cout << "Enter Operation Type : [1](+) OR [2](-) OR [3](*) OR [4](/) OR [5](Mix) : ";
        cin >> op;
    } while (op < 1 || op > 5);
    return (En_op)op;
}

void Levels_user(St_Final_Result_is_Pass& levels_game, En_level levels_choice)
{
    if (levels_choice == Easy) levels_game.QuestionsLEvel = "Easy";
    else if (levels_choice == Med) levels_game.QuestionsLEvel = "Med";
    else if (levels_choice == Hart) levels_game.QuestionsLEvel = "Hard";
    else if (levels_choice == mix) levels_game.QuestionsLEvel = "Mix";
    else levels_game.QuestionsLEvel = "Unknown";
}

void oprethoin_user(St_Final_Result_is_Pass& oprethion_game, En_op op)
{
    if (op == collection) oprethion_game.optype = "+";
    else if (op == stated) oprethion_game.optype = "-";
    else if (op == to_hit) oprethion_game.optype = "*";
    else if (op == portion) oprethion_game.optype = "/";
    else if (op == mix_op) oprethion_game.optype = "Mix";
    else oprethion_game.optype = "Unknown";
}

// دالة تسأل سؤال واحد حسب المستوى و العملية (لو العملية mix تختار عملية واحدة عشوائياً)
void check_level_(St_Final_Result_is_Pass& Final_Result_is_Pass, En_level level, En_op oprethon)
{
    int UserAnswer = 0;
    int expected = 0;

    // تحديد نطاق الأرقام حسب المستوى
    int minVal = 1, maxVal = 10;
    if (level == Easy) { minVal = 1; maxVal = 10; }
    else if (level == Med) { minVal = 10; maxVal = 100; }
    else if (level == Hart) { minVal = 100; maxVal = 300; }
    else if (level == mix) { minVal = 1; maxVal = 300; }

    int a = Random_Computer(minVal, maxVal);
    int b = Random_Computer(minVal, maxVal);

    // تأكد ألا يكون المقسوم عليه صفر (لحالة القسمة)
    if (b == 0) b = 1;

    // إذا المستخدم اختار mix كنوع عملية -> نختار عملية عشوائية من 1..4 (بدون mix_self)
    En_op actualOp = oprethon;
    if (oprethon == mix_op)
    {
        actualOp = (En_op)Random_Computer(1, 4); // + - * /
    }

    // اسأل المستخدم حسب العملية
    switch (actualOp)
    {
    case collection:
        cout << a << " + " << b << " = ?" << endl;
        expected = a + b;
        cin >> UserAnswer;
        break;
    case stated:
        cout << a << " - " << b << " = ?" << endl;
        expected = a - b;
        cin >> UserAnswer;
        break;
    case to_hit:
        cout << a << " * " << b << " = ?" << endl;
        expected = a * b;
        cin >> UserAnswer;
        break;
    case portion:
        // نطلب قسمة صحيحة (integer division) أو يمكن تعديل لتطلب ناتج عشري
        cout << a << " / " << b << " = ? (Integer division)" << endl;
        expected = a / b;
        cin >> UserAnswer;
        break;
    default:
        cout << "Unknown operation!" << endl;
        return;
    }

    // تقييم الإجابة فوراً
    if (UserAnswer == expected)
    {
        Final_Result_is_Pass.NumberOfRightAnswers++;
        system("color 2f");
        Beep(1000, 200);
        cout << "Right Answer :)" << endl;
    }
    else
    {
        Final_Result_is_Pass.NumberofWrongAnswers++;
        system("color 4f");
        Beep(400, 400);
        cout << "Wrong Answer :(  Correct = " << expected << endl;
    }
}

void Print_Final_Result(const St_Final_Result_is_Pass& Final_Result)
{
    cout << "\n\n====================================\n";
    cout << "           Final Results            \n";
    cout << "====================================\n";
    cout << "Level: " << Final_Result.QuestionsLEvel << endl;
    cout << "Operation Type: " << Final_Result.optype << endl;
    cout << "Questions Count: " << Final_Result.NumberOfQuestions << endl;
    cout << "Right Answers: " << Final_Result.NumberOfRightAnswers << endl;
    cout << "Wrong Answers: " << Final_Result.NumberofWrongAnswers << endl;

    if (Final_Result.NumberOfQuestions == 0)
    {
        cout << "Score: N/A (no questions)" << endl;
    }
    else
    {
        int score = (int)((float(Final_Result.NumberOfRightAnswers) / Final_Result.NumberOfQuestions) * 100);
        cout << "Score: " << score << "%" << endl;

        if (score >= 50)
        {
            system("color 2f");
            cout << "\n🎉 Congratulations! You Passed :)\n";
        }
        else
        {
            system("color 4f");
            cout << "\n😞 Sorry, You Failed :(\n";
        }
    }
    cout << "====================================\n";
}

int main()
{
    srand((unsigned)time(NULL));

    St_Final_Result_is_Pass Final_Result;

    cout << "Enter number of questions: ";
    cin >> Final_Result.NumberOfQuestions;

    En_level userLevel = QuestionsLEvel_user();
    En_op userOperation = oprethion();

    Levels_user(Final_Result, userLevel);
    oprethoin_user(Final_Result, userOperation);

    for (int i = 1; i <= Final_Result.NumberOfQuestions; i++)
    {
        cout << "\n---------- Question [" << i << "] ----------\n";
        check_level_(Final_Result, userLevel, userOperation);
    }

    Print_Final_Result(Final_Result);
    return 0;
}
