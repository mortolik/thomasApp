#include "SolverModel.h"
#include <cmath>
#include <algorithm>

#define PI 3.14159265

const double mu1 = 0., mu2 = 0., alpha1 = 0., beta1 = mu1, v0 = mu1, vn = mu2;
double a = 0., b = 1., h;
const double ksi = 0.5; // точка разрыва

SolverModel::SolverModel(QObject* parent)
    : QObject(parent) {}

// Реализация функции u1
double SolverModel::u1(double x) {
    const double c1 = 0.06393352077;
    const double c2 = -0.06393352077;
    return (c1 * exp(2 * x / 3) + c2 * exp(-2 * x / 3));
}

// Реализация функции u2
double SolverModel::u2(double x) {
    const double c1_hat = -0.1014378994;
    const double c2_hat = -1.850734449;
    return (c1_hat * exp(2 * x) + c2_hat * exp(-2 * x) + 1);
}

// Реализация метода UCurrent
double SolverModel::UCurrent(double x) {
    return (x < ksi) ? u1(x) : u2(x);
}

// Реализация метода XCurrent
double SolverModel::XCurrent(double i) {
    return a + i * h;
}

// Реализация метода ACapitalCurrent
double SolverModel::ACapitalCurrent(double a_current) {
    return a_current / (h * h);
}

// Реализация метода CCapitalCurrent
double SolverModel::CCapitalCurrent(double a_current, double a_next, double d_current) {
    return (a_current + a_next) / (h * h) + d_current;
}

// Реализация метода BCapitalCurrent
double SolverModel::BCapitalCurrent(double a_next) {
    return a_next / (h * h);
}

// Реализация метода AlphaNext
double SolverModel::AlphaNext(double alpha_current, double a_capital_current_value, double b_capital_current_value, double c_capital_current_value) {
    return b_capital_current_value / (c_capital_current_value - a_capital_current_value * alpha_current);
}

// Реализация метода BetaNext
double SolverModel::BetaNext(double alpha_current, double phi_current, double beta_current, double a_capital_current_value, double b_capital_current_value, double c_capital_current_value) {
    return (phi_current + a_capital_current_value * beta_current) / (c_capital_current_value - a_capital_current_value * alpha_current);
}

// Реализация метода VCurrent
double SolverModel::VCurrent(double v_next, double alpha_next, double beta_next, int i, std::vector<double> x_vector) {
    return (alpha_next * v_next + beta_next);
}

// Реализация метода PhiCurrentTest
double SolverModel::PhiCurrentTest(double x_previous, double x_next) {
    double result = 0.;
    if (ksi >= x_next) {
        result = 0;
    } else if (ksi <= x_previous) {
        result = 1;
    } else {
        result = (1 / h) * (((0) * (x_previous - h / 2) - (0) * (0.5)) + (x_previous + h / 2 - 0.5));
    }
    return result;
}

// Реализация метода DCurrentTest
double SolverModel::DCurrentTest(double x_previous, double x_next) {
    double result = 0.;
    if (ksi >= x_previous) {
        result = 1.;
    } else if (ksi < x_previous) {
        result = 1;
    } else {
        result = 1.;
    }
    return result;
}

// Реализация метода ACurrentTest
double SolverModel::ACurrentTest(double x_previous, double x_current, double h) {
    double result = 0.;
    if (ksi >= x_current) {
        result = 2.25;
    } else if (ksi < x_current) {
        result = 0.25;
    } else {
        result = pow((4 * 0.5 - 4 * x_previous) / (9 * h) + (4 * x_current - 4 * 0.5) / h, -1);
    }
    return result;
}

// Реализация метода PhiCurrentMain
double SolverModel::PhiCurrentMain(double x_previous, double x_next) {
    double result = 0;
    if (ksi <= x_previous) {
        result = 1.;
    } else if (ksi >= x_next) {
        result = ((cos(PI * (x_previous)) + cos(PI * (x_next)))) / 2;
    } else {
        result = ((cos(PI * (x_previous)) + cos(PI * (0.5)))) / 2 + (1 / h) * (x_next - 0.5);
    }
    return result;
}

// Реализация метода DCurrentMain
double SolverModel::DCurrentMain(double x_previous, double x_next) {
    double result = 0.;
    if (ksi >= x_next) {
        result = ((exp(0.5 - (x_previous)) + exp(0.5 - (x_next)))) / 2;
    } else if (ksi <= x_previous) {
        result = ((exp(((x_previous)-0.5)) + exp(((x_previous)-0.5)))) / 2;
    } else {
        result = ((exp((1 / 2 - 1 / 2)) + exp((0.5 - x_previous)))) / 2 + ((exp(x_next - 1 / 2) + exp(0.5 - 0.5))) / 2;
    }
    return result;
}

