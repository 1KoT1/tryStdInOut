#include <streambuf>
#include <iostream>
#include <unistd.h>

template < class CharT>
class StdOutBuf : public std::basic_streambuf<CharT> {
public:
	StdOutBuf() : std::basic_streambuf<CharT>() {
		Base::setp(_buffer, _buffer + BufferSize);
	}
protected:
	typedef std::basic_streambuf<CharT> Base;
	typedef typename Base::int_type int_type;
	typedef typename Base::char_type char_type;
	typedef typename Base::traits_type traits_type;
	typedef typename Base::pos_type pos_type;
	typedef typename Base::off_type off_type;

	virtual std::streamsize xsputn(const CharT *buf, std::streamsize size) {
		return write(1, buf, size);
	}

	virtual int_type overflow(int_type c = traits_type::eof()) {
		return Base::overflow(c);
		//		std::streamsize err = xsputn(_buffer, BufferSize);
		//		if(err == -1) {
		//			return traits_type::eof();
		//		}
		//		Base::setp(_buffer, _buffer + BufferSize);
		//		return 1;
	}
private:
	static const std::streamsize BufferSize = 10;
	CharT _buffer[BufferSize];




public:
	virtual void imbue( const std::locale& loc ) {
		Base::imbue(loc);
	}
	virtual Base* setbuf( char_type* s, std::streamsize n ) {
		return Base::setbuf(s, n);
	}
	virtual pos_type seekoff( off_type off, std::ios_base::seekdir dir,
														std::ios_base::openmode which = Base::ios_base::in | Base::ios_base::out ) {
		return Base::seekoff(off, dir, which);
	}
	virtual pos_type seekpos( pos_type pos,
														std::ios_base::openmode which = std::ios_base::in | std::ios_base::out) {
		return seekpos(pos, which);
	}
	virtual int sync() {
		return Base::sync();
	}
	virtual std::streamsize showmanyc() {
		return Base::showmanyc();
	}
	virtual int_type underflow() {
		return Base::underflow();
	}
	virtual int_type uflow() {
		return Base::uflow();
	}
	virtual std::streamsize xsgetn( char_type* s, std::streamsize count ) {
		return Base::xsgetn(s, count);
	}
	virtual int_type pbackfail( int_type c = traits_type::eof() ) {
		return Base::pbackfail(c);
	}
};

int main() {
	StdOutBuf<char> ob;
	std::ostream cout(&ob);
	cout << "Hello";
	cout << std::endl;
	cout << "world\n";
	cout << std::endl;
	cout << 1;
	cout << "text more 10 characters";
	return 0;
}
