#ifndef REW_BUILTIN_TYPE_INFO_HPP
#define REW_BUILTIN_TYPE_INFO_HPP

#include <typeinfo> // type_info

#include <Rew/Reflectable.hpp>
#include <Rew/Common.hpp>

REFLECTABLE_DECLARATION(std::type_info)
    BUILTIN_REFLECTABLE()
REFLECTABLE_DECLARATION_INIT()

REFLECTABLE(std::type_info)
    FUNCTION(operator==)

    #ifndef REW_CORE_MINIMAL
    FUNCTION(before)
    #endif // REW_CRE_MINIMAL

    FUNCTION(hash_code)
    FUNCTION(name)
REFLECTABLE_INIT()

#endif // REW_BUILTIN_TYPE_INFO_HPP
