#include <stdio.h>
#include <stdlib.h>

extern "C" {

bool rDebugAssertFail_Implementation(const char* condition, const char* file, unsigned int line)
{
    printf("ASSERT FAILED: %s at %s:%u\n", condition, file, line);
    return true; // Continuar o romper depende del handler
}

void rReleaseBreak()
{
    printf("RELEASE BREAK\n");
    // En PS3 podríamos usar un trap o simplemente exit
    exit(1);
}

}
