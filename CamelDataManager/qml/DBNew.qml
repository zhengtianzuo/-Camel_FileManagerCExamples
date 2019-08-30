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

    function onSOpenDataBase(strName, strPath){
        dbName.inputText = strName;
        ldbPath.inputText = strPath;
    }

    id: frmWindow
    border.color: "#148014"
    border.width: 1

    BaseMessageDialog{
        id: message
    }

    FolderDialog {
        id: folderDialog
        onAccepted: {
            var path = folderDialog.currentFolder.toString();
            path = path.replace(/^(file:\/{3})/,"");
            ldbPath.inputText = path + "/";
            ldbPath.tNameCursorPos = 0
        }
    }

    Column{
        anchors.fill: parent
        spacing: defaultMargin

        BaseTextField{
            id: dbName
            showText: qsTr("名称:")
            showWidth: 80
            inputText: qsTr("")
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
            echoMode: TextInput.Password
        }

        BaseTextField{
            id: dbrePass
            showText: qsTr("确认密码:")
            showWidth: 80
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: false
            echoMode: TextInput.Password
        }

        BaseTextField{
            id: ldbPath
            width: parent.width
            showText: qsTr("路径:")
            showWidth: 80
            inputWidth: parent.width-showWidth-defaultMargin*3 - browser.width
            readOnly: false

            BaseButton{
                id: browser
                height: 30
                width: 120
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: defaultMargin
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
                if (dbName.inputText.length === 0){
                    message.showMsg(qsTr("请输入数据库的名称"));
                    return;
                }
                if (dbPass.inputText.length === 0){
                    message.showMsg(qsTr("请输入数据库的密码"));
                    return;
                }
                if (dbrePass.inputText.length === 0){
                    message.showMsg(qsTr("请再次输入数据库的密码"));
                    return;
                }
                if (dbPass.inputText !== dbrePass.inputText){
                    message.showMsg(qsTr("两次输入的密码不相同"));
                    return;
                }
                if (ldbPath.inputText.length === 0){
                    message.showMsg(qsTr("请输入数据库的路径"));
                    return;
                }
                var intError = cDataManagerDB.cls_funManagerDB_CreateDataBase(dbName.inputText, dbPass.inputText, ldbPath.inputText);
                if (intError !== 1){
                    message.showMsg(qsTr("创建数据库错误, 错误码: ") + intError);
                    return;
                }
                intError = cDataManagerDB.cls_funManagerDB_OpenDataBase(dbName.inputText, dbPass.inputText, ldbPath.inputText);
                if (intError !== 1){
                    message.showMsg(qsTr("打开数据库错误, 错误码: ") + intError);
                    return;
                }
                message.showMsg(qsTr("已成功新建数据库"));
            }
        }
    }
}
