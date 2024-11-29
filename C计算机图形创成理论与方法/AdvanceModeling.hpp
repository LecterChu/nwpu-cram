/*
不鼓励内卷，不鼓励抄袭，不要照搬仓库里的实验作业，该上的课还是要好好上，该写的作业还是要好好写，该做的实验还是要好好做
 *
 * 本次作业我遇到的主要问题是 bool_operation 这个函数的第一个参数的值取值范围找不到
 * 刚开始是打算未实现的情况下使用qDebug输出看看的 然后发现没有输出(现在回顾了一下 应该是没有同时选中两个图形的原因)
 * 然后去找了调用关系
 * 发现DesignCommand3D.cpp中的void BoolDesignCommand::dealWithSelection()这个函数调用了
 * 但是我并没有找到调用时的取值范围 调用时使用的是一个成员变量boolType
 * 然后我再去mainwindow.cpp中找终于是发现了调用时 交运算是1 并运算是0 差运算是2
 *
 *
 * 另一个问题是static Handle(AIS_Shape) offset(TopoDS_Shape shape)中使用了BRepOffset_MakeOffset这个类
 * 当然这里也可以用BRepOffsetAPI_MakeOffsetShape类代替
 * 但是这两个类的第三个参数Tol
 * 在函数签名中只说明了是一个实数
 * 于是我去occ的官网 https://dev.opencascade.org/doc/refman/html/class_b_rep_offset_a_p_i___make_offset_shape.html 查了一下
 * 又查询了一些资料 发现这个应该是容差的意思
 * 而且推荐值是1e-6左右 试了一下 发现效果还行
 *
*/

#ifndef ADVANCEMODELING_H
#define ADVANCEMODELING_H

#include "ModelMaker.hpp"
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>

