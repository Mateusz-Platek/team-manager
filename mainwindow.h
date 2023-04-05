#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createPerson(QString pName, QString pAge, QString pType);

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_refresh_clicked();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void goToWork();

    void removeRow();

    void on_pushButton_get_sum_clicked();

private:
    Ui::MainWindow *ui;
    QString path_name;
};
#endif // MAINWINDOW_H
