/*****************************************************************************
		
		えせ Notepad
		
*****************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#define strchr		_tcschr
#define strrchr		_tcsrchr
#define strcpy		_tcscpy
#define strcpy_s	_tcscpy_s
#define strncpy_s	_tcsncpy_s
#define strcat_s	_tcscat_s
#define strlen		_tcslen
#define sprintf_s	_stprintf_s
#define fopen		_tfopen

/****************************************************************************/

int FileExist( LPTSTR szFileName ){
	FILE *fp = fopen( szFileName, _T( "r" ));
	
	if( fp ){
		fclose( fp );
		return 1;
	}
	
	return 0;
}

const TCHAR *g_szEditor[] = {
	_T( "C:\\Program Files\\xyzzy\\xyzzycli.exe" ),
	_T( "C:\\Program Files\\xyzzy\\xyzzy.exe" ),
	_T( "C:\\Program Files (x86)\\xyzzy\\xyzzycli.exe" ),
	_T( "C:\\Program Files (x86)\\xyzzy\\xyzzy.exe" ),
};

int WINAPI _tWinMain(
	HINSTANCE	hInst,
	HINSTANCE	hPrevInst,
	LPTSTR		lpCmdStr,
	int			iCmdShow ){
	
	TCHAR	szFileName[ MAX_PATH ];
	TCHAR	*pSt, *pEd;
	TCHAR	*szParam = lpCmdStr;
	
	// lpCmtStr が空文字でなく，"～" で囲まれていない場合，囲む
	if( lpCmdStr && strchr( lpCmdStr, _T( '"' )) == NULL ){
		
		// 先頭の空白以外文字をサーチ
		for( pSt = lpCmdStr; *pSt && *pSt < _T( ' ' ); ++ pSt );
		
		// 後端の空白以外文字をサーチ
		for(
			pEd = lpCmdStr + strlen( lpCmdStr ) - 1;
			pEd >= lpCmdStr && *pEd < _T( ' ' );
			--pEd
		);
		++pEd;
		
		if( pSt < pEd ){
			szFileName[ 0 ] = _T( '"' );
			strncpy_s( szFileName + 1, MAX_PATH - 1, pSt, pEd - pSt );
			strcpy( szFileName + ( pEd - pSt ) + 1, _T( "\"" ));
			
			szParam = szFileName;
		}
	}
	
	/* open the text file */
	int iCmd = FileExist( g_szEditor[ 0 ]) ? 0 : 2;
	if( GetKeyState( VK_SHIFT ) & 0x80000000 ) iCmd += 1;
	
	ShellExecute(
		NULL, _T( "open" ),
		g_szEditor[ iCmd ],
		szParam, NULL, iCmdShow
	);
	
	return( 0 );
}
