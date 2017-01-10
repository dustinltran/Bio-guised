#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H
#include <QtCore>
#include <QString>


class ConnectionThread : public QThread
{
public:
    ConnectionThread();
    void run();
    void delay(int);

private:
    QString name;

private slots:
    void gatherInfo();

signals:
    void window_loaded2();
};

#endif // CONNECTIONTHREAD_H
