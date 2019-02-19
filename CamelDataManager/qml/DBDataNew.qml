/*!
 *@file DBDataNew.qml
 *@brief 新增数据
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow{
    id: frmWindow
    height: 460
    width: 600
    modality: Qt.ApplicationModal
    flags: Qt.Window | Qt.FramelessWindowHint

    property int defaultMargin: 6

    function showWindow(){
        frmWindow.showNormal();
    }

    BaseMessageDialog{
        id: message
    }

    Rectangle{
        anchors.fill: parent
        border.color: "#148014"
        border.width: 1
        color: "transparent"
    }

    Image{
        height: 24
        width: 24
        anchors.left: parent.left
        anchors.leftMargin: defaultMargin
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        source: "qrc:/images/dromedary.ico"
    }

    Text{
        anchors.left: parent.left
        anchors.leftMargin: 40
        height: 36
        text: qsTr("添加数据")
        font.family: "Microsoft YaHei"
        font.pixelSize: 12
        verticalAlignment: Text.AlignVCenter
        color: "#148014"
    }

    BaseButton{
        id: btnClose
        height: 24
        width: 24
        anchors.top: parent.top
        anchors.topMargin: defaultMargin
        anchors.right: parent.right
        anchors.rightMargin: defaultMargin
        imgEntered: "qrc:/images/close(3).png"
        imgExited: "qrc:/images/close.png"
        imgPressed: "qrc:/images/close(1).png"
        onSClicked: {
            close();
        }
    }

    Column{
        anchors.top: parent.top
        anchors.topMargin: 40
        width: parent.width - defaultMargin*2
        anchors.horizontalCenter: parent.horizontalCenter
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
                font.pixelSize: 12
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
                currentIndex: 6
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
            text: qsTr("添加完成")
            onSClicked: {
                if (name.inputText.length === 0){
                    message.showMsg(qsTr("请输入数据名称"));
                    return;
                }
                if (value.inputText.length === 0){
                    message.showMsg(qsTr("请输入数据内容"));
                    return;
                }
                var intError = cDataManager.cls_funManagerData_Combine(comboBox.currentIndex, name.inputText, value.inputText);
                if (intError !== 1){
                    message.showMsg(qsTr("添加数据错误, 错误码: ") + intError);
                    return;
                }
                frmWindow.hide();
            }
        }
    }
}
