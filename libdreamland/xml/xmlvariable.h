/* $Id: xmlvariable.h,v 1.9.2.1.28.2 2009/10/11 18:35:39 rufina Exp $
 *
 * ruffina, Dream Land, 2003
 */
// dlvariable.h: interface for the DLVariable class.
//
//////////////////////////////////////////////////////////////////////

#ifndef XMLVARIABLE_H
#define XMLVARIABLE_H

#include "exceptionbadtype.h"
#include "xmlnode.h"

/**
 * @author Igor S. Petrenko
 * @short ������ ���� XML ����������
 * ���������� � XML ���� � ���� <str>10</str>, ��� str - ��� ����������
 * ��� ���������� ����� ���������� � ������ ����� XMLVariable. �� ����
 * ����������� ����� fromXML �������� ������ ����������� ���� � ����
 * �������������� string -> ��� ���������� �������, ���������� ��������
 * �������� ����������� � XML. ����� toXML ���������� �������� �������������.
 */
class XMLVariable : public virtual DLObject
{
public:
    typedef ::Pointer<XMLVariable> Pointer;
    
    virtual ~XMLVariable( );

public:
    virtual void fromXML( const XMLNode::Pointer& node ) throw( ExceptionBadType ) = 0;
    /** @param - ������ xmlnode ���������� �� ������ */
    virtual bool toXML( XMLNode::Pointer& node ) const = 0;
};


#endif
