#include "sendfileserver.h"
#include "ui_sendfileserver.h"
#include <QHostAddress>

SendFileServer::SendFileServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendFileServer)
{
    ui->setupUi(this);
    isHead = true;
    m_server = new QTcpServer(this);
    m_server->listen(QHostAddress::Any,8888);
    ui->selectBtn->setEnabled(false);
    ui->sendBtn->setEnabled(false);
    connect(m_server,&QTcpServer::newConnection,
    [=]()
    {
        newSock = m_server->nextPendingConnection();
        QHostAddress peerAddr = newSock->peerAddress();
        QString conMsg = QString("[%1]connect successful!").arg(peerAddr.toString());
        ui->textEdit->append(conMsg);
        ui->selectBtn->setEnabled(true);
        connect(newSock,&QTcpSocket::readyRead,
                [=]()
                {
                    QByteArray recvMsg = newSock->readAll();
                    if(QString(recvMsg) == "recv file successful")
                    {
                        newSock->disconnectFromHost();
                        newSock->close();
                        ui->selectBtn->setEnabled(false);
                        ui->sendBtn->setEnabled(false);
                    }
                }
                );
    }
    );
    connect(&timer,&QTimer::timeout,
            [=]()
            {
                timer.stop();
                sendFileData();
            }
            );
}

SendFileServer::~SendFileServer()
{
    delete ui;
}

void SendFileServer::on_selectBtn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Select file","./");
    QFileInfo info = QFileInfo(filePath);
    fileName = info.fileName();
    fileSize = info.size();
    if(!fileName.isEmpty())
    {
        file.setFileName(filePath);
        file.open(QIODevice::ReadOnly);
        ui->sendBtn->setEnabled(true);
    }
}

void SendFileServer::on_sendBtn_clicked()
{
   QString headMsg = QString("%1##%2").arg(fileName).arg(fileSize);
   qint32 len = newSock->write(headMsg.toUtf8());
   if(len>0)
   {
       timer.start(1000);
   }
}

void SendFileServer::sendFileData()
{
    ui->textEdit->append("Sending file now...");
    qint64 sendSize = 0;
    qint64 len;
    do
    {
        len = 0;
        char buf[1024*1024] = {0};
        len = file.read(buf,sizeof(buf));
        qDebug()<<"len="<<len;
        if(len>0)
        {
            len = newSock->write(buf,len);
            qDebug()<<"len="<<len;
            if(len>0)
                sendSize +=len;
        }

    }while(len>0);
    if(sendSize == fileSize){
        ui->textEdit->append("send file finished");
        file.close();
    }
}
