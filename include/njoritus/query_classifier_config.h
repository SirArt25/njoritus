#ifndef NJORITUS_QUERY_CLASSIFIER_CONFIG_H
#define NJORITUS_QUERY_CLASSIFIER_CONFIG_H

#include <apr_tables.h>
#include <njoritus/query_types.h>

typedef struct {
    const char *m_p_pattern;
    QueryType type;
} PatternTypePair;


typedef struct {
    apr_array_header_t *m_p_pairs_pattern_type;
    apr_pool_t * m_p_pool;
} QueryClassifierConfig;

apr_status_t  initQueryClassifierConfig(QueryClassifierConfig *this, apr_pool_t *p_main_pool);
apr_status_t addPatternTypePair(QueryClassifierConfig *this, const char *p_pattern, QueryType type);
int getQueryCount(const QueryClassifierConfig *this);
PatternTypePair* atQueryClassifierConfig(const QueryClassifierConfig *this, int index);
void terminateQueryClassifierConfig(QueryClassifierConfig *this);

#endif // NJORITUS_QUERY_CLASSIFIER_CONFIG_H
