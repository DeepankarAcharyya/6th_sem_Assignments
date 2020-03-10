//for mouse-event-handling
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*
                                    OBJECTIVES
--- JFrame is displayed---------------------------------------------------------Done
--- display the co-ordinates only when thte mouse is clicked--------------------Done
--- display the clicked points
*/

class final_file extends JFrame implements MouseListener{

 final_file(){
    JFrame frame =new JFrame("Data-set Frame");
       
    frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    frame.addMouseListener(this);

    int width=500, height=500;
    frame.setSize(width, height);
    frame.setVisible(true);
 }

 public void mouseClicked(MouseEvent event){  
    System.out.println("x = "+ event.getX() + " y = " + event.getY());      
    drawPoints(event.getX(),event.getY());
}

 public void mouseEntered(MouseEvent event){}

 public void mouseExited(MouseEvent event){}

 public void mousePressed(MouseEvent event){}

 public void mouseReleased(MouseEvent e){
    
 }

 public void drawPoints(int x,int y){
    Graphics g=getGraphics();
    g.drawOval(x,y,x,y);  
    g.setColor(Color.BLUE);  
    g.fillOval(x,y,10,10); 
 }

 public static void main(String[] args){
    new final_file();
    }

}