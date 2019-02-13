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
    property alias tNameCursorPos: tName.cursorPosition
    property alias readOnly: tName.readOnly
    property alias tName:tName

    height: 30+defaultMargin*2
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
        font.pixelSize: 12
    }

    Rectangle{
        id: rname
        height: parent.height - defaultMargin*2
        width: parent.width - defaultMargin
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        anchors.left: lname.right
        anchors.leftMargin: defaultMargin*2
        anchors.right: parent.right
        anchors.rightMargin: defaultMargin*2
        border.color: "#148014"
        border.width: 1

        TextEdit{
            id: tName
            text: qsTr("")
            anchors.left: parent.left
            anchors.leftMargin: defaultMargin
            anchors.right: parent.right
            anchors.rightMargin: defaultMargin
            height: parent.height
            font.family: "Microsoft YaHei"
            font.pixelSize: 12
            selectByMouse: true
            cursorVisible: false
            cursorPosition: 0
            selectByKeyboard: true
            wrapMode: TextEdit.Wrap
        }
    }
}
