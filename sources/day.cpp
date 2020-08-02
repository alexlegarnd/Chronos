#include "day.h"

Day::Day()
{
    start = QTime(9, 0, 0, 0);
    end = QTime(17, 15, 0, 0);
    time_break = 45.0;
}

double Day::get_total() {
    int sec = start.secsTo(end);
    int minutes = sec / 60;
    return (minutes - time_break) / 60;
}

void Day::set_start(QTime value)
{
    start = value;
}

void Day::set_end(QTime value)
{
    end = value;
}

void Day::set_time_break(double value)
{
    time_break = value;
}

QTime Day::get_start()
{
    return start;
}

QTime Day::get_end()
{
    return end;
}

double Day::get_time_break()
{
    return time_break;
}

QJsonObject Day::to_json()
{
    QJsonObject obj{
        {KEY_START, start.toString(Qt::DateFormat::ISODate)},
        {KEY_END, end.toString(Qt::DateFormat::ISODate)},
        {KEY_BREAK, time_break}
    };

    return obj;
}

Day Day::from_json(QJsonObject obj)
{
    Day result;

    result.start = QTime::fromString(obj[KEY_START].toString(), Qt::DateFormat::ISODate);
    result.end = QTime::fromString(obj[KEY_END].toString(), Qt::DateFormat::ISODate);
    result.time_break = obj[KEY_BREAK].toDouble();

    return result;
}
