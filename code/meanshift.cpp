#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "point.cpp"
#include "cloud.cpp"

using std::vector;

double dist2(vector<double>& v1, vector<double>& v2){
    assert(v1.size() == v2.size());
    double sum = 0;

    for (int i = 0; i < v1.size(); ++i)
        sum += (v1[i]-v2[i])*(v1[i]-v2[i]);
    return sum;
}

void updateKnn(vector<vector<int>>& knn, vector<vector<double>>& points, int k, int p, int i){
    if (p == i) return;

    if (knn[p].size() < k)
        knn[p].push_back(i);
    else {
        std::sort(knn[p].begin(), knn[p].end(), [&](int const & a, int const & b){
            return dist2(points[p], points[a]) > dist2(points[p], points[b]);
        });
        if (dist2(points[p], points[i]) < dist2(points[p], points[knn[p][0]]))
            knn[p][0] = i;
    }
    std::sort(knn[p].begin(), knn[p].end(), [&](int const & a, int const & b){
        return dist2(points[p], points[a]) > dist2(points[p], points[b]);
    });
}

vector<vector<double>> calculateAverage(vector<vector<int>>& knn, vector<vector<double>>& points, int d, int k){
    vector<vector<double>> out(points.size(), vector<double>(d, 0));

    for (int i = 0; i < points.size(); ++i){
        for (int dim = 0; dim < d; ++dim){
            for(int j = 0; j < k; ++j){
                out[i][dim] += points[knn[i][j]][dim];
            }
            out[i][dim] /= (double) k;
        }
    }

    return out;
}

int main (int argc, char **argv)
{
    // Reading dimension and k
    int d = std::stoi(argv[1]);
    int k = std::stoi(argv[3]);
    int q = std::stoi(argv[4]);

    // Filling vector of points (reading and setting)
    vector<vector<double>> points;

    std::ifstream input(argv[2]);

    while (input.peek()!=EOF){
        points.push_back(vector<double>(d));
        for (int i = 0; i < d; ++i){
            double read;
            input >> read;
            points[points.size()-1][i] = read;
        }
    }

    points.pop_back();

    // Calculation of results
    for (int i = 0; i < q; ++i){
        double percent = ((double) i)/((double)q) *100;
        std::cout << percent << " %\n";

        // Vectors of Knn
        vector<vector<int>> knn(points.size(), vector<int>(k));

        for (int i = 0; i < points.size(); ++i){
            for (int j = i; j < points.size(); ++j){
                updateKnn(knn, points, k, i, j);
                updateKnn(knn, points, k, j, i);
            }
        }

        // Average
        points = calculateAverage(knn, points, d, k);
    }

    std::cout << "100 %\n";

    std::ofstream output(std::string(argv[2])+"_meanshift");

    for (auto p: points){
        for(auto val: p){
            output << val << " ";
        }
        output << "\n";
    }

    std::cout << "Output with name: " << argv[2] << "_meanshift\n";

    output.close();

	return 0;
}


