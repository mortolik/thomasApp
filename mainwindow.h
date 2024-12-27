#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>

QT_FORWARD_DECLARE_CLASS(QSpinBox);

namespace Thomas
{
class SolverModel;
class SolverWidget;
}
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
    Thomas::SolverModel* m_model {nullptr};

    Thomas::SolverWidget *m_solverWidget {nullptr};

    QSpinBox* m_spinBox {nullptr};
};
#endif // MAINWINDOW_H
