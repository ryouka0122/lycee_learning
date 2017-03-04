#include "MachineLearning.h"


void lycee::machine_learning::generateRandomCorpus(tstring const & path, int linesize, tstring const& pattern)
{
	std::basic_ofstream<tchar> of(path);

	if (!of) {
		return;
	}

	srand((unsigned int)time(NULL));

	for (int i = 0; i<20; i++) {
		tstringstream ss;
		tchar before = ' ', c;
		for (int j = 0; j < 40; j++) {
			do {
				// 文字が1つ前とかぶらないように
				// 最後の文字が空白にならないように
				c = pattern[rand() % ((int)pattern.size())];
			} while (before == c || (c==' '&&j==39));
			before = c;
			ss << c;
		}
		ss << std::endl;
		of << ss.str();
	}
	of.close();
}

lycee::machine_learning::delimiter::~delimiter()
{
}

lycee::machine_learning::word_delimiter::~word_delimiter()
{
}

std::deque<tstring> lycee::machine_learning::word_delimiter::split(tstring const & document)
{
	std::deque<tstring> result;
	tstring rest = document;
	tstring::size_type pos;
	while ( (pos=rest.find_first_of(' ')) == tstring::npos) {
		result.push_back(rest.substr(0, pos));
		rest = rest.substr(pos+1);
	}
	if (rest.size() > 0) {
		result.push_back(rest);
	}
	return result;
}

lycee::machine_learning::char_delimiter::~char_delimiter()
{
}

std::deque<tstring> lycee::machine_learning::char_delimiter::split(tstring const & document)
{
	std::deque<tstring> result;

	for (auto iter = document.cbegin(); iter != document.cend(); iter++) {
		result.push_back(tstring(1, *iter));
	}
	return result;
}

lycee::machine_learning::tf_idf::~tf_idf()
{
	delete this->pDelimiter;
}

lycee::machine_learning::tf_idf::tf_idf(delimiter * _delimiter)
	: pDelimiter(_delimiter)
{
	;
}

void lycee::machine_learning::tf_idf::setDocument(tstring const & filepath)
{
	std::basic_ifstream<tchar> fi(filepath);
	if (!fi) {
		return;
	}

	// 文書情報はここで破棄させる
	this->rawData.clear();
	this->corpus.clear();
	
	// 1行づつ読み込んで，指定された分解ファンクタで分解した後，文書情報に保存
	tstring line;
	while (std::getline(fi, line)) {
		if (line.empty()) {
			continue;
		}
		this->rawData.push_back(line);
		this->corpus.push_back(this->pDelimiter->split(line));
	}
	return;
}




std::deque<int> lycee::machine_learning::tf_idf::getTF(tstring const & word)
{
	std::deque<int> result;

	// 文書ごとに数え上げ
	for (auto doc = corpus.begin(); doc != corpus.end(); doc++) {
		//int cnt=0;

		// 文書内にある単語に合致しているものだけ数える
		// std::accumulate(doc->begin(), doc->end(), 0, (t)[]{return word==t;})が使える？
		
		auto cnt = std::count(doc->begin(), doc->end(), word);
		result.push_back(cnt);
	}
	return result;
}

double lycee::machine_learning::tf_idf::getIDF(tstring const & word)
{
	int docSize = this->corpus.size();

	int cnt = 0;
	for (auto doc = this->corpus.begin() ; doc != this->corpus.end() ; doc++) {
		auto pos = std::find(doc->begin(), doc->end(), word);
		if (pos != doc->end()) {
			cnt++;
		}
	}
	return log((double)docSize / cnt);
}

std::deque<double> lycee::machine_learning::tf_idf::getTFIDF(tstring const & word)
{
	return std::deque<double>();
}

