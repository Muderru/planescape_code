/* $Id: xmllong.h,v 1.6.2.2.28.2 2009/10/11 18:35:38 rufina Exp $
 *
 * ruffina, Dream Land, 2003
 */
// xmllong.h: interface for the XMLLong class.
//
//////////////////////////////////////////////////////////////////////

#ifndef XMLLONG_H
#define XMLLONG_H

#include "long.h"
#include "xmlnode.h"

/**
 * @author Igor S. Petrenko
 * @short XML ���������� long
 */
class XMLLong : public Long
{
public:
	/** �� ��������� �������� \0 */
	inline XMLLong( ) : Long( )
	{
	}
	
	inline XMLLong( long value ) : Long( value )
	{
	}
	
	inline XMLLong( const DLString& value ) throw( ExceptionBadType )
		: Long( value )
	{
	}
	
	/** ���������� xml ������������� ���������� */
	bool toXML( XMLNode::Pointer& node ) const;
	/** ������������� ������ �� xml ������ */
	void fromXML( const XMLNode::Pointer& node ) throw( ExceptionBadType );
};




/** ����� � ostream ���� XMLLong */
inline std::ostream& operator << ( std::ostream& ostr, const XMLLong& xmlLong )
{
	ostr << xmlLong.getValue( );
	return ostr;
}

#endif
