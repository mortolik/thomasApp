#pragma once

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QTabWidget)
QT_FORWARD_DECLARE_CLASS(QTableWidget)

using namespace QtCharts;

namespace Thomas
{
class SolverModel;
struct ResultTask;

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
    QChartView* m_chartViewU_V;
    QChartView* m_chartViewDiff;
};
}

