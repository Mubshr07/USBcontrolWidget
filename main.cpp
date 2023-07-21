#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QIODevice>

#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    QCoreApplication::setApplicationName("USB Relay Switch Controller");
    QCoreApplication::setOrganizationName("Mubashir Softwares");
    QCoreApplication::setApplicationVersion("1.0.0");



    QString filePath = "";
    filePath = ":/StyleSheets/AMOLED.qss";
    filePath = ":/StyleSheets/Aqua.qss";
    filePath = ":/StyleSheets/Chatbee.qss";
    filePath = ":/StyleSheets/Combinear.qss";
    //filePath = ":/StyleSheets/ConsoleStyle.qss";
    //filePath = ":/StyleSheets/Devsion.qss";

    filePath = ":/StyleSheets/Diplaytap.qss";

    //    filePath = ":/StyleSheets/ElegantDark.qss";
    //    filePath = ":/StyleSheets/Fibrary.qss";
    //    filePath = ":/StyleSheets/Genetive.qss";
    //    filePath = ":/StyleSheets/Hookmark.qss";
    //filePath = ":/StyleSheets/MacOS.qss";
    //    filePath = ":/StyleSheets/ManjaroMix.qss";
    //    filePath = ":/StyleSheets/MaterialDark.qss";
    //    filePath = ":/StyleSheets/NeonButtons.qss";
    //filePath = ":/StyleSheets/Obit.qss";
    //    filePath = ":/StyleSheets/PicPax.qss";
    //    filePath = ":/StyleSheets/SyNet.qss";
    //    filePath = ":/StyleSheets/Toolery.qss";
    //    filePath = ":/StyleSheets/Ubuntu.qss";
    //    filePath = ":/StyleSheets/VisualScript.qss";
    // filePath = ":/StyleSheets/Wstartpage.qss";


    QString styleSheetString = "";
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)){
        styleSheetString = file.readAll();
        file.close();
    }

    //qDebug()<<"StyleSheet:: "<<styleSheetString;


    MainWindow w;

    if(styleSheetString.length() > 10){
        w.setStyleSheet(styleSheetString);
    }

    w.setWindowIcon(QIcon(":/icons/pakistan Flag rectangle.png"));



    w.show();
    return a.exec();
}
