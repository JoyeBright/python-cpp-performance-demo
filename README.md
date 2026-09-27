# Python vs C++: Performance and Integration

This example compares Python and C++ using the same
nearest-neighbor computation on the Forest Cover Type, https://archive.ics.uci.edu/dataset/31/covertype.

We then expose the C++ implementation to Python using pybind11.

## Dataset

It is available under:

data/covtype.data

## Experiment

Given one data point, find the most similar point in the dataset.

For every point we compute:

distance = sum((x[j] - query[j])^2)

With 581,012 observations and 54 features, one search requires
approximately 31 million feature comparisons.

## 1. Python

Run:

python3 python/nearest.py

Record the computation time.

## 2. C++

Compile:

clang++ -O3 -std=c++17 cpp/nearest.cpp -o nearest

Run:

./nearest

Record the computation time.

## 3. Python + C++

Install the dependencies:

python3 -m pip install -r requirements.txt

Compile the Python extension:

clang++ -O3 -Wall -shared -std=c++17 \
-undefined dynamic_lookup \
$(python3 -m pybind11 --includes) \
python_cpp/nearest_cpp.cpp \
-o python_cpp/nearest_cpp$(python3-config --extension-suffix)

Run:

python3 python_cpp/combined.py