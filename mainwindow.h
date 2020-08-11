#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qsystemtrayicon.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void changeEvent(QEvent* e) override;
    void closeEvent(QCloseEvent* e) override;


private:
    void createAction();
    void createMenu();

private slots:
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void timerIsTrigger();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon* m_SystemTrayIcon;
    QMenu* m_menu;
    QAction* m_QactionShowMain;
    QAction* m_QactionExitApp;
    QTimer *m_lastTimer;
    int remainTime;
    int realTime;
};
#endif // MAINWINDOW_H
