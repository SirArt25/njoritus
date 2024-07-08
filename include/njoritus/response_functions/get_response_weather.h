#ifndef NJORITUS_GET_RESPONSE_WEATHER_H
#define NJORITUS_GET_RESPONSE_WEATHER_H

#include <apr.h>
#include <apr_file_io.h>
#include <apr_portable.h>
#include <njoritus/bot.h>
#include <njoritus/query_classifier.h>
#include <njoritus/semantic_checkers/cordinate_checker.h>
#include <utilities.h>

int responseGetWeather(const char *cp_query, apr_pool_t *p_parent_pool,
                       GeneralCallbackT *p_general_callback);

int responseStart(const char *cp_query, apr_pool_t *p_parent_pool,
                  GeneralCallbackT *p_general_callback);

int responseHelp(const char *cp_query, apr_pool_t *p_parent_pool,
                 GeneralCallbackT *p_general_callback);

#endif // NJORITUS_GET_RESPONSE_WEATHER_H
