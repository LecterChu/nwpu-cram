/*
不鼓励内卷，不鼓励抄袭，不要照搬仓库里的实验作业，该上的课还是要好好上，该写的作业还是要好好写，该做的实验还是要好好做

* 以 make_point函数 的代码为例说明我遇到的部分问题和理解:
* 1. gp_Pnt 是 OCC 中表示三维点的类，它包含了点的 x、y 和 z 坐标。在 make_point 的代码中，gp_Pnt 类型用于表示三维空间中的点坐标。
* 2. Qt 是一个用于创建图形用户界面（GUI）的 C++ 库，而 gp_Pnt 是 OpenCascade 中的一个类，专门用于处理三维几何图形。
*    这两个库在这里结合使用，Qt 用于创建用户界面和处理交互，而 OpenCascade 用于处理三维几何图形的创建和显示。
* 3. OCC 的 BRepBuilderAPI_MakeVertex 对象也可以用于在三维空间中定义一个点 它和 gp_Pnt 类有一定的区别
*    - gp_Pnt: 这是 OCC 中表示点的类。它包含了一个点的三维坐标信息（x、y 和 z）。gp_Pnt 主要用于表示几何中的点位置，它是一个数学上的点。
*    - BRepBuilderAPI_MakeVertex: 这是 OCC 中用于创建点的类。它并不是用来表示点的坐标，而是用来在 OCC 中创建一个点的几何形状。
*    通过 BRepBuilderAPI_MakeVertex 类，可以将一个 gp_Pnt 对象或一组坐标作为输入，然后创建一个点的几何形状。
*    在make_point函数的代码中，gp_Pnt 用于表示点的坐标，而 BRepBuilderAPI_MakeVertex 用于使用这个坐标创建一个点的几何形状。
*    实际上，BRepBuilderAPI_MakeVertex 类在内部会使用 gp_Pnt 类型的坐标信息。
*/

#ifndef MODELMAKER_H
#define MODELMAKER_H

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRep_Builder.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <GC_MakeCircle.hxx>
#include <GC_MakeEllipse.hxx>
#include <GC_MakeSegment.hxx>
#include <gp_Circ.hxx>
#include <gp_Elips.hxx>
#include <AIS_Shape.hxx>
#include <Quantity_Color.hxx>

#include <QVector>

class ModelMaker
{
public:
    /*****************************************************x
     * static Handle(AIS_Shape) make_point(gp_Pnt point)
     * 输入：解析几何点 point
     * 输出：一个可交互顶点，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画点
     * ***************************************************/
    static Handle(AIS_Shape) make_point(gp_Pnt point) {

        // 使用BRepBuilderAPI_MakeVertex类创建点的几何形状
        BRepBuilderAPI_MakeVertex vertex(point);

        // 通过AIS_Shape类包装点的几何形状，以便在QT中显示和交互
        Handle(AIS_Shape) anAisPoint = new AIS_Shape(vertex.Vertex());

        // 返回可交互的点形状
        return anAisPoint;
    }

    /*****************************************************x
     * static Handle(AIS_Shape) make_line(gp_Pnt Pnt1, gp_Pnt Pnt2)
     * 输入：端点 Pnt1
     *      端点 Pnt2
     * 输出：一个可交互线段，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画线段
     * 1.取学号倒数第三位数字生成圆颜色：假设学号倒数第三位数字为3，则颜色为
     *   Quantity_Color(0.3, 0.3, 0.3, Quantity_TOC_RGB)
     * ***************************************************/
    static Handle(AIS_Shape) make_line(gp_Pnt Pnt1, gp_Pnt Pnt2) {

        // 使用 BRepBuilderAPI_MakeEdge 类创建线段的几何形状
        BRepBuilderAPI_MakeEdge edge(Pnt1, Pnt2);

        // 1.取学号倒数第三位数字生成线颜色 我的学号最后三位是959
        Quantity_Color lineColor(0.9, 0.9, 0.9, Quantity_TOC_RGB);

        // 通过 AIS_Shape 类包装线段的几何形状，以便在 Qt 中显示和交互
        Handle(AIS_Shape) anAisLine = new AIS_Shape(edge.Edge());
        // 设置好颜色
        anAisLine->SetColor(lineColor);

        // 返回可交互的线段形状
        return anAisLine;
    }

