#include "WangYingXmlParser.h"
#include <string>
#include <iostream>
#include <stack>
#include <regex>

CWangYingXmlParser::CWangYingXmlParser()
{
	m_cDocument.items.clear();
}

CWangYingXmlParser::~CWangYingXmlParser()
{
	m_cDocument.items.clear();
}

bool CWangYingXmlParser::ParseXml(std::string strXml)
{
	// ��飺�����ı��Ƿ�Ϸ�
	bool bIsXmlValid = false;
	std::string strErrorMsg;
	bIsXmlValid = _IsXmlValid(strXml, &strErrorMsg);
	if (!bIsXmlValid) {
		std::cout << strErrorMsg << std::endl;
		return false;
	}
	// ������xml �ı�
	_ParseSource(strXml);

	return true;
}

// ��飺�����ı��Ƿ�Ϸ�
bool CWangYingXmlParser::_IsXmlValid(std::string strXml, std::string *pstrErrorMsg)
{
	if (nullptr == pstrErrorMsg) return false;
	std::stack<char> stackBracket;	// ջ��������
	std::stack<char> stackBackSlash;// ջ����б��
	bool bBlackSlashValid = true;
	std::string strErrorMsg;
	// ��飺����ƥ��
	for (int i = 0; i < strXml.size(); ++i) {
		// --��¼�������� < ����ֱ��ѹջ
		if ('<' == strXml[i]) stackBracket.push(strXml[i]);
		// --��¼�������� > �����ж�ջ�Ƿ�Ϊ�ա��Ƿ�ջ��Ϊ '<'�������������ջ
		else if ('>' == strXml[i] && stackBracket.size() != 0 && stackBracket.top() == '<')
			stackBracket.pop();
		// --��¼�������� / �����ж�ջ���Ƿ�Ϊ <������Ƿ��� < �����Ҳ��Ƿ��� >��
		// ��������ѹջ��������Ŀ�����������򱨴�
		else if ('/' == strXml[i] && stackBracket.top() == '<' &&
			((i != 0 && '<' == strXml[i - 1]) || (i + 1 != strXml.size() && '>' == strXml[i + 1])))
			stackBackSlash.push(strXml[i]);
		else if ('/' == strXml[i]) {
			bBlackSlashValid = false;
			break;
		}
	}
	// ������б�߲�ƥ��
	if (!bBlackSlashValid)
		strErrorMsg = "parse error: black slash write error.";
	// ���������Ų�ƥ��
	if (stackBracket.size() != 0) {
		bBlackSlashValid = false;
		strErrorMsg = "parse error: bracket does not matched.";
	}
	*pstrErrorMsg = strErrorMsg;
	return bBlackSlashValid;
}

// �����������ı����� xml �ı�������һ��һ����Ŀ
// ƥ�� <name sex="male">wang ying</name> �ı�
// <\w+.*>.*</\1>
// ƥ�� <name sex="male" /> �ı�
// <\w+[^/>]*/>
// ���ﰴ���������ָ�ʽƥ�� xml �ı��е�ÿһ�� Item
// ��������� xml �ı�������һ��һ������Ŀ
bool CWangYingXmlParser::_ParseSource(std::string strXml)
{
	std::string s = strXml;
	std::smatch m;
	std::regex e("<(\\w+).*>.*</\\1>|<\\w+[^/>]*/>");
	while (std::regex_search(s, m, e)) {
		WangYingXmlParser::CItem newItem;
		_ParseOneItem(m.str(), &newItem);
		s = m.suffix().str();
		m_cDocument.items.push_back(newItem);
	}
	return true;
}

// ����������һ����Ŀ
// �õ���Ŀ������Ŀ�б�����
// ƥ���ǩ�� <name
// <\w+\b  
// ƥ������ sex="male"
// \b\w+="\w+"
// ƥ������ >wang ying<
// >.*<
// ƥ���ǩͷ
// <\w+[^\n<]*>
bool CWangYingXmlParser::_ParseOneItem(std::string strOneItemXml, WangYingXmlParser::CItem *pItem)
{
	if (pItem == nullptr) return false;
	WangYingXmlParser::CItem newItem;
	// ��ã���Ŀ����
	std::string s = strOneItemXml;
	std::smatch m;
	std::regex regexItemName("<\\w+\\b");
	if (std::regex_search(s, m, regexItemName)) {
		std::string strItemName = m.str();
		newItem.name = strItemName.erase(0, 1);
		s = m.suffix().str();
	}
	// ��ã�����
	s = strOneItemXml;
	std::smatch tabHeadMatch;
	std::regex regexTabHead("<\\w+[^\\n<]*>");
	if (std::regex_search(s, tabHeadMatch, regexTabHead)) {
		std::string strTabHead = tabHeadMatch.str();
		std::smatch attributeMatch;
		std::regex regexAtrribute("\\b\\w+=\"\\w+\"");
		while (std::regex_search(strTabHead, attributeMatch, regexAtrribute)) {
			WangYingXmlParser::CAttribute newAtrribute;
			_ParseOneAttribute(attributeMatch.str(), &newAtrribute);
			newItem.attributes.push_back(newAtrribute);
			strTabHead = attributeMatch.suffix().str();
		}
	}
	
	// �������ԣ�˫��ǩ�������� text ����ֵ
	// ����Ŀ����Ҳ������ text ����ֵ�У���ʱ��Ҫ���� text �Ƿ�
	// ƥ��ó��µ� Item ��������Ϊ�� Item ���� text ����ֵ
	s = strOneItemXml;
	std::regex regexText(">.*<");
	if (std::regex_search(s, m, regexText)) {
		// --��ȡ���м���ı�
		std::string strTempText = m.str();
		strTempText.erase(strTempText.end() - 1, strTempText.end());
		strTempText.erase(0, 1);
		// --�����������м��ı�����ƥ���������������Ի�������Ŀ
		_ParseSubItem(strTempText, &newItem);
	}
	*pItem = newItem;
	return true;
}

