#include <cmath>
#include <iostream>

#include "point.hpp"
#include "cloud.hpp"
#include "gaussian.hpp"

gaussian::gaussian(cloud *data_, double bandwidth_):radial(data_, bandwidth_) {}

double gaussian::volume() {
    double d = (double) point::get_dim();
    return pow(2*M_PI, d/2);
}

double gaussian::profile(double t) {
    return exp(((-t)/2));
}

void gaussian::guess_bandwidth() {
    double num = 1.06*data->standard_deviation();
    double den = pow(data->get_n(), 1.0/5.0);

    bandwidth = num/den;
}
