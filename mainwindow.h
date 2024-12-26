#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SolverModel.h"
#include "TestTaskWidget.h"
#include <QMainWindow>

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
    TestTaskWidget* m_taskWidget; // Виджет для отображения таблицы
};
#endif // MAINWINDOW_H
