/*!
 *@file DBDataDel.qml
 *@brief 删除数据
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

    function showWindow(curName,curType,curValue){
        name.inputText = curName;
		curType--;
		if (curType > 8) curType--;
        comboBox.currentIndex = curType;
        value.inputText = curValue;
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
        text: qsTr("删除数据")
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
                text: qsTr("数据类型: ")
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
				enabled: false
            }
        }

        BaseTextField{
            id: name
            focus: true
            showText: qsTr("名称:")
            showWidth: 40
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: true
        }

        BaseTextEdit{
            id: value
            focus: true
            height: 260
            width: name.width
            anchors.horizontalCenter: parent.horizontalCenter
            tName.height: 230
            tName.verticalAlignment: Text.AlignTop
            showText: qsTr("值:")
            showWidth: 40
            inputText: qsTr("")
            inputWidth: parent.width-showWidth-defaultMargin*3
            readOnly: true
        }

        BaseButton{
            id: btnOK
            height: 30
            width: 120
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("确定删除")
            onSClicked: {
                var intError = cDataManagerData.cls_funManagerData_Delete(comboBox.currentIndex);
                if (intError !== 1){
                    message.showMsg(qsTr("删除数据错误, 错误码: ") + intError);
                    return;
                }
                frmWindow.hide();
            }
        }
    }
}
