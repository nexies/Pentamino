#include <QApplication>
#include "second_try.h"
#include "mainwindow.h"
//#include <QDebug>

using namespace std;


int main(int argc, char ** argv)
{
    QApplication a(argc, argv);

    auto f = [](){};

//    pnt rec6x10 [60];
//    for(int i = 0; i < 10; i++)
//    {
//        for(int j = 0; j < 6; j++)
//        {
//            rec6x10[i*6 + j].x = i;
//            rec6x10[i*6 + j].y = j;
//        }
//    }
//    for(int i = 0; i < 60; i++)
//    {
//        qDebug() << rec6x10[i].x << rec6x10[i].y;
//    }

//    PentaminoSolver solver(rec6x10);
//    if(solver.solution())
//        solver.display_solution();

    MainWindow w;
    w.show();


    return a.exec();
    return 0;
}

