#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <sys/stat.h>

// declarasikan bahwa ada variable bernama session
extern char session[50];

void Logger(int actionCode, char* message);

#endif // LOGGER_H