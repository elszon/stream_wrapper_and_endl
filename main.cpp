#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

class StreamWrapper{
public:
    StreamWrapper(std::unique_ptr<std::ostream> ostream)
        : os(std::move(ostream)){
        if(!os){
            throw std::runtime_error{"Empty ostream ptr"};
        }
    }

    using char_type   = std::ostream::char_type;
    using traits_type = std::ostream::traits_type;


    std::ostream& operator* () { return *os; }

private:
    std::unique_ptr<std::ostream> os;

};

template < typename T >
StreamWrapper& operator << (StreamWrapper& s, const T& t){
    *s << t;
    return s;
}

/// This part will pass all stream function to StreamWrapper
using F = decltype(std::endl<StreamWrapper::char_type, std::char_traits<StreamWrapper::char_type>>);

StreamWrapper& operator << (StreamWrapper& s, F f){
    f(*s);
    return s;
}



int main()
{
    StreamWrapper s(std::make_unique<std::ostringstream>());
    s << "asdb" << std::endl;

    return 0;
}
