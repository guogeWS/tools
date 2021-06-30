#include "AutoStartSetting.h"

AutoStartSetting::AutoStartSetting()
{
    cmdProcess=new QProcess();
}
void AutoStartSetting::creatLink(){
    //QFile::link(_filePath,"C:\Users\WIN 10\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup\test.lnk");
}
