/*!
 *@file DBPass.qml
 *@brief 密码
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow{
    id: frmWindow
    height: dbPass.height+btnOK.height+defaultMargin*2+40
    width: 300
    modality: Qt.ApplicationModal
    flags: Qt.Window | Qt.FramelessWindowHint

    property int defaultMargin: 6
    signal sinputText(string inputText);

    function showWindow(){
        frmWindow.showNormal();
        dbPass.tName.forceActiveFocus();
    }

    Rectangle{
        anchors.fill: parent
        border.color: "#148014"
        border.width: 1
        color: "transparent"
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

    Text{
        anchors.left: parent.left
        anchors.leftMargin: 48
        height: 40
        text: qsTr("请输入密码")
        font.family: "Microsoft YaHei"
        font.pixelSize: 15
        verticalAlignment: Text.AlignVCenter
        color: "#148014"
    }

    BaseButton{
        id: btnClose
        height: 24
        width: 24
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: defaultMargin
        imgEntered: "qrc:/images/close(3).png"
        imgExited: "qrc:/images/close.png"
        imgPressed: "qrc:/images/close(1).png"
        onSClicked: {
            close();
        }
    }

    Column{
        anchors.top: parent.top
        anchors.topMargin: 40
        width: parent.width - defaultMargin*2
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: defaultMargin

        BaseTextField{
            id: dbPass
            focus: true
            showText: qsTr("密码:")
            showWidth: 80
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: false
            echoMode: TextInput.Password
        }

        BaseButton{
            id: btnOK
            height: 30
            width: 120
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("确定")
            onSClicked: {
                frmWindow.hide();
                sinputText(dbPass.inputText);
            }
        }
    }
}
