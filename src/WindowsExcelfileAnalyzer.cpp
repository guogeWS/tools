#include "WindowsExcelfileAnalyzer.h"

WindowsExcelFileAnalyzer::WindowsExcelFileAnalyzer()
{

}
QString WindowsExcelFileAnalyzer::outPutToTxtFile(QString fileName){
    QString outPutString="";
    outPutString+=u8"研发部工作总结；"+_currentYear+"."+_currentMounth+"."+_currentData+"\n";
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
    return outPutString;

}
void WindowsExcelFileAnalyzer::writeExcelFile(QString fileName){
    infoList.clear();
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible",false);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    QAxObject *workbook=workbooks->querySubObject("Open(Qstring,Qvariant)",fileName);
    QAxObject *worksheet=workbook->querySubObject("WorkSheets(int)",1);
    //QAxObject *cell_1_1 = worksheet->querySubObject("Cells(int,int)", 1, 2);// 行  列
    int currentIndex=-1;
    QString tomoryWorkInfo;
    for(int i=1;i<35;i++){
        QAxObject *cell =worksheet->querySubObject("Cells(int,int)", dataLineCount, i);
        QString value=cell->property("Value").toString();
        if(value.contains((_currentData.length()>1?u8"-":u8"-0")+_currentData)){
            currentIndex=i;
            break;
        }
    }
    qDebug()<<"currentIndex"<<currentIndex;
    QAxObject *lastcell;
    if(currentIndex>0){
        for(int i=0;i<nameNum;i++){
            QString name=worksheet->querySubObject("Cells(int,int)", i+workSumaryFirstIndex, nameLineCount)->property("Value").toString();
            qDebug()<<"name name"<<name;
            QAxObject *cell=worksheet->querySubObject("Cells(int,int)", i+workSumaryFirstIndex, currentIndex);
            cell->setProperty("Value",infoMap[name].summaryOfTodayWork_simple);
            QAxObject *tomcell=worksheet->querySubObject("Cells(int,int)", i+tomorrowWorkFirstIndex, currentIndex);
            tomcell->setProperty("Value",infoMap[name].tomorrowWorkPlan);
            infoList.append(infoMap[name]);
        }
    }
    workbook->dynamicCall("Save");
    workbook->dynamicCall("Close");
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
void WindowsExcelFileAnalyzer::getUsefulFile(QString path){
    QDir fileDir(path);
    fileDir.setFilter(QDir::Files);
    QFileInfoList fileInfoList=fileDir.entryInfoList();
    for(int i=0;i<fileInfoList.length();i++){
        QString fileName=fileInfoList.at(i).fileName();
        if(fileName.contains(u8"周工作计划")){
            continue;
        }
        if(fileName.contains(_currentYear)){
            fileName.remove(_currentYear);
            if(fileName.contains(_currentMounth)){
                int startIndex= fileName.indexOf(_currentMounth);
                fileName= fileName.mid(startIndex+_currentMounth.length());
                if(fileName.contains(_currentData)){
                    qDebug()<<"fileName :"<<fileInfoList.at(i).fileName();
                    readExcelFile(path+fileInfoList.at(i).fileName());
                }
            }
        }
    }
    writeExcelFile(_targetFile);
    //outPutToTxtFile("");
}
QString WindowsExcelFileAnalyzer::slipText(QString text){
    return text.remove("file:///");
}
