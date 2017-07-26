
import java.awt.*;
import java.awt.event.*;
import java.io.*;

import javax.xml.transform.*;
import javax.xml.transform.stream.*;
	 
	
    class transform {
		 // 建構子 
		   public transform() {
			   
		   }
		   // 建立HTML文件
		   public void buildHTML(String xmlData,
		     String htmlFile, String xsltFile) throws Exception {
		      // 建立TransformerFactory物件
		      TransformerFactory tff =
		                 TransformerFactory.newInstance();
		      // 建立Transformer物件
		      Transformer tf = tff.newTransformer(
		                 new StreamSource(xsltFile));
		      // 轉換XML
		      tf.transform(new StreamSource(
		                   new StringReader(xmlData)), 
		                   new StreamResult(
		                   new FileOutputStream(htmlFile)));
		      System.out.println("XSLT轉換成功:"+htmlFile);
		   }
	}
	public class XSLT implements ActionListener {
	    Frame frame;
	    Button button1, button2,button3; 
	    FileDialog filedialog1, filedialog2,filedialog3;
	     
	    public static void main(String[] args) {
	        new XSLT();
	    }
	     
	    public XSLT() {
	        frame = new Frame("XSLT");
	        frame.addWindowListener(new AdapterDemo());
	        frame.setLayout(new FlowLayout());
	        frame.setSize(250, 100);
	         
	        button1 = new Button("XML");
	        button1.addActionListener(this);
	        button1.setActionCommand("XML");
	        button2 = new Button("XSL");
	        button2.addActionListener(this);
	        button2.setActionCommand("XSL");
	        button3 =new Button("start!");
	        button3.addActionListener(this);
	        button3.setActionCommand("Start!");
	        
	         
	        frame.add(button1);
	        frame.add(button2);
	        frame.add(button3);
	         
	        frame.setVisible(true);
	    }
	     
	    public void actionPerformed(ActionEvent e) {
	        if (e.getActionCommand() == "XML") {
	            filedialog1 = new FileDialog(frame);
	             
	            filedialog1.setMode(FileDialog.LOAD);
	            filedialog1.setFile("*.xml");
	            System.out.println("getDirectory(): " + filedialog1.getDirectory());
	            System.out.println("getFile(): " + filedialog1.getFile());
	            System.out.println("getMode(): " + filedialog1.getMode());
	         
	            filedialog1.setVisible(true);
	        }
	         
	        if (e.getActionCommand() == "XSL") {
	            filedialog2 = new FileDialog(frame);
	         
	            filedialog2.setMode(FileDialog.LOAD);
	            filedialog2.setFile("*.xsl");
	            System.out.println("getDirectory(): " + filedialog2.getDirectory());
	            System.out.println("getFile(): " + filedialog2.getFile());
	            System.out.println("getMode(): " + filedialog2.getMode());
	         
	            filedialog2.setVisible(true);
	        }
	        
	        if(e.getActionCommand()=="Start!")
	        {
	        	filedialog3 = new FileDialog(frame);
	            
	            filedialog3.setMode(FileDialog.SAVE);
	            filedialog3.setFile("*.html");
	            System.out.println("getDirectory(): " + filedialog3.getDirectory());
	            System.out.println("getFile(): " + filedialog3.getFile());
	            System.out.println("getMode(): " + filedialog3.getMode());
	             
	            filedialog3.setVisible(true);
	        	System.out.println("XSLT");
	        	System.out.println(filedialog1.getDirectory()+filedialog1.getFile());
	        	transform app = new transform();
	        	BufferedReader br;
	        	try {
	    			br = new BufferedReader(new FileReader(filedialog1.getDirectory()+filedialog1.getFile()));
	    		
	    	      String strLine;
	    	      StringBuffer strBuffer = new StringBuffer();
	    	      // 讀取XML文件的內容
	    	      while ( (strLine = br.readLine()) != null ) {
	    	         strBuffer.append(strLine+"\n");
	    	      }
	    	      // 呼叫方法建立轉換輸出的HTML文件        
	    	      app.buildHTML(strBuffer.toString(), 
	    	    		  filedialog3.getDirectory()+filedialog3.getFile(), filedialog2.getDirectory()+filedialog2.getFile());
	    	      
	    		}
	        	catch (Exception e1) {
	    			// TODO Auto-generated catch block
	    			e1.printStackTrace();
	    		}
	        }
	    }
	}
	
	class AdapterDemo extends WindowAdapter {
	    public void windowClosing(WindowEvent e) {
	        System.exit(0);
	    }
	}
