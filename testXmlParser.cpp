// ����ģ��Ĳ���������
#include "./WangYingXmlParser/WangYingXmlParser/WangYingXmlParser.h"
#include <iostream>
#include <cstdlib>

const std::string xml_0 = "<name sex=\"male\">wang ying</name><age>12</age><love action=\"coding\"/>";
const std::string xml_1 = "<person isStudent=\"false\">\
<name>wang ying</name>\
<age>12</age>\
<country isAsia=\"true\">china</country>\
</person>";
const std::string xml_2 = "<person isStudent=\"false\">\
<name>wang ying</name>\
<age>12</age>\
<country isAsia=\"true\">china</country>\
<hobby>\
<coding language=\"c++\"/>\
<sexygirl/>\
</hobby>\
</person>";
const std::string xml_3 = "<person>\
<name>\
<ag/e>\
<country </country>\
</monkey>";

int main()
{
	CWangYingXmlParser wangYingXmlParser;
	// ����
	// --�޸����������������� xml ���
	std::string strXml = xml_2; 
	std::cout << "�õ��� xml �ı�:" << std::endl << strXml << std::endl << std::endl;
	if (wangYingXmlParser.ParseXml(strXml)) {
		// --��ȡ
		WangYingXmlParser::CDocument xmlDocument;
		wangYingXmlParser.GetXmlDocument(&xmlDocument);
		// --��ӡ
		wangYingXmlParser.PrintXmlData(xmlDocument);
	}
	// ����ʧ��
	else {
		std::string strErrorMessage;
		wangYingXmlParser.GetErrorMessage(&strErrorMessage);
		std::cout << "����ʧ�ܣ�" << std::endl;
		std::cout << strErrorMessage << std::endl;
	}
	
	system("pause");
	return 0;
}
