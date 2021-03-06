#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->window_title->setText(this->windowTitle());
    this->setWindowFlags(Qt::FramelessWindowHint);
    init();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (isWidgetIsTitleBar()) {
        move(event->globalX() - m_nMouseClick_X_Coordinate ,
             event->globalY() - m_nMouseClick_Y_Coordinate);
    }

}

bool MainWindow::isWidgetIsTitleBar() {
    return (m_nMouseClick_X_Coordinate >= xmin &&
            m_nMouseClick_X_Coordinate < xmax &&
            m_nMouseClick_Y_Coordinate >= ymin &&
            m_nMouseClick_Y_Coordinate < ymax);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::get_save_file_path() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (!QDir(path).exists()) {
        QDir().mkpath(path);
    }
    path += "/data/";
    if (!QDir(path).exists()) {
        QDir().mkpath(path);
    }
    path += SAVE_FILENAME;
    return path;
}

void MainWindow::init() {
    objectId.insert(ui->mon_button->objectName(), Identifier::mon);
    objectId.insert(ui->tue_button->objectName(), Identifier::tue);
    objectId.insert(ui->wed_button->objectName(), Identifier::wed);
    objectId.insert(ui->thu_button->objectName(), Identifier::thu);
    objectId.insert(ui->fri_button->objectName(), Identifier::fri);
    xmax = ui->titleBar->x() + ui->titleBar->width();
    xmin = ui->titleBar->x();
    ymax = ui->titleBar->x() + ui->titleBar->height();
    ymin = ui->titleBar->y();
    connect(ui->aboutButton, &QPushButton::clicked, this, &MainWindow::open_about);
    connect(ui->template_settings_button, &QPushButton::clicked, this, &MainWindow::edit_template);
    connect(ui->dateEdit, &QDateEdit::dateTimeChanged, this, &MainWindow::compute_week_number);
    connect(ui->mon_button, &QPushButton::clicked, this, &MainWindow::edit);
    connect(ui->tue_button, &QPushButton::clicked, this, &MainWindow::edit);
    connect(ui->wed_button, &QPushButton::clicked, this, &MainWindow::edit);
    connect(ui->thu_button, &QPushButton::clicked, this, &MainWindow::edit);
    connect(ui->fri_button, &QPushButton::clicked, this, &MainWindow::edit);
    todayWeekNumber = QDate::currentDate().weekNumber();
    dayOfWeek = QDate::currentDate().dayOfWeek();
    saveLoaded = false;

    if (QFile::exists(get_save_file_path())) {
        open_save();
    } else {
        Welcome w(week_template);
        w.exec();
        week_template = w.get_result();
    }
    if (saveLoaded) {
        set_date_to_now();
        compute_time();
    }
}

void MainWindow::highlightDayOfWeek() {
    ui->monLabel->setText("Lundi");
    ui->tueLabel->setText("Mardi");
    ui->wedLabel->setText("Mercredi");
    ui->thuLabel->setText("Jeudi");
    ui->friLabel->setText("Vendredi");
    if (todayWeekNumber == current_week.getWeekNumber()) {
        switch (dayOfWeek) {
            case 1: {
                ui->monLabel->setText(QString("> %1 <").arg(ui->monLabel->text()));
                break;
            }
            case 2: {
                ui->tueLabel->setText(QString("> %1 <").arg(ui->tueLabel->text()));
                break;
            }
            case 3: {
                ui->wedLabel->setText(QString("> %1 <").arg(ui->wedLabel->text()));
                break;
            }
            case 4: {
                ui->thuLabel->setText(QString("> %1 <").arg(ui->thuLabel->text()));
                break;
            }
            case 5: {
                ui->friLabel->setText(QString("> %1 <").arg(ui->friLabel->text()));
                break;
            }
            default: break;
        }
    }
}

void MainWindow::set_date_to_now() {
    auto date = QDate::currentDate();
    ui->dateEdit->setDate(date);
}

