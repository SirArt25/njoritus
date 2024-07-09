#include <mjolnir.h>
#include <utilities.h>

const SecretSchema MJOLNIR = {
    "com.example.ServiceOnly", // Unique names for mjolnir
    SECRET_SCHEMA_NONE,        // No flags for mjolnir
    {
        {"service", SECRET_SCHEMA_ATTRIBUTE_STRING}, // Service name
        {"NULL", 0},
    }};

/**
 * @brief
 *
 * @param p_parent_pool
 * @param p_data
 * @param p_path
 * @return int
 */
int secureExport(apr_pool_t *p_parent_pool, char *p_data, const char *p_path) {
  if (p_parent_pool == NULL || p_data == NULL || p_path == NULL) {
    return EXIT_FAILURE;
  }

  apr_pool_t *p_child_pool;
  apr_status_t status = initializePool(&p_child_pool, p_parent_pool);

  if (status != APR_SUCCESS) {
    apr_pool_destroy(p_child_pool);
    return EXIT_FAILURE;
  }

  apr_file_t *file;
  status = apr_file_open(&file, p_path, APR_WRITE | APR_CREATE | APR_TRUNCATE,
                         APR_OS_DEFAULT, p_child_pool);

  if (status != APR_SUCCESS) {
    apr_pool_destroy(p_child_pool);
    return EXIT_FAILURE;
  }

  size_t bytes_written = strlen(p_data);
  status = apr_file_write(file, p_data, &bytes_written);
  if (status != APR_SUCCESS || bytes_written != strlen(p_data)) {
    apr_file_close(file);
    apr_pool_destroy(p_child_pool);
    apr_terminate();
    return EXIT_FAILURE;
  }

  purgePointer(p_data, strlen(p_data));

  apr_file_close(file);
  apr_pool_destroy(p_child_pool);

  return EXIT_SUCCESS;
}
