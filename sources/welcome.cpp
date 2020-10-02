#include "welcome.h"
#include "ui_welcome.h"

Welcome::Welcome(Week wtemplate, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
    ui->window_title->setText(this->windowTitle());
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    w = wtemplate;
    init();
}

Welcome::~Welcome()
{
    delete ui;
}

void Welcome::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void Welcome::mouseMoveEvent(QMouseEvent *event) {
    if (isWidgetIsTitleBar()) {
        move(event->globalX() - m_nMouseClick_X_Coordinate ,
             event->globalY() - m_nMouseClick_Y_Coordinate);
    }

}

bool Welcome::isWidgetIsTitleBar() {
    return (m_nMouseClick_X_Coordinate >= xmin &&
            m_nMouseClick_X_Coordinate < xmax &&
            m_nMouseClick_Y_Coordinate >= ymin &&
            m_nMouseClick_Y_Coordinate < ymax);
}

void Welcome::init() {
    set_value_to_widget();
    objectId.insert(ui->mon_button->objectName(), Identifier::mon);
    objectId.insert(ui->tue_button->objectName(), Identifier::tue);
    objectId.insert(ui->wed_button->objectName(), Identifier::wed);
    objectId.insert(ui->thu_button->objectName(), Identifier::thu);
    objectId.insert(ui->fri_button->objectName(), Identifier::fri);
    xmax = ui->titleBar->x() + ui->titleBar->width();
    xmin = ui->titleBar->x();
    ymax = ui->titleBar->x() + ui->titleBar->height();
    ymin = ui->titleBar->y();
    connect(ui->mon_button, &QPushButton::clicked, this, &Welcome::edit);
    connect(ui->tue_button, &QPushButton::clicked, this, &Welcome::edit);
    connect(ui->wed_button, &QPushButton::clicked, this, &Welcome::edit);
    connect(ui->thu_button, &QPushButton::clicked, this, &Welcome::edit);
    connect(ui->fri_button, &QPushButton::clicked, this, &Welcome::edit);
}

Week Welcome::get_result() {
    return w;
}

void Welcome::set_value_to_widget() {
    ui->mon_time_label->setText(Tools::double_to_string_time(w.getMon().get_total()));
    ui->tue_time_label->setText(Tools::double_to_string_time(w.getTue().get_total()));
    ui->wed_time_label->setText(Tools::double_to_string_time(w.getWed().get_total()));
    ui->thu_time_label->setText(Tools::double_to_string_time(w.getThu().get_total()));
    ui->fri_time_label->setText(Tools::double_to_string_time(w.getFri().get_total()));
    ui->total->setText(Tools::double_to_string_time(w.total()));
}

void Welcome::edit() {
    QString name = QObject::sender()->objectName();
    switch (get_identifier(name)) {
        case mon:
            w.setMon(modify_value(w.getMon()));
            break;
        case tue:
            w.setTue(modify_value(w.getTue()));
            break;
        case wed:
            w.setWed(modify_value(w.getWed()));
            break;
        case thu:
            w.setThu(modify_value(w.getThu()));
            break;
        case fri:
            w.setFri(modify_value(w.getFri()));
            break;
    }
    set_value_to_widget();
}

Day Welcome::modify_value(Day d) {
    SetDayDialog sdd(d, true, this);
    int result = sdd.exec();
    if (result == QDialog::Accepted) {
        return sdd.get_result();
    }
    return d;
}

Identifier Welcome::get_identifier(QString objectName) {
    return objectId[objectName];
}

