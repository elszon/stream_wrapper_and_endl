#pragma once

#include <memory>
#include <sstream>
#include <stdexcept>


template < typename OutputStream >
class IOStreamWrapper {
public:
    using OStream = OutputStream;

    virtual ~IOStreamWrapper() = default;

    virtual OStream& operator* () = 0;

    /// This will give stream function handler
    using StreamFun = decltype(std::endl<typename OStream::char_type, std::char_traits<typename OStream::char_type>>);
};


template < typename OutputStream = std::ostream,
           typename = std::enable_if_t<std::is_base_of<std::ostream, OutputStream>::value> >
class OStreamWrapper : public IOStreamWrapper<OutputStream> {
public:

    using OStream = typename IOStreamWrapper<OutputStream>::OStream;

    OStreamWrapper(std::unique_ptr<OStream> ostream)
        : os(std::move(ostream)){
        if(!os){
            throw std::runtime_error{"Empty ostream ptr"};
        }
    }

    OStream& operator* () override { return *os; }

    /// This will give stream function handler
    using StreamFun = decltype(std::endl<typename OStream::char_type, std::char_traits<typename OStream::char_type>>);


private:
    std::unique_ptr<OStream> os;

};

template < typename Stream, typename T >
IOStreamWrapper<Stream>& operator << (IOStreamWrapper<Stream>& s, const T& t){
    *s << t;
    return s;
}


template < typename Stream >
IOStreamWrapper<Stream>& operator << (IOStreamWrapper<Stream>& s, typename OStreamWrapper<Stream>::StreamFun f){
    f(*s);
    return s;
}