class AdvanceModeling
{
public:
    /*****************************************************
     * static Handle(AIS_Shape) bool_operation(int boolType, TopoDS_Shape shape1, TopoDS_Shape shape2)
     * 输入：int boolType 布尔算法类别
     *      TopoDS_Shape shape1 拓扑体
     *      TopoDS_Shape shape2 拓扑体
     *
     * TODO: 对两个拓扑体进行布尔运算。
     * 判断布尔运算类型，根据不同类型选用Fuse、Common、Cut布尔算法。
     * ***************************************************/
    static Handle(AIS_Shape) bool_operation(int boolType, TopoDS_Shape shape1, TopoDS_Shape shape2) {
    /*
    这个函数返回一个Handle(AIS_Shape)，即OpenCASCADE中用于管理显示对象的智能指针。函数的输入包括一个整数boolType表示布尔运算的类型，以及两个TopoDS_Shape对象，即待运算的两个拓扑体。

        1.boolType 的值对应关系在 mainwindow.cpp 中进行了定义，分别表示并运算（0）、交运算（1）、差运算（2）。

        2.在函数中通过 switch 语句根据传入的 boolType 来选择不同的布尔运算算法：
        对于并运算（boolType == 0），使用 BRepAlgoAPI_Fuse 类。
        对于交运算（boolType == 1），使用 BRepAlgoAPI_Common 类。
        对于差运算（boolType == 2），使用 BRepAlgoAPI_Cut 类。

        3.执行布尔运算：
        对选定的布尔运算算法对象（boolOperation）调用 Build 函数，以执行相应的布尔运算。
        判断运算是否成功，通过 IsDone() 函数。

        4.处理布尔运算结果：
        如果运算成功，创建一个新的 AIS_Shape 对象用于包装运算结果，该对象用于在OpenCASCADE中进行显示。
        返回结果：

        5.返回包装了布尔运算结果的 AIS_Shape 对象。
    */

    // boolType 的值对应关系需要到mainwindow.cpp中查看
    // 交运算是1 并运算是0 差运算是2
    Handle(AIS_Shape) anAisBoolShape;

    // 根据不同的布尔运算类型选择对应的算法
    switch (boolType) {
       case 0: // 并运算
       {
           // 使用并运算算法
            /*
            BRepAlgoAPI_Fuse 是 OpenCASCADE 中用于执行并运算的类。这类的构造函数接受两个参数，分别是两个拓扑体 (shape1 和 shape2)。
            通过调用构造函数，创建了一个 BRepAlgoAPI_Fuse 类型的对象 boolOperation，该对象内部封装了并运算的相关算法。
            */
           BRepAlgoAPI_Fuse boolOperation(shape1, shape2);

           // 构建并运算结果
           boolOperation.Build();

           // 判断并运算是否成功
           if (boolOperation.IsDone()) {
               // 创建新的 AIS_Shape 对象来包装并运算结果
               anAisBoolShape = new AIS_Shape(boolOperation.Shape());
           }
           break;
       }
       case 1: // 交运算
       {
           // 使用交运算算法
            /*
            BRepAlgoAPI_Common 是 OpenCASCADE 中用于执行交运算的类。这类的构造函数接受两个参数，分别是两个拓扑体 (shape1 和 shape2)。
            通过调用构造函数，创建了一个 BRepAlgoAPI_Common 类型的对象 boolOperation，该对象内部封装了交运算的相关算法。
            */
           BRepAlgoAPI_Common boolOperation(shape1, shape2);

           // 构建交运算结果
           boolOperation.Build();

           // 判断交运算是否成功
           if (boolOperation.IsDone()) {
               // 创建新的 AIS_Shape 对象来包装交运算结果
               anAisBoolShape = new AIS_Shape(boolOperation.Shape());
           }
           break;
       }
       case 2: // 差运算
       {
           // 使用差运算算法
            /*
            BRepAlgoAPI_Cut 是 OpenCASCADE 中用于执行差运算的类。这类的构造函数接受两个参数，分别是两个拓扑体 (shape1 和 shape2)。
            通过调用构造函数，创建了一个 BRepAlgoAPI_Cut 类型的对象 boolOperation，该对象内部封装了差运算的相关算法。
            */
           BRepAlgoAPI_Cut boolOperation(shape1, shape2);

           // 构建差运算结果
           boolOperation.Build();

           // 判断差运算是否成功
           if (boolOperation.IsDone()) {
               // 创建新的 AIS_Shape 对象来包装差运算结果
               anAisBoolShape = new AIS_Shape(boolOperation.Shape());
           }
           break;
       }
       default:
           // 处理未知的布尔运算类型
           break;
    }

       // 返回布尔运算结果
       return anAisBoolShape;
    }

