## Project 1 – Investigating a Suspicious Binary

**Goal:** build a small ELF binary (`data_sync`) and inspect it with standard tools (no execution required).

### Build

```bash
cd binary_analysis
gcc -Wall -Wextra -O2 -o data_sync data_sync.c
```

### Inspect

Run whichever tools you need for your analysis, for example:

```bash
objdump -f -h -d ./data_sync
nm ./data_sync
nm -D ./data_sync
strings ./data_sync | less
```

Use the outputs to infer what `data_sync` does (entry point, sections, imported functions, and any interesting strings).
