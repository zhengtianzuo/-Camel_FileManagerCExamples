/*!
 *@file DBNew.qml
 *@brief 新建
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0
import Qt.labs.platform 1.0

Rectangle{
    property int defaultMargin: 6

    id: frmWindow

    FolderDialog {
        id: folderDialog
        onAccepted: {
            var path = folderDialog.currentFolder.toString();
            path = path.replace(/^(file:\/{3})/,"");
            ldbPath.inputText = path;
            ldbPath.tNameCursorPos = 0
        }
    }

    Column{
        anchors.fill: parent

        BaseTextField{
            id: dbName
            showText: qsTr("名称:")
            showWidth: 80
            inputText: qsTr("数据库的名称")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: false
        }

        BaseTextField{
            id: dbPass
            showText: qsTr("密码:")
            showWidth: 80
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: false
        }

        BaseTextField{
            id: dbrePass
            showText: qsTr("确认密码:")
            showWidth: 80
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: false
        }

        Row{
            height: ldbPath.height
            width: parent.width

            BaseTextField{
                id: ldbPath
                showText: qsTr("路径:")
                showWidth: 80
                inputWidth: parent.width-showWidth-defaultMargin*3 - browser.width
                readOnly: false
            }

            BaseButton{
                id: browser
                height: 30
                width: 120
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("浏览")
                onSClicked: {
                    folderDialog.open();
                }
            }
        }

        BaseButton{
            id: btnNew
            height: 30
            width: 120
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("新建")
            onSClicked: {

            }
        }
    }
}
