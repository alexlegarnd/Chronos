#ifndef WEEK_H
#define WEEK_H

#define MONDAY "monday"
#define TUESDAY "tuesday"
#define WEDNESDAY "wednesday"
#define THURDAY "thurday"
#define FRIDAY "friday"
#define WEEK_NUMBER "weekNumber"

#include <QJsonObject>
#include "day.h"

class Week
{
public:
    Week();
    double total();

    void setMon(Day);
    void setTue(Day);
    void setWed(Day);
    void setThu(Day);
    void setFri(Day);
    void setWeekNumber(int);

    Day getMon();
    Day getTue();
    Day getWed();
    Day getThu();
    Day getFri();
    int getWeekNumber();

    static Week from_json(QJsonObject);
    QJsonObject to_json();

private:
    Day mon;
    Day tue;
    Day wed;
    Day thu;
    Day fri;
    int week_number;
};

#endif // WEEK_H
