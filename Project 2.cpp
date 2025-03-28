#include <iostream>
#include<cstdlib>
#include<time.h>
#include<windows.h>
using namespace std;

enum enQuestionLevel
{
    easyLevel = 1,
    mediumLevel = 2,
    hardLevel = 3,
    mixLevel = 4
};

enum enOperationType
{
    addition = 1,
    subtraction = 2,
    multiplication = 3,
    division = 4,
    mix = 5
};

struct stQuestion
{
    int fNumber = 0;
    int sNumber = 0;
    enOperationType operationType;
    enQuestionLevel questionLevel;
    int playerAnswer = 0;
    int correctAnswer = 0;
    bool answerResult = false;
};

struct stQuiz
{
    stQuestion questionList[100];
    short numberOfQuestions = 0;
    enQuestionLevel questionsLevel;
    enOperationType operationType;
    short numberOfRightAnswers = 0;
    short numberOfWrongAnswers = 0;
    bool isPass = false;
};

short randomNumber(short From, short To);
void resetScreen();
void startGame();
void playMathGame();
short getNumberOfQuestions();
enQuestionLevel getQuestionLevel();
enOperationType getOperationType();
void generateQuizQuestions(stQuiz& quiz);
stQuestion generateQuestion(enQuestionLevel questionLevel, enOperationType operationType);
int simpleCalculator(int fNumber, int sNumber, enOperationType operationType);
void askAndCorrectQuestionListAnswers(stQuiz& quiz);
string getOperationTypeSymbol(enOperationType operationType);
void printTheQuestion(stQuiz quiz, short question);
int readPlayerAnswer();
void correctTheQuestionAnswer(stQuiz& quiz, int question);
void setScreenColor(bool answerResult);
void printQuizResults(stQuiz quiz);
string getFinalResultsText(bool isPass);
string getQuestionLevelText(enQuestionLevel questionLevel);
string getOpTypeSymbol(enOperationType operationType);

int main()
{
    //Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));
    startGame();
}

short randomNumber(short From, short To)
{
    short randNum = rand() % (To - From + 1) + From;
    return randNum;
}

void resetScreen()
{
    system("cls");
    system("color 0F");
}

