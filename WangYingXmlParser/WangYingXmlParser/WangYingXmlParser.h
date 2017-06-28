// ����ģ��
#pragma once
#include <string>
#include <vector>

// �Զ������ݽṹ
namespace WangYingXmlParser{
	// ����
	struct CAttribute {
		std::string name;
		std::string value;
	};

	// ��Ŀ
	struct CItem {
		std::string name;
		std::vector<CAttribute> attributes;
	};

	// �ĵ�
	struct CDocument {
		std::vector<CItem> items;
	};
}

class CWangYingXmlParser {
public:
	CWangYingXmlParser();
	virtual ~CWangYingXmlParser();

public:// ������أ��д����Ƹ������͵�����
	bool ParseXml(std::string strXml);

protected:
	// ��飺�����ı��Ƿ�Ϸ�
	bool _IsXmlValid(std::string strXml, std::string *pstrErrorMsg);

	// ������������Ŀ
	bool _ParseItem(std::string strXml);

private:
	WangYingXmlParser::CDocument m_cDocument;	// ���棺���������ݽṹ
};
