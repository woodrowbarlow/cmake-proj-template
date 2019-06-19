#include <stdio.h>

void gui_start(void)
{
    printf("%s:%s:%u\n", __FILE__, __FUNCTION__, __LINE__);
}

void gui_stop(void)
{
    printf("%s:%s:%u\n", __FILE__, __FUNCTION__, __LINE__);
}
