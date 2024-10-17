#include "Filedialog.h"
/*
	OpenFileDialog() 
	Can Open Window File Box
	And Select file 

	Output Select FilePaht
*/


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
	ofn.lpstrFilter = L"JSON Files\0*.json\0All Files\0*.*\0";
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
/*
	OpenFileDialog()
	Can Open Window File Box
	And Select Image file

	Output Select Image FilePath
*/


std::wstring OpenImageFileDialog() 
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
	// 이미지 파일 필터 설정 (PNG, JPG, GIF, 모든 파일)
	ofn.lpstrFilter = L"Image Files\0*.png;*.jpg;*.gif\0All Files\0*.*\0";
	ofn.nFilterIndex = 1;  // 기본 필터 인덱스 (1: 이미지 파일)
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


std::wstring SaveFileDialog(const std::string& currentFile)
{
	OPENFILENAME ofn;         // 공통 대화 상자 구조체
	wchar_t szFile[MAX_PATH];  // 파일 경로를 저장할 버퍼 (wchar_t로 설정)
	HWND hwnd = NULL;          // 소유자 윈도우 핸들 (NULL일 경우 기본 윈도우 사용)

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;

	// 버퍼를 명시적으로 초기화
	ZeroMemory(szFile, sizeof(szFile));  // 배열 전체를 0으로 초기화

	// std::string을 std::wstring으로 변환
	std::wstring wCurrentFile(currentFile.begin(), currentFile.end());
	wcscpy_s(szFile, wCurrentFile.c_str());  // 변환된 경로를 szFile에 복사

	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
	ofn.lpstrFilter = L"JSON Files\0*.json\0All Files\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrDefExt = L"json";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// 유니코드 버전 사용
	if (GetSaveFileNameW(&ofn) == TRUE)
	{
		return ofn.lpstrFile;  // 선택된 파일 경로를 반환
	}

	return std::wstring();  // 아무것도 선택되지 않으면 빈 문자열 반환
}


/*
	Input wstring

	Convert wString to String

	Output string
*/
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

