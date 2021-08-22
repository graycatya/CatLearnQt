import QtQuick 2.12

Item {
    id: root

    function testClass()
    {
        return "Method testClass"
    }

    function testClass1(str)
    {
        return "Method testClass: " + str;
    }

    Component.onCompleted: {
        console.log(root.testClass())
        console.log(root.testClass1("Name"))
    }


}
