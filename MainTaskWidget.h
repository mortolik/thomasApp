#pragma once

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QTabWidget)
QT_FORWARD_DECLARE_CLASS(QTableWidget)

QT_CHARTS_USE_NAMESPACE
namespace Thomas
{
class SolverModel;
struct ResultTask;

class MainTaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainTaskWidget(SolverModel* model, QWidget *parent = nullptr);
    void updateData(const ResultTask& result);
    void updateInfoLabel(const ResultTask& result);

private:
    SolverModel* m_model;
    QTabWidget* m_tabWidget;
    QTableWidget* m_table;
    QLabel* m_infoLabel{nullptr};
    QChartView* m_chartViewV_V2;    // График для V и V2
    QChartView* m_chartViewDiff;    // График для разности V - V2
};
}
