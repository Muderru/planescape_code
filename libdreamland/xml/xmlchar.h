/* $Id: xmlchar.h,v 1.7.2.2.28.2 2009/10/11 18:35:38 rufina Exp $
 *
 * ruffina, Dream Land, 2003
 */
// xmlchar.h: interface for the XMLClar class.
//
//////////////////////////////////////////////////////////////////////

#ifndef XMLCHAR_H
#define XMLCHAR_H

#include "char.h"
#include "xmlnode.h"

/**
 * @author Igor S. Petrenko
 * @short XML ���������� char
 */
class XMLChar : public Char
{
public:
	/** �� ��������� �������� \0 */
	inline XMLChar( ) : Char( )
	{
	}
	
	inline XMLChar( char value ) : Char( value )
	{
	}
	
	inline XMLChar( const DLString& value ) throw( ExceptionBadType )
		: Char( value )
	{
	}
	
	/** ���������� xml ������������� ���������� */
	bool toXML( XMLNode::Pointer& node ) const;
	/** ������������� ������ �� xml ������ */
	void fromXML( const XMLNode::Pointer& node ) throw( ExceptionBadType );
};





/** ����� � ostream ���� XMLChar */
inline std::ostream& operator << ( std::ostream& ostr, const XMLChar& xmlChar )
{
	ostr << xmlChar.getValue( );
	return ostr;
}

#endif
