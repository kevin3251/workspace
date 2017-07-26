//判斷碰撞的方法是以Separating Axis Theorem為主
//固定讀TEST.txt檔
import java.awt.geom.Point2D;
import java.util.Arrays;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
public class RectangleWorld {
	//static Scanner scanner = new Scanner(System.in);
	private static Rectangle[] R;
	public static double Dot(Point2D.Double P,Point2D.Double A){
		return P.getX()*A.getX()+P.getY()*A.getY(); 
	}
	public static void setRectangleWorld() throws IOException{
		FileReader F = new FileReader("TEST.txt");
		BufferedReader B = new BufferedReader(F);
		String Str = B.readLine();  
		int N = Integer.parseInt(Str);
		R = new Rectangle[N];
		for(int i=0;i<N;i++){
			String[] Hold = new String[6];
			Str = B.readLine();
			Hold = Str.split("\\s");
			Point2D.Double P1,P2,P3,P4,A1,A2;
			P1 = new Point2D.Double(Double.parseDouble(Hold[0]),Double.parseDouble(Hold[1]));
			P2 = new Point2D.Double(Double.parseDouble(Hold[2]),Double.parseDouble(Hold[3]));
			P3 = new Point2D.Double(Double.parseDouble(Hold[4]),Double.parseDouble(Hold[5]));
			P4 = new Point2D.Double(P1.getX()+(P3.getX()-P2.getX()), P1.getY()+(P3.getY()-P2.getY()));
			A1 = new Point2D.Double((P2.getX()-P1.getX())/P1.distance(P2), (P2.getY()-P1.getY())/P1.distance(P2));
			A2 = new Point2D.Double((P3.getX()-P2.getX())/P3.distance(P2), (P3.getY()-P2.getY())/P3.distance(P2));
			R[i] = new Rectangle(P1,P2,P3,P4,A1,A2);
		}
		F.close();
	}
	//先把Rectangle A的四個點放進APoints陣列中,以此類推
	//在把兩個Rectangle的兩個軸放進Axes陣列
	//從Separating Axis Theorem得知,兩個Rectangle在每個軸上的投影都重疊的話,這兩個Rectangle就會碰撞
	//而如果其中一個軸上的投影沒重疊,就不會碰撞
	//因此我們可以分別從每個軸,一個一個地判斷
	//透過從該軸跟一個Rectanle的四個點的內積所取得的量,找出最大跟最小的量
	//再從另一個Rectangle的四個點,跟四個軸的內積所取得的量,找出最大跟最小的量
	//之後從兩個Rectangle的最大跟最小的量,看看範圍上是否重疊
	//當有一個軸上的範圍沒重疊時,return false
	//如果都重疊,return true,表示碰撞
	public static boolean Overlap(Rectangle A,Rectangle B){
		Point2D.Double[] APoints = {A.getP1(),A.getP2(),A.getP3(),A.getP4()};
		Point2D.Double[] BPoints = {B.getP1(),B.getP2(),B.getP3(),B.getP4()};
		Point2D.Double[] Axes = {A.getAxis1(),A.getAxis2(),B.getAxis1(),B.getAxis2()};
		double ProjAMin=0,ProjAMax=0; // 用來抓取Rectangle A的最大,最小的內積 
		double ProjBMin=0,ProjBMax=0; // 用來抓取Rectangle B的最大,最小的內積 
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if(j==0){
					ProjAMin = Dot(APoints[j],Axes[i]);
					ProjAMax = ProjAMin;
					ProjBMin = Dot(BPoints[j],Axes[i]);
					ProjBMax = ProjBMin;
				}else{
					double TempA = Dot(APoints[j],Axes[i]);
					double TempB = Dot(BPoints[j],Axes[i]);
					if(TempA<ProjAMin)
						ProjAMin = TempA;
					if(TempA>ProjAMax)
						ProjAMax = TempA;
					if(TempB<ProjBMin)
						ProjBMin = TempB;
					if(TempB>ProjBMax)
						ProjBMax = TempB;	
				}
			}
			if(( ProjAMin > ProjBMax)||ProjBMin > ProjAMax) //判斷範圍上是否重疊
				return false;
		}
	   return true;
	}
	public static void main(String[] args) throws IOException{ 
		setRectangleWorld();
		Arrays.sort(R);
		for(Rectangle Buf : R){
			if(Buf!=R[0]){
				if(!Overlap(R[0],Buf))
				   Buf.PrintRectangle();
			}
			else
				Buf.PrintRectangle();;
		}
	}
}
