#ifndef VALUES_INCLUDED
#define VALUES_INCLUDED

#include <stdio.h>
#include <string.h>


class Value
{
public:
	Value(int value)
	{
		set(static_cast<long>(value));
	}
	Value(unsigned value)
	{
		set(static_cast<long>(value));
	}
	Value(float value)
	{
		set(value);
	}
	Value(double value)
	{
		set(value);
	}
	Value(const char* value)
	{
		set(value);
	}

	long get_long(void)
	{
		return integer;
	}
	float get_float(void)
	{
		return floating;
	}
	const char* get_string(void)
	{
		return string;
	}

private:
	void set(long value)
	{
		integer = value;
		floating = static_cast<double>(value);
		sprintf(string, "%li", integer);
	}
	void set(double value)
	{
		integer = static_cast<long>(value);
		floating = value;
		sprintf(string, "%f", value);
	}
	void set(const char* value)
	{
		integer = -10000;
		floating = -10000.0;
		strlcpy(string, value, sizeof(string));
	}

	long integer;
	double floating;
	char string[256];
};

Value GetValue(int command);

#endif
