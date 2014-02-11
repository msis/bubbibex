#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void Init();
    void drawAll();

private:
    Ui::MainWindow *ui;

signals:


private slots:


private slots:
    void on_timeBar_valueChanged(int position);
    void on_tmaxField_valueChanged(int );
    void on_buttonSimu_stateChanged(int );
    void on_buttonPaving_stateChanged(int );
    void on_buttonField_stateChanged(int );
};



#endif // MAINWINDOW_H
