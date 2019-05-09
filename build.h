#ifndef BUILD_H
#define BUILD_H
#include <QDebug>
#include <vector>
#include <string.h>
using namespace std;
/*不适用设计模式*/
class ExportHeaderModel {
public:
	ExportHeaderModel(string strDepId, string strExportDate) : m_strDepId(strDepId), m_strExportDate(strExportDate) {
    }
	string getDepId() {
		return m_strDepId;
	}
	string getExportDate() {
		return m_strExportDate;
	}
private:
	string m_strDepId;//对账单的部门id
	string m_strExportDate;//对账单的导出日期
};

#endif // BUILD_H
