/*****************************************************************************

		dds.h -- Deyu Deyu Software's standard include file
		Copyright(C) 1997 - 2001 by Deyu Deyu Software

*****************************************************************************/

#ifndef _DDS_H
#define _DDS_H

#define	Case		break; case
#define Default		break; default
#define until( x )	while( !( x ))
#define INLINE		static __inline

/*** new type ***************************************************************/

typedef unsigned		UINT;
typedef unsigned char	UCHAR;
typedef int				BOOL;

/*** debug macros ***********************************************************/

#if defined _DEBUG && !defined DEBUG
# define DEBUG
#endif

#ifdef DEBUG
# define IfDebug			if( 1 )
# define IfNoDebug			if( 0 )
# define DebugCmd( x )		x
# define NoDebugCmd( x )
# define DebugParam( x, y )	( x )

/*** output debug message ***************************************************/

#include <stdio.h>
#include <tchar.h>
#include <stdarg.h>

#define DEBUG_SPRINTF_BUFSIZE	1024
#define DEBUG_MESSAGE_HEADER	_T( "DEBUG:" )
#ifdef _MSC_VER
# define C_DECL __cdecl
#else
# define C_DECL
#endif

static _TCHAR * C_DECL DebugSPrintf( _TCHAR *szFormat, va_list arg ){
	
	static _TCHAR	szMsg[ DEBUG_SPRINTF_BUFSIZE ];
	
#	ifdef _MSC_VER
		_vsntprintf_s( szMsg, DEBUG_SPRINTF_BUFSIZE, _TRUNCATE, szFormat, arg );
#	else /* _MSC_VER */
		vsprintf( szMsg, szFormat, arg );
#	endif /* _MSC_VER */
	
	szMsg[ DEBUG_SPRINTF_BUFSIZE - 1 ] = '\0';
	
	return( szMsg );
}
#undef DEBUG_SPRINTF_BUFSIZE

static int C_DECL DebugMsg( _TCHAR *szFormat, ... ){
	
	va_list	arg;
	
	va_start( arg, szFormat );
	_fputts( DEBUG_MESSAGE_HEADER, stdout );
	_vtprintf( szFormat, arg );
	va_end( arg );
	
	return( 0 );
}

#ifdef _INC_WINDOWS
static int C_DECL DebugMsgD( _TCHAR *szFormat, ... ){
	
	va_list	arg;
	
	va_start( arg, szFormat );
	OutputDebugString( DEBUG_MESSAGE_HEADER );
	OutputDebugString( DebugSPrintf( szFormat, arg ));
	va_end( arg );
	
	return( 0 );
}

static int C_DECL DebugMsgW( _TCHAR *szFormat, ... ){
	
	va_list	arg;
	
	va_start( arg, szFormat );	
	MessageBox( NULL, DebugSPrintf( szFormat, arg ), _T( "DEBUG message" ), MB_OK );
	va_end( arg );
	
	return( 0 );
}

static int C_DECL DebugPrintfD( _TCHAR *szFormat, ... ){
	
	va_list	arg;
	
	va_start( arg, szFormat );
	OutputDebugString( DebugSPrintf( szFormat, arg ));
	va_end( arg );
	
	return( 0 );
}

#endif	/* _INC_WINDOWS */
#undef DEBUG_MESSAGE_HEADER
#ifdef C_DECL
# undef C_DECL
#endif

/*** no debug macros ********************************************************/

#else	/* _DEBUG */
# ifndef _MSC_VER
#  define __noop			0&&
# endif
# define IfDebug			if( 0 )
# define IfNoDebug			if( 1 )
# define DebugCmd( x )
# define NoDebugCmd( x )	x
# define DebugParam( x, y )	( y )
# define DebugMsg			__noop
# define DebugMsgW			__noop
# define DebugMsgD			__noop
# define DebugPrintf		__noop
# define DebugPrintfD		__noop
#endif	/* _DEBUG */

/*** constants definition ***************************************************/

#define REGISTORY_KEY_DDS	"Software\\DeyuDeyu\\"

#endif	/* !def _DDS_H */
