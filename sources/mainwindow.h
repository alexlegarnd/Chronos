#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define KEY_TEMPLATE "template"
#define KEY_WEEKS "weeks"
#define SAVE_FILENAME "data.json"
#define SAVE_FILE_VERSION 2
#define KEY_SAVE_FILE_VERSION "version"

#include <QMouseEvent>
#include <QGraphicsView>
#include <QJsonArray>
#include <QMainWindow>
#include <QDir>
#include <QStandardPaths>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMap>
#include <QMapIterator>
#include <QMessageBox>
#include <QTimer>
#include <QProcess>
#include <QDir>

#include "week.h"
#include "welcome.h"
#include "tools.h"
#include "aboutbox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void correctly_started();

private:
    Ui::MainWindow *ui;
    void init();
    void open_save();
    void save_to_file();
    void panic_dialog(QString text);

    // UI Update
    void updateStartLabel();
    void updateBreakLabel();
    void updateEndLabel();
    void highlightDayOfWeek();
    void updateValidIcon();

    QString get_save_file_path();
    Identifier get_identifier(QString objectName);
    Day modify_value(Day);

    Week week_template;
    Week current_week;
    QMap<int, Week> weeks;
    QMap<QString, Identifier> objectId;
    int todayWeekNumber;
    int dayOfWeek;
    bool saveLoaded;

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
    void compute_week_number(const QDateTime &dt);
    void compute_time();
    void set_date_to_now();
    void edit();
    void edit_template();
    void open_about();
};
#endif // MAINWINDOW_H
