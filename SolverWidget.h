#ifndef SOLVERWIDGET_H
#define SOLVERWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include "TestTaskWidget.h"
#include "MainTaskWidget.h"
#include "SolverModel.h"

class SolverWidget : public QWidget {
    Q_OBJECT

public:
    explicit SolverWidget(SolverModel* model, QWidget *parent = nullptr);
    TestTaskWidget* getTestTaskWidget() const;
    MainTaskWidget* getMainTaskWidget() const;
    int currentIndex() const; // Возвращает индекс текущей вкладки
signals:
    void currentTabChanged(int index); // Сигнал о переключении вкладки
private:
    QTabWidget* m_tabWidget;
    TestTaskWidget* m_testTaskWidget;
    MainTaskWidget* m_mainTaskWidget;
};

#endif // SOLVERWIDGET_H
