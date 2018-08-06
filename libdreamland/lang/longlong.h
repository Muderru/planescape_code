/* $Id: longlong.h,v 1.1.2.1.30.2 2009/10/11 18:35:37 rufina Exp $
 *
 * ruffina, Dream Land, 2004
 */
/***************************************************************************
                          longlong.h  -  description
                             -------------------
    begin                : Thu Nov 1 2001
    copyright            : (C) 2001 by Igor S. Petrenko
    email                : nofate@europe.com
 ***************************************************************************/

#ifndef LONGLONG_H
#define LONGLONG_H

#include "dlstring.h"
/**
 * @author Igor S. Petrenko
 */
class LongLong
{
public:
	static const DLString TYPE;

public:	
	/** �� ��������� �������� 0 */
	inline LongLong( ) : value( 0 )
	{
	}

	inline LongLong( long long value ) : value( value )
	{
	}

	inline LongLong( const DLString& value ) throw( ExceptionBadType )
	{
		fromString( value );
	}

	
	DLString toString( ) const throw( );
	void fromString( const DLString& value ) throw( ExceptionBadType );
	
	inline long long getValue( ) const
	{
		return value;
	}

	inline void setValue( long long value )
	{
		this->value = value;
	}

	inline operator long long & ( ) {
	    return value;
	}
private:
	long long value;
};




/** ����� � ostream ���� LongLong */
inline std::ostream& operator << ( std::ostream& ostr, const LongLong& longLongValue )
{
	ostr << longLongValue.getValue( );
	return ostr;
}

#endif
