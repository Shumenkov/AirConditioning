import QtQuick 2.4
import QtQuick.Controls 2.3

//import MainWindowController 1.0
Item {

    //    MainWindowController {
    //        id: settings
    //    }
    width: 701
    height: 264

    Connections {
        target: MainWindowController
        onSendBodyImage: {
            bodyImage.source = bodyImageSourse
        }
        onSendOnIndicator: {
            onIndicator.source = indicatorSourse
        }

        onSendTemperature: {
            temperatureLabel.text = temperature
        }
    }

    FontLoader {
        id: digitalFont
        source: "qrc:/src/Digital.ttf"
    }

    Image {
        id: bodyImage
        x: 0
        y: 0
        width: 701
        height: 264
        source: "qrc:/Images/close.png"
        fillMode: Image.PreserveAspectFit

        Image {
            id: onIndicator
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 652
            anchors.bottomMargin: 205
            anchors.topMargin: 40
            anchors.rightMargin: 30
            source: "qrc:/Images/OFF.png"
            fillMode: Image.PreserveAspectFit
        }

        Label {
            id: temperatureLabel
            text: "4554"
            anchors.fill: parent
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            anchors.bottomMargin: 166
            anchors.rightMargin: 30
            anchors.topMargin: 72
            anchors.leftMargin: 630
            font.pointSize: 20
            font.family: digitalFont.name
            color: "white"
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:3}D{i:5}
}
##^##*/