    /*****************************************************
     * static Handle(AIS_Shape) chamfer(TopoDS_Shape shape)
     * 输入：TopoDS_Shape shape 拓扑体
     *
     * TODO: 对拓扑体进行倒角。
     * 搜索拓扑体的第三条边，并对其进行倒角处理。
     * ***************************************************/
    static Handle(AIS_Shape) chamfer(TopoDS_Shape shape) {

        /*
            这个函数返回一个 Handle(AIS_Shape)，即OpenCASCADE中用于管理显示对象的智能指针。函数的输入参数是一个 TopoDS_Shape 对象，表示待进行倒角操作的拓扑体。

            1.获取拓扑体的边：
            使用 TopExp_Explorer 遍历拓扑体的边，将它们存储在 TopTools_ListOfShape 类型的 edges 中。在这里，循环中的 i 计数器用于找到拓扑体的第三条边。

            2.判断是否存在边：
            检查是否成功找到拓扑体的第三条边，如果 edges 不为空，则继续进行倒角操作。

            3.创建倒角算法对象：
            使用 BRepFilletAPI_MakeChamfer 创建倒角算法对象 chamferOperation，并传入原始的拓扑体。

            4.添加倒角边并设置倒角距离：
            从 edges 中获取第一条边（即原拓扑体的第三条边），将其添加到倒角算法对象中，并设置倒角距离。

            5.构建倒角结果：
            调用 chamferOperation.Build(); 执行倒角操作。

            6.判断倒角是否成功：
            使用 chamferOperation.IsDone() 检查倒角是否成功完成。

            7.创建新的 AIS_Shape 对象来包装倒角结果：
            如果倒角成功，通过 new AIS_Shape(chamferOperation.Shape()) 创建一个新的 AIS_Shape 对象，用于包装倒角后的结果。

            8.返回倒角结果：
            返回包装了倒角结果的 AIS_Shape 对象。
        */
        Handle(AIS_Shape) anAisChamferShape;

        // 获取拓扑体的边
        TopTools_ListOfShape edges;

        // 使用TopExp_Explorer来遍历拓扑体的边 获取图形的第3条边
        /*
            TopExp_Explorer 是 OpenCASCADE 中的一个类，用于在拓扑结构中进行探索和遍历。
            具体来说，TopExp_Explorer 用于在给定的拓扑体中查找满足指定类型的子元素。

            参数说明：

            shape: 表示待遍历的拓扑体，即 TopoDS_Shape 对象。
            TopAbs_EDGE: 表示要查找的子元素的类型，这里是边。

            在后续的代码中，exp.More() 用于检查是否还有更多的边需要遍历。
            exp.Next() 用于将遍历指针移动到下一个边，以便下一次循环可以获取下一个边。
        */
        int i=1;
        for (TopExp_Explorer exp(shape, TopAbs_EDGE); exp.More(); exp.Next(),i++) {
            if(i == 3) edges.Append(TopoDS::Edge(exp.Current()));
        }

        // 判断是否存在边
        if (!edges.IsEmpty()) {
            // 获取第一条边 即原图形的第3条边
            TopoDS_Edge chamferEdge = TopoDS::Edge(edges.First());

            // 创建倒角算法对象
            /*
                BRepFilletAPI_MakeChamfer 是 OpenCASCADE 中用于进行倒角操作的类。
                该类提供了一组方法，允许用户在拓扑体的边上创建倒角。
                通过这个类，可以对拓扑体的边进行倒角，并最终得到一个新的拓扑体。

                参数说明：
                shape: 表示待进行倒角操作的拓扑体，即 TopoDS_Shape 对象。
                通过构造函数将待倒角的拓扑体传递给 BRepFilletAPI_MakeChamfer 对象。

                在后续的代码中，通过 chamferOperation.Add(50.0, chamferEdge); 添加要倒角的边，并设置倒角距离
                通过 chamferOperation.Build(); 执行倒角操作。
                最终，通过 chamferOperation.Shape() 获取倒角后的拓扑体。
            */
            BRepFilletAPI_MakeChamfer chamferOperation(shape);

            // 添加倒角边并设置倒角距离
            chamferOperation.Add(50.0, chamferEdge);  // 第一个参数为倒角距离，根据实际需求调整

            // 构建倒角结果
            chamferOperation.Build();

            // 判断倒角是否成功
            if (chamferOperation.IsDone()) {
                // 创建新的 AIS_Shape 对象来包装倒角结果
                anAisChamferShape = new AIS_Shape(chamferOperation.Shape());
            }
        }

        // 返回倒角结果
        return anAisChamferShape;
    }

