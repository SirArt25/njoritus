#ifndef THOR_SHIELD_MJOLNIR_H
#define THOR_SHIELD_MJOLNIR_H

#include <apr.h>
#include <apr_file_io.h>
#include <apr_portable.h>
#include <keyutils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int secureExport(apr_pool_t *p_parent_pool, char *p_data, const char *p_path);
int deleteKey(const char *cp_service_name);

#endif // THOR_SHIELD_MJOLNIR_H
