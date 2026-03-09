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
#define LOG_FILE "/var/log/data_sync.log"

void log_message(const char *msg) {
    FILE *log = fopen(LOG_FILE, "a");
    if (log) {
        time_t now = time(NULL);
        fprintf(log, "[%s] %s\n", ctime(&now), msg);
        fclose(log);
    }
}

int sync_directory(const char *src, const char *dst) {
    DIR *dir = opendir(src);
    if (!dir) return -1;
    
    struct dirent *entry;
    char src_path[512], dst_path[512];
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
            
        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dst_path, sizeof(dst_path), "%s/%s", dst, entry->d_name);
        
        int src_fd = open(src_path, O_RDONLY);
        if (src_fd < 0) continue;
        
        int dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (dst_fd < 0) {
            close(src_fd);
            continue;
        }
        
        char buffer[BUFFER_SIZE];
        ssize_t bytes;
        while ((bytes = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
            write(dst_fd, buffer, bytes);
        }
        
        close(src_fd);
        close(dst_fd);
        log_message("File synchronized");
    }
    
    closedir(dir);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_dir> <dest_dir>\n", argv[0]);
        return 1;
    }
    
    log_message("Data sync started");
    int result = sync_directory(argv[1], argv[2]);
    log_message(result == 0 ? "Data sync completed" : "Data sync failed");
    
    return result;
}
