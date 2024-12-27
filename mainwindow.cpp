#include "MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Создаем модель и виджет
    m_model = new SolverModel(this);
    m_solverWidget = new SolverWidget(m_model, this);

    // Создаем кнопку для запуска задачи
    QPushButton *runButton = new QPushButton("Run Task", this);
    connect(runButton, &QPushButton::clicked, this, &MainWindow::runTask);

    // Подключаем обработчик переключения вкладок
    connect(m_solverWidget, &SolverWidget::currentTabChanged, this, &MainWindow::onTabChanged);

    // Настраиваем layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(m_solverWidget);
    layout->addWidget(runButton);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::runTask() {
    // Запускаем задачу для активной вкладки
    onTabChanged(m_solverWidget->currentIndex());
}

void MainWindow::onTabChanged(int index) {
    int taskNumber = index; // 0 - Test, 1 - Main
    int separatingCount = 1000; // Пример: 100 точек
    ResultTask result = m_model->runTask(taskNumber, separatingCount);

    // Обновляем данные в активной вкладке
    if (index == 0) { // Вкладка "Test"
        m_solverWidget->getTestTaskWidget()->updateData(result);
    } else { // Вкладка "Main"
        m_solverWidget->getMainTaskWidget()->updateData(result);
    }
}
