#include "WindowsExcelfileAnalyzer.h"

WindowsExcelFileAnalyzer::WindowsExcelFileAnalyzer()
{

}
void WindowsExcelFileAnalyzer::readExcelFile(QString fileName){
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    QAxObject *workbook=workbooks->querySubObject("Open(Qstring,Qvariant)",fileName);
    QAxObject *worksheet=workbook->querySubObject("WorkSheets(int)",1);

}
