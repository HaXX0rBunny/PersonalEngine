#pragma once
#include <string>
#include <windows.h>
#include <commdlg.h>  // For GetOpenFileName
#include <atlconv.h>


std::wstring OpenFileDialog();
std::wstring OpenImageFileDialog();
//std::wstring SaveFileDialog();
std::wstring SaveFileDialog(const std::string& filepath = '\0');
std::string WstrTostr(const std::wstring& in);