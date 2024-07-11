#include <njoritus/user_interface.h>
#include <utilities/utilities.h>

/**
 * @brief
 *
 * @param p_parent_pool
 * @return int
 */
int manageNjoritusBot(apr_pool_t *p_parent_pool) {
  NjoritusBot njoritus;
  if (setupNjoritusBot(&njoritus) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }
  if (runNjoritusBot(&njoritus, p_parent_pool) != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }
  destroyNjoritusBot(&njoritus);
  return EXIT_SUCCESS;
}
