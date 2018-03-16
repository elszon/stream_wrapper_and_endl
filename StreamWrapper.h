#pragma once

#include <memory>
#include <sstream>
#include <stdexcept>


class IOStreamWrapper {
public:
    using OStream = std::ostream;

    virtual ~IOStreamWrapper() = default;

    virtual OStream& operator* () = 0;

    /// This will give stream function handler
    using StreamFun = decltype(std::endl<typename OStream::char_type, std::char_traits<typename OStream::char_type>>);
};

template < typename T >
IOStreamWrapper& operator << (IOStreamWrapper& s, const T& t){
    *s << t;
    return s;
}


IOStreamWrapper& operator << (IOStreamWrapper& s, typename IOStreamWrapper::StreamFun f){
    f(*s);
    return s;
}




class OStreamWrapper final : public IOStreamWrapper{
public:
    OStreamWrapper(std::unique_ptr<OStream> ostream)
        : os(std::move(ostream)){
        if(!os){
            throw std::runtime_error{"Empty ostream ptr"};
        }
    }

    OStream& operator* () override { return *os; }

private:
    std::unique_ptr<OStream> os;

};
