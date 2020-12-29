#include "WindowsExcelfileAnalyzer.h"

WindowsExcelFileAnalyzer::WindowsExcelFileAnalyzer()
{

}
void WindowsExcelFileAnalyzer::outPutToTxtFile(QString fileName){
//    QFile file(fileName);
//    if(file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text)){
//        file.write(u8"\n");
//        file.write(u8"研发部工作总结；2020.12.29\n");
//        for(int i=0;i<infoList.length();i++){
//            QString message=infoList[i].name+":"+infoList[i].summaryOfTodayWork+"\n";
//            file.write(message.toLatin1());
//        }
//        file.write(u8"研发部工作安排；\n");
//        for(int i=0;i<infoList.length();i++){
//            QString message=infoList[i].name+":"+infoList[i].tomorrowWorkPlan+"\n";
//            file.write(message.toLatin1());
//        }
//    }
//    file.close();
    QString outPutString="";
    outPutString+=u8"研发部工作总结；2020.12."+_currentData+"\n";
    for(int i=0;i<infoList.length();i++){
        QString message=infoList[i].name+":"+infoList[i].summaryOfTodayWork+"\n";
        outPutString+=message;
    }
    outPutString+=u8"研发部工作安排；\n";
    for(int i=0;i<infoList.length();i++){
        QString message=infoList[i].name+":"+infoList[i].tomorrowWorkPlan+"\n";
        outPutString+=message;
    }
    qDebug().noquote()<<outPutString;
}
void WindowsExcelFileAnalyzer::writeExcelFile(QString fileName){
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    QAxObject *workbook=workbooks->querySubObject("Open(Qstring,Qvariant)",fileName);
    QAxObject *worksheet=workbook->querySubObject("WorkSheets(int)",1);
    //QAxObject *cell_1_1 = worksheet->querySubObject("Cells(int,int)", 1, 2);// 行  列
    int currentIndex;
    QString tomoryWorkInfo;
    for(int i=1;i<35;i++){
        QAxObject *cell =worksheet->querySubObject("Cells(int,int)", 9, i);
        QString value=cell->property("Value").toString();
        if(value.contains(u8"-"+_currentData)){
            currentIndex=i;
            break;
        }
    }
    for(int i=14;i<20;i++){
        QString name=worksheet->querySubObject("Cells(int,int)", i, 2)->property("Value").toString();
        qDebug()<<"name name"<<name;
        QAxObject *cell=worksheet->querySubObject("Cells(int,int)", i, currentIndex);
        cell->setProperty("Value",infoMap[name].summaryOfTodayWork_simple);
        tomoryWorkInfo+=infoMap[name].tomorrowWorkPlan+"\n";
        infoList.append(infoMap[name]);
    }
    QAxObject *lastcell=worksheet->querySubObject("Cells(int,int)", 20, currentIndex);
    lastcell->setProperty("Value",tomoryWorkInfo);
    workbook->dynamicCall("Close");
    workbook->dynamicCall("SaveAs (const QString&,int,const QString&,const QString&,bool,bool)",
                                  fileName,56,QString(""),QString(""),false,false);

    excel.dynamicCall("Quit()");

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
            if(message!=""){
                workinfo.summaryOfTodayWork+=message+"("+allEnvDataList_i[2].toString()+")"+u8"。";
                workinfo.summaryOfTodayWork_simple+=message+u8"。";
            }

        }
        if(i==tomotyInfoIndex){
            workinfo.tomorrowWorkPlan=allEnvDataList_i[0].toString();
        }
    }
    workinfo.tomorrowWorkPlan.remove(u8"1、");
    if(!workinfo.tomorrowWorkPlan.contains(u8"。")){
        workinfo.tomorrowWorkPlan+=u8"。";
    }
    infoMap[workinfo.name]=workinfo;
    qDebug()<<"info info"<<workinfo.name<<":"<<workinfo.summaryOfTodayWork<<":"<<workinfo.tomorrowWorkPlan;
    workbook->dynamicCall("Close");
    excel.dynamicCall("Quit()");

}
