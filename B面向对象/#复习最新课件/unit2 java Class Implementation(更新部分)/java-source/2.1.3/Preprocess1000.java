
import java.io.*;
import java.util.*;

public class Preprocess1000 {

	/**
	 * @param args
	 */
	private static int b;// 版本号
	private static int g;// 故障语句编号
	private static String path1;// 添加编号后的故障版本输出
	private static String path2;// 没添加编号的故障版本输出
	private static String path3;// 正确的输出
	private static String result;
	private static PrintWriter writer;
	private static int fail;
	private static int pass;

	private static int testcases;// 程序执行时测试用例的个数
	private static int statement ;// 程序执行时编号的语句数
	private static int xunhuannumber;// 程序中最外层循环的个数
	// 测试用例数数组
	private static int test[] = { 2, 5, 10, 20, 50, 100, 200, 300, 400, 500,
			600, 700, 800, 900, 1000, 1100, 1200, 1578 };// 不同的版本，最后一个值要改变*******

	private static int fails[];
	private static int passs[];
	private static int total[];
	private static BufferedReader stdIn = new BufferedReader(
			new InputStreamReader(System.in));

	private static void preprocess1() throws IOException {
		String str1 = null;
		String str2 = null;
		BufferedReader file1 = null;
		BufferedReader file2 = null;
		// 比较添加编号后的故障版本输出和没添加编号的故障版本输出是否一致
		for (int i = 1; i <= testcases; i++) {
			file1 = new BufferedReader(new FileReader(path1 + i));// 读添加编号后的故障版本输出
			file2 = new BufferedReader(new FileReader(path2 + i));// 读没添加编号的故障版本输出
			do {
				str1 = file1.readLine();
				str2 = file2.readLine();
				if (str1 == null && str2 == null) {
					break;
				} else if (str1 != null && str2 != null) {
					if (!str1.equals(str2)) {
						writer.println("添加编号后的故障版本输出与没添加编号的输出不一致" + i);
						System.exit(0);
					}
				} else {
					writer.println("添加编号后的故障版本输出与没添加编号的输出不一致" + i);
					System.exit(0);
				}
			} while (true);
			file1.close();
			file2.close();
		}
		//writer.println("Ok1");
	}

