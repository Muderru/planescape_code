/* $Id: xmllonglong.h,v 1.6.2.2.28.3 2009/10/11 18:35:38 rufina Exp $
 *
 * ruffina, Dream Land, 2003
 */
// xmllonglong.h: interface for the XMLLongLong class.
//
//////////////////////////////////////////////////////////////////////

#ifndef XMLLONGLONG_H
#define XMLLONGLONG_H

#include "longlong.h"
#include "xmlnode.h"

/**
 * @author Igor S. Petrenko
 * @short XML ���������� long long
 */
class XMLLongLong : public LongLong
{
public:
	/** �� ��������� �������� \0 */
	inline XMLLongLong( ) : LongLong( )
	{
	}
	
	inline XMLLongLong( long long value ) : LongLong( value )
	{
	}
	
	inline XMLLongLong( const DLString& value ) throw( ExceptionBadType )
		: LongLong( value )
	{
	}
	
	/** ���������� xml ������������� ���������� */
	bool toXML( XMLNode::Pointer& node ) const;
	/** ������������� ������ �� xml ������ */
	void fromXML( const XMLNode::Pointer& node ) throw( ExceptionBadType );
};


/** ����� � ostream ���� XMLLongLong */
inline std::ostream& operator << ( std::ostream& ostr, const XMLLongLong& xmlLongLong )
{
	ostr << xmlLongLong.getValue( );
	return ostr;
}

class XMLLongLongNoEmpty : public XMLLongLong {
public:
	inline XMLLongLongNoEmpty( )
	{
	}
	
	inline XMLLongLongNoEmpty( int value ) : XMLLongLong( value )
	{
	}

	bool toXML( XMLNode::Pointer& node ) const;
};

#endif
