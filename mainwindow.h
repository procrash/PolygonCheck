#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <iostream>

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>

#include "point.h"
#include "line.h"
#include "polygon.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:


explicit MainWindow(QWidget *parent = nullptr);
~MainWindow();
protected:

void paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    for (auto line : lines) {
        painter.drawLine(line.start.x, line.start.y, line.end.x, line.end.y);

    }
}

void mousePressEvent(QMouseEvent* event){
    std::cout << "Point clicked at:"<< event->pos().x() << " " <<  event->pos().y() << std::endl;

    points.push_back(Point(event->pos().x(), event->pos().y()));

    lines.clear();

    if (points.size()>1)
    for (std::size_t idx = 0; idx<points.size()-1; ++idx) {
        Line line(Point(points[idx].x, points[idx].y), Point(points[idx+1].x, points[idx+1].y));
        lines.push_back(line);
    }

    if (points.size()>0) {
        Line line(Point(points[points.size()-1].x, points[points.size()-1].y), Point(points[0].x, points[0].y));
        lines.push_back(line);
    }

    Polygon polygon(lines);
    std::cout << "IsSimple:" <<  (polygon.isSimple() ? "TRUE": "FALSE") << std::endl;

    this->update();
}

private:
Ui::MainWindow *ui;
std::vector<Point> points;
std::vector<Line> lines;

};

#endif // MAINWINDOW_H
