#include <iostream>
#include <limits>
#include <cmath>

const double maxdiff = 1e-10;
bool isEqual(double a, double b) {
    return (std::abs(a - b) < maxdiff);
}

double a, b;
double f(double x) {
    if (x < a || isEqual(x, a)) {       // x <= a
        return std::abs(x);
    }
    else if (x < b) {                   // a < x < b
        return std::abs(x) + std::cos(x);
    }
    else {                              // x >= b
        return std::tan(x);
    }
}

#define Infinity std::numeric_limits<double>::infinity()
int main() {
    double xStart, xEnd, dx;
    std::cout << "Enter A, B, xStart, xEnd, dx: ";
    std::cin >> a >> b >> xStart >> xEnd >> dx;

    double max = -Infinity, min = Infinity;
    for (double x = xStart; x < xEnd || isEqual(x, xEnd); x += dx) {
        double val = f(x);
        if (val < min) min = val;
        if (val > max) max = val;

        std::cout << "f(" << x << ") = " << val << std::endl;
    }

    std::cout << "Min: " << min << std::endl << "Max: " << max << std::endl;

    return 0;
}