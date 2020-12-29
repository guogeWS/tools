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
    QAxObject *usedrange=worksheet->querySubObject("UsedRange");
    QAxObject *rows = usedrange->querySubObject("Rows");
    int rows_int=rows->property("Count").toInt();
    QString Range="A1:H"+QString::number(rows_int);
    QAxObject *allEnvData=worksheet->querySubObject("Range(String)",Range);
    QVariant allEnvDataValue=allEnvData->property("Value");
    QVariantList  allEnvDataList=allEnvDataValue.toList();
    DailyWorkInfo workinfo;
    int summaryInfoIndex=0;
    int tomotyInfoIndex=17;
    for(int i=0;i<rows_int;i++){
        QVariantList  allEnvDataList_i= allEnvDataList[i].toList();
        QString testInfo=allEnvDataList_i[0].toString();
        if(testInfo.contains(u8"任务总结")){
            summaryInfoIndex=i+2;
        }
        if(testInfo.contains(u8"明日的活动计划")){
            tomotyInfoIndex=i+1;
        }
    }
    for(int i=0;i<rows_int;i++){
        QVariantList  allEnvDataList_i= allEnvDataList[i].toList();
        if(i==1){
            workinfo.name=allEnvDataList_i[2].toString();
        }
        if(i>=summaryInfoIndex&&i<tomotyInfoIndex-1){
            QString message=allEnvDataList_i[0].toString();
            if(message!="")
                workinfo.summaryOfTodayWork+=message+"("+allEnvDataList_i[2].toString()+")"+u8"。";
        }
        if(i==tomotyInfoIndex){
            workinfo.tomorrowWorkPlan=allEnvDataList_i[0].toString();
        }
    }
    workinfo.tomorrowWorkPlan.remove(u8"1、");
    if(!workinfo.tomorrowWorkPlan.contains(u8"。")){
        workinfo.tomorrowWorkPlan+=u8"。";
    }
    qDebug()<<"info info"<<workinfo.name<<":"<<workinfo.summaryOfTodayWork<<":"<<workinfo.tomorrowWorkPlan;
    workbook->dynamicCall("Close");
    excel.dynamicCall("Quit()");

}
