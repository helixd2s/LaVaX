// build.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "build.h"


// This is an example of an exported variable
BUILD_API int nbuild=0;

// This is an example of an exported function.
BUILD_API int fnbuild(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Cbuild::Cbuild()
{
    return;
}
