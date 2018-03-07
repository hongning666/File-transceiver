#include "recvfileclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RecvFileClient w;
    w.show();

    return a.exec();
}
