/*!
 *@file DBNewData.qml
 *@brief 新增数据
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow{
    id: frmWindow
    height: 400
    width: 600
    modality: Qt.ApplicationModal

    property int defaultMargin: 6

    function showWindow(){
        frmWindow.showNormal();
    }

    Column{
        height: parent.height - defaultMargin*2
        width: parent.width - defaultMargin*2
        anchors.centerIn: parent
        spacing: defaultMargin

        Row{
            height: 30+defaultMargin*2
            width: parent.width

            Text{
                id: lname
                text: qsTr("选择数据类型: ")
                height: 30+defaultMargin*2
                width: contentWidth
                verticalAlignment: Text.AlignVCenter
                font.family: "Microsoft YaHei"
                font.pixelSize: 15
            }

            ComboBox {
                id: comboBox
                height: 30+defaultMargin*2
                width: 200
                model: [qsTr("Short"), qsTr("Integer"), qsTr("Float"),
                    qsTr("Double"), qsTr("Currency"), qsTr("Date"),
                    qsTr("String"), qsTr("File"), qsTr("ByteArray"),
                    qsTr("ShortArray"), qsTr("IntegerArray"), qsTr("FloatArray"),
                    qsTr("DoubleArray"), qsTr("CurrencyArray"), qsTr("DateArray"),
                    qsTr("StringArray")]
            }
        }

        BaseTextField{
            id: name
            focus: true
            showText: qsTr("名称:")
            showWidth: 40
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: false
        }

        BaseTextEdit{
            id: value
            focus: true
            height: 260
            width: name.width
            anchors.horizontalCenter: parent.horizontalCenter
            tName.height: 230
            showText: qsTr("值:")
            showWidth: 40
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: false
        }

        BaseButton{
            id: btnOK
            height: 30
            width: 120
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("确定")
            onSClicked: {
                frmWindow.hide();
            }
        }
    }
}
