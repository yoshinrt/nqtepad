/*****************************************************************************
		
		���� Notepad
		
*****************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include "Shlwapi.h"
#include "dds.h"

/*** ���K�\�����g�p����ꏊ�� std::wregex ���邽�߂̃w���p�֐� *******************/
// �����₷���ŗD��ŁC���s�����͋��߂Ȃ��D

std::unordered_map<std::wstring, std::wregex *> RegTbl;

std::wregex &regex_helper( const std::wstring& strRe, const char *file, const int line ){
	std::wregex **regex = &RegTbl[ strRe ];
	
	if( *regex == NULL ){
		try {
			*regex = new std::wregex( strRe, std::regex_constants::icase );
		}catch( std::regex_error& e ){
			DebugMsgD( L"%s(%d): %s\n", file, line, e.what());
			exit( 1 );
		}
	}
	
	return **regex;
}

#define re( reg ) regex_helper( std::wstring( L##reg ), __FILE__, __LINE__ )

/****************************************************************************/

int WINAPI wWinMain(
	HINSTANCE	hInst,
	HINSTANCE	hPrevInst,
	LPWSTR		lpCmdStr,
	int			iCmdShow
){
	static const WCHAR szEditor[][ 256 ] = {
		L"C:\\Program Files\\sakura\\sakura.exe",
		L"D:\\Program Files\\sakura\\sakura.exe",
		L"C:\\Program Files (x86)\\sakura\\sakura.exe",
		L"",
		L"",
		L"\0Last Last Last Last Last Last",
	};
	
	std::wstring strEditorArg( lpCmdStr );
	
	DebugMsgD( L"lpCmdStr: >>>%s<<<\n", lpCmdStr );
	
	// notepad.exe ���܂܂��ꍇ�C�����܂ł𖳎� && �Ȍ�̃p�����[�^�̓X�y�[�X����ł� 1�̃t�@�C���Ƃ݂Ȃ�
	if( std::regex_search( lpCmdStr, re( "\\bNotepad\\.exe\\b" ))){
		strEditorArg = std::regex_replace( lpCmdStr, re( ".*\\bnotepad\\.exe\"? *(.*)" ), L"$1" );
	}
	
	// strEdirotArg �� " ���܂܂�Ȃ��ꍇ�C" �ł�����
	if( wcschr( strEditorArg.c_str(), L'"' ) == nullptr ){
		strEditorArg = std::regex_replace( strEditorArg, re( "^\\s*(.*?)\\s*$" ), L"\"$1\"" );
	}
	
	// �G�f�B�^��T��
	int iCmd;
	for( iCmd = 0; szEditor[ iCmd ][ 0 ]; ++iCmd ){
		if( PathFileExists( szEditor[ iCmd ])) break;
	}
	
	DebugMsgD( L"exec: [%s] [%s]\n", szEditor[ iCmd ], strEditorArg.c_str());
	
	ShellExecute(
		NULL, L"open",
		szEditor[ iCmd ],
		strEditorArg.c_str(), nullptr, iCmdShow
	);
	
	return( 0 );
}
