#include <cmath>

#include "point.hpp"
#include "flat.hpp"

flat::flat(cloud *data_, double bandwidth_):radial(data_, bandwidth_) {}

double flat::volume() {
    double d = (double) point::get_dim();
    double num = pow(M_PI, d/2);
    double den = tgamma(d/2 + 1);

    return num/den;
}

double flat::profile(double t) {
    if (t < 1) return 1;
    return 0;
}