void MainWindow::open_save() {
    QFile* file = new QFile(get_save_file_path());
    file->open(QIODevice::ReadOnly);
    auto json = QString(file->readAll());
    file->close();
    delete file;

    QJsonObject obj = QJsonDocument::fromJson(json.toUtf8()).object();
    if (obj[KEY_SAVE_FILE_VERSION].toInt() == SAVE_FILE_VERSION) {
        week_template = Week::from_json(obj[KEY_TEMPLATE].toObject());
        QJsonArray arr = obj[KEY_WEEKS].toArray();
        for (QJsonValue val : arr) {
            weeks[val.toObject()["weekNumber"].toInt()] = Week::from_json(val.toObject());
        }
        saveLoaded = true;
    } else if (obj[KEY_SAVE_FILE_VERSION].toInt() < SAVE_FILE_VERSION) {
        QString updater = QCoreApplication::applicationDirPath() + "/save-updater.exe";
        if (QFile::exists(updater)) {
            QProcess* process = new QProcess(this);
            process->execute(updater, QStringList({"update"}));
            delete process;
            open_save();
        } else {
            panic_dialog("Cette application n'a pas pu démarrer car save-updater.exe est introuvable.\n"
                         "La réinstallation de cette application peut corriger ce problème");
        }
    } else {
        panic_dialog("Votre fichier de sauvegarde a été enregistré depuis une version plus récente de Chronos\n"
                     "Mettez à jour Chronos pour pouvoir utiliser ce fichier");
    }
}

void MainWindow::panic_dialog(QString text) {
    QMessageBox::critical(this, tr("Chronos"), text,
                                   QMessageBox::Ok, QMessageBox::Ok);
    QTimer::singleShot(0, this, &MainWindow::close);
}

void MainWindow::save_to_file() {
    QJsonArray arr;
    for (Week w : weeks) {
        arr.append(w.to_json());
    }
    QJsonObject obj {
        {KEY_TEMPLATE, week_template.to_json()},
        {KEY_WEEKS, arr},
        {KEY_SAVE_FILE_VERSION, SAVE_FILE_VERSION}
    };
    QJsonDocument doc(obj);
    QFile *f = new QFile(get_save_file_path());
    if (f->open(QIODevice::WriteOnly)) {
        f->write(doc.toJson());
        f->close();
    }
}

void MainWindow::compute_week_number(const QDateTime &dt) {
    int n = dt.date().weekNumber();
    ui->label_semaine->setText(QString("Semaine : %1").arg(QString::number(n)));
    QMapIterator<int, Week> it(weeks);
    bool working = true;
    bool found = false;
    while (it.hasNext() && working) {
        Week w = it.next().value();
        if (w.getWeekNumber() == n) {
            current_week = w;
            working = false;
            found = true;
        }
    }
    if (!found) {
        current_week = Week(week_template);
        current_week.setWeekNumber(n);
        weeks.insert(n, current_week);
        save_to_file();
    }
    compute_time();
    highlightDayOfWeek();
}

void MainWindow::compute_time() {
    ui->mon_time_label->setText(Tools::double_to_string_time(current_week.getMon().get_total()));
    ui->tue_time_label->setText(Tools::double_to_string_time(current_week.getTue().get_total()));
    ui->wed_time_label->setText(Tools::double_to_string_time(current_week.getWed().get_total()));
    ui->thu_time_label->setText(Tools::double_to_string_time(current_week.getThu().get_total()));
    ui->fri_time_label->setText(Tools::double_to_string_time(current_week.getFri().get_total()));
    ui->total_time_label->setText(Tools::double_to_string_time(current_week.total()));
    updateStartLabel();
    updateBreakLabel();
    updateEndLabel();
    updateValidIcon();

    double late = 0.0;
    double overtime = 0.0;
    int todayWeekNumber = QDate::currentDate().weekNumber();
    for (Week w : weeks) {
        if (w.getWeekNumber() <= todayWeekNumber) {
            late += (week_template.total() - w.total());
            overtime += (w.total() - week_template.total());
        }
    }

    ui->late_time_label->setText(Tools::double_to_string_time((late > 0.0) ? late : 0.0));
    ui->overtime_time_label->setText(Tools::double_to_string_time((overtime > 0.0) ? overtime : 0.0));
}

