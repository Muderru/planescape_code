/* $Id: xmlinteger.h,v 1.8.2.2.28.3 2009/10/11 18:35:38 rufina Exp $
 *
 * ruffina, Dream Land, 2003
 */
// xmlinteger.h: interface for the XMLInteger class.
//
//////////////////////////////////////////////////////////////////////

#ifndef XMLINTEGER_H
#define XMLINTEGER_H

#include "integer.h"
#include "xmlnode.h"
#include "xmlvariable.h"

/**
 * @author Igor S. Petrenko
 * @short XML ���������� int
 */
class XMLInteger : public Integer
{
public:
	/** �� ��������� �������� \0 */
	inline XMLInteger( ) : Integer( )
	{
	}
	
	inline XMLInteger( int value ) : Integer( value )
	{
	}
	
	inline XMLInteger( const DLString& value ) throw( ExceptionBadType )
		: Integer( value )
	{
	}
	
	/** ���������� xml ������������� ���������� */
	bool toXML( XMLNode::Pointer& node ) const;
	/** ������������� ������ �� xml ������ */
	void fromXML( const XMLNode::Pointer& node ) throw( ExceptionBadType );
};

class XMLIntegerNoEmpty : public XMLInteger {
public:
	inline XMLIntegerNoEmpty( )
	{
	}
	
	inline XMLIntegerNoEmpty( int value ) : XMLInteger( value )
	{
	}

	bool toXML( XMLNode::Pointer& node ) const;
};

class XMLIntegerVariable : public virtual XMLVariable, public XMLInteger {
public:
    virtual bool toXML( XMLNode::Pointer& ) const;
    virtual void fromXML( const XMLNode::Pointer& ) throw( ExceptionBadType );
};

template <int def>
class XMLIntegerNoDef : public XMLInteger {
public:
    XMLIntegerNoDef( ) : XMLInteger(def) { }

    inline bool toXML(XMLNode::Pointer &parent) const {
        if (getValue( ) == def)
            return false;
        else 
            return XMLInteger::toXML(parent);
    }
};


/** ����� � ostream ���� XMLInteger */
inline std::ostream& operator << ( std::ostream& ostr, const XMLInteger& xmlInteger )
{
	ostr << xmlInteger.getValue( );
	return ostr;
}

#endif
