<%@ page contentType="text/html;charset=big5" %>
<%@ page import= "java.sql.*"%>
<%@ page import= "java.io.*" %>

<html>
<head><title>Delivery</title></head><body>
<p align="left">
<font size="5"><b>列印送貨單</b></font>
</p>
<%
  String JDriver = "net.ucanaccess.jdbc.UcanaccessDriver";
  String connectDB="jdbc:ucanaccess://C:\\Program Files\\Apache Software Foundation\\Tomcat 8.0\\webapps\\ROOT\\20151211\\CloudShopping.accdb";


  Class.forName(JDriver);
  Connection con = DriverManager.getConnection(connectDB);
  Statement stmt = con.createStatement();
  
  
  request.setCharacterEncoding("big5");
  String MsgName = request.getParameter("ID");
  String cartView = cartStr+"View";

   
  String sql="SELECT * FORM RegistryClient WHERE 証號= '"+
			cartStr+"';";
	
  if(stmt.execute(sql)){
	  ResultSet rsl =stmt.getResult();
	  While(rsl.next()){
		  %>
		  名稱:<%=rsl.getString("名稱")%><br>
		  地址:<%=rsl.getString("地址")%><br>
		  電話:<%=rsl.getString("電話")%><br>
		  貨品:<br>
		  <%
	  }
  }
  String sq2="SELECT * FORM "+ cartStr;
  if(stmt.execute(sq2)){
	  ResultSet rs2 =stmt.getResult();
	  %>
	  <TABLE BORDER = "1">
	  <TR><TD>編號</TD><TD>品名</TD><TD>單價</TD>
	  </TR><%
	  while(rs2.next()){
		  String indexStr=rs2.getString("編號");
		  String nameStr = rs2.getString("品名");
		  String priceStr =rs2.getString("單價");
		  
		  out.print("<TR>");
		  out.print("<TD>");
		  out.print(indexStr);
		  out.print("</TD>");
		  out.print("<TD>");
		  out.print(nameStr);
		  out.print("</TD>");
		  out.print("<TD>");
		  out.print(priceStr);
		  out.print("</TD>");
		  out.print("</TR>");
	  }
	  out.print("</TABLE>");
	}
  String sql3="SELECT * FORM "+cartView;
  out.print("合計: ");
  
  if(stmt.execute(sql3)){
	  ResultSet rs3 =stmt.getResult();
	  While(rs3.next()){
		  out.print(rs3.getString("單價之總計"));
	  }
  }
   stmt.close();
   con.close();
}
 %>
</body>
</html>