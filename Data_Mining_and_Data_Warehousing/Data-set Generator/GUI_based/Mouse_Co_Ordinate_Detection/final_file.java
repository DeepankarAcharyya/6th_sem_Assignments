
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
//for mouse-event-handling
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*
                            OBJECTIVES
--- JFrame is displayed
--- display the co-ordinates only when thte mouse is clicked
--- display the points
*/
class myMouseListener implements MouseListener{
     
 public void mouseClicked(MouseEvent event){  
    System.out.println("x = "+ event.getX() + " y = " + event.getY());      
 }

 public void mouseEntered(MouseEvent event){}

 public void mouseExited(MouseEvent event){}

 public void mousePressed(MouseEvent event){}

 public void mouseReleased(MouseEvent e){
    // Graphics g=getGraphics();  
    // g.setColor(Color.BLUE);  
    // g.fillOval(e.getX(),e.getY(),10,10);
 }
}


public class final_file {
    
   public static void main(String[] args){
       JFrame frame =new JFrame("Data-set Frame");
       
       frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
       frame.addMouseListener(new myMouseListener());

       int width=500, height=500;
       frame.setSize(width, height);
       frame.setVisible(true);
   }
}
