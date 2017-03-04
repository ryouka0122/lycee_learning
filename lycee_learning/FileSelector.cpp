#include "FileSelector.h"

lycee::dialog::FileSelector::~FileSelector()
{
}

lycee::dialog::FileSelector::FileSelector(HWND _hWnd)
	: hWnd(_hWnd), title(TEXT("ファイル選択ダイアログ")), selectFilePath()
{
}

void lycee::dialog::FileSelector::setTitle(tstring const & _title)
{
	this->title = _title;
}

bool lycee::dialog::FileSelector::show(FileSelectorMode mode)
{
	TCHAR filepath[MAX_PATH] = {0};
	this->selectFilePath = filepath;

	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.lpstrFilter = TEXT("All Files(*.*)\0*.*\0\0");
	ofn.lpstrFile = filepath;
	ofn.nMaxFile = MAX_PATH;

	BOOL result = FALSE;
	if (FileSelectorMode::OPEN_MODE == mode) {
		result = GetOpenFileName(&ofn);
	}
	else {
		// save mode
		ofn.Flags |= OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;
		result = GetSaveFileName(&ofn);
	}
	if (TRUE==result) {
		this->selectFilePath.assign(ofn.lpstrFile);
	}
	return !!result;
}

tstring lycee::dialog::FileSelector::getSelectFilePath()
{
	return this->selectFilePath;
}
