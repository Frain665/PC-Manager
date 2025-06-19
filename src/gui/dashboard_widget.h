#ifndef DASHBOARD_WIDGET_HPP
#define DASHBOARD_WIDGET_HPP

#include <modules/system_monitor.h>
#include <QWidget>
#include <QGridLayout>
#include <memory>

class QProgressBar;
class QLabel;
class QChart;
struct SystemData;

class DashboardWidget : public QWidget 
{
    Q_OBJECT

public:
    DashboardWidget(QWidget* parent = nullptr);

    void updateData(const SystemData& data);

private:
    void setupLayout();
    void createCpuWidget();
    void createRamWidget();
    void createDiskWidget();
    void createGpuWidget();

    std::unique_ptr<QGridLayout> m_layout;

    QProgressBar* m_cpuProgressBar;
    QLabel* m_cpuLabel;

    QProgressBar* m_ramProgressBar;
    QLabel* m_ramLabel;

    QProgressBar* m_diskProgressBar;
    QLabel* m_diskLabel;

    QProgressBar* m_gpuProgressBar;
    QLabel* m_gpuLabel;

    QChart* m_cpuChart;
    QChart* m_ramChart;
};

#endif //DASHBOARD_WIDGET_HPP