import QtQuick 2.12

Item {
    id: root 
    clip: true 
    //anchors.centerIn: parent 

    //Image对象属性抛出
    property alias source: image.source

    //SequentialAnimation对象元素抛出
    property alias animation_loops: squential_animation.loops 
    property alias animation_running: squential_animation.running 

    //PropertyAnimation对象元素抛出
    property double animation_from: 1 
    property double animation_to: 0.8 
    property int animation_duration: 2000


    Image {
        id: image 
        width: root.width
        height: root.height
        asynchronous: true

        SequentialAnimation {
            id: squential_animation
            loops: Animation.Infinite
            NumberAnimation {
                //id: property_animation 
                target: image 
                property: "scale"
                from: animation_from 
                to: animation_to 
                duration: animation_duration
                easing.type: Easing.InOutQuad
            }
            NumberAnimation {
                target: image 
                property: "scale"
                from: animation_to 
                to: animation_from
                duration: animation_duration
                easing.type: Easing.InOutQuad
            }
        }
    }
}
