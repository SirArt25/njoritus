#ifndef THOR_SHIELD_MJOLNIR_H
#define THOR_SHIELD_MJOLNIR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libsecret/secret.h>


extern const SecretSchema mjolnir;

void securePrint(const char* pData);

#endif // THOR_SHIELD_MJOLNIR_H