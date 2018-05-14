#include "myserialport.h"
#include <QSerialPort>
#include <QtSerialPort/QSerialPort>
#include <QObject>
#include <QTextStream>

MySerialPort::MySerialPort()
{
    serial = new QSerialPort(this);
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    openSerialPort();
}


void MySerialPort::openSerialPort()
{
    //QString portName = "/dev/ttyUSB0";
    QString portName = "/dev/Winsock";
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        serial->flush();
        showStatusMessage("Connectedd");

    } else {

        showStatusMessage(tr("Open error"));
    }
}

void MySerialPort::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();

    showStatusMessage(tr("Disconnected"));
}

void MySerialPort::writeData(const QByteArray &data)
{
    const qint64 bytesWritten = serial->write(data);
}

void MySerialPort::readData()
{
   QByteArray data = serial->readAll();

   QTextStream(stdout) << data << endl;

}

void MySerialPort::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        closeSerialPort();
    }
}


void MySerialPort::showStatusMessage(const QString &message)
{
   QTextStream(stdout) << message << endl;
}
