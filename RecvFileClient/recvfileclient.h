#ifndef RECVFILECLIENT_H
#define RECVFILECLIENT_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

namespace Ui {
class RecvFileClient;
}

class RecvFileClient : public QWidget
{
    Q_OBJECT

public:
    explicit RecvFileClient(QWidget *parent = 0);
    ~RecvFileClient();

private slots:
    void on_connectBtn_clicked();
    void on_progressBar_valueChanged(int value);

public:
    void readFileData();
private:
    Ui::RecvFileClient *ui;
    QString fileName;
    qint64  fileSize;
    QFile file;
    QTcpSocket *tcpSock;
    bool isHead;
    qint64 readSize;
};

#endif // RECVFILECLIENT_H
