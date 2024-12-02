/*
不鼓励内卷，不鼓励抄袭，不要照搬仓库里的实验作业，该上的课还是要好好上，该写的作业还是要好好写，该做的实验还是要好好做
 * 自定义建模大作业:比萨斜塔
*/

#ifndef MYCREATION_H
#define MYCREATION_H

#define MYDEBUG qDebug()<<__LINE__;
#define PI 3.14

#include "OccWidget.h"
#include "ModelMaker.hpp"
#include "AdvanceModeling.hpp"
#include "BasicModeling.hpp"
#include "ModelMaker.hpp"
#include <GeomAPI_ExtremaCurveCurve.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <GCE2d_MakeSegment.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepLib.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <Font_SystemFont.hxx>
#include <Font_FontMgr.hxx>
#include <Font_FontAspect.hxx>

class MyCreation
{
public:

    /*
     * 比萨斜塔及小球自由落体
     * 实现大致思路如下:
     * 1.先构建第一层塔体(实现思路见layerModel这个函数)
     * 2.对第一层塔体缩放并移动3次得到一个4层的塔体
     * 3.在最高层边沿设置一个点作为小球的释放点
     * 4.将塔体和释放点沿y轴旋转18度左右实现斜塔效果
     * 5.在底层做一个比较扁的长方体作为地面，让底层和这个长方体做并运算实现斜塔的地沉效果
     * 6.让小球释放点投影到地面得到一条自由落体轨迹
     * 7.对轨迹进行离散化，得到经过释放后到达地面这段时间内，经过等间隔时间小球位置的对应点集(实现方法见disperse这个函数)
     * 8.在上一步得到点的位置画出小球
     * 9.将以上的构成部分加入需要返回的复合图形中
    */
    static TopoDS_Shape MyDesign()
    {
        TopoDS_Compound aRes;

        // 构建复合形状
        BRep_Builder aBuilder;
        aBuilder.MakeCompound(aRes);

        // 构建第一层
        TopoDS_Shape layer0=layerModel();
        // 对第一层进行缩放和移动得到第二层
        // 缩放倍数为0.9 移动距离为之前层的高度
        TopoDS_Shape layer1=translate(scale(layer0,0.9),20);
        // 同理得到第三层
        TopoDS_Shape layer2=translate(scale(layer1,0.9),20*0.9);
        // 同理得到第4层
        TopoDS_Shape layer3=translate(scale(layer2,0.9),20*0.9*0.9);

        // 被投影点的高度是65 距离中心点距离为8.25
        BRepBuilderAPI_MakeVertex vertex(gp_Pnt(8.25,0,65));
        TopoDS_Shape point=vertex.Vertex();

        // 做4层足够了 沿y轴进行旋转18度变成斜的
        Standard_Real rotate_rad=PI/20.0;
        layer0=rotate(layer0,gp_Vec(0,1,0),rotate_rad);
        layer1=rotate(layer1,gp_Vec(0,1,0),rotate_rad);
        layer2=rotate(layer2,gp_Vec(0,1,0),rotate_rad);
        layer3=rotate(layer3,gp_Vec(0,1,0),rotate_rad);
        point=rotate(point,gp_Vec(0,1,0),rotate_rad);

        // 旋转后底层的最高点大概是1.55
        // 做一个简单的地面
        gp_Pnt Pnt1=gp_Pnt(-30,-30,-1.55);
        gp_Pnt Pnt2=gp_Pnt(30,30,1.55);
        BRepPrimAPI_MakeBox makeBox(Pnt1, Pnt2);
        TopoDS_Shape layer_box=makeBox.Shape();

        // 让底层嵌入地面
        layer0=Fuse(layer0,layer_box);

        // 创建一个无限的面作为投影面
        gp_Pln pln = gp_Pln(gp_Pnt(0,0,1.55),gp_Dir(0,0,1));
        BRepBuilderAPI_MakeFace layer_face (pln);
        TopoDS_Shape ground=layer_face.Shape();

        // 进行投影
        BRepBuilderAPI_MakeVertex projection_MakeVertex(project2_face(point,ground));
        TopoDS_Shape projection_point=projection_MakeVertex.Shape();

        // 创建线段的几何形状
        BRepBuilderAPI_MakeEdge edge(BRep_Tool::Pnt(TopoDS::Vertex(projection_point)), BRep_Tool::Pnt(TopoDS::Vertex(point)));
        TopoDS_Shape anAisLine = edge.Edge();

        // 以自由落体规则离散化这条边
        QVector <gp_Pnt> pnts=disperse(anAisLine);
        // 使用离散化后的点画小球
        for(gp_Pnt p:pnts){
            // 使用BRepPrimAPI_MakeSphere类创建球体 半径为0.5
            BRepPrimAPI_MakeSphere sphereBuilder(p, 0.5);
            TopoDS_Shape sphere = sphereBuilder.Shape();

            // 添加到复合形状中(小球自由落体位置)
            aBuilder.Add(aRes,sphere);
        }

        // 添加到复合形状中(塔体、释放点、轨迹线)
        aBuilder.Add(aRes,layer0);
        aBuilder.Add(aRes,layer1);
        aBuilder.Add(aRes,layer2);
        aBuilder.Add(aRes,layer3);
        aBuilder.Add(aRes,point);
        aBuilder.Add(aRes,edge);

        return aRes;
    }

