#include "clientcontroller.h"


//添加好友的请求 以及反馈
void ClientController::requestAddFriend(quint32 receiver){//发送好友请求

    ChatMessage chat = ChatMessage(getMyInfo().getID(),receiver);
    auto message = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND,chat.toQByteArray());
    sendMessageWhenConnected(std::move(message));
}

void ClientController::agreeFriendRequest(quint32 sender,quint32 receiver){

    ChatMessage chat = ChatMessage(sender,receiver);
    auto message = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND_AGREED,chat.toQByteArray());
    sendMessageWhenConnected(std::move(message));
}

void ClientController::declineFriendRequest(quint32 sender,quint32 receiver){

    ChatMessage chat = ChatMessage(sender,receiver);
    auto message = std::make_unique<Msg>(MsgType::REQUEST_ADD_FRIEND_DECLINED,chat.toQByteArray());
    sendMessageWhenConnected(std::move(message));
}

//删除好友
void ClientController::requestDeleteFriend(quint32 receiver){

    ChatMessage chat = ChatMessage(getMyInfo().getID(),receiver);
    auto message = std::make_unique<Msg>(MsgType::REQUEST_DELETE_FRIEND,chat.toQByteArray());
    sendMessageWhenConnected(std::move(message));
}


//添加新好友之后
//将好友添加到现存的数据结构中
void ClientController::dynamicAppendFriend(UserInfo _friend) {
    //将好友添加到好友列表中
    friendList.append(_friend);
    //为好友新建消息List
    chatMsgMap[_friend.getID()] = new QList<ChatMessage>;
}
//删除同上
void ClientController::dynamicRemoveFriend(UserInfo _friend) {

    for (int i = 0; i < friendList.size(); ++i) {
        if (friendList[i].getID() == _friend.getID()) {
            friendList.removeAt(i);
            break;
        }
    }
    quint32 friendID = _friend.getID();
    if (chatMsgMap.contains(friendID)) {
        delete chatMsgMap[friendID];
        chatMsgMap.remove(friendID);
    }
}


//发送好友列表获取的请求
void ClientController::requestFriendList(UserInfo info) {

    auto message = std::make_unique<Msg>(MsgType::REQUEST_ALL_FRIEND_LIST, info.toQByteArray());

    sendMessageWhenConnected(std::move(message));
}


QList<UserInfo> * ClientController::getFriendList() {
    return &friendList;
}
