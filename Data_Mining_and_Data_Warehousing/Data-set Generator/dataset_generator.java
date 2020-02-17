//for filehandling
import java.io.IOException;
import java.io.FileWriter;
//for mouse-event-handling
import java.awt.*;
import java.awt.event.*;

class dataset_generator extends Frame implements MouseListener , MouseMotionListener
{
    int pos_x,pos_y;
    String str=" "; //will be replaced by a counter

    public MouseXY()
  {
    addMouseListener(this);
    addMouseMotionListener(this);

    setSize(300, 300);
    setVisible(true);
  }

  /*  public MouseStart(){
        addMouseListener(this);
        addMouseMotionListener(this);

        setSize(300,300);
        setVisible(true);
    }
*/
    public void mouseClicked(MouseEvent e){
        pos_x=e.getX();
        pos_y=e.getY();
        str="Mouse Clicked";
        repaint();
    }

    public void paint(Graphics g){
        g.setFont(new Font("Monospaced", Font.BOLD, 20));
        g.fillOval(pos_x, pos_y, 10, 10);                 // gives the bullet
        g.drawString(pos_x + "," + pos_y,  pos_x+10, pos_y -10);  // displays the x and y position
        g.drawString(str, pos_x+10, pos_y+20);
    }

    public static void main(String[] args) throws IOException {
        FileWriter fd=new FileWriter("Co_ordinates.txt");
        System.out.println("File opened!!");
        fd.close();

        //new MouseStart();
        new MouseXY();
    }
}