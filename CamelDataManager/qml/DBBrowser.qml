/*!
 *@file DBBrowser.qml
 *@brief 数据库
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

Page{

    property int defaultMargin: 6

    id: dbs

    ListModel {
        id: listModel

        ListElement {
            text: qsTr("111222333随便的一些内容")
        }
        ListElement {
            text: qsTr("AAABBBCCC随便的一些内容")
        }
        ListElement {
            text: qsTr("DDDEEEFFF随便的一些内容")
        }
        ListElement {
            text: qsTr("GGGHHHIII随便的一些内容")
        }
        ListElement {
            text: qsTr("JJJKKKLLL随便的一些内容")
        }
        ListElement {
            text: qsTr("111222333随便的一些内容")
        }
        ListElement {
            text: qsTr("AAABBBCCC随便的一些内容")
        }
        ListElement {
            text: qsTr("DDDEEEFFF随便的一些内容")
        }
        ListElement {
            text: qsTr("GGGHHHIII随便的一些内容")
        }
        ListElement {
            text: qsTr("JJJKKKLLL随便的一些内容")
        }
        ListElement {
            text: qsTr("111222333随便的一些内容")
        }
        ListElement {
            text: qsTr("AAABBBCCC随便的一些内容")
        }
        ListElement {
            text: qsTr("DDDEEEFFF随便的一些内容")
        }
        ListElement {
            text: qsTr("GGGHHHIII随便的一些内容")
        }
        ListElement {
            text: qsTr("JJJKKKLLL随便的一些内容")
        }
        ListElement {
            text: qsTr("111222333随便的一些内容")
        }
        ListElement {
            text: qsTr("AAABBBCCC随便的一些内容")
        }
        ListElement {
            text: qsTr("DDDEEEFFF随便的一些内容")
        }
        ListElement {
            text: qsTr("GGGHHHIII随便的一些内容")
        }
        ListElement {
            text: qsTr("JJJKKKLLL随便的一些内容")
        }
    }

    Component{
        id: listDelegate
        Rectangle{
            property int fromIndex: 0
            property int toIndex: 0
            color: "transparent"

            id: listItem
            width: listview.width
            height: 30

            Text {
                id: label
                font.family: "microsoft yahei"
                font.pointSize: 12
                anchors.fill: parent
                text: model.text
                color: "#148014"
                verticalAlignment: Text.AlignVCenter
            }
            Rectangle{
                color: "#AAAAAA"
                height: 1
                width: parent.width
                anchors.bottom: parent.bottom
            }
            MouseArea {
                id: mousearea
                anchors.fill: parent
                onPressed: {
                    listview.currentIndex = index;
                    listItem.fromIndex = index;
                    label.color = "#4040FF"
                }
                onReleased: {
                    label.color = "#148014"
                    console.debug("fromIndex: ", listItem.fromIndex, "toIndex: ", listItem.toIndex);
                }
                onMouseYChanged: {
                    var lastIndex = listview.indexAt(mousearea.mouseX + listItem.x,
                                                     mousearea.mouseY + listItem.y);
                    if ((lastIndex < 0) || (lastIndex > listModel.rowCount()))
                        return;
                    if (index !== lastIndex){
                        listModel.move(index, lastIndex, 1);
                    }
                    listItem.toIndex = lastIndex;
                }
            }
        }
    }

    ListView{
        z:1
        id: listview
        width: parent.width/3
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: defaultMargin
        anchors.left: parent.left
        anchors.leftMargin: defaultMargin
        model: listModel
        delegate: listDelegate
        interactive: false
    }

    DBInfo{
        id: dbInfo
        height: parent.height*0.55
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        anchors.left: listview.right
        anchors.leftMargin: defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: defaultMargin
    }

    DBControl{
        id: dbControl
        anchors.top: dbInfo.bottom
        anchors.topMargin: defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: defaultMargin
        anchors.left: listview.right
        anchors.leftMargin: defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: defaultMargin
    }
}
