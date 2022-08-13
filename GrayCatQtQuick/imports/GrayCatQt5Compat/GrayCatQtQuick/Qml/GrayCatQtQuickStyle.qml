pragma Singleton
import QtQuick 2.12

QtObject {
    id: graycatqtquickstyle

    /* 获取相对于根窗口的全局的坐标，输入参数为需要获取全局坐标的对象 */
    function getGlobalPosition(targetObject) {
        var positionX = 0
        var positionY = 0
        var obj = targetObject

        /* 遍历所有的父窗口 */
        while (obj !== null) {
            /* 累加计算坐标 */
            positionX += obj.x
            positionY += obj.y

            obj = obj.parent
        }

        return {"x": positionX, "y": positionY}
    }
}
