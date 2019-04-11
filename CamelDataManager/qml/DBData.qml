/*!
 *@file DBData.qml
 *@brief 浏览
 *@version 1.0
 *@section LICENSE Copyright (C) 2003-2103 CamelSoft Corporation
 *@author zhengtianzuo
*/
import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle{
    property int defaultMargin: 6
    property string curName: ""
    property int curType: 0
    property string curValue: ""

    id: frmWindow

    BaseMessageDialog{
        id: message
    }

    Row{
        id: rowData
        height: parent.height - control.height - defaultMargin*3
        width: parent.width - defaultMargin*2
        anchors.margins: defaultMargin
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: defaultMargin

        BaseTableView{
            id: tableView
            height: parent.height
            width: parent.width/2
            itemDelegate: Text {
                x: defaultMargin
                font.family: "Microsoft YaHei"
                font.pixelSize: 12
                verticalAlignment: Text.AlignVCenter
                color: "#000000"
                text: styleData.value
            }
            onClicked: {
                curValue = cDataManager.cls_funManagerData_GetData(row);
                if (curValue.length === 0){
                    message.showMsg(qsTr("获取数据错误"));
                    return;
                }
                curName = cDataManager.cls_funManagerData_GetName(row);
                curType = cDataManager.cls_funManagerData_GetType(row);
                textEdit.text = curValue;
            }
        }

        Rectangle{
            height: tableView.height
            width: parent.width/2 - defaultMargin
            border.color: "#148014"
            border.width: 1

            Column{
                id: colDetail
                anchors.fill: parent
                spacing: defaultMargin

                SwipeView {
                    id: view
                    height: parent.width
                    width: parent.width
                    currentIndex: 0
                    interactive: false

                    TextEdit{
                        id: textEdit
                        font.family: "Microsoft YaHei"
                        font.pixelSize: 14
                        selectByMouse: true
                        selectByKeyboard: true
                        wrapMode: TextEdit.Wrap
                    }

                    AnimatedImage{

                    }

                    Rectangle{

                    }

                    Rectangle{

                    }
                }

                BaseButton{
                    id: btnModify
                    height: 24
                    width: 120
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("应用修改")
                    onSClicked: {
                        if (textEdit.text.length === 0){
                            message.showMsg(qsTr("数据内容无效"));
                            return;
                        }
                        cDataManager.cls_funManagerData_Modify(curType, curName, textEdit.text);
                    }
                }
            }
        }
    }

    Rectangle{
        id: control
        anchors.top: rowData.bottom
        anchors.topMargin: defaultMargin
        anchors.horizontalCenter: parent.horizontalCenter
        height: 48
        width: parent.width - defaultMargin*2
        border.color: "#148014"
        border.width: 1

        BasePageNavigation{
            id: pageNavigation
            anchors.left: parent.left
            anchors.leftMargin: defaultMargin
            anchors.verticalCenter: parent.verticalCenter
            nCout: 23
            nCurPage: 1
            nPageSize: 5
            onSCurPage: {

            }
        }

        Row{
            anchors.right: parent.right
            anchors.rightMargin: defaultMargin
            height: parent.height
            width: parent.width - pageNavigation.width
            layoutDirection: Qt.RightToLeft
            spacing: defaultMargin

            BaseButton{
                id: btnDel
                height: 24
                width: 60
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("删除")
                onSClicked: {
                    if (curName.length === 0){
                        message.showMsg(qsTr("请先选择被删除数据."));
                        return;
                    }
                    dBDataDel.showWindow(curName,curType,curValue);
                }
            }

            BaseButton{
                id: btnAdd
                height: 24
                width: 60
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("添加")
                onSClicked: {
                    dBDataNew.showWindow();
                }
            }
        }
    }

    DBDataNew{
        id: dBDataNew
    }

    DBDataDel{
        id: dBDataDel
    }
}
