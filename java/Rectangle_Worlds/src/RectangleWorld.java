//�P�_�I������k�O�HSeparating Axis Theorem���D
//�T�wŪTEST.txt��
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
	//����Rectangle A���|���I��iAPoints�}�C��,�H������
	//�b����Rectangle����Ӷb��iAxes�}�C
	//�qSeparating Axis Theorem�o��,���Rectangle�b�C�Ӷb�W����v�����|����,�o���Rectangle�N�|�I��
	//�Ӧp�G�䤤�@�Ӷb�W����v�S���|,�N���|�I��
	//�]���ڭ̥i�H���O�q�C�Ӷb,�@�Ӥ@�Ӧa�P�_
	//�z�L�q�Ӷb��@��Rectanle���|���I�����n�Ҩ��o���q,��X�̤j��̤p���q
	//�A�q�t�@��Rectangle���|���I,��|�Ӷb�����n�Ҩ��o���q,��X�̤j��̤p���q
	//����q���Rectangle���̤j��̤p���q,�ݬݽd��W�O�_���|
	//���@�Ӷb�W���d��S���|��,return false
	//�p�G�����|,return true,��ܸI��
	public static boolean Overlap(Rectangle A,Rectangle B){
		Point2D.Double[] APoints = {A.getP1(),A.getP2(),A.getP3(),A.getP4()};
		Point2D.Double[] BPoints = {B.getP1(),B.getP2(),B.getP3(),B.getP4()};
		Point2D.Double[] Axes = {A.getAxis1(),A.getAxis2(),B.getAxis1(),B.getAxis2()};
		double ProjAMin=0,ProjAMax=0; // �Ψӧ��Rectangle A���̤j,�̤p�����n 
		double ProjBMin=0,ProjBMax=0; // �Ψӧ��Rectangle B���̤j,�̤p�����n 
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
			if(( ProjAMin > ProjBMax)||ProjBMin > ProjAMax) //�P�_�d��W�O�_���|
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
