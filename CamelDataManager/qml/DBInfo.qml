/*!
 *@file DBInfo.qml
 *@brief DB信息
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    property int defaultMargin: 6

    id: frmWindow

    Column{
        anchors.fill: parent

        Rectangle{
            height: 30+defaultMargin*2
            width: parent.width

            BaseTextField{
                id: dbName
                showText: qsTr("名称:")
                inputText: qsTr("数据库的名称")
                inputWidth: 200
            }

            BaseTextField{
                id: dbNum
                anchors.left: dbName.right
                anchors.leftMargin: defaultMargin
                showText: qsTr("文件数:")
                inputText: qsTr("99")
                inputWidth: 60
            }

            BaseTextField{
                id: dbSize
                anchors.left: dbNum.right
                anchors.leftMargin: defaultMargin
                showText: qsTr("大小:")
                inputText: qsTr("1.25M")
                inputWidth: 60
            }

            }
//        Rectangle{

//            border.color: "#148014"
//            border.width: 1

//            Text{
//                id: ldbname
//                text: qsTr("名称:")
//                height: 30
//                width: contentWidth
//                anchors.top: parent.top
//                anchors.topMargin: defaultMargin
//                anchors.left: parent.left
//                anchors.leftMargin: defaultMargin
//                verticalAlignment: Text.AlignVCenter
//                font.family: "Microsoft YaHei"
//                font.pixelSize: 15
//            }

//            Rectangle{
//                id: recName
//                height: 30
//                width: 200
//                anchors.top: parent.top
//                anchors.topMargin: defaultMargin
//                anchors.left: ldbname.right
//                anchors.leftMargin: defaultMargin*2
//                TextField{
//                    id: dbName
//                    anchors.left: parent.left
//                    anchors.leftMargin: defaultMargin
//                    height: parent.height
//                    text: qsTr("数据库的名称")
//                    font.family: "Microsoft YaHei"
//                    font.pixelSize: 15
//                    selectByMouse: true
//                    cursorVisible: false
//                    readOnly: true
//                    verticalAlignment: Text.AlignVCenter
//                }
//            }

//            Text{
//                id: ldbnum
//                text: qsTr("文件数:")
//                height: 30
//                width: contentWidth
//                anchors.top: parent.top
//                anchors.topMargin: defaultMargin
//                anchors.left: dbName.right
//                anchors.leftMargin: defaultMargin*2
//                verticalAlignment: Text.AlignVCenter
//                font.family: "Microsoft YaHei"
//                font.pixelSize: 15
//            }

//            Rectangle{
//                id: recNum
//                height: 30
//                width: contentWidth
//                anchors.top: parent.top
//                anchors.topMargin: defaultMargin
//                anchors.left: ldbnum.right
//                anchors.leftMargin: defaultMargin*2
//                TextField{
//                    id: dbNum
//                    anchors.left: parent.left
//                    anchors.leftMargin: defaultMargin
//                    height: parent.height
//                    text: qsTr("99")
//                    font.family: "Microsoft YaHei"
//                    font.pixelSize: 15
//                    selectByMouse: true
//                    cursorVisible: false
//                    readOnly: true
//                    verticalAlignment: Text.AlignVCenter
//                }
//            }

//            Text{
//                id: ldbsize
//                text: qsTr("大小:")
//                height: 30
//                width: contentWidth
//                anchors.top: parent.top
//                anchors.topMargin: defaultMargin
//                anchors.left: recNum.right
//                anchors.leftMargin: defaultMargin
//                verticalAlignment: Text.AlignVCenter
//                font.family: "Microsoft YaHei"
//                font.pixelSize: 15
//            }

//            Rectangle{
//                id: recSie
//                height: 30
//                width: contentWidth
//                anchors.top: parent.top
//                anchors.topMargin: defaultMargin
//                anchors.left: ldbsize.right
//                anchors.leftMargin: defaultMargin*2
//                TextField{
//                    id: dbSize
//                    anchors.left: parent.left
//                    anchors.leftMargin: defaultMargin
//                    height: parent.height
//                    text: qsTr("2.4M")
//                    font.family: "Microsoft YaHei"
//                    font.pixelSize: 15
//                    selectByMouse: true
//                    cursorVisible: false
//                    readOnly: true
//                    verticalAlignment: Text.AlignVCenter
//                }
//            }
//        }


//        Rectangle{
//            height: 30+defaultMargin*2
//            width: parent.width
//            border.color: "#148014"
//            border.width: 1

//            Text{
//                id: ldbPath
//                text: qsTr("路径:")
//                height: 30
//                width: 30
//                anchors.top: parent.top
//                anchors.topMargin: defaultMargin
//                anchors.left: parent.left
//                anchors.leftMargin: defaultMargin
//                verticalAlignment: Text.AlignVCenter
//                font.family: "Microsoft YaHei"
//                font.pixelSize: 15
//            }

//            Rectangle{
//                id: recPath
//                height: 30
//                width: parent.width - ldbPath.width
//                anchors.top: parent.top
//                anchors.topMargin: defaultMargin
//                anchors.left: ldbPath.right
//                anchors.leftMargin: defaultMargin*2
//                TextField{
//                    id: dbPath
//                    anchors.left: parent.left
//                    anchors.leftMargin: defaultMargin
//                    height: parent.height
//                    width: parent.width
//                    text: qsTr("C:/Program Files (x86)/Microsoft SDKs/Windows Kits/10/ExtensionSDKs/Microsoft.VCLibs/14.0/Appx/Retail/x86/Microsoft.VCLibs.x86.14.00.appx")
//                    font.family: "Microsoft YaHei"
//                    font.pixelSize: 15
//                    selectByMouse: true
//                    cursorVisible: false
//                    readOnly: true
//                    verticalAlignment: Text.AlignVCenter
//                }
//            }
//        }
    }
}
