#ifndef CONFIG_H
#define CONFIG_H
#include <QtCore>

/**
 * @brief _Douyu_Room_Pattern 正则匹配
 */
const QString _Douyu_Room_Pattern = "ROOM = (\\{[\\w\\W]+\\});";
const QString _Douyu_Room_Args_Pattern = "ROOM.args = (\\{[\\w\\W]+\\});";
const QString _Douyu_ServerConfig_Pattern = "\\{[\\w\\W]+\\}";
const QString _Douyu_MagicString = "7oE9nPEG9xXV69phU31FYCLUagKeYtsF";
const qint32 _Douyu_CTS_Num = 0xb1020000; //斗鱼客户端到服务端的固定字段

/**
 * @brief _Douyu_RoomId json key集合
 */
const QStringList _Douyu_RoomId = (QStringList()<<"room_id");
const QStringList _Douyu_ServerConfig = (QStringList()<<"server_config");

#endif // CONFIG_H

