#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <chrono>

using namespace std;

int main() {

    const int FEATURES = 54;

    cout << "Loading dataset..." << endl;

    ifstream file("../data/covtype.data");

    if (!file.is_open()) {
        cerr << "Could not open covtype.data" << endl;
        return 1;
    }

    vector<vector<double>> data;

    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        string value;

        vector<double> row;

        // Read the 54 features
        for (int i = 0; i < FEATURES; i++) {

            getline(ss, value, ',');

            row.push_back(stod(value));
        }

        // We deliberately ignore the final cover-type label.

        data.push_back(row);
    }

    file.close();

    cout << "Loaded " << data.size()
         << " data points" << endl;

    // First location is the query
    const vector<double>& query = data[0];

    auto start =
        chrono::high_resolution_clock::now();

    double bestDistance =
        numeric_limits<double>::max();

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

    auto end =
        chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed =
        end - start;

    cout << "Closest location: "
         << bestIndex << endl;

    cout << "Distance: "
         << bestDistance << endl;

    cout << "Computation time: "
         << elapsed.count()
         << " seconds" << endl;

    return 0;
}