#include "Filedialog.h"
/*
	OpenFileDialog() 
	Can Open Window File Box
	And Select file 

	Output Select FilePaht
*/


std::wstring OpenFileDialog() 
{
	OPENFILENAME ofn;       // ���� ��ȭ ���� ����ü
	wchar_t szFile[MAX_PATH];       // ���� ��θ� ������ ����
	HWND hwnd = NULL;       // ������ ������ �ڵ� (NULL�� ��� �⺻ ������ ���)
	HANDLE hf = NULL;              // ���� �ڵ�

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
		return ofn.lpstrFile;  // ���õ� ���� ��θ� ��ȯ
	}

	return std::wstring();  // �ƹ��͵� ���õ��� ������ �� ���ڿ� ��ȯ
}
/*
	OpenFileDialog()
	Can Open Window File Box
	And Select Image file

	Output Select Image FilePath
*/


std::wstring OpenImageFileDialog() 
{
	OPENFILENAME ofn;       // ���� ��ȭ ���� ����ü
	wchar_t szFile[MAX_PATH];       // ���� ��θ� ������ ����
	HWND hwnd = NULL;       // ������ ������ �ڵ� (NULL�� ��� �⺻ ������ ���)
	HANDLE hf = NULL;              // ���� �ڵ�

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	// �̹��� ���� ���� ���� (PNG, JPG, GIF, ��� ����)
	ofn.lpstrFilter = L"Image Files\0*.png;*.jpg;*.gif\0All Files\0*.*\0";
	ofn.nFilterIndex = 1;  // �⺻ ���� �ε��� (1: �̹��� ����)
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return ofn.lpstrFile;  // ���õ� ���� ��θ� ��ȯ
	}

	return std::wstring();  // �ƹ��͵� ���õ��� ������ �� ���ڿ� ��ȯ
}


std::wstring SaveFileDialog(const std::string& currentFile)
{
	OPENFILENAME ofn;         // ���� ��ȭ ���� ����ü
	wchar_t szFile[MAX_PATH];  // ���� ��θ� ������ ���� (wchar_t�� ����)
	HWND hwnd = NULL;          // ������ ������ �ڵ� (NULL�� ��� �⺻ ������ ���)

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;

	// ���۸� ��������� �ʱ�ȭ
	ZeroMemory(szFile, sizeof(szFile));  // �迭 ��ü�� 0���� �ʱ�ȭ

	// std::string�� std::wstring���� ��ȯ
	std::wstring wCurrentFile(currentFile.begin(), currentFile.end());
	wcscpy_s(szFile, wCurrentFile.c_str());  // ��ȯ�� ��θ� szFile�� ����

	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
	ofn.lpstrFilter = L"JSON Files\0*.json\0All Files\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrDefExt = L"json";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// �����ڵ� ���� ���
	if (GetSaveFileNameW(&ofn) == TRUE)
	{
		return ofn.lpstrFile;  // ���õ� ���� ��θ� ��ȯ
	}

	return std::wstring();  // �ƹ��͵� ���õ��� ������ �� ���ڿ� ��ȯ
}


/*
	Input wstring

	Convert wString to String

	Output string
*/
std::string WstrTostr(const std::wstring& in) 
{
	if (in.empty())  // �Է� ���ڿ��� ��� �ִ��� Ȯ��
	{
		return "";
	}

	USES_CONVERSION;  // W2A ��� ����

	int __convert = static_cast<int>(wcslen(in.c_str()) + 1);
	if (__convert > 0)
	{
		// ���� �����÷� ������ ���� _malloca ���
		CHAR* buffer = (CHAR*)_malloca(__convert * sizeof(WCHAR));
		if (buffer != nullptr)
		{
			AtlW2AHelper(buffer, in.c_str(), __convert * sizeof(WCHAR), _acp);
			std::string result(buffer);
			_freea(buffer);  // �޸� ����
			return result;
		}
	}
	return "";
}

