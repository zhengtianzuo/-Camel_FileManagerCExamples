/*!
 *@file BaseMessageDialog.qml
 *@brief 消息提醒
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow{
    id: frmWindow
    height: msg.height+btnOK.height+defaultMargin*2+60
    width: 300
    visible: false
    modality: Qt.ApplicationModal
    flags: Qt.Window | Qt.FramelessWindowHint

    function showMsg(strMsg){
        msg.text = strMsg;
        frmWindow.show();
    }

    property int defaultMargin: 6

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
        anchors.leftMargin: 40
        height: 36
        text: qsTr("提示")
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
        spacing: defaultMargin*2

        Text{
            id: msg
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Microsoft YaHei"
            font.pixelSize: 15
        }

        BaseButton{
            id: btnOK
            height: 30
            width: 120
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("确定")
            onSClicked: {
                close();
            }
        }
    }
}
