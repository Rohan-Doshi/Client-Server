#include <QtWidgets>
#include <QtNetwork>
#include <cstring>
#include "sender.h"

Sender::Sender(QWidget *parent)
    : QWidget(parent)
{
    statusLabel = new QLabel(tr("Ready to start the Lab Examination\n\nBroadcasting is carried out on port 45454"));
    statusLabel->setWordWrap(true);

    startButton = new QPushButton(tr("&Start Examination Now"));
    quitButton = new QPushButton(tr("&Stop Monitoring"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    timer = new QTimer(this);

    udpSocket = new QUdpSocket(this);

    connect(startButton, SIGNAL(clicked()), this, SLOT(startBroadcasting()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(stopBroadcasting()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("ABSR_USB_MONITORING_TOOL"));
}

void Sender::startBroadcasting()
{
    startButton->setEnabled(false);
    statusLabel->setText(tr("ABSR_CUSTOM_USB DRIVER Program is getting Loaded on CLIENT Terminals\n"));
    const char *ss = "LOAD_ABSR_DRIVER_UTILITY";
    udpSocket->writeDatagram( ss  ,QHostAddress::Broadcast, 45454);
}
void Sender::stopBroadcasting()
{
    startButton->setEnabled(true);
    statusLabel->setText(tr("Now unloading ABSR_DRIVERS from client systems"));
    const char *ss = "UNLOAD_ABSR_DRIVER_UTILITY";
    udpSocket->writeDatagram( ss  ,QHostAddress::Broadcast, 45454);
}
