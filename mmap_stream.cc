#include "mmap_stream.hpp"
#include <streambuf>
#include <functional>
#include <cassert>
#include <cstring>

using namespace std;

mmap_stream::mmap_stream(const char *begin, const char *end)
{
    setg((char*)begin, (char*)begin, (char*)end);
}

streamsize mmap_stream::size() {
  return egptr() - eback();
}

mmap_stream::int_type mmap_stream::underflow()
{
    if (gptr() == egptr()) {
        return traits_type::eof();
    }
    return *(gptr());
}

mmap_stream::int_type mmap_stream::uflow()
{
    if (gptr() == egptr()) {
        return traits_type::eof();
    }
    gbump(1);

    return *(gptr());
}

mmap_stream::int_type mmap_stream::pbackfail(int_type ch)
{
    if (gptr() ==  eback() || (ch != traits_type::eof() && ch != gptr()[-1]))
        return traits_type::eof();
    gbump(-ch);
    return *(gptr());
}

streamsize mmap_stream::showmanyc()
{
    return egptr() - gptr();
}

streampos mmap_stream::seekoff(streamoff off, ios_base::seekdir way, ios_base::openmode which = ios_base::in) {
  if(way == ios_base::beg) {
    setg(eback(), eback()+off, egptr());
  } else if(way == ios_base::cur) {
    gbump(off);
  } else {
    setg(eback(), egptr()-off, egptr());
  }
  return gptr() - eback();
}

streampos mmap_stream::seekpos(streampos sp, ios_base::openmode which = ios_base::in) {
    return seekoff(sp - pos_type(off_type(0)), std::ios_base::beg, which);
}
