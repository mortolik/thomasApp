#ifndef SOLVERMODEL_H
#define SOLVERMODEL_H

#include <QObject>
#include <vector>

struct ResultTask {
    std::vector<double> x_vector;
    std::vector<double> u_vector;
    std::vector<double> v_vector;
    std::vector<double> v_double_counting_vector;
    std::vector<double> error_vector;
    double max_error_x = 0.;
    double max_error = 0.;
};

class SolverModel : public QObject {

public:
    explicit SolverModel(QObject* parent = nullptr);
    ResultTask runTask(int task, int separatingCount);

private:
    void taskCalculation(int separatingCount, ResultTask& result, bool isTestTask);
    void exactSolutionCalculation(int separatingCount, ResultTask& result);
    void errorCalculation(int elementQuantity, ResultTask& result, bool isTestTask);

    // Функции для тестовой задачи
    double PhiCurrentTest(double x_previous, double x_next);
    double DCurrentTest(double x_previous, double x_next);
    double ACurrentTest(double x_previous, double x_current, double h);

    // Функции для основной задачи
    double PhiCurrentMain(double x_previous, double x_next);
    double DCurrentMain(double x_previous, double x_next);
    double ACurrentMain(double x_previous, double x_current);

    // Общие функции
    double ACapitalCurrent(double a_current);
    double CCapitalCurrent(double a_current, double a_next, double d_current);
    double BCapitalCurrent(double a_next);
    double XCurrent(double i);
    double AlphaNext(double alpha_current, double a_capital_current_value, double b_capital_current_value, double c_capital_current_value);
    double BetaNext(double alpha_current, double phi_current, double beta_current, double a_capital_current_value, double b_capital_current_value, double c_capital_current_value);
    double VCurrent(double v_next, double alpha_next, double beta_next, int i, std::vector<double> x_vector);
    double UCurrent(double x);

    // Функции для точного решения
    double u1(double x);
    double u2(double x);
};

#endif // SOLVERMODEL_H