    /*****************************************************
     * static Handle(AIS_Shape) fillet(TopoDS_Shape shape)
     * 输入：TopoDS_Shape shape 拓扑体
     *
     * TODO: 对拓扑体进行圆角。
     * 搜索拓扑体的第一条边，并对其进行圆角处理。
     * ***************************************************/
    static Handle(AIS_Shape) fillet(TopoDS_Shape shape) {

        /*
        这个函数返回一个 Handle(AIS_Shape)，即OpenCASCADE中用于管理显示对象的智能指针。
        函数的输入参数是一个 TopoDS_Shape 对象，表示待进行圆角操作的拓扑体。

            1.获取拓扑体的边：
            使用 TopExp_Explorer 遍历拓扑体的边，将它们存储在 TopTools_ListOfShape 类型的 edges 中。

            2.判断是否存在边：
            检查是否成功找到拓扑体的边，如果 edges 不为空，则继续进行圆角操作。

            3.创建圆角算法对象：
            使用 BRepFilletAPI_MakeFillet 创建圆角算法对象 filletOperation，并传入原始的拓扑体。

            4.添加圆角边并设置圆角半径：
            从 edges 中获取第一条边，将其添加到圆角算法对象中，并设置圆角半径。

            5.构建圆角结果：
            调用 filletOperation.Build(); 执行圆角操作。

            6.判断圆角是否成功：
            使用 filletOperation.IsDone() 检查圆角是否成功完成。

            7.创建新的 AIS_Shape 对象来包装圆角结果：
            如果圆角成功，通过 new AIS_Shape(filletOperation.Shape()) 创建一个新的 AIS_Shape 对象，用于包装圆角后的结果。

            8.返回圆角结果：
            返回包装了圆角结果的 AIS_Shape 对象。
        */
        Handle(AIS_Shape) anAisFilletShape;

        // 获取拓扑体的边
        TopTools_ListOfShape edges;

        // 使用TopExp_Explorer来遍历拓扑体的边
        for (TopExp_Explorer exp(shape, TopAbs_EDGE); exp.More(); exp.Next())
        {
            edges.Append(TopoDS::Edge(exp.Current()));
        }

        // 判断是否存在边
        if (!edges.IsEmpty())
        {
            // 获取第一条边
            TopoDS_Edge filletEdge = TopoDS::Edge(edges.First());

            // 创建圆角算法对象 与倒角算法对象类似
            BRepFilletAPI_MakeFillet filletOperation(shape);

            // 添加圆角边并设置圆角半径
            filletOperation.Add(100.0,filletEdge); // 第二个参数为圆角半径，根据实际需求调整

            // 构建圆角结果
            filletOperation.Build();

            // 判断圆角是否成功
            if (filletOperation.IsDone())
            {
                // 创建新的 AIS_Shape 对象来包装圆角结果
                anAisFilletShape = new AIS_Shape(filletOperation.Shape());
            }
        }

        // 返回圆角结果
        return anAisFilletShape;
    }

    /*****************************************************
     * static Handle(AIS_Shape) translate(TopoDS_Shape shape)
     * 输入：TopoDS_Shape shape 任意拓扑图形
     *
     * TODO: 对所选图形进行移动。
     * 取学号后三位作为x坐标创建向量。
     * 用该向量设置平移变换
     * ***************************************************/
    static Handle(AIS_Shape) translate(TopoDS_Shape shape) {
        /*
        这个函数返回一个 Handle(AIS_Shape)，即OpenCASCADE中用于管理显示对象的智能指针。函数的输入参数是一个 TopoDS_Shape 对象，表示待进行平移操作的拓扑体。

            1.定义平移向量：
            创建一个 gp_Vec 对象 translationVector，表示平移的向量。在这里，向量的 x 坐标被设置为 959。（学号后三位）

            2.创建平移变换：
            使用 gp_Trsf 类创建一个平移变换 translationTransformation，并通过 SetTranslation 方法将平移向量设置到这个变换中。

            3.应用平移变换到拓扑体：
            创建一个 TopLoc_Location 对象 location，将平移变换设置到这个位置。然后，通过 shape.Move(location); 将平移变换应用到拓扑体上。

            4.创建新的 AIS_Shape 对象来包装平移后的结果：
            通过 new AIS_Shape(shape); 创建一个新的 AIS_Shape 对象，用于包装平移后的拓扑体。

            5.返回平移后的结果：
            返回包装了平移后结果的 AIS_Shape 对象。
        */
        Handle(AIS_Shape) anAisTranslateShape;

        // 定义平移向量
        gp_Vec translationVector(959.0,0,0);

        // 创建平移变换
        gp_Trsf translationTransformation;
        /*
            translationTransformation: 这是一个 gp_Trsf 类型的对象，表示几何体上的变换。在这里，它被用来表示平移变换。

            SetTranslation(translationVector): 这是 gp_Trsf 类的方法，用于设置平移向量。
            它接受一个 gp_Vec 类型的向量作为参数。在这里，translationVector 是一个 gp_Vec 对象，表示平移的向量。

            这样定义后，在后面，通过 shape.Move(location);，可以将拓扑体沿着指定的平移向量进行平移
        */
        translationTransformation.SetTranslation(translationVector);

        // 应用平移变换到拓扑体
        TopLoc_Location location(translationTransformation);
        shape.Move(location);

        // 创建新的 AIS_Shape 对象来包装平移后的结果
        anAisTranslateShape = new AIS_Shape(shape);

        // 返回平移后的结果
        return anAisTranslateShape;
    }

