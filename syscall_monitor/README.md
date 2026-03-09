## Project 2 – System Call Monitoring Tool

### Overview

This project demonstrates how a file backup program interacts with the operating system by tracing its system calls using `strace`.

The C program (`file_backup.c`) performs:

- **File creation** (`data.txt`)
- **Writing logs** (`backup.log`)
- **Reading files** and creating a backup copy (`data.backup`)

### Files

- `file_backup.c` – C source code for the backup tool.
- `file_backup` – Compiled executable (generated on Linux).
- `file_backup_strace.txt` – Saved `strace` output used for analysis.

### Compilation (on Linux / WSL)

From the project root:

```bash
cd syscall_monitor
gcc -Wall -Wextra -O2 -o file_backup file_backup.c
```

### Running with `strace`

To trace all system calls made by the program and save them for analysis:

```bash
strace -o file_backup_strace.txt ./file_backup
```

This will:

- Execute the backup program.
- Log all system calls to `file_backup_strace.txt`.
- Create or update the files `backup.log`, `data.txt`, and `data.backup`.

### Program behavior (for reference)

At a high level:

- `main()` logs that the program started.
- `create_data_file()`:
  - Creates `data.txt` using `open(..., O_WRONLY | O_CREAT | O_TRUNC, 0644)`.
  - Writes some text into it using `write`.
  - Closes the file with `close`.
- `read_and_backup()`:
  - Opens `data.txt` for reading.
  - Creates or truncates `data.backup` for writing.
  - Copies data using a loop with `read` and `write`.
  - Logs “Backup completed”.
  - Opens `data.backup` with `fopen` and prints its contents using `fgets` and `printf`.
- On exit, the program logs that it has finished.

### What to extract from `strace`

Open `file_backup_strace.txt` and identify:

- **File-related system calls** (examples you should see):
  - `open` / `openat`
  - `creat` (sometimes used internally)
  - `read`
  - `write`
  - `close`
  - `stat` / `fstat` / `lstat`
  - `unlink` (if any temporary files are removed)
- **Process-related system calls**:
  - `execve` – when the program starts.
  - `brk`, `mmap`, `munmap` – memory management.
  - `getpid`, `getuid`, etc. – process identity.
  - `exit_group` – when the process terminates.

You do not need to list every single call, but you should:

- Categorize calls as **file-related** or **process-related**.
- Explain in your own words what each important call does in the context of this program.

### Summary table for the report

In your report, include a table similar to the following (fill in with your actual observations):

| System Call | Category       | When it occurs in program                  | Purpose (in your own words)                           |
|------------|----------------|--------------------------------------------|------------------------------------------------------|
| `execve`   | Process-related | At program start                           | Loads and starts executing the `file_backup` binary. |
| `openat`   | File-related    | When `data.txt` or `backup.log` is opened | Opens or creates a file and returns a file descriptor. |
| `write`    | File-related    | When writing to `data.txt` or `backup.log`| Writes bytes from memory to the file descriptor.     |
| `read`     | File-related    | When copying `data.txt` to `data.backup`   | Reads bytes from a file descriptor into memory.      |
| `close`    | File-related    | After finishing with a file                | Closes an open file descriptor.                      |
| `exit_group` | Process-related | At program termination                     | Ends the process and all its threads.                |

### Report guidance (short explanation)

In your short report or summary:

- Explain that you compiled and ran `file_backup` under `strace`.
- Describe briefly what the program does at source level (file creation, backup, logging).
- Summarize:
  - The main **file-related system calls** and how they correspond to operations in the C code.
  - The main **process-related system calls** observed at startup/termination.
- Conclude with a brief explanation of how system call tracing helps understand a program’s interaction with the operating system.

