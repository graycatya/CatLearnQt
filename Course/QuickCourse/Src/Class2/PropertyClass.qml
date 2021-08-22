import QtQuick 2.12
import QtQml 2.12

Rectangle {
    id: root

    // 使用下面语法定义一个属性
    // [default] property <propertyType> <propertyName>: <value>
    property color defaultColor: "red" // 定义一个属性并赋初值

    // var 是一种万能类型
    property var varNumber: 1.0
    property var varString: "abc"
    property var varBool: false
    property var varList: [1, 2, "qt", true]
    property var varObject: Item { width: 100; height: 100 }

    // QML对象类型也可以作为一个属性类型
    property Item defaultItem

    /*
        列表类型属性
        [default] property list <<objectType>> <propertyName>: <value>
    */
    property list <QtObject> defaultListObject: [
        QtObject { objectName: "object0" },
        QtObject { objectName: "object1" },
        QtObject { objectName: "object2" }
    ]

    /*
        属性别名: 与普通的属性定义不同
        属性别名不需要分配一个新的唯一的存储空间，
        而是将新声明的属性(称为别名属性)作为一个已经存在的属性(被别名的属性)的直接引用
        [default] property alias <name>: <alias reference>
    */
    property alias defaultObjectName: objectN

    Item {
        id: objectN
    }

    /*
        默认属性
        对象定义可以有一个默认属性，默认属性至多有一个。
    */
    default property var defaultNumber


    /*
        只读属性
        readonly property <propertyType> <propertyName>: <initialValue>
    */
    readonly property int defaultId: 10 // 只读属性需要给定初值，或给定属性绑定


    property int defaultWidth: 400

    width: defaultWidth
    height: { width - 100 } // 绑定表达式初始化


    color: defaultColor // 鼎泰绑定自定义颜色属性

    /*
        声明一个自定义的属性，则会隐的为该属性创建一个值改变信号，以及一个信号处理器
        on<PropertyName>Changed
        并且自定义的属性或原生属性首字母要大写，才能使用信号处理器
    */
    onDefaultColorChanged: {
        console.log("defaultColor: " + root.defaultColor)
    }

    Component.onCompleted: {
        timer.start();
    }

    function testClass() {
        root.defaultColor = "gray"
        root.defaultWidth = 500

        console.log("root objectName: " + root.objectName)
        root.objectName = "rootName1"
        console.log("root objectName: " + root.objectName)

        // 打印列表类型里定义的对象名
        for(let i = 0; i < root.defaultListObject.length; i++)
        {
            console.log("listObjectname: " + root.defaultListObject[i].objectName)
        }
    }

    Timer {
        id: timer
        interval: 1000
        onTriggered: {
            testClass()
        }
    }

}
