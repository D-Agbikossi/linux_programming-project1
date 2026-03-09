import time
import random
import math
import sys

def compute_statistics(data):
    """Compute mean, variance, and standard deviation of large dataset"""
    n = len(data)
    if n == 0:
        return 0, 0, 0
    
    # Calculate mean
    total = 0
    for i in range(n):
        total += data[i]
    mean = total / n
    
    # Calculate variance
    variance = 0
    for i in range(n):
        variance += (data[i] - mean) ** 2
    variance /= n
    
    # Calculate standard deviation
    std_dev = math.sqrt(variance)
    
    return mean, variance, std_dev

def main():
    # Generate large dataset
    sizes = [100000, 500000, 1000000, 5000000]
    
    print("Pure Python Performance Test")
    print("-" * 50)
    
    for size in sizes:
        print(f"\nTesting with {size:,} elements:")
        
        # Generate random data
        data = [random.random() * 1000 for _ in range(size)]
        
        # Time the computation
        start_time = time.time()
        mean, var, std = compute_statistics(data)
        end_time = time.time()
        
        print(f"  Mean: {mean:.4f}")
        print(f"  Variance: {var:.4f}")
        print(f"  Std Dev: {std:.4f}")
        print(f"  Time: {(end_time - start_time)*1000:.2f} ms")
        
        sys.stdout.flush()

if __name__ == "__main__":
    main()
    