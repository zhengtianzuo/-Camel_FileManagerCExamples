/*!
 *@file DBPass.qml
 *@brief 密码
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow{
    id: frmWindow
    height: dbPass.height+btnOK.height+defaultMargin*2
    width: 300
    modality: Qt.ApplicationModal

    property int defaultMargin: 6
    signal sinputText(string inputText);

    function showWindow(){
        frmWindow.showNormal();
        dbPass.tName.forceActiveFocus();
    }

    Column{
        anchors.fill: parent
        spacing: defaultMargin

        BaseTextField{
            id: dbPass
            focus: true
            showText: qsTr("密码:")
            showWidth: 80
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: false
            echoMode: TextInput.Password
        }

        BaseButton{
            id: btnOK
            height: 30
            width: 120
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("确定")
            onSClicked: {
                frmWindow.hide();
                sinputText(dbPass.inputText);
            }
        }
    }
}
