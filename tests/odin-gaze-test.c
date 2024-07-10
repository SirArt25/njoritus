#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>

extern char *getWeatherLatLng(double lat, double lng);
extern char *getWeatherName(const char *location);
extern void freeCStyleString(char *str);

typedef struct {
  char str[512];
  char response[10];
} PairCityExist;

typedef struct {
  double lat;
  double lng;
  char response[10];
} LatLngResponse;

void test_response_name() {
  // getWeatherName(cp_query);
  PairCityExist city_pair[] = {{"Yerevan", "-"},        {"Gyumri", "-"},
                               {"London", "-"},         {"Berlin", "-"},
                               {"Berlin123", "(null)"}, {"Paris", "-"}};

  int size = sizeof(city_pair) / sizeof(city_pair[0]);

  for (int i = 0; i < size; ++i) {
    char *p_response = getWeatherName(city_pair[i].str);
    if (strcmp(city_pair[i].response, "-") == 0) {
      CU_ASSERT(strcmp(p_response, "(null)") != 0);
    } else {
      CU_ASSERT(p_response == NULL);
    }
    freeCStyleString(p_response);
  }
}

void test_response_lat_lng() {
  LatLngResponse lat_lng_pairs[] = {{16, 12, "-"},        {17, 92, "-"},
                                    {29, 180, "-"},       {26, 122, "-"},
                                    {190, 123, "(null)"}, {90.1, 90, "(null)"}};

  int size = sizeof(lat_lng_pairs) / sizeof(lat_lng_pairs[0]);

  for (int i = 0; i < size; ++i) {
    char *p_response =
        getWeatherLatLng(lat_lng_pairs[i].lat, lat_lng_pairs[i].lng);
    if (strcmp(lat_lng_pairs[i].response, "-") == 0) {
      CU_ASSERT(strcmp(p_response, "(null)") != 0);
    } else {
      CU_ASSERT(p_response == NULL);
    }
    freeCStyleString(p_response);
  }
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
  if (CU_add_test(pSuite, "test of test_response_name()", test_response_name) ==
      NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(pSuite, "test of test_response_lat_lng()",
                  test_response_lat_lng) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Run all tests using the basic interface
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_number_of_failures();
}
