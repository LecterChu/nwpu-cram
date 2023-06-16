import java.util.*;

public class StringTokenizerClassDemo {

	public static void main(String[] args) {

		//字符串按用户要求解析为单词序列示例
		String str = "This string has five tokens";
		StringTokenizer tokenizer = new StringTokenizer(str);

		int i = 1;
		
		  for (;i<tokenizer.countTokens();i++) { System.out.println("Token #" +
		  i + ": " + tokenizer.nextToken()); }
		 
		 /*
		while (tokenizer.hasMoreTokens()) {
			System.out.println("Token #" + i + ":  " + tokenizer.nextToken());
			++i;
		}	
		*/	
	}
}