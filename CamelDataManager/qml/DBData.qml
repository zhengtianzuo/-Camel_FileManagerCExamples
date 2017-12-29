/*!
 *@file DBData.qml
 *@brief 浏览
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle{
    property int defaultMargin: 6

    id: frmWindow

    Row{
        id: rowData
        height: parent.height - control.height
        width: parent.width
        spacing: defaultMargin

        BaseTableView{
            id: tableView
            height: parent.height
            width: parent.width/2
        }

        Column{
            id: colDetail
            height: tableView.height
            width: parent.width/2
            spacing: defaultMargin

            SwipeView {
                id: view
                height: parent.width
                width: parent.width
                currentIndex: 0
                interactive: false

                TextEdit{

                }

                AnimatedImage{

                }

                Rectangle{

                }

                Rectangle{

                }
            }

            BaseButton{
                id: btnModify
                height: 24
                width: 120
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("应用修改")
                onSClicked: {

                }
            }
        }
    }

    Rectangle{
        id: control
        anchors.top: rowData.bottom
        anchors.topMargin: defaultMargin
        height: 48
        width: parent.width
        border.color: "#148014"
        border.width: 1

        BasePageNavigation{
            id: pageNavigation
            anchors.left: parent.left
            anchors.leftMargin: defaultMargin
            anchors.verticalCenter: parent.verticalCenter
            nCout: 23
            nCurPage: 1
            nPageSize: 5
            onSCurPage: {

            }
        }

        Row{
            anchors.right: parent.right
            anchors.rightMargin: defaultMargin
            height: parent.height
            width: parent.width - pageNavigation.width
            layoutDirection: Qt.RightToLeft
            spacing: defaultMargin

            BaseButton{
                id: btnDel
                height: 24
                width: 60
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("删除")
                onSClicked: {

                }
            }

            BaseButton{
                id: btnAdd
                height: 24
                width: 60
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("添加")
                onSClicked: {

                }
            }
        }
    }
}
