#include "cpuTimer.h"

double getCpuTime()
{
#ifdef _WIN32
    LARGE_INTEGER freq, start;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    return (double)(start.QuadPart) / (double)freq.QuadPart;

#elif __APPLE__ && __MACH__
    // macOS : Use mach_task_basic_info to get user time
    mach_task_basic_info_data_t info;
    mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO < (task_info_t)&info, &count) == KERN_SUCCESS)
    {
        return (double)info.user_time.seconds + (double)info.user_time.microseconds / 1000000.0;
    }
    return 0.0; // Return 0 on error
#elif __linux__
    // Linux: Use getrusage to get user time
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return (double)usage.ru_utime.tv_sec + (double)usage.ru_utime.tv_usec / 1000000.0;

#else
    // Fallback for other platforms
    return 0.0;

#endif
}