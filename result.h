#ifndef RESULT_H
#define RESULT_H

#include <vector>
#include <QString>
using namespace std;

struct Result
{
    QString user_name;
    QString time;
    QString date;
    QString test_name;
    QString num_answer;
    vector <QString> correct;

};

#endif // RESULT_H
