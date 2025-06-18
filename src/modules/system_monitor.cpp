#include <QStorageInfo>
#include <QDir>
#include <QSysInfo>

#ifdef Q_OS_WINDOWS
#include <windows.h>
#include <psapi.h>
#endif

QVector<double> getCpuUsage() {
    QVector<double> cores;
#ifdef Q_OS_WINDOWS
    PDH_HQUERY query;
    PdhOpenQuery(NULL, NULL, &query);

    for (int i = 0; i < QThread::idealThreadCount(); i++) {
        PDH_HCOUNTER counter;
        wchar_t path[128];
        swprintf(path, L"\\Processor(%d)\\%% Processor Time", i);
        PdhAddCounter(query, path, NULL, &counter);
        PdhCollectQueryData(query);

        PDH_FMT_COUNTERVALUE value;
        PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, NULL, &value);
        cores.append(value.doubleValue);
    }
    PdhCloseQuery(query);
#endif
    return cores;
}

double getMemoryUsage() {
#ifdef Q_OS_WINDOWS
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return (memInfo.ullTotalPhys - memInfo.ullAvailPhys) /
        static_cast<double>(memInfo.ullTotalPhys) * 100.0;
#endif
    return 0.0;
}