import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.3

Window {
    id: window
    width: 720 * .7
    height: 1240 * .7
    visible: true
    title: qsTr("Hello World")



    Connections {
            target: MainWindowController
    }

    Column{
        id: column
        spacing: 10

        Button {
            id: pushButtonPower
            checked: true
            text: qsTr("Power")
            anchors.horizontalCenter: parent.horizontalCenter
            property bool isPowerOn : false

            contentItem: Text {
                text: pushButtonPower.text
                font: pushButtonPower.font
                opacity: enabled ? 1.0 : 0.3
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: 150
                implicitHeight: 150
                opacity: enabled ? 1 : 0.3
                color: MainWindowController.powerButColor
                radius: size / 2

                readonly property real size: Math.min(pushButtonPower.width, pushButtonPower.height)
                width: size
                height: size
                anchors.centerIn: parent

                Canvas {
                    id: canvas
                    anchors.fill: parent

                    //                    Connections {
                    //                        target: control
                    //                        function onProgressChanged() { canvas.requestPaint(); }
                    //                    }

                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.clearRect(0, 0, width, height)
                        ctx.strokeStyle ="white"
                        ctx.lineWidth = parent.size / 15
                        ctx.beginPath()
                        var startAngle = 5.11
                        var endAngle = 10.63
                        ctx.arc(width / 2, height / 2, width / 2 - ctx.lineWidth / 2 - 2, startAngle, endAngle)
                        ctx.stroke()
                        ctx.strokeStyle = "white"
                        ctx.fillRect(width/2.1, 0, width/15, height/5)
                        ctx.roundedRect(width/2.05, 0, width/20, height/4, 1, 1);
                        ctx.stroke()
                    }
                }
            }

            onClicked: {
                MainWindowController.pushButtonPowerClicked();
            }
        }

        Rectangle{
            height: 3
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            color: "#BFBDBD"
            radius: 2
        }

        TemperatureDial{
            width: window.width
            height: window.height/2

        }

        Rectangle{
            height: 3
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            color: "#BFBDBD"
            radius: 2
        }
        Text {
            id: textLouvrePosition
            text: qsTr("Louvre position")
            anchors.left: parent.left
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            font.pointSize: 15
        }

        Row{
            id: row
            anchors.horizontalCenter: parent.horizontalCenter
            layoutDirection: Qt.LeftToRight
            spacing: 100


            Rectangle{
                id: rectangleFullOpen
                color: "#92D8FF"
                radius: 12
                width: 100
                height: 100

                Image {
                    id: imageFullOpen
                    x: parent.width / 2 - parent.width/2.1
                    y: parent.height / 2 - parent.height/2.1
                    height: parent.height/1.04
                    width: parent.width/1.06
                    source: "../image/full_open.png"
                    fillMode: Image.PreserveAspectFit



                }
            }

            Rectangle{
                id: rectangleHalfOpen
                color: "#92D8FF"
                radius: 12
                width: 100
                height: 100

                Image {
                    id: imageHalfOpen
                    x: parent.width / 2 - parent.width/2.1
                    y: parent.height / 2 - parent.height/2.1
                    height: parent.height/1.04
                    width: parent.width/1.06
                    source: "../image/half_open.png"
                    fillMode: Image.PreserveAspectFit



                }
            }


            //            Image {
            //                id: imageHalfOpen
            //                source: "image/half_open.png"
            //                fillMode: Image.PreserveAspectFit

            //            }
        }


    }










}





/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
