

#pragma once
#include <QApplication>
#include <QTimer>
#include <memory>

#include <gui/main_window.h>

class MainWindow;
class SystemMonitor;

class App : public QApplication {
    Q_OBJECT

public:
    App(int argc, char* argv[]);
    ~App();

    int run();
    void shutdown();

private slots:
    void updateData();

private:
    std::unique_ptr<MainWindow> m_mainWindow;
    std::unique_ptr<SystemMonitor> m_systemMonitor;
    std::unique_ptr<QTimer> m_updateTimer;

    void setupConnections();
    void startMonitoring();
};