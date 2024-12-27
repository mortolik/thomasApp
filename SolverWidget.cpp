#include "SolverWidget.h"
#include <QVBoxLayout>

SolverWidget::SolverWidget(SolverModel* model, QWidget *parent)
    : QWidget(parent) {
    // Создаем layout для виджета
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создаем QTabWidget для вкладок
    m_tabWidget = new QTabWidget(this);
    layout->addWidget(m_tabWidget);

    // Создаем вкладку "Test" с TestTaskWidget
    m_testTaskWidget = new TestTaskWidget(model);
    m_tabWidget->addTab(m_testTaskWidget, "Test");

    // Создаем вкладку "Main" с MainTaskWidget
    m_mainTaskWidget = new MainTaskWidget(model);
    m_tabWidget->addTab(m_mainTaskWidget, "Main");

    // Подключаем сигнал переключения вкладок
    connect(m_tabWidget, &QTabWidget::currentChanged, this, &SolverWidget::currentTabChanged);

    setLayout(layout);
}

TestTaskWidget* SolverWidget::getTestTaskWidget() const {
    return m_testTaskWidget;
}

MainTaskWidget* SolverWidget::getMainTaskWidget() const {
    return m_mainTaskWidget;
}

int SolverWidget::currentIndex() const {
    return m_tabWidget->currentIndex();
}
