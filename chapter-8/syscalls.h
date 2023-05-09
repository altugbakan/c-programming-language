#if defined(__linux__) || defined(__APPLE__)
#include <sys/syscall.h>
#include <unistd.h>
#elif _WIN32
#include <io.h>
#endif

#include <fcntl.h>