// Реализация метода ACurrentMain
double SolverModel::ACurrentMain(double x_previous, double x_current) {
    double result = 0.;
    if (ksi >= x_current) {
        result = ((x_previous + 1) * (x_previous + 1) + (x_current + 1) * (x_current + 1)) / 2;
    } else if (ksi <= x_previous) {
        result = ((((x_previous) * (x_previous)) + ((x_current) * (x_current))) / 2);
    } else {
        result = 2 / (pow((x_previous + 1), -2) + pow((0.5 + 1), -2) + pow(0.5, -2) + pow(x_current, -2));
    }
    return result;
}

// Реализация метода runTask
ResultTask SolverModel::runTask(int task, int separatingCount) {
    ResultTask result;
    h = (b - a) / separatingCount;

    if (task == 1) {
        taskCalculation(separatingCount * 2, result, false);
        result.v_double_counting_vector = result.v_vector;
        taskCalculation(separatingCount, result, false);
        errorCalculation(separatingCount, result, false);
    } else {
        taskCalculation(separatingCount, result, true);
        exactSolutionCalculation(separatingCount, result);
        errorCalculation(separatingCount, result, true);
    }

    return result;
}

// Реализация метода taskCalculation
void SolverModel::taskCalculation(int separatingCount, ResultTask& result, bool isTestTask) {
    std::vector<double> v_vector = {vn};
    std::vector<double> alpha_vector = {alpha1};
    std::vector<double> beta_vector = {beta1};
    std::vector<double> a_capital_vector;
    std::vector<double> b_capital_vector;
    std::vector<double> c_capital_vector;
    std::vector<double> a_vector;
    std::vector<double> phi_vector;
    std::vector<double> d_vector;

    std::vector<double> x_vector = { XCurrent(0) };
    for (int i = 1; i <= separatingCount; i++) {
        double x_previous = XCurrent(i - 1.),
            x_current = XCurrent(i),
            x_half_previous = XCurrent(i - 0.5),
            x_half_next = XCurrent(i + 0.5);
        x_vector.push_back(x_current);

        a_vector.push_back(isTestTask ? ACurrentTest(x_previous, x_current, h) : ACurrentMain(x_previous, x_current));
        phi_vector.push_back(isTestTask ? PhiCurrentTest(x_half_previous, x_half_next) : PhiCurrentMain(x_half_previous, x_half_next));
        d_vector.push_back(isTestTask ? DCurrentTest(x_half_previous, x_half_next) : DCurrentMain(x_half_previous, x_half_next));
    }

    phi_vector.pop_back();
    d_vector.pop_back();

    for (int i = 0; i < separatingCount - 1; i++) {
        a_capital_vector.push_back(ACapitalCurrent(a_vector[i]));
        c_capital_vector.push_back(CCapitalCurrent(a_vector[i], a_vector[i + 1], d_vector[i]));
        b_capital_vector.push_back(BCapitalCurrent(a_vector[i + 1]));

        beta_vector.push_back(BetaNext(alpha_vector[i], phi_vector[i], beta_vector[i], a_capital_vector[i], b_capital_vector[i], c_capital_vector[i]));
        alpha_vector.push_back(AlphaNext(alpha_vector[i], a_capital_vector[i], b_capital_vector[i], c_capital_vector[i]));
    }

    for (int i = separatingCount - 1; i >= 0; i--) {
        v_vector.push_back(VCurrent(v_vector[separatingCount - 1 - i], alpha_vector[i], beta_vector[i], i, result.x_vector));
    }

    std::reverse(v_vector.begin(), v_vector.end());
    result.v_vector = v_vector;
    result.x_vector = x_vector;
}

// Реализация метода exactSolutionCalculation
void SolverModel::exactSolutionCalculation(int separatingCount, ResultTask& result) {
    result.u_vector.clear();
    for (int i = 0; i <= separatingCount; i++) {
        result.u_vector.push_back(UCurrent(XCurrent(i)));
    }
}

// Реализация метода errorCalculation
void SolverModel::errorCalculation(int elementQuantity, ResultTask& result, bool isTestTask) {
    result.max_error = 0.;
    result.error_vector.clear();
    for (int i = 0; i <= elementQuantity; i++) {
        double error = isTestTask ? std::abs(result.u_vector[i] - result.v_vector[i]) : std::abs(result.v_vector[i] - result.v_double_counting_vector[i * 2]);
        result.error_vector.push_back(error);
        if (result.max_error < error) {
            result.max_error = error;
            result.max_error_x = XCurrent(i);
        }
    }
}