    /*****************************************************x
     * static Handle(AIS_Shape) make_circle(gp_Pnt p, Standard_Real r)
     * 输入：圆心点 p
     *      圆半径 r
     * 输出：一个可交互圆，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画圆
     * 1.2D绘图以z轴方向作为法向D，3D绘图取学号末尾三位数字作为坐标实体创建法向D，以点p和法向D创建坐标系，
     *   在此坐标系中创建圆，例：假设学号以123结尾，则坐标为（2, 1, 3）
     * 2.取学号倒数第二位数字生成圆颜色：假设学号倒数第二位数字为2，则颜色为
     *   Quantity_Color(0.2, 0.2, 0.2, Quantity_TOC_RGB)
     * ***************************************************/
    static Handle(AIS_Shape) make_circle(gp_Pnt p, Standard_Real r, Standard_Boolean is3D) {

        // 创建AIS_Shape指针
        Handle(AIS_Shape) anAisCircle;

        // 1.2D绘图以z轴方向作为法向D，我的学号后三位是959，3D绘图取(5,9,9)作为坐标实体创建法向D，以点p和法向D创建坐标系，在此坐标系中创建圆
        gp_Ax2 axis;
        if (is3D) {
            // 3D模式下，以点p和法向D(5, 9, 9)创建坐标系
            axis = gp_Ax2(p, gp_Dir(5, 9, 9), gp_Dir(1, 0, 0));
        } else {
            // 2D模式下，以点p创建坐标系，法向D为默认z轴方向
            axis = gp_Ax2(p, gp_Dir(0, 0, 1));
        }

        // 创建圆
        gp_Circ circle(axis, r);
        // 使用 BRepBuilderAPI_MakeEdge 类创建圆的几何形状
        TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle);

        // 创建AIS_Shape
        anAisCircle = new AIS_Shape(edge);

        // 2.我的学号后三位是959 取圆颜色为Quantity_Color(0.5, 0.5, 0.5, Quantity_TOC_RGB)
        anAisCircle->SetColor(Quantity_Color(0.5, 0.5, 0.5, Quantity_TOC_RGB));

