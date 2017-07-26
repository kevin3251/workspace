import java.awt.geom.Point2D;
public class Rectangle implements Comparable <Rectangle>{
	private Point2D.Double P1,P2,P3,P4,Axis1,Axis2;
	private double Area; 
	
	//使用Separating Axis Theorem判斷碰撞所需要的2個向量軸 ,Axis1為第一個軸的向量,以此類推
	public void setArea(double Area){
		this.Area = Area;
	}
	public void setP1(Point2D.Double P){
		P1 = P;
	}
	public void setP2(Point2D.Double P){
		P2 = P;
	}
	public void setP3(Point2D.Double P){
		P3 = P;
	}
	public void setP4(Point2D.Double P){
		P4 = P;
	}
	public void setAxis1(Point2D.Double A){
		Axis1 = A;
	}
	public void setAxis2(Point2D.Double A){
		Axis2 = A;
	}
	public double getArea(){
		return this.Area;
	}
	public Point2D.Double getP1(){
		return this.P1;
	}
	public Point2D.Double getP2(){
		return this.P2;
	}
	public Point2D.Double getP3(){
		return this.P3;
	}
	public Point2D.Double getP4(){
		return this.P4;
	}
	public Point2D.Double getAxis1(){
		return this.Axis1;
	}
	public Point2D.Double getAxis2(){
		return this.Axis2;
	}
	public void PrintRectangle(){ //輸出Rectangle的資料
		System.out.printf("%f %f %f %f %f%n",P1.getX(),P1.getY(),P2.getX(),P2.getY(),P3.getX());
		System.out.printf("%f A=%f%n",P3.getY(),this.getArea());
	}
	public Rectangle(Point2D.Double P1,Point2D.Double P2,Point2D.Double P3,Point2D.Double P4,Point2D.Double A1,Point2D.Double A2){
		setP1(P1);
		setP2(P2);
		setP3(P3);
		setP4(P4);
		setAxis1(A1);
		setAxis2(A2);
		setArea(P1.distance(P2)*P2.distance(P3));
	}
	@Override
	//implements Comparable 需要的compareTo函式 ,sort會使用
	public int compareTo(Rectangle R) {
		return (int)(R.getArea()-this.getArea());
	}	
}
