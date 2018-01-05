/*!
 *@file DBInfo.qml
 *@brief DB信息
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtCharts 2.2

Rectangle {
    property int defaultMargin: 6

    id: frmWindow
    visible: true

    Column{
        anchors.fill: parent

        Rectangle{
            id: dbInfo
            height: 30+defaultMargin*2
            width: parent.width
            border.color: "#148014"
            border.width: 1
            color: "transparent"

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
            id: dbpath
            height: 30+defaultMargin*2
            width: parent.width
            border.color: "#148014"
            border.width: 1

            BaseTextField{
                id: ldbPath
                showText: qsTr("路径:")
                inputWidth: parent.width-showWidth-defaultMargin*3
                Component.onCompleted: {
                    ldbPath.inputText = qsTr("C:/Program Files (x86)/Microsoft SDKs/Windows Kits/10/ExtensionSDKs/Microsoft.VCLibs/14.0/Appx/Retail/x86/Microsoft.VCLibs.x86.14.00.appx")
                    ldbPath.tNameCursorPos = 0
                }
            }
        }

        ChartView {
            height: parent.height - dbInfo.height - dbpath.height
            width: parent.width
            theme: ChartView.ChartThemeQt
            antialiasing: true
            legend.visible: false
            animationOptions: ChartView.AllAnimations

            PieSeries {
                id: pieSeries
                PieSlice {
                    borderColor: "#AAAAAA"
                    color: "#804040"
                    label: qsTr("整形")
                    labelVisible: true
                    value: 66.6
                }
                PieSlice {
                    borderColor: "#AAAAAA"
                    color: "#408040"
                    label: qsTr("字符串")
                    labelVisible: true
                    value: 30
                }
                PieSlice {
                    borderColor: "#AAAAAA"
                    color: "#404080"
                    label: qsTr("文件")
                    labelVisible: true
                    value: 3.4
                }
            }
        }
    }
}
