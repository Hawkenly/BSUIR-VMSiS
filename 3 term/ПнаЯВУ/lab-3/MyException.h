#pragma once
#include <string>
#include <iostream>

class MyException{
protected:
    int code;
    std::string ErrMessage;
public:
    explicit MyException(int code, std::string ErrMessage) noexcept :code(code),ErrMessage(ErrMessage){};
    virtual void show() const noexcept
    {
        std::cout<<"----------"<<std::endl<<"Unknown error!"<<std::endl<<"Error code: "<<666<<std::endl<<"----------"<<std::endl;
    }
};

