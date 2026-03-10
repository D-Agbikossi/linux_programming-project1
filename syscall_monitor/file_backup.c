#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define LOG_FILE "backup.log"
#define DATA_FILE "data.txt"
#define BACKUP_FILE "data.backup"

void write_log(const char *message)
{
    FILE *log = fopen(LOG_FILE, "a");
    if (log)
    {
        time_t now = time(NULL);
        fprintf(log, "[%ld] %s\n", now, message);
        fclose(log);
    }
}

void create_data_file()
{
    int fd = open(DATA_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        write_log("Failed to create data file");
        return;
    }

    const char *content = "Important data\nLine 2\nLine 3\n";
    ssize_t written = write(fd, content, strlen(content));

    if (written < 0)
    {
        perror("write");
        write_log("Write failed");
    }

    close(fd);
    write_log("Data file created");
}

void read_and_backup()
{
    int src_fd = open(DATA_FILE, O_RDONLY);
    if (src_fd < 0)
    {
        perror("open");
        write_log("Failed to open data file for reading");
        return;
    }

    int dst_fd = open(BACKUP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd < 0)
    {
        perror("open");
        close(src_fd);
        write_log("Failed to create backup file");
        return;
    }

    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0)
    {
        ssize_t total_written = 0;

        while (total_written < bytes_read)
        {
            ssize_t written = write(dst_fd,
                                    buffer + total_written,
                                    bytes_read - total_written);

            if (written < 0)
            {
                perror("write");
                close(src_fd);
                close(dst_fd);
                write_log("Backup write failed");
                return;
            }

            total_written += written;
        }
    }

    if (bytes_read < 0)
    {
        perror("read");
        write_log("Read error during backup");
    }

    close(src_fd);
    close(dst_fd);

    write_log("Backup completed");

    FILE *backup = fopen(BACKUP_FILE, "r");
    if (backup)
    {
        char line[256];
        while (fgets(line, sizeof(line), backup))
        {
            printf("Backup contains: %s", line);
        }
        fclose(backup);
    }
}

int main()
{
    printf("File Backup Program Started (PID: %d)\n", getpid());

    write_log("Program started");

    create_data_file();
    read_and_backup();

    write_log("Program finished");

    printf("Backup completed. Check %s and %s\n", DATA_FILE, BACKUP_FILE);

    return 0;
}
