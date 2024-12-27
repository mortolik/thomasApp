#include "SolverWidget.h"
#include "MainTaskWidget.h"
#include "TestTaskWidget.h"
#include <QTabWidget>
#include <QVBoxLayout>
namespace Thomas
{

SolverWidget::SolverWidget(SolverModel* model, QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_tabWidget = new QTabWidget(this);
    layout->addWidget(m_tabWidget);

    m_testTaskWidget = new TestTaskWidget(model);
    m_tabWidget->addTab(m_testTaskWidget, "Test");

    m_mainTaskWidget = new MainTaskWidget(model);
    m_tabWidget->addTab(m_mainTaskWidget, "Main");

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
}
