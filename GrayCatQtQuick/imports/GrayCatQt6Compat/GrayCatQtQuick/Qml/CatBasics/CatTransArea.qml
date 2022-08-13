import QtQuick 2.12
import QtQuick.Controls 2.12

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
    onDoubleClicked: { mouse.accepted = false; }
    onPositionChanged: { mouse.accepted = false; }
    onPressed: { mouse.accepted = false; }
    onPressAndHold: { mouse.accepted = false; }
    onClicked: { mouse.accepted = false; }
    onReleased: { mouse.accepted = false; }
    onWheel: {
        try {
            wheel.accepted = false;
        } catch(err) {
            console.log(err.message)
        }
    }
}
