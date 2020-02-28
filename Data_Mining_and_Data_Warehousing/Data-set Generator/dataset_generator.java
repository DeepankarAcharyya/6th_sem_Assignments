//for filehandling
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
//for mouse-event-handling
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class dataset_generator extends JFrame implements MouseListener{
    PrintWriter output;

    dataset_generator(){
        JFrame frame = new JFrame("Data-Point Generator");
        frame.addMouseListener(this);
        frame.setSize(500, 500);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setVisible(true);
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
    
    public static void main(String[] args) throws IOException{
        try{
            //-------------------------------File Creation-------------------------------
            File myObj=new File("Output_Co_Ordinates.txt");
            if(myObj.createNewFile()){
                System.out.println("File Created : "+myObj.getName());
            }
            else{
                System.out.println("File already exists.");
            }
        
            output=new PrintWriter("Output_Co_Ordinates.txt");
            //--------------------------------------------------------------------------

            
            new dataset_generator();
             
            output.close();
            
           }catch (IOException e){
            System.out.println("An error occured.");
            e.printStackTrace();
        }
   }
}