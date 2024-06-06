#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <sys/stat.h>

void Logger(char* session, int actionCode, char* message);

#endif // LOGGER_H