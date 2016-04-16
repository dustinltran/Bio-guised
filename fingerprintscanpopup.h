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
    explicit FingerprintScanPopup(QWidget *parent = 0);
    ~FingerprintScanPopup();

private:
    Ui::FingerprintScanPopup *ui;
};

#endif // FINGERPRINTSCANPOPUP_H
