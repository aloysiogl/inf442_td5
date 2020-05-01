#include <cmath>

#include "point.hpp"
#include "cloud.hpp"
#include "radial.hpp"

radial::radial(cloud *data_, double bandwidth_):kernel(data_)
{
    bandwidth = bandwidth_;
}

double radial::density(point &p) {
    double sum = 0;

    for (int i = 0; i < data->get_n(); ++i){
        double dist = p.dist(data->get_point(i));
        double dist2 = dist*dist;
        sum+=profile(dist2/(bandwidth*bandwidth));
    }

    double c = 1/volume();
    double bandD = pow(bandwidth, p.get_dim());
    double n = (double) data->get_n();

    return c/(n*bandD)*sum;
}