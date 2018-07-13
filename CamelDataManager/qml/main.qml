/*!
 *@file main.qml
 *@brief 主文件
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow {
    property int defaultMargin: 6

    id: frmWindow
    visible: true
    width: 1024
    height: 768
    title: qsTr("")
    flags: Qt.Window | Qt.FramelessWindowHint
    font.family: "Microsoft YaHei"
    font.pixelSize: 15

    Image {
        id: imgBack
        anchors.fill: parent
        source: "qrc:/images/SilkStyle_Back.png"
    }

    Image{
        height: 24
        width: 24
        anchors.left: parent.left
        anchors.leftMargin: defaultMargin
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        source: "qrc:/dromedary.ico"
    }

    MouseArea{
        anchors.fill: parent
        property point clickPos: "0,0"
        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            frmWindow.setX(frmWindow.x+delta.x)
            frmWindow.setY(frmWindow.y+delta.y)
        }
    }

    Column{
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        height: parent.height - defaultMargin*2
        width: parent.width

        Row{
            id: rowBtn
            height: 32
            spacing: defaultMargin/2
            anchors.right: parent.right
            anchors.rightMargin: defaultMargin
            BaseButton{
                id: btnMin
                anchors.top: parent.top
                anchors.topMargin: defaultMargin
                height: 24
                width: 24
                imgEntered: "qrc:/images/min(3).png"
                imgExited: "qrc:/images/min.png"
                imgPressed: "qrc:/images/min(1).png"
                onSClicked: {
                    showMinimized();
                }
            }
            BaseButton{
                id: btnClose
                anchors.top: parent.top
                anchors.topMargin: defaultMargin
                height: 24
                width: 24
                imgEntered: "qrc:/images/close(3).png"
                imgExited: "qrc:/images/close.png"
                imgPressed: "qrc:/images/close(1).png"
                onSClicked: {
                    Qt.quit();
                }
            }
        }

        BaseTabBar{
            id: bar
            height: 48
            width: 64*myModel.count
            Component.onCompleted: {
                myModel.append({ "modelText": qsTr("数据库"), "modelColor": "#148014", "modelColorG": "#4040ff", "modelSrc": "qrc:/images/DB.svg", "modelSrcG": "qrc:/images/DBG.svg"})
                myModel.append({ "modelText": qsTr("浏览"), "modelColor": "#148014", "modelColorG": "#4040ff", "modelSrc": "qrc:/images/List.svg", "modelSrcG": "qrc:/images/ListG.svg"})
                myModel.append({ "modelText": qsTr("查询"), "modelColor": "#148014", "modelColorG": "#4040ff", "modelSrc": "qrc:/images/Search.svg", "modelSrcG": "qrc:/images/SearchG.svg"})
                myModel.append({ "modelText": qsTr("关于"), "modelColor": "#148014", "modelColorG": "#4040ff", "modelSrc": "qrc:/images/About.svg", "modelSrcG": "qrc:/images/AboutG.svg"})
                //bar.currentIndex = 1;
            }
        }

        SwipeView {
            id: view
            height: frmWindow.height - bar.height - rowBtn.height - defaultMargin*2
            width: parent.width
            currentIndex: bar.currentIndex
            interactive: false
            onCurrentIndexChanged: {
                bar.currentIndex = currentIndex;
            }

            DBBrowser{

            }

            DBData{

            }

            DBSearch{

            }

            DBAbout{

            }
        }
    }
}
