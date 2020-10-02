#include "setdaydialog.h"
#include "ui_setdaydialog.h"

SetDayDialog::SetDayDialog(Day d, bool isNotValidable, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDayDialog)
{
    ui->setupUi(this);
    ui->window_title->setText(this->windowTitle());
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    ui->validateButton->setEnabled(!isNotValidable);
    this->d = d;
    init();
}

SetDayDialog::~SetDayDialog()
{
    delete ui;
}

void SetDayDialog::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void SetDayDialog::mouseMoveEvent(QMouseEvent *event) {
    if (isWidgetIsTitleBar()) {
        move(event->globalX() - m_nMouseClick_X_Coordinate ,
             event->globalY() - m_nMouseClick_Y_Coordinate);
    }

}

bool SetDayDialog::isWidgetIsTitleBar() {
    return (m_nMouseClick_X_Coordinate >= xmin &&
            m_nMouseClick_X_Coordinate < xmax &&
            m_nMouseClick_Y_Coordinate >= ymin &&
            m_nMouseClick_Y_Coordinate < ymax);
}

void SetDayDialog::init() {
    ui->start_edit->setTime(d.get_start());
    ui->end_edit->setTime(d.get_end());
    ui->break_edit->setValue(d.get_time_break());
    xmax = ui->titleBar->x() + ui->titleBar->width();
    xmin = ui->titleBar->x();
    ymax = ui->titleBar->x() + ui->titleBar->height();
    ymin = ui->titleBar->y();
    connect(ui->start_edit, &QTimeEdit::timeChanged, this, &SetDayDialog::compute_time);
    connect(ui->end_edit, &QTimeEdit::timeChanged, this, &SetDayDialog::compute_time);
    connect(ui->validateButton, &QPushButton::clicked, this, &SetDayDialog::validate);
    connect(ui->break_edit, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &SetDayDialog::compute_time);
    ui->total_label->setText(Tools::double_to_string_time(d.get_total()));
}

void SetDayDialog::compute_time() {
    d.set_start(ui->start_edit->time());
    d.set_end(ui->end_edit->time());
    d.set_time_break(ui->break_edit->value());
    ui->total_label->setText(Tools::double_to_string_time(d.get_total()));
}

Day SetDayDialog::get_result() {
    return d;
}

void SetDayDialog::validate() {
    d.set_validate(true);
    accept();
}
