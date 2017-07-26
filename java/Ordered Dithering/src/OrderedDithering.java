
import javax.imageio.ImageIO;
import java.net.URL;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.awt.Color;
import java.io.File;

public class OrderedDithering {

	private static URL imgUrl;
	private static BufferedImage img;
	private static int width;
	private static int height;
	
	public final static int[] ditherMatrix ={
			  0,  32,   8,  40,   2,  34,  10,  42,
			 16,  48,  24,  58,  18,  50,  26,  58,
			  4,  36,  12,  44,   6,  38,  14,  46,
			 20,  52,  28,  60,  22,  54,  30,  62,
			  1,  33,   9,  41,   3,  35,  11,  43,
			 17,  49,  25,  57,  19,  51,  27,  59,
			  5,  37,  13,  45,   7,  39,  15,  47,
			 21,  53,  29,  61,  23,  55,  31,  63
	};

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		imgUrl = new URL("http://www.ece.rice.edu/~wakin/images/lena512.bmp");
		
		//從URL抓取圖片
		img = ImageIO.read(imgUrl);
		width = img.getWidth();
		height = img.getHeight();
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				Color c = new Color(img.getRGB(j, i));
				int gray = (c.getGreen() + c.getRed() + c.getBlue())/3;
				if((gray/4) > ditherMatrix[j%8*8+i%8]){
					img.setRGB(j, i, new Color(0,0,0).getRGB());    //將像素設為黑色
				}else{
					img.setRGB(j, i, new Color(255,255,255).getRGB());   //將像素設為白色
				}
			}
		}
		File output = new File("output.bmp");   //輸出檔案
		ImageIO.write(img, "bmp", output);   //寫入輸出檔案
		System.out.println("finished");
	}

}
