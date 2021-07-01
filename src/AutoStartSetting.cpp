#include "AutoStartSetting.h"

AutoStartSetting::AutoStartSetting()
{
    cmdProcess=new QProcess();
}
bool AutoStartSetting::creatLink(){
    _fileName=_filePath.mid(_filePath.lastIndexOf('/')+1,_filePath.lastIndexOf('.')-_filePath.lastIndexOf('/')-1);
    if(QFile::link(_filePath,_fileName+".lnk")){
        QString tarPath="C:/Users/WIN 10/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup/"+_fileName+".lnk";
        QFile::copy(_fileName+".lnk",tarPath);
        QFile::remove(_fileName+".lnk");
        return true;
    }
    return false;
}
