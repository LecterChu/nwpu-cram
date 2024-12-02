/*
不鼓励内卷，不鼓励抄袭，不要照搬仓库里的实验作业，该上的课还是要好好上，该写的作业还是要好好写，该做的实验还是要好好做
 *
 ** 遇到的问题与解决过程 **
本次作业中我遇到的问题主要是在投影函数`project2_curve`和`project2_face`这两个函数
我开始的实现虽然可以通过编译 也可以运行
但会报Runtime Error 具体报错是`Qvector`中出现了"Index out of range"的问题

**解决方案1:**
我在这两个函数中可能出现越界的地方添加了判断
也通过`qDebug`函数对这两个函数的返回情况进行打印 确信我确实是把投影点作为结果返回了的
但这些措施都不起作用

** 解决方案2:**
以`project2_curve`函数为例,我去寻找了它的调用关系,发现它只在`DesignCommand.cpp`中被调用
我去阅读了调用project2_curve的源码
发现这个函数的返回值应当包括两个点
一个是投影点 还有一个是被投影点
`DesignCommand.cpp`会给这两个点之间画一条线(所以这里当返回两个相同点的时候会触发`abort`)
当返回了这两个点之后,问题解决

** 解决方案2(续):**
成功解决问题后,我发现程序绘图还有点问题,不会绘制投影点
再次阅读源码后,我发现我返回数组的两个点的顺序写反了
返回的点集有一定的顺序 投影点为第2个 而被投影点是第1个
`DesignCommand.cpp`会取数组中第2个点,在图上绘制投影点
修改后绘图正确
 */

#ifndef BASICMODELING_H
#define BASICMODELING_H

#include "ModelMaker.hpp"
#include <TopoDS_Shape.hxx>
#include "TopoDS_Edge.hxx"
#include <TopoDS.hxx>
#include <GeomAPI_ExtremaCurveCurve.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <GeomAPI_IntCS.hxx>
#include <AIS_InteractiveContext.hxx>
#include <QVector>
#include<iostream>
using std::cout;

class BasicModeling
{
public:
    /*****************************************************x
     * QVector <gp_Pnt> disperse(TopoDS_Shape shape)
     * 输入：TopoDS_Shape shape 由曲线构成的拓扑边
     * 输出：QVector <gp_Pnt> 一组解析几何点
     *
     * TODO: 对曲线构成的拓扑边进行离散化。
     * 判断拓扑形状是否为边，并在拓扑边上均匀选取A个点，A为学号末两位数。
     * 通过参数化曲线获取边参数取值范围。根据所需取点个数A计算步长。
     * 依照步长依次获取曲线上的点并放入数组中。
     * ***************************************************/
    static QVector <gp_Pnt> disperse(TopoDS_Shape shape) {
        /*
            这段代码的主要实现思路是对曲线构成的拓扑边进行离散化，即在拓扑边上均匀选取一定数量的点，生成一组解析几何点。以下是主要的步骤：

            1.判断拓扑形状是否为边： 使用 shape.ShapeType() == TopAbs_EDGE 条件判断，确保处理的拓扑形状为边。
            2.强制类型转换： 将 TopoDS_Shape 强制转换为 TopoDS_Edge，以便后续获取边的参数化曲线等信息。
            3.确定点的数量： 设置需要在拓扑边上均匀选取的点的数量，这里是59个点。
            4.获取边的参数范围： 使用 BRep_Tool::Curve 获取边的参数化曲线以及曲线的参数范围。
            5.计算步长： 根据所需的点的数量，计算参数范围内的步长。
            6.循环获取点： 使用循环依次计算曲线上的点，步长由前面计算得到，保证在参数范围内均匀获取点。
            7.将点添加到数组： 将计算得到的点逐个添加到 QVector <gp_Pnt> 数组中。
            8.返回结果： 返回包含离散化点的数组。
        */

        QVector <gp_Pnt> points;

        // 判断拓扑形状是否为边
        if (shape.ShapeType() == TopAbs_EDGE) {
            // 将TopoDS_Shape强制转换为TopoDS_Edge
            TopoDS_Edge edge = TopoDS::Edge(shape);

            // 在拓扑边上均匀选取59个点 这里要-1 否则会多一个点
            Standard_Integer numPoints = 59 - 1;

            // 通过参数化曲线获取边参数取值范围
            Standard_Real uStart, uEnd;
            // BRep_Tool::Curve 通过输入的拓扑边 edge，获取其参数化曲线以及曲线的参数范围（起始和终止参数值）
            Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, uStart, uEnd);

            // 计算步长
            Standard_Real step = (uEnd - uStart) / numPoints;

            // 依照步长依次获取曲线上的点并放入数组中
            for (Standard_Integer i = 0; i <= numPoints; ++i) {
                Standard_Real u = uStart + i * step;
                // 通过参数u获取曲线上的点
                gp_Pnt point = curve->Value(u);
                points.push_back(point);
            }
        }