    /*****************************************************
     * static Handle(AIS_Shape) rotate(TopoDS_Shape shape)
     * 输入：TopoDS_Shape shape 任意拓扑图形
     *
     * TODO: 对图形进行旋转。
     * 取学号末尾三位数字作为坐标实体从而创建方向D，例：假设学号以123结尾，则坐标实体为（1, 2, 3）。
     * 以全局坐标系原点和方向D创建一个坐标轴，作为旋转时的中心轴。
     * 用该中心轴和任意旋转角度设置旋转变换
     * ***************************************************/
    static Handle(AIS_Shape) rotate(TopoDS_Shape shape) {
        /*
        这个函数返回一个 Handle(AIS_Shape)，即OpenCASCADE中用于管理显示对象的智能指针。函数的输入参数是一个 TopoDS_Shape 对象，表示待进行旋转操作的拓扑体。

            1.定义旋转轴的方向向量：
            创建一个 gp_Vec 对象 rotationAxisVector，表示旋转轴的方向向量。在这里，向量的坐标为 (9.0, 5.0, 9.0)。（学号末尾三位数字）

            2.创建旋转轴：
            使用 gp_Ax1 类创建旋转轴 rotationAxis。通过构造函数，指定旋转轴的原点为全局坐标系的原点 (0.0, 0.0, 0.0)，方向为 gp_Dir(rotationAxisVector)。

            3.创建旋转变换：
            使用 gp_Trsf 类创建一个旋转变换 rotationTransformation。通过 SetRotation 方法，将旋转轴和旋转角度设置到这个变换中。

            4.应用旋转变换到拓扑体：
            创建一个 TopLoc_Location 对象 location，将旋转变换设置到这个位置。然后，通过 shape.Move(location); 将旋转变换应用到拓扑体上。

            5.创建新的 AIS_Shape 对象来包装旋转后的结果：
            通过 new AIS_Shape(shape); 创建一个新的 AIS_Shape 对象，用于包装旋转后的拓扑体。

            6.返回旋转后的结果：
            返回包装了旋转后结果的 AIS_Shape 对象。

        */
        Handle(AIS_Shape) anAisRotateShape;

        // 定义旋转轴的方向向量
        gp_Vec rotationAxisVector(9.0, 5.0, 9.0);

        // 创建旋转轴
        gp_Ax1 rotationAxis(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(rotationAxisVector));

        // 创建旋转变换
        gp_Trsf rotationTransformation;
        /*
            rotationTransformation: 这是一个 gp_Trsf 类型的对象，表示几何体上的变换。在这里，它被用来表示旋转变换。

            SetRotation(rotationAxis, 45.0): 这是 gp_Trsf 类的方法，用于设置旋转参数。它接受两个参数：

            rotationAxis: 旋转轴，这是一个 gp_Ax1 类型的对象，表示旋转的轴线。
            45.0: 旋转角度，这里设置为 45.0 度。

            在后面，通过 shape.Move(location);，可以将拓扑体进行旋转
        */
        rotationTransformation.SetRotation(rotationAxis, 45.0);  // 旋转角度为45度，根据实际需求调整

        // 应用旋转变换到拓扑体
        TopLoc_Location location(rotationTransformation);
        shape.Move(location);

        // 创建新的 AIS_Shape 对象来包装旋转后的结果
        anAisRotateShape = new AIS_Shape(shape);

        // 返回旋转后的结果
        return anAisRotateShape;
    }

