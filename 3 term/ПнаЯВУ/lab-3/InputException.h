#include "MyException.h"

class InputException:public MyException{
public:
    explicit InputException(int code, std::string ErrMessage) noexcept : MyException(code,ErrMessage){};
    void show() const noexcept override
    {
        std::cout<<"----------"<<std::endl<<"Input error! "<<ErrMessage<<std::endl<<"Error code: "<<code<<std::endl<<"----------"<<std::endl;
    }
};
