#include "logger.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <raylib.h>


char *current_time_to_str() {
    time_t now = time(NULL);

    char *formated_time = ctime(&now);
    formated_time[strlen(formated_time)-1] = '\0';

    return formated_time;
}
void logger_log(const char* message) {
    const char *time_stamped_message = TextFormat("[%s] %s", current_date_to_str(), message);
    const char *escape_code = "\x1B[32m";
    const char *reset_code = "\033[0m";
    const char *output = TextFormat("\n%sLOG: %s%s\n", escape_code, time_stamped_message, reset_code);
    fprintf(stdout, "%s", output);
}
void logger_err(const char* message) {
    const char *time_stamped_message = TextFormat("[%s] %s", current_date_to_str(), message);
    const char *escape_code = "\x1B[91m";
    const char *reset_code = "\033[0m";
    const char *output = TextFormat("\n%sERR: %s%s\n", escape_code, time_stamped_message, reset_code);
    fprintf(stderr, "%s", output);
}
