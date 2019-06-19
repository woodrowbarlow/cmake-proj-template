#include <stdio.h>

#include "config.h"
#include "gui/gui.h"
#include "util/util.h"

int main(int argc, char *argv[])
{
    printf("Example Application %s\n", VERSION_STRING);
    printf("Branch: %s\n", GIT_BRANCH);
    printf("Revision: %s\n", GIT_REVISION);
    gui_start();
    util_healthcheck();
    gui_stop();
    return 0;
}
