## Project 1 – Investigating a Suspicious Binary

### Overview

This project simulates a suspicious binary called `data_sync` and analyses it **without executing it** using standard ELF inspection tools.

The C program (`data_sync.c`) behaves like a simple directory/file synchronization tool:

- Reads entries from a source directory.
- Copies file contents from source to destination.
- Logs synchronization events to a log file.

### Files

- `data_sync.c` – C source code implementing the simulated `data_sync` tool.
- `data_sync` – Compiled ELF binary (generated on Linux).
- `data_sync_objdump.txt` – Saved output from `objdump`.
- `data_sync_nm.txt` – Saved output from `nm`.
- `data_sync_nm_dynamic.txt` – Saved output from `nm -D`.

### Compilation

From the project root (where the `binary_analysis` folder lives), run:

```bash
cd binary_analysis
gcc -Wall -Wextra -O2 -o data_sync data_sync.c
```

This produces an ELF executable named `data_sync`.

### Static analysis commands

Run the following commands and save their outputs to text files for the report:

- **Basic ELF header, sections, and disassembly**

```bash
objdump -f -h -d ./data_sync > data_sync_objdump.txt
```

- **All symbols (including local)**

```bash
nm ./data_sync > data_sync_nm.txt
```

- **Imported (dynamic) symbols**

```bash
nm -D ./data_sync > data_sync_nm_dynamic.txt
```

Optional (for string evidence in your report):

```bash
strings ./data_sync | less
```

### What to identify in the outputs

- **Entry point**  
  - In `data_sync_objdump.txt`, look near the top (output of `objdump -f`) for `start address 0x...`.  
  - Record that address as the **entry point** of the program.

- **Imported library functions** (from `nm -D`)  
  - Look for standard library calls such as:
    - `opendir`, `readdir`, `closedir`
    - `open`, `read`, `write`, `close`
    - `fopen`, `fprintf`, `fclose`, `perror`
    - `time`, `ctime`
  - These indicate that the binary performs directory traversal, file I/O, and logging with timestamps.

- **Sections inside the ELF** (from `objdump -h`)  
  - Identify key sections such as:
    - `.text` – executable code.
    - `.data` – initialized global data.
    - `.bss` – uninitialized global data.
    - `.rodata` – read‑only data (e.g. constant strings).
    - `.plt`, `.got` – dynamic linking / procedure linkage.
    - `.eh_frame` and related sections – exception/unwind info.
  - Note their sizes and general roles in your report.

### Forensic report guidance (1–2 pages)

Use the saved command outputs to write a short report. Suggested structure:

- **Introduction**
  - Scenario: unknown `data_sync` binary found on a server.
  - Goal: infer behavior only via ELF/static inspection.

- **Methodology**
  - List and briefly explain commands used:
    - `objdump -f -h -d data_sync`
    - `nm data_sync`
    - `nm -D data_sync`
    - (Optionally) `strings data_sync`

- **Findings**
  - **Entry point**: give the address reported by `objdump`.
  - **Sections**: describe the main sections and what they typically contain.
  - **Imported functions**: list the key libc functions and explain what each family suggests (directory scanning, file copying, logging, time handling).
  - Mention any recognizable strings (e.g., log messages) if you used `strings`.

- **Interpretation**
  - Based on the imported functions and strings, argue that the program:
    - Traverses a directory.
    - Copies file contents from one location to another.
    - Logs synchronization events with timestamps to a log file.
  - Emphasize that these conclusions are drawn *without* executing the binary.

- **Conclusion**
  - Summarize what the `data_sync` binary most likely does and how ELF inspection supports this conclusion.

