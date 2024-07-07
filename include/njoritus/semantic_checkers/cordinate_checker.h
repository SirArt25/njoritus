#ifndef NJORITUS_SEMANTIC_CHECKERS_CORDINATE_CHECKERS_H
#define NJORITUS_SEMANTIC_CHECKERS_CORDINATE_CHECKERS_H

#include <njoritus/callbacks.h>
#include <njoritus/regex_wrapper.h>

typedef struct {
  const char *cp_latitude;
  const char *cp_longitude;
} Coordinates;

typedef struct {
  double m_latitude;
  double m_longitude;
} Coordinates_double;

int cordinateChecker(const RegexWrapper *cp_regex_wrapper, const char *cp_str,
                     apr_pool_t *cp_parent_pool,
                     GeneralCallbackT *p_cordinate_call);
int validateCoordinates(const Coordinates *coords);

#endif // NJORITUS_SEMANTIC_CHECKERS_CORDINATE_CHECKERS_H
