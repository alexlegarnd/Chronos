#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QMouseEvent>
#include <math.h>

#include "week.h"
#include "day.h"
#include "tools.h"
#include "setdaydialog.h"

enum Identifier {
    mon = 1,
    tue = 2,
    wed = 3,
    thu = 4,
    fri = 5
};

namespace Ui {
class Welcome;
}

class Welcome : public QDialog
{
    Q_OBJECT

public:
    explicit Welcome(Week tpl, QWidget *parent = nullptr);
    ~Welcome();

    Week get_result();

private:
    Ui::Welcome *ui;

    Week w;
    QMap<QString, Identifier> objectId;

    void init();
    void set_value_to_widget();
    Identifier get_identifier(QString objectName);
    Day modify_value(Day);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    int xmax;
    int xmin;
    int ymax;
    int ymin;
    inline bool isWidgetIsTitleBar();

public slots:
    void edit();
};

#endif // WELCOME_H
