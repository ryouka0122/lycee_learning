// ---------------------------------------------
//
// tf_idf
// ファイルの1行ごとを文書と定義し，任意の単位に分解したものを元に
// TF-IDF値を算出するクラス
//
#ifndef __LYCEE__MACHINE_LEARNING__HEADER__
#define __LYCEE__MACHINE_LEARNING__HEADER__

#include "main.h"

namespace lycee {

namespace machine_learning {

	void generateRandomCorpus(tstring const& path, int linesize, tstring const& pattern);
	


	// -----------------------------------------------------------
	// 文書分解ロジック
	//

	// 文字分解ファンクタ（基底クラス）
	struct delimiter {
		virtual ~delimiter()=0;
		virtual std::deque<tstring> split(tstring const& document)=0;
	};

	// 半角スペースを区切り文字に分解するファンクタ
	struct word_delimiter : virtual public delimiter {
		virtual ~word_delimiter();
		virtual std::deque<tstring> split(tstring const& document);
	};

	// 1文字ごとに分解するファンクタ
	struct char_delimiter : virtual public delimiter {
		virtual ~char_delimiter();
		virtual std::deque<tstring> split(tstring const& document);
	};


	// ---------------------------------------------
	//
	//
	class tf_idf {
	public:
		// 型定義
		typedef std::deque<tstring> TermList;
		typedef std::deque<TermList> Corpus;

		// デストラクタ
		virtual ~tf_idf();
		
		// コンストラクタ
		explicit tf_idf(delimiter *_delimiter);
		
		
		// 文書を設定
		void setDocument(tstring const& filepath);

		std::deque<tstring> getRawData() const {
			return this->rawData;
		}

		Corpus getCorpus() const {
			return this->corpus;
		}

		
		// TF値の算出
		std::deque<int> getTF(tstring const& word);
		
		// IDF値の算出
		double getIDF(tstring const& word);
		
		// TF-IDF値の算出
		std::deque<double> getTFIDF(tstring const& word);
		
	private:
		// 分解器
		delimiter *pDelimiter;
		
		// 文書データ（RawData）
		std::deque<tstring> rawData;

		// 文書情報
		std::deque< TermList > corpus;

	};


}	// machine_learning

}	// lycee
#endif	// __LYCEE__MACHINE_LEARNING__HEADER__