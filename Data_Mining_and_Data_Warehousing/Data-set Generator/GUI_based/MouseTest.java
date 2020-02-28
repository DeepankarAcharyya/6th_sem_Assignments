import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
  
public class MouseTest
{
    JLabel label;
    JPanel child;
  
    public void setText(int x, int y)
    {
        String s = "";
        if(x > 0 && y > 0)
            s = "x = " + x + "  y = " + y;
        label.setText(s);
    }
  
    private JPanel getContent()
    {
        label = new JLabel();
        label.setHorizontalAlignment(JLabel.CENTER);
        GridBagLayout gridbag = new GridBagLayout();
        GridBagConstraints gbc = new GridBagConstraints();
        child = new JPanel(gridbag);
        child.setBorder(BorderFactory.createEtchedBorder());
        child.setPreferredSize(new Dimension(400,400));
        child.add(label, gbc);
        JPanel parent = new JPanel(gridbag);
        parent.setOpaque(true);
        parent.add(child, gbc);
        return parent;
    }
  
    public static void main(String[] args)
    {
        MouseTest test = new MouseTest();
        JPanel panel = test.getContent();
        panel.addMouseMotionListener(new MotionSensor(test));
        JFrame f = new JFrame();
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setContentPane(panel);
        f.setSize(500,500);
        f.setLocation(200,200);
        f.setVisible(true);
    }
}
  
class MotionSensor extends MouseMotionAdapter
{
    MouseTest mouseTest;
    boolean overChild;
  
    public MotionSensor(MouseTest mt)
    {
        mouseTest = mt;
        overChild = false;
    }
  
    public void mouseMoved(MouseEvent e)
    {
        Point p = e.getPoint();
        Rectangle r = mouseTest.child.getBounds();
        if(r.contains(p))
        {
            if(!overChild)
                overChild = true;
            // you can do this by hand
            int x = p.x - r.x;
            int y = p.y - r.y;
            mouseTest.setText(x, y);
  
            //   --- or ---
  
            // let SwingUtilities do the work
            //Component source = (Component)e.getSource();
            //Point xp = SwingUtilities.convertPoint(source, p, mouseTest.child);
            //mouseTest.setText(xp.x, xp.y);
        }
        else if(overChild)  // reset
        {
            overChild = false;
            mouseTest.setText(-1, -1);
        }
    }
}