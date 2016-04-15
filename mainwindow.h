#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networkaccess.h"
#include "jsonparse.h"
#include "douyutcpsocket.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void htmlContent(const QString html);
    void showChatMessage(QMap<QString, QString>);
    void showChatMessageString(QString message);
    void start();
private:
    Ui::MainWindow *ui;
    NetworkAccess *network_access;
    DouyuTcpSocket *tcpSocket;
};

#endif // MAINWINDOW_H
