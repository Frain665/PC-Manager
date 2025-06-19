#ifndef RAM_MONITOR_H
#define RAM_MONITOR_H

#include <pdh.h>

#include <QObject>
#include <QTimer>
#include <memory>
#include <cstdint>

struct RamInfo {
    uint64_t totalMemory;
    uint64_t usedMemory;
    uint64_t freeMemory;
    double usagePercentage;
    uint64_t totalSwap;
    uint64_t usedSwap;
};

class RamMonitor {
public:
    RamMonitor();

    double getRamUsage();
    RamInfo getRamInfo();

private:
    void updateRamStats();

    RamInfo m_currentInfo;
};

#endif // RAM_MONITOR_H