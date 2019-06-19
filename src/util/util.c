#include <stdio.h>

void util_healthcheck(void)
{
    printf("%s:%s:%u\n", __FILE__, __FUNCTION__, __LINE__);
}