void startGame()
{
    char playAgain = 'y';
    do
    {
        resetScreen();
        playMathGame();
        cout << "Do you want to play again? Y/N ? ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    system("color 0F");
}

void playMathGame()
{
    stQuiz quiz;
    quiz.numberOfQuestions = getNumberOfQuestions();
    quiz.questionsLevel = getQuestionLevel();
    quiz.operationType = getOperationType();
    generateQuizQuestions(quiz);
    askAndCorrectQuestionListAnswers(quiz);
    printQuizResults(quiz);
    setScreenColor(quiz.isPass);
}

short getNumberOfQuestions()
{
    short numberOfQuestions = 0;
    do
    {
        cout << "How many questions do you want to answer ? ";
        cin >> numberOfQuestions;
    } while (numberOfQuestions < 1 || numberOfQuestions > 10);
    return numberOfQuestions;
}

enQuestionLevel getQuestionLevel()
{
    short questionLevel;
    do
    {
        cout << "Enter question level [1]Easy, [2]Medium, [3]Hard, [4]Mix? ";
        cin >> questionLevel;
    } while (questionLevel < 1 || questionLevel>4);
    return (enQuestionLevel)questionLevel;
}

enOperationType getOperationType()
{
    short operationType;
    do
    {
        cout << "Enter operation type [1]Addition, [2]subtraction, [3]multiplication, [4]Division, [5]Mix? ";
        cin >> operationType;
    } while (operationType < 1 || operationType>5);
    return (enOperationType)operationType;
}

void generateQuizQuestions(stQuiz& quiz)
{

    for (short question = 0;question < quiz.numberOfQuestions;question++)
    {
        quiz.questionList[question] = generateQuestion(quiz.questionsLevel, quiz.operationType);
    }
}

stQuestion generateQuestion(enQuestionLevel questionLevel, enOperationType operationType)
{
    stQuestion question;
    if (questionLevel == enQuestionLevel::mixLevel)
    {
        questionLevel = (enQuestionLevel)randomNumber(1, 3);
    }
    if (operationType == enOperationType::mix)
    {
        operationType = (enOperationType)randomNumber(1, 4);
    }
    question.operationType = operationType;

    switch (questionLevel)
    {
    case enQuestionLevel::easyLevel:
        question.fNumber = randomNumber(1, 10);
        question.sNumber = randomNumber(1, 10);
        question.correctAnswer = simpleCalculator(question.fNumber, question.sNumber, question.operationType);
        question.questionLevel = questionLevel;
        return question;
    case enQuestionLevel::mediumLevel:
        question.fNumber = randomNumber(10, 50);
        question.sNumber = randomNumber(10, 50);
        question.correctAnswer = simpleCalculator(question.fNumber, question.sNumber, question.operationType);
        question.questionLevel = questionLevel;
        return question;
    case enQuestionLevel::hardLevel:
        question.fNumber = randomNumber(50, 100);
        question.sNumber = randomNumber(50, 100);
        question.correctAnswer = simpleCalculator(question.fNumber, question.sNumber, question.operationType);
        question.questionLevel = questionLevel;
        return question;
    }
    return question;
}

int simpleCalculator(int fNumber, int sNumber, enOperationType operationType)
{
    switch (operationType)
    {
    case enOperationType::addition:
        return fNumber + sNumber;
    case enOperationType::subtraction:
        return fNumber - sNumber;
    case enOperationType::multiplication:
        return fNumber * sNumber;
    case enOperationType::division:
        return fNumber / sNumber;
    default:
        return fNumber + sNumber;
    }
}

void askAndCorrectQuestionListAnswers(stQuiz& quiz)
{
    for (short question = 0;question < quiz.numberOfQuestions;question++)
    {
        printTheQuestion(quiz, question);
        quiz.questionList[question].playerAnswer = readPlayerAnswer();
        correctTheQuestionAnswer(quiz, question);
    }
    quiz.isPass = (quiz.numberOfRightAnswers >= quiz.numberOfWrongAnswers);
}

string getOperationTypeSymbol(enOperationType operationType)
{
    switch (operationType)
    {
    case enOperationType::addition:
        return "+";
    case enOperationType::subtraction:
        return "-";
    case enOperationType::multiplication:
        return "*";
    case enOperationType::division:
        return "/";
    }
}

void printTheQuestion(stQuiz quiz, short question)
{
    cout << '\n';
    cout << "Question [" << question + 1 << "/" << quiz.numberOfQuestions << "]" << "\n\n";
    cout << quiz.questionList[question].fNumber << '\n';
    cout << quiz.questionList[question].sNumber << "  ";
    cout << getOperationTypeSymbol(quiz.questionList[question].operationType) << '\n';
    cout << "-----------------------\n";
}

int readPlayerAnswer()
{
    int playerAnswer = 0;
    cin >> playerAnswer;
    return playerAnswer;
}

void correctTheQuestionAnswer(stQuiz& quiz, int question)
{
    if (quiz.questionList[question].playerAnswer != quiz.questionList[question].correctAnswer)
    {
        quiz.questionList[question].answerResult = false;
        quiz.numberOfWrongAnswers++;
        cout << "Wrong answer :-(\n";
        cout << "The right answer is: ";
        cout << quiz.questionList[question].correctAnswer;
        cout << '\n';
    }
    else
    {
        quiz.questionList[question].answerResult = true;
        quiz.numberOfRightAnswers++;
        cout << "Right answer :-)\n";
    }
    cout << endl;
    setScreenColor(quiz.questionList[question].answerResult);
}

void setScreenColor(bool answerResult)
{
    if (answerResult == true)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << '\a';
    }
}

void printQuizResults(stQuiz quiz)
{
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Resutls is " << getFinalResultsText(quiz.isPass);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << quiz.numberOfQuestions << endl;
    cout << "Questions Level : " << getQuestionLevelText(quiz.questionsLevel) << endl;
    cout << "OpType : " << getOpTypeSymbol(quiz.operationType) << endl;
    cout << "Number of Right Answers: " << quiz.numberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << quiz.numberOfWrongAnswers << endl;
    cout << "______________________________\n";
}

string getFinalResultsText(bool isPass)
{
    return (isPass ? "Pass:-)" : "Fail:-(");
}

string getQuestionLevelText(enQuestionLevel questionLevel)
{
    string questionLevelArr[4] = { "Easy","Medium","Hard","Mix" };
    return questionLevelArr[questionLevel - 1];
    //switch (questionLevel)
    //{
    //case enQuestionLevel::easyLevel:
    //    return "Easy";
    //case enQuestionLevel::mediumLevel:
    //    return "Medium";
    //case enQuestionLevel::hardLevel:
    //    return "Hard";
    //case enQuestionLevel::mixLevel:
    //    return "Mix";
    //}
}

string getOpTypeSymbol(enOperationType operationType)
{
    string operationTypeArr[5] = { "Addition","Subtraction","Multiplication","Division","Mix" };
    return operationTypeArr[operationType - 1];
    /*switch (operationType)
    {
    case enOperationTpe::addition:
        return "Addition";
    case enOperationTpe::subtraction:
        return "Subtraction";
    case enOperationTpe::multiplication:
        return "Multiplication";
    case enOperationTpe::division:
        return "Division";
    case enOperationTpe::mix:
        return "Mix";
    }*/
}