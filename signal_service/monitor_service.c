#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

// Global flag for program state
volatile sig_atomic_t keep_running = 1;
volatile sig_atomic_t show_status = 0;
volatile sig_atomic_t emergency_stop = 0;

// Signal handler function
void signal_handler(int signum) {
    switch(signum) {
        case SIGINT:
            keep_running = 0;
            break;
            
        case SIGUSR1:
            printf("\nSystem status requested by administrator.\n");
            show_status = 1;
            break;
            
        case SIGTERM:
            printf("\nEmergency shutdown signal received.\n");
            emergency_stop = 1;
            keep_running = 0;
            break;
    }
}

// Setup signal handlers
void setup_signal_handlers() {
    struct sigaction sa;
    
    // Clear structure
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    
    // Set flags to automatically restart interrupted system calls
    sa.sa_flags = SA_RESTART;
    
    // Register handlers for different signals
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Failed to set SIGINT handler");
        exit(1);
    }
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Failed to set SIGUSR1 handler");
        exit(1);
    }
    
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Failed to set SIGTERM handler");
        exit(1);
    }
    
    printf("Signal handlers registered successfully\n");
    printf("Process ID: %d\n", getpid());
    printf("Send signals using: kill -SIGUSR1 %d\n", getpid());
    printf("Press Ctrl+C to test SIGINT\n\n");
}

int main() {
    int counter = 0;
    
    // Setup signal handlers
    setup_signal_handlers();
    
    printf("Monitor Service Started\n");
    printf("=======================\n");
    
    // Main service loop
    while (keep_running) {
        // Check for status request
        if (show_status) {
            printf("[Monitor Service] System status: Running normally. Uptime: %d seconds\n", 
                   counter * 5);
            show_status = 0;
        }
        
        // Check for emergency stop
        if (emergency_stop) {
            break;
        }
        
        // Regular status message every 5 seconds
        printf("[Monitor Service] System running normally... (Uptime: %d seconds)\n", 
               counter * 5);
        
        // Sleep for 5 seconds
        sleep(5);
        counter++;
    }
    
    // Graceful shutdown
    if (!emergency_stop) {
        printf("\nMonitor Service shutting down safely.\n");
        printf("Total uptime: %d seconds\n", counter * 5);
        printf("Shutdown complete.\n");
    }
    
    return 0;
}
