/* $Id: pointer.h,v 1.1.2.2 2009/10/11 18:35:37 rufina Exp $
 *
 * ruffina, Dream Land, 2004
 */
/***************************************************************************
                          pointer.h  -  description
                             -------------------
    begin                : Thu May 31 2001
    copyright            : (C) 2001 by Igor S. Petrenko
    email                : nofate@europe.com
 ***************************************************************************/

#ifndef POINTER_H
#define POINTER_H

/**
 * @author Igor S. Petrenko
 * @short ������������ ��� Pointer ��� ������ new
 */
static const struct NEWStruct {} NEW = {};

/**
 * @short ������ � ����������� ( �������� � link/unlink ������ DLObject )
 * @author Igor S. Petrenko
 */
template<typename T>
class Pointer
{
public:
	typedef Pointer<T> SelfType;

public:
	/** ������ ��������� */
	inline Pointer( ) : pointer( 0 )
	{
	}
	
	/** ��� �������� Pointer ����� ���� */
	inline Pointer( const SelfType& cpointer )
	{
		setPointerWithoutSelf( cpointer.pointer );
	}
	
	/** ��� ��������, Pointer ������� ���� */
	template<typename NoT>
	inline Pointer( NoT cpointer )
	{
		setPointerWithoutSelf( cpointer.getPointer( ) );
	}
	
	/** ����� ������ � this ( link ) */
	inline Pointer( T* pointer )
	{
		setPointerWithoutSelf( pointer );
	}

	/** ����� ������ � this ( link ) */
	inline Pointer( const T* pointer )
	{
		setPointerWithoutSelf( const_cast<T*>( pointer ) );
	}
	
	/** ����������� �� ���������, ��� ���������� */
	inline Pointer( const NEWStruct& )
	{
		setPointerWithoutSelf( new T( ) );
	}

	/** ����������� �� ���������, 1-� �������� */
	template<typename Arg1>
	inline Pointer( const NEWStruct&, Arg1 arg1 )
	{
		setPointerWithoutSelf( new T( arg1 ) );
	}
	
	/** ����������� �� ���������, 2-�� ��������� */
	template<typename Arg1, typename Arg2>
	inline Pointer( const NEWStruct&, Arg1 arg1, Arg2 arg2 )
	{
		setPointerWithoutSelf( new T( arg1, arg2 ) );
	}
	
	/** ����������� �� ���������, 3-� ��������� */
	template<typename Arg1, typename Arg2, typename Arg3>
	inline Pointer( const NEWStruct&, Arg1 arg1, Arg2 arg2, Arg3 arg3 )
	{
		setPointerWithoutSelf( new T( arg1, arg2, arg3 ) );
	}

	/** ����������� �� ���������, 4-� ��������� */
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	inline Pointer( const NEWStruct&, Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4 )
	{
		setPointerWithoutSelf( new T( arg1, arg2, arg3, arg4 ) );
	}
	
	/** ���� ��������� ���., �� unlink */
	inline ~Pointer( )
	{
		if( pointer != 0 ) pointer->unlink( );
	}

	/** @return �������� ������ ��������� */
	inline T* getPointer( )
	{
		return pointer;
	}
	
	/** @return �������� const ������ ��������� */
	inline const T* getPointer( ) const
	{
		return pointer;
	}

	/** @return �������� ������ ��������� � �������� ����� static_cast � ���� P*/
	template<typename T1>
	inline T1* getStaticPointer( )
	{
		return static_cast<T1*>( pointer );
	}

	template<typename T1>
	inline T1* getConstPointer( ) const
	{
		return const_cast<T1*>( static_cast<T1*>( pointer ) );
	}
	
	/** @return �������� ������ ��������� � �������� ����� dynamic_cast � ���� T1*/
	template<typename T1>
	inline T1* getDynamicPointer( )
	{
		return dynamic_cast<T1*>( pointer );
	}
	
	/** ���������� ��������� */
	inline void setPointer( T* pointer )
	{
		if( this->pointer != 0 ) this->pointer->unlink( );
		setPointerWithoutSelf( pointer );
	}
	
	/** ��������� ����� */
	inline SelfType& operator = ( T* pointer )
	{
		setPointer( pointer );
		return *this;
	}
	
	inline SelfType& operator = ( const SelfType& cpointer )
	{
		setPointer( cpointer.pointer );
		return *this;
	}
	
	/**
	 * ��������� ���������. ������������ ���� NT ��������� T
	 */
	template<typename NoT>
	inline SelfType& operator = ( NoT& cpointer )
	{
		setPointer( cpointer.getPointer( ) );
		return *this;
	}
	
	/** ������ � ������ ����� '*' */
	inline T* operator * ( ) 
	{
		return pointer;
	}
	
	/** ������ � ������, ��� const,  ����� '*' */
	inline const T* operator * ( ) const
	{
		return pointer;
	}
	
	/** ������ � ������ ����� '->' */
	inline T* operator -> ( )
	{
		return pointer;
	}

	/** ������ � ������, ��� const,  ����� '->' */
	inline const T* operator -> ( ) const
	{
		return pointer;
	}

	/** @return true - ���� ��������� ����� */
	inline bool operator == ( const SelfType& cpointer ) const
	{
		return pointer == cpointer.pointer;
	}
	
	/** @return true - ���� ��������� ����� */
	template<typename NoT>
	inline bool operator == ( const NoT& cpointer ) const
	{
		return pointer == cpointer.getPointer( );
	}

	/** @return true - ���� ��������� �� ����� */
	inline bool operator != ( const SelfType& cpointer ) const
	{
		return pointer != cpointer.pointer;
	}
	
	/** @return true - ���� ��������� �� ����� */
	template<typename NoT>
	inline bool operator != ( const NoT& cpointer ) const
	{
		return pointer != cpointer.getPointer( );
	}
	
	inline operator bool( ) const
	{
		return !isEmpty( );
	}
	
	/** @return true - ���� ��������� ������ */
	inline bool isEmpty( ) const
	{
		return pointer == 0;
	}

	/** �������� ��������� ( unlink ) */
	inline void clear( )
	{
	    if (pointer != 0) {
		pointer->unlink( );
		pointer = 0;
	    }
	}
	
	inline void strip( )
	{
	    if (pointer != 0) {
		pointer->setLinkCount( pointer->getLinkCount( ) - 1 );
		pointer = 0;
	    }
	}

	/** ������� ������ */
	inline void construct( )
	{
		setPointer( new T( ) );
	}

private:
	/** ���������� ���������, ���� ��� ����� isEmpty */
	inline void setPointerWithoutSelf( T* pointer )
	{
		if( pointer != 0 ) pointer->link( );
		this->pointer = pointer;
	}
		
private:
	T* pointer;
};



#endif