    /*
     * 构建第一层的过程
     * 大致思路如下:
     * 1.先做一个圆柱体作为框架
     * 2.对圆柱体进行倒角 这里只要倒角上面的边 会比较美观
     * 3.给圆柱体的上面部分加两个圆环作为装饰
     * 4.在两个圆环之间加入一些圆柱形突出装饰
     * 5.用圆柱体和长方体并运算为一个拱门 并复制为一周共8个
     * 6.为了拱门比较平滑 需要对拱门进行圆角操作
     * 7.在塔体上减去这些拱门 相当于开了拱门
    */
    static TopoDS_Shape layerModel(){

        /**********作塔体**********/

        // 取圆柱体地面半径 R = 10 高度 H = 20
        Standard_Real R = 10;
        Standard_Real H = 20;

        // 创建圆柱体的坐标轴，以(0, 0, 0)为原点，方向D为(0, 0, 1)
        gp_Ax2 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));

        // 使用BRepPrimAPI_MakeCylinder类创建圆柱体
        BRepPrimAPI_MakeCylinder cylinderBuilder(axis, R, H);
        TopoDS_Shape aCylinder = cylinderBuilder.Shape();
        // 对圆柱体进行倒角 这里只要倒角一条边就可以了 比较美观
        TopoDS_Shape aCylinder_chamfer = chamfer(aCylinder,0.5);


        /**********上半部分的装饰**********/

        // 取圆环体中心环半径 R1 = 10 截面半径 R2 = 0.25
        Standard_Real torus_R1 = 10;
        Standard_Real torus_R2 = 0.25;

        // 使用BRepPrimAPI_MakeTorus类创建圆环体
        // 在(0, 0, 18)的高度位置 方向朝上
        BRepPrimAPI_MakeTorus torusBuilder(gp_Ax2(gp_Pnt(0, 0, 18), gp_Dir(0, 0, 1)), torus_R1, torus_R2);

        // 获取创建的圆环体 复制两份 一份向下移动到14高度的位置
        TopoDS_Shape torus1 = torusBuilder.Shape();
        TopoDS_Shape torus2 = translate(torus1, -4);

        // 将圆环体与倒角后的圆柱并运算 可以得到有环花纹的圆柱体
        TopoDS_Shape layer_torus1 = Fuse(aCylinder_chamfer, torus1);
        TopoDS_Shape layer_torus2 = Fuse(layer_torus1, torus2);

        // 构建小的圆柱体作为两环间的浮雕
        // 距离原点水平距离为10 半径为1 高度为0.5 方向朝外
        gp_Ax2 axis_small(gp_Pnt(10, 0, 0), gp_Dir(1, 0, 0));
        BRepPrimAPI_MakeCylinder cylinderBuilder_small(axis_small, 1, 0.5);
        TopoDS_Shape cylinder_small = cylinderBuilder_small.Shape();
        // 将小圆柱体移动到高度16的位置
        cylinder_small=translate(cylinder_small,16);

        // 进行pi/8度的旋转 此旋转是为了和之后的拱门装饰错开 达到一个相间的效果
        cylinder_small=rotate(cylinder_small, gp_Vec(0,0,1), PI/8);
        // 旋转复制8次 这样每 2*PI/8 的弧度就有一个小圆柱体
        TopoDS_Shape cylinder_smalls = rotate_copy(cylinder_small, 8);

        // 作并运算后上半部分完成
        TopoDS_Shape layer_up_finish = Fuse(cylinder_smalls, layer_torus2);


        /**********准备做下半部分的拱门效果**********/

        // 做长方体 长4 宽2 高10 Pnt1这里-0.2是为了后续圆角多出来的一部分被减去
        gp_Pnt Pnt1=gp_Pnt(-2,-8,-0.2);
        gp_Pnt Pnt2=gp_Pnt(2,-10,10);
        BRepPrimAPI_MakeBox makeBox(Pnt1, Pnt2);
        TopoDS_Shape box=makeBox.Shape();

        // 构建小的圆柱体 高度为10 距离原点水平距离为10 半径为2 高度为2
        gp_Ax2 axis_semi(gp_Pnt(0, -10, 0), gp_Dir(0, 1, 0));
        BRepPrimAPI_MakeCylinder cylinderBuilder_semi(axis_semi, 2, 2);
        TopoDS_Shape cylinder_semi = cylinderBuilder_semi.Shape();
        // 移动到高度10的位置
        cylinder_semi=translate(cylinder_semi,10);

        // 圆柱体和长方体并运算放一起 得到一个类似拱门的东西
        TopoDS_Shape cylinder_box=Fuse(cylinder_semi,box);
        // 进行圆角 参数为0.2 太大效果不好
        TopoDS_Shape cylinder_box_fillet=fillet(cylinder_box,0.2);
        // 旋转复制8次
        TopoDS_Shape cylinder_boxs=rotate_copy(cylinder_box_fillet,8);

        // 在原有的基础图形上对拱门作差 得到完整的一层的图形
        TopoDS_Shape layer_final=Cut(layer_up_finish,cylinder_boxs);

        // 返回结果
        return layer_final;
    }

    /*
     * 向z方向平移 r 的值
     * 可以参考AdvanceModeling.hpp
    */
    static TopoDS_Shape translate(TopoDS_Shape shape,Standard_Real r) {

        // 定义平移向量
        gp_Vec translationVector(0,0,r);

        // 创建平移变换
        gp_Trsf translationTransformation;

        // 设置平移量
        translationTransformation.SetTranslation(translationVector);

        // 应用平移变换到拓扑体
        TopLoc_Location location(translationTransformation);
        shape.Move(location);

        // 返回平移后的结果
        return shape;
    }

    /*
     * 以原点作为缩放点进行缩放 times 倍
     * 可以参考AdvanceModeling.hpp
    */
    static TopoDS_Shape scale(TopoDS_Shape shape,Standard_Real times) {

        // 定义缩放的中心点
        gp_Pnt scaleCenterPoint(0, 0, 0);

        // 创建缩放变换
        gp_Trsf scaleTransformation;
        // 在原点进行缩放
        scaleTransformation.SetScale(scaleCenterPoint, times);

        // 应用缩放变换到拓扑体
        TopLoc_Location location(scaleTransformation);
        shape.Move(location);

        // 返回缩放后的结果
        return shape;
    }

    /*
     * 在原点沿指定方向v旋转rad
     * 可以参考AdvanceModeling.hpp
    */
    static TopoDS_Shape rotate(TopoDS_Shape shape,gp_Vec v,Standard_Real rad) {

        // 创建旋转轴
        gp_Ax1 rotationAxis(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(v));

        // 创建旋转变换
        gp_Trsf rotationTransformation;

        // 旋转角度为rad
        rotationTransformation.SetRotation(rotationAxis, rad);

        // 应用旋转变换到拓扑体
        TopLoc_Location location(rotationTransformation);
        shape.Move(location);

        // 返回旋转后的结果
        return shape;
    }

    /*
     * 对拓扑体进行倒角 但只对第一条边进行倒角
     * 可以参考AdvanceModeling.hpp
    */
    static TopoDS_Shape chamfer(TopoDS_Shape shape,Standard_Real rad) {
        // 创建倒角算法对象 与倒角算法对象类似
        BRepFilletAPI_MakeChamfer chamferOperation(shape);

        // 使用TopExp_Explorer来遍历拓扑体的边
        for (TopExp_Explorer exp(shape, TopAbs_EDGE); exp.More(); exp.Next())
        {
            chamferOperation.Add(rad,TopoDS::Edge(exp.Current()));
            // 只对第一条边进行倒角
            break;
        }

        // 构建倒角结果
        chamferOperation.Build();
        if (!chamferOperation.IsDone()) return TopoDS_Shape();

        // 返回倒角结果
        return chamferOperation.Shape();
    }

    /*
     * 对拓扑体进行圆角
     * 可以参考AdvanceModeling.hpp
    */
    static TopoDS_Shape fillet(TopoDS_Shape shape,Standard_Real rad) {

        // 创建圆角算法对象 与倒角算法对象类似
        BRepFilletAPI_MakeFillet filletOperation(shape);


        // 使用TopExp_Explorer来遍历拓扑体的边
        for (TopExp_Explorer exp(shape, TopAbs_EDGE); exp.More(); exp.Next())
        {
            filletOperation.Add(rad,TopoDS::Edge(exp.Current()));
        }
        // 构建圆角结果
        filletOperation.Build();

        // 返回圆角结果
        return filletOperation.Shape();
    }

    /*
     * 旋转复制
     * 即将一个TopoDS_Shape沿z轴进行旋转并复制times次
    */
    static TopoDS_Shape rotate_copy(TopoDS_Shape shape, Standard_Real times){
        TopoDS_Shape result = shape;

        Standard_Real angle = 2 * PI / times;
        // 定义旋转轴的方向向量
        gp_Vec rotationAxisVector(0, 0, 1.0);

        // 创建旋转轴
        gp_Ax1 rotationAxis(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(rotationAxisVector));

        // 创建旋转变换
        gp_Trsf rotationTransformation;

        // 每次旋转角度为angle
        rotationTransformation.SetRotation(rotationAxis, angle);

        // 应用旋转变换到拓扑体
        TopLoc_Location location(rotationTransformation);

        // 将每次旋转的结果加入result
        for(int i = 1; i < times; i++){
            shape.Move(location);
            result=Fuse(shape, result);
        }

        return result;
    }


    /*
     * 进行并运算
     * 可以参考AdvanceModeling.hpp
    */
    static TopoDS_Shape Fuse(TopoDS_Shape shape1,TopoDS_Shape shape2){
        BRepAlgoAPI_Fuse boolOperation(shape1, shape2);

        // 构建并运算结果
        boolOperation.Build();

        return boolOperation.Shape();
    }


    /*
     * 进行差运算
     * 可以参考AdvanceModeling.hpp
    */
    static TopoDS_Shape Cut(TopoDS_Shape shape1,TopoDS_Shape shape2){
        BRepAlgoAPI_Cut boolOperation(shape1, shape2);

        // 构建差运算结果
        boolOperation.Build();

        return boolOperation.Shape();
    }


    /*
     * 点到面的投影
     * 可以参考BasicModeling.hpp
    */
    static gp_Pnt project2_face(TopoDS_Shape shape1, TopoDS_Shape shape2) {

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
                return projectPoint.NearestPoint();
            }
        } else if (shape2.ShapeType() == TopAbs_VERTEX && shape1.ShapeType() == TopAbs_FACE){
            // 交换shape1和shape2，调用同一个函数
            return project2_face(shape2,shape1);
        }

        return gp_Pnt();
    }

    /*
     * 按自由落体规则离散化点 返回12个点
     * 可以参考BasicModeling.hpp
     * 参考自由落体规则进行了一定的修改:
     *      1.如果总共设置n个点的离散化的点，可以将线段分为n^2个单位
     *      2.小球在第i个时间的位置应该是在i^2单位的位置，将这个点加入返回列表
    */
    static QVector <gp_Pnt> disperse(TopoDS_Shape shape) {
        QVector <gp_Pnt> points;

        // 判断拓扑形状是否为边
        if (shape.ShapeType() == TopAbs_EDGE) {
            // 将TopoDS_Shape强制转换为TopoDS_Edge
            TopoDS_Edge edge = TopoDS::Edge(shape);

            // 离散的点数
            Standard_Integer numPoints = 12;

            // 通过参数化曲线获取边参数取值范围
            Standard_Real uStart, uEnd;
            // BRep_Tool::Curve 通过输入的拓扑边 edge，获取其参数化曲线以及曲线的参数范围（起始和终止参数值）
            Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, uEnd, uStart);

            // 计算步长
            Standard_Real step = (uEnd - uStart) / (numPoints*numPoints);

            // 依照步长依次获取曲线上的点并放入数组中
            for (Standard_Integer i = 0; i <= numPoints; ++i) {
                Standard_Real u = uStart + i * i * step;
                // 通过参数u获取曲线上的点
                gp_Pnt point = curve->Value(u);
                points.push_back(point);
            }
        }

        return points;
    }
};

#endif // MYCREATION_H
