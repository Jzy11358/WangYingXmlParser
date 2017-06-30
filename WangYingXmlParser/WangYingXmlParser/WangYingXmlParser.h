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

	// ��ȡ����ȡ��ǰ xml ������
	bool GetXmlDocument(WangYingXmlParser::CDocument *pXmlDocument);

	// ��ӡ������ǰ xml �����ݴ�ӡ����׼���
	void PrintXmlData(WangYingXmlParser::CDocument xmlDocument);

protected:
	// ��飺�����ı��Ƿ�Ϸ�
	bool _IsXmlValid(std::string strXml, std::string *pstrErrorMsg);

	// �����������ı����� xml �ı�������һ��һ����Ŀ
	bool _ParseSource(std::string strXml);

	// ����������һ����Ŀ
	bool _ParseOneItem(std::string strOneItemXml, WangYingXmlParser::CItem *pItem);

	// ����������һ����Ŀ������Ŀ���� text ���ԣ�����Ŀ�ı�ǩ��֮�����Ϊ������Ŀ���� text ���ԣ�
	bool _ParseSubItem(std::string strOneItemXml, WangYingXmlParser::CItem *pItem);

	// ����������һ������
	bool _ParseOneAttribute(std::string strOneAttribute, WangYingXmlParser::CAttribute *pAttribute);

	// ��ӡ����ӡһ�� Item
	void _PrintOneItem(WangYingXmlParser::CItem item, int nSubLevel);

private:
	WangYingXmlParser::CDocument m_cDocument;	// ���棺���������ݽṹ
};
