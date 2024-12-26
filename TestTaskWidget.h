#ifndef TESTTASKWIDGET_H
#define TESTTASKWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "SolverModel.h"

class TestTaskWidget : public QWidget {
    Q_OBJECT
public:
    explicit TestTaskWidget(SolverModel* model, QWidget *parent = nullptr);
    void updateTable(const ResultTask& result);

private:
    SolverModel* m_model;
    QTableWidget* m_table;
};

#endif // TESTTASKWIDGET_H
