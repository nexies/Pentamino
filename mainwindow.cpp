#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridview.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    grid = new GridView(this);
    this->setCentralWidget(grid);

    connect(grid, &GridView::selected,
            this, &MainWindow::onSelected);
    connect(ui->actionFind_solution, &QAction::triggered,
            this, &MainWindow::onActionFindSolutionTriggered);
    connect(ui->actionClear, &QAction::triggered,
            this, &MainWindow::onActionClearTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSelected(int num)
{
    if(num == 60)
        legal = true;
    else
        legal = false;
}

void MainWindow::onActionFindSolutionTriggered()
{
    if(!legal)
    {
        QMessageBox::warning(this, "Error", "You have to select exactly 60 cells to try solve");
        return;
    }


    auto list = grid->givePoints();
    auto solver = new PentaminoSolver(list);

    if(solver->solution())
    {
        QMessageBox::information(this, "Done!", "Solution found");
        grid->setPoints(solver->schema());
    }else{
        QMessageBox::information(this, "Failed", "Could not find a solution :(");
    }
    delete solver;
}

void MainWindow::onActionClearTriggered()
{
    grid->clear();
}
