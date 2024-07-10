#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <apr.h>
#include <apr_pools.h>
#include <stdio.h>
#include <stdlib.h>
#include <thor-shield/dec.h>
#include <thor-shield/enc.h>
#include <thor-shield/mjolnir.h>
#include <utilities.h>

typedef struct {
  const char *service_name;
  const char *secret_token;
} SecretTestPair;

void test_secret_management() {
  SecretTestPair secret_pairs[] = {{"service1", "secret1"},
                                   {"service2", "secret2"},
                                   {"service3", "secret3"},
                                   {"service4", "secret4"},
                                   {"service5", "secret5"}};

  int num_pairs = sizeof(secret_pairs) / sizeof(secret_pairs[0]);

  apr_pool_t *p_pool;
  apr_initialize();
  apr_pool_create(&p_pool, NULL);

  for (int i = 0; i < num_pairs; ++i) {
    const char *service_name = secret_pairs[i].service_name;
    const char *secret_token = secret_pairs[i].secret_token;

    int save_result = saveSecret(secret_token, service_name);
    CU_ASSERT(save_result == 0);

    char *loaded_secret = loadSecret(service_name, p_pool);
    CU_ASSERT_PTR_NOT_NULL(loaded_secret);
    if (loaded_secret != NULL) {
      CU_ASSERT_STRING_EQUAL(loaded_secret, secret_token);
    }

    int delete_result = deleteKey(service_name);
    CU_ASSERT(delete_result == 0);

    char *deleted_secret = loadSecret(service_name, p_pool);
    CU_ASSERT_PTR_NULL(deleted_secret);
  }

  apr_pool_destroy(p_pool);
  apr_terminate();
}

int main() {
  if (CU_initialize_registry() != CUE_SUCCESS) {
    return CU_get_error();
  }

  CU_pSuite pSuite = CU_add_suite("Suite_1", 0, 0);
  if (pSuite == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (CU_add_test(pSuite, "test of test_secret_management()",
                  test_secret_management) == NULL) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_number_of_failures();
}
