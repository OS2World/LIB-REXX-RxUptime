#define INCL_DOSPROCESS
#define INCL_DOSPROFILE
#define INCL_DOSMISC
#define INCL_DOSERRORS
#define INCL_REXXSAA
#define INCL_RXFUNC
#include <os2.h>
#include <rexxsaa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RETURN_INVALID                   40
#define RETURN_OK                        0

RexxFunctionHandler RxMSCount;
RexxFunctionHandler RxTmrTime;
RexxFunctionHandler RxTmrFreq;
RexxFunctionHandler RxLoadUptime;
RexxFunctionHandler RxDropUptime;

ULONG RxMSCount(CHAR *name,
                ULONG numargs,
                RXSTRING args[],
                CHAR *qjunk,
                RXSTRING *rstring)
{
    ULONG msecs;
    APIRET rc;

    rc=DosQuerySysInfo(QSV_MS_COUNT, QSV_MS_COUNT, &msecs, sizeof(msecs));

    if (rc!=NO_ERROR)
        {
        strcpy(rstring->strptr, "-1");
        rstring->strlength=2;
        }
    else
        {
        char nbuf[13];

        sprintf(nbuf, "%u", msecs);

        strcpy(rstring->strptr, nbuf);
        rstring->strlength=strlen(nbuf);
        }

    return RETURN_OK;
}

ULONG RxTmrFreq(CHAR *name,
                ULONG numargs,
                RXSTRING args[],
                CHAR *qjunk,
                RXSTRING *rstring)
{
    ULONG tmFreq;
    APIRET rc;

    rc=DosTmrQueryFreq(&tmFreq);

    if (rc!=NO_ERROR)
        {
        strcpy(rstring->strptr, "-1");
        rstring->strlength=2;
        }
    else
        {
        char nbuf[13];

        sprintf(nbuf, "%u", tmFreq);

        strcpy(rstring->strptr, nbuf);
        rstring->strlength=strlen(nbuf);
        }

    return RETURN_OK;
}

ULONG RxTmrTime(CHAR *name,
                ULONG numargs,
                RXSTRING args[],
                CHAR *qjunk,
                RXSTRING *rstring)
{
    QWORD tmVal;
    APIRET rc;

    rc=DosTmrQueryTime(&tmVal);

    if (rc!=NO_ERROR)
        {
        strcpy(rstring->strptr, "-1");
        rstring->strlength=2;
        }
    else
        {
        char nbuf[27];

        sprintf(nbuf, "%u %u", tmVal.ulHi, tmVal.ulLo);

        strcpy(rstring->strptr, nbuf);
        rstring->strlength=strlen(nbuf);
        }

    return RETURN_OK;
}

ULONG RxLoadUptime(CHAR *name,
                   ULONG numargs,
                   RXSTRING args[],
                   CHAR *qjunk,
                   RXSTRING *rstring)
{
    APIRET rc;

    rc=RexxRegisterFunctionExe("RxMSCount",RxMSCount);
    rc=RexxRegisterFunctionExe("RxTmrTime",RxTmrTime);
    rc=RexxRegisterFunctionExe("RxTmrFreq",RxTmrFreq);
    rc=RexxRegisterFunctionExe("RxLoadUptime",RxLoadUptime);
    rc=RexxRegisterFunctionExe("RxDropUptime",RxDropUptime);

    if (rc==RXFUNC_NOMEM)
        return RETURN_INVALID;

    return RETURN_OK;
}

ULONG RxDropUptime(CHAR *name,
                   ULONG numargs,
                   RXSTRING args[],
                   CHAR *qjunk,
                   RXSTRING *rstring)
{
    RexxDeregisterFunction("RxMSCount");
    RexxDeregisterFunction("RxTmrFreq");
    RexxDeregisterFunction("RxTmrTime");
    RexxDeregisterFunction("RxLoadUptime");
    RexxDeregisterFunction("RxDropUptime");

    return RETURN_OK;
}
