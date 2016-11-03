#ifndef INTEGER_H
#define INTEGER_H

class Integer
{
public:
	Integer(long ll =0);
	Integer(const Integer& h);
	~Integer();

	//Member overloaded operators
	// const Integer operator+(const Integer& right);
	// const long operator<<(const Integer& param);

	//Non-member overloaded operators
	friend const Integer operator+(const Integer& left, const Integer& right);
	friend std::ostream& operator<<(std::ostream& out, const Integer& param);	
	friend std::istream& operator>>(std::istream& in, Integer& param);

private:
	long i;
	
};

#endif // INTEGER_H ///:~
