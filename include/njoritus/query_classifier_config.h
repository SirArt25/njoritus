#ifndef NJORITUS_QUERY_CLASSIFIER_CONFIG_H
#define NJORITUS_QUERY_CLASSIFIER_CONFIG_H

#include <apr_tables.h>
#include <njoritus/query_types.h>
#include <njoritus/regex_wrapper.h>

typedef int (*SemanticChecker)(const RegexWrapper *, const char *,
                                                            apr_pool_t *);

typedef struct {
    const char *m_p_pattern;
    SemanticChecker m_semantic_checker;
} PatternConfig;

typedef struct {
    PatternConfig m_pattern_config;
    QueryType m_type;
} QuerryPattern;


typedef struct {
    apr_array_header_t *m_array_pattern_configs;
    apr_pool_t * m_p_pool;
} QueryClassifierConfig;

apr_status_t  initQueryClassifierConfig(QueryClassifierConfig *this,
                                                    apr_pool_t *p_main_pool);
apr_status_t addPatternConfig(QueryClassifierConfig *this,
                const char *p_pattern, SemanticChecker checker, QueryType type);
int getQueryCount(const QueryClassifierConfig *this);
QuerryPattern* atQueryClassifierConfig(const QueryClassifierConfig *this,
                                                                int index);
void terminateQueryClassifierConfig(QueryClassifierConfig *this);

#endif // NJORITUS_QUERY_CLASSIFIER_CONFIG_H
