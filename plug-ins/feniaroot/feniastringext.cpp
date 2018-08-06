/* $Id: feniastringext.cpp,v 1.1.2.8.6.14 2009/10/11 21:41:08 margo Exp $
 *
 * ruffina, 2004
 */

#include "register-impl.h"
#include "reglist.h"
#include "char.h"
#include "dl_strings.h"
#include "dl_ctype.h"
#include "regexp.h"
#include "nativeext.h"
#include "feniastring.h"
#include "idcontainer.h"
#include "regcontainer.h"
#include "reglist.h"

namespace Scripting {

NMI_INVOKE(FeniaString, size, "")
{
    return (int)size();
}

NMI_INVOKE(FeniaString, capitalize, "")
{
    DLString str = *this;
    str.capitalize();
    return Register( str );
}

NMI_INVOKE(FeniaString, trim, "")
{
    DLString str = *this;
    str.stripWhiteSpace();
    return Register( str );
}

NMI_INVOKE(FeniaString, strPrefix, "")
{
    if (args.empty( ))
       throw Scripting::NotEnoughArgumentsException( );
    
    if (empty( ))
        return false;
    return strPrefix( args.front( ).toString( ) );
}

NMI_INVOKE(FeniaString, ruscase, "")
{
    int cse = 1;
    
    if (!args.empty())
        cse = args.front().toNumber( );

    return Register( ruscase( cse + '0' ) );
}

NMI_INVOKE(FeniaString, getOneArgument, "���������� ������ ����� ��� ������ ����� � ��������")
{
    DLString str = *this;
    return str.getOneArgument( );
}

NMI_INVOKE(FeniaString, cutOneArgument, "���������� ������ ��� ������� ����� (��� ��� ������ ����� � ��������)")
{
    DLString str = *this;
    str.getOneArgument( );
    return str;
}

NMI_INVOKE(FeniaString, upperFirstChar, "���������� �� ��  ������, �� � ������� �����")
{
    DLString str = *this;
    str.upperFirstCharacter();
    return Register( str );
}

NMI_INVOKE(FeniaString, matchAndReplace, "(pattern, str) �������� � ������ ������ ��� ��������� $1..$9 �� ��������������� ����������") 
{
    if (args.size() != 2)
        throw NotEnoughArgumentsException();

    DLString pattern = args.front().toString();
    DLString str = args.back().toString();
    DLString result = *this;
    
    try {
        RegExp re( pattern.c_str() );
        RegExp::MatchVector mv;
        
        mv = re.subexpr( str.c_str() );
        if (mv.size() == 0)
            return result;

        for (int i = mv.size() - 1; i >= 0; i--) {
            DLString num;
            num << "$" << i + 1;
            result.replaces(num, mv[i]);            
        }
        
    } catch( const std::exception &e ) {
        throw CustomException(e.what());
    }

    return result;
}

NMI_INVOKE(FeniaString, match, "")
{
    if (args.empty())
        throw NotEnoughArgumentsException();
    
    try {
        RegExp re( args.front().toString().c_str() );

        return re.match( c_str() );
    } catch( const std::exception &e ) {
        throw CustomException(e.what());
    }
}

NMI_INVOKE(FeniaString, matchCase, "")
{
    if (args.empty())
        throw NotEnoughArgumentsException();
        
    try {
        RegExp re( args.front().toString().c_str(), true );

        return re.match( c_str() );
    } catch( const std::exception &e ) {
        throw IllegalArgumentException();
    }
}

NMI_INVOKE(FeniaString, isName, "")
{
    if (args.empty())
        throw NotEnoughArgumentsException();
        
    return isName( args.front().toString().c_str() );
}

NMI_INVOKE(FeniaString, is_name, "")
{
    if (args.empty())
        throw NotEnoughArgumentsException();
        
    const DLString &a = args.front().toString();
    char l[size()+1], r[a.size()+1];

    ::copy(begin(), end(), l);
    l[size()] = 0;

    ::copy(a.begin(), a.end(), r);
    r[a.size()] = 0;
    
    return is_name( l, r );
}

NMI_INVOKE(FeniaString, substr, "���������� ���������, ������ �������� - �������� ������������ ������, ������ - ����� ���������, �� ��������� - �� �����")
{
    if (args.empty())
        throw NotEnoughArgumentsException();
        
    try {
        RegisterList::const_iterator iter;
        int i1, i2 = std::string::npos;

        iter = args.begin();
        i1 = iter->toNumber();

        if (++iter != args.end())
            i2 = iter->toNumber();
        
        return substr( i1, i2 );
    } catch( const std::exception &e ) {
        throw IllegalArgumentException();
    }
}

NMI_INVOKE(FeniaString, stripColour, "")
{
    DLString rc;
    
    for(iterator i = begin(); i != end();) {
        char c = *i++;
        
        if(c == '{') {
            if(*i++ == '{')
                rc += '{';
        } else
            rc += c;
    }
    
    return rc;
}


NMI_INVOKE(FeniaString, contains, "")
{
    char strbuf[size( )];
    char *p_strbuf = strbuf;
    char *s_tok;
    
    if (args.empty())
        throw NotEnoughArgumentsException();
        
    const char *arg = args.front( ).toString( ).c_str( );
    strcpy(strbuf, c_str( ));

    while (( s_tok = strtok( p_strbuf, " " ) ) != NULL) {
        p_strbuf = NULL;

        if (::is_name( s_tok, arg ))
            return true;
    }
    
    return false;
}

NMI_INVOKE(FeniaString, split, "�������� - �����������. ���������� List �� ��������")
{
    char delim;
    size_type pos1, pos2;
    RegList::Pointer list(NEW);
    
    if (args.empty() || args.front().toString().empty())
        delim = '\n';
    else
        delim = args.front().toString().at(0);
        
        
    pos1 = pos2 = 0;

    do {
        pos2 = find(delim, pos1);
        
        if (pos2 == DLString::npos) 
            pos2 = size();
        
        list->push_back(Register(substr(pos1, pos2 - pos1)));
        pos1 = pos2 + 1;
    }
    while (pos1 < size());

    Object *obj = &Object::manager->allocate();
    obj->setHandler(list);

    return Register(obj);
}

NMI_INVOKE(FeniaString, api, "")
{
    ostringstream buf;
    
    traitsAPI<FeniaString>( buf );
    return Register( buf.str( ) );
}


NMI_INVOKE(FeniaString, replace, "�������� ��� ��������� ������ ��������� �� ������")
{
    DLString aStr, bStr;
    RegisterList::const_iterator iter;
    
    if (args.size() < 2)
        throw NotEnoughArgumentsException();

    iter = args.begin();
    aStr = iter->toString();
    bStr = (++iter)->toString();

    DLString r = *this;
    r.replaces( aStr, bStr );
    return r;
}

NMI_INVOKE(FeniaString, isRussian, "���������� true ���� ������ �� ����� � �������� ������ ������� �����")
{
    if (empty( ))
        return false;

    for (iterator i = begin(); i != end(); i++) 
        if (!dl_isrusalpha( *i ))
            return false;

    return true;
}
NMI_INVOKE(FeniaString, toLower, "")
{
    DLString s = *this;
    for( DLString::size_type pos = 0; pos < s.length( ); pos++ )
    {
            char& ch = s.at( pos );
            ch = Char::lower( ch );
    }
    return s;
}
}

