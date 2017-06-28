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
	// ��������Ŀ
	_ParseItem(strXml);

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

// ������������Ŀ
bool CWangYingXmlParser::_ParseItem(std::string strXml)
{
	// TODO:�����ı��õ���Ŀ������
	std::string s = strXml;
	std::smatch m;
	std::regex e("[<>/]");
	std::string result;
	while (std::regex_search(s, m, e)) {
		s = m.suffix().str();
		std::string prefix= m.prefix().str();
	}
	return true;
}