void MainWindow::updateValidIcon() {
    ui->mondayValidate->setVisible(current_week.getMon().get_validate());
    ui->tuesdayValidate->setVisible(current_week.getTue().get_validate());
    ui->wednesdayValidate->setVisible(current_week.getWed().get_validate());
    ui->thurdayValidate->setVisible(current_week.getThu().get_validate());
    ui->fridayValidate->setVisible(current_week.getFri().get_validate());
}

void MainWindow::updateStartLabel() {
    ui->monStartLabel->setText(current_week.getMon().get_start().toString("HH:mm"));
    ui->tueStartLabel->setText(current_week.getTue().get_start().toString("HH:mm"));
    ui->wedStartLabel->setText(current_week.getWed().get_start().toString("HH:mm"));
    ui->thuStartLabel->setText(current_week.getThu().get_start().toString("HH:mm"));
    ui->friStartLabel->setText(current_week.getFri().get_start().toString("HH:mm"));
}

void MainWindow::updateBreakLabel() {
    ui->monBreakLabel->setText(QString("%1 min.").arg(current_week.getMon().get_time_break()));
    ui->tueBreakLabel->setText(QString("%1 min.").arg(current_week.getTue().get_time_break()));
    ui->wedBreakLabel->setText(QString("%1 min.").arg(current_week.getWed().get_time_break()));
    ui->thuBreakLabel->setText(QString("%1 min.").arg(current_week.getThu().get_time_break()));
    ui->friBreakLabel->setText(QString("%1 min.").arg(current_week.getFri().get_time_break()));
}

void MainWindow::updateEndLabel() {
    ui->monEndLabel->setText(current_week.getMon().get_end().toString("HH:mm"));
    ui->tueEndLabel->setText(current_week.getTue().get_end().toString("HH:mm"));
    ui->wedEndLabel->setText(current_week.getWed().get_end().toString("HH:mm"));
    ui->thuEndLabel->setText(current_week.getThu().get_end().toString("HH:mm"));
    ui->friEndLabel->setText(current_week.getFri().get_end().toString("HH:mm"));
}

void MainWindow::edit() {
    QString name = QObject::sender()->objectName();
    switch (get_identifier(name)) {
        case mon:
            current_week.setMon(modify_value(current_week.getMon()));
            break;
        case tue:
            current_week.setTue(modify_value(current_week.getTue()));
            break;
        case wed:
            current_week.setWed(modify_value(current_week.getWed()));
            break;
        case thu:
            current_week.setThu(modify_value(current_week.getThu()));
            break;
        case fri:
            current_week.setFri(modify_value(current_week.getFri()));
            break;
    }
    weeks[current_week.getWeekNumber()] = current_week;
    save_to_file();
    compute_time();
}

Day MainWindow::modify_value(Day d) {
    bool isNotValidable = (current_week.getWeekNumber() > todayWeekNumber);
    SetDayDialog sdd(d, isNotValidable, this);
    int result = sdd.exec();
    if (result == QDialog::Accepted) {
        return sdd.get_result();
    }
    return d;
}

Identifier MainWindow::get_identifier(QString objectName) {
    return objectId[objectName];
}

void MainWindow::edit_template() {
    Welcome w(week_template);
    int res = w.exec();
    if (res == QDialog::Accepted) {
        week_template = w.get_result();
        save_to_file();
        compute_time();
    }
}

void MainWindow::open_about() {
    AboutBox a(this);
    a.exec();
}
