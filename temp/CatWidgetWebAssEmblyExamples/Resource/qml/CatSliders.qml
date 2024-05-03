import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: root;
    //width: 250; height: 200;
    property color rootBackgroundColor: "white"
    property color sliderBackgroundColor: "white"
    property color sliderColor: "#773f72"
    property color slidingBlockColor: "#585858"
    property color slidingBlockPressColor: "#db4a15"
    property color slidingBorderColor: "transparent"
    property color textColor: "white"
    signal setRootBackgroundColor(color mcolor)

    function onRootBackgroundColor(setcolor)
    {
        root.rootBackgroundColor = setcolor;
    }

    signal setSliderBackgroundColor(color mcolor)

    function onSliderBackgroundColor(setcolor)
    {
        root.sliderBackgroundColor = setcolor;
    }

    signal setSliderColor(color mcolor)

    function onSliderColor(setcolor)
    {
        root.sliderColor = setcolor;
    }
    signal setSlidingBlockColor(color mcolor)

    function onSlidingBlockColor(setcolor)
    {
        root.slidingBlockColor = setcolor;
    }
    signal setSlidingBlockPressColor(color mcolor)

    function onSlidingBlockPressColor(setcolor)
    {
        root.slidingBlockPressColor = setcolor;
    }
    signal setSlidingBorderColor(color mcolor)

    function onSlidingBorderColor(setcolor)
    {
        root.slidingBorderColor = setcolor;
    }

    signal setTextColor(color mcolor)

    function onTextColor(setColor)
    {
        root.textColor = setColor;
    }
    Rectangle {
        id: rootbackground
        color: rootBackgroundColor;
        anchors.centerIn: parent;
        width: root.width;
        height: root.height;

        Column {
            spacing: 5

            anchors.centerIn: parent

            Text {
                id: sliderText
                text: qsTr("Slider");
                color: textColor;
                font {
                    bold: true
                    family: "Ubuntu"
                }
            }

            Slider {
                id: slider0
                from: 0; to: 100;
                value: 35;
                background: Rectangle {
                    x: slider0.leftPadding
                    y: slider0.topPadding + slider0.availableHeight / 2 - height / 2
                    implicitWidth: 200; implicitHeight: 4
                    width: slider0.availableWidth; height: implicitHeight
                    radius: 2; color: sliderBackgroundColor

                    Rectangle {
                        y: slider0.horizontal ? 0 : slider0.visualPosition * parent.height
                        width: slider0.horizontal ? slider0.position * parent.width : parent.width
                        height: parent.height
                        //height: slider0.horizontal ? parent.height : slider0.position * parent.height
                        color: sliderColor; radius: 2
                    }
                }

                handle: Rectangle {
                    x: slider0.leftPadding + slider0.visualPosition * (slider0.availableWidth - width)
                    y: slider0.topPadding + slider0.availableHeight / 2 - height / 2
                    implicitWidth: 14; implicitHeight: 14; radius: 7
                    color: slider0.pressed ? slidingBlockPressColor : slidingBlockColor
                    border.color: slidingBorderColor
                }


            }

            Slider {
                id: sliderv0
                from: 0; to: 100;
                value: 10;
                orientation: Qt.Vertical;
                background: Rectangle {
                    anchors.centerIn: parent
                    y: sliderv0.leftPadding
                    implicitWidth: 4; implicitHeight: 200
                    //x: sliderv0.bottomPadding + slider0.availableWidth /2 - width / 2
                    width: implicitWidth; height: sliderv0.availableHeight
                    radius: 2; color: sliderBackgroundColor

                    Rectangle {
                        y: sliderv0.vertical ? sliderv0.visualPosition * parent.height : 0
                        width: parent.width
                        height: sliderv0.vertical ? sliderv0.position * parent.height : parent.height
                        //height: slider0.horizontal ? parent.height : slider0.position * parent.height
                        color: sliderColor; radius: 2
                    }
                }

                handle: Rectangle {
                    y: sliderv0.leftPadding + sliderv0.visualPosition * (sliderv0.availableHeight - height)
                    x: sliderv0.bottomPadding + sliderv0.availableWidth / 2 - width / 2
                    implicitWidth: 14; implicitHeight: 14; radius: 7
                    color: sliderv0.pressed ? slidingBlockPressColor : slidingBlockColor
                    border.color: slidingBorderColor
                }
            }

            Text {
                id: rangesliderText
                text: qsTr("RangeSlider");
                color: textColor;
                font {
                    bold: true
                    family: "Ubuntu"
                }
            }

            RangeSlider {
                id: slider1
                //width: rootbackground.width;

                from: 0; to: 100; stepSize: 1
                first.value: 25; second.value: 75
                background: Rectangle {
                    x: slider1.leftPadding
                    y: slider1.topPadding + slider1.availableHeight / 2 - height / 2
                    implicitWidth: 200; implicitHeight: 4
                    width: slider1.availableWidth; height: implicitHeight
                    radius: 2; color: sliderBackgroundColor

                    Rectangle {
                        x: slider1.first.visualPosition * parent.width
                        width: slider1.second.visualPosition * parent.width - x
                        height: parent.height
                        color: sliderColor; radius: 2
                    }
                }

                first.handle: Rectangle {
                    x: slider1.leftPadding + slider1.first.visualPosition * (slider1.availableWidth - width)
                    y: slider1.topPadding + slider1.availableHeight / 2 - height / 2
                    implicitWidth: 14; implicitHeight: 14; radius: 7
                    color: slider1.first.pressed ? slidingBlockPressColor : slidingBlockColor
                    border.color: slidingBorderColor
                }

                second.handle: Rectangle {
                    x: slider1.leftPadding + slider1.second.visualPosition * (slider1.availableWidth - width)
                    y: slider1.topPadding + slider1.availableHeight / 2 - height / 2
                    implicitWidth: 14; implicitHeight: 14; radius: 7
                    color: slider1.second.pressed ? slidingBlockPressColor : slidingBlockColor
                    border.color: slidingBorderColor
                }
            }

            RangeSlider {
                id: sliderv1
                from: 0; to: 100; stepSize: 1;
                first.value: 10; second.value: 40;
                orientation: Qt.Vertical;
                background: Rectangle {
                    anchors.centerIn: parent
                    y: sliderv1.topPadding + sliderv1.availableHeight / 2 - height / 2
                    implicitWidth: 4; implicitHeight: 200
                    width: implicitWidth; height: sliderv1.availableHeight
                    radius: 2; color: sliderBackgroundColor

                    Rectangle {
                        y: sliderv1.second.visualPosition * parent.height
                        width: parent.width
                        height: sliderv1.first.visualPosition * parent.height - y
                        color: sliderColor; radius: 2
                    }
                }

                first.handle: Rectangle {
                    y: sliderv1.topPadding + sliderv1.first.visualPosition * (sliderv1.availableHeight - height)
                    x: sliderv1.leftPadding + sliderv1.first.visualPosition * (sliderv1.availableWidth - width)
                    implicitWidth: 14; implicitHeight: 14; radius: 7
                    color: sliderv1.first.pressed ? slidingBlockPressColor : slidingBlockColor
                    border.color: slidingBorderColor
                }

                second.handle: Rectangle {
                    y: sliderv1.topPadding + sliderv1.second.visualPosition * (sliderv1.availableHeight - height)
                    x: sliderv1.leftPadding + sliderv1.second.visualPosition * (sliderv1.availableWidth - width)
                    implicitWidth: 14; implicitHeight: 14; radius: 7
                    color: sliderv1.second.pressed ? slidingBlockPressColor : slidingBlockColor
                    border.color: slidingBorderColor
                }
            }
        }
    }
    Component.onCompleted: {
        root.setRootBackgroundColor.connect(root.onRootBackgroundColor)
        root.setSliderBackgroundColor.connect(root.onSliderBackgroundColor)
        root.setSliderColor.connect(root.onSliderColor)
        root.setSlidingBlockColor.connect(root.onSlidingBlockColor)
        root.setSlidingBlockPressColor.connect(root.onSlidingBlockPressColor)
        root.setSlidingBorderColor.connect(root.onSlidingBorderColor)
        root.setTextColor.connect(root.onTextColor)
    }
    Component.onDestruction: {
        root.setRootBackgroundColor.disconnect(root.onRootBackgroundColor)
        root.setSliderBackgroundColor.disconnect(root.onSliderBackgroundColor)
        root.setSliderColor.disconnect(root.onSliderColor)
        root.setSlidingBlockColor.disconnect(root.onSlidingBlockColor)
        root.setSlidingBlockPressColor.disconnect(root.onSlidingBlockPressColor)
        root.setTextColor.disconnect(root.onTextColor)
    }
}
