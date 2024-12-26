#include "TestTaskWidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>

TestTaskWidget::TestTaskWidget(SolverModel* model, QWidget *parent)
    : QWidget(parent), m_model(model) {
    // Создаем таблицу
    m_table = new QTableWidget(this);
    m_table->setColumnCount(4); // 4 столбца: x_i, u(x_i), v(x_i), |u(x_i) - v(x_i)|
    m_table->setHorizontalHeaderLabels({"x_i", "u(x_i)", "v(x_i)", "|u(x_i) - v(x_i)|"});
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Настраиваем layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_table);
    setLayout(layout);
}

void TestTaskWidget::updateTable(const ResultTask& result) {
    // Очищаем таблицу перед обновлением
    m_table->setRowCount(0);

    // Заполняем таблицу данными
    for (size_t i = 0; i < result.x_vector.size(); ++i) {
        int row = m_table->rowCount();
        m_table->insertRow(row);

        // x_i
        m_table->setItem(row, 0, new QTableWidgetItem(QString::number(result.x_vector[i])));

        // u(x_i)
        m_table->setItem(row, 1, new QTableWidgetItem(QString::number(result.u_vector[i])));

        // v(x_i)
        m_table->setItem(row, 2, new QTableWidgetItem(QString::number(result.v_vector[i])));

        // |u(x_i) - v(x_i)|
        double error = std::abs(result.u_vector[i] - result.v_vector[i]);
        m_table->setItem(row, 3, new QTableWidgetItem(QString::number(error)));
    }
}
