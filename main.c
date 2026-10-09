#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define COMMAND_SIZE 1000
#define MAX_CRON_ENTRIES 1000


typedef struct 
{
    int interval_sec;
    char command[COMMAND_SIZE];
    int seconds_count;
} CronEntry;


int main()
{
    printf("Running the executor ...\n");
  
    // Read cronjobs config file
    FILE *conf_file = fopen("cronjob.conf", "r");
  
    if (!conf_file)
    {
        perror("[!] Failed opening cronjob.conf");
        return EXIT_FAILURE;
    }

    CronEntry cron_entries[MAX_CRON_ENTRIES];
    memset(cron_entries, 0, MAX_CRON_ENTRIES * sizeof(CronEntry));
 
  // Read the cronjob config file
    size_t current_idx = 0;
    char line[COMMAND_SIZE];
    memset(line, 0, COMMAND_SIZE);

    while (fgets(line, COMMAND_SIZE, conf_file) != NULL)
    {
        // Parse the cronjob config file
        int interval_sec = 0;
        char command[COMMAND_SIZE];
        memset(command, 0, COMMAND_SIZE);

        sscanf(line, "%d %800c", &interval_sec, command);

        cron_entries[current_idx].interval_sec = interval_sec;
        strcpy(cron_entries[current_idx].command, command); 
        cron_entries[current_idx].seconds_count = 0;

        current_idx++;
        memset(line, 0, COMMAND_SIZE);
    }

    while (1) 
    {
        for (size_t idx = 0; idx < current_idx; idx++) 
        {
            if (cron_entries[idx].interval_sec - cron_entries[idx].seconds_count == 0)
            {
                system(cron_entries[idx].command);
                cron_entries[idx].seconds_count = 0;
            }
            cron_entries[idx].seconds_count++;
        }
        sleep(1);
  }

    return EXIT_SUCCESS;
}
