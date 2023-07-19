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
    devices = usb_relay_device_enumerate();

    while(devices != nullptr || devices != NULL) {
        ui->cmbListDevices->addItem(QString::fromUtf8((char*)devices->serial_number));
        deviceMap->insert(devices->serial_number, devices);
        devices = devices->next;
    }


    qDebug()<<" Total Devices:: "<<devices;


}
void MainWindow::on_pbOpenSelectedDevices_clicked()
{
    unsigned char *selectedSerialNo = (unsigned char*) (ui->cmbListDevices->currentText().toUtf8().data());
    selectedDevice = deviceMap->value(selectedSerialNo);
    deviceHandler = usb_relay_device_open(selectedDevice);

}
void MainWindow::on_pbCloseSelectedDevices_clicked()
{
    usb_relay_device_close(deviceHandler);
}


void MainWindow::on_pbOpenRelay1_clicked()
{
    usb_relay_device_open_one_relay_channel(deviceHandler, 0);
}
void MainWindow::on_pbCloseRelay1_clicked()
{
    usb_relay_device_close_one_relay_channel(deviceHandler, 0);
}


void MainWindow::on_pbOpenRelay2_clicked()
{
    usb_relay_device_open_one_relay_channel(deviceHandler, 0);
}
void MainWindow::on_pbCloseRelay2_clicked()
{
    usb_relay_device_close_one_relay_channel(deviceHandler, 1);
}

