#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>

#define BUFFER_SIZE 4096
#define LOG_FILE "data_sync.log"

void log_message(const char *msg)
{
    FILE *log = fopen(LOG_FILE, "a");
    if (!log)
        return;

    time_t now = time(NULL);
    char *time_str = ctime(&now);

    if (time_str)
    {
        time_str[strlen(time_str) - 1] = '\0';
        fprintf(log, "[%s] %s\n", time_str, msg);
    }

    fclose(log);
}

int copy_file(const char *src_path, const char *dst_path)
{
    int src_fd = open(src_path, O_RDONLY);
    if (src_fd < 0)
    {
        perror("open source");
        return -1;
    }

    int dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd < 0)
    {
        perror("open destination");
        close(src_fd);
        return -1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes;

    while ((bytes = read(src_fd, buffer, BUFFER_SIZE)) > 0)
    {
        ssize_t total_written = 0;

        while (total_written < bytes)
        {
            ssize_t written = write(dst_fd, buffer + total_written, bytes - total_written);

            if (written < 0)
            {
                perror("write");
                close(src_fd);
                close(dst_fd);
                return -1;
            }

            total_written += written;
        }
    }

    if (bytes < 0)
        perror("read");

    close(src_fd);
    close(dst_fd);

    return 0;
}

int sync_directory(const char *src, const char *dst)
{
    DIR *dir = opendir(src);
    if (!dir)
    {
        perror("opendir");
        return -1;
    }

    struct dirent *entry;
    char src_path[512];
    char dst_path[512];

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dst_path, sizeof(dst_path), "%s/%s", dst, entry->d_name);

        struct stat st;

        if (stat(src_path, &st) == -1)
            continue;

        if (S_ISDIR(st.st_mode))
            continue;

        if (copy_file(src_path, dst_path) == 0)
            log_message("File synchronized");
        else
            log_message("File synchronization failed");
    }

    closedir(dir);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_dir> <dest_dir>\n", argv[0]);
        return 1;
    }

    log_message("Data sync started");

    int result = sync_directory(argv[1], argv[2]);

    if (result == 0)
        log_message("Data sync completed");
    else
        log_message("Data sync failed");

    return result;
}