// ����������һ����Ŀ������Ŀ���� text ���ԣ�����Ŀ�ı�ǩ��֮�����Ϊ������Ŀ���� text ���ԣ�
bool CWangYingXmlParser::_ParseSubItem(std::string strOneItemXml, WangYingXmlParser::CItem *pItem)
{
	if (pItem == nullptr) return false;
	std::string s = strOneItemXml;
	std::smatch m;
	std::regex regexItem("<(\\w+).*>.*</\\1>|<\\w+[^/>]*/>");
	// ƥ�䣺ʶ�����Ŀ���ݹ���� _ParseOneItem ƥ������Ŀ
	if (std::regex_search(s, m, regexItem)) {
		WangYingXmlParser::CItem newSubItem;
		_ParseOneItem(m.str(), &newSubItem);
		pItem->subitems.push_back(newSubItem);
		s = m.suffix().str();
		while (std::regex_search(s, m, regexItem)) {
			WangYingXmlParser::CItem newSubItem;
			std::string strss = m.str();
			_ParseOneItem(m.str(), &newSubItem);
			pItem->subitems.push_back(newSubItem);
			s = m.suffix().str();
		}
	} 
	// ƥ�䣺ʶ��� text ����
	else {
		WangYingXmlParser::CAttribute textAtrribute;
		textAtrribute.name = "text";
		textAtrribute.value = s;
		pItem->attributes.push_back(textAtrribute);
	}
	return true;
}

// ����������һ������
// ���ݹ������ı������� sex="male"
// ƥ�� sex=
// \b\w+=
// ƥ�� ��male��
// "\w*"
bool CWangYingXmlParser::_ParseOneAttribute(std::string strOneAttribute, WangYingXmlParser::CAttribute *pAttribute)
{
	if (pAttribute == nullptr) return false;
	WangYingXmlParser::CAttribute newAtrribute;
	// ��ȡ����������
	std::string s = strOneAttribute;
	std::smatch m;
	std::regex regexAtrributeName("\\b\\w+=");
	if (std::regex_search(s, m, regexAtrributeName)) {
		std::string strTempName = m.str();
		strTempName.erase(strTempName.end() - 1, strTempName.end());
		newAtrribute.name = strTempName;
	}
	// ��ȡ������ֵ
	s = strOneAttribute;
	std::regex regexAtrributeValue("\"\\w*\"");
	if (std::regex_search(s, m, regexAtrributeValue)) {
		std::string strTempValue = m.str();
		strTempValue.erase(strTempValue.end() - 1, strTempValue.end());
		strTempValue.erase(0, 1);
		newAtrribute.value = strTempValue;
	}
	*pAttribute = newAtrribute;
	return true;
}

// ��ȡ��أ���ȡ��ǰ xml ��Ŀ��������ֵ
bool CWangYingXmlParser::GetXmlDocument(WangYingXmlParser::CDocument *pXmlDocument)
{
	if (pXmlDocument == nullptr) return false;
	*pXmlDocument = m_cDocument;
	return true;
}

// ��ӡ������ǰ xml �����ݴ�ӡ����׼���
void CWangYingXmlParser::PrintXmlData(WangYingXmlParser::CDocument xmlDocument)
{
	std::cout << "������õ�����Ϣ��" << std::endl;
	for (auto item : xmlDocument.items) {
		_PrintOneItem(item, 0);
	}
}

// ��ӡ����ӡһ�� Item
void CWangYingXmlParser::_PrintOneItem(WangYingXmlParser::CItem item, int subLevel)
{
	std::string strTab;
	for (int i = 0; i < subLevel; ++i) strTab += "\t";
	std::cout << "Level_" << subLevel << std::endl;
	std::cout << strTab << item.name << ":" << std::endl;
	for (auto attribute : item.attributes) {
		std::cout << "\tattributes: " << attribute.name << "��" << attribute.value << std::endl;
	}
	subLevel++;
	for (auto subItem : item.subitems) {
		_PrintOneItem(subItem, subLevel);
	}
}