#include "tools.h"

QString Tools::double_to_string_time(double value) {
    const int h = floor(value);
    value = round((value - h) * 60);
    if (value == 0.0) {
        return QString("%1h").arg(QString::number(h));
    } else if (value < 10.0) {
        return QString("%1h0%2").arg(QString::number(h), QString::number(value));
    }

    return QString("%1h%2").arg(QString::number(h), QString::number(value));
}
