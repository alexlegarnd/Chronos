#include "aboutbox.h"
#include "ui_aboutbox.h"

AboutBox::AboutBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutBox)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    xmax = ui->frame->x() + ui->frame->width();
    xmin = ui->frame->x();
    ymax = ui->frame->x() + ui->frame->height();
    ymin = ui->frame->y();
}

AboutBox::~AboutBox()
{
    delete ui;
}

void AboutBox::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void AboutBox::mouseMoveEvent(QMouseEvent *event) {
    if (isWidgetIsTitleBar()) {
        move(event->globalX() - m_nMouseClick_X_Coordinate ,
             event->globalY() - m_nMouseClick_Y_Coordinate);
    }

}

bool AboutBox::isWidgetIsTitleBar() {
    return (m_nMouseClick_X_Coordinate >= xmin &&
            m_nMouseClick_X_Coordinate < xmax &&
            m_nMouseClick_Y_Coordinate >= ymin &&
            m_nMouseClick_Y_Coordinate < ymax);
}
