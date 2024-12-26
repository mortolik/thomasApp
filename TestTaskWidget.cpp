#include "TestTaskWidget.h"
#include <QVBoxLayout>
#include <QHeaderView>

TestTaskWidget::TestTaskWidget(SolverModel* model, QWidget *parent)
    : QWidget(parent), m_model(model) {
    // Создаем layout для виджета
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создаем таблицу
    m_table = new QTableWidget(this);
    m_table->setColumnCount(4); // 4 столбца: x_i, u(x_i), v(x_i), |u(x_i) - v(x_i)|
    m_table->setHorizontalHeaderLabels({"x_i", "u(x_i)", "v(x_i)", "|u(x_i) - v(x_i)|"});
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(m_table);

    // Создаем первый график для u и v
    QChart *chartU_V = new QChart();
    chartU_V->setTitle("Графики u и v");
    m_chartViewU_V = new QChartView(chartU_V);
    m_chartViewU_V->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(m_chartViewU_V);

    // Создаем второй график для разности u - v
    QChart *chartDiff = new QChart();
    chartDiff->setTitle("Разность u - v");
    m_chartViewDiff = new QChartView(chartDiff);
    m_chartViewDiff->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(m_chartViewDiff);

    setLayout(layout);
}

void TestTaskWidget::updateData(const ResultTask& result) {
    // Очищаем таблицу и графики перед обновлением
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

    // Заполняем таблицу и серии данными
    for (size_t i = 0; i < result.x_vector.size(); ++i) {
        double x = result.x_vector[i];
        double u = result.u_vector[i];
        double v = result.v_vector[i];
        double diff = std::abs(u - v);

        // Добавляем строку в таблицу
        int row = m_table->rowCount();
        m_table->insertRow(row);
        m_table->setItem(row, 0, new QTableWidgetItem(QString::number(x, 'f', 15)));
        m_table->setItem(row, 1, new QTableWidgetItem(QString::number(u, 'f', 15)));
        m_table->setItem(row, 2, new QTableWidgetItem(QString::number(v, 'f', 15)));
        m_table->setItem(row, 3, new QTableWidgetItem(QString::number(diff, 'f', 15)));

        // Добавляем точки в серии
        seriesU->append(x, u);
        seriesV->append(x, v);
        seriesDiff->append(x, diff);
    }

    // Добавляем серии на первый график
    m_chartViewU_V->chart()->addSeries(seriesU);
    m_chartViewU_V->chart()->addSeries(seriesV);

    // Настраиваем оси для первого графика
    m_chartViewU_V->chart()->createDefaultAxes();
    m_chartViewU_V->chart()->axisX()->setTitleText("x");
    m_chartViewU_V->chart()->axisY()->setTitleText("Значения");

    // Добавляем серию на второй график
    m_chartViewDiff->chart()->addSeries(seriesDiff);

    // Настраиваем оси для второго графика
    m_chartViewDiff->chart()->createDefaultAxes();
    m_chartViewDiff->chart()->axisX()->setTitleText("x");
    m_chartViewDiff->chart()->axisY()->setTitleText("Разность u - v");
}
