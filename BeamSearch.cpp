/*
Finding the maximum of the function 
f(x1,x2,x3) = a0 + a1x1 + a2x2 + a3x3 + a4 * x1 * x2 + a5 * x1 *x3 + a6 * x2 * x3
by using beam search

By Vaps
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

class Model {
    double alpha[7] = {
        27.5579, -78.6723, 1.37064, 84.5722,
        0.398334, 18.267, -1.19521
    };
public:
// Function f(x1,x2,x3) = a0 + a1x1 + a2x2 + a3x3 + a4 * x1 * x2 + a5 * x1 *x3 + a6 * x2 * x3
// Evaluate Method: returns deproteinization efficiency
    double evaluate(double x1, double x2, double x3) const {
        return alpha[0] + alpha[1]*x1 + alpha[2]*x2 + alpha[3]*x3
             + alpha[4]*x1*x2 + alpha[5]*x1*x3 + alpha[6]*x2*x3;
    }
};

class State {
public:
// fx is the deproteinization prediction based on x1, x2 and x3 values
    double x1, x2, x3, fx;
    // Default constructor with initialization in variables
    State() : x1(0), x2(0), x3(0), fx(-100) {}

    // Parameterized constructor
    State(double x1, double x2, double x3, const Model& model)
        : x1(x1), x2(x2), x3(x3) {
        fx = model.evaluate(x1, x2, x3);
    }

    // Operator < compares the fx value of each object State
    bool operator<(const State& other) const {
        return fx > other.fx;
    }

    // Function for printing values
    void print() const {
        cout << "Efficiency predicted: " << min(fx, 100.0) << " %\n";
        cout << "Molarity:             " << x1 << " M\n";
        cout << "Temperature:          " << x2 << " °C\n";
        cout << "Time:                 " << x3 * 60 << " minutes\n\n";
    }
};

class BeamSearch {
private:
    const Model& model;
    int beamWidth;
    int maxIter;
public:
// Parameterized Constructor
    BeamSearch(const Model& m, int width = 5, int iters = 15)
        : model(m), beamWidth(width), maxIter(iters) {}

    State search(double x1_min, double x1_max) {
        vector<State> beam;

        // We consider the intervals:
        // Molarity [x1_min, x2_max]
        // Temperature [80, 110]
        // Time in hours [0.9, 1.3]

        for (double x1 = x1_min; x1 <= x1_max; x1 += 0.01)
            for (double x2 = 80; x2 <= 110; x2 += 1.0)
                for (double x3 = 0.9; x3 <= 1.3; x3 += 0.01)
                // Emplace_back - function to add an element at the end of the vector, faster than push back
                    beam.emplace_back(x1, x2, x3, model);


        // It sorts by using the operator < defined previously
        sort(beam.begin(), beam.end());

        // Resize function keeps the BeamWidth number of elements in the vector and delete the others
        beam.resize(beamWidth);

        // beam vector has top beamWidth combinations

        for (int iter = 0; iter < maxIter; ++iter) {
            vector<State> next;
            // We iterate over beam vector
            for (const auto& s : beam) {
                // We consider small perturbations and generate new State objects
                for (double dx1 : {-0.01, 0.0, 0.01})
                    for (double dx2 : {-0.5, 0.0, 0.5})
                        for (double dx3 : {-0.01, 0.0, 0.01}) {
                            double nx1 = s.x1 + dx1;
                            double nx2 = s.x2 + dx2;
                            double nx3 = s.x3 + dx3;
                            // We verify restriction limits
                            if (nx1 < x1_min || nx1 > x1_max ||
                                nx2 < 80 || nx2 > 110 ||
                                nx3 < 0.9 || nx3 > 1.3)
                                continue;
                            next.emplace_back(nx1, nx2, nx3, model);
                        }
            }
            sort(next.begin(), next.end());
            auto w = min(beamWidth, (int)next.size());
            next.resize(w);
            beam = next;
        }

        return beam.front();
    }
};

int main() {
    Model model;
    BeamSearch searcher(model);

    // Intervals considering are
    // Low molarity [0.4, 0.8]
    // Medium molarity [0.8, 1.0]
    // High molarity [1.0, 1.4]
    vector<pair<double, double>> intervals = {
        {0.4, 0.8},
        {0.8, 1.0},
        {1.0, 1.4}
    };

    for (const auto& [x1_min, x1_max] : intervals) {
        cout << "Interval [" << x1_min << ", " << x1_max << "]\n";
        State best = searcher.search(x1_min, x1_max);
        best.print();
    }

    return 0;
}
