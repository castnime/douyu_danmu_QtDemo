#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stringgenerator.h"
#include "danmuconfig.h"
#include <QRegExp>



MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    network_access = new NetworkAccess();
    tcpSocket = new DouyuTcpSocket(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(start()));
    connect(network_access,SIGNAL(pageLoadFinished(QString)),
            this,SLOT(htmlContent(QString)));
    //connect(tcpSocket,SIGNAL(chatMessageString(QString)),this,SLOT(showChatMessageString(QString)));
    connect(tcpSocket,SIGNAL(chatMessage(QMap<QString,QString>)),this,SLOT(showChatMessage(QMap<QString,QString>)));
}

MainWindow::~MainWindow()
{
    delete tcpSocket;
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
        bool ok = false;
        roomid.toInt(&ok);
        if(!ok)
        {
            QString url_str = QString("http://www.douyu.com/%1").arg(roomid);
            QUrl url = QUrl(QString(url_str));
            network_access->loadingPage(url);
        }
        else
        {
            tcpSocket->connectDanmuServer(roomid);
        }
    }
    else
    {
        ui->lineEdit_roomid->setText(QString(""));
    }
}


void MainWindow::htmlContent(const QString html)
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
    if(parse.init(json))
    {
        QString roomid = parse.getJsonValue(_Douyu_RoomId);
        tcpSocket->connectDanmuServer(roomid);
    }
    else
    {
        ui->lineEdit_roomid->setText(QString(""));
        ui->lineEdit_roomid->setPlaceholderText("加载失败");
        ui->plainTextEdit->setPlainText(QString(""));
    }

}

void MainWindow::showChatMessage(QMap<QString,QString> messageMap)
{
    /*QString nickname = messageMap["nn"];
    QString level = messageMap["level"];
    QString txt = messageMap["txt"];
    QString message = QString("<font style=\"color:#3B91C5;font-family:Microsoft YaHei\">%1</font> <font style=\"color:#E34945;font-family:consolas\">[lv.%2]</font><font style=\"color:#3B91C5;font-family:Microsoft YaHei\">:</font> <font style=\"color:#454545;font-family:Microsoft YaHei\">%3</font>").arg(nickname).arg(level).arg(txt);
    */
    ui->plainTextEdit->appendHtml(StringGenerator::getString(messageMap));
}

void MainWindow::showChatMessageString(QString message)
{

    ui->plainTextEdit->appendPlainText(message);
}
