#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "brick.h"

class myThread : public QThread
{
public:
    explicit myThread(QString threadName, Brick br, QPainter &painter);

    // Переопределяем метод run(), в котором будет
    // располагаться выполняемый код
    void run();
private:
    QString name;   // Имя потока
    Brick br;
    QPainter painter;
};

#endif // MYTHREAD_H
