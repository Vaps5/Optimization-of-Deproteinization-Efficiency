/*
Finding the maximums of the function 
f(x1,x2,x3) = a0 + a1x1 + a2x2 + a3x3 + a4 * x1 * x2 + a5 * x1 *x3 + a6 * x2 * x3
by exhaustive search

By Vaps
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

// Coefficients
double alpha[] = {
    27.5579, -78.6723, 1.37064, 84.5722, 0.398334, 18.267, -1.19521
};


//     Function f(x1,x2,x3) = a0 + a1x1 + a2x2 + a3x3 + a4 * x1 * x2 + a5 * x1 *x3 + a6 * x2 * x3
double f(double x1, double x2, double x3) {
    return alpha[0] + alpha[1]*x1 + alpha[2]*x2 + alpha[3]*x3 +
           alpha[4]*x1*x2 + alpha[5]*x1*x3 + alpha[6]*x2*x3;
}

int main() {
    pair<double, double> intervals[3] = {
        {0.4, 0.8}, {0.8, 1.0}, {1.0, 1.4}
    };

    for (int idx = 0; idx < 3; ++idx) {
        // Optimum values
        double x1_opt = 0, x2_opt = 0, x3_opt = 0, f_max = -10;
        for (double x1 = intervals[idx].first; x1 <= intervals[idx].second; x1 += 0.01)
        // x2 = Temperature is in range [80, 110]
            for (double x2 = 80; x2 <= 110; x2 += 0.01)
            // x3 = Time in hours is in range [0,9,1.3]
                for (double x3 = 0.9; x3 <= 1.3; x3 += 0.01) {
                    double val = f(x1, x2, x3);
                    if (val > f_max) {
                        f_max = val;
                        x1_opt = x1;
                        x2_opt = x2;
                        x3_opt = x3;
                    }
                }
        cout << "Interval [" << intervals[idx].first << ", " << intervals[idx].second << "]\n";
        cout << "  Optimum Efficiency:  " << min(f_max, 100.0) << " %\n";
        cout << "  Optimum Molarity:            " << x1_opt << " M\n";
        cout << "  Optimum Temperature:          " << x2_opt << " °C\n";
        cout << "  Optimum Time:               " << x3_opt * 60 << " minutes\n\n";
    }

    return 0;
}
