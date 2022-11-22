#include <string.h>
#include <streambuf>
#include <iostream>
#include <unistd.h>

using std::basic_streambuf;
using std::endl;
using std::ostream;
using std::streamsize;

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

int main() {
	StdOutBuf<char> ob;
	ostream cout(&ob);
	cout << "Hello";
	cout << endl;
	cout << "world\n";
	cout << endl;
	cout << 1;
	cout << "text more 10 characters";
	return 0;
}
