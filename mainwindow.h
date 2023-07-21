#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>
#include <cstring>
#include <QChar>
#include <uchar.h>

#include <QTimer>
#include <QDateTime>
#include <usb_relay_dll/usb_relay_device.h>

#include <QMessageBox>

#include "qdebug.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onTimerClockElapsed();

private slots:
    void on_pbFindDevices_clicked();

    void on_pbOpenSelectedDevices_clicked();
    void on_pbCloseSelectedDevices_clicked();
    void on_pbOpenRelay1_clicked();
    void on_pbCloseRelay1_clicked();
    void on_pbOpenRelay2_clicked();
    void on_pbCloseRelay2_clicked();


private:
    Ui::MainWindow *ui;

    QTimer *timerClock;
    //usb_relay_device_info *devices;
    usb_relay_device_info *selectedDevice;

    QMap<QString, usb_relay_device_info*>deviceMap;
    int deviceHandler;


    bool m_bOpened = false;


    /*****************************/
    struct usb_relay_device_info *m_pDeviceList;
    //int m_hCurDevice;
    int m_hCureDeviceIndex;


};
#endif // MAINWINDOW_H
