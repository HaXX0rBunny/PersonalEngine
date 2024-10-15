#pragma once
#include <string>
#include <windows.h>
#include <commdlg.h>  // For GetOpenFileName
#include <atlconv.h>
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
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
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

std::wstring SaveFileDialog()
{
	OPENFILENAME ofn;       // ���� ��ȭ ���� ����ü
	wchar_t szFile[MAX_PATH];    // ���� ��θ� ������ ���� (wchar_t�� ����)
	HWND hwnd = NULL;       // ������ ������ �ڵ� (NULL�� ��� �⺻ ������ ���)

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";  // �����ڵ� ���ڿ� ���
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileNameW(&ofn) == TRUE)  // �����ڵ� ���� ���
	{
		return ofn.lpstrFile;  // ���õ� ���� ��θ� ��ȯ
	}
	return std::wstring();  // �ƹ��͵� ���õ��� ������ �� ���ڿ� ��ȯ
}



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

