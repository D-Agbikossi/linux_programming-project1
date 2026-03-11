## Linux Programming – Project 1

This repo contains four small Linux programming examples. Each folder is self‑contained.

- `binary_analysis/` – ELF analysis of a simulated `data_sync` binary.
- `syscall_monitor/` – System call tracing of a file backup tool.
- `python_extension/` – Python stats C extension + benchmark.
- `signal_service/` – Signal‑driven monitoring service.

### Requirements

- Linux or WSL with `gcc`, `make`, and standard build tools.
- Python 3 (for `python_extension/`).

### Quick start

- **Project 1 – ELF analysis**
  - `cd binary_analysis`
  - `gcc -Wall -Wextra -O2 -o data_sync data_sync.c`
  - Use tools like `objdump`, `nm`, and `strings` on `./data_sync` as needed.

- **Project 2 – System call monitor**
  - `cd syscall_monitor`
  - `gcc -Wall -Wextra -O2 -o file_backup file_backup.c`
  - `strace -o file_backup_strace.txt ./file_backup`

- **Project 3 – Python C extension**
  - `cd python_extension`
  - `python3 -m pip install . --user`  *(or `python3 setup.py build && python3 setup.py install --user`)*
  - `python3 benchmark.py`

- **Project 4 – Signal service**
  - `cd signal_service`
  - `gcc -Wall -Wextra -O2 -o monitor_service monitor_service.c`
  - In one terminal: `./monitor_service`
  - In another: send signals with `kill -SIGUSR1 <pid>`, `kill -SIGINT <pid>`, `kill -SIGTERM <pid>`

For more detail on any project, see the README inside its folder.
