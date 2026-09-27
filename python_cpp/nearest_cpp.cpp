#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>
#include <limits>

namespace py = pybind11;

int find_nearest(
    const std::vector<std::vector<double>>& data)
{
    const int FEATURES = 54;

    const std::vector<double>& query = data[0];

    double bestDistance =
        std::numeric_limits<double>::max();

    int bestIndex = -1;

    for (size_t i = 1; i < data.size(); i++) {

        double distance = 0.0;

        for (int j = 0; j < FEATURES; j++) {

            double diff =
                data[i][j] - query[j];

            distance += diff * diff;
        }

        if (distance < bestDistance) {
            bestDistance = distance;
            bestIndex = static_cast<int>(i);
        }
    }

    return bestIndex;
}


// Expose the C++ function to Python
PYBIND11_MODULE(nearest_cpp, module) {

    module.def(
        "find_nearest",
        &find_nearest,
        "Find the nearest data point"
    );
}