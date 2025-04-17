#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include "MsgHandler.h"

class loginHandler : public MsgHandler
{
    Q_OBJECT
public:
    explicit loginHandler(QObject *parent = nullptr);
    virtual void parse(Msg& msg);

    UserInfo &getMyInfo();
signals:
    void loginSuccessful(UserInfo info);
    void loginFailed();

private:
    UserInfo myInfo;

};
#endif // LOGINHANDLER_H
