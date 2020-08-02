#include "week.h"

Week::Week()
{
    mon = Day();
    tue = Day();
    wed = Day();
    thu = Day();
    fri = Day();
    week_number = 0;
}

Week Week::from_json(QJsonObject obj) {
    Week w;
    w.mon = Day::from_json(obj[MONDAY].toObject());
    w.tue = Day::from_json(obj[TUESDAY].toObject());
    w.wed = Day::from_json(obj[WEDNESDAY].toObject());
    w.thu = Day::from_json(obj[THURDAY].toObject());
    w.fri = Day::from_json(obj[FRIDAY].toObject());
    w.week_number = obj[WEEK_NUMBER].toInt();
    return w;
}

QJsonObject Week::to_json() {
    QJsonObject obj {
        {MONDAY, mon.to_json()},
        {TUESDAY, tue.to_json()},
        {WEDNESDAY, wed.to_json()},
        {THURDAY, thu.to_json()},
        {FRIDAY, fri.to_json()},
        {WEEK_NUMBER, week_number}
    };
    return obj;
}

double Week::total() {
    return mon.get_total() + tue.get_total() + wed.get_total() + thu.get_total() + fri.get_total();
}

Day Week::getMon() {
    return mon;
}

Day Week::getTue() {
    return tue;
}

Day Week::getWed() {
    return wed;
}

Day Week::getThu() {
    return thu;
}

Day Week::getFri() {
    return fri;
}

int Week::getWeekNumber() {
    return week_number;
}

void Week::setMon(Day value) {
    mon = value;
}

void Week::setTue(Day value) {
    tue = value;
}

void Week::setWed(Day value) {
    wed = value;
}

void Week::setThu(Day value) {
    thu = value;
}

void Week::setFri(Day value) {
    fri = value;
}

void Week::setWeekNumber(int value) {
    week_number = value;
}
