#include <njoritus/query_classifier.h>
#include <regex.h>
#include <utilities.h>

/**
 * @brief
 *
 * @param this
 * @param p_main_pool
 * @param cp_config
 * @return apr_status_t
 */
apr_status_t initQueryClassifier(QueryClassifier *this, apr_pool_t *p_main_pool,
                                 const QueryClassifierConfig *cp_config) {
  if (this == NULL || cp_config == NULL) {
    return -1;
  }
  apr_status_t status = initializePool(&this->m_p_pool, p_main_pool);

  if (status != APR_SUCCESS) {
    return status;
  }

  this->m_query_classifier_config = cp_config;

  if (status != APR_SUCCESS) {
    apr_pool_destroy(this->m_p_pool);
    return status;
  }

  return APR_SUCCESS;
}

/**
 * @brief
 *
 * @param this
 */
void terminateQueryClassifier(QueryClassifier *this) {
  if (this != NULL && this->m_p_pool != NULL) {
    apr_pool_destroy(this->m_p_pool);
  }
}

/**
 * @brief
 *
 * @param this
 * @param cp_text
 * @return QueryType
 */
QueryType proccessQuery(QueryClassifier *this, const char *cp_text) {
  if (this == NULL || cp_text == NULL) {
    return QUERY_TYPE_UNKNOWN;
  }

  if (this->m_query_classifier_config == NULL) {
    return QUERY_TYPE_UNKNOWN;
  }

  NjoritusRegex regex;
  emptyInitilizeNjoritusRegex(&regex);

  int size = getQueryCount(this->m_query_classifier_config);

  for (int i = 0; i < size; i++) {
    QuerryPattern *p_query_pattern =
        atQueryClassifierConfig(this->m_query_classifier_config, i);

    if (p_query_pattern == NULL) {
      cleanupNjoritusRegex(&regex);
      return QUERY_TYPE_UNKNOWN;
    }
    recompileNjoritusRegex(&regex, &p_query_pattern->m_pattern_config);
    if (matchNjoritusRegex(&regex, cp_text) == 0) {
      cleanupNjoritusRegex(&regex);
      return p_query_pattern->m_type;
    }
    cleanupNjoritusRegex(&regex);
  }
  return QUERY_TYPE_UNKNOWN;
}

/**
 * @brief
 *
 * @param p_config
 * @param p_classifier
 * @param c_val
 * @return int
 */
int terminateQuerying(QueryClassifierConfig *p_config,
                      QueryClassifier *p_classifier, int c_val) {
  if (p_config != NULL) {
    terminateQueryClassifierConfig(p_config);
  }
  if (p_classifier != NULL) {
    terminateQueryClassifier(p_classifier);
  }
  return c_val;
}

/**
 * @brief
 *
 * @param p_config
 * @param p_classifier
 * @param p_parent_pool
 * @return int
 */
int initializeQuerying(QueryClassifierConfig *p_config,
                       QueryClassifier *p_classifier,
                       apr_pool_t *p_parent_pool) {
  if (p_config == NULL || p_classifier == NULL) {
    return -1;
  }

  int status = initQueryClassifierConfig(p_config, p_parent_pool);
  if (status != APR_SUCCESS) {
    return status;
  }

  status = initQueryClassifier(p_classifier, p_parent_pool,
                               (const QueryClassifierConfig *)p_config);
  if (status != APR_SUCCESS) {
    return terminateQuerying(p_config, NULL, status);
  }
  return status;
}
