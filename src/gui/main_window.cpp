#include "main_window.h"
#include "dashboard_widget.h"
#include "../modules/system_monitor.h"
#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) 
{
    setupUI();
    setupMenuBar();
    setupStatusBar();
}

MainWindow::~MainWindow()
{}

void MainWindow::setupUI() 
{
    m_dashboardWidget = std::make_unique<DashboardWidget>();
    setCentralWidget(m_dashboardWidget.get());

    setWindowTitle("System Monitor");
    resize(800, 600);
}

void MainWindow::setupMenuBar()
{
}

void MainWindow::setupStatusBar()
{
}

void MainWindow::onDataUpdated(const SystemData& data) 
{
    m_dashboardWidget->updateData(data);

    statusBar()->showMessage(
        QString("CPU: %1% | RAM: %2%")
        .arg(data.cpuUsage, 0, 'f', 1)
        .arg(data.ramUsage, 0, 'f', 1)
    );
}