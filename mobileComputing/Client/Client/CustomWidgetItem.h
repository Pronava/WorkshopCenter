// CustomWidgetItem.h

#ifndef CUSTOMWIDGETITEM_H
#define CUSTOMWIDGETITEM_H

#include <QListWidgetItem>

struct RoomInfo {
    QString room_id;
    int port;
    int state;
    QString group;
};

class CustomWidgetItem : public QListWidgetItem
{
public:
    CustomWidgetItem(const RoomInfo &info, QListWidget *view = nullptr)
        : QListWidgetItem(info.group, view), roomInfo(info) {}

    RoomInfo getRoomInfo() const { return roomInfo; }

private:
    RoomInfo roomInfo;
};

#endif // CUSTOMWIDGETITEM_H
