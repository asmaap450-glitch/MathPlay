#include <cmath>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

enum enlevel { easy = 1, med = 2, hard = 3, mix = 4 };

enum enOprator { add = 1, sub = 2, mul = 3, Div = 4, opmix = 5 };

struct stQuestion {
    enlevel Questionlevel;
    enOprator Operatortype;
    int Num1;
    int Num2;
    int correctAnswer = 0;
    int userAnswer = 0;
    bool Answerresult = false;
};

struct  stQuizz {
    stQuestion Questionslist[100];
    short numofQustion;
    enlevel Qustionlevel;
    enOprator optype;
    short numofcorrectAnswer = 0;
    short numofwrongAnswer = 0;
    bool isPassed = false;
};

int ReadHowManyQuestion()
{
    int num;
    cout << "How many Question you want \n";
    cin >> num;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "enter vaild number\n";
        cin >> num;
    }
    return num;
}

enlevel ReadQuestionLevel() {
    int level{};
    do {
        cout << "What level you want [1]Easr, [2]medium, [3]Hard, [4]mix\n";
        cin >> level;
    } while (level < 1 || level > 4);
    return(enlevel)level;
}

enOprator ReadOpratorType() {
    int input;
    do {
        cout << "what operator do you want [1]add , [2]sub , [3]mul , [4]div , [5]mix \n";
        cin >> input;
    } while (input < 1 || input > 5);
    return (enOprator)input;
}

string QuestionLevelText(enlevel Questionlevel) {
    string arrQuestion[4] = { "easy", "med", "Hard",  "mix" };
    return arrQuestion[Questionlevel - 1];
}

int randomNumber(int from, int to) {
    return rand() % (to - from + 1) + from;
}

int SimpelCalculator(int num1, int num2, enOprator optype) {
    switch (optype) {
    case enOprator::add:
        return num1 + num2;
    case enOprator::sub:
        return num1 - num2;
    case enOprator::mul:
        return num1 * num2;
    case enOprator::Div:
        return num1 / num2;
    default:
        return 0;
    }
}

void screencollor(bool right) {
    if (right)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

string getopratortext(enOprator optype) {
    switch (optype) {
    case enOprator::add:
        return "+";
    case enOprator::sub:
        return "-";
    case enOprator::mul:
        return "*";
    case enOprator::Div:
        return "/";
    default:
        return "max";
    }
}

stQuestion GenerateQuestion(enlevel Questionlevel, enOprator optype) {
    stQuestion Question;
    if (Questionlevel == enlevel::mix) {
        Questionlevel = (enlevel)randomNumber(1, 3);
    }
    Question.Questionlevel = Questionlevel;

    if (optype == enOprator::opmix) {
        optype = (enOprator)randomNumber(1, 4);
    }
    Question.Operatortype = optype;

    switch (Questionlevel) {
    case enlevel::easy:
        Question.Num1 = randomNumber(1, 10);
        Question.Num2 = randomNumber(1, 10);
        break;
    case enlevel::med:
        Question.Num1 = randomNumber(10, 50);
        Question.Num2 = randomNumber(10, 50);
        break;
    case enlevel::hard:
        Question.Num1 = randomNumber(50, 100);
        Question.Num2 = randomNumber(50, 100);
        break;
    }
    Question.correctAnswer = SimpelCalculator(Question.Num1, Question.Num2, Question.Operatortype);
    return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz) {
    for (short question = 0; question < Quizz.numofQustion;question++)
        Quizz.Questionslist[question] = GenerateQuestion(Quizz.Qustionlevel, Quizz.optype);
}

void AskAndCorrectqQuestionAnswer(stQuizz& Quizz) {

    for (int howQuestion = 0;howQuestion < Quizz.numofQustion;howQuestion++) {

        // fancation printquestion for teacher
        cout << "\nQuestion [" << howQuestion + 1 << " / " << Quizz.numofQustion << "]\n";
        cout << Quizz.Questionslist[howQuestion].Num1 << "\n";
        cout << getopratortext(Quizz.Questionslist[howQuestion].Operatortype) << "";
        cout << Quizz.Questionslist[howQuestion].Num2 << " \n ";
        cout << "__________________\n";
        // even here
        cin >> Quizz.Questionslist[howQuestion].userAnswer;
        // fanction correct answer for teacher 
        if (Quizz.Questionslist[howQuestion].userAnswer == Quizz.Questionslist[howQuestion].correctAnswer) {
            cout << "correst (:\n";
            Quizz.numofcorrectAnswer++;
            screencollor(true);
        }
        else
        {
            cout << "wrong ):\n";
            cout << "the correct answer is : " << Quizz.Questionslist[howQuestion].correctAnswer << "\n";
            Quizz.numofwrongAnswer++;
            screencollor(false);
        }
        // even here 
        Quizz.isPassed = (Quizz.numofcorrectAnswer >= Quizz.numofwrongAnswer);
    }
}

string getFinalResult(bool pass) {
    if (pass)
        return "pass(:\n";
    else
        return "fail ):\n";
}

void printQuizzResult(stQuizz Quizz) {
    cout << "_________________________________\n";
    cout << "\nQuizz Result\n" << getFinalResult(Quizz.isPassed);
    cout << "________________________________\n";
    cout << " number of question : " << Quizz.numofQustion << "\n";
    cout << " question level : " << QuestionLevelText(Quizz.Qustionlevel) << "\n";
    cout << " oprator type : " << getopratortext(Quizz.optype) << "\n";
    cout << "number of correst answer : " << Quizz.numofcorrectAnswer << "\n";
    cout << "number of wrong answer : " << Quizz.numofwrongAnswer << "\n";
    cout << "__________________________________\n";
}

void playMathGame(stQuizz& Quizz) {

    Quizz.numofQustion = ReadHowManyQuestion();
    Quizz.Qustionlevel = ReadQuestionLevel();
    Quizz.optype = ReadOpratorType();
    GenerateQuizzQuestions(Quizz);
    AskAndCorrectqQuestionAnswer(Quizz);
    printQuizzResult(Quizz);

}

void resetScreen() {
    system("cls");
    system("color 0F");
}

void startGame() {
    stQuizz Quizz;

    char playAgain = 'Y';

    do {
        resetScreen();

        playMathGame(Quizz);

        cout << "do you want to play again? y / n\n";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    startGame();

    return 0;
}