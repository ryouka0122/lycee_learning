#ifndef __FILE_SELECTOR__HEADER__
#define __FILE_SELECTOR__HEADER__

#include "main.h"

namespace lycee {
	
namespace dialog {

	enum FileSelectorMode {
		OPEN_MODE,
		SAVE_MODE,
	};

	class FileSelector {
	public:
		virtual ~FileSelector();
		explicit FileSelector(HWND _hWnd);
	
		void setTitle(tstring const& _title);

		bool show(FileSelectorMode mode);

		tstring getSelectFilePath();

	private:
		HWND hWnd;
		tstring title;
		tstring selectFilePath;

		;
	};





}	// dialog

}	// lycee
#endif	// __FILE_SELECTOR__HEADER__
