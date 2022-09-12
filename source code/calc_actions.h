#ifndef CALC_ACTIONS_H
#define CALC_ACTIONS_H
#include <QString>
#include <QVector>
#include <QRegularExpression>

class Calc_actions
{
public:
    Calc_actions();
    QString evaluate(QString data);
private:

    QMap<QString, QString> pow(QStringList pows_unsolved);
    QMap<QString, QString> sqrt(QStringList sqrts_unsolved);
};

#endif // CALC_ACTIONS_H
