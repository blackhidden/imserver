/**
 *      @desc:  业务逻辑
 *      @author:jiacobi
 *      @date:  2020.2.13
 **/
#pragma once

#include <memory>
#include "../net/TcpConnection.h"

using namespace net;

class BussinessLogic final
{
private:
    BussinessLogic() = delete;
    ~BussinessLogic() = delete;

    BussinessLogic(const BussinessLogic& rhs) = delete;
    BussinessLogic& operator =(const BussinessLogic& rhs) = delete;

public:
    static void registerUser(const std::string& data, const std::shared_ptr<TcpConnection>& conn, bool keepalive, std::string& retData);

};
