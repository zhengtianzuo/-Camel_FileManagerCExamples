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
            border.color: "#148014"
            border.width: 1

            BaseTextField{
                id: dbName
                showText: qsTr("名称:")
                inputText: qsTr("数据库的名称")
                inputWidth: parent.width-dbNum.width-dbSize.width-showWidth-defaultMargin*3
            }

            BaseTextField{
                id: dbNum
                anchors.left: dbName.right
                showText: qsTr("文件数:")
                inputText: qsTr("99")
                inputWidth: 60
            }

            BaseTextField{
                id: dbSize
                anchors.left: dbNum.right
                showText: qsTr("大小:")
                inputText: qsTr("1.25M")
                inputWidth: 80
            }
        }

        Rectangle{
            height: 30+defaultMargin*2
            width: parent.width
            border.color: "#148014"
            border.width: 1

            BaseTextField{
                id: ldbPath
                showText: qsTr("路径:")
                inputText: qsTr("C:/Program Files (x86)/Microsoft SDKs/Windows Kits/10/ExtensionSDKs/Microsoft.VCLibs/14.0/Appx/Retail/x86/Microsoft.VCLibs.x86.14.00.appx")
                inputWidth: parent.width-showWidth-defaultMargin*3
            }
        }
    }
}
