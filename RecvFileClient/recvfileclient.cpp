#include "recvfileclient.h"
#include "ui_recvfileclient.h"

RecvFileClient::RecvFileClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecvFileClient)
{
    ui->setupUi(this);
    tcpSock = new QTcpSocket(this);
    ui->progressBar->hide();
}

RecvFileClient::~RecvFileClient()
{
    delete ui;
}

void RecvFileClient::on_connectBtn_clicked()
{
    isHead = true;
    QHostAddress srvAddr = QHostAddress(ui->ipEdit->text());
    qint16 srvPort = ui->portEdit->text().toInt();
    tcpSock->connectToHost(srvAddr,srvPort);
    connect(tcpSock,&QTcpSocket::readyRead,
            [=]()
            {
                if(isHead)
                {
                    isHead = false;
                    QByteArray buf;
                    buf = tcpSock->readAll();
                    QString fileInfo = QString(buf);
                    fileName = fileInfo.section("##",0,0);
                    fileSize = fileInfo.section("##",1,1).toLongLong();
                    file.setFileName(fileName);
                    file.open(QIODevice::WriteOnly);
                    readSize = 0;
                    ui->progressBar->setMinimum(0); //最小值
                    ui->progressBar->setMaximum(fileSize/1024); //最大值
                    ui->progressBar->setValue(0); //当前值
                }
                else
                {
                    ui->progressBar->show();
                    qint64 len = 0;
                    char buf[1024*1024] = {0};
                    len = tcpSock->read(buf,sizeof(buf));
                    if(len>0)
                    {
                        len = file.write(buf,len);
                        readSize +=len;
                    }
                    ui->progressBar->setValue(readSize/1024);
                    if(readSize == fileSize)
                    {
                        file.close();
                        QString endMsg = QString("recv file successful");
                        tcpSock->write(endMsg.toUtf8());
                        tcpSock->close();
                        ui->connectBtn->setEnabled(true);
                        ui->progressBar->hide();
                    }
                }
            }
            );
    ui->connectBtn->setEnabled(false);
}

void RecvFileClient::on_progressBar_valueChanged(int value)
{

}
