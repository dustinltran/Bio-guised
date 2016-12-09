#ifndef BIOGUISED_H
#define BIOGUISED_H

#include <QMainWindow>

namespace Ui {
class BioGuised;
}

class BioGuised : public QMainWindow
{
    Q_OBJECT

public:
    explicit BioGuised(QWidget *parent = 0);
    ~BioGuised();

private slots:
    void on_addFile_clicked();

    void on_deleteFile_clicked();

    void on_addApplication_clicked();

    void on_createNewFileFolder_clicked();

    void on_unhideFile_clicked();

    void on_unhideApplication_clicked();

private:
    Ui::BioGuised *ui;
};

#endif // BIOGUISED_H
