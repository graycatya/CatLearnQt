import QtQuick
import QtQuick.Controls

MouseArea{
    readonly property string version: "1.0"
    anchors.fill: parent 
    // 悬停事件是否被处理
    hoverEnabled: true
    /* 此属性保存组合的鼠标事件
     * 是否会自动传播到与此鼠标区域重叠但视觉堆叠顺序较低的其他鼠标区域
    */
    propagateComposedEvents: true
    // 此属性保存此鼠标区域的光标形状
    cursorShape: enabled ? Qt.PointingHandCursor : Qt.ForbiddenCursor

    //将accept设置为true将防止鼠标事件传播到此项下面的项。
    onDoubleClicked: function(mouse){ mouse.accepted = false; }
    onPositionChanged: function(mouse){ mouse.accepted = false; }
    onPressed: function(mouse){ mouse.accepted = false; }
    onPressAndHold: function(mouse){ mouse.accepted = false; }
    onClicked: function(mouse){ mouse.accepted = false; }
    onReleased: function(mouse){ mouse.accepted = false; }
    onWheel: function(wheel) {
        try {
            wheel.accepted = false;
        } catch(err) {
            console.log(err.message)
        }
    }
}
