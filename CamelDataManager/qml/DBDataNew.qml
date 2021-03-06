﻿/*!
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

    function newLine(){
        listModel.append({"name":"", "value":""})
        listModel.sync();
    }

    function showWindow(){
        listModel.clear();
        newLine();
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
            id: selectLine
            height: 30+defaultMargin*2
            width: parent.width
            spacing: defaultMargin

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
                onCurrentIndexChanged: {
                    switch (currentIndex)
                    {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                        break;
                    case 14:
                        break;
                    case 15:
                        break;
                    default:
                        break;
                    }

                }
            }

            BaseButton{
                id: btnAddline
                height: 30
                width: 120
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("增加行")
                onSClicked: {
                    newLine();
                }
            }

            BaseButton{
                id: btnOK
                height: 30
                width: 120
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("添加完成")
                onSClicked: {
                    var rowCount = listModel.count;
                    for( var i = 0;i < rowCount;i++ ) {
                        var model = listModel.get(i);
                        if (model.name.length === 0){
                            var info = qsTr("请输入第") + (i+1) + qsTr("行数据名称");
                            message.showMsg(info);
                            return;
                        }
                        if (model.value.length === 0){
                            var info1 = qsTr("请输入第") + (i+1) + qsTr("行数据内容");
                            message.showMsg(info1);
                            return;
                        }
                        var intError = cDataManagerData.cls_funManagerData_Combine(comboBox.currentIndex, model.name, model.value);
                        if (intError !== 1){
                            var info2 = qsTr("添加第") + (i+1) + qsTr("行数据错误, 错误码: " + intError);
                            message.showMsg(info2);
                            return;
                        }
                    }
                    frmWindow.hide();
                }
            }
        }

        Rectangle{
            id: listviewback
            height: parent.height - selectLine.height - defaultMargin*2
            width: parent.width
            color: "red"

            ListView{
                id: listview
                height: contentHeight
                width: parent.width
                model: listModel
                delegate: listDelegate
                interactive: false
            }
        }

        ListModel {
            id: listModel
        }

        Component{
            id: listDelegate

            Row{
                height: 30+defaultMargin*2
                width: parent.width

                Rectangle{
                    height: 30+defaultMargin*2
                    width: 30+defaultMargin*2
                    border.color: "#148014"
                    border.width: 1

                    Text {
                        height: 32
                        width: 32
                        anchors.centerIn: parent
                        font.family: "Microsoft YaHei"
                        font.pixelSize: 12
                        text: model.index+1
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                BaseTextField{
                    id: name
                    focus: true
                    showText: qsTr("名称:")
                    showWidth: 40
                    inputText: qsTr("")
                    inputWidth: (parent.width-parent.height)/3-showWidth-defaultMargin*3
                    readOnly: false
                    onSEditingFinished:{
                        listModel.set(model.index, {"name": text})
                    }
                }

                BaseTextEdit{
                    id: value
                    focus: true
                    height: name.height
                    width: name.width*2
                    tName.height: 30
                    showText: qsTr("值:")
                    showWidth: 40
                    inputText: qsTr("")
                    inputWidth: (parent.width-parent.height)/3*2-showWidth-defaultMargin*3
                    readOnly: false
                    onSEditingFinished:{
                        listModel.set(model.index, {"value": text})
                    }
                }
            }
        }
    }
}
