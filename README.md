## Linux Programming – Project 1

This repository contains four small, practical projects for a Linux programming course.  
Each project focuses on a different low-level concept: ELF binaries, system calls, Python C extensions, and Unix signals.

The work is intended to be completed and understood **individually**.  
This README gives a high-level overview; each subdirectory has its own detailed `README.md` with exact commands and instructions.

- `binary_analysis/` – Project 1: Investigating a Suspicious Binary (ELF analysis).
- `syscall_monitor/` – Project 2: System Call Monitoring Tool (`strace`).
- `python_extension/` – Project 3: Python Performance C Extension.
- `signal_service/` – Project 4: Signal-Based Server Controller.

All commands below assume a Linux environment (or WSL on Windows) with:

- A C compiler (e.g. `gcc`).
- Standard development tools (`make`, `strace`, `objdump`, `nm`).
- Python 3 with a working C toolchain for building extensions.

---

## Project 1 – Investigating a Suspicious Binary

**Goal:** Analyse an unknown ELF executable (`data_sync`) **without executing it**, and infer its likely behavior.

- Source and analysis live in `binary_analysis/`.
- Main file: `data_sync.c` (simulated file synchronization tool).

Typical workflow (see `binary_analysis/README.md` for full details):

```bash
cd binary_analysis
gcc -Wall -Wextra -O2 -o data_sync data_sync.c
objdump -f -h -d ./data_sync > data_sync_objdump.txt
nm ./data_sync > data_sync_nm.txt
nm -D ./data_sync > data_sync_nm_dynamic.txt
```

Use these outputs to:

- Identify the **entry point**.
- List **imported library functions**.
- Describe important **ELF sections**.
- Write a short forensic report explaining what `data_sync` likely does.

---

## Project 2 – System Call Monitoring Tool

**Goal:** Observe how a small file backup program interacts with the kernel using `strace`.

- Files live in `syscall_monitor/`.
- Main file: `file_backup.c`.

Typical workflow:

```bash
cd syscall_monitor
gcc -Wall -Wextra -O2 -o file_backup file_backup.c
strace -o file_backup_strace.txt ./file_backup
```

From `file_backup_strace.txt`, identify and summarise:

- **File-related system calls** (e.g. `open`, `read`, `write`, `close`).
- **Process-related system calls** (e.g. `execve`, `exit_group`).

The project deliverables include:

- The C source.
- The `strace` output file.
- A short explanation and a system-call summary table.

Full details and a suggested table format are in `syscall_monitor/README.md`.

---

## Project 3 – Python Performance C Extension

**Goal:** Speed up heavy numeric computation in Python by moving core loops into a C extension.

- Files live in `python_extension/`.
- Key files:
  - `stats_pure.py` – pure Python statistics (mean, variance, std dev).
  - `stats_module.c` – CPython C extension implementing the same logic.
  - `setup.py` – build script.
  - `benchmark.py` – performance comparison harness.

Typical workflow:

```bash
cd python_extension
python3 setup.py build
python3 setup.py install --user
python3 benchmark.py
```

The benchmark:

- Computes statistics on large randomly generated datasets.
- Prints a table comparing:
  - Pure Python runtime.
  - C extension runtime.
  - Speedup and percentage improvement.

Deliverables:

- Python program and C extension source.
- Benchmark results.
- A brief performance explanation using your measured numbers.

See `python_extension/README.md` for more guidance.

---

## Project 4 – Signal-Based Server Controller

**Goal:** Implement a simple monitoring service that runs continuously and responds to Unix signals.

- Files live in `signal_service/`.
- Main file: `monitor_service.c`.

The service:

- Prints a status message every 5 seconds.
- Handles the following signals:
  - `SIGINT` – graceful shutdown (`"Monitor Service shutting down safely."`).
  - `SIGUSR1` – status request (`"System status requested by administrator."`).
  - `SIGTERM` – emergency shutdown (`"Emergency shutdown signal received."`).

Typical workflow:

```bash
cd signal_service
gcc -Wall -Wextra -O2 -o monitor_service monitor_service.c
./monitor_service            # terminal 1: run service
kill -SIGUSR1 <pid>          # terminal 2: request status
kill -SIGINT <pid>           # or use Ctrl+C for graceful shutdown
kill -SIGTERM <pid>          # emergency shutdown
```

Deliverables:

- `monitor_service.c` and compilation command.
- Terminal logs or screenshots showing each signal being handled.
- A short explanation of how signal handlers are registered and what each signal does.

Full details are in `signal_service/README.md`.

---

## Notes

- This repository is intended for **learning and assessment**. Make sure you understand every part of the code and analysis before submitting.
- Keep the repository public as required by the assignment instructions.
- For grading, ensure:
  - All source files compile on a standard Linux toolchain.
  - Generated analysis outputs (`objdump`, `nm`, `strace`, benchmark results) are included where requested.
  - Your written reports follow the structures suggested in each project’s README.
