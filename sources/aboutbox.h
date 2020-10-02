#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>
#include <QMouseEvent>
#include <iostream>

namespace Ui {
class AboutBox;
}

class AboutBox : public QDialog
{
    Q_OBJECT

public:
    explicit AboutBox(QWidget *parent = nullptr);
    ~AboutBox();

private:
    Ui::AboutBox *ui;

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

#endif // ABOUTBOX_H
