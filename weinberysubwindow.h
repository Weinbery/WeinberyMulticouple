#ifndef WEINBERYSUBWINDOW_H
#define WEINBERYSUBWINDOW_H

#include <QMdiSubWindow>

class WeinberySubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit WeinberySubWindow(QMdiSubWindow *parent = 0);
    /// 子窗口类型枚举
    enum SubWindowType {
        swNoneType = 0,
        swGraphic,              // 模型视图，默认创建一个，且程序默认只维护一个
        swDataVisualization,    // 数据可视化，2D曲线、图表，3D动态图等
        swStatusMonitor,        // 状态监显曲线，对计算状态进行管窥
        swTextType              // 打开类text文本类型文件，应对mcnp5输入文件inp的编辑
    };
    /// setter
    void setSubWindowType(SubWindowType windowType) { subWindowType = windowType; }
    /// getter
    SubWindowType getSubWindowType() const { return subWindowType; }

signals:

public slots:

private:
    SubWindowType subWindowType;
};

#endif // WEINBERYSUBWINDOW_H
