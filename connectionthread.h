#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H
#include <QThread>
#include <QString>



class ConnectionThread : public QThread
{
public:
    explicit ConnectionThread();
    void run();
    void delay(int);

private:
    QString name;
};

#endif // CONNECTIONTHREAD_H
