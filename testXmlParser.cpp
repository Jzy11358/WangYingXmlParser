// ����ģ��Ĳ���������
#include "./WangYingXmlParser/WangYingXmlParser/WangYingXmlParser.h"
#include <iostream>
#include <cstdlib>

int main()
{
	CWangYingXmlParser wangYingXmlParser;
	// ����
	std::string strXml = "<name sex=\"male\">wang ying</name><age>12</age><love action=\"coding\"/>";
	std::cout << "�õ��� xml �ı�:" << std::endl << strXml << std::endl << std::endl;
	wangYingXmlParser.ParseXml(strXml);
	// ��ȡ
	WangYingXmlParser::CDocument xmlDocument;
	wangYingXmlParser.GetXmlDocument(&xmlDocument);
	int nItemIndex = 0;
	int nAttriIndex = 0;
	std::cout << "������õ�����Ϣ��" << std::endl;
	for (auto item : xmlDocument.items) {
		std::cout << "item" << nItemIndex++ << "			" << item.name << std::endl;
		nAttriIndex = 0;
		for (auto atrribute : item.attributes) {
			std::cout << "attribute" << nAttriIndex++ << "				" \
				<< atrribute.name << "		" << atrribute.value <<std::endl;
		}
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}