	// str是测试用例的执行路径和for循环的信息，ipass表示成功执行或失败执行
	private static void process(String str, Boolean ispass, int j) {
		String path,xunhuan;
		String temp1[];		
		if (str.contains("for")) {
			String tongji[] = str.split("for");
			path = tongji[0]; // 测试用例的执行路径
			xunhuan = tongji[1];
			temp1 = xunhuan.split(" ");
			for (int i = 0; i < temp1.length; ++i) {
				// System.out.println("aaa"+temp1[i]);
				total[i] += Integer.parseInt(temp1[i]);
			}
                } else {
                        path = str;
			Set<String> temp = new HashSet<String>(Arrays.asList(path
					.split(" ")));
			for (String o : temp) {
				if (ispass) {
					passs[Integer.valueOf(o) - 1]++;// pass[执行代码行数-1]表示相应的代码行被成功测试用例执行的次数
													
				} else {
					fails[Integer.valueOf(o) - 1]++;// //fails[执行代码行数-1]表示相应的代码行被失败测试用例执行的次数(aef)
				}
			}
		}
			
			

	}



// 判断哪些测试用例成功，哪些测试用例失败，并根据测试用例执行的相应的路径的信息，统计代码行被成功执行或失败执行的次数
	private static void preprocess2(int ts) throws IOException {
		String str1 = null;
		String str2 = null;
		String str3 = null;
		BufferedReader file1 = null;
		BufferedReader file2 = null;
		int flag=0;
		int ran=0;
                //保证随机选择的测试用例不重复
               ArrayList<Integer> intArr = new ArrayList<Integer> ();
		
		intArr.add(0);
		// 任选ts个result文件，进行信息统计
		for (int i = 1; i <= ts; i++) {
		//随机选一个与以前选的不重复的测试用例
		    while(true) {
			
			flag=0;
			
                        ran = Math.round(new Float(testcases * (Math.random())));
			//System.out.println("yusuande 随机数：  "+ ran);
			if (ran == 0) {
					ran = 1;
			}	
			for(int num:intArr)
			{
				
				if (num==ran) {
					break;					                                
				}
                                
                        }
			
                        intArr.add(ran);
			break;	

                     }
                        intArr.add(ran);
			//System.out.println("随机数：  "+ ran);
			BufferedReader file = new BufferedReader(new FileReader(result+ ran + ".txt"));
			//消除空白行			
			file.readLine();// 添加编号的故障版本每个测试用例执行的输出路径
			

			file1 = new BufferedReader(new FileReader(path1 + ran));// 读添加编号的故障版本输出
																	
			file2 = new BufferedReader(new FileReader(path3 + ran));// 读正确程序的输出
			
																	
			str1 = file1.readLine();
			str2 = file2.readLine();	
			
			//writer.println("对比的两个字符串分别为：" + str1+"----"+str2);		
			if (str1 == null && str2 == null) {
					
					pass++; // 认为该测试用例通过
					process(file.readLine(), true, i);
					//writer.println("两个都为空串");
					
			} else {
																	
				do {
					if (str1 != null && str2 != null) {
						if (!str1.equals(str2)) {
							fail++; // 认为该测试用例失败
							process(file.readLine(), false, i);
							flag=1;
							//writer.println("两个都不为空串，但不相等");
							break;
						} 
					} else {
						//writer.println("对比的两个字符串分别为222：" + str1+"----"+str2);	
						fail++; // 认为该测试用例失败
						process(file.readLine(), false, i);
						flag=1;
						//writer.println("对比的两个字符串分别为333：" + str1+"----"+str2);	
						//writer.println("一个为空串");
						break;
					}
					
					str1 = file1.readLine();
					str2 = file2.readLine();	
					//writer.println("对比的两个字符串分别为444：" + str1+"----"+str2);	
				} while(!(str1 == null && str2 == null));
				
				if(flag==0) {
					pass++; // 认为该测试用例成功
					process(file.readLine(), true, i);
					//writer.println("两个都不为空串，并且相等");	
				}				
			}		
					
			file.close();
                        file1.close();
			file2.close();
		}
		//writer.println("Ok2");
	}
   private static void preprocess3(int ts) throws IOException {
		String str1 = null;
		String str2 = null;
		String str3 = null;
		BufferedReader file1 = null;
		BufferedReader file2 = null;
		
		// 任选ts个result文件，进行信息统计
		for (int i = 1; i <= ts; i++) {
		
		    
			//System.out.println("随机数：  "+ ran);
			BufferedReader file = new BufferedReader(new FileReader(result+ i + ".txt"));
			//消除空白行			
			file.readLine();// 添加编号的故障版本每个测试用例执行的输出路径

			file1 = new BufferedReader(new FileReader(path1 + i));// 读添加编号的故障版本输出
																	
			file2 = new BufferedReader(new FileReader(path3 + i));// 读正确程序的输出
																	
			do {
				// 
				str1 = file1.readLine();
				str2 = file2.readLine();
				if (str1 == null && str2 == null) {
					pass++; // 认为该测试用例通过
					process(file.readLine(), true, i);
					break;
				} else if (str1 != null && str2 != null) {
					if (!str1.equals(str2)) {
						fail++; // 认为该测试用例失败
						process(file.readLine(), false, i);
						break;
					}
				} else {
					fail++; // 认为该测试用例失败
					process(file.readLine(), false, i);
					break;
				}
			} while (true);
			file.close();
                        file1.close();
			file2.close();
		}
		//writer.println("Ok2");
	}

/*
	// 判断哪些测试用例成功，哪些测试用例失败，并根据测试用例执行的相应的路径的信息，统计代码行被成功执行或失败执行的次数
	private static void preprocess2(int ts) throws IOException {
		String str1 = null;
		String str2 = null;
		String str3 = null;
		BufferedReader file1 = null;
		BufferedReader file2 = null;

		for (int i = 1; i <= ts; i++) {
			// 任选ts个result文件，进行信息统计
			int ran = Math.round(new Float(ts * (Math.random())));
			if (ran == 0) {
				ran = 1;
			}
			//System.out.println("随机数：  "+ ran);
			BufferedReader file = new BufferedReader(new FileReader(result+ ran + ".txt"));
			//消除空白行			
			file.readLine();// 添加编号的故障版本每个测试用例执行的输出路径

			file1 = new BufferedReader(new FileReader(path1 + ran));// 读添加编号的故障版本输出
																	
			file2 = new BufferedReader(new FileReader(path3 + ran));// 读正确程序的输出
																	
			do {
				// 
				str1 = file1.readLine();
				str2 = file2.readLine();
				if (str1 == null && str2 == null) {
					pass++; // 认为该测试用例通过
					process(file.readLine(), true, i);
					break;
				} else if (str1 != null && str2 != null) {
					if (!str1.equals(str2)) {
						fail++; // 认为该测试用例失败
						process(file.readLine(), false, i);
						break;
					}
				} else {
					fail++; // 认为该测试用例失败
					process(file.readLine(), false, i);
					break;
				}
			} while (true);
			file.close();
                        file1.close();
			file2.close();
		}
		//writer.println("Ok2");
	}
      */
	public static void main(String[] args) throws IOException {

			//运行18种类型的测试套件，测试用例数分别存储在test数组中
			/*bugInfo.txt中存储每个程序版本的信息（版本号b,程序执行时编号的语句数statement，
			程序执行时测试用例的个数testcases,程序中最外层循环的个数xunhuannumber,故障语句的编号g）*/
		for (int t =9; t <10; t++) {//调试 （2）---正常修改为18//for1

                        BufferedReader in = new BufferedReader(new FileReader("bugInfo.txt"));
			String s = in.readLine();

                        //s代表某个程序某个版本的相关信息
			while (s != null) {//while2
				int multiset=1;
				int multisetUp=10000;
				double totalScore1=0;
				double totalScore2=0;
				double totalScore3=0;
				double totalScore4=0;
				int averRank1=0;
				int averRank2=0;
				int averRank3=0;
				int averRank4=0;
				int loop=0;
				//每类测试套件执行的统计得分结果存储在scoreOutput1.txt (......)	
				writer = new PrintWriter(new FileWriter("./score1000/" + t+ ".txt"),true);
                                //对不同多重集而言，版本信息不变，只不过是重新计算得分
				StringTokenizer st = new StringTokenizer(s, ",");
				b = Integer.parseInt(st.nextToken());
				statement = Integer.parseInt(st.nextToken());
				testcases = Integer.parseInt(st.nextToken());
				xunhuannumber = Integer.parseInt(st.nextToken());
				g = Integer.parseInt(st.nextToken());
				fails = new int[statement];
				passs = new int[statement];
				total = new int[xunhuannumber];
	                        writer.println("版本=" + b + ",  故障语句编号=" + g);

				// 处理不同的实验程序此处需要修改*********************************
				path1 = new String("./versions/v" + b + "/outputgai/t");// 添加编号后的故障版本输出
				//path2 = new String("./versions/v" + b + "/outputyuan/t");// 没添加编号的故障版本输出
				path3 = new String("./source/outputs/t");// 正确的输出
				result = new String("./versions/v" + b + "/fail/fail");// 每个测试用例的执行路径保存为一个文件

				// 比较添加编号后的故障版本输出和没添加编号的故障版本输出是否一致,已经有的实验内容，compareSF.java进行比较
				//preprocess1();
				  //表示每套测试用例运行次数（10000），然后，相当于多重集为1万个，求总平均分	
				System.out.println("第" +(t+1)+"个测试套件：");
				//如果是测试用例的最大数，多重集就1个
                                if (t==17) {
					multisetUp=2;				
				}
				while (multiset<multisetUp){//while1
					
					
					for (int k = 0; k < statement; k++) {
						fails[k] = 0;
						passs[k] = 0;
					}

					for (int m = 0; m < xunhuannumber; m++) {
						total[m] = 0;
					}  

					System.out.println("       正在处理第 "+t+" 个测试套件的第 "+multiset+" 个多重集，请稍等");
					
					fail = 0;
					pass = 0;

					// 判断哪些测试用例成功，哪些测试用例失败
					// 并根据测试用例执行的相应路径的信息，统计代码行被成功执行或失败执行的次数
					if (t==17) {
						//如果t是17，就不用随机抽取了
						preprocess3(test[t]);
                                        } else {					
						//如果t不是最大17，则就从最大的测试用例集中随机选取一部分，						
						preprocess2(test[t]);
					}


					// 用四种方法分别计算排名
					int[] O = new int[statement];
					int[] Op = new int[statement];
					double[] Tarantula = new double[statement];
					double[] Jaccard = new double[statement];
                                        //排名计算公式再考察一遍
					for (int i = 0; i < statement; i++) {
						if (fail - fails[i] > 0)// anf>0,-1
						{
							O[i] = -1;
						} else {
							O[i] = pass - passs[i];// anp
						}
					}

					
					for (int i = 0; i < statement; i++) {
						Op[i] = fails[i]*(pass + 1) - passs[i];
					}


					for (int i = 0; i < statement; i++) {
						double factor1 = (double)fails[i] /(double)fail;
						double factor2 =(double) passs[i] /(double)pass;
						//writer.println("fails： "+i+"[]---"+fails[i]);
						//writer.println("passs:  "+i+"[]---"+passs[i]);
						//writer.println("factor1： "+factor1);
						//writer.println("factor2： "+factor2);
                                                if(Math.abs(factor1 + factor2-0)<1e-6)  {
							Tarantula[i] =0;
							//writer.println("语句排名： "+(i+1)+"   "+Tarantula[i]);
						} else {
							Tarantula[i] = factor1 / (factor1 + factor2);
                                        	        //writer.println("语句排名： "+(i+1)+"   "+Tarantula[i]);
						}
					}


					for (int i = 0; i < statement; i++) {
						Jaccard[i] = (double)fails[i] / (double)(fail + passs[i]);
					}
/*
					//打印排名：
					writer.print("O各语句的排名：");
					for (int i = 0; i < statement; i++) {
						
						writer.print("("+i+", "+O[i]+")"+",");
                                                writer.flush();
						
					}
					writer.println();
					writer.print("Op各语句的排名：");
					for (int i = 0; i < statement; i++) {
						
						writer.print("("+i+", "+Op[i]+")"+",");
                                                writer.flush();
						
					}
					writer.println();
					writer.print("Taranla各语句的排名：");
					for (int i = 0; i < statement; i++) {
						
						writer.print("("+i+", "+Tarantula[i]+")"+",");
                                                writer.flush();
						
					}
					writer.println();
					writer.print("Jaccard各语句的排名：");
					for (int i = 0; i < statement; i++) {
						
						writer.print("("+i+", "+Jaccard[i]+")"+",");
                                                writer.flush();
						
					}
*/
					//writer.println();
					//writer.println("成功测试用例的个数：" + pass);
					//writer.println("失败测试用例的个数：" + fail);
					//writer.println("经过故障语句的成功测试用例数：" + passs[g-1]);
					//writer.println("经过故障语句的失败测试用例数：" + fails[g-1]);
					// 计算得分
					int k1 = 0;
					int k2 = 0;
					int k3 = 0;
					int k4 = 0;
					int p1 = O[g - 1];// 故障语句的排名
					int p2 = Op[g - 1];
					double p3 = Tarantula[g - 1];
					double p4 = Jaccard[g - 1];
					
					for (int i = 0; i < statement; i++) {//for2
						// p1总是存储哪个最大的排名
						if (O[i] == O[g - 1] && p1 == O[g - 1]) { // k1存储
							k1++;
							//writer.println("语句"+i+"时，k1的变化:---" + k1);
						} else if (O[i] > p1) {
							if (p1 == O[g - 1]) {
								k1 = 2;
								//writer.println("语句"+i+"时，k1的变化:---" + k1);
							} else {
								k1++;
								//writer.println("语句"+i+"时，k1的变化:---" + k1);
							}
							p1 = O[i];

							// System.out.println(p1 + "  " + i);
						}


						if (Op[i] == Op[g - 1] && p2 == Op[g - 1]) {
							k2++;
						} else if (Op[i] > p2) {
							if (p2 == Op[g - 1]) {
								k2 = 2;
							} else {
								k2++;
							}
							p2 = Op[i];
							// System.out.println(p2 + "  " + i);
						}
						
						//Math.abs(a-b)<1e-6
						if ((Math.abs(Tarantula[i]- Tarantula[g-1])<1e-6)&& (Math.abs(p3 - Tarantula[g - 1])<1e-6)) { 
							k3++;
						} else if (Tarantula[i] > p3) {
							if (Math.abs(p3-Tarantula[g - 1])<1e-6) {
								k3 = 2;
							} else {
								k3++;
							}
							p3 = Tarantula[i];

							// System.out.println(p1 + "  " + i);
						}

						if((Math.abs(Jaccard[i] -Jaccard[g - 1])<1e-6)&& (Math.abs(p4 -Jaccard[g - 1])<1e-6)) { 
							k4++;
						} else if (Jaccard[i] > p4) {
							if (Math.abs(p4-Jaccard[g - 1])<1e-6) {
								k4 = 2;
							} else {
								k4++;
							}
							p4 = Jaccard[i];

							// System.out.println(p1 + "  " + i);
						}

					}//for2

				
					if (p1 == O[g - 1] && k1 != 0) {
						totalScore1+=1.0 / k1;						
						averRank1+=1;
					} else {
						averRank1+=k1;
					}

					
					if (p2 == Op[g - 1] && k2 != 0) {
						totalScore2+=1.0 / k2;
						averRank2+=1;
					} else {
						averRank2+=k2;
					}

					
					if (p3 == Tarantula[g - 1] && k3 != 0) {
						totalScore3+=1.0 / k3;
						averRank3+=1;
					} else {
						averRank3+=k3;
					}

					
					if (p4 == Jaccard[g - 1] && k4 != 0) {
						totalScore4+=1.0 / k4;
						averRank4+=1;
					} else {
						averRank4+=k4;
					}
                                       /*
					writer.println("k1为:---" + k1);
					writer.println("k2为:---" + k2);
					writer.println("k3为:---" + k3);
					writer.println("k4为:---" + k4);
					writer.println("averRank1为:---" + averRank1);
					writer.println("averRank2为:---" + averRank2);
					writer.println("averRank3为:---" + averRank3);
					writer.println("averRank4为:---" + averRank4);
					writer.println("totalScore1为:---" + totalScore1);
					writer.println("totalScore2为:---" + totalScore2);
					writer.println("totalScore3为:---" + totalScore3);
					writer.println("totalScore4为:---" + totalScore4);
                                      */
					
					
					for (int i = 0; i < xunhuannumber; i++) {
						loop +=total[i]/test[t];
					}
					//下一个多重集
					multiset+=1;
					//System.out.println(multiset);	
					
				}//while1

				//所有多重集计算完毕，进行总平均
			
				
                                totalScore1=totalScore1/(double)(multiset-1);
				totalScore2=totalScore2/(double)(multiset-1);
				totalScore3=totalScore3/(double)(multiset-1);
				totalScore4=totalScore4/(double)(multiset-1);
                                averRank1=averRank1/(multiset-1);
				averRank2=averRank2/(multiset-1); 
				averRank3=averRank3/(multiset-1);
				averRank4=averRank4/(multiset-1);
				loop=loop/(multiset-1);
				writer.println("O：    ");					
				writer.println("总平均分为:---" + totalScore1);				
				writer.println("平均排名:---" + averRank1);
				
				writer.println("Op:    ");					
				writer.println("总平均分为:---" + totalScore2);				
				writer.println("平均排名:---" + averRank2);
				
				writer.println("Tarantula:    ");		
				writer.println("总平均分为:---" + totalScore3);				
				writer.println("平均排名:---" + averRank4);
				
				writer.println("Jaccard:    ");					
				writer.println("总平均分为:---" + totalScore4);				
				writer.println("平均排名:---" + averRank4);
				writer.println("平均loop:    "+loop); 
				writer.close();
                                       
			//处理下一个版本		
			s = in.readLine();   
		}//while2 
		in.close();		
	}//for1  
				
			System.out.println("finish!!!!!!!!");
 }

}
