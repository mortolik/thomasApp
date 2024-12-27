#include "MainTaskWidget.h"
#include <QVBoxLayout>
#include <QHeaderView>

MainTaskWidget::MainTaskWidget(SolverModel* model, QWidget *parent)
    : QWidget(parent), m_model(model) {
    // Создаем layout для виджета
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создаем QTabWidget для вкладок
    m_tabWidget = new QTabWidget(this);
    layout->addWidget(m_tabWidget);

    // Создаем QLabel для справки
    m_infoLabel = new QLabel(this);
    layout->addWidget(m_infoLabel);

    // Создаем вкладку "Графики"
    QWidget *graphTab = new QWidget();
    QVBoxLayout *graphLayout = new QVBoxLayout(graphTab);

    // Создаем первый график для V и V2
    QChart *chartV_V2 = new QChart();
    chartV_V2->setTitle("Графики V и V2");
    m_chartViewV_V2 = new QChartView(chartV_V2);
    m_chartViewV_V2->setRenderHint(QPainter::Antialiasing);
    graphLayout->addWidget(m_chartViewV_V2);

    // Создаем второй график для разности V - V2
    QChart *chartDiff = new QChart();
    chartDiff->setTitle("Разность V - V2");
    m_chartViewDiff = new QChartView(chartDiff);
    m_chartViewDiff->setRenderHint(QPainter::Antialiasing);
    graphLayout->addWidget(m_chartViewDiff);

    // Добавляем вкладку "Графики"
    m_tabWidget->addTab(graphTab, "Графики");

    // Создаем вкладку "Таблица"
    QWidget *tableTab = new QWidget();
    QVBoxLayout *tableLayout = new QVBoxLayout(tableTab);

    // Создаем таблицу
    m_table = new QTableWidget(this);
    m_table->setColumnCount(5); // 5 столбцов: № узла, x_i, V(x_i), V2(x_{2i}), V(x_i) - V2(x_{2i})
    m_table->setHorizontalHeaderLabels({"№ узла", "x_i", "V(x_i)", "V2(x_{2i})", "V(x_i) - V2(x_{2i})"});
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableLayout->addWidget(m_table);

    // Добавляем вкладку "Таблица"
    m_tabWidget->addTab(tableTab, "Таблица");

    setLayout(layout);
}

void MainTaskWidget::updateData(const ResultTask& result) {
    // Очищаем таблицу и графики перед обновлением
    m_table->setRowCount(0);
    m_chartViewV_V2->chart()->removeAllSeries();
    m_chartViewDiff->chart()->removeAllSeries();

    // Создаем серии для V и V2
    QLineSeries *seriesV = new QLineSeries();
    seriesV->setName("V(x)");
    QLineSeries *seriesV2 = new QLineSeries();
    seriesV2->setName("V2(x)");

    // Увеличиваем толщину линии для V(x)
    // QPen penV = seriesV->pen();
    // penV.setWidth(3); // Устанавливаем толщину линии (например, 3 пикселя)
    // seriesV->setPen(penV);

    // Создаем серию для разности V - V2
    QLineSeries *seriesDiff = new QLineSeries();
    seriesDiff->setName("V(x) - V2(x)");

    // Заполняем таблицу и серии данными
    for (size_t i = 0; i < result.x_vector.size(); ++i) {
        double x = result.x_vector[i];
        double v = result.v_vector[i];
        double v2 = result.v_double_counting_vector[i * 2]; // V2(x_{2i})
        double diff = result.error_vector[i];

        // Добавляем строку в таблицу
        int row = m_table->rowCount();
        m_table->insertRow(row);
        m_table->setItem(row, 0, new QTableWidgetItem(QString::number(i))); // № узла
        m_table->setItem(row, 1, new QTableWidgetItem(QString::number(x, 'f', 15))); // x_i
        m_table->setItem(row, 2, new QTableWidgetItem(QString::number(v, 'f', 15))); // V(x_i)
        m_table->setItem(row, 3, new QTableWidgetItem(QString::number(v2, 'f', 15))); // V2(x_{2i})
        m_table->setItem(row, 4, new QTableWidgetItem(QString::number(diff, 'f', 15))); // V(x_i) - V2(x_{2i})

        // Добавляем точки в серии
        seriesV->append(x, v);
        seriesV2->append(x, v2);
        seriesDiff->append(x, diff);
    }

    // Добавляем серии на первый график
    m_chartViewV_V2->chart()->addSeries(seriesV);
    m_chartViewV_V2->chart()->addSeries(seriesV2);

    // Настраиваем оси для первого графика
    m_chartViewV_V2->chart()->createDefaultAxes();
    m_chartViewV_V2->chart()->axisX()->setTitleText("x");
    m_chartViewV_V2->chart()->axisY()->setTitleText("Значения");

    // Добавляем серию на второй график
    m_chartViewDiff->chart()->addSeries(seriesDiff);

    // Настраиваем оси для второго графика
    m_chartViewDiff->chart()->createDefaultAxes();
    m_chartViewDiff->chart()->axisX()->setTitleText("x");
    m_chartViewDiff->chart()->axisY()->setTitleText("Разность V - V2");
    // Обновляем справку
    updateInfoLabel(result);
}

void MainTaskWidget::updateInfoLabel(const ResultTask& result) {
    // Формируем текст справки
    QString info;
    info += QString("Для решения задачи использована равномерная сетка с числом разбиений n = %1.\n").arg(result.x_vector.size() - 1);
    info += "Задача должна быть решена с погрешностью не более ε = 0.5⋅10⁻⁶.\n";
    info += QString("Задача решена с погрешностью ε₁ = %1.\n").arg(result.max_error);
    info += QString("Максимальное отклонение численных решений наблюдается в точке x = %1.\n").arg(result.max_error_x);

    // Устанавливаем текст в QLabel
    m_infoLabel->setText(info);
}
