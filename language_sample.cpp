#define endl "\n";

class ostream
{
	string:buffer;

	function print_buffer() {
		print(this->buffer) if !this->buffer.empty();
		this->buffer.clean();
		write(1, this->buffer.c_str(), this->buffer.length());
	}
}
ostream:cout;

function operator(:)(string:a, [integer]:b)
{
	string:result;
	int:neg;

	if (a < 0)
		neg = 1;
	if (a != 0)
	{
		result += a % 10 + 48;
		a /= 10;
	}
	if (neg)
		result += '-';
	return (result.reverse());
}

function operator(<<)(&ostream:stream, [primitive]:a)
{
	if (typeof(a) == "char")
		stream.buffer += a;
	stream.buffer += string:a;
	return (stream);
}

int:a = 5;
cout << a << endl;
cout.print_buffer();
