import QtQuick 2.7

Item {
    property alias blackFont: blackFont
    FontLoader{
        id:blackFont;
        source: "qrc:/fonts/source/fonts/TengXiangMingSongJian-W4-2.ttf"
    }
}
