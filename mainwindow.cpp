#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <qtimer.h>
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("定时时钟"));
	setWindowIcon(QIcon(":/new/prefix1/img/138.jpg"));
	m_SystemTrayIcon = new QSystemTrayIcon();
	m_SystemTrayIcon->setIcon(QIcon(":/new/prefix1/img/138.jpg"));
	m_SystemTrayIcon->setToolTip(QString::fromLocal8Bit("测试时钟图标"));
	connect(m_SystemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

	connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
		int wantMin = ui->lineEdit->text().toInt();
		int wantSecond = ui->lineEdit_2->text().toInt();
		int wantTime = wantMin * 60 + wantSecond;
		remainTime = wantTime > 0 ? wantTime : 60 * 60;
		realTime = remainTime;
		if (m_lastTimer->isActive()) {
			m_lastTimer->stop();
		}
		m_lastTimer->start();
		});

	createAction();
	createMenu();
	m_SystemTrayIcon->show();
	m_lastTimer = new QTimer();
	m_lastTimer->setInterval(1000);
	connect(m_lastTimer, &QTimer::timeout, this, &MainWindow::timerIsTrigger);
}

MainWindow::~MainWindow()
{
	delete ui;
}
void MainWindow::timerIsTrigger()
{
	remainTime -= 1;
	if (remainTime <= 0) {
		m_SystemTrayIcon->showMessage("CLOCK", QString::fromLocal8Bit("%1分%2秒时间到了").arg(realTime / 60).arg(realTime%60), QSystemTrayIcon::MessageIcon::Information, 60000);
		remainTime = 0;
		m_lastTimer->stop();
	}
	int min = remainTime / 60;
	int secons = remainTime % 60;
	ui->remainLabel->setText(QString::fromLocal8Bit("剩余%1分%2秒").arg(min).arg(secons));
}


void MainWindow::changeEvent(QEvent* e)
{
	if ((e->type() == QEvent::WindowStateChange) && this->isMinimized())
	{
		QTimer::singleShot(100, this, SLOT(close));
	}
}

void MainWindow::closeEvent(QCloseEvent*) {
}

void MainWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason) {
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		this->show();
		break;
	default:
		break;
	}
}

void MainWindow::createAction()
{
	m_QactionShowMain = new QAction(QString::fromLocal8Bit("显示主页面"), this);
	connect(m_QactionShowMain, &QAction::triggered, this, [=]() {
		this->show();
		});

	m_QactionExitApp = new QAction(QString::fromLocal8Bit("退出程序"), this);
	connect(m_QactionExitApp, &QAction::triggered, this, [=]() {exit(0); });
}

void MainWindow::createMenu()
{
	m_menu = new QMenu(this);
	m_menu->addAction(m_QactionShowMain);
	m_menu->addSeparator();
	m_menu->addAction(m_QactionExitApp);
	m_SystemTrayIcon->setContextMenu(m_menu);
}

