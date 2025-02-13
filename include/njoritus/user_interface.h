#ifndef NJORITUS_USER_INTERFACE_H
#define NJORITUS_USER_INTERFACE_H

#include <apr.h>
#include <apr_file_io.h>
#include <apr_portable.h>
#include <njoritus/bot.h>
#include <njoritus/query_classifier.h>
#include <njoritus/semantic_checkers/cordinate_checker.h>
#include <utilities.h>

int manageNjoritusBot(apr_pool_t *p_parent_pool);

#endif // NJORITUS_USER_INTERFACE_H
