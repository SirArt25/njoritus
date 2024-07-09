#ifndef NJORD_CORE_H
#define NJORD_CORE_H

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int initialize();
int initializeAPR();
void handleSigint(int sig);

#endif // NJORD_CORE_H
