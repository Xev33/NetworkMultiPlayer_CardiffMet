#ifndef FIXED_H_
#define FIXED_H_

inline uint32_t ConvertToFixed( float inNumber, float inMin, float inPrecision )
{
	return static_cast< int > ( ( inNumber - inMin ) / inPrecision );
}

inline float ConvertFromFixed( uint32_t inNumber, float inMin, float inPrecision )
{
	return static_cast< float >( inNumber ) * inPrecision + inMin;
}

#endif
