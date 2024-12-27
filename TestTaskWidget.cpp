#include <QLabel>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTableWidget>

#include "TestTaskWidget.h"
#include "SolverModel.h"

namespace Thomas
{
TestTaskWidget::TestTaskWidget(SolverModel* model, QWidget *parent)
    : QWidget(parent), m_model(model) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_infoLabel = new QLabel(this);
    layout->addWidget(m_infoLabel);

    m_tabWidget = new QTabWidget(this);
    layout->addWidget(m_tabWidget);

    QWidget *graphTab = new QWidget();
    QVBoxLayout *graphLayout = new QVBoxLayout(graphTab);

    // Создаем первый график для u и v
    QChart *chartU_V = new QChart();
    chartU_V->setTitle("Графики u и v");
    m_chartViewU_V = new QChartView(chartU_V);
    m_chartViewU_V->setRenderHint(QPainter::Antialiasing);
    graphLayout->addWidget(m_chartViewU_V);

    // Создаем второй график для разности u - v
    QChart *chartDiff = new QChart();
    chartDiff->setTitle("Разность u - v");
    m_chartViewDiff = new QChartView(chartDiff);
    m_chartViewDiff->setRenderHint(QPainter::Antialiasing);
    graphLayout->addWidget(m_chartViewDiff);

    m_tabWidget->addTab(graphTab, "Графики");

    QWidget *tableTab = new QWidget();
    QVBoxLayout *tableLayout = new QVBoxLayout(tableTab);

    m_table = new QTableWidget(this);
    m_table->setColumnCount(4); // 4 столбца: x_i, u(x_i), v(x_i), |u(x_i) - v(x_i)|
    m_table->setHorizontalHeaderLabels({"x_i", "u(x_i)", "v(x_i)", "|u(x_i) - v(x_i)|"});
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableLayout->addWidget(m_table);

    m_tabWidget->addTab(tableTab, "Таблица");

    setLayout(layout);
}

void TestTaskWidget::updateData(const ResultTask& result) {
    m_table->setRowCount(0);
    m_chartViewU_V->chart()->removeAllSeries();
    m_chartViewDiff->chart()->removeAllSeries();

    // Создаем серии для u и v
    QLineSeries *seriesU = new QLineSeries();
    seriesU->setName("u(x)");
    QLineSeries *seriesV = new QLineSeries();
    seriesV->setName("v(x)");

    // Раскоментировать, когда нужно будет сделать жирнее численное решение, чтобы показать, что оно строится
    // QPen penU = seriesU->pen();
    // penU.setWidth(3);
    // seriesU->setPen(penU);

    // Создаем серию для разности u - v
    QLineSeries *seriesDiff = new QLineSeries();
    seriesDiff->setName("u(x) - v(x)");

    for (size_t i = 0; i < result.x_vector.size(); ++i) {
        double x = result.x_vector[i];
        double u = result.u_vector[i];
        double v = result.v_vector[i];
        double diff = std::abs(u - v);

        int row = m_table->rowCount();
        m_table->insertRow(row);
        m_table->setItem(row, 0, new QTableWidgetItem(QString::number(x, 'f', 15)));
        m_table->setItem(row, 1, new QTableWidgetItem(QString::number(u, 'f', 15)));
        m_table->setItem(row, 2, new QTableWidgetItem(QString::number(v, 'f', 15)));
        m_table->setItem(row, 3, new QTableWidgetItem(QString::number(diff, 'f', 15)));

        seriesU->append(x, u);
        seriesV->append(x, v);
        seriesDiff->append(x, diff);
    }

    m_chartViewU_V->chart()->addSeries(seriesU);
    m_chartViewU_V->chart()->addSeries(seriesV);

    m_chartViewU_V->chart()->createDefaultAxes();
    m_chartViewU_V->chart()->axisX()->setTitleText("x");
    m_chartViewU_V->chart()->axisY()->setTitleText("Значения");

    m_chartViewDiff->chart()->addSeries(seriesDiff);

    m_chartViewDiff->chart()->createDefaultAxes();
    m_chartViewDiff->chart()->axisX()->setTitleText("x");
    m_chartViewDiff->chart()->axisY()->setTitleText("Разность u - v");

    updateInfoLabel(result);
}
void TestTaskWidget::updateInfoLabel(const ResultTask& result) {
    // Формируем текст справки
    QString info;
    info += QString("Для решения задачи использована равномерная сетка с числом разбиений n = %1.\n").arg(result.x_vector.size() - 1);
    info += "Задача должна быть решена с погрешностью не более ε = 0.5⋅10⁻⁶.\n";
    info += QString("Задача решена с погрешностью ε₁ = %1.\n").arg(result.max_error);
    info += QString("Максимальное отклонение аналитического и численного решений наблюдается в точке x = %1.\n").arg(result.max_error_x);

    // Устанавливаем текст в QLabel
    m_infoLabel->setText(info);
}
}
