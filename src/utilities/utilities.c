#include <utilities.h>

void purgePointer(volatile void *data, size_t len) {

    if(data == NULL) {
        return;
    }

    volatile char *p_vol_data = (volatile char *)data;

    while (len) {
        *p_vol_data++ = 0;
        len--;
    }
}
