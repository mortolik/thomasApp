#ifndef MAINTASKWIDGET_H
#define MAINTASKWIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QTableWidget>
#include <QTabWidget>
#include "SolverModel.h"

QT_CHARTS_USE_NAMESPACE

    class MainTaskWidget : public QWidget {
    Q_OBJECT

public:
    explicit MainTaskWidget(SolverModel* model, QWidget *parent = nullptr);
    void updateData(const ResultTask& result);

private:
    SolverModel* m_model;
    QTabWidget* m_tabWidget;
    QTableWidget* m_table;
    QChartView* m_chartViewV_V2;    // График для V и V2
    QChartView* m_chartViewDiff;    // График для разности V - V2
};

#endif // MAINTASKWIDGET_H