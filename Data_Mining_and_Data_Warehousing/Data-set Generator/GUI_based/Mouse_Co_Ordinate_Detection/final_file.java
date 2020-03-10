//for mouse-event-handling
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/*
                                    OBJECTIVES
--- JFrame is displayed---------------------------------------------------------Done
--- display the co-ordinates only when thte mouse is clicked--------------------Done
--- display the clicked points--------------------------------------------------Done
*/

class final_file extends JFrame implements MouseListener{

 final_file(){
    this.addMouseListener(this);  
    this.setSize(800,800);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setVisible(true);
 }

 public void mouseClicked(MouseEvent event){  
    Graphics g=getGraphics();  
    g.setColor(Color.BLUE);  
    g.fillOval(event.getX(),event.getY(),10,10);
        
    System.out.println("x = "+ event.getX() + " y = " + event.getY());      
}

 public void mouseEntered(MouseEvent event){}

 public void mouseExited(MouseEvent event){}

 public void mousePressed(MouseEvent event){}

 public void mouseReleased(MouseEvent e){
    
 }

 public static void main(String[] args){
    new final_file();
    }

}