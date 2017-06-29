// ����ģ��
#pragma once
#include <string>
#include <vector>

// �Զ������ݽṹ
namespace WangYingXmlParser{
	// ����
	struct CAttribute {
		std::string name;		// ��������
		std::string value;		// ����ֵ
	};

	// ��Ŀ
	struct CItem {
		std::string name;				// ��Ŀ����
		std::vector<CItem> subitems;	// ����Ŀ
		std::vector<CAttribute> attributes;
	};

	// �ĵ�
	struct CDocument {
		std::vector<CItem> items;	// ��Ŀ�б�
	};
}

class CWangYingXmlParser {
public:
	CWangYingXmlParser();
	virtual ~CWangYingXmlParser();

public:// ������أ��д����Ƹ������͵�����
	bool ParseXml(std::string strXml);

public:// ��ȡ��أ���ȡ��ǰ xml ��Ŀ��������ֵ
	bool GetXmlDocument(WangYingXmlParser::CDocument *pXmlDocument);

protected:
	// ��飺�����ı��Ƿ�Ϸ�
	bool _IsXmlValid(std::string strXml, std::string *pstrErrorMsg);

	// �����������ı����� xml �ı�������һ��һ����Ŀ
	bool _ParseSource(std::string strXml);

	// ����������һ����Ŀ
	bool _ParseOneItem(std::string strOneItemXml, WangYingXmlParser::CItem *pItem);

	// ����������һ������
	bool _ParseOneAttribute(std::string strOneAttribute, WangYingXmlParser::CAttribute *pAttribute);

private:
	WangYingXmlParser::CDocument m_cDocument;	// ���棺���������ݽṹ
};
