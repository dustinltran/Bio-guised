#ifndef FINGERPRINTSCANPOPUP_H
#define FINGERPRINTSCANPOPUP_H

#include <QDialog>

namespace Ui {
class FingerprintScanPopup;
}

class FingerprintScanPopup : public QDialog
{
    Q_OBJECT

public:
    bool registerPrint(int);
    void delay(int);
    explicit FingerprintScanPopup(QWidget *parent = 0);
    ~FingerprintScanPopup();

private slots:


private:
    Ui::FingerprintScanPopup *ui;
};

#endif // FINGERPRINTSCANPOPUP_H

