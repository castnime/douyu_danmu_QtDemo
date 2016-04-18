#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stringgenerator.h"
#include "danmuconfig.h"
#include <QRegExp>
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QPlainTextEdit>



MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    ui->tabWidget->addTab(new QPlainTextEdit(this),QString("连接状态"));
    ui->tabWidget->addTab(new QPlainTextEdit(this),QString("弹幕消息"));
    ui->tabWidget->addTab(new QPlainTextEdit(this),QString("打赏"));

    QPlainTextEdit *edit = static_cast<QPlainTextEdit*>(ui->tabWidget->widget(0));
    edit->setReadOnly(true);
    edit = static_cast<QPlainTextEdit*>(ui->tabWidget->widget(1));
    edit->setReadOnly(true);
    edit = static_cast<QPlainTextEdit*>(ui->tabWidget->widget(2));
    edit->setReadOnly(true);
    edit = NULL;

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
        //ui->plainTextEdit->setPlainText(QString(""));

    }

}


void MainWindow::showChatMessage(QMap<QString,QString> messageMap)
{
    QPlainTextEdit *edit = NULL;
    if(messageMap["type"] == "connectstate")
    {//连接状态
        edit = static_cast<QPlainTextEdit *>(ui->tabWidget->widget(0));
    }
    else if(messageMap["type"] == "chatmsg")
    {//弹幕消息
        edit = static_cast<QPlainTextEdit *>(ui->tabWidget->widget(1));
    }
    else if(messageMap["type"] == "dgb" || messageMap["type"] == "bc_buy_deserve")
    {//打赏消息
        edit = static_cast<QPlainTextEdit *>(ui->tabWidget->widget(2));
    }
    if(edit != NULL)
    {
        edit->appendHtml(StringGenerator::getString(messageMap));
    }

}

void MainWindow::showChatMessageString(QString message)
{

}



