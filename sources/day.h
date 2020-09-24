#ifndef DAY_H
#define DAY_H

#define KEY_START "start"
#define KEY_END "end"
#define KEY_BREAK "break"
#define KEY_VALIDATE "validate"

#include <QTime>
#include <QJsonObject>
#include <math.h>

class Day
{

private:
    QTime start;
    QTime end;
    double time_break;
    bool validate;

public:
    Day();

    void set_start(QTime value);
    void set_end(QTime value);
    void set_time_break(double value);
    void set_validate(bool);

    QTime get_start();
    QTime get_end();
    double get_time_break();
    bool get_validate();
    QJsonObject to_json();

    double get_total();

    static Day from_json(QJsonObject);
};

#endif // DAY_H
