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

private:
    Ui::BioGuised *ui;
};

#endif // BIOGUISED_H
