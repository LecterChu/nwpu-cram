package precheck;

import java.util.ArrayList;

/**
 * 收集记录错误信息
 *
 * @author suyuzhang
 * @version 1.0
 */
public class ErrorRecorder {
    public ArrayList<String> errors; // 一个字符串数组列表，用于存储错误信息。
    public final static String[] ErrorType ={"命名冲突，重复定义","未定义即使用","类型错误","溢出","数组越界"}; // 一个包含错误类型字符串的常量数组。

    /**
     * 错误记录
     */
    public ErrorRecorder()
    {
        this.errors=new ArrayList<String>();
    }

    /**
     * 向错误列表中添加错误信息
     * 接收参数包括行号 line，错误类型 type，名称 name，错误代码 error 和期望值 expected。根据参数生成相应的错误信息，并添加到错误列表中。
     *
     * @param line     行
     * @param type     类型
     * @param name     名字
     * @param error    错误
     * @param expected 预期
     */
    public void addError(String line,String type,String name,int error,String expected)
    {
        if(expected==null)
            errors.add("line "+line+" exception:" + type + " " + name + " "+ErrorType[error]);
        else
            errors.add("line "+line+" exception:" + type + " " + name + " "+ErrorType[error]+" , Expected: "+expected);
    }

    /**
     * 将错误列表中的所有错误信息组合成一个字符串，并返回该字符串。
     *
     * @return {@link String}
     */
    public String getErrors()
    {
        StringBuilder allError= new StringBuilder();
        for(String error:errors)
        {
            allError.append(error).append("\n");
        }
        return allError.toString();
    }

}
