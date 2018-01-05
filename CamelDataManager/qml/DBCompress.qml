/*!
 *@file DBCompress.qml
 *@brief 压缩
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle{
    property int defaultMargin: 6

    id: frmWindow
    border.color: "#148014"
    border.width: 1

    Rectangle{
        height: parent.height
        width: parent.width
        border.color: "#148014"
        border.width: 1

        Column{
            anchors.verticalCenter: parent.verticalCenter
            height: contentHeight
            width: parent.width
            spacing: defaultMargin

            BaseProgress{
                id: cProgress
                height: 30
                width: parent.width*9/10
                anchors.horizontalCenter: parent.horizontalCenter
                progress: 66

                BaseProgress{
                    id: pProgress
                    height: 10
                    width: parent.width
                    anchors.bottom: parent.bottom
                    progress: 88
                }
            }

            Row{
                width: btnAnalysis.width+btnCompress.width
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: defaultMargin

                BaseButton{
                    id: btnAnalysis
                    height: 30
                    width: 120
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("分析")
                    onSClicked: {

                    }
                }

                BaseButton{
                    id: btnCompress
                    height: 30
                    width: 120
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("压缩")
                    onSClicked: {

                    }
                }
            }
        }
    }
}