        return points;
    }

    /*****************************************************x
     * QVector <gp_Pnt> get_extrema(TopoDS_Shape shape1, TopoDS_Shape shape2)
     * 输入：TopoDS_Shape shape1 由曲线构成的拓扑边
     *      TopoDS_Shape shape2 由曲线构成的拓扑边
     * 输出：QVector <gp_Pnt> 一组解析几何点
     *
     * TODO: 计算两条拓扑边的最大极值点和最小极值点。
     * 判断两个拓扑形状的类型是否为边，并通过求极值算法计算所有极值点。
     * 从所有极值点找出最大极值点和最小极值点，分别放入数组中。
     * 数组0和1位存放最大极值点，数组2和3位方最小极值点。
     * ***************************************************/
    static QVector <gp_Pnt> get_extrema(TopoDS_Shape shape1, TopoDS_Shape shape2) {
        /*
         * 这段代码的主要目标是计算两条拓扑边的最大和最小极值点。以下是代码的主要实现思路：

        1.判断拓扑形状类型： 首先，通过 shape1 和 shape2 的 ShapeType() 函数判断它们是否为边（TopAbs_EDGE 类型）。
        2.获取几何曲线： 如果两个形状都是边，将它们转换为 TopoDS_Edge 类型，并使用 BRep_Tool::Curve 函数获取对应的几何曲线以及曲线的参数范围。
        3.创建求极值算法对象： 使用 GeomAPI_ExtremaCurveCurve 类创建一个求解两条曲线之间极值的算法对象，并传入相应的几何曲线和参数范围。
        4.遍历极值点： 获取极值点的个数，并在有极值点的情况下遍历所有极值点，找出最大和最小的极值距离。对于每个极值点，使用 ecc.Distance 获取距离，使用 ecc.Points 获取极值点的坐标。
        5.更新最大和最小极值点： 在遍历的过程中，比较当前极值点的距离，如果大于最大极值距离，则更新最大极值点；如果小于最小极值距离，则更新最小极值点。
        6.将结果存入数组： 将找到的最大和最小极值点分别存入 points 数组中，按照数组的顺序，0 和 1 位存放最大极值点，2 和 3 位存放最小极值点。
        7.返回结果： 返回包含最大和最小极值点的 points 数组。
         */

        QVector <gp_Pnt> points;

        // 判断两个拓扑形状是否为边
        if (shape1.ShapeType() == TopAbs_EDGE && shape2.ShapeType() == TopAbs_EDGE) {
            // 将拓扑边转换为几何曲线
            TopoDS_Edge edge1 = TopoDS::Edge(shape1);
            TopoDS_Edge edge2 = TopoDS::Edge(shape2);
            // 获取曲线的参数范围
            Standard_Real first1, last1, first2, last2;
            // BRep_Tool::Curve 通过输入的拓扑边 edge，获取其参数化曲线以及曲线的参数范围（起始和终止参数值）
            Handle(Geom_Curve) curve1 = BRep_Tool::Curve(edge1, first1, last1);
            Handle(Geom_Curve) curve2 = BRep_Tool::Curve(edge2, first2, last2);

            // 创建求极值算法对象
            /*
                GeomAPI_ExtremaCurveCurve：这是OpenCASCADE（OCC）库提供的一个类。它属于几何算法包，用于计算两条曲线之间的极值距离。
                1.ecc：这是GeomAPI_ExtremaCurveCurve类的一个实例。它代表计算两条曲线（curve1和curve2）之间的极值距离。
                2.curve1和curve2：这是几何曲线对象的句柄。它们使用BRep_Tool::Curve函数从边（edge1和edge2）中获得。这些曲线表示边的几何形状。
                3.first1、last1、first2、last2：这些是曲线的参数范围。这些参数指定了计算极值距离的区间。它们使用BRep_Tool::Curve获得，并表示每条曲线的有效参数范围。
            */
            GeomAPI_ExtremaCurveCurve ecc(curve1, curve2, first1, last1, first2, last2);

            // 获取极值点的个数
            int num = ecc.NbExtrema();

            // 如果有极值点，遍历所有极值点，找出最大和最小的极值距离
            if (num > 0) {
                Standard_Real max_dist = 0.0;
                Standard_Real min_dist = RealLast();
                gp_Pnt max_pnt1, max_pnt2, min_pnt1, min_pnt2;

                for (int i = 1; i <= num; i++) {
                    // 获取第i个极值点的距离和坐标
                    Standard_Real dist = ecc.Distance(i);
                    gp_Pnt pnt1, pnt2;
                    ecc.Points(i, pnt1, pnt2);

                    // 如果距离大于最大极值距离，更新最大极值点
                    if (dist > max_dist) {
                        max_dist = dist;
                        max_pnt1 = pnt1;
                        max_pnt2 = pnt2;
                    }

                    // 如果距离小于最小极值距离，更新最小极值点
                    if (dist < min_dist) {
                        min_dist = dist;
                        min_pnt1 = pnt1;
                        min_pnt2 = pnt2;
                    }
                }

                // 将最大和最小的极值点放入数组中
                points.push_back(max_pnt1);
                points.push_back(max_pnt2);
                points.push_back(min_pnt1);
                points.push_back(min_pnt2);
            }
        }

        return points;
    }

    /*****************************************************x
     * QVector <gp_Pnt> project2_curve(TopoDS_Shape shape1, TopoDS_Shape shape2)
     * 输入：TopoDS_Shape shape1 拓扑点/边
     *      TopoDS_Shape shape2 拓扑边/点
     * 输出：QVector <gp_Pnt> 一组解析几何点
     *
     * TODO: 计算拓扑点到拓扑边的投影。
     * 注意：shape1和shape2不一定是拓扑点或拓扑边，需要进行判断。
     * ***************************************************/
    static QVector <gp_Pnt> project2_curve(TopoDS_Shape shape1, TopoDS_Shape shape2) {
        /*
            实现思路：

        1.判断输入的两个TopoDS_Shape对象的类型，分别为拓扑点/边。
        如果输入的是拓扑点和拓扑边，则获取拓扑点的几何点和拓扑边的几何曲线。
        2.利用OpenCASCADE的GeomAPI_ProjectPointOnCurve类计算点到曲线的投影，并将结果存储在QVector<gp_Pnt>中。
        3.根据投影点和被投影点的不同情况，将其添加到points中，并返回。

        特殊情况处理：
        函数中考虑了输入为拓扑点/边和拓扑边/点两种情况，并在需要时进行了交换处理。
        若输入的拓扑点和拓扑边不符合要求，函数将返回一个空的点集合。
        */

        QVector <gp_Pnt> points;
            // 判断shape1和shape2的类型
            TopAbs_ShapeEnum type1 = shape1.ShapeType();
            TopAbs_ShapeEnum type2 = shape2.ShapeType();
            // 如果shape1是拓扑点，shape2是拓扑边
            if (type1 == TopAbs_VERTEX && type2 == TopAbs_EDGE) {
                // 获取拓扑点的几何点
                gp_Pnt pnt = BRep_Tool::Pnt(TopoDS::Vertex(shape1));
                // 获取拓扑边的几何曲线
                Standard_Real f, l;
                Handle(Geom_Curve) curve = BRep_Tool::Curve(TopoDS::Edge(shape2), f, l);
                // 计算点到曲线的投影
                // 在构造函数中，传入拓扑点、拓扑边的几何曲线以及曲线的参数范围。
                // 通过proj.Point(index)可以获取计算结果中的投影点。
                GeomAPI_ProjectPointOnCurve proj(pnt, curve, f, l);
                // 如果有投影点，取第一个投影点
                if (proj.NbPoints() > 0) {
                    // 这里需要去读明白 DesignCommand.cpp 中调用这个函数的源码
                    // 要返回的点不只有投影点，还需要被投影点
                    TopoDS_Vertex vertex = TopoDS::Vertex(shape1);
                    points.append(BRep_Tool::Pnt(vertex));

                    // 返回的点集有一定的顺序 投影点为第2个 而被投影点是第1个
                    points.append(proj.Point(1));
                }
            }
            // 如果shape1是拓扑边，shape2是拓扑点
            else if (type1 == TopAbs_EDGE && type2 == TopAbs_VERTEX) {
                // 交换shape1和shape2，调用同一个函数
                points = project2_curve(shape2, shape1);
            }
            // 否则，返回空的点集合
            return points;
    }

    /*****************************************************x
     * QVector <gp_Pnt> project2_face(TopoDS_Shape shape1, TopoDS_Shape shape2)
     * 输入：TopoDS_Shape shape1 拓扑点/面
     *      TopoDS_Shape shape2 拓扑面/点
     * 输出：QVector <gp_Pnt> 一组解析几何点
     *
     * TODO: 计算拓扑点到拓扑面的投影。
     * 注意：shape1和shape2不一定是拓扑点和拓扑面，需要进行判断。
     * ***************************************************/
    static QVector <gp_Pnt> project2_face(TopoDS_Shape shape1, TopoDS_Shape shape2) {
        /*
            实现思路:
                1.预处理:
                    通过 shape1.ShapeType() 和 shape2.ShapeType() 判断输入的两个拓扑实体的类型，确保 shape1 是拓扑点，shape2 是拓扑面。
                    若不满足条件，则通过交换 shape1 和 shape2，保证 shape1 是拓扑点，shape2 是拓扑面。
                2.拓扑转换：
                    将 shape1 和 shape2 转换为对应的拓扑点 vertex 和拓扑面 face。
                3.获取拓扑点坐标：
                    通过 BRep_Tool::Pnt(vertex) 获取拓扑点的坐标，存储在 gp_Pnt point 中。
                4.获取拓扑面曲面：
                    通过 BRep_Tool::Surface(face) 获取拓扑面的曲面，存储在 Handle_Geom_Surface surface 中。
                5.计算投影：
                    使用 GeomAPI_ProjectPointOnSurf 类计算拓扑点到拓扑面的投影，将拓扑点投影到曲面上。
                6.处理投影结果：
                    如果投影结果中有点（projectPoint.NbPoints() > 0），则将拓扑点和投影点按照一定顺序添加到 points 中。
                7.返回结果：
        */

        QVector<gp_Pnt> points;

        // 判断shape1和shape2的类型，确保shape1是拓扑点，shape2是拓扑面
        if (shape1.ShapeType() == TopAbs_VERTEX && shape2.ShapeType() == TopAbs_FACE) {
            // 将shape1和shape2转换为对应的拓扑点和拓扑面
            TopoDS_Vertex vertex = TopoDS::Vertex(shape1);
            TopoDS_Face face = TopoDS::Face(shape2);

            // 获取拓扑点的坐标
            gp_Pnt point = BRep_Tool::Pnt(vertex);

            // 获取拓扑面的曲面
            Handle_Geom_Surface surface = BRep_Tool::Surface(face);

            // 使用GeomAPI_ProjectPointOnSurf计算拓扑点到拓扑面的投影
            // 后续代码中可以通过调用 projectPoint.NearestPoint() 获取点到曲面的投影点
            GeomAPI_ProjectPointOnSurf projectPoint(point, surface);

            // 获取投影结果
            if (projectPoint.NbPoints() > 0) {
                // 这里需要去读明白 DesignCommand3D.cpp 中调用这个函数的源码
                // 要返回的点不只有投影点，还需要被投影点
                TopoDS_Vertex vertex = TopoDS::Vertex(shape1);
                points.append(BRep_Tool::Pnt(vertex));

                // 返回的点集有一定的顺序 投影点为第2个 而被投影点是第1个
                points.append(projectPoint.NearestPoint());
            }
        } else if (shape2.ShapeType() == TopAbs_VERTEX && shape1.ShapeType() == TopAbs_FACE){
            // 交换shape1和shape2，调用同一个函数
            return project2_face(shape2,shape1);
        }
        return points;
    }

    /*****************************************************x
     * void selection_activate(int selectionType, Handle(AIS_InteractiveContext) context)
     * 输入：int selectionType 模型选择类别
     *      Handle(AIS_InteractiveContext) context 一个AIS_InteractiveContext
     *
     * TODO: 针对所有可见模型切换选择模式。
     * 禁用所有已激活选择模式，根据输入的模型选择类别激活选择模式。
     * 模型选择类别数值参考MainWindow.cpp中重置选择、选择点、选择边、选择面、选择实体按钮代码。
     * ***************************************************/
    static void selection_activate(int selectionType, Handle(AIS_InteractiveContext) context) {
        // 这个函数比较简单 就是通过context->Activate这个函数激活选择模式
        // 主要难点是要去看MainWindow.cpp里面的代码 知道selectionType的取值的含义
        // 这里我们遇到一个问题 例如选择点 本来使用的是 context->Activate(TopAbs_SHAPE);
        // 但实际上在使用中发现这和要求的功能不相同 无法做到选择点
        // 解决方案:这里需要使用AIS_Shape::SelectionMode进行包装
        // AIS_Shape::SelectionMode这个函数会将传入的宏做一个映射

        // 已经选中的对象清除
        context->ClearSelected(true);
        // 禁用所有已激活选择模式
        context->Deactivate();

        // 根据输入的模型选择类别激活选择模式
        switch (selectionType) {
        case 0: // 重置选择
            break;
        case 1: // 选择点
            //context->Activate(TopAbs_SHAPE); //TopAbs_VERTEX
            // Return selection mode for specified shape type.
            context->Activate(AIS_Shape::SelectionMode(TopAbs_VERTEX));
            break;
        case 2: // 选择边
            context->Activate(AIS_Shape::SelectionMode(TopAbs_EDGE));
            break;
        case 4: // 选择面
            context->Activate(AIS_Shape::SelectionMode(TopAbs_FACE));
            break;
        case 6: // 选择实体按钮代码
            context->Activate(AIS_Shape::SelectionMode(TopAbs_SOLID));
            break;
        default:
            break;
        }

}

};

#endif // BASICMODELING_H
