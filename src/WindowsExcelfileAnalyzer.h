#ifndef WINDOWSEXCELFILEANALYZER_H
#define WINDOWSEXCELFILEANALYZER_H

#include <QObject>
#include <QAxObject>
class WindowsExcelFileAnalyzer
{
public:
    WindowsExcelFileAnalyzer();
    void readExcelFile(QString fileName);
};

#endif // WINDOWSEXCELFILEANALYZER_H
