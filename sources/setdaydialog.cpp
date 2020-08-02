#include "setdaydialog.h"
#include "ui_setdaydialog.h"

SetDayDialog::SetDayDialog(Day d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDayDialog)
{
    ui->setupUi(this);
    this->d = d;
    init();
}

SetDayDialog::~SetDayDialog()
{
    delete ui;
}

void SetDayDialog::init() {
    ui->start_edit->setTime(d.get_start());
    ui->end_edit->setTime(d.get_end());
    ui->break_edit->setValue(d.get_time_break());
    connect(ui->start_edit, &QTimeEdit::timeChanged, this, &SetDayDialog::compute_time);
    connect(ui->end_edit, &QTimeEdit::timeChanged, this, &SetDayDialog::compute_time);
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
