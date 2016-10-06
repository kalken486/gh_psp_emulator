////////////////////////////////////////////////////////
/// psp_ex.h
////////////////////////////////////////////////////////
#ifndef _PSP_EX_H
#define _PSP_EX_H
////////////////////////////////////////////////////////

static inline void memcpy4x( unsigned long* dest, unsigned long* src, short ct4x )
{
	for( ; ct4x>0 ; ct4x-- ){ *dest++ = *src++ ; } // dest++; src++ ; }
}

static inline void memset4x( unsigned long* dest, unsigned long set, short ct4x )
{
	for( ; ct4x>0 ; ct4x-- ){ *dest++ = set ; }
}


////////////////////////////////////////////////////////
#endif //_PSP_EX_H
////////////////////////////////////////////////////////
