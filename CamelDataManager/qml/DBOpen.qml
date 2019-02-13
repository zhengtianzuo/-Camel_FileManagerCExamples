/*!
 *@file DBOpen.qml
 *@brief 打开
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
        ldbPath.inputText = strPath;
    }

    id: frmWindow
    border.color: "#148014"
    border.width: 1

    BaseMessageDialog{
        id: message
    }

    DBPass{
        id: dBPass
        onSinputText:{
            var intError = cDataManager.cls_funManagerDB_OpenDataBase("", inputText, ldbPath.inputText);
            if (intError !== 1){
                message.showMsg(qsTr("打开数据库错误, 错误码: ") + intError);
            }else{
                cDataManager.cls_funManagerData_GetAllList();
            }
        }
    }

    FileDialog {
        id: fileDialog
        fileMode: FileDialog.OpenFile
        onAccepted: {
            var path = fileDialog.currentFile.toString();
            path = path.replace(/^(file:\/{3})/,"");
            ldbPath.inputText = path;
            ldbPath.tNameCursorPos = 0
            if (ldbPath.inputText.length === 0){
                message.showMsg(qsTr("请输入数据库的路径"));
                return;
            }
            dBPass.showWindow();
        }
    }

    Column{
        height: parent.height
        width: parent.width

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
                    fileDialog.open();
                }
            }
        }
    }
}
