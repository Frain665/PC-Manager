#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include <memory>

class DashboardWidget;
struct SystemData;

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void onDataUpdated(const SystemData& data);

private slots:
    void onMenuTriggered();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();

    std::unique_ptr<DashboardWidget> m_dashboardWidget;
};

#endif //MAIN_WINDOW_HPP