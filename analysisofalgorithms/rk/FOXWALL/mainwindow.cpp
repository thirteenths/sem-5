#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QMessageBox>
#include <QPainter>
//#include <QLabel>
#include "drawlabel.h"

#include <vector>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::MainWindow),
	defaultBoundColor(Qt::black),
    defaultFillColor(Qt::black),
	fillColor(defaultFillColor),
    pixmap(x_max + 1, y_max + 1),
    image(x_max + 1, y_max + 1, QImage::Format_RGB32),
	start_point(0)
{
	ui->setupUi(this);

	ui->drawLabel->setPixmapPointer(pixmap);

    clearImage();
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_fillPushButton_clicked()
{
    QPainter painter(&pixmap);
    painter.setPen(fillColor);

    painter.drawRect(0, 0, x_max - 1, y_max - 1) ;


    //painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));


    //bricklayer(0, 300, painter);
    //painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    //bricklayer(300, 600, painter);
    //painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    //bricklayer(600, 900, painter);
    //painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    //bricklayer(900, 1200, painter);

    brickparallel(painter);

	displayImage();
}

void MainWindow::brickparallel(QPainter &painter)
{
    std::vector<std::thread> threadArray;
    int start = 0;
    int end = 300;

    QVector<QBrush> color = {QBrush(Qt::red, Qt::SolidPattern),QBrush(Qt::darkCyan, Qt::SolidPattern), QBrush(Qt::green, Qt::SolidPattern),QBrush(Qt::yellow, Qt::SolidPattern) };

    for (int i = 0; i < 4; i++)
    {
            painter.setBrush(color[i]);
            threadArray.push_back(std::thread(&MainWindow::bricklayer, this, start, end, std::ref(painter), color[i]));
            start += 300;
            end += 300;
    }

    for (int i = 0; i < 4; i++)
    {
        threadArray[i].join();
    }
}

void MainWindow::bricklayer(int start, int end, QPainter &painter, QBrush color)
{
    //painter.setBrush(color);
    const int delay_value = 100;

    int row = (end - start)/deltaBrick;
    int column = 1;
    int delta = 0;

    for (int i = 0; i < 50; i++)
    {
        row--;
        mtx.lock();
        painter.setBrush(color);
        painter.drawRect(start + deltaBrick * (row) + delta, y_max - deltaBrick/2 * column, deltaBrick, deltaBrick/2);
        mtx.unlock();
        if (!row) {
            row = (end - start)/deltaBrick;
            column++;
        }
        if (column % 2)
            delta = 0;
        else
            delta = 50;
        mtx.lock();
        displayImage();
        mtx.unlock();
        delay(delay_value);
    }
    //mtx.lock();
    //displayImage();
    //mtx.unlock();
}

bool MainWindow::boundPixel(int x, int y)
{
	return image.pixelColor(x, y) == defaultBoundColor;
}

bool MainWindow::cleanPixel(int x, int y)
{
	const QColor color = image.pixelColor(x, y);
	return color != defaultBoundColor && color != fillColor;
}



void MainWindow::on_clearPushButton_clicked()
{
	clearImage();
	closed = false;
	points.clear();
	edges.clear();
    start_point = 0;
}


void MainWindow::delay(int times)
{
	for (int i = 0; i < times; i++) {
        mtx.lock();
		repaint();
        //resize(width(), height());
        mtx.unlock();
	}
}

void MainWindow::clearImage()
{
	pixmap.fill();
	displayImage();
}

void MainWindow::displayImage()
{
	ui->drawLabel->update();
	image = pixmap.toImage();
}

