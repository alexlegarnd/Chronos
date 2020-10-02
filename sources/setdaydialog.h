#ifndef SETDAYDIALOG_H
#define SETDAYDIALOG_H

#include <QDialog>
#include <QMouseEvent>

#include "day.h"
#include "tools.h"

namespace Ui {
class SetDayDialog;
}

class SetDayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDayDialog(Day d, bool isNotValidable, QWidget *parent = nullptr);
    ~SetDayDialog();

    Day get_result();

public slots:
    void compute_time();
    void validate();

private:
    Ui::SetDayDialog *ui;

    Day d;

    void init();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    int xmax;
    int xmin;
    int ymax;
    int ymin;
    inline bool isWidgetIsTitleBar();
};

#endif // SETDAYDIALOG_H
