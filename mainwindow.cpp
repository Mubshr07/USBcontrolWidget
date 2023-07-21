#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    timerClock = new QTimer(this);
    connect(timerClock, SIGNAL(timeout()), this, SLOT(onTimerClockElapsed()));
    timerClock->start(1000);

    this->setWindowTitle("Mubashir Softwares");


    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::Drawer);

    this->setAttribute(Qt::WA_DeleteOnClose);


    usb_relay_init();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimerClockElapsed()
{
    ui->lblDate->setText(QDateTime::currentDateTime().toString("dd MMM yyyy"));
    ui->lblTime->setText(QDateTime::currentDateTime().toString("HH:mm:ss"));
}





void MainWindow::on_pbFindDevices_clicked()
{
    if (m_bOpened)
    {
        QMessageBox::information(this, "Attention", "Close Current Device First");
        return;
    }

    /*
    if (m_pDeviceList)
    {
        qDebug()<<"usb_relay_device_free_enumerate. ";
        usb_relay_device_free_enumerate(m_pDeviceList);
        m_pDeviceList = NULL;
    }
    */
    //qDebug()<<"Devices List Clear. ";

    m_pDeviceList = usb_relay_device_enumerate();

    ui->cmbListDevices->clear();

    if (m_pDeviceList)
    {
        int indx = 1;
        struct usb_relay_device_info *cur_device = m_pDeviceList;
        while (cur_device)
        {
            qDebug()<<indx<<" -> Device Sr:: "<<QString((char*) cur_device->serial_number)<<"  Type:"<<cur_device->type<<"  Path:"<<cur_device->device_path;

            ui->cmbListDevices->addItem(QString((char*) cur_device->serial_number));
            deviceMap.insert(QString((char*) cur_device->serial_number), cur_device);
            cur_device = cur_device->next;
            indx++;
        }
    }



}
void MainWindow::on_pbOpenSelectedDevices_clicked()
{
    if (m_bOpened)
    {
        QMessageBox::information(this, "Attention", "Close Current Device First");
        return;
    }

    if (deviceMap.isEmpty())
    {
        QMessageBox::information(this, "Attention", "Devices are not found.");
        return;
    }
    if (ui->cmbListDevices->currentText().length() < 2)
    {
        QMessageBox::information(this, "Attention", "Valid device not selected.");
        return;
    }

    selectedDevice = deviceMap.value(ui->cmbListDevices->currentText());

    qDebug()<<"Selected Device Sr:: "<<QString((char*) selectedDevice->serial_number)<<"  Type:"<<selectedDevice->type<<"  Path:"<<selectedDevice->device_path;



    //1. open usb relay device
    deviceHandler = usb_relay_device_open(selectedDevice);
    qDebug()<<"Device handler:: "<<deviceHandler;


    if (deviceHandler)
    {
        //2. Get status
        unsigned int status = 0;
        if (0 == usb_relay_device_get_status(deviceHandler, &status))
        {
            ui->lblDeviceStatus->setStyleSheet("color: lime; font-weight: 700;");
            ui->lblDeviceStatus->setText("Opened");
            m_bOpened = true;
            //m_hCureDeviceIndex = fd->second->type;
        }
        else
        {
            usb_relay_device_close(deviceHandler);

            ui->lblDeviceStatus->setStyleSheet("color: red; font-weight: 700;");
            ui->lblDeviceStatus->setText("Closed");
            deviceHandler = 0;
            QMessageBox::information(this,"Error", "Open Device Error!!");
        }

    }
    else
    {
        QMessageBox::information(this,"Error", "Open Device Error!!" );
    }



}
void MainWindow::on_pbCloseSelectedDevices_clicked()
{
    if (!m_bOpened)
    {
        QMessageBox::information(this,"Error", "Open Device First");
        return;
    }

    m_bOpened = false;

    usb_relay_device_close(deviceHandler);

    ui->lblDeviceStatus->setStyleSheet("color: maroon; font-weight: 700;");
    ui->lblDeviceStatus->setText("Closed");
    deviceHandler = 0;
}


void MainWindow::on_pbOpenRelay1_clicked()
{
    if (!m_bOpened)
    {
        QMessageBox::information(this,"Error", "Open Device First");
        return;
    }

    int ret = usb_relay_device_open_one_relay_channel(deviceHandler, 1);
    if (ret == 0)
    {
        ui->lblRelay1_Status->setStyleSheet("background-color:lime;padding-left: 10px; color: black;");
    }

}
void MainWindow::on_pbCloseRelay1_clicked()
{
    if (!m_bOpened)
    {
        QMessageBox::information(this,"Error", "Open Device First");
        return;
    }
    int ret =  usb_relay_device_close_one_relay_channel(deviceHandler, 1);
    if (ret == 0)
    {
        ui->lblRelay1_Status->setStyleSheet("background-color:maroon;padding-left: 10px; color: black;");
    }
}


void MainWindow::on_pbOpenRelay2_clicked()
{
    if (!m_bOpened)
    {
        QMessageBox::information(this,"Error", "Open Device First");
        return;
    }

    int ret = usb_relay_device_open_one_relay_channel(deviceHandler, 2);
    if (ret == 0)
    {
        ui->lblRelay2_Status->setStyleSheet("background-color:lime;padding-left: 10px; color: black;");
    }
}
void MainWindow::on_pbCloseRelay2_clicked()
{
    if (!m_bOpened)
    {
        QMessageBox::information(this,"Error", "Open Device First");
        return;
    }
    int ret =  usb_relay_device_close_one_relay_channel(deviceHandler, 2);
    if (ret == 0)
    {
        ui->lblRelay2_Status->setStyleSheet("background-color:maroon;padding-left: 10px; color: black;");
    }
}

