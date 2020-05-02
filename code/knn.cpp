#include "point.hpp"
#include "cloud.hpp"
#include "kernel.hpp"
#include "knn.hpp"
#include <vector>
#include <algorithm>

knn::knn(cloud *data_, int k_, double V_):kernel(data_) {
    k = k_;
    V = V_;
}

double knn::density(point &p) {
    // Getting dk
    std::vector<int> kpoints;

    for(int i = 0; i < data->get_n(); ++i){
        if (kpoints.size() < k)
            kpoints.push_back(i);
        else {
            std::sort(kpoints.begin(), kpoints.end(), [&](int const& a, int const& b){
                return p.dist(data->get_point(a)) > p.dist(data->get_point(b));
            });
            if (p.dist(data->get_point(i)) < p.dist(data->get_point(kpoints[0])))
                kpoints[0] = i;
        }
    }
    std::sort(kpoints.begin(), kpoints.end(), [&](int const & a, int const & b){
        return p.dist(data->get_point(a)) > p.dist(data->get_point(b));
    });

    double dk = p.dist(data->get_point(kpoints[0]));

    // Return value
    double den = 2 * ((double) data->get_n()) * dk * V;

    return ((double) k)/den;
}