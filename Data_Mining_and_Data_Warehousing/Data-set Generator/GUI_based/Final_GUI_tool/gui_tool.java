import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class gui_tool extends JFrame implements MouseListener {
     gui_tool(){

        this.addMouseListener(this);  
        this.setSize(800,800);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
     }
     
     public void file_write(int x,int y) throws IOException{
        FileWriter file=new FileWriter("Output_Co_Ordinates.txt");
        file.write("["+x+"," + y+"]");
        file.close();
     }

     public void mouseClicked(MouseEvent event){  
        Graphics g=getGraphics();  
        g.setColor(Color.BLUE);  
        g.fillOval(event.getX(),event.getY(),10,10);    
        System.out.println("x = "+ event.getX() + " y = " + event.getY());
        try {
            file_write(event.getX(),event.getY());
        } catch (Exception e) {
            System.out.println("Exception generated!");
        }      
    }
    
     public void mouseEntered(MouseEvent event){}
    
     public void mouseExited(MouseEvent event){}
    
     public void mousePressed(MouseEvent event){}
    
     public void mouseReleased(MouseEvent e){
        
     }
    
     public static void main(String[] args) throws IOException{
        new gui_tool();
    }
    
}