#include "main.h"
#include "lycee_learning.h"

#include "FileSelector.h"
#include "MachineLearning.h"

void selectDataFile(lycee::dialog::FileSelector &fileSelector, tstring const &title, HWND hItem) {
	fileSelector.setTitle(title);
	if (!fileSelector.show(lycee::dialog::FileSelectorMode::OPEN_MODE)) {
		return;
	}
	Edit_SetText(hItem, fileSelector.getSelectFilePath().c_str());
	return;
}

void selectRandomDataFile(lycee::dialog::FileSelector &fileSelector, tstring const &title, HWND hItem) {
	fileSelector.setTitle(title);
	if (!fileSelector.show(lycee::dialog::FileSelectorMode::SAVE_MODE)) {
		return;
	}
	// 選んだパスを取得
	tstring path = fileSelector.getSelectFilePath();

	// ランダム文書の生成
	lycee::machine_learning::generateRandomCorpus(path, 30, TEXT("  abc1111111122222222333333333"));

	// そのまま使えるようにテキストボックスに設定
	Edit_SetText(hItem, path.c_str());
	return;
}

tstring getItemText(HWND hItem) {
	tchar path[MAX_PATH] = { 0 };
	Edit_GetText(hItem, path, MAX_PATH);
	return tstring(path);
}

void calculateTFIDF(HWND hDlg) {
	const static tstring CRLF = TEXT("\r\n");
	lycee::machine_learning::tf_idf calculator(new lycee::machine_learning::char_delimiter());
	
	tstring word = getItemText(GetDlgItem(hDlg, IDC_EDIT_WORD));
	if (word.size() == 0) {
		return;
	}
	// 入力した最初の文字だけ使う
	word = word.substr(0, 1);

	tstring document = getItemText(GetDlgItem(hDlg, IDC_EDIT_DOCUMENT));
	calculator.setDocument(document);

	std::deque<int> tfList = calculator.getTF(word);
	double idf = calculator.getIDF(word);
	std::deque<tstring> rawData = calculator.getRawData();

	tstringstream ss;
	ss << "word: " << word << CRLF;
	ss << "idf : " << idf << CRLF;
	auto tf = tfList.begin();
	for (auto line = rawData.begin(); line != rawData.end(); line++, tf++) {
		ss << *line << " : tf=" << *tf << CRLF;
	}
	ss << std::ends;
	Edit_SetText(GetDlgItem(hDlg, IDC_EDITBOX_RESULT), ss.str().c_str());
	return;
}



LRESULT CALLBACK DialogProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static lycee::dialog::FileSelector fileSelector(hDlg);

	switch (msg) {
	case WM_CLOSE:
		// 終了確認
		if (IDOK == MessageBox(hDlg, TEXT("終了しますか？"), TEXT("確認"), MB_ICONINFORMATION | MB_OKCANCEL)) {
			// OKを押したので終了
			EndDialog(hDlg, 1);
		}
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_GENERATE:
			selectRandomDataFile(fileSelector, TEXT("ランダムデータの生成先の指定"), GetDlgItem(hDlg, IDC_EDIT_DOCUMENT));
			break;
		case IDC_BUTTON_SEARCH_DOCUMENT:
			selectDataFile(fileSelector, TEXT("文書データの選択"), GetDlgItem(hDlg, IDC_EDIT_DOCUMENT));
			break;
		case IDC_BUTTON_SEARCH_WEIGHT:
			selectDataFile(fileSelector, TEXT("重みデータの選択"), GetDlgItem(hDlg, IDC_EDIT_WEIGHT));
			break;
		case IDC_BUTTON_EXECUTE:
			calculateTFIDF(hDlg);
			break;
		}
		return TRUE;
	}
	return FALSE;
}


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	int ret = DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, (DLGPROC)DialogProc);

	tstringstream ss;
	ss << ret << std::endl << std::ends;
	OutputDebugString(ss.str().c_str());

	return 0;
}
