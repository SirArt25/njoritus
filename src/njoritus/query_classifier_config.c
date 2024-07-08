#include <njoritus/query_classifier_config.h>
#include <stddef.h>

/**
 * @brief
 *
 * @param this
 * @param main_pool
 * @return apr_status_t
 */
apr_status_t initQueryClassifierConfig(QueryClassifierConfig *this,
                                       apr_pool_t *p_main_pool) {
  apr_status_t status = apr_pool_create(&this->m_p_pool, p_main_pool);

  if (status != APR_SUCCESS) {
    return status;
  }

  this->m_array_pattern_configs =
      apr_array_make(this->m_p_pool, 2, sizeof(QuerryPattern));

  if (this->m_array_pattern_configs == NULL) {
    apr_pool_destroy(this->m_p_pool);
    return APR_ENOMEM;
  }
  return APR_SUCCESS;
}

/**
 * @brief
 *
 * @param this
 * @param p_pattern
 * @param checker
 * @param p_gcallback
 * @param type
 * @return apr_status_t
 */
apr_status_t addPatternConfig(QueryClassifierConfig *this,
                              const char *p_pattern, SemanticChecker checker,
                              GeneralCallbackT *p_gcallback, QueryType type) {

  QuerryPattern *p_pattern_config =
      (QuerryPattern *)apr_array_push(this->m_array_pattern_configs);

  if (p_pattern_config == NULL) {
    return APR_ENOMEM;
  }

  p_pattern_config->m_pattern_config.m_p_pattern = p_pattern;
  p_pattern_config->m_pattern_config.m_semantic_checker = checker;
  p_pattern_config->m_pattern_config.m_p_gcallback = p_gcallback;
  p_pattern_config->m_type = type;

  return APR_SUCCESS;
}

/**
 * @brief
 *
 * @param QueryClassifierConfig
 */
void terminateQueryClassifierConfig(QueryClassifierConfig *this) {
  if (this != NULL && this->m_p_pool != NULL) {
    apr_pool_destroy(this->m_p_pool);
  }
}

/**
 * @brief Get the Query Count object
 *
 * @param this
 * @return int
 */
int getQueryCount(const QueryClassifierConfig *this) {
  if (this == NULL) {
    return -1;
  }
  return this->m_array_pattern_configs->nelts;
}

/**
 * @brief
 *
 * @param this
 * @param index
 * @return PatternConfig*
 */
QuerryPattern *atQueryClassifierConfig(const QueryClassifierConfig *this,
                                       int index) {
  if (index < 0 || index >= getQueryCount(this)) {
    return NULL;
  }
  QuerryPattern *pairs = (QuerryPattern *)this->m_array_pattern_configs->elts;
  return &pairs[index];
}
