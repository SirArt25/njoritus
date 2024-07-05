#ifndef NJORITUS_REGEX_H
#define NJORITUS_REGEX_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    regex_t regex;
    int is_compiled;
} NjoritusRegex;

int compileNjoritusRegex(NjoritusRegex *this, const char *cp_pattern);
int recompileNjoritusRegex(NjoritusRegex *this, const char *cp_pattern);
int matchNjoritusRegex(NjoritusRegex *this, const char *cp_text);
int isNjoritusRegexCompiled(NjoritusRegex *this);
void cleanupNjoritusRegex(NjoritusRegex *this);
#endif // NJORITUS_REGEX_H
