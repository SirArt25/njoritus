#ifndef THOR_SHIELD_ENC_H
#define THOR_SHIELD_ENC_H

#include <thor-shield/mjolnir.h>

int saveSecret(const char * cpLabel, const char * cpToken,
                 const char * cpSeviceName);

char * readTokenFromFile(const char *pPath);

#endif // THOR_SHIELD_ENC_H
