#include <QLabel>
#include <QWidget>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>

#include "MainWindow.h"
#include "MainTaskWidget.h"
#include "SolverModel.h"
#include "SolverWidget.h"
#include "TestTaskWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    m_model = new Thomas::SolverModel(this);
    m_solverWidget = new Thomas::SolverWidget(m_model, this);

    QGroupBox *controlGroupBox = new QGroupBox("Управление", this);
    QHBoxLayout *controlLayout = new QHBoxLayout(controlGroupBox);

    QLabel *spinBoxLabel = new QLabel("Количество узлов:", controlGroupBox);
    m_spinBox = new QSpinBox(controlGroupBox);
    m_spinBox->setMinimumWidth(60);
    m_spinBox->setMinimum(0);
    m_spinBox->setMaximum(10000);
    m_spinBox->setValue(1000);

    QPushButton *runButton = new QPushButton("Run Task", controlGroupBox);
    connect(runButton, &QPushButton::clicked, this, &MainWindow::runTask);

    controlLayout->addWidget(spinBoxLabel);
    controlLayout->addWidget(m_spinBox);
    controlLayout->addWidget(runButton);

    controlLayout->setAlignment(Qt::AlignLeft);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(controlGroupBox);
    layout->addWidget(m_solverWidget);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
    resize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::runTask() {
    int separatingCount = m_spinBox->value();

    // Определяем номер задачи (0 - Test, 1 - Main) на основе активной вкладки
    int taskNumber = m_solverWidget->currentIndex();

    Thomas::ResultTask result = m_model->runTask(taskNumber, separatingCount);

    if (taskNumber == 0) { // Вкладка "Test"
        m_solverWidget->getTestTaskWidget()->updateData(result);
    } else { // Вкладка "Main"
        m_solverWidget->getMainTaskWidget()->updateData(result);
    }
}
