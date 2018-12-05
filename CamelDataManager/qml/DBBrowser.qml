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

    Component{
        id: listDelegate
        Rectangle{
            property int fromIndex: 0
            property int toIndex: 0
            color: "transparent"

            id: listItem
            width: listviewback.width
            height: 30

            Text {
                id: label
                font.family: "microsoft yahei"
                font.pointSize: 12
                anchors.fill: parent
                text: model.name
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
                    if (listItem.fromIndex !== listItem.toIndex){
                        listData.move(listItem.fromIndex, listItem.toIndex);
                    }
                    //console.debug("fromIndex: ", listItem.fromIndex, "toIndex: ", listItem.toIndex);
                }
                onMouseYChanged: {
                    var lastIndex = listview.indexAt(mousearea.mouseX + listItem.x,
                                                     mousearea.mouseY + listItem.y);
                    if ((lastIndex < 0) || (lastIndex > listData.rowCount()))
                        return;
                    listItem.toIndex = lastIndex;
                }
            }
        }
    }

    Rectangle{
        z:1
        id: listviewback
        width: parent.width/3
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: defaultMargin
        anchors.left: parent.left
        anchors.leftMargin: defaultMargin
        color: "transparent"
        border.color: "#148014"
        border.width: 1

        ListView{
            id: listview
            height: parent.height - 2
            width: parent.width - 2
            anchors.centerIn: parent
            model: listData
            delegate: listDelegate
            interactive: false
        }
    }

    DBInfo{
        id: dbInfo
        height: parent.height*0.55
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        anchors.left: listviewback.right
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
        anchors.left: listviewback.right
        anchors.leftMargin: defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: defaultMargin
    }
}
