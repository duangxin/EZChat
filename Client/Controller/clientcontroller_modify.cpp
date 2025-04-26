#include"clientcontroller.h"

#include <QFile>
#include <QFileInfo>

//换用户名
void ClientController::requestModifyUserName(QString newUserName) {
    UserInfo OldUserInfo = getMyInfo();

    auto message = std::make_unique<Msg>(MsgType::MODIFY_USERNAME,
                                         UserInfo(OldUserInfo.getID(), newUserName, OldUserInfo.getPwd(),
                                                  OldUserInfo.getAvatarName()).toQByteArray());
    sendMessageWhenConnected(std::move(message));

}


//请求更换头像, 返回头像的完整路径
void ClientController::requestModifyAvatar(QString imgPath){
    UserInfo OldUserInfo = getMyInfo();

    auto message = std::make_unique<Msg>(MsgType::MODIFY_AVATAR,
                                         UserInfo(OldUserInfo.getID(), OldUserInfo.getName(), OldUserInfo.getPwd(),
                                                  imgPath).toQByteArray());
    sendMessageWhenConnected(std::move(message));
}

