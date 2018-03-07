#ifndef SENDFILESERVER_H
#define SENDFILESERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QTimer>
#include <QDebug>

namespace Ui {
class SendFileServer;
}

class SendFileServer : public QWidget
{
    Q_OBJECT

public:
    explicit SendFileServer(QWidget *parent = 0);
    ~SendFileServer();

private slots:
    void on_selectBtn_clicked();

    void on_sendBtn_clicked();
public:
    void sendFileData();

private:
    Ui::SendFileServer *ui;
    QTcpServer *m_server;
    QTcpSocket *newSock;
    QFile file;
    QString fileName;
    qint64  fileSize;
    bool isHead;
    QTimer timer;
};

#endif // SENDFILESERVER_H
