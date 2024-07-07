#ifndef NJORITUS_REGEX_WRAPPER_H
#define NJORITUS_REGEX_WRAPPER_H

#include <apr_strings.h>
#include <regex.h>
#include <stdio.h>

typedef struct {
  regex_t m_regex;
  int m_is_compiled; // FALSE = not compiled, TRUE = compiled
} RegexWrapper;

int compileRegexWrapper(RegexWrapper *this, const char *cp_pattern);
void emptyInitilizeRegexWrapper(RegexWrapper *this);
int recompileRegexWrapper(RegexWrapper *this, const char *cp_pattern_config);
int isRegexWrapperCompiled(const RegexWrapper *this);
void cleanupRegexWrapper(RegexWrapper *this);
int rawMatchRegexWrapper(RegexWrapper *this, const char *cp_text);

#endif // NJORITUS_REGEX_WRAPPER_H