        return anAisCircle;
    }

    /*****************************************************x
     * static Handle(AIS_Shape) make_elips(gp_Pnt p, Standard_Real r1)
     * 输入：椭圆中心点 p
     *      椭圆长半径 r1
     * 输出：一个可交互椭圆，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画椭圆
     * 1.取学号末位数字a计算椭圆短体半径 r2 = r1 / (a / 5 + 1.5)
     * 2.2D绘图以z轴方向作为法向D，3D绘图取学号末尾三位数字作为坐标实体从而创建法向D，以点p和法向D创建坐标系，
     *   在此坐标系中创建椭圆，例：假设学号以123结尾，则坐标为（2, 3, 1）
     * 3.取学号末尾位数字生成椭圆颜色：假设学号末尾位数字为3，则颜色为
     *   Quantity_Color(0.3, 0.3, 0.3, Quantity_TOC_RGB)
     * ***************************************************/
    static Handle(AIS_Shape) make_elips(gp_Pnt p, Standard_Real r1, Standard_Boolean is3D) {

        // 我的学号最后三位是959 后续会根据这一信息设置相关参数

        // 创建用于存储可交互对象的AIS_Shape指针
        Handle(AIS_Shape) anAisEllipse;

        // 1.取椭圆短体半径 r2 = r1 / 3.3    ( 9 / 5 + 1.5 = 3.3 )
        Standard_Real r2 = r1 / 3.3;

        // 2.2D绘图以z轴方向作为法向D，3D绘图取（5, 9, 9）作为坐标实体从而创建法向D，
        // 以点p和法向D创建坐标系，在此坐标系中创建椭圆
        gp_Ax2 axis;
        if (is3D) {
            // 如果是3D绘图，则取（5, 9, 9）作为法向D，以点p和法向D创建坐标系
            axis = gp_Ax2(p, gp_Dir(5, 9, 9), gp_Dir(1, 0, 0));
        } else {
            // 如果是2D绘图，则以点p创建坐标系，法向默认为z轴方向
            axis = gp_Ax2(p, gp_Dir(0, 0, 1));
        }

        // 创建椭圆
        gp_Elips ellipse(axis, r1, r2);

        // 使用BRepBuilderAPI_MakeEdge类创建椭圆的边缘
        TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(ellipse);

        // 创建AIS_Shape，AIS_Shape是OpenCASCADE中用于交互式显示的对象
        anAisEllipse = new AIS_Shape(edge);

        // 3.取椭圆颜色为Quantity_Color(0.9, 0.9, 0.9, Quantity_TOC_RGB)
        // 设置AIS_Shape的颜色，Quantity_Color表示颜色，RGB(0.9, 0.9, 0.9)为浅灰色
        anAisEllipse->SetColor(Quantity_Color(0.9, 0.9, 0.9, Quantity_TOC_RGB));

        // 返回创建的AIS_Shape
        return anAisEllipse;
    }

    /*****************************************************x
     * static Handle(AIS_Shape) make_BSpline(Handle(TColgp_HArray1OfPnt) aPoints)
     * 输入：控制点数组 Handle(TColgp_HArray1OfPnt) aPoints
     * 输出：一个可交互B样条，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画B样条曲线
     * 1.取学号末尾三位数字生成B样条颜色：假设学号以123结尾，则颜色为
     *   Quantity_Color(0.2, 0.1, 0.3, Quantity_TOC_RGB)
     * ***************************************************/
    static Handle(AIS_Shape) make_BSpline(QVector<gp_Pnt> aPoints) {

        // 我的学号最后三位是959 后续会根据这一信息设置相关参数

        // 创建用于存储可交互对象的AIS_Shape指针
        Handle(AIS_Shape) anAisBSpline;

        // 调用OCC类和方法，实现画B样条曲线

        // 1.取B样条颜色为Quantity_Color(0.5, 0.9, 0.9, Quantity_TOC_RGB)
        Quantity_Color color(0.5, 0.9, 0.9, Quantity_TOC_RGB);

        // 构建TColgp_Array1OfPnt，用于传递控制点
        TColgp_Array1OfPnt controlPoints(1, aPoints.size());
        for (int i = 1; i <= aPoints.size(); ++i) {
            controlPoints.SetValue(i, aPoints.at(i - 1));
        }

        // 使用GeomAPI_PointsToBSpline创建B样条曲线
        GeomAPI_PointsToBSpline bsplineAlgorithm(controlPoints);

        // 获取生成的B样条曲线
        Handle(Geom_BSplineCurve) bsplineCurve = bsplineAlgorithm.Curve();

        // 判断曲线是否有效
        if (!bsplineCurve.IsNull()) {
            // 使用BRepBuilderAPI_MakeEdge类创建B样条曲线的边缘
            TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(bsplineCurve);

            // 创建AIS_Shape，AIS_Shape是OpenCASCADE中用于交互式显示的对象
            anAisBSpline = new AIS_Shape(edge);

            // 设置AIS_Shape的颜色
            anAisBSpline->SetColor(color);
        }

        // 返回创建的AIS_Shape
        return anAisBSpline;
    }

    /*****************************************************x
     * static Handle(AIS_Shape) make_box(gp_Pnt Pnt1, gp_Pnt Pnt2)
     * 输入：长方体顶点 Pnt1
     *      Pnt1 对角顶点 Pnt2
     * 输出：一个可交互长方体，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画长方体
     * 1.取学号末尾三位数字生成长方体颜色：假设学号以123结尾，则颜色为
     *   Quantity_Color(0.2, 0.3, 0.1, Quantity_TOC_RGB)
     * ***************************************************/
    static Handle(AIS_Shape) make_box(gp_Pnt Pnt1, gp_Pnt Pnt2){

        // 我的学号最后三位是959 后续会根据这一信息设置相关参数

        // 使用 BRepPrimAPI_MakeBox 类创建长方体的几何形状
        BRepPrimAPI_MakeBox makeBox(Pnt1, Pnt2);

        // 取学号末尾三位数字生成长方体的颜色
        Quantity_Color boxColor(0.5, 0.9, 0.9, Quantity_TOC_RGB);

        // 通过 AIS_Shape 类包装长方体的几何形状，以便在 Qt 中显示和交互
        Handle(AIS_Shape) anAisBox = new AIS_Shape(makeBox.Shape());
        // 设置颜色
        anAisBox->SetColor(boxColor);

        // 返回可交互的长方体形状
        return anAisBox;
    }

    /*****************************************************x
     * static Handle(AIS_Shape) make_cylinder(gp_Pnt p, Standard_Real H)
     * 输入：圆柱体地面中心点 p
     *      圆柱体高 H
     * 输出：一个可交互圆柱体，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画圆柱体
     * 1.取学号末位数字a计算圆柱体地面半径 R = H / (a + 1)
     * 2.取学号末尾三位数字作为坐标实体从而创建方向D，以点p和方向D创建坐标系，
     *   在此坐标系中创建圆柱体，例：假设学号以123结尾，则坐标为（3, 2, 1）
     * 3.取学号末尾三位数字生成圆柱体颜色：假设学号以123结尾，则颜色为
     *   Quantity_Color(0.3, 0.2, 0.1, Quantity_TOC_RGB)
     * ***************************************************/
    static Handle(AIS_Shape) make_cylinder(gp_Pnt p, Standard_Real H) {
        // 我的学号最后三位是959 后续会根据这一信息设置相关参数

        // 创建用于存储可交互对象的AIS_Shape指针
        Handle(AIS_Shape) anAisCylinder;

        // 1.取圆柱体地面半径 R = H / 10
        Standard_Real R = H / 10.0;

        // 2.取（9, 5, 9）从而创建方向D，以点p和方向D创建坐标系，在此坐标系中创建圆柱体

        // 创建圆柱体的坐标轴，以center为原点，方向D为(9, 5, 9)
        gp_Ax2 axis(p, gp_Dir(9, 5, 9));

        // 使用BRepPrimAPI_MakeCylinder类创建圆柱体
        BRepPrimAPI_MakeCylinder cylinderBuilder(axis, R, H);

        // 获取创建的圆柱体
        TopoDS_Shape cylinder = cylinderBuilder.Shape();

        // 判断圆柱体是否有效
        if (!cylinder.IsNull()) {
            // 创建AIS_Shape，AIS_Shape是OpenCASCADE中用于交互式显示的对象
            anAisCylinder = new AIS_Shape(cylinder);

            // 3.取圆柱体颜色为Quantity_Color(0.9, 0.5, 0.9, Quantity_TOC_RGB)

            // 设置AIS_Shape的颜色，Quantity_Color表示颜色，RGB(0.9, 0.5, 0.9)为紫色
            anAisCylinder->SetColor(Quantity_Color(0.9, 0.5, 0.9, Quantity_TOC_RGB));
        }

        // 返回创建的AIS_Shape
        return anAisCylinder;
    }

    /*****************************************************x
     * static Handle(AIS_Shape) make_cone(gp_Pnt p, Standard_Real R)
     * 输入：圆锥体地面中心点 p
     *      圆锥体地面半径 R
     * 输出：一个可交互圆锥体，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画圆锥体
     * 1.取学号末位数字a计算圆锥体高度 H = R1 - a
     * 原作业要求圆锥体高度H＝R1-a，现改成H = R1/(a+1)，保证H为正值
     * 2.取学号末尾三位数字作为坐标实体从而创建方向D，以点p和方向D创建坐标系，
     *   在此坐标系中创建圆锥体，例：假设学号以123结尾，则坐标为（3, 1, 2）
     * 3.取学号末尾三位数字生成圆锥体颜色，例：假设学号以123结尾，则颜色为
     *   Quantity_Color(0.3, 0.1, 0.2, Quantity_TOC_RGB)
     * ***************************************************/
    static Handle(AIS_Shape) make_cone(gp_Pnt p, Standard_Real R) {

        // 我的学号最后三位是959 后续会根据这一信息设置相关参数

        // 创建用于存储可交互对象的AIS_Shape指针
        Handle(AIS_Shape) anAisCone;

        // 调用OCC类和方法，实现画圆锥体

        // 1.取圆锥体高度 H = R1 - 9 这里要判断一下需要为正 否则会abort
        // Standard_Real H = R - 9 > 0 ? R - 9 : 1;
        // 原作业要求圆锥体高度H＝R1-a，现改成H = R1/10，保证H为正值
        Standard_Real H = R / 10;

        // 2.取（9, 9, 5）作为坐标实体从而创建方向D，以点p和方向D创建坐标系，在此坐标系中创建圆锥体

        // 创建圆锥体的坐标轴，以center为原点，方向D为(9, 9, 5)
        gp_Ax2 axis(p, gp_Dir(9, 9, 5));

        // 使用BRepPrimAPI_MakeCone类创建圆锥体
        BRepPrimAPI_MakeCone coneBuilder(axis, R, 0, H);

        // 获取创建的圆锥体
        TopoDS_Shape cone = coneBuilder.Shape();

        // 判断圆锥体是否有效
        if (!cone.IsNull()) {
            // 创建AIS_Shape，AIS_Shape是OpenCASCADE中用于交互式显示的对象
            anAisCone = new AIS_Shape(cone);

            // 3.取圆锥体颜色为Quantity_Color(0.9, 0.9, 0.5, Quantity_TOC_RGB)

            // 设置AIS_Shape的颜色，Quantity_Color表示颜色，RGB(0.9, 0.9, 0.5)为黄色
            anAisCone->SetColor(Quantity_Color(0.9, 0.9, 0.5, Quantity_TOC_RGB));
        }

        // 返回创建的AIS_Shape
        return anAisCone;
    }

    /*****************************************************x
     * static Handle(AIS_Shape) make_sphere(gp_Pnt center, Standard_Real R)
     * 输入：球体中心点 center
     *      球体半径 R
     * 输出：一个可交互球体，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画球体
     * 1.取学号末尾三位数字生成球体颜色：假设学号以123结尾，则颜色为
     *   Quantity_Color(0.1, 0.3, 0.2, Quantity_TOC_RGB)
     * ***************************************************/
    static Handle(AIS_Shape) make_sphere(gp_Pnt center, Standard_Real R) {

        // 我的学号最后三位是959 后续会根据这一信息设置相关参数

        // 创建用于存储可交互对象的AIS_Shape指针
        Handle(AIS_Shape) anAisSphere;

        // 1.取球体颜色为Quantity_Color(0.9, 0.9, 0.5, Quantity_TOC_RGB)
        Quantity_Color color(0.9, 0.9, 0.5, Quantity_TOC_RGB);

        // 使用BRepPrimAPI_MakeSphere类创建球体
        BRepPrimAPI_MakeSphere sphereBuilder(center, R);

        // 获取创建的球体
        TopoDS_Shape sphere = sphereBuilder.Shape();

        // 判断球体是否有效
        if (!sphere.IsNull()) {
            // 创建AIS_Shape，AIS_Shape是OpenCASCADE中用于交互式显示的对象
            anAisSphere = new AIS_Shape(sphere);

            // 设置AIS_Shape的颜色
            anAisSphere->SetColor(color);
        }

        // 返回创建的AIS_Shape
        return anAisSphere;
    }

    /*****************************************************x
     * static Handle(AIS_Shape) make_torus(gp_Pnt center, Standard_Real R1)
     * 输入：圆环体中心点 center
     *      圆环体中心环半径 R1
     * 输出：一个可交互圆环体，类型为 AIS_Shape
     *
     * TODO: 调用OCC类和方法，实现画圆环体
     * 1.取学号末位数字a计算圆环体截面半径 R2 = R1 / (a + 1)
     * 2.取学号末尾三位数字作为坐标实体从而创建方向D，以点p和方向D创建坐标系，
     *   在此坐标系中创建圆环体，例：假设学号以123结尾，则坐标为（1, 2, 3）
     * 3.取学号末尾三位数字生成圆环体颜色：假设学号以123结尾，则颜色为
     *   Quantity_Color(0.1, 0.2, 0.3, Quantity_TOC_RGB)
     * ***************************************************/
    static Handle(AIS_Shape) make_torus(gp_Pnt center, Standard_Real R1) {

        // 我的学号最后三位是959 后续会根据这一信息设置相关参数

        // 创建用于存储可交互对象的AIS_Shape指针
        Handle(AIS_Shape) anAisTorus;

        // 调用OCC类和方法，实现画圆环体

        // 1.取圆环体截面半径 R2 = R1 / 10
        Standard_Real R2 = R1 / 10.0;

        // 2.取（9, 5, 9）作为坐标实体从而创建方向D，以点p和方向D创建坐标系，在此坐标系中创建圆环体

        // 创建圆环体的坐标轴，以center为原点，方向D为(9, 5, 9)
        gp_Ax2 axis(center, gp_Dir(9, 5, 9));

        // 使用BRepPrimAPI_MakeTorus类创建圆环体
        BRepPrimAPI_MakeTorus torusBuilder(axis, R1, R2);

        // 获取创建的圆环体
        TopoDS_Shape torus = torusBuilder.Shape();

        // 判断圆环体是否有效
        if (!torus.IsNull()) {
            // 创建AIS_Shape，AIS_Shape是OpenCASCADE中用于交互式显示的对象
            anAisTorus = new AIS_Shape(torus);

            // 3.取圆环体颜色为Quantity_Color(0.9, 0.5, 0.9, Quantity_TOC_RGB)
            // 设置AIS_Shape的颜色，Quantity_Color表示颜色，RGB(0.9, 0.5, 0.9)为紫色
            anAisTorus->SetColor(Quantity_Color(0.9, 0.5, 0.9, Quantity_TOC_RGB));
        }

        // 返回创建的AIS_Shape
        return anAisTorus;
    }
};

#endif // MODELMAKER_H
