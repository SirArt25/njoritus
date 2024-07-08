#ifndef THOR_SHIELD_MJOLNIR_H
#define THOR_SHIELD_MJOLNIR_H

#include <apr.h>
#include <apr_file_io.h>
#include <apr_portable.h>
#include <libsecret/secret.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const SecretSchema MJOLNIR;

int secureExport(apr_pool_t *p_parent_pool, char *p_data, const char *p_path);

#endif // THOR_SHIELD_MJOLNIR_H
