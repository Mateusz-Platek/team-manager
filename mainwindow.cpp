#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>
#include "person.h"
#include "driver.h"
#include "mechanic.h"
#include <vector>

std::vector<Person*> persons;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Driver");
    ui->comboBox->addItem("Mechanic");
    setWindowTitle("Team Menager");
}

MainWindow::~MainWindow()
{
    for (auto person : persons) {
        delete person;
    }
    delete ui;
}

void MainWindow::on_pushButton_add_clicked()
{
    QString name = ui->lineEdit_name->text();
    int age = ui->lineEdit_age->text().toInt();

    try {
        if (age < 18 || age > 100) {
            throw(age);
        }
        if (name.size() < 3 || name.size() > 40) {
            throw(name);
        }
    }
    catch(int num) {
        (void)num;
        QMessageBox::information(this, "Wrong age", "Age is too small or too big");
        return;
    }
    catch(QString cName) {
        QMessageBox::information(this, "Wrong name", "Name is too short or too long");
        return;
    }

    ui->lineEdit_name->setText("");
    ui->lineEdit_age->setText("");
    if (ui->comboBox->currentText() == "Driver") {
        persons.push_back(new Driver(name, age));
    } else if (ui->comboBox->currentText() == "Mechanic") {
        persons.push_back(new Mechanic(name, age));
    }
    on_pushButton_refresh_clicked();
}

void MainWindow::on_pushButton_refresh_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QTableWidgetItem *headers[] {
        new QTableWidgetItem("Name"),
        new QTableWidgetItem("Age"),
        new QTableWidgetItem("Experience"),
        new QTableWidgetItem("Role"),
        new QTableWidgetItem("Work"),
        new QTableWidgetItem("Remove")
    };
    for (int i = 0; i < sizeof(headers) / sizeof(QTableWidgetItem*); i++) {
        ui->tableWidget->setHorizontalHeaderItem(i, headers[i]);
    }

    for (auto person : persons) {
        QTableWidgetItem *items[] {
            new QTableWidgetItem(person->getName()),
            new QTableWidgetItem(QString::number(person->getAge())),
            new QTableWidgetItem(QString::number(person->experience()))
        };
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(rowCount + 1);
        for (int i = 0; i < sizeof(items) / sizeof(QTableWidgetItem*); i++) {
            items[i]->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(rowCount, i, items[i]);
        }

        if (person->getType() == 0) {
            QTableWidgetItem *item = new QTableWidgetItem("Driver");
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(rowCount, 3, item);
        } else if (person->getType() == 1) {
            QTableWidgetItem *item = new QTableWidgetItem("Mechanic");
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            ui->tableWidget->setItem(rowCount, 3, item);
        }

        QPushButton *pushButton_work = new QPushButton("Work");
        connect(pushButton_work, &QPushButton::clicked, this, &MainWindow::goToWork);
        ui->tableWidget->setCellWidget(rowCount, 4, pushButton_work);
        QPushButton *pushButton_remove = new QPushButton("Remove");
        connect(pushButton_remove, &QPushButton::clicked, this, &MainWindow::removeRow);
        ui->tableWidget->setCellWidget(rowCount, 5, pushButton_remove);
    }
}


void MainWindow::on_actionNew_triggered()
{
    path_name = "";
    for (auto person : persons) {
        delete person;
    }
    persons.clear();
    on_pushButton_refresh_clicked();
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C:/","Bin files (*.bin)");
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly)) {
        return;
    }

    for (auto person : persons) {
        delete person;
    }
    persons.clear();

    QDataStream in(&file);
    size_t personSize;
    in >> personSize;
    for (int i = 0; i < personSize; i++) {
        int age;
        in >> age;
        int experience;
        in >> experience;
        int type;
        in >> type;
        QString name;
        in >> name;
        if (type == 0) {
            Person *person = new Driver(name, age);
            person->setExperience(experience);
            persons.push_back(person);
        } else if (type == 1) {
            Person *person = new Mechanic(name, age);
            person->setExperience(experience);
            persons.push_back(person);
        }
    }

    file.close();

    on_pushButton_refresh_clicked();
}

void MainWindow::on_actionSave_triggered()
{
    if (path_name == "") {
        QMessageBox::information(this, "Save as", "First use save us");
        return;
    }
    QFile file(path_name);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QDataStream out(&file);
    size_t personsSize = persons.size();
    out << personsSize;
    for (auto person : persons) {
        int age = person->getAge();
        out << age;
        int experience = person->experience();
        out << experience;
        int type = person->getType();
        out << type;
        QString name = person->getName();
        out << name;
    }

    file.flush();
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save a file", "C:/", "Bin files (*.bin)");
    path_name = file_name;
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QDataStream out(&file);
    size_t personsSize = persons.size();
    out << personsSize;
    for (auto person : persons) {
        int age = person->getAge();
        out << age;
        int experience = person->experience();
        out << experience;
        int type = person->getType();
        out << type;
        QString name = person->getName();
        out << name;
    }

    file.flush();
    file.close();
}

void MainWindow::goToWork()
{
    int row = ui->tableWidget->currentRow();
    persons[row]->work();
    on_pushButton_refresh_clicked();
}

void MainWindow::removeRow()
{
    int row = ui->tableWidget->currentRow();
    delete persons[row];
    persons.erase(persons.begin() + row);
    on_pushButton_refresh_clicked();
}

void MainWindow::createPerson(QString pName, QString pAge, QString pType)
{
    int age = pAge.toInt();
    int type = pType.toInt();

    try {
        if (age < 18 || age >100) {
            throw(age);
        }
        if (type < 0 || type > 1) {
            throw(type);
        }
    }
    catch(int num) {
        (void)num;
        QMessageBox::information(this, "Wrong age or role", "Age is too small or too big\n");
        return;
    }

    if (type == 0) {
        Person *person = new Driver(pName, age);
        persons.push_back(person);
        on_pushButton_refresh_clicked();
    } else if (type == 1) {
        Person *person = new Mechanic(pName, age);
        persons.push_back(person);
        on_pushButton_refresh_clicked();
    }
}


void MainWindow::on_pushButton_get_sum_clicked()
{
    int sum = 0;
    for (auto person : persons) {
        sum = sum + *person;
    }
    ui->lineEdit_sum->setText(QString::number(sum));
}

