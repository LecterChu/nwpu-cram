package precheck;

import gen.MIDLLexer;
import gen.MIDLParser;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

/**
 * 从指定的输入文件中读取代码，并依次进行词法分析、语法分析和语义分析
 *
 * @author suyuzhang
 * @version 1.0
 */

public class PreCheck {
    // private static final String inputFileName = "./src/main/txt/inputLines.txt";

    public static SemanticAnalysis mc;

    /**
     * 预检查方法
     *
     * @param inputFileName 输入文件名
     * @return 处理后的文件名
     * @throws IOException IO异常
     */
    public static String preCheck(String inputFileName) throws IOException {
        // 读取文件内容
        BufferedReader bufferedReader = new BufferedReader(new FileReader(inputFileName));
        StringBuilder codes = new StringBuilder();
        String line;
        while ((line = bufferedReader.readLine()) != null) {
            codes.append(line).append("\n");
        }

        // 解析输入内容
        CharStream input = CharStreams.fromString(codes.toString());
        MIDLLexer lexer = new MIDLLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        MIDLParser parser = new MIDLParser(tokens);
        ParseTree tree = parser.specification();

        // 语义分析
        mc = new SemanticAnalysis();
        mc.visit(tree);

        // 打印语义分析结果
        if (mc.er.getErrors().isEmpty()) {
            System.out.println("The code is semantically correct.");
        } else {
            System.err.println("Errors TraceBack: ");
            System.err.println(mc.er.getErrors());
        }

        // 获取文件名部分
        String fileName = inputFileName.substring(inputFileName.lastIndexOf('/') + 1);
        String name = fileName.split("\\.")[0];
        bufferedReader.close();
        return name;
    }

    public static void main(String[] args) throws IOException {
        System.out.println("请输入文件地址(比如 ./src/main/test/test1.txt )：");
        Scanner sc = new Scanner(System.in);
        String inputFileName = sc.next();
        preCheck(inputFileName);
        sc.close();
    }
}

