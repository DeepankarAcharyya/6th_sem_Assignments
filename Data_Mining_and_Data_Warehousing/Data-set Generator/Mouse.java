import java.awt.*;  
import java.awt.event.*;  
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import javax.swing.*;

public class Mouse extends Frame implements MouseListener{  
    
  /*  static PrintWriter output;

    public static void myFile() throws IOException{
        File myObj=new File("Output_Co_Ordinates.txt");
            if(myObj.createNewFile()){
                System.out.println("File Created : "+myObj.getName());
            }
            else{
                System.out.println("File already exists.");
            }
            
            output=new PrintWriter("Output_Co_Ordinates.txt");
    }
*/
    Mouse(){  
       //----------------------------------------------
        addMouseListener(this);  
        setSize(800,800);
        setLayout(null);  
        setVisible(true);
    }  
    public void mouseClicked(MouseEvent e) {  
        Graphics g=getGraphics();  
        g.setColor(Color.BLUE);  
        g.fillOval(e.getX(),e.getY(),10,10);
        System.out.println(e.getX()+","+e.getY());  
    }  
    public void mouseEntered(MouseEvent e) {}  
    public void mouseExited(MouseEvent e) {}  
    public void mousePressed(MouseEvent e) {}  
    public void mouseReleased(MouseEvent e) {}  
      
public static void main(String[] args) throws IOException {
    //myFile();
    new Mouse();  
}  
}  