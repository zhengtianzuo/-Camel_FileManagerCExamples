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
        anchors.fill: parent

        BaseTabBar{
            id: bar
            height: 48
            width: 64*myModel.count
            Component.onCompleted: {
                myModel.append({ "modelText": qsTr("新建"), "modelColor": "#148014", "modelColorG": "#4040ff", "modelSrc": "1qrc:/images/DBN.svg", "modelSrcG": "1qrc:/images/DBNG.svg"})
                myModel.append({ "modelText": qsTr("打开"), "modelColor": "#148014", "modelColorG": "#4040ff", "modelSrc": "1qrc:/images/DB.svg", "modelSrcG": "1qrc:/images/DBG.svg"})
                myModel.append({ "modelText": qsTr("修改"), "modelColor": "#148014", "modelColorG": "#4040ff", "modelSrc": "1qrc:/images/DBM.svg", "modelSrcG": "1qrc:/images/DBMG.svg"})
                myModel.append({ "modelText": qsTr("压缩"), "modelColor": "#148014", "modelColorG": "#4040ff", "modelSrc": "1qrc:/images/DBC.svg", "modelSrcG": "1qrc:/images/DBCG.svg"})
                myModel.append({ "modelText": qsTr("删除"), "modelColor": "#148014", "modelColorG": "#4040ff", "modelSrc": "1qrc:/images/DBD.svg", "modelSrcG": "1qrc:/images/DBDG.svg"})
            }
        }

        SwipeView {
            id: view
            height: frmWindow.height - bar.height
            width: parent.width
            currentIndex: bar.currentIndex
            interactive: false
            onCurrentIndexChanged: {
                bar.currentIndex = currentIndex;
            }

            DBNew{
                visible: SwipeView.isCurrentItem
            }

            DBOpen{
                visible: SwipeView.isCurrentItem
            }

            DBModify{
                visible: SwipeView.isCurrentItem
            }

            DBCompress{
                visible: SwipeView.isCurrentItem
            }

            DBDelete{
                visible: SwipeView.isCurrentItem
            }
        }
    }
}
