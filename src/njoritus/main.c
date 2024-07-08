#include <njoritus/bot.h>
#include <njoritus/core.h>
#include <njoritus/user_interface.h>
#include <utilities.h>

int main() {

  if (initialize() != APR_SUCCESS) {
    return EXIT_FAILURE;
  }

  apr_pool_t *pool = NULL;
  if (initializePool(&pool, NULL) != APR_SUCCESS) {
    return cleanupAndTerminate(IMMEDIATE_TERMINATE, NULL, EXIT_FAILURE);
  }

  int status = manageNjoritusBot(pool);
  return cleanupAndTerminate(IMMEDIATE_TERMINATE, pool, status);
}
