## Project 3 – Python Performance Extension

**Goal:** compare a pure‑Python statistics implementation with an equivalent C extension.

### Install the extension

From the `python_extension` directory:

```bash
cd python_extension
python3 -m pip install . --user
# or:
# python3 setup.py build
# python3 setup.py install --user
```

You should then be able to import `stats_c`:

```bash
python3 -c "import stats_c; print('stats_c imported OK')"
```

### Run the benchmark

```bash
python3 benchmark.py
```

This prints timings for `stats_pure` vs `stats_c` on large datasets so you can see the speedup.

