import Qt5Compat.GraphicalEffects

DropShadow {
    id: root
    property int samples: 0
    horizontalOffset: samples / 2
    verticalOffset: samples / 2
}
