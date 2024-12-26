#include "MainWindow.h"
#include "SolverModel.h"
#include "TestTaskWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Создаем модель
    m_model = new SolverModel(this);

    // Создаем виджет для отображения таблицы
    m_taskWidget = new TestTaskWidget(m_model, this);

    // Создаем кнопку для запуска задачи
    QPushButton* runButton = new QPushButton("Run Task", this);
    connect(runButton, &QPushButton::clicked, this, &MainWindow::runTask);

    // Настраиваем layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->addWidget(m_taskWidget);
    layout->addWidget(runButton);
    centralWidget->setLayout(layout);

    // Устанавливаем центральный виджет
    setCentralWidget(centralWidget);

    // Настройки окна
    setWindowTitle("Thomas Algorithm Solver");
    resize(600, 400);
}

MainWindow::~MainWindow() {
    // Автоматическое удаление объектов, так как они являются дочерними
}

void MainWindow::runTask() {
    // Запускаем задачу и обновляем таблицу
    ResultTask result = m_model->runTask(0, 1000); // Пример: тестовая задача с 100 точками
    m_taskWidget->updateTable(result);
}
