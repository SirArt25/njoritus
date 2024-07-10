#include <njoritus/response_functions/get_response_weather.h>
#include <string.h>

extern char *getWeatherLatLng(double lat, double lng);
extern char *getWeatherName(const char *location);
extern void freeCStyleString(char *str);

int responseGetWeather(const char *cp_query, apr_pool_t *p_parent_pool,
                       GeneralCallbackT *p_general_callback) {
  if (isCallbackFunction(p_general_callback) || cp_query == NULL) {
    return EXIT_FAILURE;
  }
  QueryClassifierConfig config;
  QueryClassifier classifier;

  if (initializeQuerying(&config, &classifier, p_parent_pool) != APR_SUCCESS) {
    return EXIT_FAILURE;
  }

  Coordinates_double cordinates;
  GeneralCallbackT *p_cordinate_callback =
      createCallbackData((void *)&cordinates, classifier.m_p_pool);
  if (p_cordinate_callback == NULL) {
    return terminateQuerying(&config, &classifier, EXIT_FAILURE);
  }

  const char *p_pattern = "^([-+]?([1-8]?[0-9](\\.[0-9]+)?|90(\\.0+)?)),"
                          "\\s*([-+]?((1[0-7][0-9]|[0-9]?[0-9])"
                          "(\\.[0-9]+)?|180(\\.0+)?))$";

  if (addPatternConfig(&config, p_pattern, cordinateChecker,
                       p_cordinate_callback,
                       QUERY_TYPE_LAT_LONG) != APR_SUCCESS) {
    return terminateQuerying(&config, NULL, EXIT_FAILURE);
  }

  if (addPatternConfig(&config, "([A-Za-z\\s]+)", NULL, NULL,
                       QUERY_TYPE_CITY_NAME) != APR_SUCCESS) {
    return terminateQuerying(&config, NULL, EXIT_FAILURE);
  }

  int result = proccessQuery(&classifier, cp_query);
  char *p_result = (char *)p_general_callback->callback.data;
  if (p_result == NULL) {
    return terminateQuerying(&config, &classifier, EXIT_FAILURE);
  }

  if (result == QUERY_TYPE_UNKNOWN) {
    const int BAD_SIZE = 100;
    strncpy(p_result, "Location does not exist", BAD_SIZE);
    return terminateQuerying(&config, &classifier, EXIT_SUCCESS);
  }

  char *p_temp_result = NULL;

  if (result == QUERY_TYPE_CITY_NAME) {
    p_temp_result = getWeatherName(cp_query);
  } else if (result == QUERY_TYPE_LAT_LONG) {
    p_temp_result =
        getWeatherLatLng(cordinates.m_latitude, cordinates.m_longitude);
  }

  if (p_temp_result == NULL) {
    const int BAD_SIZE = 100;
    strncpy(p_result, "Location does not exist", BAD_SIZE);
    return terminateQuerying(&config, &classifier, EXIT_SUCCESS);
  }
  strncpy(p_result, p_temp_result, strlen(p_temp_result));
  freeCStyleString(p_temp_result);
  return terminateQuerying(&config, &classifier, EXIT_SUCCESS);
}

int responseStart(const char *cp_query, apr_pool_t *p_parent_pool,
                  GeneralCallbackT *p_general_callback) {
  if (isCallbackFunction(p_general_callback) || cp_query == NULL) {
    return EXIT_FAILURE;
  }

  char *p_result = (char *)p_general_callback->callback.data;
  if (p_result == NULL) {
    return EXIT_FAILURE;
  }
  p_parent_pool = NULL;
  const int MESSAGE_SIZE = 100;
  strncpy(p_result, "Hello! Welcome to Njoritus!", MESSAGE_SIZE);
  return EXIT_SUCCESS;
}

int responseHelp(const char *cp_query, apr_pool_t *p_parent_pool,
                 GeneralCallbackT *p_general_callback) {

  if (isCallbackFunction(p_general_callback) || cp_query == NULL) {
    return EXIT_FAILURE;
  }

  char *p_result = (char *)p_general_callback->callback.data;
  if (p_result == NULL) {
    return EXIT_FAILURE;
  }
  p_parent_pool = NULL;
  const int MESSAGE_SIZE = 450;
  strncpy(
      p_result,
      "Hi there! Here are the commands you can use with Njoritus:\n"

      "/start - Start the Njoritus and get a welcome message.\n"
      "/getweather [City] or /getweather [Latitude, Longitude]\n"
      "\t- Provide a city name or coordinates to get the current weather.\n"
      "\t Examples: `/getweather London` or `/getweather 51.5074, -0.1278`\n"
      "/help - Display this help message with the list of available "
      "commands.\n\n"

      "If you have any questions or need further assistance, feel free to ask!",
      MESSAGE_SIZE);
  return EXIT_SUCCESS;
}
