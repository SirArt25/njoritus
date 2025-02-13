#ifndef NJORITUS_QUERY_CLASSIFIER_H
#define NJORITUS_QUERY_CLASSIFIER_H

#include <njoritus/query_classifier_config.h>
#include <njoritus/regex.h>
typedef struct {
  apr_pool_t *m_p_pool;
  const QueryClassifierConfig *m_query_classifier_config;
} QueryClassifier;

apr_status_t initQueryClassifier(QueryClassifier *this, apr_pool_t *p_main_pool,
                                 const QueryClassifierConfig *cp_config);

void terminateQueryClassifier(QueryClassifier *this);

QueryType proccessQuery(QueryClassifier *this, const char *cp_text);

int initializeQuerying(QueryClassifierConfig *p_config,
                       QueryClassifier *p_classifier,
                       apr_pool_t *p_parent_pool);
int terminateQuerying(QueryClassifierConfig *p_config,
                      QueryClassifier *p_classifier, int c_val);

#endif // NJORITUS_QUERY_CLASSIFIER_H
