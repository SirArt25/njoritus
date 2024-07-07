#ifndef NJORITUS_SEMANTIC_CHECKERS_CORDINATE_CHECKERS_H
#define NJORITUS_SEMANTIC_CHECKERS_CORDINATE_CHECKERS_H

#include <njoritus/regex_wrapper.h>

typedef struct {
    const char * cp_latitude;
    const char * cp_longitude;
} Coordinates;

int cordinateChecker(const RegexWrapper * cp_regex_wrapper, const char *cp_str,
                                                apr_pool_t * cp_parent_pool);
int validate_coordinates(const Coordinates *coords);

#endif // NJORITUS_SEMANTIC_CHECKERS_CORDINATE_CHECKERS_H
