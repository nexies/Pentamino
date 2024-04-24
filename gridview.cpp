#include "gridview.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

GridView::GridView(QWidget * parent, int x, int y) :
    QWidget(parent)
{
    dimentions = {x, y};
    grid = QVector<QVector<Cell>> (x);
    for(int i = 0; i < x; i++)
    {
        grid[i] = QVector<Cell>(y);
    }
}

pnt *GridView::givePoints()
{
    pnt * out = new pnt[60];
    int c = 0;
    for(int i = 0; i < dimentions.first; i++){
        for(int j = 0; j < dimentions.second; j++)
        {
            if(grid[i][j].active)
            {
                out[c].x = i;
                out[c].y = j;
                c++;
            }
        }
    }
    return out;
}

void GridView::setPoints(pnt *points)
{
    clear();
    for(int i = 0; i < 60; i++)
    {
        grid[points[i].x][points[i].y].active = true;
        switch(points[i].val)
        {
        case 0:
            grid[points[i].x][points[i].y].color = Qt::darkBlue;
            break;
        case 1:
            grid[points[i].x][points[i].y].color = Qt::red;
            break;
        case 2:
            grid[points[i].x][points[i].y].color = Qt::blue;
            break;
        case 3:
            grid[points[i].x][points[i].y].color = Qt::green;
            break;
        case 4:
            grid[points[i].x][points[i].y].color = Qt::yellow;
            break;
        case 5:
            grid[points[i].x][points[i].y].color = Qt::darkRed;
            break;
        case 6:
            grid[points[i].x][points[i].y].color = Qt::lightGray;
            break;
        case 7:
            grid[points[i].x][points[i].y].color = Qt::cyan;
            break;
        case 8:
            grid[points[i].x][points[i].y].color = Qt::magenta;
            break;
        case 9:
            grid[points[i].x][points[i].y].color = Qt::darkGreen;
            break;
        case 10:
            grid[points[i].x][points[i].y].color = Qt::darkYellow;
            break;
        case 11:
            grid[points[i].x][points[i].y].color = Qt::darkMagenta;
            break;
        default:
            grid[points[i].x][points[i].y].color = Qt::white;
            break;
        }
    }
    repaint();
}

void GridView::drawGrid(QPainter & painter)
{
    QRect selfRect = this->geometry();
    int h = selfRect.height();
    int w = selfRect.width();
    int hspan = h / dimentions.first;
    int wspan = w / dimentions.second;

    for(int i = 1; i < dimentions.first + 1; i++)
        painter.drawLine(wspan * i, 0, wspan * i, h);
    for(int j = 1; j < dimentions.second + 1; j++)
        painter.drawLine(0, hspan * j, w, hspan * j);

}

void GridView::paintCells(QPainter &painter)
{
    QRect selfRect = this->geometry();
    int h = selfRect.height();
    int w = selfRect.width();
    int cellh = h / dimentions.first;
    int cellw = w / dimentions.second;

    for(int x = 0; x < dimentions.first; x++){
        for(int y = 0; y < dimentions.second; y++)
        {
            if(grid[x][y].active)
                painter.setBrush(grid[x][y].color);
            else
                painter.setBrush(Qt::white);
            painter.drawRect(y * cellw, x * cellh, cellw, cellh);
        }
    }
}

void GridView::clear()
{
    for(int i = 0; i < dimentions.first; i++){
        for(int j = 0; j < dimentions.second; j++)
        {
            grid[i][j].active = false;
            grid[i][j].color = Qt::blue;
        }
    }
    currentActive = 0;
    repaint();
}

void GridView::mousePressEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    QRect selfRect = this->geometry();
    int h = selfRect.height();
    int w = selfRect.width();
    int cellh = h / dimentions.first;
    int cellw = w / dimentions.second;
    int x = point.y() / cellh;
    int y = point.x() / cellw;

//    qDebug() << x << y;
    if(grid[x][y].active){
        currentActive --;
        grid[x][y].active = false;
    }else{
        currentActive ++;
        grid[x][y].active = true;
    }
//    grid[x][y].active = !grid[x][y].active;
    qDebug() << currentActive;
    emit selected (currentActive);
    repaint();
}

void GridView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    paintCells(painter);
//    drawGrid(painter);
    return QWidget::paintEvent(event);
}

