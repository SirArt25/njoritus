#ifndef NJORITUS_REGEX_H
#define NJORITUS_REGEX_H

#include <njoritus/query_classifier_config.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  RegexWrapper m_regex_wrapper;
  const PatternConfig *m_cp_pattern_config;
} NjoritusRegex;

int compileNjoritusRegex(NjoritusRegex *this,
                         const PatternConfig *cp_pattern_config);
void emptyInitilizeNjoritusRegex(NjoritusRegex *this);
int recompileNjoritusRegex(NjoritusRegex *this,
                           const PatternConfig *cp_pattern_config);
int matchNjoritusRegex(NjoritusRegex *this, const char *cp_text);
int isNjoritusRegexCompiled(NjoritusRegex *this);
void cleanupNjoritusRegex(NjoritusRegex *this);

#endif // NJORITUS_REGEX_H
