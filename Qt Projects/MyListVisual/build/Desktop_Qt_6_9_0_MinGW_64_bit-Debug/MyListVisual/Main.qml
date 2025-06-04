import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: "Circular Doubly Linked List"
    property var nodeList: []

    Column{
        spacing: 10
        padding: 20
        TextField{
            id: inputData
            x:100
            y:100
            width: 200
            height: 20
            placeholderText: "Input data"
        }

        TextField{
            id: inputPos
            x:100
            y:100
            width: 200
            height: 20
            placeholderText: "Input position"
        }

        Button{
            text: "Add at the position"
            onClicked:{
                wrapper.addAtThePosition(inputData.text, inputPos.text)
            }
        }

        Button{
            text: "Add at the beginning"
            onClicked: {
                wrapper.addAtTheBeginning(inputData.text)
            }
        }
        Button{
            text: "Add at the end"

            onClicked: {
                wrapper.addAtTheEnd(inputData.text)
            }
        }
        Button{
            text: "Delete all"
            onClicked: {
                wrapper.deleteAll()
            }
        }
        Button{
            text: "Print all in back order"
            onClicked: {
                wrapper.printAllInBackOrder()
            }
        }
        Button{
            text: "Delete from position"
            onClicked: {
                wrapper.deleteFromPosition(inputPos.text)
            }
        }

        Button{
            text: "Show List"
            onClicked: {
                nodeList = wrapper.getAll()
                console.log(nodeList)
            }
        }

        Row{ //A Row is a layout element in QML that arranges its children horizontally (left to right).
             //It automatically places each child next to the previous one
            spacing: 5
            Repeater{ //The Repeater creates multiple items dynamically — like a for-loop in QML
                      //It repeats a template (called a delegate) for each item in the model.
                model: nodeList //The data (from C++) to loop over.
                delegate: Rectangle { //The visual template for one item (here: a square with text)
                    width: 30
                    height: 30
                    color: "red"
                    border.color: "black"
                    Text {
                        anchors.centerIn: parent
                        text: modelData
                    }
                }
            }
        }
    }
}
