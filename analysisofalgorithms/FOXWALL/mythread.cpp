#include "mythread.h"
#include <QDebug>

#include "mainwindow.h"

myThread::myThread(QString threadName, Brick br, QPainter &painter):name(threadName)
{
    this->br.delay = br.delay;
    this->br.end = br.end;
    this->br.start = br.start;



    this->painter = painter;
    //this->br.painter = *br.painter;
}

void myThread::run()
{

    //bricklayer(900, 1200, painter);
    int row = (br.end - br.start)/br.deltaBrick;
    int column = 1;
    int delta = 0;

    for (int i = 0; i < 20; i++)
    {
        row--;
        painter.drawRect(br.start + br.deltaBrick * (row) + delta, 1200 - br.deltaBrick/2 * column, br.deltaBrick, br.deltaBrick/2);

        if (!row) {
            row = (br.end - br.start)/br.deltaBrick;
            column++;
        }
        if (column % 2)
            delta = 0;
        else
            delta = 50;
        displayImage();
        delay(br.delay);
    }
    displayImage();
}

void MainWindow::delay(int times)
{
    for (int i = 0; i < times; i++) {
        repaint();
        resize(width(), height());
    }
}

