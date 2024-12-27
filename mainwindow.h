#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSpinBox>
#include "SolverModel.h"
#include "SolverWidget.h"
#include "TestTaskWidget.h"
#include <QMainWindow>
#include "MainTaskWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void runTask();

private:
    SolverModel* m_model;         // Модель для вычислений

    SolverWidget *m_solverWidget;

    QSpinBox* m_spinBox;
};
#endif // MAINWINDOW_H
