#ifndef THOR_SHIELD_ENC_H
#define THOR_SHIELD_ENC_H

#include <mjolnir.h>

int saveSecret(const char * cp_label, const char * cp_token,
                 const char * cp_service_name);

char * readTokenFromFile(apr_pool_t *p_parent_pool, const char *p_path);

#endif // THOR_SHIELD_ENC_H
