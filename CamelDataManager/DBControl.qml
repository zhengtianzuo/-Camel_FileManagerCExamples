/*!
 *@file DBControl.qml
 *@brief DB操作
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: frmWindow

    Column{
        height: parent.height
        width: parent.width

        TabBar {
            id: bar
            height: 48
            width: 48*myModel.count
            currentIndex: 0

            ListModel {
                id: myModel
                ListElement { modelText: qsTr("新建"); modelSrc: "qrc:/images/DBN.svg"; modelSrcG: "qrc:/images/DBNG.svg";}
                ListElement { modelText: qsTr("打开"); modelSrc: "qrc:/images/DB.svg"; modelSrcG: "qrc:/images/DBG.svg";}
                ListElement { modelText: qsTr("修改"); modelSrc: "qrc:/images/DBM.svg"; modelSrcG: "qrc:/images/DBMG.svg";}
                ListElement { modelText: qsTr("压缩"); modelSrc: "qrc:/images/DBC.svg"; modelSrcG: "qrc:/images/DBCG.svg";}
                ListElement { modelText: qsTr("删除"); modelSrc: "qrc:/images/DBD.svg"; modelSrcG: "qrc:/images/DBDG.svg";}
            }

            Repeater {
                model: myModel

                TabButton {
                    height: bar.height
                    contentItem:Text{
                        font.family: "Microsoft YaHei"
                        font.pixelSize: 15
                        text: modelText
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignBottom
                        color: (model.index === bar.currentIndex) ? "#148014" : "#000000"
                    }
                    background:Image{
                        width: 24
                        height: 24
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: (model.index === bar.currentIndex) ? modelSrcG : modelSrc
                    }
                }
            }
        }

        SwipeView {
            id: view
            height: frmWindow.height - bar.height
            width: parent.width
            currentIndex: bar.currentIndex
            onCurrentIndexChanged: {
                bar.currentIndex = currentIndex;
            }

            Rectangle{
                Text{
                    text: "1"
                }
            }

            Rectangle{
                Text{
                    text: "2"
                }
            }

            Rectangle{
                Text{
                    text: "3"
                }
            }

            Rectangle{
                Text{
                    text: "4"
                }
            }

            Rectangle{
                Text{
                    text: "5"
                }
            }
        }
    }
}
