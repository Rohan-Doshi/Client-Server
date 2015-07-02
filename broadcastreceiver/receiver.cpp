#include <QtWidgets>
#include <QtNetwork>
#include <cstring>
#include "receiver.h"
using namespace std;
Receiver::Receiver(QWidget *parent)
    : QWidget(parent)
{
    statusLabel = new QLabel(tr("Default usb_storage drivers are currently in used.\nWaiting for administrative commands.\n"));
    statusLabel->setWordWrap(true);

    quitButton = new QPushButton(tr("&Quit"));


    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);



    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("ABSR_USB_CLIENT-SIDE_MONITORING_TOOL"));
}

void Receiver::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
        {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            char *Ddata = datagram.data();
            udpSocket->readDatagram(Ddata, datagram.size());
            statusLabel->setText(Ddata);
            if((string)Ddata == "LOAD_ABSR_DRIVER_UTILITY")
                {
                    Receiver::loader(1);
                }
            else if ((string)Ddata == "UNLOAD_ABSR_DRIVER_UTILITY")
                {
                    Receiver::unloader(1);
                }
        }

}
int Receiver::loader(int flag)
{
    setWindowTitle(tr("LOADED"));
}
int Receiver::unloader(int flag)
{
    setWindowTitle(tr("UNLOADED"));
}
