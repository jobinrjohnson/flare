add_library(
        types
        STATIC

        implementation/BaseType.cpp BaseType.h
        implementation/IntType.cpp IntType.h
        implementation/StringType.cpp StringType.h
        implementation/ClassObjectType.cpp ClassObjectType.h
        implementation/BoolType.cpp BoolType.h
        implementation/DoubleType.cpp DoubleType.h
        implementation/VoidType.cpp VoidType.h
)