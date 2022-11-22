#include <ostream>
#include <streambuf>
#include <iostream>
#include <string>
#include <unistd.h>

using std::basic_streambuf;
using std::istream;
using std::streamsize;
using std::string;

const int StdOutFD = 1;
const streamsize StdOutBufferSize = 10;

template < class CharT>
class StdOutBuf : public basic_streambuf<CharT> {
private:
	typedef basic_streambuf<CharT> Base;
	typedef typename Base::int_type int_type;
	typedef typename Base::char_type char_type;
	typedef typename Base::traits_type traits_type;
	typedef typename Base::pos_type pos_type;
	typedef typename Base::off_type off_type;
public:
	StdOutBuf() : Base() {
		Base::setp(_buffer, _buffer + StdOutBufferSize);
	}
	~StdOutBuf() {
		sync();
	}
protected:
	virtual int_type overflow(int_type c = traits_type::eof()) {
		streamsize n = StdOutBufferSize;
		if(c != traits_type::eof()) {
			_buffer[StdOutBufferSize] = c;
			n = StdOutBufferSize + 1;
		}
		streamsize err = write(StdOutFD, _buffer, n);
		if(err == -1) {
			return traits_type::eof();
		}
		Base::setp(_buffer, _buffer + StdOutBufferSize);
		return _buffer[0];
	}

	virtual int sync() {
		streamsize n = Base::pptr() - _buffer;
		Base::setp(_buffer, _buffer + StdOutBufferSize);
		return write(StdOutFD, _buffer, n);
	}
private:
	CharT _buffer[StdOutBufferSize + 1];
};

const int StdInFD = 0;
const streamsize StdInBufferSize = 10;

template < class CharT>
class StdInBuf : public std::basic_streambuf<CharT> {
public:
	StdInBuf() : std::basic_streambuf<CharT>() {
		Base::setg(_buffer, _buffer, _buffer);
	}
protected:
	typedef std::basic_streambuf<CharT> Base;
	typedef typename Base::int_type int_type;
	typedef typename Base::char_type char_type;
	typedef typename Base::traits_type traits_type;
	typedef typename Base::pos_type pos_type;
	typedef typename Base::off_type off_type;
	virtual int_type underflow() {
		streamsize n = read(StdInFD, _buffer, StdInBufferSize);
		if(n > 0) {
			Base::setg(_buffer, _buffer, _buffer + n);
			return traits_type::to_int_type(_buffer[0]);
		} else {
			Base::setg(_buffer, _buffer, _buffer);
			return traits_type::eof();
		}
	}
private:
	CharT _buffer[StdInBufferSize];
};

int main() {
	StdInBuf<char> ib;
	istream cin(&ib);
	string s, s2;
	int i;
	cin >> s >> s2 >> i;
	return 0;
}
