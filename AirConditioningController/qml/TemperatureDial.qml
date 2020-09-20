import QtQuick 2.0
import QtQuick.Controls 2.3



Item {
    id: temperatureDial


    function getTempVisible(){
        if(comboBoxTemperatureValue.currentIndex == 0)
            return "°C"
        else
            return "°F"
    }

    function getTempMultiplication(value){
        if(comboBoxTemperatureValue.currentIndex == 0)
            return value
        else
            return (value * 9/5) + 32
    }

    Connections {
        target: MainWindowController

        onSendTemperature: {
            dialTemperature.value = temperature
        }

        onSetEnableControls:{
            dialTemperature.enabled= enabled
        }
    }

    Image {
        id: imageTemperatureBG
        anchors.left: temperatureDial.left
        anchors.right: temperatureDial.right
        anchors.top: temperatureDial.top
        anchors.bottom: temperatureValue.top

        source: "../image/temp_dial_bg.png"
        sourceSize.height: 0
        sourceSize.width: 0


        height: temperatureDial.height * (9/10)
        width: temperatureDial.width
        fillMode: Image.PreserveAspectFit

        Dial {
            id: dialTemperature
            x: imageTemperatureBG.width / 2 - width / 2
            y: imageTemperatureBG.height / 2 - height / 2
            width: imageTemperatureBG.width/1.3
            height: imageTemperatureBG.height/1.3
            enabled: false
            baselineOffset: 0
            wheelEnabled: false
            clip: false
            stepSize: 1
            live: true
            value: 15
            from: 15
            to: 35
            background: Rectangle {
                x: dialTemperature.width / 2 - width / 2
                y: dialTemperature.height / 2 - height / 2
                width: Math.max(64, Math.min(dialTemperature.width, dialTemperature.height))
                height: width
                color: "white"
                radius: width / 2
                border.color: dialTemperature.pressed ? "#4F4F4F" : "#BFBDBD"
                opacity: dialTemperature.enabled ? 1 : 0.3
            }

            handle: Rectangle {
                id: handleItem
                x: dialTemperature.background.x + dialTemperature.background.width  / 2 - width / 2
                y: dialTemperature.background.y + dialTemperature.background.height / 2 - height / 2
                width: Math.min(dialTemperature.width, dialTemperature.height) / 15
                height: Math.min(dialTemperature.width, dialTemperature.height) / 5
                color: dialTemperature.pressed ? "#4F4F4F" : "#BFBDBD"
                radius: 50

                antialiasing: true
                opacity: dialTemperature.enabled ? 1 : 0.3
                transform: [
                    Translate {
                        y: -Math.min(dialTemperature.background.width, dialTemperature.background.height) * 0.6 + handleItem.height / 2
                    },
                    Rotation {
                        angle: dialTemperature.angle
                        origin.x: handleItem.width / 2
                        origin.y: handleItem.height / 2
                    }
                ]
            }

            Text {
                id: temperatureText
                text: Math.round(getTempMultiplication(dialTemperature.value)) +  getTempVisible()
                x: dialTemperature.width / 2 - width / 2
                y: dialTemperature.height / 2 - height / 2
                width: dialTemperature.width/3
                height: dialTemperature.height/3
                font.pixelSize: Math.min(dialTemperature.width, dialTemperature.height)/3
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onValueChanged: MainWindowController.tempDialValueChanged(Math.round(dialTemperature.value))

        }


    }
    Row{
        id: temperatureValue
        anchors.left: temperatureDial.left
        anchors.right: temperatureDial.right
        anchors.top: imageTemperatureBG.bottom
        anchors.bottom: temperatureDial.bottom
        height: temperatureDial.height * (1/10)
        width: temperatureDial.width
        //spacing: 10

        Text{
            width: temperatureValue.width/2
            text: "Temperature display style"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 0
            anchors.leftMargin: 0
            font.pixelSize: Math.min(temperatureValue.width, temperatureValue.height)/2.2
        }

        ComboBox {
            id: comboBoxTemperatureValue
            width: temperatureValue.width/2.3
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            flat: false
            wheelEnabled: true
            currentIndex: 0
            editable: false
            model: ["Celsius", "Fahrenheit"]
            font.pixelSize: Math.min(temperatureValue.width, temperatureValue.height)/2.8
            anchors.rightMargin: 10

            delegate: ItemDelegate {
                width: comboBoxTemperatureValue.width
                contentItem: Text {
                    text: modelData
                    color: "#00A4FF"
                    font: comboBoxTemperatureValue.font
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                highlighted: comboBoxTemperatureValue.highlightedIndex === index
            }


            indicator: Canvas {
                id: canvas
                x: comboBoxTemperatureValue.width - width - comboBoxTemperatureValue.rightPadding
                y: comboBoxTemperatureValue.topPadding + (comboBoxTemperatureValue.availableHeight - height) / 2
                width: 12
                height: 8
                contextType: "2d"

                //                Connections {
                //                    target: comboBoxTemperatureValue
                //                    function onPressedChanged() { canvas.requestPaint(); }
                //                }

                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = comboBoxTemperatureValue.pressed ? "#007FB7" : "#00A4FF";
                    context.fill();
                }
            }

            contentItem: Text {
                //                leftPadding: 0
                //                rightPadding: control.indicator.width + control.spacing

                text: comboBoxTemperatureValue.displayText
                font: comboBoxTemperatureValue.font
                color: comboBoxTemperatureValue.pressed ? "#007FB7" : "#00A4FF"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideRight
            }

            background: Rectangle {
                implicitWidth: 120
                implicitHeight: 40
                border.color: comboBoxTemperatureValue.pressed ? "#007FB7" : "#00A4FF"
                border.width: comboBoxTemperatureValue.visualFocus ? 2 : 1
                radius: 5
            }

            popup: Popup {
                y: comboBoxTemperatureValue.height - 1
                width: comboBoxTemperatureValue.width
                implicitHeight: contentItem.implicitHeight
                padding: 1

                contentItem: ListView {
                    clip: true
                    implicitHeight: contentHeight
                    model: comboBoxTemperatureValue.popup.visible ? comboBoxTemperatureValue.delegateModel : null
                    currentIndex: comboBoxTemperatureValue.highlightedIndex

                    ScrollIndicator.vertical: ScrollIndicator { }
                }

                background: Rectangle {
                    border.color: "#00A4FF"
                    radius: 5
                }
            }
        }
    }
}







/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.6600000262260437;height:480;width:640}
}
##^##*/
