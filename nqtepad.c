/*****************************************************************************
		
		���� Notepad
		
1999.07.20	Wz macro �� IfDoc �̋@�\���ڐA
1999.12.16	�����������t�@�C���T�C�Y�� .doc ���J���ƕs���I�����Ă�
1999.12.26	�t�@�C���S�̂�ǂ݂���� szWordID ���T�[�`
1999.12.28	�N���p�����[�^���^�����Ȃ������Ƃ��ɑΉ�
2000.04.01	word �� ShellExecute ����Ǝ��ʂ̂ŁC���� winword �����s
2000.06.15	winword �̑��݂������F��
2000.08.20	Win2000 �̃o�[�W�����`�F�b�N�΍�ɁC�{�Ƃ� Ver �����R�s�[
2012.07.05	64bit �o�[�W����w / doc �I�[�v���@�\�폜

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
