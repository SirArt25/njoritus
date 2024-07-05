#ifndef THOR_SHIELD_MJOLNIR_H
#define THOR_SHIELD_MJOLNIR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsecret/secret.h>
#include <apr.h>
#include <apr_file_io.h>
#include <apr_portable.h>

extern const SecretSchema mjolnir;

int secureExport(apr_pool_t *p_parent_pool, char* p_data,
                const char *p_path);

#endif // THOR_SHIELD_MJOLNIR_H
