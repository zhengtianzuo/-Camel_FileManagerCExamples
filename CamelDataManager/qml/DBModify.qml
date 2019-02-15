/*!
 *@file DBModify.qml
 *@brief 修改
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle{
    property int defaultMargin: 6

    function onSOpenDataBase(strName, strPath){
        dbName.inputText = strName;
    }

    BaseMessageDialog{
        id: message
    }

    id: frmWindow
    border.color: "#148014"
    border.width: 1

    Column{
        anchors.fill: parent
        spacing: defaultMargin

        BaseTextField{
            id: dbName
            width: parent.width
            showText: qsTr("名称:")
            showWidth: 80
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3 - btnModifyName.width

            BaseButton{
                id: btnModifyName
                height: 30
                width: 120
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: defaultMargin
                text: qsTr("修改名称")
                onSClicked: {
                    if (dbName.inputText.length === 0){
                        message.showMsg(qsTr("请输入数据库的名称"));
                        return;
                    }
                    var intError = cDataManager.cls_funManagerDB_SetName(dbName.inputText);
                    if (intError !== 1){
                        message.showMsg(qsTr("修改数据库名称错误, 错误码: ") + intError);
                        return;
                    }
                }
            }
        }

        BaseTextField{
            id: dbPass
            showText: qsTr("新密码:")
            showWidth: 80
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: false
            echoMode: TextInput.Password
        }

        BaseTextField{
            id: dbrePass
            width: parent.width
            showText: qsTr("确认密码:")
            showWidth: 80
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3 - btnModifyPass.width
            readOnly: false
            echoMode: TextInput.Password

            BaseButton{
                id: btnModifyPass
                height: 30
                width: 120
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: defaultMargin
                text: qsTr("修改密码")
                onSClicked: {
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
                    var intError = cDataManager.cls_funManagerDB_ChangePassword(dbrePass.inputText);
                    if (intError !== 1){
                        message.showMsg(qsTr("修改数据库密码错误, 错误码: ") + intError);
                        return;
                    }
                    message.showMsg(qsTr("已成功修改数据库密码"));
                }
            }
        }
    }
}
