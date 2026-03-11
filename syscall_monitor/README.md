## Project 2 – System Call Monitoring Tool

**Goal:** run a small file backup program under `strace` and see which system calls it makes.

### Build

```bash
cd syscall_monitor
gcc -Wall -Wextra -O2 -o file_backup file_backup.c
```

### Run with `strace`

```bash
strace -o file_backup_strace.txt ./file_backup
```

This creates `file_backup_strace.txt` plus a few simple test files. Use the trace to see which calls are file‑related vs process‑related and how they map to the code.

