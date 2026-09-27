import csv
import time

import nearest_cpp


FILE = "data/covtype.data"

print("Loading dataset...")

data = []

with open(FILE, "r") as file:

    reader = csv.reader(file)

    for row in reader:

        features = [
            float(x) for x in row[:54]
        ]

        data.append(features)


print("Loaded", len(data), "data points")


start = time.perf_counter()

closest = nearest_cpp.find_nearest(data)

end = time.perf_counter()


print("Closest location:", closest)

print(
    "Python -> C++ time:",
    end - start,
    "seconds"
)