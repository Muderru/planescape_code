/* $Id: dlobject.h,v 1.5.2.9.6.2 2009/10/11 18:35:37 rufina Exp $
 *
 * ruffina, Dream Land, 2004
 */
// dlobject.h: interface for the DLObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DLOBJECT_H
#define DLOBJECT_H

#include <config.h>

#include "pointer.h"

/**
 * @author Igor S. Petrenko
 * @short ������� ����� ��� ���� �������� DL
 * ���, ��� ��� ������ ����� � ������� ����� ���� � ���-�� �����,
 * �� ����� ����� �������� ���� void* + ������ ��������� �����������
 * ��������������, ��������� dynamic_cast
 */

#define dallocate( type, args... )      new type ( args )
#define ddeallocate( _pointer )         delete _pointer

class DLObject  {
public:
	typedef ::Pointer<DLObject> Pointer;

public:
	inline DLObject( ) : linkCount( 0 )
	{
	}

	/** � ������ private */
	virtual ~DLObject( );
	
	inline void link( ) const
	{
		linkCount++;
	}

	inline void unlink( ) const
	{
		if( linkCount <= 1 )
		{
			delete this;
		}
		else
		{
			linkCount--;
		}
	}
	
public:
	inline int getLinkCount( ) const
	{
		return linkCount;
	}

	// ������ ��� Pointer!!!
	inline void setLinkCount( int linkCount )
	{
		this->linkCount = linkCount;
	}

private:
	mutable int linkCount;
};


#endif
