#pragma once
#include <string>
#include <windows.h>
#include <commdlg.h>  // For GetOpenFileName
#include <atlconv.h>
std::wstring OpenFileDialog()
{
	OPENFILENAME ofn;       // 공통 대화 상자 구조체
	wchar_t szFile[MAX_PATH];       // 파일 경로를 저장할 버퍼
	HWND hwnd = NULL;       // 소유자 윈도우 핸들 (NULL일 경우 기본 윈도우 사용)
	HANDLE hf = NULL;              // 파일 핸들

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return ofn.lpstrFile;  // 선택된 파일 경로를 반환
	}

	return std::wstring();  // 아무것도 선택되지 않으면 빈 문자열 반환
}

std::wstring SaveFileDialog()
{
	OPENFILENAME ofn;       // 공통 대화 상자 구조체
	wchar_t szFile[MAX_PATH];    // 파일 경로를 저장할 버퍼 (wchar_t로 설정)
	HWND hwnd = NULL;       // 소유자 윈도우 핸들 (NULL일 경우 기본 윈도우 사용)

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";  // 유니코드 문자열 사용
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileNameW(&ofn) == TRUE)  // 유니코드 버전 사용
	{
		return ofn.lpstrFile;  // 선택된 파일 경로를 반환
	}
	return std::wstring();  // 아무것도 선택되지 않으면 빈 문자열 반환
}



std::string WstrTostr(const std::wstring& in)
{
	if (in.empty())  // 입력 문자열이 비어 있는지 확인
	{
		return "";
	}

	USES_CONVERSION;  // W2A 사용 가능

	int __convert = static_cast<int>(wcslen(in.c_str()) + 1);
	if (__convert > 0)
	{
		// 스택 오버플로 방지를 위해 _malloca 사용
		CHAR* buffer = (CHAR*)_malloca(__convert * sizeof(WCHAR));
		if (buffer != nullptr)
		{
			AtlW2AHelper(buffer, in.c_str(), __convert * sizeof(WCHAR), _acp);
			std::string result(buffer);
			_freea(buffer);  // 메모리 해제
			return result;
		}
	}
	return "";
}

