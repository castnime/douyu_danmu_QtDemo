#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "danmuconfig.h"
#include <QRegExp>



MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    network_access = new NetworkAccess();
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(start()));
    connect(network_access,SIGNAL(pageLoadFinished(QString)),
            this,SLOT(htmlContent(QString)));

}

MainWindow::~MainWindow()
{
    delete network_access;
    delete ui;
}

void MainWindow::start()
{
    QString roomid = (ui->lineEdit_roomid->text()).trimmed();
    QRegExp rx("[0-9a-zA-Z]+");
    rx.setMinimal(false);
    if(rx.exactMatch(roomid))
    {
        QString url_str = QString("http://www.douyu.com/%1").arg(roomid);
        QUrl url = QUrl(QString(url_str));
        network_access->loadingPage(url);
    }
    else
    {
        ui->lineEdit_roomid->setText(QString(""));
    }
}


void MainWindow::htmlContent(const QString &html)
{
    //正则数据提取JSON
    QString pattern = _Douyu_Room_Pattern;
    QRegExp regExp(pattern);
    regExp.setMinimal(true);
    QString json;
    int pos = 0;
    while((pos = regExp.indexIn(html,pos)) != -1)
    {
        json = regExp.capturedTexts().at(1);
        pos += regExp.matchedLength();
    }
    JSONParse parse;
    parse.init(json);
    QString roomid = parse.getJsonValue(_Douyu_RoomId);

    DouyuTcpSocket *tcpSocket = new DouyuTcpSocket(this);
    tcpSocket->connectDanmuServer(roomid);

    connect(tcpSocket,SIGNAL(chatMessage(QMap<QString,QString>)),this,SLOT(showChatMessage(QMap<QString,QString>)));


}

void MainWindow::showChatMessage(QMap<QString,QString> messageMap)
{
    QString nickname = messageMap["nn"];
    QString level = messageMap["level"];
    QString txt = messageMap["txt"];
    QString message = QString("[%1] [lv.%2]:   %3").arg(nickname).arg(level).arg(txt);
    ui->plainTextEdit->appendPlainText(message);
}