    /*****************************************************
     * static Handle(AIS_Shape) scale(TopoDS_Shape shape)
     * 输入：TopoDS_Shape shape 任意拓扑图形
     *
     * TODO: 对图形进行缩放。
     * 取学号末尾三位数字为坐标创建中心点，例：假设学号以123结尾，则点坐标为（3, 2, 1）。
     * 以该中心点对图形进行缩放，缩放比例用学号末尾三位数字计算，例如：假设学号以abc结尾，则点坐标为(a+b+c)/10.
     * ***************************************************/
    static Handle(AIS_Shape) scale(TopoDS_Shape shape) {
        /*
        这个函数返回一个 Handle(AIS_Shape)，即 OpenCASCADE 中用于管理显示对象的智能指针。函数的输入参数是一个 TopoDS_Shape 对象，表示待进行缩放操作的拓扑体。

        1.定义缩放的中心点：
        创建一个 gp_Pnt 对象 scaleCenterPoint，表示缩放的中心点。在这里，中心点的坐标为 (9.0, 5.0, 9.0)。

        2.创建缩放变换：
        使用 gp_Trsf 类创建一个缩放变换 scaleTransformation。通过 SetScale 方法，将缩放的中心点和缩放比例设置到这个变换中。

        3.应用缩放变换到拓扑体：
        创建一个 TopLoc_Location 对象 location，将缩放变换设置到这个位置。然后，通过 shape.Move(location); 将缩放变换应用到拓扑体上。

        4.创建新的 AIS_Shape 对象来包装缩放后的结果：
        通过 new AIS_Shape(shape); 创建一个新的 AIS_Shape 对象，用于包装缩放后的拓扑体。

        5.返回缩放后的结果：
        返回包装了缩放后结果的 AIS_Shape 对象。
        */
        Handle(AIS_Shape) anAisScaleShape;

        // 定义缩放的中心点
        gp_Pnt scaleCenterPoint(9.0, 5.0, 9.0);

        // 创建缩放变换
        gp_Trsf scaleTransformation;
        // 取(9.0, 5.0, 9.0)为坐标创建中心点。以该中心点对图形进行缩放，缩放比例用2.3
        scaleTransformation.SetScale(scaleCenterPoint, 2.3);

        // 应用缩放变换到拓扑体
        TopLoc_Location location(scaleTransformation);
        shape.Move(location);

        // 创建新的 AIS_Shape 对象来包装缩放后的结果
        anAisScaleShape = new AIS_Shape(shape);

        // 返回缩放后的结果
        return anAisScaleShape;
    }

