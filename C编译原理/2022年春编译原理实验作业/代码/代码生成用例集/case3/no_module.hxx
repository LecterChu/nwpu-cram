/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from no_module.idl using "idltoc".
The idltoc tool is part of the RTI Data Distribution Service distribution.
For more information, type 'idltoc -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef no_module_h
#define no_module_h

#ifndef rti_me_cpp_hxx
#include "rti_me_cpp.hxx"
#endif

#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif
#else
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

struct ASeq;
class ATypeSupport;
class ADataWriter;
class ADataReader;

class A 
{
  public:
    typedef struct ASeq Seq;
    typedef ATypeSupport TypeSupport;
    typedef ADataWriter DataWriter;
    typedef ADataReader DataReader;

	CDR_Short i1=10;
};

extern const char *ATYPENAME;

REDA_DEFINE_SEQUENCE_STRUCT(ASeq, A);

REDA_DEFINE_SEQUENCE_IN_C(ASeq, A);


NDDSUSERDllExport extern RTI_BOOL
A_initialize(A* sample)
{
    CDR_Primitive_init_Short(&sample->i1);
    return RTI_TRUE;
}

NDDSUSERDllExport extern RTI_BOOL
A_finalize(A* sample)
{
    UNUSED_ARG(sample);
    return RTI_TRUE;
}



#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
#endif

#endif /* no_module */
