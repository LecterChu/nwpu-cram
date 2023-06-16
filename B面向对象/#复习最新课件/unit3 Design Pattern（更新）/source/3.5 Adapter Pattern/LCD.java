public class LCD{
	
	public static void main(String[] args){
		
		GraphicSender gs = new VideoCard(new CPU());
		System.out.println(gs.request());
		
	}
}