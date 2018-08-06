/* $Id: reglistext.cpp,v 1.1.2.7.6.5 2009/02/08 14:22:03 rufina Exp $
 *
 * ruffina, 2004
 */
#include <sstream>

#include "reglist.h"
#include "register-impl.h"
#include "fenia/object.h"
#include "nativeext.h"
#include "subr.h"

#include "dl_math.h"

using namespace Scripting;

NMI_INVOKE( RegList, random, "���������� ��������� ������� ������")
{
    size_t n;
    const_iterator i;
    
    if (size() == 0)
	return Register();

    n = number_range( 0, size() - 1 );
    for (i = begin( ); i != end( ) && n > 0; i++, n--)
	;
    
    return *i;
}

NMI_INVOKE( RegList, front , "���������� ������ ������� ������")
{
    return front();
}

NMI_INVOKE( RegList, pop_front, "������� ������ ������� ������" )
{
    if (empty( ))
	throw Scripting::Exception("list is already empty");

    pop_front( );
    self->changed();

    return Register( );
}

NMI_INVOKE( RegList, back , "���������� ��������� ������� ������")
{
    return back();
}

NMI_INVOKE( RegList, pop_back, "������� ��������� ������� ������" )
{
    if (empty( ))
	throw Scripting::Exception("list is already empty");

    pop_back( );
    self->changed();

    return Register( );
}


NMI_INVOKE( RegList, add , "��������� � ����� ������ ��� �������� �� ������ � ����������")
{
    insert(end( ), args.begin(), args.end());

    self->changed();

    return Register( self );
}

NMI_INVOKE( RegList, push_front, "��������� ������� � ������ ������" )
{
    if (args.empty( ))
	throw Scripting::NotEnoughArgumentsException( );
	
    push_front( args.front( ) );
    self->changed();

    return Register( );
}

NMI_INVOKE( RegList, push_back, "��������� ������� � ����� ������" )
{
    if (args.empty( ))
	throw Scripting::NotEnoughArgumentsException( );
	
    push_back( args.front( ) );
    self->changed();

    return Register( );
}

struct RemIfEq {
    RemIfEq(const Register &r) : reg(r) { }
    
    bool operator () (const Register &r) {
	return (reg == r).toBoolean( );
    }

    const Register &reg;
};

NMI_INVOKE( RegList, sub , "������� �� ������ ��� ��������� ��������� �� ������ � ����������")
{
    for(RegisterList::const_iterator i = args.begin(); i != args.end(); i++)
	remove_if( RemIfEq(*i) );

    self->changed();

    return Register( self );
}

NMI_INVOKE( RegList, has, "true ���� ��������� ������� ���������� � ������")
{
    if (args.empty( ))
	throw Scripting::NotEnoughArgumentsException( );
    
    const Register &arg = args.front( );

    for (const_iterator i = begin( ); i != end( ); i++)
	if ((arg == *i).toBoolean( ))
	    return true;

    return false;
}

NMI_INVOKE( RegList, size , "������ ������")
{
    return (int)size( );
}

struct RegisterWeakOrder {
    bool operator () ( const Register &k1, const Register &k2 ) {
	return (k1 < k2).toBoolean( );
    }
};

NMI_INVOKE( RegList, sort , "��������� ������ �� �����������")
{
    sort( RegisterWeakOrder( ) );
    self->changed();

    return Register( self );
}

struct RegisterBinPred {
    bool operator () ( const Register &k1, const Register &k2 ) {
	return (k1 == k2).toBoolean( );
    }
};

NMI_INVOKE( RegList, unique , "������� ������������� ��������")
{
    unique( RegisterBinPred( ) );
    self->changed();

    return Register( self );
}

NMI_INVOKE( RegList, clone , "������� ����� ������, ������ �����")
{
    RegList::Pointer rl(NEW);

    rl->assign(begin( ), end( ));

    Scripting::Object *obj = &Scripting::Object::manager->allocate();
    obj->setHandler(rl);

    return Register( obj );
}

NMI_INVOKE( RegList, api, "�������� ��� �������")
{
    ostringstream buf;
    
    traitsAPI<RegList>( buf );
    return Register( buf.str( ) );
}
