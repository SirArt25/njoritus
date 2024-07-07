#include <njoritus/semantic_checkers/cordinate_checker.h>
#include <stdlib.h>

int validateCoordinates(const Coordinates *coords) {
  double lat = atof(coords->cp_latitude);
  double lon = atof(coords->cp_longitude);

  const double MIN_LAT = -90.0;
  const double MAX_LAT = 90.0;

  const double MIN_LON = -180.0;
  const double MAX_LON = 180.0;

  if (lat < MIN_LAT || lat > MAX_LAT || lon < MIN_LON || lon > MAX_LON) {
    return -1;
  }
  return 0;
}

int cordinateChecker(const RegexWrapper *cp_regex_wrapper, const char *cp_str,
                     apr_pool_t *p_parent_pool,
                     GeneralCallbackT *p_cordinate_call) {

  if (cp_regex_wrapper == NULL || cp_str == NULL) {
    return -1;
  }

  if (isRegexWrapperCompiled(cp_regex_wrapper) == FALSE) {
    return -1;
  }

  apr_pool_t *p_pool = NULL;
  if (apr_pool_create(&p_pool, p_parent_pool) != APR_SUCCESS) {
    return -1;
  }

  const int MATCH_COUNT = 6;
  const int LAT_POS = 1;
  const int LON_POS = 5;
  regmatch_t pmatch[MATCH_COUNT]; // Full match + Latitude +
                                  // Longitude and subgroups

  int status =
      regexec(&cp_regex_wrapper->m_regex, cp_str, MATCH_COUNT, pmatch, 0);
  int result = -1;
  if (status == REG_NOERROR) {
    Coordinates coords;

    int lat_len = pmatch[LAT_POS].rm_eo - pmatch[LAT_POS].rm_so;
    int lon_len = pmatch[LON_POS].rm_eo - pmatch[LON_POS].rm_so;

    char *p_latitude = apr_palloc(p_pool, lat_len + 1);
    char *p_longitude = apr_palloc(p_pool, lon_len + 1);

    strncpy(p_latitude, cp_str + pmatch[LAT_POS].rm_so, lat_len);
    p_latitude[lat_len] = '\0';

    strncpy(p_longitude, cp_str + pmatch[LON_POS].rm_so, lon_len);
    p_longitude[lon_len] = '\0';

    coords.cp_latitude = p_latitude;
    coords.cp_longitude = p_longitude;

    double lat = atof(coords.cp_latitude);
    double lon = atof(coords.cp_longitude);
    if (p_cordinate_call != NULL && isCallbackData(p_cordinate_call)) {
      Coordinates_double *cord_call =
          (Coordinates_double *)p_cordinate_call->callback.data;
      if (cord_call != NULL) {
        cord_call->m_latitude = lat;
        cord_call->m_longitude = lon;
      }
    }

    result = validateCoordinates(&coords);
  } else if (status == REG_NOMATCH) {
    result = 1;
  } else {
    const int BUFFER_SIZE = 100;
    char msgbuf[BUFFER_SIZE];
    regerror(status, &cp_regex_wrapper->m_regex, msgbuf, BUFFER_SIZE);
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    result = status;
  }
  apr_pool_destroy(p_pool);
  return result;
}
