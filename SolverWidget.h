#pragma once

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QTabWidget)

namespace Thomas
{
class TestTaskWidget;
class MainTaskWidget;
class SolverModel;

class SolverWidget : public QWidget {
    Q_OBJECT

public:
    explicit SolverWidget(SolverModel* model, QWidget *parent = nullptr);
    TestTaskWidget* getTestTaskWidget() const;
    MainTaskWidget* getMainTaskWidget() const;
    int currentIndex() const;
signals:
    void currentTabChanged(int index);
private:
    QTabWidget* m_tabWidget;
    TestTaskWidget* m_testTaskWidget;
    MainTaskWidget* m_mainTaskWidget;
};
}
