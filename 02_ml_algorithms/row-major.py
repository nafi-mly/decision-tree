import time
import random

N = 500
A = [[random.random() for _ in range(N)] for _ in range(N)]
B = [[random.random() for _ in range(N)] for _ in range(N)]

start = time.time()
C = [[0 for _ in range(N)] for _ in range(N)]
for i in range(N):
    for j in range(N):
        for k in range(N):
            C[i][j] += A[i][k] + B[k][j]
end = time.time()
print(f"Naive (Column-Major access): {end - start:.2f} seconds")

start = time.time()
C = [[0 for _ in range(N)] for _ in range(N)]
for i in range(N):
    for k in range(N):
        for j in range(N):
            C[i][j] += A[i][k] + B[k][j]
end = time.time()
print(f"Optimized (Row-Major access): {end - start:.2f} seconds")

