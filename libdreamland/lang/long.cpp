/* $Id: long.cpp,v 1.1.34.2 2009/10/11 18:35:37 rufina Exp $
 *
 * ruffina, Dream Land, 2004
 */
/***************************************************************************
                          long.cpp  -  description
                             -------------------
    begin                : Thu Nov 1 2001
    copyright            : (C) 2001 by Igor S. Petrenko
    email                : nofate@europe.com
 ***************************************************************************/

#include <sstream>

#include "long.h"

const DLString Long::TYPE = "Long";


void Long::fromString( const DLString & str ) throw( ExceptionBadType )
{
	std::basic_istringstream<char> s( str.c_str( ) );
	long i;
  		
	s >> i;

	if( s )
	{
		this->value = i;
		return;
	}
	throw ExceptionBadType( TYPE, str );
}

DLString Long::toString( ) const throw( )
{
	std::basic_ostringstream<char>  buf;

	buf << value;
	return buf.str( );
}
