/*!
 *@file DBDelete.qml
 *@brief 删除
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

    Row{
        anchors.margins: defaultMargin
        anchors.centerIn: parent
        spacing: defaultMargin

        BaseButton{
            id: btnClear
            height: 48
            width: 120
            text: qsTr("清空")
            onSClicked: {

            }
        }

        Column{
            BaseButton{
                id: btnDelete
                height: 24
                width: 120
                text: qsTr("删除")
                onSClicked: {

                }
            }

            BaseCheckBox{
                id: chkDelete
                height: 24
                width: 120
                text: qsTr("同时本地也删除")
            }
        }
    }
}
