/* $Id: dlstring.h,v 1.27.2.13.6.8 2009/10/11 18:35:37 rufina Exp $
 *
 * ruffina, Dream Land, 2004
 */
#ifndef DLSTRING_H
#define DLSTRING_H

#include <string>

#include "exceptionbadtype.h"

/**
 * @author Igor S. Petrenko
 * @short ������������ string
 * ��������� ����������� ����� string. ��������� �������� ������ � �������,
 * �������, etc
 */
class DLString : public std::string
{
public:
	static const DLString emptyString;

public:
	inline DLString( ) : string( )
	{
	}

	inline DLString( const string& str ) : string( str )
	{
	}

	inline DLString( const char* str ) : string( str )
	{
	}

	inline DLString( const DLString& value )
	{
		assign( value );
	}

	inline DLString( short value )
	{
		assign( value );
	}

	inline DLString( unsigned int value )
	{
		assign( value );
	}

	inline DLString( int value )
	{
		assign( value );
	}

	inline DLString( long value )
	{
		assign( value );
	}

	inline DLString( long long value )
	{
		assign( value );
	}


	inline DLString& assign( char ch )
	{
		*static_cast<string*>( this ) = ch;
		return *this;
	}

	inline DLString& assign( const char* str, size_type n )
	{
		( *static_cast<string*>( this ) ).assign( str, n );
		return *this;
	}

	inline DLString& assign( const string& str )
	{
		*static_cast<string*>( this ) = str;
		return *this;
	}

	DLString& assign( short );
	DLString& assign( unsigned int );
	DLString& assign( int );
	DLString& assign( long );
	DLString& assign( long long );
	
	inline DLString& append( char ch )
	{
		*static_cast<string*>( this ) += ch;
		return *this;
	}

	inline DLString& append( const char* str, size_type n )
	{
		( *static_cast<string*>( this ) ).append( str, n );
		return *this;
	}

	inline DLString& append( const string& str )
	{
		*static_cast<string*>( this ) += str;
		return *this;
	}

	DLString& append( short );
	DLString& append( unsigned int );
	DLString& append( int );
	DLString& append( long );
	DLString& append( long long );

	inline DLString& operator = ( const char* str )
	{
		return assign( str );
	}

	inline DLString& operator = ( const string& str )
	{
		return assign( str );
	}

	inline DLString& operator = ( char ch )
	{
		return assign( ch );
	}

	inline DLString& operator = ( short value )
	{
		return assign( value );
	}

	inline DLString& operator = ( unsigned int value )
	{
		return assign( value );
	}

	inline DLString& operator = ( int value )
	{
		return assign( value );
	}

	inline DLString& operator = ( long value )
	{
		return assign( value );
	}

	inline DLString& operator = ( long long value )
	{
		return assign( value );
	}

	inline DLString& operator += ( const char* str )
	{
		return append( str );
	}

	inline DLString& operator += ( const string& str )
	{
		return append( str );
	}

	inline DLString& operator += ( char value )
	{
		return append( value );
	}

	inline DLString& operator += ( short value )
	{
		return append( value );
	}

	inline DLString& operator += ( unsigned int value )
	{
		return append( value );
	}

	inline DLString& operator += ( int value )
	{
		return append( value );
	}

	inline DLString& operator += ( long value )
	{
		return append( value );
	}

	inline DLString& operator += ( long long value )
	{
		return append( value );
	}

	inline DLString& operator << ( const char* value )
	{
		return append( value );
	}

	inline DLString& operator << ( const DLString& value )
	{
		return append( value );
	}

	inline DLString& operator << ( const string& value )
	{
		return append( value );
	}

	inline DLString& operator << ( char value )
	{
		return append( value );
	}

	inline DLString& operator << ( short value )
	{
		return append( value );
	}

	inline DLString& operator << ( unsigned int value )
	{
		return append( value );
	}

	inline DLString& operator << ( int value )
	{
		return append( value );
	}

	inline DLString& operator << ( long value )
	{
		return append( value );
	}

	inline DLString& operator << ( long long value )
	{
		return append( value );
	}

	/*
	 * case-less, colour-less comparision
	 */
	bool operator ^ ( const DLString & ) const;
	/** caseless comparision */
	bool equalLess( const DLString & ) const;

	/*
	* ����� ������� ��� ����������� ����������� ����� � ������ ����
	* ��� ��� ��������� �������������� ��������� ����������()
	*/
	int toInt( ) const throw( ExceptionBadType );
	long toLong( ) const throw( ExceptionBadType );
	long long toLongLong( ) const throw( ExceptionBadType );
	long int toLongInt( ) const throw( ExceptionBadType );
	bool toBoolean( ) const throw( ExceptionBadType );
	char toChar( ) const throw( ExceptionBadType );
	unsigned char toByte( ) const throw( ExceptionBadType );
	
	/*
	 * Compare strings, case insensitive, for prefix matching.
	 * @return true if this string is a prefix of 'str' 
	 */
	bool strPrefix( const DLString &str ) const;
	/*
	 * Compare strings, case insensitive, for suffix matching.
	 * @return true if this string is a suffix of 'str' 
	 */
	bool strSuffix( const DLString &str ) const;

	/** ���������� ������ �������� � ���������� ��� */
	DLString getOneArgument( );
	/** ���������� <�����><��������> �� ������ � ���������� ��� */
	int getMultArgument( );
	/** ���������� <�����><�����> �� ������ � ���������� ��� */
	int getNumberArgument( );
	/** ��������������� ������� */
	int splitFirstNumber( char );

	void colourstrip( );
	DLString colourStrip( ) const;
	size_type colorLength( ) const;

	bool lessCase( const DLString& str ) const;
	
	bool isNumber( ) const;
	
	/** ������� ������� � ������ � ����� ������ */
	inline void stripWhiteSpace( )
	{
		stripRightWhiteSpace( );
		stripLeftWhiteSpace( );
	}

	/** ������� ������� � ������ ������ */
	void stripLeftWhiteSpace( );
	/** ������� ������� � ����� ������ */
	void stripRightWhiteSpace( );
	
	DLString& toLower( );
	DLString toLower( ) const;
	DLString& toUpper( );
	DLString toUpper( ) const;
	DLString & upperFirstCharacter( );
	/** make an initial-capped string */
	DLString& capitalize( );

	/** case-insensitive, full-word-match search of subword */
	bool isName( const DLString & msg);
	DLString &substitute( char, char );

	DLString substitute( char, const char *) const;
	DLString &replaces( const DLString &, const DLString & );

	DLString ruscase( char gram_case ) const;
	DLString quote( ) const;
	DLString &cutSize( size_t );
};

#endif
