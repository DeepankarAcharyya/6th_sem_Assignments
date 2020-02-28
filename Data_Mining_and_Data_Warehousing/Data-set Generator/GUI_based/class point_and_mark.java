import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class point_and_mark { 
    public static void main(String[] args) {
        JFrame frame = new JFrame("Frame");
        frame.setSize(500, 500);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setVisible(true);
    
        Timer timer = new Timer(66, new ActionListener() {
    
            @Override
            public void actionPerformed(ActionEvent e) {
                Point p = MouseInfo.getPointerInfo().getLocation();
                p = new Point(p.x - frame.getLocation().x, p.y - frame.getLocation().y);
                System.out.println("Mouse: " + p);
    
            }
        });
        timer.start();
    }
}