#pragma once

#include <QMainWindow>
#include "second_try.h"

namespace Ui {
class MainWindow;
}

class GridView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    GridView * grid;
    bool legal = false;

    Ui::MainWindow *ui;

private slots:
    void onSelected(int num);
    void onActionFindSolutionTriggered();
    void onActionClearTriggered();
};

