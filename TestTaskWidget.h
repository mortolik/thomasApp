#ifndef TESTTASKWIDGET_H
#define TESTTASKWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include "SolverModel.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

using namespace QtCharts;

class TestTaskWidget : public QWidget {
    Q_OBJECT
public:
    explicit TestTaskWidget(SolverModel* model, QWidget *parent = nullptr);

    void updateData(const ResultTask& result);
    void updateInfoLabel(const ResultTask& result);

private:
    SolverModel* m_model;
    QTabWidget* m_tabWidget;
    QTableWidget* m_table;
    QLabel* m_infoLabel{nullptr};
    QChartView* m_chartViewU_V;    // График для u и v
    QChartView* m_chartViewDiff;   // График для разности u - v
};

#endif // TESTTASKWIDGET_H
