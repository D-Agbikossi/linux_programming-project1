import time
import random
import stats_c
import stats_pure
import sys

def run_benchmark():
    sizes = [100000, 500000, 1000000, 5000000]
    
    print("=" * 70)
    print("PERFORMANCE COMPARISON: Python vs C Extension")
    print("=" * 70)
    print(f"{'Data Size':<15} {'Python (ms)':<15} {'C Ext (ms)':<15} {'Speedup':<10} {'Improvement':<15}")
    print("-" * 70)
    
    for size in sizes:
        # Generate data once for both tests
        data = [random.random() * 1000 for _ in range(size)]
        
        # Test Python version
        start = time.time()
        py_mean, py_var, py_std = stats_pure.compute_statistics(data)
        py_time = (time.time() - start) * 1000
        
        # Test C extension
        start = time.time()
        c_mean, c_var, c_std = stats_c.compute_statistics(data)
        c_time = (time.time() - start) * 1000
        
        # Calculate speedup
        speedup = py_time / c_time if c_time > 0 else 0
        improvement = ((py_time - c_time) / py_time) * 100 if py_time > 0 else 0
        
        print(f"{size:<15,} {py_time:<15.2f} {c_time:<15.2f} {speedup:<10.2f}x {improvement:<15.1f}%")
        
        # Verify results match
        assert abs(py_mean - c_mean) < 0.0001, "Mean values don't match!"
        assert abs(py_var - c_var) < 0.0001, "Variance values don't match!"
        assert abs(py_std - c_std) < 0.0001, "Std dev values don't match!"
        
        sys.stdout.flush()
    
    print("=" * 70)
    print("Results verified: All calculations match exactly!")

if __name__ == "__main__":
    run_benchmark()
    