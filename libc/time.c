#define __OE_NEED_TIME_CALLS
#define _GNU_SOURCE
#include <sys/time.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <openenclave/enclave.h>
#include <openenclave/bits/calls.h>

time_t time(time_t *tloc)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
        return (time_t)-1;

    if (tloc)
        *tloc = tv.tv_sec;

    return tv.tv_sec;
}

#if 0
int gettimeofday(struct timeval* tv, struct timezone* tz)
#else
int gettimeofday(struct timeval* tv, void* tz)
#endif
{
    size_t ret = -1;
    OE_GettimeofdayArgs* args = NULL;

    if (!(args = OE_HostCalloc(1, sizeof(OE_GettimeofdayArgs))))
        goto done;

    args->ret = -1;

    if (tv)
        args->tv = &args->tvbuf;

    if (tz)
        args->tz = NULL;

    if (__OE_OCall(OE_FUNC_GETTIMEOFDAY, (uint64_t)args, NULL) != OE_OK)
        goto done;

    if (args->ret == 0)
    {
        if (tv)
            memcpy(tv, &args->tvbuf, sizeof(args->tvbuf));

        if (tz)
            memcpy(tz, &args->tzbuf, sizeof(args->tzbuf));
    }

    ret = args->ret;

done:

    if (args)
        OE_HostFree(args);

    return ret;
}

int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
    size_t ret = -1;
    OE_ClockgettimeArgs* args = NULL;

    if (!(args = OE_HostMalloc(sizeof(OE_ClockgettimeArgs))))
        goto done;

    args->ret = -1;
    args->tp = tp ? &args->tpbuf : NULL;

    if (__OE_OCall(OE_FUNC_CLOCK_GETTIME, (uint64_t)args, NULL) != OE_OK)
        goto done;

    if (args->ret == 0)
    {
        if (tp)
            memcpy(tp, &args->tpbuf, sizeof(args->tpbuf));
    }

    ret = args->ret;

done:

    if (args)
        OE_HostFree(args);

    return ret;
}

size_t strftime(
    char *str, 
    size_t max, 
    const char *format, 
    const struct tm *tm)
{
    size_t ret = 0;
    OE_StrftimeArgs* a = NULL;

    if (!str || !format || !tm)
        goto done;

    if (!(a = OE_HostCalloc(1, sizeof(OE_StrftimeArgs))))
        goto done;

    if (strlcpy(a->format, format, sizeof(a->format)) >= sizeof(a->format))
        goto done;

    memcpy(&a->tm, tm, sizeof(struct tm));

    if (__OE_OCall(OE_FUNC_STRFTIME, (uint64_t)a, NULL) != OE_OK)
        goto done;

    if (strlcpy(str, a->str, max) >= max)
    {
        *str = '\0';
        goto done;
    }

    ret = a->ret;

done:

    if (a)
        OE_HostFree(a);

    return ret;
}

size_t strftime_l(
    char *s,
    size_t max,
    const char *format,
    const struct tm *tm,
    locale_t loc)
{
    return strftime(s, max, format, tm);
}

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    size_t ret = -1;
    OE_NanosleepArgs* args = NULL;

    if (!(args = OE_HostCalloc(1, sizeof(OE_NanosleepArgs))))
        goto done;

    args->ret = -1;

    if (req)
    {
        memcpy(&args->reqbuf, req, sizeof(args->reqbuf));
        args->req = &args->reqbuf;
    }

    if (rem)
        args->rem = &args->rembuf;

    if (__OE_OCall(OE_FUNC_NANOSLEEP, (uint64_t)args, NULL) != OE_OK)
        goto done;

    if (args->ret == 0)
    {
        if (rem)
            memcpy(rem, &args->rembuf, sizeof(args->rembuf));
    }

    ret = args->ret;

done:

    if (args)
        OE_HostFree(args);

    return ret;
}
