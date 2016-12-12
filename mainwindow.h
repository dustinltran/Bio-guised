#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define FINGERS 10

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void delay(int);
    ~MainWindow();

protected:
      void showEvent(QShowEvent *ev);

signals:
      void window_loaded();

private slots:
    void gatherInfo();

    void closeEvent(QCloseEvent *bar);

    void on_RegisterButton_clicked();

    void on_LPinky_clicked();

    void on_LRing_clicked();

    void on_LMiddle_clicked();

    void on_LIndex_clicked();

    void on_LThumb_clicked();

    void on_RThumb_clicked();

    void on_RIndex_clicked();

    void on_RMiddle_clicked();

    void on_RRing_clicked();

    void on_RPinky_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
