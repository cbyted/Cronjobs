# Cronjob Simulator

A small C program that simulates a cron job by reading scheduled commands from `cronjobs.conf`.

## Configuration

Create a `cronjobs.conf` file in the program’s working directory:

```text
1 ls -lh
2 echo "Hello world"
8 echo "Just another test"
```

Each line contains a time value followed by the command to run. The program reads this file when it starts.

## Build

Using GCC:

```bash
gcc -Wall -Wextra -o cronjob main.c
```

## Run

Make sure `cronjobs.conf` is in the current directory, then run:

```bash
./cronjob
```

