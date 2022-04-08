#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QVector>
#include <QPixmap>
#include <QImage>
#include <QColor>
#include <QStack>
#include <mutex>
#include <QWidget>
#include <QPainter>
#include <thread>

#include "drawlabel.h"

//#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

    friend class myThread;

private slots:
	void on_fillPushButton_clicked();
    void on_clearPushButton_clicked();



private:
	Ui::MainWindow *ui;

	bool closed;
	QVector<QPoint> points;
	QVector<QLine> edges;

	const QColor defaultBoundColor = Qt::black;
	const QColor defaultFillColor;
	QColor fillColor;
	QPixmap pixmap;
	QImage image;

	int start_point;
	enum DrawType {	none, horizontal, vertical, diagonal };
	DrawType drawType();
	void addPoint(const QPoint &point, DrawType drawType);
	void addEdge(const QLine &edge);

    void bricklayer(int start, int end, QPainter &painter, QBrush color);


	void delay(int);
	void clearImage();
	void displayImage();
	void colorLabel();

	static const int x_min = 0;
	static const int y_min = 0;
    static const int x_max = 1201;
    static const int y_max = 851;
	void pushNewSeed(QStack<QPoint> &stack, int y, int x_left, int x_right);
	bool cleanPixel(int x, int y);
	bool boundPixel(int x, int y);

    std::mutex mtx;

    QPainter painter;


    int deltaBrick = 100;

public:
    //QPainter pain() {return painter;};
    void brickparallel(QPainter &painter);
};
#endif // MAINWINDOW_H
