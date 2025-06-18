#ifndef RAM_MONITOR_H
#define RAM_MONITOR_H

#include <pdh.h>

#include <QObject>
#include <QTimer>
#include <memory>

class RAMMonitor : public QObject
{
    Q_OBJECT

public:
    explicit RAMMonitor(QObject* parent = nullptr);
    ~RAMMonitor();

    void startMonitoring(int intervalMs = 1000);
    void stopMonitoring();

    double getTotalRAM() const;    
    double getUsedRAM() const;     
    double getFreeRAM() const;     
    double getRAMUsage() const;    

signals:
    void ramDataUpdated(double totalGB, double usedGB, double freeGB, double usagePercent);

private slots:
    void updateRAMData();

private:
    void fetchRAMData();

    QTimer* m_timer;
    double m_totalRAM;    
    double m_usedRAM;     
    double m_freeRAM;     
    double m_usagePercent;
};

#endif // RAM_MONITOR_H