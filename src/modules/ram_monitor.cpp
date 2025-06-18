#include "ram_monitor.h"

#include <Windows.h>
#include <Psapi.h>
#include <QDebug>

RAMMonitor::RAMMonitor(QObject* parent)
    : QObject(parent),
    m_timer(new QTimer(this)),
    m_totalRAM(0),
    m_usedRAM(0),
    m_freeRAM(0),
    m_usagePercent(0)
{
    connect(m_timer, &QTimer::timeout, this, &RAMMonitor::updateRAMData);
}

RAMMonitor::~RAMMonitor()
{
    stopMonitoring();
}

void RAMMonitor::startMonitoring(int intervalMs)
{
    if (!m_timer->isActive()) 
    {
        m_timer->start(intervalMs);
        updateRAMData(); 
    }
}

void RAMMonitor::stopMonitoring()
{
    if (m_timer->isActive()) 
    {
        m_timer->stop();
    }
}

void RAMMonitor::updateRAMData()
{
    fetchRAMData();
    emit ramDataUpdated(m_totalRAM, m_usedRAM, m_freeRAM, m_usagePercent);
}

void RAMMonitor::fetchRAMData()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);

    m_totalRAM = static_cast<double>(memoryStatus.ullTotalPhys) / (1024 * 1024 * 1024);
    m_freeRAM = static_cast<double>(memoryStatus.ullAvailPhys) / (1024 * 1024 * 1024);
    m_usedRAM = m_totalRAM - m_freeRAM;
    m_usagePercent = memoryStatus.dwMemoryLoad;
}

double RAMMonitor::getTotalRAM() const 
{ 
    return m_totalRAM; 
}

double RAMMonitor::getUsedRAM() const 
{ 
  
    return m_usedRAM; 
}

double RAMMonitor::getFreeRAM() const 
{ 
    return m_freeRAM; 
}

double RAMMonitor::getRAMUsage() const 
{ 
    return m_usagePercent; 
}