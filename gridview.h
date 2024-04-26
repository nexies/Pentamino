#pragma once

#include <QWidget>
#include <QPair>
#include "second_try.h"

class GridView : public QWidget
{
    Q_OBJECT
public:

    struct Cell
    {
        bool active {false};
        QColor color = QColor(Qt::blue);
    };

    GridView(QWidget * parent, int x = 20, int y = 20);

    pnt * givePoints();
    void setPoints(pnt * points);

public:
    QPair<int, int> dimentions;
    QVector<QVector<Cell>> grid;
    int currentActive = 0;

    void drawGrid (QPainter & painter);
    void paintCells (QPainter & painter);
    void clear ();

protected:
    bool dragSettingValue = false;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void paintEvent(QPaintEvent * event) override;

public slots:
signals:
    void selected(int num);

};

