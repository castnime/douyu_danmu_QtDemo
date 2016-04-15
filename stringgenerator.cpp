#include "stringgenerator.h"

/**
 * @brief StringGenerator::StringGenerator
 * html字符串生成
 */
StringGenerator::StringGenerator()
{

}

QString StringGenerator::getString(QMap<QString, QString> &messageMap)
{
    QString str = "";
    QString font_color_blue = "#3B91C5";
    QString font_color_red = "#E34945";
    QString font_color_black = "#454545";
    QString font_MS = "Microsoft YaHei";
    QString font_Con = "consolas";

    if(messageMap["type"] == "chatmsg") //聊天
    {
        str = QString("%1 %2 %3 %4").arg(TE(font_color_blue,font_MS,messageMap["nn"]))
                .arg(TE(font_color_red,font_Con,"[lv."+messageMap["level"]+"]"))
                .arg(TE(font_color_blue,font_MS,":"))
                .arg(TE(font_color_black,font_MS,messageMap["txt"]));
     }

    else if(messageMap["type"] == "onlinegift") //领取鱼丸暴击
    {
        str = QString("");
    }
    else if(messageMap["type"] == "dgb") //赠送礼物
    {
        /*-----------------------------------------------------------------------------------
         * gfid    |  50   |     53        |  57       |  52     |  54         |     59     |
         * ---------------------------------------------------------------------------------
         * 表示内容| 100鱼丸|我爱你(520鱼丸)|赞(0.1鱼翅)|666(6鱼翅)|飞机(100鱼翅)|火箭(500鱼翅)|
         * ----------------------------------------------------------------------------------
         *
         */

        int gfid = messageMap["gfid"].toInt();
        QString gfid_str = "";
        switch (gfid) {
        case 50:
            gfid_str = "100鱼丸";
            break;
        case 52:
            gfid_str = "6鱼翅(666)";
            break;
        case 53:
            gfid_str = "520鱼丸(我爱你)";
            break;
        case 54:
            gfid_str = "100鱼翅(飞机)";
            break;
        case 57:
            gfid_str = "0.1鱼翅(赞)";
            break;
        case 59:
            gfid_str = "500鱼翅(火箭)";
            break;
        default:
            gfid_str = "什么鬼?(不清楚)";
            break;
        }
        str = QString("%1 %2 %3").arg(TE(font_color_blue,font_MS,messageMap["nn"]))
                .arg(TE(font_color_black,font_MS,"赠送给主播"))
                .arg(TE(font_color_red,font_Con+","+font_MS,gfid_str));
    }
    else if(messageMap["type"] == "uenter") //特殊身份用户进入房间
    {
    }
    else if(messageMap["type"] == "bc_buy_deserve") //用户赠送酬勤通知消息
    {
        str = QString("%1 %2 %3 %4").arg(TE(font_color_black,font_MS,"酬勤赠送:"))
                .arg(TE(font_color_red,font_MS,"赠送数量:"+messageMap["cnt"]))
                .arg(TE(font_color_blue,font_MS,"酬勤等级:"+messageMap["lev"]))
                .arg(TE(font_color_black,font_MS,"用户信息:"+messageMap["sui"]));
    }
    else
    {
        str = "";
    }
    return str;
}


QString StringGenerator::TE(QString color, QString font_family,QString txt)
{
    return QString("<font style=\"font-family:%1;color:%2\">%3</font>").arg(font_family)
            .arg(color).arg(txt);
}
