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
            id: label
            x: 644
            y: 71
            text: ""
        }
    }
}
