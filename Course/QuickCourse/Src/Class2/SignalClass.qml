import QtQuick 2.12

Item {
 id: root

 // signal <signalName> [([ <type> <parameterName>[, ...] ])] // 信号定义

 // 无参数,可以省略括号
 signal defaultSignal
 signal defaultSignal1(string test)

 //on<Signal> 信号处理器,信号首字母大写
 onDefaultSignal: {
    console.log("root defaultSignal")
 }
 onDefaultSignal1: {
    console.log("root defaultSignal1: " + test)
 }

 // Connections 对象可以接收指定目标(target)的任意信号
 Item {
    anchors.fill: parent

    Connections {
        target: root
        /*onDefaultSignal: {
            console.log("test defaultSignal")
        }*/

        // qt 5.15 新用法
        function onDefaultSignal(){
           console.log("Connections test defaultSignal")
        }
    }

 }

 function testClass()
 {
    root.defaultSignal()
    root.defaultSignal1("test")
 }

 Timer {
    id: timer
    interval: 1000
    onTriggered: {
        testClass()
    }
 }

 function testSignalConnect()
 {
    console.log("testSignalConnect")
 }

 Component.onCompleted: {
    root.defaultSignal.connect(testSignalConnect) // 绑定信号与槽
    root.defaultSignal()
    root.defaultSignal.disconnect(testSignalConnect)
 }

}
