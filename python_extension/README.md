## Project 3 – Python Performance Extension

### Overview

This project compares the performance of:

- A **pure Python** implementation of basic statistics on large numeric datasets.
- A **C extension module** using the CPython C API that performs the same computation more efficiently.

The goal is to show a clear performance improvement from moving heavy numeric loops into C.

### Files

- `stats_pure.py` – Pure Python implementation of:
  - `compute_statistics(data)` that returns `(mean, variance, std_dev)`.
- `stats_module.c` – C extension implementing the same computation.
- `setup.py` – Build script for the `stats_c` extension module.
- `benchmark.py` – Script that:
  - Generates large lists of random numbers.
  - Measures and compares performance of `stats_pure` vs `stats_c`.

### Building the C extension (on Python 3)

From the `python_extension` directory:

```bash
cd python_extension
python3 setup.py build
python3 setup.py install --user
```

Depending on your environment, you may instead use:

```bash
python -m pip install .
```

After installation, you should be able to import `stats_c` from Python:

```bash
python3 -c "import stats_c; print('stats_c imported OK')"
```

### Running the benchmark

From inside `python_extension`:

```bash
python3 benchmark.py
```

Expected behavior:

- The script prints a formatted table like:

  - Data sizes (e.g. `100,000`, `500,000`, `1,000,000`, `5,000,000` elements).
  - Time in milliseconds for:
    - Pure Python (`stats_pure.compute_statistics`).
    - C extension (`stats_c.compute_statistics`).
  - Calculated **speedup** factor and **percentage improvement**.

- It also asserts that the numerical results (mean, variance, standard deviation) from Python and C match closely for correctness.

### What to record for the deliverables

- **Python program**:
  - `stats_pure.py` (core algorithm in pure Python).
- **C extension module**:
  - `stats_module.c` plus `setup.py`.
- **Benchmark results**:
  - Save the console output of `python3 benchmark.py` (e.g. copy into a text file `benchmark_results.txt`).
  - Highlight one or two representative rows showing clear speedup.

### Performance explanation (for your report)

In your short explanation:

- Describe what the computation does:
  - Mean, variance, and standard deviation over large lists of floating-point numbers.
- Explain why the **C extension is faster**, for example:
  - C loops operate on raw numeric values without Python’s per-element object overhead.
  - Fewer Python bytecode instructions and function calls.
  - Less frequent memory allocation and reference counting in the inner loop.
- Use your benchmark numbers to support the explanation:
  - Mention approximate timings for one or two data sizes.
  - Report the speedup factor (e.g. “around 5× faster”) and improvement percentage.
- Conclude by noting that heavy numeric work benefits from moving hot loops into native code, especially when pure Python uses explicit loops instead of vectorized libraries.

