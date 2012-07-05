/*****************************************************************************
		
		えせ Notepad
		
1999.07.20	Wz macro の IfDoc の機能を移植
1999.12.16	ごく小さいファイルサイズの .doc を開くと不正終了してた
1999.12.26	ファイル全体を読みこんで szWordID をサーチ
1999.12.28	起動パラメータが与えられなかったときに対応
2000.04.01	word を ShellExecute すると死ぬので，直接 winword を実行
2000.06.15	winword の存在を自動認識
2000.08.20	Win2000 のバージョンチェック対策に，本家の Ver 情報をコピー
2012.07.04	64bit 版 www

*****************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#ifdef _WIN64
	#define CMD_TXT		_T( "C:\\Program Files (x86)\\WZ EDITOR\\wzeditor.exe" )
#else
	#define CMD_TXT		_T( "C:\\Program Files\\WZ Editor\\wzeditor.exe" )
#endif

#define CMD_DOC		_T( "C:\\Program Files\\Accessories\\WORDPAD.EXE" )
#define CMD_WORD	_T( "C:\\Program Files\\Microsoft Office\\Office\\WINWORD.EXE" )

const WCHAR	szWordID[] = L"WordDocument";

/****************************************************************************/

int WINAPI _tWinMain(
	HINSTANCE	hInst,
	HINSTANCE	hPrevInst,
	LPTSTR		lpCmdStr,
	int			iCmdShow ){
	
	TCHAR	szFileName[ MAX_PATH ],
			szFileNameQuated[ MAX_PATH ],
			szExecDocFile[ MAX_PATH ];
	
	TCHAR	*pBuf, *p;
	FILE	*fp;
	UINT	uFileSize, u;
	BOOL	bDoc = FALSE;
	
	do{
		/* make up file name */
		
		if( *lpCmdStr == _T( '\0' )){
			/* param is NULL */
			*szFileNameQuated = _T( '\0' );
			break;
			
		}else if(( p = _tcschr( lpCmdStr, _T( '"' )))== NULL ){
			/* file name is not quated. */
			_tcscpy( szFileName, lpCmdStr );
			
		}else{
			/* file name is quated. */
			_tcscpy( szFileName, ++p );
			if(( p = _tcschr( szFileName, _T( '"' )))!= NULL ) *p = _T( '\0' );
		}
		
		_stprintf( szFileNameQuated, _T( "\"%s\"" ), szFileName );
		
		/* is word file? */
		
		if(( fp = _tfopen( szFileName, _T( "rb" )))== NULL ) break;
		
		/* get file size & alloc memory */
		fseek( fp, 0, SEEK_END );
		uFileSize = ftell( fp );
		fseek( fp, 0, SEEK_SET );
		
		if(( pBuf =( TCHAR *)malloc( uFileSize ))== NULL ) break;
		
		/* read file */
		fread( pBuf, sizeof( TCHAR ), uFileSize, fp );
		fclose( fp );
		
		if( uFileSize <= sizeof( szWordID )) break;
		
		/* search Word ID */
		for( u = 0; u <= uFileSize - sizeof( szWordID ); ++u ){
			if( pBuf[ u ]== *szWordID &&
				!memcmp( &pBuf[ u ], szWordID, sizeof( szWordID )))
				break;
		}
		
		free( pBuf );
		if( u > uFileSize - sizeof( szWordID )) break;
		
		/* open the word file */
		bDoc = TRUE;
		
		// is winword exist?
		if(( UINT )FindExecutable( CMD_WORD, NULL, szExecDocFile ) <= 32 )
			_tcscpy( szExecDocFile, CMD_DOC );
		
	}while( 0 );
	
	/* open the text file */
	
	ShellExecute( NULL, _T( "open" ), bDoc ? szExecDocFile : CMD_TXT,
		szFileNameQuated, NULL, iCmdShow );
	
	return( 0 );
}
