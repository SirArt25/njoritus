#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <apr.h>
#include <njoritus/core.h>
#include <njoritus/query_classifier.h>
#include <njoritus/semantic_checkers/cordinate_checker.h>
#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>

typedef struct {
  char str[512];
  QueryType type;
} QAPair;

void test_process_query() {
  if (initializeAPR() != APR_SUCCESS) {
    return;
  }

  apr_pool_t *p_pool = NULL;
  if (initializePool(&p_pool, NULL) != APR_SUCCESS) {
    apr_terminate();
    return;
  }

  QueryClassifierConfig config;
  QueryClassifier classifier;

  if (initializeQuerying(&config, &classifier, p_pool) != APR_SUCCESS) {
    cleanupAndTerminate(IMMEDIATE_TERMINATE, p_pool, EXIT_FAILURE);
    return;
  }

  Coordinates_double cordinates;
  GeneralCallbackT *p_cordinate_callback =
      createCallbackData((void *)&cordinates, classifier.m_p_pool);
  if (p_cordinate_callback == NULL) {
    terminateQuerying(&config, &classifier, EXIT_FAILURE);
    cleanupAndTerminate(IMMEDIATE_TERMINATE, p_pool, EXIT_FAILURE);
    return;
  }

  const char *p_pattern = "^([-+]?([1-8]?[0-9](\\.[0-9]+)?|90(\\.0+)?)),"
                          "\\s*([-+]?((1[0-7][0-9]|[0-9]?[0-9])"
                          "(\\.[0-9]+)?|180(\\.0+)?))$";

  if (addPatternConfig(&config, p_pattern, cordinateChecker,
                       p_cordinate_callback,
                       QUERY_TYPE_LAT_LONG) != APR_SUCCESS) {

    terminateQuerying(&config, NULL, EXIT_FAILURE);
    cleanupAndTerminate(IMMEDIATE_TERMINATE, p_pool, EXIT_FAILURE);
    return;
  }

  if (addPatternConfig(&config, "([A-Za-z\\s]+)", NULL, NULL,
                       QUERY_TYPE_CITY_NAME) != APR_SUCCESS) {

    terminateQuerying(&config, NULL, EXIT_FAILURE);
    cleanupAndTerminate(IMMEDIATE_TERMINATE, p_pool, EXIT_FAILURE);
    return;
  }
  QAPair pairs[] = {
      {"London", QUERY_TYPE_CITY_NAME},
      {"Berlin123", QUERY_TYPE_CITY_NAME},
      {"Paris", QUERY_TYPE_CITY_NAME},
      {"18,    29", QUERY_TYPE_LAT_LONG},
      {"18,180", QUERY_TYPE_LAT_LONG},
      {"18,179.11111111111", QUERY_TYPE_LAT_LONG},
      {"90,179.11111111", QUERY_TYPE_LAT_LONG},
      {"90,180.12", QUERY_TYPE_UNKNOWN},
      {"90,-179.11111111", QUERY_TYPE_LAT_LONG},
      {"-90,179.11111111", QUERY_TYPE_LAT_LONG},
      {"-45.222, 179.11111111", QUERY_TYPE_LAT_LONG},
  };

  int size = sizeof(pairs) / sizeof(pairs[0]);

  for (int i = 0; i < size; ++i) {
    CU_ASSERT(proccessQuery(&classifier, pairs[i].str) == pairs[i].type);
  }
  terminateQuerying(&config, &classifier, EXIT_SUCCESS);
  cleanupAndTerminate(IMMEDIATE_TERMINATE, p_pool, EXIT_SUCCESS);
}

int main() {
  // Initialize CUnit test registry
  if (CU_initialize_registry() != CUE_SUCCESS) {
    return CU_get_error();
  }

  // Add a suite to the registry
  CU_pSuite pSuite = CU_add_suite("Suite_1", 0, 0);
  if (pSuite == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  // Add the test to the suite
  if (CU_add_test(pSuite, "test of process_query()", test_process_query) ==
      NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Run all tests using the basic interface
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_number_of_failures();
}
