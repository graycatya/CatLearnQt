import QtQuick 2.12

Rectangle {
    id: catrectangle
    color: "transparent"
    border.color: "transparent"


    Canvas {
        id: canvasbackground
        anchors.fill: parent
        contextType: "2d";
        onPaint: {
            context.lineWidth = 10;
            context.strokeStyle = "red";
            roundRect(context, 10, 10, canvasbackground.width,canvasbackground.height, 10)
            context.stroke();
        }

    }


    function roundRect(ctx, x, y, w, h, r) {
        // 开始绘制
        ctx.beginPath()
        // 左上角
        ctx.arc(x + r, y + r, r, Math.PI, Math.PI * 1.5)

        // 右上角
        ctx.arc(x + w - r, y + r, r, Math.PI * 1.5, Math.PI * 2)

        // border-right
        ctx.lineTo(x + w, y + h - r)

        // 右下角
        ctx.arc(x + w - r, y + h - r, r, 0, Math.PI * 0.5)

        // border-bottom
        ctx.lineTo(x + r, y + h)

        // 左下角
        ctx.arc(x + r, y + h - r, r, Math.PI * 0.5, Math.PI)

        // border-left
        ctx.lineTo(x, y + r)


        // 这里是使用 fill 还是 stroke都可以，二选一即可，但是需要与上面对应
        //ctx.fill()
        ctx.stroke()
        ctx.closePath()
        // 剪切
        ctx.clip()
    }

}
