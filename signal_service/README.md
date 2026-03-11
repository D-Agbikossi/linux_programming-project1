## Project 4 – Signal-Based Server Controller

**Goal:** run a simple monitoring service that reacts to Unix signals.

### Build

```bash
cd signal_service
gcc -Wall -Wextra -O2 -o monitor_service monitor_service.c
```

### Run and send signals

In one terminal:

```bash
./monitor_service
```

In another terminal, get the PID (if needed) and send signals:

```bash
ps aux | grep monitor_service   # find <pid> if not printed
kill -SIGUSR1 <pid>             # request status
kill -SIGINT <pid>              # graceful shutdown (or Ctrl+C)
kill -SIGTERM <pid>             # emergency shutdown
```

Watch the service output to see how each signal is handled.

