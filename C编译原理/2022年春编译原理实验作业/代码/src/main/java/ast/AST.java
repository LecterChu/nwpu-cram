package ast;

import gen.MIDLLexer;
import gen.MIDLParser;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

import java.io.*;
import java.util.Scanner;

/**
 * MIDL源代码到抽象语法树的分析程序
 *
 * @author suyuzhang
 * @version 1.0
 */

public class AST {
    private static final String OUTPUT_FILE_NAME = "./src/main/txt/SyntaxOut"; // 输出格式化的AST

    public static void main(String[] args) throws Exception {
        System.out.println("请输入文件地址(比如 ./src/main/txt/test1.txt )：");
        Scanner sc = new Scanner(System.in);
        String inputFileName = sc.next();
        File inputFile = new File(inputFileName);
        if (inputFile.exists() && inputFile.isFile()) {
            System.out.println("Successfully!\n");
        } else {
            System.out.println("ERROR: Invalid file!");
            return;
        }

        BufferedReader bufferedReader = new BufferedReader(new FileReader(inputFile));
        String fileName = inputFileName.substring(inputFileName.lastIndexOf('/') + 1); // 获取文件名部分
        String number = fileName.replaceAll("[^\\d]", ""); // 去除非数字字符
        File outputFile = new File(OUTPUT_FILE_NAME + number + ".txt");
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(outputFile));

        // 如果想一次读取整个文件
        StringBuilder line = new StringBuilder();
        String t;
        while ((t = bufferedReader.readLine()) != null) {
            line.append(t);
        }

        // 如果每次读入一行MIDL完整代码，然后输入给antlr递归程序
        CharStream input = CharStreams.fromString(line.toString());
        MIDLLexer lexer = new MIDLLexer(input);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        MIDLParser parser = new MIDLParser(tokens);
        ParseTree tree = parser.specification();
        ASTTree ag = new ASTTree();
        ag.visit(tree);

        bufferedWriter.write(ag.astParseTree + "\n");
        bufferedWriter.flush();

        bufferedReader.close();
        bufferedWriter.close();
        System.out.println("输出结果已保存到 " + outputFile);
    }
}