    /*****************************************************
     * static Handle(AIS_Shape) mirror(TopoDS_Shape shape)
     * 输入：TopoDS_Shape shape 任意拓扑图形
     *
     * TODO: 对图形进行镜像。
     * 取学号末尾三位数字作为坐标实体从而创建方向D，例：假设学号以123结尾，则坐标实体为（2, 1, 3）。
     * 以全局坐标系原点和方向D创建一个坐标轴，作为镜像的对称轴。
     * ***************************************************/
    static Handle(AIS_Shape) mirror(TopoDS_Shape shape) {
        /*
        这个函数返回一个 Handle(AIS_Shape)，即 OpenCASCADE 中用于管理显示对象的智能指针。函数的输入参数是一个 TopoDS_Shape 对象，表示待进行镜像操作的拓扑体。

            1.定义镜像轴的方向向量：
            创建一个 gp_Vec 对象 mirrorAxisVector，表示镜像轴的方向向量。在这里，向量的坐标为 (5.0, 9.0, 9.0)。

            2.创建镜像轴：
            使用 gp_Ax1 类创建镜像轴 mirrorAxis。通过构造函数，指定镜像轴的原点为全局坐标系的原点 (0.0, 0.0, 0.0)，方向为 gp_Dir(mirrorAxisVector)。

            3.创建镜像变换：
            使用 gp_Trsf 类创建一个镜像变换 mirrorTransformation。通过 SetMirror 方法，将镜像轴设置到这个变换中。

            4.应用镜像变换到拓扑体：
            创建一个 TopLoc_Location 对象 location，将镜像变换设置到这个位置。然后，通过 shape.Move(location); 将镜像变换应用到拓扑体上。

            5.创建新的 AIS_Shape 对象来包装镜像后的结果：
            通过 new AIS_Shape(shape); 创建一个新的 AIS_Shape 对象，用于包装镜像后的拓扑体。

            6.返回镜像后的结果：
            返回包装了镜像后结果的 AIS_Shape 对象
        */
        Handle(AIS_Shape) anAisMirrorShape;

        // 定义镜像轴的方向向量
        gp_Vec mirrorAxisVector(5.0, 9.0, 9.0);

        // 创建镜像轴
        gp_Ax1 mirrorAxis(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(mirrorAxisVector));

        // 创建镜像变换
        gp_Trsf mirrorTransformation;
        // SetMirror将根据mirrorAxis设置一个镜像变换
        mirrorTransformation.SetMirror(mirrorAxis);

        // 应用镜像变换到拓扑体
        TopLoc_Location location(mirrorTransformation);
        // 通过 shape.Move(location); 可以将镜像变换应用到拓扑体上。
        shape.Move(location);

        // 创建新的 AIS_Shape 对象来包装镜像后的结果
        anAisMirrorShape = new AIS_Shape(shape);

        // 返回镜像后的结果
        return anAisMirrorShape;
    }

    /*****************************************************
     * static Handle(AIS_Shape) offset(TopoDS_Shape shape)
     * 输入：TopoDS_Shape shape 任意拓扑图形
     *
     * TODO: 对图形进行偏置。
     * 以学号最后两位数字作为偏移量，对图像进行偏移。例：假设学号以23结尾，则偏移量为23。
     * ***************************************************/
    static Handle(AIS_Shape) offset(TopoDS_Shape shape) {
        // 这里也可以用BRepOffsetAPI_MakeOffsetShape

        // 偏置和平移是两种几何操作，它们都可以根据一个拓扑图形和一个距离，创建一个新的拓扑图形，但它们有以下区别：
        // 平移是将目标对象沿着某一方向进行移动，平移对象几何形状及尺寸均不变，只是位置发生变化；
        // 偏置是将目标对象沿着法向方向移动一定距离，偏置对象的位置不变，但几何形状及尺寸可能发生变化。
        Handle(AIS_Shape) anAisOffsetShape;

        // 创建一个偏置对象，指定图形和偏置量
        // 这里的第3个参数Tol是偏移的容差，用于处理精度问题。
        // Tol这个参数是用于定义偏移后的图形的精度的，它表示两个点之间的最大距离，才能被认为是重合的1。一般来说，Tol的值应该根据图形的尺寸和精细程度来选择，
        // 越小的值表示越高的精度，但也可能导致偏移失败或者效率低下。
        // 使用1.0e-6，它适用于大多数情况。
        BRepOffset_MakeOffset offsetMaker(shape, 59.0,1.0e-6);

        // 检查偏置是否成功
        if (offsetMaker.IsDone()) {
            // 获取偏置后的图形
            TopoDS_Shape offsetShape = offsetMaker.Shape();

            // 创建一个AIS_Shape对象，用于显示
            anAisOffsetShape = new AIS_Shape(offsetShape);
        }

        return anAisOffsetShape;
    }
};

#endif // ADVANCEMODELING_H


