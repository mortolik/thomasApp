#include "MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Создаем модель и виджет
    m_model = new SolverModel(this);
    m_solverWidget = new SolverWidget(m_model, this);

    // Создаем спинбокс для ввода количества узлов
    QHBoxLayout *spinBoxLayout = new QHBoxLayout();
    QLabel *spinBoxLabel = new QLabel("Количество узлов:", this);
    m_spinBox = new QSpinBox(this);
    m_spinBox->setMinimum(10); // Минимальное количество узлов
    m_spinBox->setMaximum(10000); // Максимальное количество узлов
    m_spinBox->setValue(1000); // Значение по умолчанию
    spinBoxLayout->addWidget(spinBoxLabel);
    spinBoxLayout->addWidget(m_spinBox);

    // Создаем кнопку для запуска задачи
    QPushButton *runButton = new QPushButton("Run Task", this);
    connect(runButton, &QPushButton::clicked, this, &MainWindow::runTask);

    // Настраиваем layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(m_solverWidget);
    layout->addLayout(spinBoxLayout); // Добавляем спинбокс
    layout->addWidget(runButton);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::runTask() {
    // Получаем количество узлов из спинбокса
    int separatingCount = m_spinBox->value();

    // Определяем номер задачи (0 - Test, 1 - Main) на основе активной вкладки
    int taskNumber = m_solverWidget->currentIndex();

    // Выполняем задачу
    ResultTask result = m_model->runTask(taskNumber, separatingCount);

    // Обновляем данные в активной вкладке
    if (taskNumber == 0) { // Вкладка "Test"
        m_solverWidget->getTestTaskWidget()->updateData(result);
    } else { // Вкладка "Main"
        m_solverWidget->getMainTaskWidget()->updateData(result);
    }
}
