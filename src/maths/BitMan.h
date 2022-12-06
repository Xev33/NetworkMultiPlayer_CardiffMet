#ifndef BIN_MATH_H_
#define BIN_MATH_H_

template< int tValue, int tBits >
struct GetRequiredBitsHelper
{
	enum { Value = GetRequiredBitsHelper< ( tValue >> 1 ), tBits + 1 >::Value };
};

template< int tBits >
struct GetRequiredBitsHelper< 0, tBits >
{
	enum { Value = tBits };
};

template< int tValue >
struct GetRequiredBits
{
	enum { Value = GetRequiredBitsHelper< tValue, 0 >::Value };
};

#endif
