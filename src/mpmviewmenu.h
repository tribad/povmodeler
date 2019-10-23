#ifndef MPMVIEWMENU_H
#define MPMVIEWMENU_H

enum class GLView {
    Top,
    Bottom,
    Left,
    Right,
    Back,
    Front,
    Camera,
    Undefined
};

class MPMViewMenu
{
public:
    MPMViewMenu();
    virtual ~MPMViewMenu() {}
    virtual void togglePropertyVisibility(bool changed) = 0;
    virtual void toggleGlView(GLView view, bool changed) = 0;
};

#endif // MPMVIEWMENU_H
