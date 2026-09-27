import csv
import time

FILE = "data/covtype.data"

print("Loading dataset...")

data = []

with open(FILE, "r") as file:
    reader = csv.reader(file)

    for row in reader:
        # First 54 columns are features.
        # Last column is the cover-type label.
        features = [float(x) for x in row[:54]]
        data.append(features)

print("Loaded", len(data), "data points")

# Use the first location as our query.
query = data[0]

start = time.perf_counter()

best_distance = float("inf")
best_index = -1

# Start at 1 so we don't compare the query with itself.
for i in range(1, len(data)):

    distance = 0.0

    for j in range(54):
        diff = data[i][j] - query[j]
        distance += diff * diff

    if distance < best_distance:
        best_distance = distance
        best_index = i

end = time.perf_counter()

print("Closest location:", best_index)
print("Distance:", best_distance)
print("Computation time:", end - start, "seconds")