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
    QList<int> firstList; // Roma rakamlarını çevirirken sayı listesini tutabilmek için

private slots:
    void on_pushButton_clicked(); // Roma2TamSayi

    void on_pushButton_2_clicked(); // TamSayi2Roma

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
