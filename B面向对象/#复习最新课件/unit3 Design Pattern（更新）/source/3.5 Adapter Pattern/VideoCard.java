
public class VideoCard extends GraphicSender{
	
	private CPU cpu;
	
	public VideoCard(CPU cpu){
		
		this.cpu=cpu;
	}
	public String requests(){
		return cpu.getData();
	}
	
}
