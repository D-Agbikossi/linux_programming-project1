## Project 4 – Signal-Based Server Controller

### Overview

This project implements a simple background-style monitoring service that:

- Runs continuously and prints a status message every 5 seconds.
- Responds to Unix signals (`SIGINT`, `SIGUSR1`, `SIGTERM`) with different behaviors.

The main goal is to demonstrate how a program can register and handle signals from the operating system or other processes.

### Files

- `monitor_service.c` – C source code for the monitoring service.
- `monitor_service` – Compiled executable (on Linux).

### Compilation (on Linux / WSL)

From the project root:

```bash
cd signal_service
gcc -Wall -Wextra -O2 -o monitor_service monitor_service.c
```

### Running the service

In **terminal 1**, start the service:

```bash
./monitor_service
```

You should see output similar to:

- A startup banner (process ID and basic info).
- A repeated status line every 5 seconds:

```text
[Monitor Service] System running normally... (Uptime: 0 seconds)
[Monitor Service] System running normally... (Uptime: 5 seconds)
...
```

Leave this terminal running.

### Sending signals to the service

In **terminal 2**, find the process ID (PID) of the running service (if it is not clearly printed):

```bash
ps aux | grep monitor_service
```

Then send signals using `kill`:

- **Request status (`SIGUSR1`)**

```bash
kill -SIGUSR1 <pid>
```

Expected behavior in terminal 1:

- The program prints:

```text
System status requested by administrator.
```

- Followed by a detailed status line from the main loop, for example:

```text
[Monitor Service] System status: Running normally. Uptime: 10 seconds
```

- **Graceful shutdown (`SIGINT`)**

Typically triggered by `Ctrl+C` in terminal 1, or:

```bash
kill -SIGINT <pid>
```

Expected behavior:

- The service exits its main loop and prints:

```text
Monitor Service shutting down safely.
Total uptime: <N> seconds
Shutdown complete.
```

- **Emergency shutdown (`SIGTERM`)**

```bash
kill -SIGTERM <pid>
```

Expected behavior:

- The signal handler prints:

```text
Emergency shutdown signal received.
```

- The program then exits its main loop and terminates quickly.

### What to capture for the deliverables

- **Source code**:
  - `monitor_service.c`.
- **Compilation command**:
  - For example: `gcc -Wall -Wextra -O2 -o monitor_service monitor_service.c`.
- **Terminal demonstration**:
  - Copy or screenshot:
    - Normal running output (periodic status messages).
    - Output after sending `SIGUSR1`.
    - Output when shutting down via `SIGINT` and via `SIGTERM`.
- **Short explanation (½–1 page)**:
  - How `sigaction` (or `signal`) is used to register handlers in `setup_signal_handlers()`.
  - What happens when each signal is received:
    - `SIGINT`: triggers a graceful shutdown, leading to “Monitor Service shutting down safely.”
    - `SIGUSR1`: prints “System status requested by administrator.” and then a detailed status message.
    - `SIGTERM`: prints “Emergency shutdown signal received.” and stops the service.
  - Why signal handling is useful in background services and daemons.

