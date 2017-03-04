// ---------------------------------------------
//
// tf_idf
// �t�@�C����1�s���Ƃ𕶏��ƒ�`���C�C�ӂ̒P�ʂɕ����������̂�����
// TF-IDF�l���Z�o����N���X
//
#ifndef __LYCEE__MACHINE_LEARNING__HEADER__
#define __LYCEE__MACHINE_LEARNING__HEADER__

#include "main.h"

namespace lycee {

namespace machine_learning {

	void generateRandomCorpus(tstring const& path, int linesize, tstring const& pattern);
	


	// -----------------------------------------------------------
	// �����������W�b�N
	//

	// ���������t�@���N�^�i���N���X�j
	struct delimiter {
		virtual ~delimiter()=0;
		virtual std::deque<tstring> split(tstring const& document)=0;
	};

	// ���p�X�y�[�X����؂蕶���ɕ�������t�@���N�^
	struct word_delimiter : virtual public delimiter {
		virtual ~word_delimiter();
		virtual std::deque<tstring> split(tstring const& document);
	};

	// 1�������Ƃɕ�������t�@���N�^
	struct char_delimiter : virtual public delimiter {
		virtual ~char_delimiter();
		virtual std::deque<tstring> split(tstring const& document);
	};


	// ---------------------------------------------
	//
	//
	class tf_idf {
	public:
		// �^��`
		typedef std::deque<tstring> TermList;
		typedef std::deque<TermList> Corpus;

		// �f�X�g���N�^
		virtual ~tf_idf();
		
		// �R���X�g���N�^
		explicit tf_idf(delimiter *_delimiter);
		
		
		// ������ݒ�
		void setDocument(tstring const& filepath);

		std::deque<tstring> getRawData() const {
			return this->rawData;
		}

		Corpus getCorpus() const {
			return this->corpus;
		}

		
		// TF�l�̎Z�o
		std::deque<int> getTF(tstring const& word);
		
		// IDF�l�̎Z�o
		double getIDF(tstring const& word);
		
		// TF-IDF�l�̎Z�o
		std::deque<double> getTFIDF(tstring const& word);
		
	private:
		// ������
		delimiter *pDelimiter;
		
		// �����f�[�^�iRawData�j
		std::deque<tstring> rawData;

		// �������
		std::deque< TermList > corpus;

	};


}	// machine_learning

}	// lycee
#endif	// __LYCEE__MACHINE_LEARNING__HEADER__