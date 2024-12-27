#include "MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Создаем модель и виджет
    m_model = new SolverModel(this);
    m_solverWidget = new SolverWidget(m_model, this);

    // Создаем группу для кнопки и спинбокса
    QGroupBox *controlGroupBox = new QGroupBox("Управление", this);
    QHBoxLayout *controlLayout = new QHBoxLayout(controlGroupBox);

    // Создаем спинбокс для ввода количества узлов
    QLabel *spinBoxLabel = new QLabel("Количество узлов:", controlGroupBox);
    m_spinBox = new QSpinBox(controlGroupBox);
    m_spinBox->setMinimumWidth(60);
    m_spinBox->setMinimum(0); // Минимальное количество узлов
    m_spinBox->setMaximum(10000); // Максимальное количество узлов
    m_spinBox->setValue(1000); // Значение по умолчанию

    // Создаем кнопку для запуска задачи
    QPushButton *runButton = new QPushButton("Run Task", controlGroupBox);
    connect(runButton, &QPushButton::clicked, this, &MainWindow::runTask);

    // Добавляем спинбокс и кнопку в layout группы
    controlLayout->addWidget(spinBoxLabel);
    controlLayout->addWidget(m_spinBox);
    controlLayout->addWidget(runButton);

    // Выравниваем элементы по левой стороне
    controlLayout->setAlignment(Qt::AlignLeft);

    // Настраиваем layout главного окна
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(controlGroupBox); // Добавляем группу
    layout->addWidget(m_solverWidget);
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
