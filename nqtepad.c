/*****************************************************************************
		
		えせ Notepad
		
1999.07.20	Wz macro の IfDoc の機能を移植
1999.12.16	ごく小さいファイルサイズの .doc を開くと不正終了してた
1999.12.26	ファイル全体を読みこんで szWordID をサーチ
1999.12.28	起動パラメータが与えられなかったときに対応
2000.04.01	word を ShellExecute すると死ぬので，直接 winword を実行
2000.06.15	winword の存在を自動認識
2000.08.20	Win2000 のバージョンチェック対策に，本家の Ver 情報をコピー
2012.07.05	64bit バージョンw / doc オープン機能削除

*****************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#define CMD_TXT		_T( "C:\\Program Files\\WZ Editor\\wzeditor.exe" )
#define CMD_TXT32	_T( "C:\\Program Files (x86)\\WZ Editor\\wzeditor.exe" )

#define strchr		_tcsrchr
#define strcpy_s	_tcscpy_s
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

int WINAPI _tWinMain(
	HINSTANCE	hInst,
	HINSTANCE	hPrevInst,
	LPTSTR		lpCmdStr,
	int			iCmdShow ){
	
	TCHAR	szFileName[ MAX_PATH ];
	TCHAR	*p;
	
	if(
		*lpCmdStr != _T( '\0' ) &&
		( p = strchr( lpCmdStr, _T( '"' ))) == NULL
	){
		/* file name is not quated. */
		sprintf_s( szFileName, MAX_PATH, _T( "\"%s\"" ), lpCmdStr );
		p = szFileName;
	}else{
		p = lpCmdStr;
	}
	
	/* open the text file */
	ShellExecute(
		NULL, _T( "open" ),
		FileExist( CMD_TXT32 ) ? CMD_TXT32 : CMD_TXT,
		p, NULL, iCmdShow
	);
	
	return( 0 );
}
