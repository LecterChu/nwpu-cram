package precheck;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * 处理语句
 *
 * @author suyuzhang
 * @version 1.0
 */
public class Calculator {
    public static ArrayList<String> exps= new ArrayList<String>();
    public static ArrayList<String> nums= new ArrayList<String>();

    /**
     * 用于检测整数是否溢出，根据参数 numss 和 isPos 来判断是否为正数溢出。
     *
     * @param numss numss
     * @return boolean
     */
    static boolean checkOverFlow(String numss,boolean isPos)
    {
        String up = "32767";
        String down = "32768";
        if(isPos)
        {
            return !(numss.length() <= 5 && (numss.length() != 5 || (numss.compareTo(up) <= 0)));
        }
        else
        {
            return !(numss.length() <= 5 && (numss.length() != 5 || (numss.compareTo(down) <= 0)));
        }
    }


    /**
     * 预处理，将算式中的运算符和数字分别存储在 exps 和 nums 数组列表中
     *
     * @param inputs 输入
     */
    public static void preProcess(String inputs)
    {

        //初始化nums栈
        exps.clear();
        nums.clear();

        String REPLACE = " ";
        String EXPREGEX = "\\*|\\+|-|/|%|<<|>>|&|\\^|~|\\|";
        Pattern p = Pattern.compile(EXPREGEX);
        Matcher m = p.matcher(inputs);
        String tp = m.replaceAll(REPLACE);
        String []splitss = tp.split("\\s+");
        for(String ss:splitss){
            if(ss.length()>0)nums.add(ss);
//            System.out.println(nums.get(nums.size()-1));
        }

        //初始化exps栈
        String NUMREGEX = "\\d*";
        p = Pattern.compile(NUMREGEX);
        m = p.matcher(inputs);
        tp = m.replaceAll(REPLACE);
        splitss = tp.split("\\s+");
        for(int i=0;i < splitss.length;i++){
            if(splitss[i].length()>0) {
                if(splitss[i].equals("<")||splitss[i].equals(">")){
                    exps.add(splitss[i]+splitss[++i]);
                }
                else exps.add(splitss[i]);
                System.out.println(exps.get(exps.size()-1));
            }
        }
    }

    /**
     * 根据输入的算式、类型和正负标志，进行运算并返回结果。该方法会先进行预处理，
     * 然后通过遍历 exps 和 nums 列表，根据运算符和操作数进行相应的计算。在计算过程中，会检查整数是否溢出，并返回相应的错误信息。
     *
     * @param inputs 输入
     * @param type   类型
     * @param isPos  是pos
     * @return {@link String}
     */
    public static String calAns(String inputs,String type,boolean isPos)
    {
        preProcess(inputs);
        String temp = "";
        label:
        while(exps.size()>0)
        {
            String exp = exps.get(exps.size()-1);
            String num1 = nums.get(nums.size()-1);
            String num2 = "";
            int a = 0,b=0;
            float c=0,d=0;
            if(nums.size() > 1)
                num2 = nums.get(nums.size()-2);


            if(type.equals("INTEGER")) {
                try {
                    if (nums.size() > 1) a = Integer.parseInt(num2);
                    b = Integer.parseInt(num1);
                }catch (Exception e){
                    temp="TypeError";
                    return temp;
                }
            }
            else if(type.equals("FLOATING_PT")){
                try {
                    if (nums.size() > 1) c = Float.parseFloat(num2);
                    d = Float.parseFloat(num1);
                }catch(Exception e){
                    temp="TypeError";
                    return temp;
                }
            }

            switch (exp) {
                case "+":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a + b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else if (type.equals("FLOATING_PT")) {
                        temp = Float.toString(c + d);
                    }
                    break;
                case "-":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a - b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else if (type.equals("FLOATING_PT")) {
                        temp = Float.toString(c - d);
                    }
                    break;
                case "*":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a * b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else if (type.equals("FLOATING_PT")) {
                        temp = Float.toString(c * d);
                    }
                    break;
                case "/":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a / b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else {
                        temp = Float.toString(c / d);
                    }
                    break;
                case "<<":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a << b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else {
                        //表示本来应该是int类型
                        temp = "TypeError";
                        break label;
                    }
                    break;
                case ">>":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a >> b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }

                    } else {
                        //表示本来应该是int类型
                        temp = "TypeError";
                        break label;
                    }
                    break;
                case "|":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a | b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else {
                        temp = "TypeError";
                        break label;
                    }
                    break;
                case "&":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a & b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else {
                        temp = "TypeError";
                        break label;
                    }
                    break;
                case "^":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a ^ b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else {
                        temp = "TypeError";
                        break label;
                    }
                    break;
                case "%":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(a % b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else {
                        //表示本来应该是int类型
                        temp = "TypeError";
                        break label;
                    }
                    break;
                case "~":
                    if (type.equals("INTEGER")) {
                        try {
                            temp = Integer.toString(~b);
                        } catch (Exception e) {
                            temp = "overflow";
                            return temp;
                        }
                        if (checkOverFlow(temp, isPos)) {
                            temp = "overflow";
                            return temp;
                        }
                    } else {
                        //表示本来应该是int类型
                        temp = "TypeError";
                        break label;
                    }
                    break;
            }

            //弹出和放入
            if(!exp.equals("~")){
                nums.remove(nums.size()-1);
                if(nums.size()>1)nums.remove(nums.size()-2);
            }
            else nums.remove(nums.size()-1);
            exps.remove(exps.size()-1);
            nums.add(temp);
        }
        if(nums.size()>0)temp = nums.get(nums.size()-1);
        return temp;
    }

}


