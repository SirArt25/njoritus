#include <njoritus/user_interface.h>
#include <utilities/utilities.h>

static int terminateInteractiveQuery(QueryClassifierConfig *p_config,
                                     QueryClassifier *p_classifier, int c_val);

extern char *getWeatherLatLng(double lat, double lng);
extern char *getWeatherName(char *location);

int interactiveInput(apr_file_t *in_file, apr_pool_t *pool) {
  QueryClassifierConfig config;

  if (initQueryClassifierConfig(&config, pool) != APR_SUCCESS) {
    return EXIT_FAILURE;
  }

  const char *p_pattern = "^([-+]?([1-8]?[0-9](\\.[0-9]+)?|90(\\.0+)?)),"
                          "\\s*([-+]?((1[0-7][0-9]|[0-9]?[0-9])"
                          "(\\.[0-9]+)?|180(\\.0+)?))$";

  Coordinates_double cordinates;
  GeneralCallbackT cordinate_callback;
  setCallbackData(&cordinate_callback, &cordinates);
  SemanticChecker checker = cordinateChecker;
  if (addPatternConfig(&config, p_pattern, checker, &cordinate_callback,
                       QUERY_TYPE_LAT_LONG) != APR_SUCCESS) {
    return terminateInteractiveQuery(&config, NULL, EXIT_FAILURE);
  }

  checker = NULL;
  if (addPatternConfig(&config, "([A-Za-z\\s]+)", checker, NULL,
                       QUERY_TYPE_CITY_NAME) != APR_SUCCESS) {
    return terminateInteractiveQuery(&config, NULL, EXIT_FAILURE);
  }

  QueryClassifier classifier;
  if (initQueryClassifier(&classifier, pool, &config) != APR_SUCCESS) {
    return terminateInteractiveQuery(&config, NULL, EXIT_FAILURE);
  }

  const int LENGTH = 256;
  char input[LENGTH];

  while (1) {

    // apr_size_t len = sizeof(input) - 1;

    printf("Enter a line (type 'end' to terminate): ");
    fflush(stdout);

    if (readInput(input, LENGTH, in_file) != APR_SUCCESS) {
      return terminateInteractiveQuery(&config, &classifier, EXIT_FAILURE);
    }

    // Check if the input is "end"
    if (strcmp(input, "end") == 0) {
      printf("Terminating...\n");
      break;
    }

    int result = proccessQuery(&classifier, input);

    if (result == QUERY_TYPE_CITY_NAME) {
      printf("You entered a city: %s\n", input);
      printf("Temperature of city : %s\n", getWeatherName(input));
    } else if (result == QUERY_TYPE_LAT_LONG) {
      printf("You entered a lat  %f  long: %f\n", cordinates.m_latitude,
             cordinates.m_longitude);
      printf("Temperature of lat long : %s\n",
             getWeatherLatLng(cordinates.m_latitude, cordinates.m_longitude));
    } else {
      printf("You entered a not understand: %s\n", input);
    }
  }

  return terminateInteractiveQuery(&config, &classifier, EXIT_SUCCESS);
}

int terminateInteractiveQuery(QueryClassifierConfig *p_config,
                              QueryClassifier *p_classifier, int c_val) {
  if (p_config != NULL) {
    terminateQueryClassifierConfig(p_config);
  }
  if (p_classifier != NULL) {
    terminateQueryClassifier(p_classifier);
  }
  return c_val;
}
