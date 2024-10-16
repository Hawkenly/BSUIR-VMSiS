#include "MyException.h"

class ReadFileException:public MyException{
public:
    ReadFileException(int code, std::string ErrMessage) noexcept : MyException(code,ErrMessage){};
    void show() const noexcept override
    {
        std::cout<<"----------"<<std::endl<<"File error! "<<ErrMessage<<std::endl<<"Error code: "<<code<<std::endl<<"----------"<<std::endl;
    }
};