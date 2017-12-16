/*!
 *@file BaseTextField.qml
 *@brief 自定义TextField
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle{
    property int defaultMargin: 6
    property alias showText: lname.text
    property alias showWidth: lname.width
    property alias inputText: tName.text
    property alias inputWidth: rname.width

    width: lname.width+defaultMargin+rname.width+defaultMargin*2
    border.color: "#148014"
    border.width: 1

    Text{
        id: lname
        text: qsTr("")
        height: 30
        width: contentWidth
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        anchors.left: parent.left
        anchors.leftMargin: defaultMargin
        verticalAlignment: Text.AlignVCenter
        font.family: "Microsoft YaHei"
        font.pixelSize: 15
    }

    Rectangle{
        id: rname
        height: 30
        width: 30
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        anchors.left: lname.right
        anchors.leftMargin: defaultMargin/2
        TextField{
            id: tName
            anchors.left: parent.left
            anchors.leftMargin: defaultMargin
            anchors.right: parent.right
            anchors.rightMargin: defaultMargin
            height: parent.height
            text: qsTr("")
            font.family: "Microsoft YaHei"
            font.pixelSize: 15
            selectByMouse: true
            cursorVisible: false
            readOnly: true
            verticalAlignment: Text.AlignVCenter
            cursorPosition: 0
        }
    }
}
