#include "GlobalTool.h"

GlobalTool::GlobalTool()
{
}
QString GlobalTool::slipText(QString text){
    return text.remove("file:///");
}
float GlobalTool::getScale(){
    return QApplication::primaryScreen()->logicalDotsPerInch()/96.0;
}
